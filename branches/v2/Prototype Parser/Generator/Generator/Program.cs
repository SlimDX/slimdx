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
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;
using GoldParser;

namespace Generator
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
			int lineNumber = 0;
			string section = null;
			var options = new Dictionary<string, List<string>>();

			foreach (var line in File.ReadLines(configFile))
			{
				lineNumber++;

				var option = line.Trim();
				if (string.IsNullOrWhiteSpace(option) || option.StartsWith("#"))
					continue;

				// options file is .ini-style with [Section] markers
				if (option.StartsWith("[") && option.EndsWith("]"))
				{
					section = option.Trim('[', ']');
					options.Add(section, new List<string>());
				}
				else
				{
					if (string.IsNullOrWhiteSpace(section))
						throw new InvalidOperationException(string.Format("No section defined for option on line {0}.", lineNumber));
					options[section].Add(option);
				}
			}

			// primary source file is the one that wave is run against to produce
			// a single preprocessed monolithic header
			var primarySource = options.GetOption("PrimarySource");
			var grammarPath = options.GetOption("Grammar");
			var wavePath = options.GetOption("Wave");

			// run boost::wave on the primary source file to get a preprocessed file and a list of macros
			// -E indicates default naming scheme for output file (ie. input.i)
			// -m macros.txt creates a separate file containing a list of all found macros
			// --variadics enables macros with empty argument lists (necessary for some win32 header)
			// -S adds an include path (specified in our config file)
			// -D adds a predefined macro (several are necessary to compile the win32 headers)
			// final argument is the primary header file to run against
			var arguments = new StringBuilder("-E -m macros.txt --variadics ");

			foreach (var path in options.GetOptions("IncludePaths"))
				arguments.Append("-S \"").Append(path).Append("\" ");

			foreach (var symbol in options.GetOptions("Symbols"))
				arguments.Append("-D ").Append(symbol).Append(" ");

			// copy the primary source file to local so that wave doesn't try to create the output file
			// in the source directory, which potentially has restricted access
			var source = Path.GetFileName(primarySource);
			File.Copy(primarySource, source, true);

			arguments.AppendFormat("\"{0}\"", source);
			Preprocess(wavePath, arguments.ToString());
			File.Delete(source);

			// before parsing, run some transformations on the preprocessed file to
			// get rid of garbage to cut down on the size needed to be examined
			// as well as to get rid of junk I was too lazy to add to the parser grammar.
			// this includes dropping any source that is not from the given primary or ancillary
			// sources, which is indicated in the preprocessed file by #line directives
			List<string> relevantSources;
			if (!options.TryGetValue("AncillarySources", out relevantSources))
				relevantSources = new List<string>();

			relevantSources.Add(Path.Combine(Directory.GetCurrentDirectory(), source));
			source = Path.ChangeExtension(source, ".i");
			Transform(source, new HashSet<string>(relevantSources));

			// run the parse on the preprocessed file to generate a model of the file in memory
			var parser = new HeaderParser(grammarPath);
			var root = parser.Parse(source);

			// for testing purposes, output XML of the parse tree
			root.ToXml().Save("test.xml");
		}

		/// <summary>
		/// Run boost::wave on the source headers to produce a single preprocessed output file.
		/// </summary>
		/// <param name="wavePath">The path to the wave executable.</param>
		/// <param name="arguments">The arguments passed to boost::wave.</param>
		static void Preprocess(string wavePath, string arguments)
		{
			var startInfo = new ProcessStartInfo(wavePath, arguments)
			{
				CreateNoWindow = true,
				RedirectStandardOutput = true,
				UseShellExecute = false
			};

			using (var process = Process.Start(startInfo))
			{
				string info = process.StandardOutput.ReadToEnd();
				process.WaitForExit();

				Console.WriteLine(info);
			}
		}

		/// <summary>
		/// Performs transformations on a preprocessed file to prepare it for parsing.
		/// </summary>
		/// <param name="preprocessedFile">The preprocessed file.</param>
		/// <param name="relevantSources">The relevant sources. 
		/// Any code that did not originate in one of these sources is removed before parsing.</param>
		static void Transform(string preprocessedFile, HashSet<string> relevantSources)
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
