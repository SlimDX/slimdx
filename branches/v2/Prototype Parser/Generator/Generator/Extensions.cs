using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Generator
{
	static class Extensions
	{
		public static string GetOption(this Dictionary<string, List<string>> options, string name)
		{
			List<string> optionGroup;
			if (!options.TryGetValue(name, out optionGroup) || optionGroup.Count == 0)
				return null;

			return optionGroup[0];
		}

		public static IEnumerable<string> GetOptions(this Dictionary<string, List<string>> options, string name)
		{
			List<string> optionGroup;
			if (!options.TryGetValue(name, out optionGroup) || optionGroup.Count == 0)
				return Enumerable.Empty<string>();

			return optionGroup;
		}
	}
}
