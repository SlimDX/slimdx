using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.Drawing;

namespace SampleFramework
{
    [StructLayout(LayoutKind.Sequential)]
    struct NativeMessage
    {
        #region Fields

        public IntPtr hWnd;
        public uint msg;
        public IntPtr wParam;
        public IntPtr lParam;
        public uint time;
        public Point p;

        #endregion
    }
}
