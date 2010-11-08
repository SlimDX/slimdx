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

namespace SlimDX2
{
    /// <summary>
    /// A COM Interface Callback
    /// </summary>
    /// <typeparam name="T"></typeparam>
    internal class ComObjectCallback : ComObject
    {
        private readonly CppObjectCallback cppCallback;
        private object _callback;
        private int _count;

        /// <summary>
        /// Default Constructor.
        /// </summary>
        /// <param name="callback">the client callback</param>
        /// <param name="numberOfCallbackMethods">number of methods to allocate in the VTBL</param>
        protected ComObjectCallback(object callback, int numberOfCallbackMethods)
        {
            _callback = callback;
            cppCallback = new CppObjectCallback(numberOfCallbackMethods + 3);
            NativePointer = cppCallback.NativePointer;

            AddMethod(new QueryInterfaceDelegate(QueryInterfaceImpl));
            AddMethod(new AddRefDelegate(AddRefImpl));
            AddMethod(new ReleaseDelegate(ReleaseImpl));
        }

        /// <summary>
        /// Add a method supported by this interface. This method is typically called from inherited constructor.
        /// </summary>
        /// <param name="method">the managed delegate method</param>
        protected void AddMethod(Delegate method)
        {
            cppCallback.AddMethod(method);
        }

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate int QueryInterfaceDelegate(ref Guid guid, out IntPtr output);

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public  delegate int AddRefDelegate();

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public  delegate int ReleaseDelegate();

        private int QueryInterfaceImpl(ref Guid guid, out IntPtr output)
        {
            if (guid == _callback.GetType().GUID)
            {
                output = NativePointer;
                return Result.Ok.Code;
            }
            output = IntPtr.Zero;
            return Result.NoInterface.Code;
        }

        private int AddRefImpl()
        {
            _count++;
            return _count;
        }

        private int ReleaseImpl()
        {
            _count--;
            return _count;
        }
    }
}