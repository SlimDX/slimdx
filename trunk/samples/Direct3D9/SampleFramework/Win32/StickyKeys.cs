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
