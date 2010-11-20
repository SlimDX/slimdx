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
using GoldParser;
using System.Xml.Linq;

namespace Generator
{
	/// <summary>
	/// Represents a non-terminal parse node.
	/// </summary>
	class NonTerminal : IParseNode
	{
		List<IParseNode> children = new List<IParseNode>();

		public Rule Rule
		{
			get;
			private set;
		}

		public IEnumerable<IParseNode> Children
		{
			get { return children; }
		}

		public NonTerminal(Rule rule)
		{
			Rule = rule;
		}

		public void Add(object node)
		{
			if (node != null)
				children.Add(node as IParseNode);
		}

		public XElement ToXml()
		{
			return (XElement)((IParseNode)this).ToXml();
		}

		object IParseNode.ToXml()
		{
			var childXml = children.Select(c => c.ToXml()).Where(c => c != null).ToArray();
			if (childXml.Length == 0)
				return null;

			var name = Rule.Name.Trim('<', '>').Replace(' ', '_');
			if(name == "ID" || name == "Value")
				return childXml[0];

			return new XElement(name, childXml);
		}
	}
}
