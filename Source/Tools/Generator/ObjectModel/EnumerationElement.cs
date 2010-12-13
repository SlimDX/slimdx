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
using System.Collections.ObjectModel;

namespace SlimDX.Generator.ObjectModel
{
	/// <summary>
	/// Represents an enumeration within a source code model.
	/// </summary>
	class EnumerationElement : TypeElement
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="EnumerationElement"/> class.
		/// </summary>
		/// <param name="nativeName">The enumeration's native name.</param>
		public EnumerationElement(string nativeName)
			: base(nativeName, nativeName)
		{
		}

		/// <summary>
		/// Gets the enumeration's items.
		/// </summary>
		public ReadOnlyCollection<EnumerationItemElement> Items
		{
			get
			{
				return new ReadOnlyCollection<EnumerationItemElement>(itemElements);
			}
		}

		/// <summary>
		/// Adds an item to the enumeration.
		/// </summary>
		/// <param name="itemElement">The item.</param>
		public void AddItem(EnumerationItemElement itemElement)
		{
			if (itemElement == null)
				throw new ArgumentNullException("itemElement");
			itemElements.Add(itemElement);
		}

		List<EnumerationItemElement> itemElements = new List<EnumerationItemElement>();
	}
}
