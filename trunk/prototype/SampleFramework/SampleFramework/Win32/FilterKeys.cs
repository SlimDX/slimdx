using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace SampleFramework
{
    /// <summary>
    /// Manages the enabling and disabling of filter key settings.
    /// </summary>
    static class FilterKeys
    {
        // constants
        const uint SPI_GETFILTERKEYS = 50;
        const uint SPI_SETFILTERKEYS = 59;
        const uint FKF_HOTKEYACTIVE = 4;
        const uint FKF_CONFIRMHOTKEY = 8;
        const uint FKF_FILTERKEYSON = 1;

        // variables
        static FILTERKEYS stored = new FILTERKEYS();

        /// <summary>
        /// Initializes the <see cref="FilterKeys"/> class.
        /// </summary>
        static FilterKeys()
        {
            // clear the fields
            stored.cbSize = 0;
            stored.dwFlags = 0;

            // grab the size
            int bytes = Marshal.SizeOf(stored);

            // marshal the structure
            IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
            Marshal.StructureToPtr(stored, pointer, false);

            // get filter key settings
            NativeMethods.SystemParametersInfo(SPI_GETFILTERKEYS, (uint)bytes, pointer, 0);

            // marshal the structure
            stored = (FILTERKEYS)Marshal.PtrToStructure(pointer, typeof(FILTERKEYS));
            Marshal.FreeCoTaskMem(pointer);
        }

        /// <summary>
        /// Disables filter keys.
        /// </summary>
        public static void Disable()
        {
            // check if they are on
            if ((stored.dwFlags & FKF_FILTERKEYSON) == 0)
            {
                // build up the new structure
                FILTERKEYS keys = new FILTERKEYS();
                keys.dwFlags = stored.dwFlags;
                keys.cbSize = stored.cbSize;

                // set the correct flags
                keys.dwFlags &= ~(int)FKF_HOTKEYACTIVE;
                keys.dwFlags &= ~(int)FKF_CONFIRMHOTKEY;

                // marshal the structure
                int bytes = Marshal.SizeOf(keys);
                IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
                Marshal.StructureToPtr(keys, pointer, false);

                // set the filter key settings
                NativeMethods.SystemParametersInfo(SPI_SETFILTERKEYS, (uint)bytes, pointer, 0);

                // clean up memory
                Marshal.FreeCoTaskMem(pointer);
            }
        }

        /// <summary>
        /// Restores the filter key settings.
        /// </summary>
        public static void Restore()
        {
            // marshal the structure
            int bytes = Marshal.SizeOf(stored);
            IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
            Marshal.StructureToPtr(stored, pointer, false);

            // set the filter key settings
            NativeMethods.SystemParametersInfo(SPI_SETFILTERKEYS, (uint)bytes, pointer, 0);

            // clean up memory
            Marshal.FreeCoTaskMem(pointer);
        }
    }
}
