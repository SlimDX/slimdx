using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace SampleFramework
{
    #region TOGGLEKEYS

    [StructLayout(LayoutKind.Sequential)]
    struct TOGGLEKEYS
    {
        #region Fields

        public int cbSize;
        public int dwFlags;

        #endregion
    }

    #endregion

    #region ToggleKeys

    public static class ToggleKeys
    {
        #region Constants

        const uint SPI_GETTOGGLEKEYS = 52;
        const uint SPI_SETTOGGLEKEYS = 53;
        const uint TKF_HOTKEYACTIVE = 4;
        const uint TKF_CONFIRMHOTKEY = 8;
        const uint TKF_TOGGLEKEYSON = 1;

        #endregion

        #region Variables

        static TOGGLEKEYS stored = new TOGGLEKEYS();

        #endregion

        #region Constructor

        static ToggleKeys()
        {
            int bytes = Marshal.SizeOf(stored);

            IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
            Marshal.StructureToPtr(stored, pointer, false);

            NativeMethods.SystemParametersInfo(SPI_GETTOGGLEKEYS, (uint)bytes, pointer, 0);

            stored = (TOGGLEKEYS)Marshal.PtrToStructure(pointer, typeof(TOGGLEKEYS));
            Marshal.FreeCoTaskMem(pointer);
        }

        #endregion

        #region Methods

        public static void Disable()
        {
            if ((stored.dwFlags & TKF_TOGGLEKEYSON) == 0)
            {
                TOGGLEKEYS keys = new TOGGLEKEYS();
                keys.dwFlags = stored.dwFlags;
                keys.cbSize = stored.cbSize;

                keys.dwFlags &= ~(int)TKF_HOTKEYACTIVE;
                keys.dwFlags &= ~(int)TKF_CONFIRMHOTKEY;

                int bytes = Marshal.SizeOf(keys);
                IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
                Marshal.StructureToPtr(keys, pointer, false);

                NativeMethods.SystemParametersInfo(SPI_SETTOGGLEKEYS, (uint)bytes, pointer, 0);

                Marshal.FreeCoTaskMem(pointer);
            }
        }

        public static void Restore()
        {
            int bytes = Marshal.SizeOf(stored);
            IntPtr pointer = Marshal.AllocCoTaskMem(bytes);
            Marshal.StructureToPtr(stored, pointer, false);

            NativeMethods.SystemParametersInfo(SPI_SETTOGGLEKEYS, (uint)bytes, pointer, 0);

            Marshal.FreeCoTaskMem(pointer);
        }

        #endregion
    }

    #endregion
}
