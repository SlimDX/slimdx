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
	/// Represents a variable within a source code model.
	/// 
	/// A variable is a named instance of a type. Thus, variable elements are
	/// used to represent function parameters as well.
	/// </summary>
	class VariableElement : BaseElement
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="VariableElement"/> class.
		/// </summary>
		/// <param name="nativeName">The variable's native name.</param>
		/// <param name="type">The variable's type.</param>
		/// <param name="indirectionLevel">The indirection level of the variable.</param>
		public VariableElement(string nativeName, TypeElement type, int indirectionLevel)
			: base(nativeName)
		{
			if (type == null)
				throw new ArgumentNullException("type");
			if (indirectionLevel < 0)
				throw new ArgumentOutOfRangeException("Value must be non-negative.", "indirectionLevel");
			Type = type;
			IndirectionLevel = indirectionLevel;
		}

		/// <summary>
		/// Gets the type of the variable.
		/// </summary>
		public TypeElement Type
		{
			get;
			private set;
		}

		/// <summary>
		/// Gets the indirection level of the variable.
		/// </summary>
		public int IndirectionLevel
		{
			get;
			private set;
		}
	}
}
