using SlimDX.Direct3D9;

namespace Interface
{
    /// <summary>
    /// Represents a screen vertex.
    /// </summary>
    struct ScreenVertex
    {
        #region Fields

        /// <summary>
        /// The X position.
        /// </summary>
        public float X;

        /// <summary>
        /// The Y position.
        /// </summary>
        public float Y;

        /// <summary>
        /// The Z position.
        /// </summary>
        public float Z;

        /// <summary>
        /// The W position.
        /// </summary>
        public float W;

        /// <summary>
        /// The vertex color.
        /// </summary>
        public int Color;

        /// <summary>
        /// The texture U coordinate.
        /// </summary>
        public float U;

        /// <summary>
        /// The texture V coordinate.
        /// </summary>
        public float V;

        #endregion

        #region Properties

        /// <summary>
        /// Gets the flexible vertex format.
        /// </summary>
        /// <value>The vertex format.</value>
        public static VertexFormat Format
        {
            get { return VertexFormat.PositionRhw | VertexFormat.Diffuse | VertexFormat.Texture1; }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="ScreenVertex"/> struct.
        /// </summary>
        /// <param name="x">The X position.</param>
        /// <param name="y">The y position.</param>
        /// <param name="z">The Z position.</param>
        /// <param name="w">The W position.</param>
        /// <param name="color">The color.</param>
        /// <param name="u">The texture U coordinate.</param>
        /// <param name="v">The texture V coordinate.</param>
        public ScreenVertex(float x, float y, float z, float w, int color, float u, float v)
        {
            // store variables
            X = x;
            Y = y;
            Z = z;
            W = w;
            Color = color;
            U = u;
            V = v;
        }

        #endregion
    }
}
