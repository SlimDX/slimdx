/*
* Copyright (c) 2007-2008 SlimDX Group
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
using System.Runtime.InteropServices;
using SampleFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace Asteroids
{
    /// <summary>
    /// Defines a vertex for particle systems.
    /// </summary>
    struct ParticleVertex
    {
        /// <summary>
        /// Gets or sets the position.
        /// </summary>
        /// <value>The position.</value>
        [VertexElement(DeclarationType.Float3, DeclarationUsage.Position)]
        public Vector3 Position
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the velocity.
        /// </summary>
        /// <value>The velocity.</value>
        [VertexElement(DeclarationType.Float3, DeclarationUsage.Normal)]
        public Vector3 Velocity
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the appearance settings.
        /// </summary>
        /// <value>The appearance settings.</value>
        [VertexElement(DeclarationType.Float4, DeclarationUsage.Color)]
        public Vector4 Appearance
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the time that the particle was created.
        /// </summary>
        /// <value>The time that the particle was created.</value>
        [VertexElement(DeclarationType.Float1, DeclarationUsage.TextureCoordinate)]
        public float Time
        {
            get;
            set;
        }

        /// <summary>
        /// Gets the size, in bytes, of the <see cref="ParticleVertex"/> structure.
        /// </summary>
        /// <value>The size in bytes.</value>
        public static int SizeInBytes
        {
            get { return Marshal.SizeOf(typeof(ParticleVertex)); }
        }
    }
}
