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
	class InterfaceElement : StructElement
	{
		public string Guid
		{
			get;
			private set;
		}

		public string BaseType
		{
			get;
			private set;
		}

		public IEnumerable<FunctionElement> Functions
		{
			get;
			private set;
		}

		public InterfaceElement(SourceModel model, string name, XElement structElement, XElement inheritance, XElement declspec)
			: base(model, name, structElement)
		{
			if (inheritance != null)
				BaseType = (string)inheritance.Attribute("Name");

			if (declspec != null)
				Guid = declspec.Descendants("Declspec").FirstOrDefault(d => (string)d.Element("Token") == "uuid").Attribute("Value").Value.Trim('"');

			Functions = structElement.Descendants("Function").Select(d => new FunctionElement(model, d)).ToList();
		}
	}
}
