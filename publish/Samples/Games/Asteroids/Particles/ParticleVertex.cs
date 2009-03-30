/*
* Copyright (c) 2007-2009 SlimDX Group
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
    struct ParticleVertex
    {
        [VertexElement(DeclarationType.Float3, DeclarationUsage.Position)]
        public Vector3 Position
        {
            get;
            set;
        }

        [VertexElement(DeclarationType.Float3, DeclarationUsage.Normal)]
        public Vector3 Velocity
        {
            get;
            set;
        }

        [VertexElement(DeclarationType.Color, DeclarationUsage.Color)]
        public int Appearance
        {
            get;
            set;
        }

        [VertexElement(DeclarationType.Float1, DeclarationUsage.TextureCoordinate)]
        public float Time
        {
            get;
            set;
        }

        public static int SizeInBytes
        {
            get { return Marshal.SizeOf(typeof(ParticleVertex)); }
        }
    }
}
