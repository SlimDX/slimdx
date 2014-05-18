using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimMath
{
    /// <summary>
    /// Represents a 3x2 matrix.
    /// </summary>
    public struct Matrix3x2
    {
        /// <summary>
        /// Value at row 1 column 1 of the matrix.
        /// </summary>
        public float M11;

        /// <summary>
        /// Value at row 1 column 2 of the matrix.
        /// </summary>
        public float M12;

        /// <summary>
        /// Value at row 2 column 1 of the matrix.
        /// </summary>
        public float M21;

        /// <summary>
        /// Value at row 2 column 2 of the matrix.
        /// </summary>
        public float M22;

        /// <summary>
        /// Value at row 3 column 1 of the matrix.
        /// </summary>
        public float M31;

        /// <summary>
        /// Value at row 3 column 2 of the matrix.
        /// </summary>
        public float M32; 

        /// <summary>
        /// Gets the identity matrix.
        /// </summary>
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
