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
using System.Json;
using System.Linq;
using System.Reflection;
using System.Text;
using SlimDX.Generator.Parsing;

namespace SlimDX.Generator
{
	class Program
	{
		static void Main(string[] arguments)
		{
			var options = new Queue<string>(arguments);
			while (options.Count > 0)
			{
				var option = options.Dequeue();
				switch (option)
				{
					case "-parse":
						if (options.Count == 0)
							throw new InvalidOperationException("-parse requires one argument");
						var configurationFile = options.Dequeue();
						RunParser(configurationFile);
						break;
					case "-generate":
						if (options.Count == 0)
							throw new InvalidOperationException("-generate requires one argument");
						var modelFile = options.Dequeue();
						RunGenerator(modelFile);
						break;
				}
			}
		}

		static void RunParser(string configurationFile)
		{
			var configuration = new ConfigFile(configurationFile);
			var configurationDirectory = Path.GetDirectoryName(Path.GetFullPath(configurationFile));

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

			// run the parser on the preprocessed file to generate a model of the file in memory
			var grammarFile = Path.Combine(configurationDirectory, configuration.GetOption("Options", "Grammar"));
			var parser = new HeaderParser(grammarFile);
			var root = parser.Parse(source).ToXml();

			root.Save("test.xml");

			// Transform XML to JSON.
			JsonObject json = ModelXml.Transform(root);
			File.WriteAllText("test.json", json.ToJson());
		}

		static void RunGenerator(string modelFile)
		{
			var outputDirectory = Path.GetDirectoryName(Path.GetFullPath(modelFile));

			var json = File.ReadAllText(modelFile);
			var api = ModelJson.Parse(JsonObject.FromJson(json));

			var generatorDirectory = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
			var defaultMetadataDirectory = Path.Combine(generatorDirectory, @"Resources\Metadata");
			var defaultTemplateDirectory = Path.Combine(generatorDirectory, @"Templates");
			var templateEngine = new TemplateEngine(new[] { defaultTemplateDirectory });
			templateEngine.RegisterCallback("Namespace", (e, s) => "SlimDX.DXGI");
			templateEngine.RegisterCallbacks(typeof(TemplateCallbacks));

			if (!Directory.Exists(outputDirectory))
				Directory.CreateDirectory(outputDirectory);

			foreach (var item in api.Interfaces)
			{
				var outputPath = Path.Combine(outputDirectory, item.Name + ".cs");
				if (File.Exists(outputPath))
					File.Delete(outputPath);
				File.WriteAllText(outputPath, templateEngine.ApplyByName("Interface", item));
			}

			TrampolineAssemblyBuilder trampolineBuilder = new TrampolineAssemblyBuilder();
			foreach (var interfaceModel in api.Interfaces)
			{
				foreach (var methodModel in interfaceModel.Methods)
				{
					List<TrampolineParameter> parameters = new List<TrampolineParameter>();
					foreach (var parameterModel in methodModel.Parameters)
					{
						TrampolineParameterFlags flags = TrampolineParameterFlags.Default;
						parameters.Add(new TrampolineParameter(parameterModel.Type.MarshallingType, flags));
					}

					trampolineBuilder.Add(new Trampoline(methodModel.Type.MarshallingType, parameters.ToArray()));
				}
			}

			trampolineBuilder.CreateAssembly(string.Format("{0}.Trampoline", "SlimDX.DXGI"));
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
					output.AppendLine(line);
			}

			File.WriteAllText(preprocessedFile, output.ToString());
		}
	}
}
