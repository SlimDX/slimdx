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
	/// Represents a function within a source code model.
	/// </summary>
	class FunctionElement : BaseElement
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="FunctionElement"/> class.
		/// </summary>
		/// <param name="nativeName">The function's native name.</param>
		/// <param name="index">The function's virtual dispatch table index.</param>
		/// <param name="returnType">The function's return type.</param>
		/// <param name="parameters">The function's parameters.</param>
		public FunctionElement(string nativeName, int index, TypeElement returnType, params VariableElement[] parameters)
			: base(nativeName)
		{
			if (returnType == null)
				throw new ArgumentNullException("returnType");

			Index = index;
			ReturnType = returnType;
			if (parameters != null)
				Parameters = new ReadOnlyCollection<VariableElement>(new List<VariableElement>(parameters));
			else
				Parameters = new ReadOnlyCollection<VariableElement>(new List<VariableElement>());
		}

		/// <summary>
		/// Gets the function's virtual dispatch table index.
		/// </summary>
		public int Index
		{
			get;
			private set;
		}

		/// <summary>
		/// Gets the return type of the function.
		/// </summary>
		public TypeElement ReturnType
		{
			get;
			private set;
		}

		/// <summary>
		/// Gets the parameters to the function.
		/// </summary>
		public ReadOnlyCollection<VariableElement> Parameters
		{
			get;
			private set;
		}
	}
}
