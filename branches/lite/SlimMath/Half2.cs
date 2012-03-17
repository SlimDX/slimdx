/*
* Copyright (c) 2007-2010 SlimMath Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

using System;
using System.Globalization;
using System.Runtime.InteropServices;
using System.ComponentModel;

namespace SlimMath
{
    /// <summary>
    /// Defines a two component vector, using half precision floating point coordinates.
    /// </summary>
    [Serializable]
    [StructLayout(LayoutKind.Sequential)]
    public struct Half2 : IEquatable<Half2>, IFormattable
    {
        /// <summary>
        /// Gets or sets the X component of the vector.
        /// </summary>
        /// <value>The X component of the vector.</value>
        public Half X;

        /// <summary>
        /// Gets or sets the Y component of the vector.
        /// </summary>
        /// <value>The Y component of the vector.</value>
        public Half Y;

        /// <summary>
        /// Initializes a new instance of the <see cref="T:SlimMath.Half2"/> structure.
        /// </summary>
        /// <param name="x">The X component.</param>
        /// <param name="y">The Y component.</param>
        public Half2(Half x, Half y)
        {
            this.X = x;
            this.Y = y;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="T:SlimMath.Half2"/> structure.
        /// </summary>
        /// <param name="value">The value to set for both the X and Y components.</param>
        public Half2(Half value)
        {
            this.X = value;
            this.Y = value;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="T:SlimMath.Half2"/> structure.
        /// </summary>
        /// <param name="x">The X component.</param>
        /// <param name="y">The Y component.</param>
        public Half2(float x, float y)
        {
            this.X = (Half)x;
            this.Y = (Half)y;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="T:SlimMath.Half2"/> structure.
        /// </summary>
        /// <param name="value">The value to set for both the X and Y components.</param>
        public Half2(float value)
        {
            this.X = this.Y = (Half)value;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SlimMath.Half2"/> struct.
        /// </summary>
        /// <param name="values">The values to assign to the X and Y components of the vector. This must be an array with two elements.</param>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="values"/> is <c>null</c>.</exception>
        /// <exception cref="ArgumentOutOfRangeException">Thrown when <paramref name="values"/> contains more or less than two elements.</exception>
        public Half2(float[] values)
        {
            if (values == null)
                throw new ArgumentNullException("values");
            if (values.Length != 2)
                throw new ArgumentOutOfRangeException("values", "There must be two and only two input values for Half2.");

            X = (Half)values[0];
            Y = (Half)values[1];
        }

        /// <summary>
        /// Creates an array containing the elements of the vector.
        /// </summary>
        /// <returns>A two-element array containing the components of the vector.</returns>
        public Half[] ToArray()
        {
            return new Half[] { X, Y };
        }

        /// <summary>
        /// Tests for equality between two objects.
        /// </summary>
        /// <param name="left">The first value to compare.</param>
        /// <param name="right">The second value to compare.</param>
        /// <returns>
        /// <c>true</c> if <paramref name="left"/> has the same value as <paramref name="right"/>; otherwise, <c>false</c>.</returns>
        public static bool operator ==(Half2 left, Half2 right)
        {
            return left.Equals(right);
        }

        /// <summary>
        /// Tests for inequality between two objects.
        /// </summary>
        /// <param name="left">The first value to compare.</param>
        /// <param name="right">The second value to compare.</param>
        /// <returns>
        /// <c>true</c> if <paramref name="left"/> has a different value than <paramref name="right"/>; otherwise, <c>false</c>.</returns>
        public static bool operator !=(Half2 left, Half2 right)
        {
            return !left.Equals(right);
        }

        /// <summary>
        /// Performs an explicit conversion from <see cref="T:SlimMath.Vector2"/> to <see cref="T:SlimMath.Half2"/>.
        /// </summary>
        /// <param name="value">The value to be converted.</param>
        /// <returns>The converted value.</returns>
        public static explicit operator Half2(Vector2 value)
        {
            return new Half2(value.X, value.Y);
        }

        /// <summary>
        /// Performs an implicit conversion from <see cref="T:SlimMath.Half2"/> to <see cref="T:SlimMath.Vector2"/>.
        /// </summary>
        /// <param name="value">The value to be converted.</param>
        /// <returns>The converted value.</returns>
        public static implicit operator Vector2(Half2 value)
        {
            return new Vector2(value.X, value.Y);
        }

        /// <summary>
        /// Returns a <see cref="System.String"/> that represents this instance.
        /// </summary>
        /// <returns>
        /// A <see cref="System.String"/> that represents this instance.
        /// </returns>
        public override string ToString()
        {
            return string.Format(CultureInfo.CurrentCulture, "X:{0} Y:{1}", X, Y);
        }

        /// <summary>
        /// Returns a <see cref="System.String"/> that represents this instance.
        /// </summary>
        /// <param name="format">The format.</param>
        /// <returns>
        /// A <see cref="System.String"/> that represents this instance.
        /// </returns>
        public string ToString(string format)
        {
            if (format == null)
                return ToString();

            return string.Format(CultureInfo.CurrentCulture, "X:{0} Y:{1}", X.ToString(format, CultureInfo.CurrentCulture), Y.ToString(format, CultureInfo.CurrentCulture));
        }

        /// <summary>
        /// Returns a <see cref="System.String"/> that represents this instance.
        /// </summary>
        /// <param name="formatProvider">The format provider.</param>
        /// <returns>
        /// A <see cref="System.String"/> that represents this instance.
        /// </returns>
        public string ToString(IFormatProvider formatProvider)
        {
            return string.Format(formatProvider, "X:{0} Y:{1}", X, Y);
        }

        /// <summary>
        /// Returns a <see cref="System.String"/> that represents this instance.
        /// </summary>
        /// <param name="format">The format.</param>
        /// <param name="formatProvider">The format provider.</param>
        /// <returns>
        /// A <see cref="System.String"/> that represents this instance.
        /// </returns>
        public string ToString(string format, IFormatProvider formatProvider)
        {
            if (format == null)
                ToString(formatProvider);

            return string.Format(formatProvider, "X:{0} Y:{1}", X.ToString(format, formatProvider), Y.ToString(format, formatProvider));
        }

        /// <summary>
        /// Returns the hash code for this instance.
        /// </summary>
        /// <returns>A 32-bit signed integer hash code.</returns>
        public override int GetHashCode()
        {
            return X.GetHashCode() + Y.GetHashCode();
        }

        /// <summary>
        /// Determines whether the specified object instances are considered equal. 
        /// </summary>
        /// <param name="value1"/>
        /// <param name="value2"/>
        /// <returns>
        /// <c>true</c> if <paramref name="value1"/> is the same instance as <paramref name="value2"/> or 
        /// if both are <c>null</c> references or if <c>value1.Equals(value2)</c> returns <c>true</c>; otherwise, <c>false</c>.</returns>
        public static bool Equals(ref Half2 value1, ref Half2 value2)
        {
            return (value1.X == value2.X) && (value1.Y == value2.Y);
        }

        /// <summary>
        /// Returns a value that indicates whether the current instance is equal to the specified object. 
        /// </summary>
        /// <param name="other">Object to make the comparison with.</param>
        /// <returns>
        /// <c>true</c> if the current instance is equal to the specified object; <c>false</c> otherwise.</returns>
        public bool Equals(Half2 other)
        {
            return (this.X == other.X) && (this.Y == other.Y);
        }

        /// <summary>
        /// Returns a value that indicates whether the current instance is equal to a specified object. 
        /// </summary>
        /// <param name="obj">Object to make the comparison with.</param>
        /// <returns>
        /// <c>true</c> if the current instance is equal to the specified object; <c>false</c> otherwise.</returns>
        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;

            if (obj.GetType() != GetType())
                return false;

            return Equals((Half2)obj);
        }
    }
}
