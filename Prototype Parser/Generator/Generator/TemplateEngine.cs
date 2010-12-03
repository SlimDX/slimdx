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
using System.Text.RegularExpressions;
using System.Collections;

namespace Generator
{
	class TemplateEngine
	{
		Regex regex = new Regex(@"{(\\}|.)*?}");

		public string Directory
		{
			get;
			private set;
		}

		public TemplateEngine(string directory)
		{
			Directory = directory;
		}

		public string Apply(string template, object source)
		{
			template = Path.Combine(Directory, template);
			if (!File.Exists(template))
				throw new FileNotFoundException("Could not find template file.", template);

			template = File.ReadAllText(template);
			return regex.Replace(template.Replace("\\{", "`"), m => Evaluate(source, m)).Replace("`", "{").Replace("\\}", "}");
		}

		string Evaluate(object source, Match match)
		{
			var capture = match.Captures[0].Value.Trim('{', '}');
			string propertyName = capture;
			int index = capture.IndexOf(':');
			if (index >= 0)
				propertyName = capture.Substring(0, index);

			var value = source.GetType().GetProperty(propertyName).GetValue(source, null);
			if (index >= 0)
			{
				var template = capture.Substring(index + 1);
				var suffix = string.Empty;
				
				index = template.IndexOf(' ');
				if (index >= 0)
				{
					suffix = Escape(template.Substring(index + 1));
					template = template.Substring(0, index);
				}

				var enumerable = GetEnumerable(value);
				if (enumerable != null)
					return string.Join(suffix, enumerable.Cast<object>().Select(o => Apply(template, o)));

				return Apply(template, value);
			}
			else
				return Format(value);
		}

		static string Format(object source)
		{
			if (source == null)
				return null;

			var str = source as string;
			if (str != null)
				return str;

			var enumerable = GetEnumerable(source);
			if (enumerable != null)
				return string.Join(", ", enumerable.Cast<object>());

			return source.ToString();
		}

		static IEnumerable GetEnumerable(object source)
		{
			var enumerable = source as IEnumerable;
			if (enumerable == null)
			{
				var iter = source as IEnumerator;
				if (iter != null)
					enumerable = Iterate(iter);
			}

			return enumerable;
		}

		static IEnumerable Iterate(IEnumerator iterator)
		{
			while (iterator.MoveNext())
				yield return iterator.Current;
		}

		static string Escape(string input)
		{
			return input.Replace("\\t", "\t").Replace("\\n", "\n").Replace("\\s", " ");
		}
	}
}
