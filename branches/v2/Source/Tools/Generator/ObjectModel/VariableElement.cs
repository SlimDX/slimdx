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
	/// Specifies possible usages for an indirect parameter (pointer or reference).
	/// </summary>
	[Flags]
	enum UsageQualifiers
	{
		/// <summary>
		/// No particular usage specified. The system will try to guess the correct usage
		/// for parameters without an explicit usage.
		/// </summary>
		None = 0,

		/// <summary>
		/// The parameter is a reference to an input value.
		/// </summary>
		In = 0x1,

		/// <summary>
		/// The parameter acts as a return value for the function.
		/// </summary>
		Out = 0x2,

		/// <summary>
		/// The parameter can optionally be passed as a null pointer.
		/// </summary>
		IsOptional = 0x4,

		/// <summary>
		/// An array parameter has its element count specified by a linked parameter.
		/// </summary>
		HasElementCountRelation = 0x10,

		/// <summary>
		/// A pointer to a block of memory has its binary size specified by a linked parameter.
		/// </summary>
		HasBinarySizeRelation = 0x20,

		/// <summary>
		/// The method containing the parameter can be called twice, first passing a null pointer, in order to
		/// get the size of the resulting array, which will be returned via the linked parameter.
		/// </summary>
		IsPartial = 0x40
	}

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
			: this(nativeName, type, indirectionLevel, UsageQualifiers.None)
		{
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="VariableElement"/> class.
		/// </summary>
		/// <param name="nativeName">The variable's native name.</param>
		/// <param name="type">The variable's type.</param>
		/// <param name="indirectionLevel">The indirection level of the variable.</param>
		/// <param name="usage">The usage qualifiers for an indirect parameter variable.</param>
		public VariableElement(string nativeName, TypeElement type, int indirectionLevel, UsageQualifiers usage)
			: this(nativeName, nativeName, type, indirectionLevel, usage)
		{
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="VariableElement"/> class.
		/// </summary>
		/// <param name="nativeName">The variable's native name.</param>
		/// <param name="managedName">The variable's managed name.</param>
		/// <param name="type">The variable's type.</param>
		/// <param name="indirectionLevel">The indirection level of the variable.</param>
		/// <param name="usage">The usage qualifiers for an indirect parameter variable.</param>
		public VariableElement(string nativeName, string managedName, TypeElement type, int indirectionLevel, UsageQualifiers usage)
			: base(nativeName, managedName)
		{
			if (type == null)
				throw new ArgumentNullException("type");
			if (indirectionLevel < 0)
				throw new ArgumentOutOfRangeException("Value must be non-negative.", "indirectionLevel");
			Type = type;
			IndirectionLevel = indirectionLevel;
			Usage = usage;
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

		/// <summary>
		/// Gets the usage qualifiers for an indirect parameter variable. If the variable is not a parameter or
		/// is not an indirect parameter (ie. a pointer or a reference), this member should be ignored.
		/// </summary>
		public UsageQualifiers Usage
		{
			get;
			private set;
		}
	}
}
