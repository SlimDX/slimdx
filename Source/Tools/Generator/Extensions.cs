using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimDX.Generator
{
	static class Extensions
	{
		public static StringBuilder Indent(this StringBuilder builder, int level)
		{
			return builder.Append('\t', level);
		}
	}
}
