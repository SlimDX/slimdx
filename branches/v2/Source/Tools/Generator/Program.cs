// Copyright (c) 2007-2011 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Linq;
using SlimDX.Generator.Parsing;
using SlimDX.Generator.ObjectModel;
using System.Reflection;
using System.Xml.Linq;

namespace SlimDX.Generator
{
	class Program
	{
		static void Main(string[] args)
		{
			var xml = XDocument.Load("DXGI.xml");
			var api = ModelXml.Parse(xml.Root);

			var configurationFile = @"config.txt";
			if (args != null & args.Length > 0 && !string.IsNullOrWhiteSpace(args[0]))
				configurationFile = args[0].Trim();

			if (!File.Exists(configurationFile))
				Console.WriteLine("Could not open config file \"{0}\".", configurationFile);
			else
			{
#if !DEBUG
				try
				{
#endif
				Run(configurationFile);
#if !DEBUG
				}
				catch (Exception e)
				{
					Console.WriteLine("Exception occurred: " + e.ToString());
				}
#endif
			}
		}

		/// <summary>
		/// Runs the generator using options specified in the given configuration file.
		/// </summary>
		/// <param name="configurationFile">The configuration file.</param>
		static void Run(string configurationFile)
		{
			var configuration = new ConfigFile(configurationFile);
			var configurationDirectory = Path.GetDirectoryName(Path.GetFullPath(configurationFile));
			var generatorDirectory = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
			var defaultMetadataDirectory = Path.Combine(generatorDirectory, @"Resources\Metadata");
			var defaultTemplateDirectory = Path.Combine(generatorDirectory, @"Templates");

			var templateEngine = new TemplateEngine(new[] { defaultTemplateDirectory });
			templateEngine.RegisterCallback("Namespace", (e, s) => configuration.GetOption("Options", "Namespace"));
			templateEngine.RegisterCallbacks(typeof(TemplateCallbacks));

			// run boost::wave on the primary source file to get a preprocessed file and a list of macros
			var preprocessor = new Preprocessor(configuration, configurationDirectory);
			Console.WriteLine(preprocessor.Run());

			// before parsing, run some transformations on the preprocessed file to
			// both cut down on the size needed to be examined as well as to get rid of
			// junk I was too lazy to add to the parser grammar.
			// this includes dropping any source that is not from the given primary or ancillary
			// sources, which is indicated in the preprocessed file by #line directives
			var source = preprocessor.Source;
			var rawSources = configuration.GetOptions("AncillarySources").Concat(new[] { Path.Combine(Directory.GetCurrentDirectory(), source) });
			var relevantSources = new List<string>();
			foreach (string s in rawSources)
				relevantSources.Add(Environment.ExpandEnvironmentVariables(s));

			source = Path.ChangeExtension(source, ".i");
			PreTransform(source, new HashSet<string>(relevantSources));

			var nameServiceFile = Path.Combine(configurationDirectory, configuration.GetOption("Options", "NamingRules"));
			var nameService = new NameRules(nameServiceFile);
			var metadataService = new MetadataService(new[] { defaultMetadataDirectory });

			// run the parser on the preprocessed file to generate a model of the file in memory
			var grammarFile = Path.Combine(configurationDirectory, configuration.GetOption("Options", "Grammar"));
			var parser = new HeaderParser(grammarFile);
			var root = parser.Parse(source).ToXml();

			var model = new SourceModel(root, nameService, metadataService, configuration.GetOptions("TypeMap"));
			var outputPath = Path.Combine(configurationDirectory, configuration.GetOption("Options", "OutputPath"));

			root.Save("test.xml");

			if (!Directory.Exists(outputPath))
				Directory.CreateDirectory(outputPath);
			else
			{
				foreach (var file in Directory.EnumerateFiles(outputPath, "*.*"))
					File.Delete(file);
			}

			var trampolineBuilder = new TrampolineAssemblyBuilder();
			foreach (var item in model.Interfaces)
			{
				foreach (var function in item.Functions)
				{
					var parameterTypes = new List<TrampolineParameter>();
					foreach (var parameter in function.Parameters)
					{
						var parameterFlags = TrampolineParameterFlags.Default;
						if ((parameter.Usage & UsageQualifiers.Out) != 0)
							parameterFlags = TrampolineParameterFlags.Reference;

						parameterTypes.Add(new TrampolineParameter(parameter.Type.IntermediateType, parameterFlags));
					}
					trampolineBuilder.Add(new Trampoline(function.ReturnType.IntermediateType, parameterTypes.ToArray()));
				}
			}

			trampolineBuilder.CreateAssembly("SlimDX.Trampoline");

			// write output files
			File.WriteAllText(Path.Combine(outputPath, "Enums.cs"), templateEngine.ApplyByName("EnumFile", model));
			foreach (var item in model.Structures)
				File.WriteAllText(Path.Combine(outputPath, item.ManagedName + ".cs"), templateEngine.ApplyByName("Structure", item));

			foreach (var item in model.Interfaces)
				File.WriteAllText(Path.Combine(outputPath, item.ManagedName + ".cs"), templateEngine.ApplyByName("Interface", item));
		}

		/// <summary>
		/// Performs transformations on a preprocessed file to prepare it for parsing.
		/// </summary>
		/// <param name="preprocessedFile">The preprocessed file.</param>
		/// <param name="relevantSources">The relevant sources. 
		/// Any code that did not originate in one of these sources is removed before parsing.</param>
		static void PreTransform(string preprocessedFile, HashSet<string> relevantSources)
		{
			var output = new StringBuilder();
			bool keepSource = false;
			foreach (var line in File.ReadLines(preprocessedFile))
			{
				if (line.StartsWith("#line"))
				{
					int start = line.IndexOf('"') + 1;
					var file = line.Substring(start, line.LastIndexOf('"') - start).Replace(@"\\", "\\");

					keepSource = relevantSources.Contains(file);
				}
				else if (!line.StartsWith("#pragma") && keepSource)
				{
					// static was annoying me when trying to write a grammar without ambiguities,
					// so I'm just going to remove it here for now
					output.AppendLine(line.Replace("static", ""));
				}
			}

			File.WriteAllText(preprocessedFile, output.ToString());
		}
	}
}
