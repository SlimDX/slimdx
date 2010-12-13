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

namespace SlimDX.Generator.ObjectModel
{
	abstract class BaseElement
	{
		string name;

		public SourceModel Model
		{
			get;
			private set;
		}

		/// <summary>
		/// Gets the element's native name.
		/// </summary>
		public string NativeName
		{
			get
			{
				return name;
			}
			protected set
			{
				if (name != value)
				{
					name = value;
					RebuildName();
				}
			}
		}

		/// <summary>
		/// Gets the element's managed name.
		/// </summary>
		public string ManagedName
		{
			get;
			private set;
		}

		protected BaseElement(SourceModel model)
		{
			Model = model;
		}

		protected BaseElement(SourceModel model, string name)
			: this(model)
		{
			NativeName = name;
		}

		public override string ToString()
		{
			return NativeName;
		}

		protected virtual string BuildManagedName(string name)
		{
			if (string.IsNullOrEmpty(name))
				return "";

			if (name.Contains("_"))
				name = name.PascalCaseFromUnderscores();

			return Model.NameRules.Apply(name);
		}

		protected void RebuildName()
		{
			ManagedName = BuildManagedName(NativeName);
		}

		protected void RegisterType()
		{
			//TODO: Not sure what to do here in light of TypeMap now being <string,Type>. Commenting
			//      this out for now doesn't seem to have any adverse impact.
			//if (!Model.TypeMap.ContainsKey(Name))
			//	Model.TypeMap.Add(Name, NiceName);
		}
	}
}
