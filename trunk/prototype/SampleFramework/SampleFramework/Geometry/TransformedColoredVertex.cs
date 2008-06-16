using System.Runtime.InteropServices;
using SlimDX;
using SlimDX.Direct3D9;

namespace SampleFramework
{
    /// <summary>
    /// Represents a single transformed and colored vertex.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct TransformedColoredVertex
    {
        /// <summary>
        /// The transformed position of the vertex.
        /// </summary>
        public Vector4 PositionRhw;

        /// <summary>
        /// The color of the vertex.
        /// </summary>
        public int Color;

        /// <summary>
        /// Gets the size in bytes.
        /// </summary>
        /// <value>The size in bytes.</value>
        public static int SizeInBytes
        {
            get { return Marshal.SizeOf(typeof(TransformedColoredVertex)); }
        }

        /// <summary>
        /// Gets the format.
        /// </summary>
        /// <value>The format.</value>
        public static VertexFormat Format
        {
            get { return VertexFormat.PositionRhw | VertexFormat.Diffuse; }
        }
    }
}
