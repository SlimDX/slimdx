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
using System.Text;
using SlimDX2.Tools.XIDL;

namespace SlimDX2.Tools.XIDLToCSharp
{
    public class CSharpMethod : CSharpType, ICloneable
    {
        public CSharpMethod(CppMethod cppMethod)
        {
            CppElement = cppMethod;
        }

        public IEnumerable<Parameter> Parameters
        {
            get { return Items.OfType<Parameter>(); }
        }

        public int ParameterCount
        {
            get { return Items.OfType<Parameter>().Count(); }
        }

        public bool IsHResult
        {
            get { return HasReturnType && ReturnType.PublicType.Name == Global.Name + ".Result"; }
        }

        public bool IsReturnStruct
        {
            get
            {
                return HasReturnType && ReturnType.PublicType is CSharpStruct;
            }
        }

        protected override void UpdateFromTag(CSharpTag tag)
        {
            base.UpdateFromTag(tag);

            if (tag.NoProperty.HasValue)
                NoProperty = tag.NoProperty.Value;
        }

        public bool NoProperty { get; set; }

        public int Offset { get; set; }

        public CSharpInteropCalliSignature Interop { get; set; }

        public string CppSignature
        {
            get
            {
                if (CppElement != null)
                {
                    return CppElement.ToString();
                }
                return "Unknown";
            }
        }

        public bool HasReturnType
        {
            get { return !(ReturnType.PublicType.Type != null && ReturnType.PublicType.Type == typeof (void)); }
        }

        public string CastStart
        {
            get
            {
                if (ReturnType.PublicType.Type != null && ReturnType.PublicType.Type == typeof (bool))
                    return "(0!=";
                if (ReturnType.PublicType is CSharpInterface)
                    return "new " + ReturnType.PublicType.FullName + "((IntPtr)";
                return "";
            }
        }

        public string CastEnd
        {
            get
            {
                if (ReturnType.PublicType.Type != null && ReturnType.PublicType.Type == typeof (bool))
                    return ")";
                if (ReturnType.PublicType is CSharpInterface)
                    return ")";
                return "";
            }
        }

        public CSharpMapType ReturnType { get; set; }

        public enum ParameterAttribute
        {
            In,
            Out,
            Ref,
            RefIn
        }

        public class Parameter : CSharpMapType, ICloneable
        {
            public Parameter(CSharpMethod method, CppParameter cppParameter, CSharpType publicType,
                             CSharpType marshalType, string name)
                : base(method, cppParameter, publicType, marshalType, name)
            {
                // Default is In
                Attribute = ParameterAttribute.In;
            }

            public ParameterAttribute Attribute { get; set; }

            public bool HasPointer { get; set; }

            public bool IsOptionnal { get; set; }

            private const int SizeOfLimit = 16;

            public bool IsFixed
            {
                get
                {
                    if (Attribute == ParameterAttribute.Ref || Attribute == ParameterAttribute.RefIn)
                    {
                        if (IsRefInValueTypeOptional || IsRefInValueTypeByValue)
                            return false;
                        return true;
                    }
                    if (Attribute == ParameterAttribute.Out)
                        return true;
                    if (IsArray)
                        return true;
                    return false;
                }
            }

            public string TempName
            {
                get { return Name + "_"; }
            }

            public bool IsRefIn
            {
                get { return Attribute == ParameterAttribute.RefIn; }
            }

            public bool IsIn
            {
                get { return Attribute == ParameterAttribute.In; }
            }

            public bool IsOut
            {
                get { return Attribute == ParameterAttribute.Out; }
            }

            public bool IsPrimitive
            {
                get { return PublicType.Type != null && PublicType.Type.IsPrimitive; }
            }

            public bool IsString
            {
                get { return PublicType.Type == typeof (string); }
            }

            public bool IsValueType
            {
                get { return PublicType is CSharpStruct || (PublicType.Type != null && (PublicType.Type.IsValueType || PublicType.Type.IsPrimitive)); }
            }

            public bool HasNativeValueType
            {
                get { return PublicType is CSharpStruct && (PublicType as CSharpStruct).HasMarshalType; }
            }

            public bool IsRefInValueTypeOptional
            {
                get { return IsRefIn && IsValueType && !IsArray && IsOptionnal; }
            }

            public bool IsRefInValueTypeByValue
            {
                get { return IsRefIn && IsValueType && !IsArray && PublicType.SizeOf <= SizeOfLimit && !HasNativeValueType; }
            }

            public string ParamName
            {
                get
                {
                    StringBuilder builder = new StringBuilder();
                    if (Attribute == ParameterAttribute.Out && (!IsArray || PublicType.Name == "string"))
                        builder.Append("out ");
                    else if ((Attribute == ParameterAttribute.Ref || Attribute == ParameterAttribute.RefIn) && !IsArray)
                    {
                        if (!(IsRefInValueTypeOptional || IsRefInValueTypeByValue))
                            builder.Append("ref ");
                    }

                    if (IsRefIn && IsValueType && !IsArray && IsOptionnal)
                        builder.Append(PublicType.FullName + "?");
                    else
                        builder.Append(PublicType.FullName);

                    if (IsArray && PublicType.Name != "string")
                        builder.Append("[]");
                    builder.Append(" ");
                    builder.Append(Name);
                    return builder.ToString();
                }
            }

            public string ParamNameForNativeFunction
            {
                get
                {
                    StringBuilder builder = new StringBuilder();

                    string typeName = PublicType.FullName;
                    if ((IsIn || IsRefIn) && PublicType.Type == typeof (string))
                    {
                        if (IsWideChar)
                            builder.Append("[MarshalAs(UnmanagedType.LPWStr),In] ");
                        else
                            builder.Append("[MarshalAs(UnmanagedType.LPStr),In] ");
                    }

                    if (Attribute == ParameterAttribute.Out && (!IsArray || PublicType.Name == "string"))
                    {
                        builder.Append("out ");
                    }
                    else if ((Attribute == ParameterAttribute.Ref || Attribute == ParameterAttribute.RefIn) && !IsArray)
                    {
                        if (!(IsOptionnal && IsValueType))
                            builder.Append("ref ");
                    }
                    //else if (IsArray)
                    //    builder.Append("ref ");

                    if (PublicType is CSharpInterface)
                        typeName = "IntPtr";

                    if (HasNativeValueType)
                        typeName += ".__Native";

                    if (IsRefIn && IsOptionnal && IsValueType && !IsArray)
                        typeName = "IntPtr";

                    builder.Append(typeName);
                    if (IsArray && PublicType.Name != "string")
                        builder.Append("[]");
                    builder.Append(" ");
                    builder.Append(Name);
                    return builder.ToString();
                }
            }

            public string CallNameForFunction
            {
                get
                {
                    string typeName = Name; 
                    
                    if (IsOut)
                    {
                        if (PublicType is CSharpInterface)
                        {
                            if (IsArray)
                                return TempName;
                            else
                                return "out " + TempName;
                        }
                        if (IsArray)
                        {
                            return Name;
                        }
                        return "out " + Name;
                    }

                    //if (PublicType.Type == typeof(string))
                    //    return "(void*)" + TempName;
                    //if (PublicType.Type == typeof(bool))
                    //    return "(" + Name + "?1:0)";
                    //if (PublicType.Type == typeof(byte))
                    //    return "(int)" + Name;
                    if (PublicType is CSharpInterface && Attribute == ParameterAttribute.In && !IsArray)
                    {
                        return "(" + Name + " == null)?IntPtr.Zero:" + Name + ".NativePointer";
                    }

                    if (IsRefIn && IsOptionnal && IsValueType && !IsArray)
                        return "(" + Name + ".HasValue)?new IntPtr(&" + TempName + "):IntPtr.Zero";

                    if (HasNativeValueType)
                        typeName = TempName;
                    else if (IsArray && (IsIn || IsRefIn) && HasNativeValueType)
                        return TempName;

                    StringBuilder builder = new StringBuilder();
                    if (Attribute == ParameterAttribute.Out)
                        builder.Append("out ");
                    else if ((Attribute == ParameterAttribute.Ref || Attribute == ParameterAttribute.RefIn) && !IsArray)
                        builder.Append("ref ");
                    //else if (IsArray)
                    //    builder.Append("ref ");

                    builder.Append(" ");
                    builder.Append(typeName);
                    return builder.ToString();
                }
            }

            //IntPtr pDevice_;
            //SlimDX2.Interop.CalliVoid(_nativePointer, 3 * 4, &pDevice_);
            //pDevice = new SlimDX2.Direct3D11.Device(pDevice_);

            //for (int i = 0; i < pSamplers.Length; i++)
            //    pSamplers[i] = new SamplerState(pSamplers_[i]);

            public string CallName
            {
                get
                {
                    if (IsOut)
                    {
                        if (PublicType is CSharpInterface)
                        {
                            return "&" + TempName;
                        }
                        if (IsArray)
                        {
                            if (IsValueType && IsOptionnal)
                            {
                                return Name + "==null?(void*)IntPtr.Zero:" + TempName;
                            }
                            else
                            {
                                return TempName;
                            }
                        }
                        if (IsFixed && !HasNativeValueType)
                        {
                            return TempName;
                        }
                        if (HasNativeValueType)
                        {
                            return "&" + TempName;
                        }
                        if (IsValueType)
                        {
                            return "&" + Name;
                        }
                        else
                        {
                            return TempName;
                        }
                    }
                    if (IsRefInValueTypeOptional)
                        return "(" + Name + ".HasValue)?&" + TempName + ":(void*)IntPtr.Zero";
                    if (IsRefInValueTypeByValue)
                        return "&" + Name;
                    if (PublicType is CSharpEnum || PublicType.Type == typeof (uint))
                        return "unchecked((int)" + Name + ")";
                    if (PublicType.Type == typeof (string))
                        return "(void*)" + TempName;
                    if (PublicType.Type == typeof (bool))
                        return "(" + Name + "?1:0)";
                    if (PublicType.Type == typeof (byte))
                        return "(int)" + Name;
                    if (PublicType is CSharpInterface && Attribute == ParameterAttribute.In && !IsArray)
                        return "(void*)((" + Name + " == null)?IntPtr.Zero:" + Name + ".NativePointer)";
                    if (IsArray)
                    {
                        if (HasNativeValueType)
                        {
                            return TempName;
                        }
                        else if (IsValueType && IsOptionnal)
                        {
                            return Name + "==null?(void*)IntPtr.Zero:" + TempName;
                        }
                    }
                    if (IsFixed && !HasNativeValueType)
                        return TempName;
                    if (PublicType.Type == typeof (IntPtr) && !IsArray)
                        return "(void*)" + Name;
                    if (HasNativeValueType)
                        return "&" + TempName;
                    if (PublicType.Name == Global.Name + ".Size")
                        return "(void*)" + Name;
                    if (PublicType.Name == Global.Name + ".Color3")
                        return string.Format("{0}.Red,{0}.Green,{0}.Blue", Name);
                    if (PublicType.Name == Global.Name + ".Color4")
                        return string.Format("{0}.Red,{0}.Green,{0}.Blue,{0}.Alpha", Name);
                    if (PublicType.Name == Global.Name + ".Vector4")
                        return string.Format("{0}.X,{0}.Y,{0}.Z,{0}.W", Name);
                    if (PublicType.Name == Global.Name + ".Int4")
                        return string.Format("{0}.X,{0}.Y,{0}.Z,{0}.W", Name);
                    return Name;
                }
            }

            public object Clone()
            {
                var parameter = (Parameter)MemberwiseClone();
                parameter.ParentContainer = null;
                return parameter;
            }
        }

        public object Clone()
        {
            var  method = (CSharpMethod)MemberwiseClone();
            method.ClearItems();
            foreach (var parameter in Parameters)
                method.Add((Parameter) parameter.Clone());
            method.ParentContainer = null;
            return method;
        }
    }
}