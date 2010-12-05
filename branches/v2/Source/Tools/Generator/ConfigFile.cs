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

namespace SlimDX.Generator
{
	class ConfigFile
	{
		Dictionary<string, List<string>> options = new Dictionary<string, List<string>>();

		public ConfigFile(string fileName)
		{
			int lineNumber = 0;
			string section = null;

			foreach (var line in File.ReadLines(fileName))
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
						throw new InvalidDataException(string.Format("No section defined for option on line {0}.", lineNumber));
					options[section].Add(option);
				}
			}
		}

		public string GetOption(string section, string name)
		{
			List<string> optionGroup;
			if (!options.TryGetValue(section, out optionGroup) || optionGroup.Count == 0)
				throw new InvalidDataException("Could not find " + section + " section in config file.");

			foreach (var option in optionGroup)
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
	}
}
