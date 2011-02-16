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
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Collections.Generic;

namespace SlimDX.Generator
{
	/// <summary>
	/// Provides access to the boost::wave C++ preprocessor tool.
	/// </summary>
	class Preprocessor
	{
		string primarySource;
		string wavePath;
		string arguments;

		public string Source
		{
			get;
			private set;
		}

		public Preprocessor(ConfigFile options)
		{
			// primary source file is the one that wave is run against 
			// to produce a single preprocessed monolithic header
			primarySource = Environment.ExpandEnvironmentVariables(options.GetOption("Options", "PrimarySource"));
			wavePath = options.GetOption("Options", "Wave").RootPath(options.ConfigurationDirectory);

			// -E indicates default naming scheme for output file (e.g. input.i)
			// -m macros.txt creates a separate file containing a list of all found macros
			// --variadics enables macros with empty argument lists (necessary for some win32 header)
			// -S adds an include path (specified in our config file)
			// -D adds a predefined macro (several are necessary to compile the win32 headers)
			// -r forcibly ignores a given definition
			// final argument is the primary header file to run against
			var builder = new StringBuilder("-E -m macros.txt --variadics ");

			foreach (var path in options.GetOptions("IncludePaths"))
				builder.Append("-S \"").Append(Environment.ExpandEnvironmentVariables(path)).Append("\" ");

			foreach (var symbol in options.GetOptions("Symbols"))
				builder.Append("-D ").Append(symbol).Append(" ");

			foreach (var symbol in options.GetOptions("IgnoreSymbols"))
				builder.Append("-r ").Append(symbol).Append(" ");

			Source = Path.GetFileName(primarySource);
			builder.AppendFormat("\"{0}\"", Source);
			arguments = builder.ToString();
		}

		/// <summary>
		/// Run boost::wave on the source headers to produce a single preprocessed output file.
		/// </summary>
		/// <returns>The output from boost::wave.</returns>
		public string Run()
		{
			// copy the primary source file to local so that wave doesn't try to create the output file
			// in the source directory, which potentially has restricted access
			File.Copy(primarySource, Source, true);

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

				File.Delete(Source);
				return info;
			}
		}

		/// <summary>
		/// Performs transformations on a preprocessed file to prepare it for parsing.
		/// </summary>
		/// <param name="preprocessedFile">The preprocessed file.</param>
		/// <param name="relevantSources">The relevant sources. 
		/// Any code that did not originate in one of these sources is removed before parsing.</param>
		public static void PostTransform(string preprocessedFile, ISet<string> relevantSources)
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
