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

namespace SlimDX2.Direct3D11
{
    public partial class ClassInstance
    {
        /// <summary>
        ///   Gets the instance name of the current HLSL class.
        /// </summary>
        /// <remarks>
        ///   GetInstanceName will return a valid name only for instances acquired using <see cref = "SlimDX2.Direct3D11.ClassLinkage.GetClassInstance" />.For more information about using the <see cref = "SlimDX2.Direct3D11.ClassInstance" /> interface, see {{Dynamic Linking}}.
        /// </remarks>
        /// <returns>The instance name of the current HLSL class.</returns>
        /// <unmanaged>void GetInstanceName([Out, Buffer, Optional] LPSTR pInstanceName,[InOut] SIZE_T* pBufferLength)</unmanaged>
        public string InstanceName
        {
            get
            {
                unsafe
                {
                    Size size = new Size();
                    GetInstanceName(IntPtr.Zero, ref size);
                    sbyte* pBuffer = stackalloc sbyte[size];
                    GetInstanceName((IntPtr) pBuffer, ref size);
                    return new string(pBuffer);
                }
            }
        }

        /// <summary>
        ///   Gets the type of the current HLSL class.
        /// </summary>
        /// <remarks>
        ///   GetTypeName will return a valid name only for instances acquired using <see cref = "SlimDX2.Direct3D11.ClassLinkage.GetClassInstance" />.For more information about using the <see cref = "SlimDX2.Direct3D11.ClassInstance" /> interface, see {{Dynamic Linking}}.
        /// </remarks>
        /// <returns>Type of the current HLSL class.</returns>
        /// <unmanaged>void GetTypeName([Out, Buffer, Optional] LPSTR pTypeName,[InOut] SIZE_T* pBufferLength)</unmanaged>
        public string TypeName
        {
            get
            {
                unsafe
                {
                    Size size = new Size();
                    GetInstanceName(IntPtr.Zero, ref size);
                    sbyte* pBuffer = stackalloc sbyte[size];
                    GetTypeName((IntPtr) pBuffer, ref size);
                    return new string(pBuffer);
                }
            }
        }
    }
}