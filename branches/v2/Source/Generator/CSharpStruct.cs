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
using SlimDX.XIDL;

namespace SlimDX.Generator
{
    /// <summary>
    ///   A CSharpStruct that maps to a native struct
    /// </summary>
    public class CSharpStruct : CSharpType
    {
        public CSharpStruct() : this(null)
        {
        }

        public CSharpStruct(CppStruct cppStruct)
        {
            CppElement = cppStruct;
            IsIn = true;
            IsOut = false;
        }

        public IEnumerable<Field> Fields
        {
            get { return Items.OfType<Field>(); }
        }

        /// <summary>
        ///   True if this structure is using an explicit layout else it's a sequential structure
        /// </summary>
        public bool ExplicitLayout { get; set; }

        /// <summary>
        ///   True if this struct needs an internal marshal type
        /// </summary>
        public bool HasMarshalType { get; set; }

        public bool HasCustomMarshal { get; set; }

        public bool GenerateAsClass { get; set; }

        public bool HasCustomNew { get; set; }

        public string GetConstructor()
        {
            return string.Format(HasCustomNew ? "{0}.__NewNative()" : "new {0}.__Native()", FullName);
        }

        public string StructTypeName
        {
            get
            {
                return GenerateAsClass ? "class" : "struct";
            }
        }

        public bool IsIn { get; set; }

        public bool IsOut { get; set; }

        /// <summary>
        ///   List of declared inner structs
        /// </summary>
        public IEnumerable<CSharpStruct> InnerStructs
        {
            get { return Items.OfType<CSharpStruct>(); }
        }

        /// <summary>
        ///   Packing alignement for this structure (Default is 0 => Platform default)
        /// </summary>
        public int Pack { get; set; }

        /// <summary>
        ///   Struct field
        /// </summary>
        public class Field : CSharpField
        {
            public Field(CppField cppField, CSharpType publicType, CSharpType marshalType,
                         string name) : base(cppField, publicType, marshalType, name)
            {
            }

            public int Offset { get; set; }

            public bool IsBitField { get; set; }

            public int BitMask { get; set; }

            public int BitOffset { get; set; }
        }
    }
}