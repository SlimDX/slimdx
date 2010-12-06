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

		public string Apply(string name)
		{
			if (string.IsNullOrEmpty(name))
				return name;

			return ExpandAbbreviations(RemovePrefixes(name));
		}

		public string RemovePrefixes(string name)
		{
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

		public string ExpandAbbreviations(string name)
		{
			foreach (var entry in rules.GetOptions("Abbreviations").Select(e => e.Split(' ')))
			{
				int index = name.IndexOf(entry[0]);
				if (index >= 0)
				{
					if (!name.Substring(index).StartsWith(entry[1]))
						return name.Replace(entry[0], entry[1]);
				}
			}

			return name;
		}
	}

	static class NameExtensions
	{
		public static string PascalCaseFromUnderscores(this string name)
		{
			if (string.IsNullOrEmpty(name))
				return name;

			return string.Concat(name.Split('_').Select(s => PascalCaseFromWord(s)));
		}

		public static string PascalCaseFromWord(this string word)
		{
			if (string.IsNullOrEmpty(word))
				return word;

			return char.ToUpper(word[0]) + word.Substring(1).ToLower();
		}

		public static string CamelCase(this string name)
		{
			if (string.IsNullOrEmpty(name))
				return name;

			return char.ToLower(name[0]) + name.Substring(1);
		}
	}
}
