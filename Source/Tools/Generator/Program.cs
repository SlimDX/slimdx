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
using System.Linq;
using System.Reflection;
using Newtonsoft.Json.Linq;
using System.Runtime.InteropServices;
using SlimDX.Api;

namespace SlimDX.Generator
{
    class Program
    {
        /// <summary>
        /// The application's entry point.
        /// </summary>
        /// <param name="arguments">The command line arguments.</param>
        static void Main(string[] arguments)
        {
            if (arguments.Length == 0)
                throw new InvalidOperationException("Missing configuration file path.");

            var configuration = new Configuration(arguments[0]);
            if (!string.IsNullOrEmpty(configuration.PrimaryHeader))
            {
                var searchPaths = new HashSet<string>();
                var json = RunParser(configuration);
                foreach (var layer in configuration.Layers)
                {
                    JObject current = null;
                    current = JObject.Parse(File.ReadAllText(layer));
                    searchPaths.Add(Path.GetDirectoryName(Path.GetFullPath(layer)));

                    // combine the current layer with the base
                    if (json == null)
                        json = current;
                    else
                        CompositingEngine.Compose(json, current);
                }

                var generatedModelFile = Path.Combine(configuration.GeneratorOutputPath, configuration.ApiName + ".json");
                File.WriteAllText(generatedModelFile, json.ToString());

                // run the generator on the composed Json model
                var api = ModelJson.Parse(json, searchPaths);
                RunGenerator(api, configuration);
            }
            else
            {
                var dependencies = new List<ApiModel>();
                foreach (var dependencyPath in configuration.DependencyModelPaths)
                    dependencies.Add(ModelJson.Parse(JObject.Parse(File.ReadAllText(dependencyPath)), new string[] { }));

                var api = ModelReader.FromFile(configuration.Layers[0], dependencies);
                RunGenerator(api, configuration);
            }
        }


        static JObject RunParser(Configuration configuration)
        {
            // run boost::wave on the primary source file to get a preprocessed file and a list of macros
            var preprocessor = new Preprocessor(configuration);
            Console.WriteLine(preprocessor.Run());

            // before parsing, run some transformations on the preprocessed file to cut down on the size needed to be examined
            // this includes dropping any source that is not from the given primary or ancillary
            // sources, which is indicated in the preprocessed file by #line directives
            var source = preprocessor.Source;
            var rawSources = configuration.AdditionalHeaders.Concat(new[] { Path.Combine(Directory.GetCurrentDirectory(), source) });
            var relevantSources = new List<string>();
            foreach (string s in rawSources)
                relevantSources.Add(Environment.ExpandEnvironmentVariables(s));

            source = Path.ChangeExtension(source, ".i");
            Preprocessor.PostTransform(source, new HashSet<string>(relevantSources));

            // run the parser on the preprocessed file to generate a model of the file in memory
            var grammarFile = Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), "header_grammar.cgt");
            var parser = new HeaderParser(grammarFile);
            var root = parser.Parse(source).ToXml();
            var json = ModelXml.Transform(root);

            // add a dependency to the base SlimDX.json file
            json.Add(new JProperty("dependencies", new JArray(new JValue("../SlimDX/SlimDX.json"))));

            return json;
        }

        static void RunGenerator(ApiModel api, Configuration configuration)
        {
            var templateDirectory = Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), "Templates");
            var templateEngine = new TemplateEngine(new[] { templateDirectory });

            templateEngine.RegisterCallback("ApiNamespace", (e, s) => api.Name);
            templateEngine.RegisterCallback("ApiName", (e, s) => TemplateCallbacks.GetApiClassName(api));
            templateEngine.RegisterCallback("ApiDll", (e, s) => TemplateCallbacks.GetApiDllName(api));
            templateEngine.RegisterCallbacks(typeof(TemplateCallbacks));

            var outputDirectory = configuration.GeneratorOutputPath;
            if (!Directory.Exists(outputDirectory))
                Directory.CreateDirectory(outputDirectory);

            ApplyTemplate(api, outputDirectory, templateEngine, "Api");
            ApplyTemplate(api.Enumerations, outputDirectory, templateEngine, "Enumeration");
            ApplyTemplate(api.Structures, outputDirectory, templateEngine, "Structure");
            ApplyTemplate(api.Interfaces, outputDirectory, templateEngine, "Interface");

            BuildTrampolineAssembly(api, outputDirectory, string.Format("{0}.Trampoline", api.Name));
        }

        static void BuildTrampolineAssembly(ApiModel api, string outputDirectory, string outputFile)
        {
            MarshallingService marshaller = new MarshallingService();
            TrampolineAssemblyBuilder trampolineBuilder = new TrampolineAssemblyBuilder();
            foreach (var interfaceModel in api.Interfaces)
            {
                foreach (var methodModel in interfaceModel.Methods)
                {
                    var methodType = marshaller.ResolveType(methodModel.Type);
                    if (methodType == null)
                        throw new InvalidOperationException(string.Format("Could not resolve return type for method '{0}.'", methodModel.Name));

                    var parameters = new List<TrampolineParameter>();
                    foreach (var parameterModel in methodModel.Parameters)
                    {
                        var parameterType = marshaller.ResolveType(parameterModel);
                        if (parameterType == null)
                            throw new InvalidOperationException(string.Format("Could not resolve type for parameter '{0}.'", parameterModel.Name));

                        TrampolineParameterFlags flags = TrampolineParameterFlags.Default;
                        if (parameterModel.Flags.HasFlag(ParameterModelFlags.IsOutput) && marshaller.ResolveBehavior(parameterModel) != MarshalBehavior.Structure && marshaller.ResolveBehavior(parameterModel) != MarshalBehavior.Enumeration && marshaller.ResolveBehavior(parameterModel) != MarshalBehavior.Array)
                            flags |= TrampolineParameterFlags.Reference;

                        parameters.Add(parameterModel.Type == ApiModel.VoidModel ? new TrampolineParameter(typeof(IntPtr), flags) : new TrampolineParameter(parameterType, flags));
                    }

                    trampolineBuilder.Add(new Trampoline(true, methodType, parameters.ToArray()));
                }
            }

            foreach (var functionModel in api.Functions)
            {
                var methodType = marshaller.ResolveType(functionModel.Type);
                if (methodType == null)
                    throw new InvalidOperationException(string.Format("Could not resolve return type for method '{0}.'", functionModel.Name));

                var parameters = new List<TrampolineParameter>();
                foreach (var parameterModel in functionModel.Parameters)
                {
                    var parameterType = marshaller.ResolveType(parameterModel);
                    if (parameterType == null)
                        throw new InvalidOperationException(string.Format("Could not resolve type for parameter '{0}.'", parameterModel.Name));

                    TrampolineParameterFlags flags = TrampolineParameterFlags.Default;
                    if (parameterModel.Flags.HasFlag(ParameterModelFlags.IsOutput))
                        flags |= TrampolineParameterFlags.Reference;

                    parameters.Add(parameterModel.Type == ApiModel.VoidModel ? new TrampolineParameter(typeof(IntPtr), flags) : new TrampolineParameter(parameterType, flags));
                }

                trampolineBuilder.Add(new Trampoline(false, methodType, parameters.ToArray()));
            }

            trampolineBuilder.CreateAssembly(outputDirectory, outputFile);
        }

        static void ApplyTemplate(ApiModel item, string outputDirectory, TemplateEngine templateEngine, string templateName)
        {
            var outputPath = Path.Combine(outputDirectory, TemplateCallbacks.GetApiClassName(item) + ".cs");
            if (File.Exists(outputPath))
                File.Delete(outputPath);
            File.WriteAllText(outputPath, templateEngine.ApplyByName(templateName, item));
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
