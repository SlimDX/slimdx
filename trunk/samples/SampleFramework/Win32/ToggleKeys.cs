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
using System.Runtime.InteropServices;

namespace SampleFramework
{
    /// <summary>
    /// Manages the enabling and disabling of toggle key settings.
    /// </summary>
    static class ToggleKeys
    {
        // constants
        const uint SPI_GETTOGGLEKEYS = 52;
        const uint SPI_SETTOGGLEKEYS = 53;
        const uint TKF_HOTKEYACTIVE = 4;
        const uint TKF_CONFIRMHOTKEY = 8;
        const uint TKF_TOGGLEKEYSON = 1;

        // variables
        static TOGGLEKEYS stored = new TOGGLEKEYS();

        /// <summary>
        /// Initializes the <see cref="ToggleKeys"/> class.
        /// </summary>
        static ToggleKeys()
        {
            // grab the size
            int bytes = Marshal.SizeOf(stored);

            // marshal the structure
            IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
            Marshal.StructureToPtr(stored, pointer, false);

            // get the toggle keys settings
            NativeMethods.SystemParametersInfo(SPI_GETTOGGLEKEYS, (uint)bytes, pointer, 0);

            // marshal the structure
            stored = (TOGGLEKEYS)Marshal.PtrToStructure(pointer, typeof(TOGGLEKEYS));
            Marshal.FreeCoTaskMem(pointer);

            // hook into the app domain unload so that we can ensure that the
            // settings get returned to normal
            AppDomain.CurrentDomain.DomainUnload += CurrentDomain_DomainUnload;
            AppDomain.CurrentDomain.ProcessExit += CurrentDomain_ProcessExit;
        }

        /// <summary>
        /// Disables toggle keys.
        /// </summary>
        public static void Disable()
        {
            // check if they are on
            if ((stored.dwFlags & TKF_TOGGLEKEYSON) == 0)
            {
                // build up the new settings
                TOGGLEKEYS keys = new TOGGLEKEYS();
                keys.dwFlags = stored.dwFlags;
                keys.cbSize = stored.cbSize;

                // set the correct flags
                keys.dwFlags &= ~(int)TKF_HOTKEYACTIVE;
                keys.dwFlags &= ~(int)TKF_CONFIRMHOTKEY;

                // marshal the structure
                int bytes = Marshal.SizeOf(keys);
                IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
                Marshal.StructureToPtr(keys, pointer, false);

                // set the toggle keys settings
                NativeMethods.SystemParametersInfo(SPI_SETTOGGLEKEYS, (uint)bytes, pointer, 0);

                // clean up memory
                Marshal.FreeCoTaskMem(pointer);
            }
        }

        /// <summary>
        /// Restores the toggle key settings.
        /// </summary>
        public static void Restore()
        {
            // marshal the structure
            int bytes = Marshal.SizeOf(stored);
            IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
            Marshal.StructureToPtr(stored, pointer, false);

            // set the toggle keys settings
            NativeMethods.SystemParametersInfo(SPI_SETTOGGLEKEYS, (uint)bytes, pointer, 0);

            // clean up memory
            Marshal.FreeCoTaskMem(pointer);
        }

        /// <summary>
        /// Handles the DomainUnload event of the CurrentDomain control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        static void CurrentDomain_DomainUnload(object sender, EventArgs e)
        {
            // ensure that the settings are restored
            Restore();
        }

        /// <summary>
        /// Handles the ProcessExit event of the CurrentDomain control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        static void CurrentDomain_ProcessExit(object sender, EventArgs e)
        {
            // ensure that the settings are restored
            Restore();
        }
    }
}
