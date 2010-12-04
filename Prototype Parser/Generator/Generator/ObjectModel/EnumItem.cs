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

namespace Generator.ObjectModel
{
	class EnumItem : BaseElement
	{
		EnumElement parent;

		public string Value
		{
			get;
			private set;
		}

		public EnumItem(SourceModel model, EnumElement parent, string name, string value)
			: base(model, name)
		{
			this.parent = parent;
			Value = value;

			RebuildName();
		}

		public override string ToString()
		{
			if (string.IsNullOrEmpty(Value))
				return Name;

			return Name + " = " + Value;
		}

		protected override string BuildNiceName(string name)
		{
			if (parent == null)
				return "";

			return Model.NameRules.RemovePrefix(base.BuildNiceName(name), parent.NiceName);
		}
	}
}
