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
using SlimDX2.Windows;

namespace SlimDX2.XAPO
{
    public partial struct LockParameters
    {
        public WaveFormat Format { get; set; }

        internal unsafe partial struct __Native
        {
            internal unsafe void __MarshalFree()
            {
                if (FormatPointer != IntPtr.Zero)
                    Marshal.FreeCoTaskMem(FormatPointer);
            }

        }

        internal unsafe void __MarshalTo(ref __Native @ref)
        {
            @ref.FormatPointer = IntPtr.Zero;
            if (Format != null)
            {
                int sizeOfFormat = Marshal.SizeOf(Format);
                @ref.FormatPointer = Marshal.AllocCoTaskMem(sizeOfFormat);
                Marshal.StructureToPtr(Format, @ref.FormatPointer, false);
            }
            this.MaxFrameCount = @ref.MaxFrameCount;
        }

        internal unsafe void __MarshalFrom(ref __Native @ref)
        {
            this.Format = null;
            this.FormatPointer = @ref.FormatPointer;
            if (this.FormatPointer != IntPtr.Zero)
                this.Format = WaveFormat.MarshalFromPtr(this.FormatPointer);
            this.MaxFrameCount = @ref.MaxFrameCount;
        }


        // Method to marshal from native to managed struct
        internal unsafe void __MarshalFrom(__Native* @ref)
        {
            this.Format = null;
            this.FormatPointer = @ref->FormatPointer;
            if (this.FormatPointer != IntPtr.Zero)
                this.Format = WaveFormat.MarshalFromPtr(this.FormatPointer);
            this.MaxFrameCount = @ref->MaxFrameCount;
        }
    }
}