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
using System.Runtime.Serialization;
using System.Text;

namespace SlimDX.XIDL
{
    [DataContract]
    public class CppType : CppElement
    {
        [DataMember(Order = 0)]
        public string Type { get; set; }

        [DataMember(Order = 1)]
        public string Specifier { get; set; }

        [DataMember(Order = 2)]
        public bool Const { get; set; }

        [DataMember(Order = 3)]
        public bool IsArray { get; set; }

        [DataMember(Order = 4)]
        public string ArrayDimension { get; set; }

        public override string ToString()
        {
            StringBuilder builder = new StringBuilder();
            if (Const)
                builder.Append("const ");
            builder.Append(Type);
            builder.Append(Specifier);

            if (!string.IsNullOrEmpty(Name))
            {
                builder.Append(" ");
                builder.Append(Name);
            }

            if (IsArray)
            {
                builder.Append("[");
                builder.Append(ArrayDimension);
                builder.Append("]");
            }
            return builder.ToString();
        }

        public override int GetHashCode()
        {
            return Type.GetHashCode() + Specifier.GetHashCode();
        }

        public override bool Equals(object obj)
        {
            if (!(obj is CppType))
                return false;

            var against = obj as CppType;
            return (Type == against.Type && Specifier == against.Specifier && Const == against.Const &&
                    IsArray == against.IsArray && ArrayDimension == against.ArrayDimension);
        }
    }
}