// Copyright (c) 2007-2010 SlimDX Group
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

namespace SlimDX.Generator
{
	class Program
	{
		static void Main(string[] args)
		{
			string configFile = "config.txt";
			if (args != null & args.Length > 0 && !string.IsNullOrWhiteSpace(args[0]))
				configFile = args[0].Trim();

			if (!File.Exists(configFile))
				Console.WriteLine("Could not open config file \"{0}\".", configFile);
			else
			{
#if !DEBUG
				try
				{
#endif
				Run(configFile);
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
		/// Runs the generator using options specified in the given config file.
		/// </summary>
		/// <param name="configFile">The config file.</param>
		static void Run(string configFile)
		{
			var options = new ConfigFile(configFile);

			// run boost::wave on the primary source file to get a preprocessed file and a list of macros
			var preprocessor = new Preprocessor(options);
			Console.WriteLine(preprocessor.Run());

			// before parsing, run some transformations on the preprocessed file to
			// both cut down on the size needed to be examined as well as to get rid of
			// junk I was too lazy to add to the parser grammar.
			// this includes dropping any source that is not from the given primary or ancillary
			// sources, which is indicated in the preprocessed file by #line directives
			var source = preprocessor.Source;
			var relevantSources = options.GetOptions("AncillarySources").Concat(new[] { Path.Combine(Directory.GetCurrentDirectory(), source) });
			source = Path.ChangeExtension(source, ".i");
			PreTransform(source, new HashSet<string>(relevantSources));

			// run the parser on the preprocessed file to generate a model of the file in memory
			var parser = new HeaderParser(options.GetOption("Options", "Grammar"));
			var root = parser.Parse(source).ToXml();
			var model = new SourceModel(root, options.GetOption("Options", "NamingRules"), options.GetOptions("TypeMap"));
			var templateEngine = new TemplateEngine(options.GetOption("Options", "Templates"), options.GetOption("Options", "Namespace"));
			var outputPath = options.GetOption("Options", "OutputPath");

			templateEngine.RegisterCallback("GenerateFunctionBody", GenerateFunctionBody);

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
					var returnType = model.TypeMap[function.ReturnType.Name];
					var parameterTypes = new List<TrampolineParameter>();
					foreach (var parameterElement in function.Parameters)
					{
						//TODO: Instead of ignoring unmappable types like this, we should error out.
						Type type = null;
						if (model.TypeMap.TryGetValue(parameterElement.DataType.Name, out type))
							parameterTypes.Add(new TrampolineParameter(type));
					}
					trampolineBuilder.Add(new Trampoline(returnType, parameterTypes.ToArray()));
				}
			}

			trampolineBuilder.CreateAssembly("SlimDX.Trampoline");

			// write output files
			File.WriteAllText(Path.Combine(outputPath, "Enums.cs"), templateEngine.Apply("EnumFile.txt", model));
			foreach (var item in model.Structs)
				File.WriteAllText(Path.Combine(outputPath, item.NiceName + ".cs"), templateEngine.Apply("Struct.txt", item));

			foreach (var item in model.Interfaces)
				File.WriteAllText(Path.Combine(outputPath, item.NiceName + ".cs"), templateEngine.Apply("Interface.txt", item));
		}

		static string GenerateFunctionBody(object o)
		{
			return "// Trampoline invocation will go here eventually.";
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
