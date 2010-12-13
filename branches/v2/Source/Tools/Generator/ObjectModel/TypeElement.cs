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
using System.Xml.Linq;

namespace SlimDX.Generator.ObjectModel
{
	class TypeElement : BaseElement
	{
		public IEnumerable<string> Modifiers
		{
			get;
			private set;
		}

		public IEnumerable<int> Arrays
		{
			get;
			private set;
		}

		public string ArrayName
		{
			get { return NativeName + string.Concat(Arrays.Select(i => "[]")); }
		}

		public string ModifiedName
		{
			get;
			private set;
		}

		public TypeElement(SourceModel model, XElement element)
			: this(model, element, null)
		{
		}

		public TypeElement(SourceModel model, XElement element, IEnumerable<int> arrays)
			: base(model)
		{
			Arrays = arrays ?? Enumerable.Empty<int>();
			NativeName = (string)element.Attribute("Name");

			var scalar = element.Element("Scalar");
			if (scalar != null)
				NativeName = scalar.Element("Token").Value;

			var modifiers = new List<string>();
			var mod = element.Element("Mod");
			if (mod != null)
				modifiers.Add((string)mod.Element("Token"));

			modifiers.AddRange(element.Descendants("Pointers").Select(d => (string)d.Element("Token")));
			Modifiers = modifiers;

			RebuildName();
		}

		public TypeElement(SourceModel model, string name)
			: base(model, name)
		{
			Arrays = Enumerable.Empty<int>();
			Modifiers = Enumerable.Empty<string>();

			RebuildName();
		}

		protected override string BuildManagedName(string name)
		{
			if (string.IsNullOrEmpty(name) || Arrays == null)
				return "";

			Type type;
			if (!Model.TypeMap.TryGetValue(ArrayName, out type))
			{
				if (Model.TypeMap.TryGetValue(NativeName, out type))
					name += string.Concat(Arrays.Select(i => "[]"));
				else
					name = ArrayName;
			}
			else
			{
				name = type.Name;
			}

			ModifiedName = name;
			if (Modifiers != null && !Modifiers.Contains("const") && Modifiers.Contains("*"))
				ModifiedName = "out " + name;

			return name;
		}

		public override string ToString()
		{
			return ManagedName;
		}
	}
}
