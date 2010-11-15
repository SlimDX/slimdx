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
using SlimDX2.Tools.XIDL;

namespace SlimDX2.Tools.XIDLToCSharp
{
    public class CSharpMapType : CSharpCppElement
    {
        public CSharpMapType(CppElement cppElement, CSharpType publicType,
                             CSharpType marshalType, string name)
        {
            ParentContainer = null;
            PublicType = publicType;
            MarshalType = marshalType ?? publicType;
            Name = name;
            CppElement = cppElement;
        }

        /// <summary>
        ///   Public type used for interface
        /// </summary>
        public CSharpType PublicType { get; set; }

        /// <summary>
        ///   Internal type used for marshalling. If null, then use instead public type.
        /// </summary>
        public CSharpType MarshalType { get; set; }

        public bool IsArray { get; set; }

        public int ArrayDimension { get; set; }

        public bool IsWideChar { get; set; }
    }
}