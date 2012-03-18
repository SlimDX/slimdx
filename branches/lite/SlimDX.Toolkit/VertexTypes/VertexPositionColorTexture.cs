using System;
using System.Globalization;
using System.Runtime.InteropServices;
using SlimMath;

namespace SlimDX.Toolkit.VertexTypes
{
    /// <summary>
    /// Represents a vertex that has a position, color, and texture mapping information.
    /// </summary>
    [Serializable]
    public struct VertexPositionColorTexture : IEquatable<VertexPositionColorTexture>
    {
        /// <summary>
        /// The size of the structure, in bytes.
        /// </summary>
        public static readonly int SizeInBytes = Marshal.SizeOf(typeof(VertexPositionColorTexture));

        /// <summary>
        /// The position of the vertex.
        /// </summary>
        [VertexElement("SV_Position")]
        public Vector3 Position;

        /// <summary>
        /// The color of the vertex.
        /// </summary>
        [VertexElement("COLOR")]
        public Color4 Color;

        /// <summary>
        /// The texture coordinates.
        /// </summary>
        [VertexElement("TEXCOORD")]
        public Vector2 TextureCoordinates;

        /// <summary>
        /// Initializes a new instance of the <see cref="VertexPositionColorTexture"/> struct.
        /// </summary>
        /// <param name="position">The position.</param>
        /// <param name="color">The color.</param>
        /// <param name="textureCoordinates">The texture coordinates.</param>
        public VertexPositionColorTexture(Vector3 position, Color4 color, Vector2 textureCoordinates)
        {
            Position = position;
            Color = color;
            TextureCoordinates = textureCoordinates;
        }

        /// <summary>
        /// Implements operator ==.
        /// </summary>
        /// <param name="left">The left side of the operator.</param>
        /// <param name="right">The right side of the operator.</param>
        /// <returns>The result of the operator.</returns>
        public static bool operator ==(VertexPositionColorTexture left, VertexPositionColorTexture right)
        {
            return left.Equals(right);
        }

        /// <summary>
        /// Implements operator !=.
        /// </summary>
        /// <param name="left">The left side of the operator.</param>
        /// <param name="right">The right side of the operator.</param>
        /// <returns>The result of the operator.</returns>
        public static bool operator !=(VertexPositionColorTexture left, VertexPositionColorTexture right)
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
            return string.Format(CultureInfo.CurrentCulture, "Position={0}, Color={1}, TexCoords={2}", Position, Color, TextureCoordinates);
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
                + Color.GetHashCode()
                + TextureCoordinates.GetHashCode();
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

            return Equals((VertexPositionColorTexture)obj);
        }

        /// <summary>
        /// Indicates whether the current object is equal to another object of the same type.
        /// </summary>
        /// <param name="other">An object to compare with this object.</param>
        /// <returns>
        /// <c>true</c> if the current object is equal to the <paramref name="other"/> parameter; otherwise, <c>false</c>.
        /// </returns>
        public bool Equals(VertexPositionColorTexture other)
        {
            return
                Position == other.Position &&
                Color == other.Color &&
                TextureCoordinates == other.TextureCoordinates;
        }
    }
}
