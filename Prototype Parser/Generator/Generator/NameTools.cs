using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Generator
{
	/// <summary>
	/// Contains various helper methods to transform C++ names
	/// into proper .NET names.
	/// </summary>
	static class NameTools
	{
		public static ConfigFile Rules;

		public static string PascalCaseFromUnderscores(string name)
		{
			if (string.IsNullOrEmpty(name))
				return name;

			return string.Concat(name.Split('_').Select(s => PascalCaseFromWord(s)));
		}

		public static string PascalCaseFromWord(string word)
		{
			if (string.IsNullOrEmpty(word))
				return word;

			return char.ToUpper(word[0]) + word.Substring(1).ToLower();
		}

		public static string RemovePrefixes(string name)
		{
			if (string.IsNullOrEmpty(name))
				return name;

			foreach (var prefix in Rules.GetOptions("RemovePrefix"))
			{
				if (name.StartsWith(prefix))
					return name.Substring(prefix.Length);
			}

			return name;
		}

		public static string RemovePrefix(string name, string prefix)
		{
			return name.StartsWith(prefix) ? name.Substring(prefix.Length) : name;
		}
	}
}
