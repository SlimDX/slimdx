using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimMath
{
    public struct Matrix3x2
    {
        public float M11;
        public float M12;
        public float M21;
        public float M22;
        public float M31;
        public float M32; 

        public static Matrix3x2 Identity
        {
            get
            {
                var result = new Matrix3x2();
                result.M11 = 1.0f;
                result.M22 = 1.0f;

                return result;
            }
        }
    }
}
