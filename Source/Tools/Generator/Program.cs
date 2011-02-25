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

namespace SlimDX.Generator
{
	class Program
	{
		static void Main(string[] arguments)
		{
			if (arguments.Length == 0)
				throw new InvalidOperationException("Missing configuration file path.");

			var configuration = new ConfigFile(arguments[0]);

			// build up the Json model by running it through various layers
			JsonObject json = null;
			var searchPaths = new HashSet<string>();
			foreach (var layer in configuration.GetOptions("JsonLayers"))
			{
				// $ParseHeaders runs the parser to build the Json
				// other options are simple filenames, relative to the config file
				JsonObject current;
				if (layer == "$ParseHeaders")
					current = RunParser(configuration);
				else
				{
					var path = layer.RootPath(configuration.ConfigurationDirectory);
					current = JsonObject.FromJson(File.ReadAllText(path));
					searchPaths.Add(Path.GetDirectoryName(Path.GetFullPath(path)));
				}

				// combine the current layer with the base
				if (json == null)
					json = current;
				else
					CompositingEngine.Compose(json, current);
			}

			// run the generator on the composed Json model
			RunGenerator(json, configuration, searchPaths);
		}

		static JsonObject RunParser(ConfigFile configuration)
		{
			// run boost::wave on the primary source file to get a preprocessed file and a list of macros
			var preprocessor = new Preprocessor(configuration);
			Console.WriteLine(preprocessor.Run());

			// before parsing, run some transformations on the preprocessed file to cut down on the size needed to be examined
			// this includes dropping any source that is not from the given primary or ancillary
			// sources, which is indicated in the preprocessed file by #line directives
			var source = preprocessor.Source;
			var rawSources = configuration.GetOptions("AncillarySources").Concat(new[] { Path.Combine(Directory.GetCurrentDirectory(), source) });
			var relevantSources = new List<string>();
			foreach (string s in rawSources)
				relevantSources.Add(Environment.ExpandEnvironmentVariables(s));

			source = Path.ChangeExtension(source, ".i");
			Preprocessor.PostTransform(source, relevantSources.ToSet());

			// run the parser on the preprocessed file to generate a model of the file in memory
			var grammarFile = configuration.GetOption("Options", "Grammar").RootPath(configuration.ConfigurationDirectory);
			var parser = new HeaderParser(grammarFile);
			var root = parser.Parse(source).ToXml();
			var json = ModelXml.Transform(root);

			// add a dependency to the base SlimDX.json file
			json.Add("dependencies", new JsonObject(new JsonObject[] { "../SlimDX/SlimDX.json" }));

			// TODO: for testing only
			root.Save("test.xml");
			File.WriteAllText("test.json", json.ToNiceJson());

			return json;
		}

		static void RunGenerator(JsonObject json, ConfigFile configuration, IEnumerable<string> searchPaths)
		{
			var api = ModelJson.Parse(json, searchPaths);

			var defaultMetadataDirectory = Path.Combine(configuration.GeneratorDirectory, @"Resources\Metadata");
			var defaultTemplateDirectory = Path.Combine(configuration.GeneratorDirectory, @"Templates");
			var templateEngine = new TemplateEngine(new[] { defaultTemplateDirectory });

			var namespaceName = configuration.GetOption("Options", "Namespace");
			templateEngine.RegisterCallback("EnumItem", (e, s) => ((dynamic)s).Name.EndsWith("FORCE_DWORD") ? string.Empty : ((dynamic)s).Name + " = " + ((dynamic)s).Value + ",");
			templateEngine.RegisterCallback("Namespace", (e, s) => namespaceName);
			templateEngine.RegisterCallbacks(typeof(TemplateCallbacks));

			var outputDirectory = configuration.GetOption("Options", "OutputPath").RootPath(configuration.ConfigurationDirectory);
			if (!Directory.Exists(outputDirectory))
				Directory.CreateDirectory(outputDirectory);

			ApplyTemplate(api.Enumerations, outputDirectory, templateEngine, "Enumeration");
			ApplyTemplate(api.Structures, outputDirectory, templateEngine, "Structure");
			ApplyTemplate(api.Interfaces, outputDirectory, templateEngine, "Interface");

			BuildTrampolineAssembly(api, outputDirectory, string.Format("{0}.Trampoline", namespaceName));
		}

		static void BuildTrampolineAssembly(ApiModel api, string outputDirectory, string outputFile)
		{
			TrampolineAssemblyBuilder trampolineBuilder = new TrampolineAssemblyBuilder();
			foreach (var interfaceModel in api.Interfaces)
			{
				foreach (var methodModel in interfaceModel.Methods)
				{
					var parameters = new List<TrampolineParameter>();
					foreach (var parameterModel in methodModel.Parameters)
					{
						TrampolineParameterFlags flags = TrampolineParameterFlags.Default;
						if (parameterModel.Flags.HasFlag(ParameterModelFlags.IsOutput))
							flags |= TrampolineParameterFlags.Reference;
						var trampolineType = parameterModel.Type.MarshallingType;
						if (trampolineType == typeof(Guid))
							trampolineType = typeof(void*);
						parameters.Add(parameterModel.Type == TypeModel.VoidModel ? new TrampolineParameter(typeof(IntPtr), flags) : new TrampolineParameter(trampolineType, flags));
					}

					trampolineBuilder.Add(new Trampoline(methodModel.Type.MarshallingType, parameters.ToArray()));
				}
			}

			trampolineBuilder.CreateAssembly(outputDirectory, outputFile);
		}

		static void ApplyTemplate(IEnumerable<TypeModel> items, string outputDirectory, TemplateEngine templateEngine, string templateName)
		{
			foreach (var item in items)
			{
				var outputPath = Path.Combine(outputDirectory, item.Name + ".cs");
				if (File.Exists(outputPath))
					File.Delete(outputPath);
				File.WriteAllText(outputPath, templateEngine.ApplyByName(templateName, item));
			}
		}
	}
}
