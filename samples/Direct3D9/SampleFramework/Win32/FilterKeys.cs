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
    #region FILTERKEYS

    [StructLayout(LayoutKind.Sequential)]
    struct FILTERKEYS
    {
        #region Fields

        public int cbSize;
        public int dwFlags;

        #endregion
    }

    #endregion

    #region FilterKeys

    /// <summary>
    /// Manages the enabling and disabling of filter key settings.
    /// </summary>
    public static class FilterKeys
    {
        #region Constants

        const uint SPI_GETFILTERKEYS = 50;
        const uint SPI_SETFILTERKEYS = 59;
        const uint FKF_HOTKEYACTIVE = 4;
        const uint FKF_CONFIRMHOTKEY = 8;
        const uint FKF_FILTERKEYSON = 1;

        #endregion

        #region Variables

        static FILTERKEYS stored = new FILTERKEYS();

        #endregion

        #region Constructor

        static FilterKeys()
        {
            stored.cbSize = 0;
            stored.dwFlags = 0;

            int bytes = Marshal.SizeOf(stored);

            IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
            Marshal.StructureToPtr(stored, pointer, false);

            NativeMethods.SystemParametersInfo(SPI_GETFILTERKEYS, (uint)bytes, pointer, 0);

            stored = (FILTERKEYS)Marshal.PtrToStructure(pointer, typeof(FILTERKEYS));
            Marshal.FreeCoTaskMem(pointer);
        }

        #endregion

        #region Methods

        /// <summary>
        /// Disables filter keys.
        /// </summary>
        public static void Disable()
        {
            if ((stored.dwFlags & FKF_FILTERKEYSON) == 0)
            {
                FILTERKEYS keys = new FILTERKEYS();
                keys.dwFlags = stored.dwFlags;
                keys.cbSize = stored.cbSize;

                keys.dwFlags &= ~(int)FKF_HOTKEYACTIVE;
                keys.dwFlags &= ~(int)FKF_CONFIRMHOTKEY;

                int bytes = Marshal.SizeOf(keys);
                IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
                Marshal.StructureToPtr(keys, pointer, false);

                NativeMethods.SystemParametersInfo(SPI_SETFILTERKEYS, (uint)bytes, pointer, 0);

                Marshal.FreeCoTaskMem(pointer);
            }
        }

        /// <summary>
        /// Restores the filter key settings.
        /// </summary>
        public static void Restore()
        {
            int bytes = Marshal.SizeOf(stored);
            IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
            Marshal.StructureToPtr(stored, pointer, false);

            NativeMethods.SystemParametersInfo(SPI_SETFILTERKEYS, (uint)bytes, pointer, 0);

            Marshal.FreeCoTaskMem(pointer);
        }

        #endregion
    }

    #endregion
}
