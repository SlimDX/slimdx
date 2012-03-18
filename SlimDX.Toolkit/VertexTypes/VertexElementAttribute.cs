using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.DXGI;
using SlimDX.Direct3D11;

namespace SlimDX.Toolkit
{
    /// <summary>
    /// Describes the usage and format of an element in a vertex structure.
    /// </summary>
    [AttributeUsage(AttributeTargets.Field, AllowMultiple = false)]
    public sealed class VertexElementAttribute : Attribute
    {
        /// <summary>
        /// The HLSL semantic associated with this element in a shader input-signature.
        /// </summary>
        public string Semantic
        {
            get;
            private set;
        }

        /// <summary>
        /// The data type of the element data.
        /// </summary>
        public Format Format
        {
            get;
            private set;
        }

        /// <summary>
        /// The semantic index for the element. A semantic index modifies a semantic, with an integer index number. A semantic index is only needed in a 
        /// case where there is more than one element with the same semantic. For example, a 4x4 matrix would have four components each with the semantic
        /// name matrix, however each of the four component would have different semantic indices (0, 1, 2, and 3).
        /// </summary>
        public int SemanticIndex
        {
            get;
            set;
        }

        /// <summary>
        /// An integer value that identifies the input-assembler. Valid values are between 0 and 15.
        /// </summary>
        public int Slot
        {
            get;
            set;
        }

        /// <summary>
        /// Identifies the input data class for a single input slot.
        /// </summary>
        public InputClassification Classification
        {
            get;
            set;
        }

        /// <summary>
        /// The number of instances to draw using the same per-instance data before advancing in the buffer by one element. 
        /// This value must be 0 for an element that contains per-vertex data.
        /// </summary>
        public int InstanceDataStepRate
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="VertexElementAttribute"/> class.
        /// </summary>
        /// <param name="semantic">The HLSL semantic.</param>
        public VertexElementAttribute(string semantic)
            : this(semantic, Format.Unknown)
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="VertexElementAttribute"/> class.
        /// </summary>
        /// <param name="semantic">The HLSL semantic.</param>
        /// <param name="format">Format of the element data.</param>
        public VertexElementAttribute(string semantic, Format format)
        {
            Semantic = semantic;
            Format = format;
            Classification = InputClassification.PerVertexData;
        }
    }
}
