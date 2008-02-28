using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.Drawing;

namespace SampleFramework
{
    enum ShowWindow
    {
        Hide = 0,
        Normal = 1,
        ShowMinimized = 2,
        Maximize = 3,
        ShowMaximized = 3,
        ShowNoActivate = 4,
        Show = 5,
        Minimize = 6,
        ShowMinNoActive = 7,
        ShowNA = 8,
        Restore = 9,
        ShowDefault = 10,
        ForceMinimize = 11
    }

    [StructLayout(LayoutKind.Sequential)]
    struct WINDOWPLACEMENT
    {
        #region Fields

        public int length;
        public int flags;
        public ShowWindow showCmd;
        public Point ptMinPosition;
        public Point ptMaxPosition;
        public NativeRectangle rcNormalPosition;

        #endregion

        #region Properties

        public static int Length
        {
            get { return Marshal.SizeOf(typeof(WINDOWPLACEMENT)); }
        }

        #endregion
    }
}
