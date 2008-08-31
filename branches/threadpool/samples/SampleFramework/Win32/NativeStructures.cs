/*
* Copyright (c) 2007-2008 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
using System;
using System.Drawing;
using System.Runtime.InteropServices;

namespace SampleFramework
{
    /// <summary>
    /// Represents the unmanaged RECT type.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    struct NativeRectangle
    {
        /// <summary>
        /// The left bound of the rectangle.
        /// </summary>
        public int left;

        /// <summary>
        /// The top bound of the rectangle.
        /// </summary>
        public int top;

        /// <summary>
        /// The right bound of the rectangle.
        /// </summary>
        public int right;

        /// <summary>
        /// The bottom bound of the rectangle.
        /// </summary>
        public int bottom;
    }

    /// <summary>
    /// Represents the unmanaged MSG type.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    struct NativeMessage
    {
        /// <summary>
        /// The window handle.
        /// </summary>
        public IntPtr hWnd;

        /// <summary>
        /// The message ID.
        /// </summary>
        public uint msg;

        /// <summary>
        /// The first generic parameter.
        /// </summary>
        public IntPtr wParam;

        /// <summary>
        /// The second generic parameter.
        /// </summary>
        public IntPtr lParam;

        /// <summary>
        /// The timing of the message.
        /// </summary>
        public uint time;

        /// <summary>
        /// A context dependent point.
        /// </summary>
        public Point p;
    }

    /// <summary>
    /// Represents the unmanaged WINDOWPLACEMENT type.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    struct WINDOWPLACEMENT
    {
        /// <summary>
        /// The size of the structure, in bytes.
        /// </summary>
        public int length;

        /// <summary>
        /// Window placement flags.
        /// </summary>
        public int flags;

        /// <summary>
        /// The ShowWindow flag.
        /// </summary>
        public int showCmd;

        /// <summary>
        /// The minimum point of the window.
        /// </summary>
        public Point ptMinPosition;

        /// <summary>
        /// The maximum point of the window.
        /// </summary>
        public Point ptMaxPosition;

        /// <summary>
        /// The restored position of the window.
        /// </summary>
        public NativeRectangle rcNormalPosition;

        /// <summary>
        /// Gets the size of the structure, in bytes.
        /// </summary>
        public static int Length
        {
            get { return Marshal.SizeOf(typeof(WINDOWPLACEMENT)); }
        }
    }
}
