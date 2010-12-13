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
			var nameService = new NameRules(options.GetOption("Options", "NamingRules"));
			var model = new SourceModel(root, nameService, options.GetOptions("TypeMap"));
			var templateEngine = new TemplateEngine(options.GetOption("Options", "Templates"), options.GetOption("Options", "Namespace"));
			var outputPath = options.GetOption("Options", "OutputPath");

			templateEngine.RegisterCallback("GenerateManagedParameterType", GenerateManagedParameterType);
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
					var parameterTypes = new List<TrampolineParameter>();
					foreach (var parameter in function.Parameters)
					{
						var effectiveIndirectionLevel = GetEffectiveIndirectionLevel(parameter);
						var parameterFlags = effectiveIndirectionLevel > 0 ? TrampolineParameterFlags.Reference : TrampolineParameterFlags.Default;
						parameterTypes.Add(new TrampolineParameter(parameter.Type.IntermediateType, parameterFlags));
					}
					trampolineBuilder.Add(new Trampoline(function.ReturnType.IntermediateType, parameterTypes.ToArray()));
				}
			}

			trampolineBuilder.CreateAssembly("SlimDX.Trampoline");

			// write output files
			File.WriteAllText(Path.Combine(outputPath, "Enums.cs"), templateEngine.Apply("EnumFile.txt", model));
			foreach (var item in model.Structures)
				File.WriteAllText(Path.Combine(outputPath, item.ManagedName + ".cs"), templateEngine.Apply("Struct.txt", item));

			foreach (var item in model.Interfaces)
				File.WriteAllText(Path.Combine(outputPath, item.ManagedName + ".cs"), templateEngine.Apply("Interface.txt", item));
		}

		static string GenerateManagedParameterType(object source)
		{
			var parameter = (VariableElement)source;
			var effectiveIndirectionLevel = GetEffectiveIndirectionLevel(parameter);
			if (effectiveIndirectionLevel > 0)
				return string.Format("out {0}", parameter.Type.ManagedName);
			return parameter.Type.ManagedName;
		}

		static string GenerateFunctionBody(object source)
		{
			var function = (FunctionElement)source;
			var builder = new StringBuilder();
			var ordinal = 0;

			builder.AppendLine();

			// The intermidate objects for output parameters must be declared first.
			foreach (var parameter in function.Parameters)
			{
				var effectiveIndirectionLevel = GetEffectiveIndirectionLevel(parameter);
				if (effectiveIndirectionLevel > 0)
				{
					builder.AppendFormat("{0} _{1} = default({0});", parameter.Type.IntermediateType.FullName, parameter.ManagedName);
					builder.AppendLine();
				}
			}

			builder.AppendFormat("{0} _result = SlimDX.Trampoline.Call.{0}({1} * System.IntPtr.Size, nativePointer, ", function.ReturnType.ManagedName, ordinal);
			for (int index = 0; index < function.Parameters.Count; ++index)
			{
				var parameter = function.Parameters[index];
				var effectiveIndirectionLevel = GetEffectiveIndirectionLevel(parameter);
				if (effectiveIndirectionLevel > 0)
					builder.AppendFormat("ref _{0}", parameter.ManagedName);
				else
					builder.Append(parameter.ManagedName);

				if (index < function.Parameters.Count - 1)
					builder.Append(", ");
			}

			builder.AppendLine(");");

			// Once the call has been made, intermediate objects must be transformed to the proper managed types.
			foreach (var parameter in function.Parameters)
			{
				var effectiveIndirectionLevel = GetEffectiveIndirectionLevel(parameter);
				if (effectiveIndirectionLevel > 0)
				{
					builder.AppendFormat("{0} = new {1}(_{0});", parameter.ManagedName, parameter.Type.ManagedName);
					builder.AppendLine();
				}
			}

			builder.AppendLine("return _result;");
			return builder.ToString();
		}

		//TODO: Maybe IndirectionLevel itself should just do this...?
		static int GetEffectiveIndirectionLevel(VariableElement parameter)
		{
			var effectiveIndirectionLevel = parameter.IndirectionLevel;

			// The IntPtr type has a level of indirection built in.
			if (parameter.Type.IntermediateType == typeof(IntPtr))
				--effectiveIndirectionLevel;

			return effectiveIndirectionLevel;
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
