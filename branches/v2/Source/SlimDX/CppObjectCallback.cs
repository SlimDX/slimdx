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
using System.Runtime.InteropServices;

namespace SlimDX
{
    /// <summary>
    /// An Interface Callback
    /// </summary>
    internal class CppObjectCallback : CppObject
    {
        private readonly List<Delegate> _methods;
        private readonly IntPtr _vtblPtr;

        /// <summary>
        /// Default Constructor.
        /// </summary>
        /// <param name="numberOfCallbackMethods">number of methods to allocate in the VTBL</param>
        internal CppObjectCallback(int numberOfCallbackMethods)
        {
            // Allocate ptr to vtbl + vtbl together
            NativePointer = Marshal.AllocHGlobal(IntPtr.Size * (numberOfCallbackMethods + 1));
            _vtblPtr = IntPtr.Add(NativePointer, IntPtr.Size);
            Marshal.WriteIntPtr(NativePointer, _vtblPtr);
            _methods = new List<Delegate>(numberOfCallbackMethods);
        }

        /// <summary>
        /// Add a method supported by this interface. This method is typically called from inherited constructor.
        /// </summary>
        /// <param name="method">the managed delegate method</param>
        internal void AddMethod(Delegate method)
        {
            int index = _methods.Count;
            _methods.Add(method);
            Marshal.WriteIntPtr(IntPtr.Add(_vtblPtr, index * IntPtr.Size), Marshal.GetFunctionPointerForDelegate(method));
        }

        ~CppObjectCallback()
        {
            Marshal.FreeHGlobal(NativePointer);
        }
    }
}
