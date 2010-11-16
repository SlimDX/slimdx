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
using System.IO;
using System.Runtime.InteropServices;
using System.Security;
using SlimDX.Direct3D;

namespace SlimDX
{
    /// <summary>
    /// TODO: this is temporary. This class is going to be merged with Utilities and should be also internal
    /// </summary>
    internal static partial class Utilities
    {
        static Utilities()
        {
            CppObject.Init();
        }

        [DllImport("msvcrt.dll", EntryPoint = "memcpy", CallingConvention = CallingConvention.Cdecl,
            SetLastError = false), SuppressUnmanagedCodeSecurity]
        public static extern IntPtr CopyMemory(IntPtr dest, IntPtr src, ulong count);

        public static IntPtr CopyMemory(IntPtr dest, IntPtr src, int count)
        {
            return CopyMemory(dest, src, (ulong) count);
        }

        /// <summary>
        /// Return the sizeof a struct from a CLR. Equivalent to sizeof operator but works on generics too.
        /// </summary>
        /// <typeparam name="T">a struct to evaluate</typeparam>
        /// <returns>sizeof this struct</returns>
        public static int SizeOf<T>() where T : struct
        {
            return SlimDX.Interop.SizeOf<T>();            
        }

        /// <summary>
        /// NOT FULLY WORKING YET. NEED ALSO MORE TEST
        /// </summary>
        /// <param name="pDest"></param>
        /// <param name="pSrc"></param>
        /// <param name="count"></param>
        private static unsafe void memcpy(void* pDest, void* pSrc, int count)
        {
            SlimDX.Interop.memcpy(pDest, pSrc, count);
        }

        internal static IntPtr Read<T>(IntPtr pSrc, ref T data) where T : struct
        {
            unsafe
            {
                return (IntPtr)SlimDX.Interop.Read<T>((void*) pSrc, ref data);
            }
        }

        internal static IntPtr Read<T>(IntPtr pSrc, T[] data, int offset, int count) where T : struct
        {
            unsafe
            {
                return (IntPtr) SlimDX.Interop.Read<T>((void*) pSrc, data, offset, count);
            }
        }

        internal static IntPtr Write<T>(IntPtr pDest, ref T data) where T : struct
        {
            unsafe
            {
                return (IntPtr) SlimDX.Interop.Write<T>((void*) pDest, ref data);
            }
        }

        internal static IntPtr Write<T>(IntPtr pDest, T[] data, int offset, int count) where T : struct
        {
            unsafe
            {
                return (IntPtr) SlimDX.Interop.Write<T>((void*) pDest, data, offset, count);
            }
        }

        public static void ConvertRECTToRectangle(ref System.Drawing.Rectangle rect)
        {
            rect = new System.Drawing.Rectangle(rect.X, rect.Y, rect.Width - rect.X, rect.Height - rect.Y);
        }

        public static void ConvertRectangleToRect(ref System.Drawing.Rectangle rect)
        {
            rect = new System.Drawing.Rectangle(rect.X, rect.Y, rect.Width - rect.X, rect.Height - rect.Y);
        }

        [Flags]
        public enum CLSCTX : uint
        {
            CLSCTX_INPROC_SERVER = 0x1,
            CLSCTX_INPROC_HANDLER = 0x2,
            CLSCTX_LOCAL_SERVER = 0x4,
            CLSCTX_INPROC_SERVER16 = 0x8,
            CLSCTX_REMOTE_SERVER = 0x10,
            CLSCTX_INPROC_HANDLER16 = 0x20,
            CLSCTX_RESERVED1 = 0x40,
            CLSCTX_RESERVED2 = 0x80,
            CLSCTX_RESERVED3 = 0x100,
            CLSCTX_RESERVED4 = 0x200,
            CLSCTX_NO_CODE_DOWNLOAD = 0x400,
            CLSCTX_RESERVED5 = 0x800,
            CLSCTX_NO_CUSTOM_MARSHAL = 0x1000,
            CLSCTX_ENABLE_CODE_DOWNLOAD = 0x2000,
            CLSCTX_NO_FAILURE_LOG = 0x4000,
            CLSCTX_DISABLE_AAA = 0x8000,
            CLSCTX_ENABLE_AAA = 0x10000,
            CLSCTX_FROM_DEFAULT_CONTEXT = 0x20000,
            CLSCTX_INPROC = CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER,
            CLSCTX_SERVER = CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER,
            CLSCTX_ALL = CLSCTX_SERVER | CLSCTX_INPROC_HANDLER
        }

        [DllImport("ole32.dll", ExactSpelling = true, PreserveSig = true)]
        static public extern Result CoCreateInstance([In, MarshalAs(UnmanagedType.LPStruct)] Guid rclsid, IntPtr pUnkOuter, CLSCTX dwClsContext, [In, MarshalAs(UnmanagedType.LPStruct)] Guid riid, out IntPtr comObject);

        public static string BlobToString(Blob blob)
        {
            string output;
            unsafe
            {
                output = new string((sbyte*) blob.GetBufferPointer());
            }
            blob.Release();
            return output;
        }

        /// <summary>
        ///   Read stream to a byte[] buffer
        /// </summary>
        /// <param name = "stream">input stream</param>
        /// <returns>a byte[] buffer</returns>
        public static byte[] ReadStream(Stream stream)
        {
            int readLength = 0;
            return ReadStream(stream, ref readLength);
        }

        /// <summary>
        ///   Read stream to a byte[] buffer
        /// </summary>
        /// <param name = "stream">input stream</param>
        /// <param name = "readLength">length to read</param>
        /// <returns>a byte[] buffer</returns>
        public static byte[] ReadStream(Stream stream, ref int readLength)
        {
            Debug.Assert(stream != null);
            Debug.Assert(stream.CanRead);
            int num = readLength;
            Debug.Assert(num <= (stream.Length - stream.Position));
            if (num == 0)
                readLength = (int) (stream.Length - stream.Position);
            num = readLength;

            Debug.Assert(num >= 0);
            if (num == 0)
                return new byte[0];

            byte[] buffer = new byte[num];
            int bytesRead = 0;
            if (num > 0)
            {
                do
                {
                    bytesRead += stream.Read(buffer, bytesRead, readLength - bytesRead);
                } while (bytesRead < readLength);
            }
            return buffer;
        }
    }
}