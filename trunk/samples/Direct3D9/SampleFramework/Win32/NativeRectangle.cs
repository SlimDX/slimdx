using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace SampleFramework
{
    [StructLayout(LayoutKind.Sequential)]
    struct NativeRectangle
    {
        #region Fields

        public int left;
        public int top;
        public int right;
        public int bottom;

        #endregion
    }
}
