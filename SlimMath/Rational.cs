using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace SlimMath
{
    /// <summary>
    /// Defines a rational number as a numerator / denominator pair.
    /// </summary>
    [Serializable]
    [StructLayout(LayoutKind.Sequential)]
    public struct Rational : IEquatable<Rational>
    {
        public static readonly Rational Empty = new Rational(0, 0);

        /// <summary>
        /// Gets or sets the numerator of the rational pair.
        /// </summary>
        public int Numerator;
        
        /// <summary>
        /// Gets or sets the denominator of the rational pair.
        /// </summary>
        public int Denominator;

        /// <summary>
        /// Initializes a new instance of the <see cref="Rational"/> structure.
        /// </summary>
        /// <param name="numerator">The numerator of the rational pair.</param>
        /// <param name="denominator">The denominator of the rational pair.</param>
        public Rational(int numerator, int denominator)
        {
            Numerator = numerator;
            Denominator = denominator;
        }

        /// <summary>
        /// Performs an explicit conversion from <see cref="Rational"/> to <see cref="Single" />.
        /// </summary>
        /// <param name="value">The value to be converted.</param>
        /// <returns>The converted value.</returns> 
        public static explicit operator float(Rational value)
        {
            return (float)value.Numerator / (float)value.Denominator;
        }

        /// <summary>
        /// Tests for equality between two objects.
        /// </summary>
        /// <param name="left">The first value to compare.</param>
        /// <param name="right">The second value to compare.</param>
        /// <returns><c>true</c> if <paramref name="left"/> has the same value as <paramref name="right"/>; otherwise, <c>false</c>.</returns>
        public static bool operator ==(Rational left, Rational right)
        {
            return left.Equals(right);
        }

        /// <summary>
        /// Tests for inequality between two objects.
        /// </summary>
        /// <param name="left">The first value to compare.</param>
        /// <param name="right">The second value to compare.</param>
        /// <returns><c>true</c> if <paramref name="left"/> has a different value than <paramref name="right"/>; otherwise, <c>false</c>.</returns>
        public static bool operator !=(Rational left, Rational right)
        {
            return !left.Equals(right);
        }

        /// <summary>
        /// Returns a hash code for this instance.
        /// </summary>
        /// <returns>
        /// A hash code for this instance, suitable for use in hashing algorithms and data structures like a hash table. 
        /// </returns>
        public override int GetHashCode()
        {
            return Numerator.GetHashCode() + Denominator.GetHashCode();
        }

        /// <summary>
        /// Determines whether the specified <see cref="SlimMath.Rational"/> is equal to this instance.
        /// </summary>
        /// <param name="other">The <see cref="SlimMath.Rational"/> to compare with this instance.</param>
        /// <returns>
        /// <c>true</c> if the specified <see cref="SlimMath.Rational"/> is equal to this instance; otherwise, <c>false</c>.
        /// </returns>
        public bool Equals(Rational other)
        {
            return (this.Numerator == other.Numerator) && (this.Denominator == other.Denominator);
        }

        /// <summary>
        /// Determines whether the specified <see cref="System.Object"/> is equal to this instance.
        /// </summary>
        /// <param name="obj">The <see cref="System.Object"/> to compare with this instance.</param>
        /// <returns>
        /// <c>true</c> if the specified <see cref="System.Object"/> is equal to this instance; otherwise, <c>false</c>.
        /// </returns>
        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;

            if (obj.GetType() != GetType())
                return false;

            return Equals((Rational)obj);
        }
    }
}
