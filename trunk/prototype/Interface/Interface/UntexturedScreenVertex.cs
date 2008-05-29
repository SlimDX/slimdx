using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.Direct3D9;

namespace Interface
{
    /// <summary>
    /// Represents an untextured screen vertex.
    /// </summary>
    struct UntexturedScreenVertex
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

        #endregion

        #region Properties

        /// <summary>
        /// Gets the flexible vertex format.
        /// </summary>
        /// <value>The vertex format.</value>
        public static VertexFormat Format
        {
            get { return VertexFormat.PositionRhw | VertexFormat.Diffuse; }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="UntexturedScreenVertex"/> struct.
        /// </summary>
        /// <param name="x">The X position.</param>
        /// <param name="y">The y position.</param>
        /// <param name="z">The Z position.</param>
        /// <param name="w">The W position.</param>
        /// <param name="color">The color.</param>
        public UntexturedScreenVertex(float x, float y, float z, float w, int color)
        {
            // store variables
            X = x;
            Y = y;
            Z = z;
            W = w;
            Color = color;
        }

        #endregion
    }
}
