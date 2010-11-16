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
using System.Runtime.InteropServices;

namespace SlimDX
{
    /// <summary>
    /// Root IUnknown class to interop with COM object
    /// </summary>
    public class ComObject : CppObject
    {
        public ComObject(IntPtr pointer) : base(pointer)
        {
        }

        protected ComObject()
        {
        }

        /// <summary>
        ///   Query Interface for a particular GUID.
        /// </summary>
        /// <param name = "guid">GUID query interface</param>
        /// <param name = "outPtr">output object associated with this GUID, IntPtr.Zero in interface is not supported</param>
        public void QueryInterface(Guid guid, out IntPtr outPtr)
        {
            Result result = Marshal.QueryInterface(NativePointer, ref guid, out outPtr);
            result.CheckError();
        }

        ///<summary>
        /// Query Interface for a particular interface support.
        ///</summary>
        ///<typeparam name="T"></typeparam>
        ///<returns></returns>
        public T QueryInterface<T>() where T : ComObject
        {
            IntPtr parentPtr;
            this.QueryInterface(typeof (T).GUID, out parentPtr);
            return (T)Activator.CreateInstance(typeof(T), parentPtr);
        }

        /// <summary>
        ///   Increment COM reference
        /// </summary>
        /// <returns>Reference counter</returns>
        public int AddReference()
        {
            return Marshal.AddRef(NativePointer);
        }

        /// <summary>
        ///   Release COM reference
        /// </summary>
        /// <returns></returns>
        public int Release()
        {
            return Marshal.Release(NativePointer);
        }
    }
}