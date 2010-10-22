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
using System.Text;

namespace SlimDX2.Tools.XIDLToCSharp
{
    public class CSharpInteropCalliSignature
    {
        public CSharpInteropCalliSignature()
        {
            ParameterTypes = new List<Type>();
        }

        public int Index;
        public Type ReturnType;
        public List<Type> ParameterTypes;

        public string Name
        {
            get { return "Calli" + GetMethodName(ReturnType); }
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;
            CSharpInteropCalliSignature against = obj as CSharpInteropCalliSignature;
            if (against == null)
                return false;
            if (this.ReturnType != against.ReturnType)
                return false;
            if (this.ParameterTypes.Count != against.ParameterTypes.Count)
                return false;

            for (int i = 0; i < ParameterTypes.Count; i++)
            {
                if (ParameterTypes[i] != against.ParameterTypes[i])
                    return false;
            }
            return true;
        }

        private static string GetMethodName(Type type)
        {
            if (type == typeof (int))
                return "Int";
            if (type == typeof (void*))
                return "Ptr";
            if (type == typeof (void))
                return "Void";
            if (type == typeof (float))
                return "Float";
            if (type == typeof (long))
                return "Long";
            return type.Name;
        }


        public static string GetTypeName(Type type)
        {
            if (type == typeof (int))
                return "int";
            if (type == typeof (void*))
                return "void*";
            if (type == typeof (void))
                return "void";
            if (type == typeof (float))
                return "float";
            if (type == typeof (long))
                return "long";
            return type.Name;
        }

        public override string ToString()
        {
            StringBuilder builder = new StringBuilder();
            builder.Append(GetTypeName(ReturnType));
            builder.Append(" Calli" + GetMethodName(ReturnType) + "(");
            for (int i = 0; i < ParameterTypes.Count; i++)
            {
                builder.Append(GetTypeName(ParameterTypes[i]));
                if ((i + 1) < ParameterTypes.Count)
                    builder.Append(",");
            }
            builder.Append(")");
            return builder.ToString();
        }
    }
}