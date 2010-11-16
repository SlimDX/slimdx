using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace SlimDX.Direct2D1
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Matrix3x2
    {
        public float M11;
        public float M12;
        public float M21;
        public float M22;
        public float M31;
        public float M32;
    }
 
}
