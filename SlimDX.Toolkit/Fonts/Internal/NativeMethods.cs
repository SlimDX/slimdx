using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace SlimDX.Toolkit
{
    static class NativeMethods
    {
        public const int OBJ_BITMAP = 7;

        [StructLayout(LayoutKind.Sequential)]
        public struct RECT
        {
            public int left, top, right, bottom;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct BITMAP
        {
            public int bmType;
            public int bmWidth;
            public int bmHeight;
            public int bmWidthBytes;
            public short bmPlanes;
            public short bmBitsPixel;
            public IntPtr bmBits;
        }

        [DllImport("gdi32.dll")]
        public static extern IntPtr CreateSolidBrush(uint crColor);

        [DllImport("gdi32.dll")]
        public static extern bool DeleteObject(IntPtr hObject);

        [DllImport("gdi32.dll")]
        public static extern IntPtr GetCurrentObject(IntPtr hdc, uint uObjectType);

        [DllImport("gdi32.dll")]
        public static extern int GetObject(IntPtr hgdiobj, int cbBuffer, IntPtr lpvObject);

        [DllImport("user32.dll")]
        public static extern int FillRect(IntPtr hDC, ref RECT lprc, IntPtr hbr);

        public static BITMAP GetBitmap(IntPtr hbitmap)
        {
            var result = new BITMAP();
            unsafe { GetObject(hbitmap, Marshal.SizeOf(result), new IntPtr(&result)); }
            return result;
        }
    }
}
