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
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace SampleFramework
{
    #region STICKYKEYS

    [StructLayout(LayoutKind.Sequential)]
    struct STICKYKEYS
    {
        #region Fields

        public int cbSize;
        public int dwFlags;

        #endregion
    }

    #endregion

    #region StickyKeys

    /// <summary>
    /// Manages the enabling and disabling of sticky key settings.
    /// </summary>
    public static class StickyKeys
    {
        #region Constants

        const uint SPI_GETSTICKYKEYS = 58;
        const uint SPI_SETSTICKYKEYS = 59;
        const uint SKF_HOTKEYACTIVE = 4;
        const uint SKF_CONFIRMHOTKEY = 8;
        const uint SKF_STICKYKEYSON = 1;

        #endregion

        #region Variables

        static STICKYKEYS stored = new STICKYKEYS();

        #endregion

        #region Constructor

        static StickyKeys()
        {
            stored.cbSize = 0;
            stored.dwFlags = 0;

            int bytes = Marshal.SizeOf(stored);

            IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
            Marshal.StructureToPtr(stored, pointer, false);

            NativeMethods.SystemParametersInfo(SPI_GETSTICKYKEYS, (uint)bytes, pointer, 0);

            stored = (STICKYKEYS)Marshal.PtrToStructure(pointer, typeof(STICKYKEYS));
            Marshal.FreeCoTaskMem(pointer);
        }

        #endregion

        #region Methods

        /// <summary>
        /// Disables sticky keys.
        /// </summary>
        public static void Disable()
        {
            if ((stored.dwFlags & SKF_STICKYKEYSON) == 0)
            {
                STICKYKEYS keys = new STICKYKEYS();
                keys.dwFlags = stored.dwFlags;
                keys.cbSize = stored.cbSize;

                keys.dwFlags &= ~(int)SKF_HOTKEYACTIVE;
                keys.dwFlags &= ~(int)SKF_CONFIRMHOTKEY;

                int bytes = Marshal.SizeOf(keys);
                IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
                Marshal.StructureToPtr(keys, pointer, false);

                NativeMethods.SystemParametersInfo(SPI_SETSTICKYKEYS, (uint)bytes, pointer, 0);

                Marshal.FreeCoTaskMem(pointer);
            }
        }

        /// <summary>
        /// Restores the sticky key settings.
        /// </summary>
        public static void Restore()
        {
            int bytes = Marshal.SizeOf(stored);
            IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
            Marshal.StructureToPtr(stored, pointer, false);

            NativeMethods.SystemParametersInfo(SPI_SETSTICKYKEYS, (uint)bytes, pointer, 0);

            Marshal.FreeCoTaskMem(pointer);
        }

        #endregion
    }

    #endregion
}
