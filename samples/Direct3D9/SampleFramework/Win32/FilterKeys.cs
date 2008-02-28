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
