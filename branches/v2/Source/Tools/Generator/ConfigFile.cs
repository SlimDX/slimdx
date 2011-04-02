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

using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;

namespace SlimDX.Generator
{
	class Configuration
	{
	}


	class ConfigFile
	{
		Dictionary<string, List<string>> options = new Dictionary<string, List<string>>();

		public string ConfigurationDirectory
		{
			get;
			private set;
		}

		public string GeneratorDirectory
		{
			get;
			private set;
		}

		public ConfigFile(string fileName)
		{
			ConfigurationDirectory = Path.GetDirectoryName(Path.GetFullPath(fileName));
			GeneratorDirectory = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + @"\";

			ProcessFile(fileName);
		}

		public string GetOption(string section, string name)
		{
			List<string> optionGroup;
			if (!options.TryGetValue(section, out optionGroup) || optionGroup.Count == 0)
				throw new InvalidDataException("Could not find " + section + " section in config file.");

			// reverse the order here to let derived config file options take precedence over included parent ones
			foreach (var option in optionGroup.Reverse<string>())
			{
				int index = option.IndexOf('=');
				if (index >= 0 && option.Substring(0, index).Trim() == name)
					return option.Substring(index + 1).Trim();
			}

			throw new InvalidDataException("Could not find " + name + " option in config file.");
		}

		public IEnumerable<string> GetOptions(string name)
		{
			List<string> optionGroup;
			if (!options.TryGetValue(name, out optionGroup) || optionGroup.Count == 0)
				return Enumerable.Empty<string>();

			return optionGroup;
		}

		void ProcessFile(string fileName)
		{
			int lineNumber = 0;
			string section = null;

			foreach (var line in File.ReadLines(fileName))
			{
				lineNumber++;

				var option = line.Trim();
				if (string.IsNullOrWhiteSpace(option) || option.StartsWith("#"))
					continue;

				// automatically expand environment variables on everything, just to simply the rest of the code
				// this includes the pseudo-environment variable for the running directory of the generator
				option = option.Replace("$(GenDir)", GeneratorDirectory);

				// options file is .ini-style with [Section] markers
				if (option.StartsWith("[") && option.EndsWith("]"))
				{
					section = option.Trim('[', ']');

					if (!options.ContainsKey(section))
						options.Add(section, new List<string>());
				}
				else
				{
					if (string.IsNullOrWhiteSpace(section))
					{
						// handle "includes" of parent config files
						if (option.StartsWith("$inherit"))
							ProcessFile(option.Substring(option.IndexOf(' ') + 1).RootPath(ConfigurationDirectory));
						else
							throw new InvalidDataException(string.Format("No section defined for option on line {0}.", lineNumber));
					}
					else
						options[section].Add(option);
				}
			}
		}
	}
}
