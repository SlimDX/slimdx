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
using System.Collections.Generic;

namespace Asteroids
{
    /// <summary>
    /// Assists in remapping vector model vertices into a range suitable for rendering.
    /// </summary>
    class VertexRemapper
    {
        // variables
        Dictionary<VectorModelVertex, ushort> remap = new Dictionary<VectorModelVertex, ushort>();
        List<VectorModelVertex> vertices = new List<VectorModelVertex>();

        /// <summary>
        /// Gets the vertices.
        /// </summary>
        /// <value>The vertices.</value>
        public List<VectorModelVertex> Vertices
        {
            get { return vertices; }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="VertexRemapper"/> class.
        /// </summary>
        public VertexRemapper()
        {
        }

        /// <summary>
        /// Retrieves the correct index for the specified vertex.
        /// </summary>
        /// <param name="vertex">The vertex.</param>
        /// <returns>The correct index into the vertex buffer.</returns>
        public ushort GetIndex(VectorModelVertex vertex)
        {
            // check if we already have this vertex
            if (!remap.ContainsKey(vertex))
            {
                // add the vertex to both collections
                remap.Add(vertex, (ushort)Vertices.Count);
                Vertices.Add(vertex);
            }

            // return the index
            return remap[vertex];
        }
    }
}
