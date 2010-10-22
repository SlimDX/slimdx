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
using System.Diagnostics;
using System.Reflection;

namespace SlimDX2
{
    /// <summary>
    ///   Root class for all Cpp interop object.
    /// </summary>
    public partial class CppObject
    {
        private static readonly Assembly interopAssembly;
        protected unsafe void* _nativePointer;

        /// <summary>
        ///   Static initializer.
        /// </summary>
        static CppObject()
        {
            // Generate Interop Assembly
            interopAssembly = DynamicInterop.Generate(_interopCalliSignatures, false, null);
            // Bind AppDomain AssemblyResolve to return Interop Assembly
            AppDomain.CurrentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;
        }

        /// <summary>
        ///   Fake Init Method. Force CppObject to initialize
        /// </summary>
        /// <returns></returns>
        internal static void Init()
        {
            Debug.WriteLineIf(interopAssembly == null, "Warning, interop assembly was not dynamically generated");
        }

        /// <summary>
        ///   Default constructor.
        /// </summary>
        /// <param name = "pointer">Pointer to Cpp Object</param>
        public CppObject(IntPtr pointer)
        {
            NativePointer = pointer;
            //unsafe
            //{
            //    _nativePointer = (void*) pointer;
            //}
        }

        protected CppObject()
        {
        }

        /// <summary>
        ///   Get a pointer to the underlying Cpp Object
        /// </summary>
        public IntPtr NativePointer
        {
            get
            {
                unsafe
                {
                    return (IntPtr) _nativePointer;
                }
            }
            set
            {
                unsafe
                {
                    void* newNativePointer = (void*) value;
                    if (_nativePointer != newNativePointer)
                    {
                        _nativePointer = newNativePointer;
                        NativePointerUpdated();
                    }
                }
            }
        }

        /// <summary>
        ///   Method that could be modified by inherited class
        /// </summary>
        protected virtual void NativePointerUpdated()
        {
        }

        /// <summary>
        ///   Assembly Resolve callback
        /// </summary>
        /// <param name = "sender"></param>
        /// <param name = "args"></param>
        /// <returns></returns>
        private static Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
        {
            return (args.Name == interopAssembly.FullName) ? interopAssembly : null;
        }
    }
}