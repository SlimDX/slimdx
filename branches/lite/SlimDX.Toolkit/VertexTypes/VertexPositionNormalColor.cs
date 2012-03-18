using System;
using System.Globalization;
using System.Runtime.InteropServices;
using SlimMath;

namespace SlimDX.Toolkit.VertexTypes
{
    /// <summary>
    /// Represents a vertex that has a position, normal vector, and color.
    /// </summary>
    [Serializable]
    public struct VertexPositionNormalColor : IEquatable<VertexPositionNormalColor>
    {
        /// <summary>
        /// The size of the structure, in bytes.
        /// </summary>
        public static readonly int SizeInBytes = Marshal.SizeOf(typeof(VertexPositionNormalColor));

        /// <summary>
        /// The position of the vertex.
        /// </summary>
        [VertexElement("SV_Position")]
        public Vector3 Position;

        /// <summary>
        /// The vertex normal.
        /// </summary>
        [VertexElement("NORMAL")]
        public Vector3 Normal;

        /// <summary>
        /// The color of the vertex.
        /// </summary>
        [VertexElement("COLOR")]
        public Color4 Color;

        /// <summary>
        /// Initializes a new instance of the <see cref="VertexPositionNormalColor"/> struct.
        /// </summary>
        /// <param name="position">The position.</param>
        /// <param name="normal">The normal.</param>
        /// <param name="color">The color.</param>
        public VertexPositionNormalColor(Vector3 position, Vector3 normal, Color4 color)
        {
            Position = position;
            Normal = normal;
            Color = color;
        }

        /// <summary>
        /// Implements operator ==.
        /// </summary>
        /// <param name="left">The left side of the operator.</param>
        /// <param name="right">The right side of the operator.</param>
        /// <returns>The result of the operator.</returns>
        public static bool operator ==(VertexPositionNormalColor left, VertexPositionNormalColor right)
        {
            return left.Equals(right);
        }

        /// <summary>
        /// Implements operator !=.
        /// </summary>
        /// <param name="left">The left side of the operator.</param>
        /// <param name="right">The right side of the operator.</param>
        /// <returns>The result of the operator.</returns>
        public static bool operator !=(VertexPositionNormalColor left, VertexPositionNormalColor right)
        {
            return !(left == right);
        }

        /// <summary>
        /// Returns a <see cref="System.String"/> that represents this instance.
        /// </summary>
        /// <returns>
        /// A <see cref="System.String"/> that represents this instance.
        /// </returns>
        public override string ToString()
        {
            return string.Format(CultureInfo.CurrentCulture, "Position={0}, Normal={1}, Color={2}", Position, Normal, Color);
        }

        /// <summary>
        /// Returns the hash code for this instance.
        /// </summary>
        /// <returns>
        /// A 32-bit signed integer that is the hash code for this instance.
        /// </returns>
        public override int GetHashCode()
        {
            return Position.GetHashCode()
                + Normal.GetHashCode()
                + Color.GetHashCode();
        }

        /// <summary>
        /// Indicates whether this instance and a specified object are equal.
        /// </summary>
        /// <param name="obj">Another object to compare to.</param>
        /// <returns>
        /// <c>true</c> if <paramref name="obj"/> and this instance are the same type and represent the same value; otherwise, <c>false</c>.
        /// </returns>
        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;

            if (GetType() != obj.GetType())
                return false;

            return Equals((VertexPositionNormalColor)obj);
        }

        /// <summary>
        /// Indicates whether the current object is equal to another object of the same type.
        /// </summary>
        /// <param name="other">An object to compare with this object.</param>
        /// <returns>
        /// <c>true</c> if the current object is equal to the <paramref name="other"/> parameter; otherwise, <c>false</c>.
        /// </returns>
        public bool Equals(VertexPositionNormalColor other)
        {
            return
                Position == other.Position &&
                Normal == other.Normal &&
                Color == other.Color;
        }
    }
}
