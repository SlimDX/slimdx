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
	/// Represents a type within a source code model.
	/// 
	/// Type elements encapsulate three different kinds of data about a type. The 
	/// 'native' data is that which came from the original header files, the 'managed' 
	/// data corresponds to the high-level C# view of the type, and the 'intermediate'
	/// data refers to how instances of the type are marshalled across the 
	/// native/managed barrier.
	/// 
	/// A given type element will always have native and intermediate data available,
	/// but not all elements will have complete managed data.
	/// </summary>
	class TypeElement : BaseElement
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="TypeElement"/> class.
		/// </summary>
		/// <param name="nativeName">The type's native name.</param>
		/// /// <param name="managedName">The type's managed name.</param>
		protected TypeElement(string nativeName, string managedName)
			: base(nativeName, managedName)
		{
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="TypeElement"/> class.
		/// </summary>
		/// <param name="nativeName">The type's native name.</param>
		/// <param name="managedType">The type's managed name.</param>
		public TypeElement(string nativeName, Type managedType)
			: base(nativeName, managedType.Name)
		{
			// When the managed type already exists, it can be directly used 
			// as the intermediate type.
			IntermediateType = managedType;
		}

		/// <summary>
		/// Gets the element's intermediate type.
		/// </summary>
		public Type IntermediateType
		{
			get;
			protected set;
		}
	}
}
