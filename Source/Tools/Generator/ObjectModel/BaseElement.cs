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

namespace SlimDX.Generator.ObjectModel
{
	/// <summary>
	/// Represents an element within a source code model.
	/// </summary>
	abstract class BaseElement
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="BaseElement"/> class.
		/// </summary>
		/// <param name="nativeName">The element's native name.</param>
		/// <param name="metadata">The element's metadata.</param>
		protected BaseElement(string nativeName, Metadata metadata)
			: this(nativeName, nativeName, metadata)
		{
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="BaseElement"/> class.
		/// </summary>
		/// <param name="nativeName">The element's native name.</param>
		/// <param name="managedName">The element's managed name.</param>
		/// <param name="metadata">The element's metadata.</param>
		protected BaseElement(string nativeName, string managedName, Metadata metadata)
		{
			if (string.IsNullOrEmpty(nativeName))
				throw new ArgumentException("Value may not be null or empty.", "nativeName");
			if (string.IsNullOrEmpty(managedName))
				throw new ArgumentException("Value may not be null or empty.", "managedName");
			if (metadata == null)
				throw new ArgumentNullException("metadata");

			Metadata = metadata;
			NativeName = nativeName;
			ManagedName = Metadata["OverrideName"] ?? managedName;
		}

		/// <summary>
		/// Gets the element's native name.
		/// </summary>
		public string NativeName
		{
			get;
			protected set;
		}

		/// <summary>
		/// Gets the element's managed name.
		/// </summary>
		public string ManagedName
		{
			get;
			protected set;
		}

		/// <summary>
		/// Gets the element's metadata.
		/// </summary>
		public Metadata Metadata
		{
			get;
			private set;
		}

		/// <summary>
		/// Returns a <see cref="System.String"/> that represents this instance.
		/// </summary>
		/// <returns>
		/// A <see cref="System.String"/> that represents this instance.
		/// </returns>
		public override string ToString()
		{
			return NativeName;
		}
	}
}
