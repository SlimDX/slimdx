using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace SampleFramework
{
    /// <summary>
    /// Manages the enabling and disabling of sticky key settings.
    /// </summary>
    static class StickyKeys
    {
        // constants
        const uint SPI_GETSTICKYKEYS = 58;
        const uint SPI_SETSTICKYKEYS = 59;
        const uint SKF_HOTKEYACTIVE = 4;
        const uint SKF_CONFIRMHOTKEY = 8;
        const uint SKF_STICKYKEYSON = 1;

        // variables
        static STICKYKEYS stored = new STICKYKEYS();

        /// <summary>
        /// Initializes the <see cref="StickyKeys"/> class.
        /// </summary>
        static StickyKeys()
        {
            // clear the fields
            stored.cbSize = 0;
            stored.dwFlags = 0;

            // grab the size
            int bytes = Marshal.SizeOf(stored);

            // marshal the structure
            IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
            Marshal.StructureToPtr(stored, pointer, false);

            // get sticky key settings
            NativeMethods.SystemParametersInfo(SPI_GETSTICKYKEYS, (uint)bytes, pointer, 0);

            // marshal the structure
            stored = (STICKYKEYS)Marshal.PtrToStructure(pointer, typeof(STICKYKEYS));
            Marshal.FreeCoTaskMem(pointer);

            // hook into the app domain unload so that we can ensure that the
            // settings get returned to normal
            AppDomain.CurrentDomain.DomainUnload += CurrentDomain_DomainUnload;
            AppDomain.CurrentDomain.ProcessExit += CurrentDomain_ProcessExit;
        }

        /// <summary>
        /// Disables sticky keys.
        /// </summary>
        public static void Disable()
        {
            // check if they are on
            if ((stored.dwFlags & SKF_STICKYKEYSON) == 0)
            {
                // build up the new structure
                STICKYKEYS keys = new STICKYKEYS();
                keys.dwFlags = stored.dwFlags;
                keys.cbSize = stored.cbSize;

                // set the correct flags
                keys.dwFlags &= ~(int)SKF_HOTKEYACTIVE;
                keys.dwFlags &= ~(int)SKF_CONFIRMHOTKEY;

                // marshal the structure
                int bytes = Marshal.SizeOf(keys);
                IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
                Marshal.StructureToPtr(keys, pointer, false);

                // set the sticky key settings
                NativeMethods.SystemParametersInfo(SPI_SETSTICKYKEYS, (uint)bytes, pointer, 0);

                // clean up memory
                Marshal.FreeCoTaskMem(pointer);
            }
        }

        /// <summary>
        /// Restores the sticky key settings.
        /// </summary>
        public static void Restore()
        {
            // marshal the structure
            int bytes = Marshal.SizeOf(stored);
            IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
            Marshal.StructureToPtr(stored, pointer, false);

            // set the sticky key settings
            NativeMethods.SystemParametersInfo(SPI_SETSTICKYKEYS, (uint)bytes, pointer, 0);

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
