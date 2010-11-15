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
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;

namespace SlimDX.XIDL
{
    [DataContract]
    public class CppMethod : CppElement
    {
        public CppMethod()
        {
            ReturnType = new CppType();
        }

        [DataMember(Order = 0)]
        public CppType ReturnType { get; set; }

        [DataMember(Order = 1)]
        public CppCallingConvention CallingConvention { get; set; }

        [DataMember(Order = 2)]
        public int Offset { get; set; }

        [DataMember(Order = 3, Name = "Parameters")]
        private List<CppParameter> _Parameters
        {
            get { return Parameters.ToList(); }
            set { Add(value); }
        }

        public IEnumerable<CppParameter> Parameters
        {
            get { return InnerElements.OfType<CppParameter>(); }
        }

        protected override IEnumerable<CppElement> AllInnerElements
        {
            get
            {
                List<CppElement> allElements = new List<CppElement>(InnerElements);
                allElements.Add(ReturnType);
                return allElements;
            }            
        }


        public override string ToString()
        {
            StringBuilder builder = new StringBuilder();
            builder.Append(ReturnType);
            builder.Append(" ");
            if (Parent is CppInterface)
            {
                builder.Append(Parent.Name);
                builder.Append("::");
            }
            builder.Append(Name);
            builder.Append("(");
            int i = 0, count = Parameters.Count();
            foreach (var cppParameter in Parameters)
            {
                builder.Append(cppParameter);
                if ((i + 1) < count)
                {
                    builder.Append(",");
                }
                i++;
            }
            builder.Append(")");
            return builder.ToString();
        }
    }
}