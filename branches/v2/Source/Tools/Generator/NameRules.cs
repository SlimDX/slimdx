using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimDX.Generator
{
	/// <summary>
	/// Contains various helper methods to transform C++ names into proper .NET names.
	/// </summary>
	class NameRules
	{
		ConfigFile rules;

		public NameRules(string ruleFile)
		{
			rules = new ConfigFile(ruleFile);
		}

		public string PascalCaseFromUnderscores(string name)
		{
			if (string.IsNullOrEmpty(name))
				return name;

			return string.Concat(name.Split('_').Select(s => PascalCaseFromWord(s)));
		}

		public string PascalCaseFromWord(string word)
		{
			if (string.IsNullOrEmpty(word))
				return word;

			return char.ToUpper(word[0]) + word.Substring(1).ToLower();
		}

		public string RemovePrefixes(string name)
		{
			if (string.IsNullOrEmpty(name))
				return name;

			foreach (var prefix in rules.GetOptions("RemovePrefix"))
			{
				if (name.StartsWith(prefix))
					return name.Substring(prefix.Length);
			}

			return name;
		}

		public string RemovePrefix(string name, string prefix)
		{
			return name.StartsWith(prefix) ? name.Substring(prefix.Length) : name;
		}
	}
}
