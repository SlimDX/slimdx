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
using System;
using SlimDX;
using SlimDX.Direct3D9;

namespace Water
{
    class Entity : IDisposable
    {
        Mesh mesh;
        Texture texture;
        Effect effect;

        Matrix worldMatrix = Matrix.Identity;
        Matrix viewMatrix = Matrix.Identity;
        Matrix projectionMatrix = Matrix.Identity;

        protected Mesh Mesh
        {
            get { return mesh; }
        }

        protected Texture Texture
        {
            get { return texture; }
        }

        protected Effect Effect
        {
            get { return effect; }
        }

        protected Matrix WorldMatrix
        {
            get { return worldMatrix; }
        }

        protected Matrix ViewMatrix
        {
            get { return viewMatrix; }
        }

        protected Matrix ProjectionMatrix
        {
            get { return projectionMatrix; }
        }

        public Entity(Device device, string meshFileName, string effectFileName, string textureFileName)
        {
            mesh = Mesh.FromFile(device, meshFileName, MeshFlags.Managed);

            VertexElement[] elements = new VertexElement[]
            {
                new VertexElement(0, 0, DeclarationType.Float3, DeclarationMethod.Default, DeclarationUsage.Position, 0),
				new VertexElement(0, 12, DeclarationType.Float3, DeclarationMethod.Default, DeclarationUsage.Normal, 0),
				new VertexElement(0, 24, DeclarationType.Float3, DeclarationMethod.Default, DeclarationUsage.TextureCoordinate, 0),
				new VertexElement(0, 36, DeclarationType.Float3, DeclarationMethod.Default, DeclarationUsage.Tangent, 0),
				new VertexElement(0, 48, DeclarationType.Float3, DeclarationMethod.Default, DeclarationUsage.Binormal, 0),
				VertexElement.VertexDeclarationEnd
            };

            Mesh tempMesh = mesh.Clone(device, MeshFlags.Managed, elements);
            mesh.Dispose();
            mesh = tempMesh;

            mesh.ComputeTangentFrame(TangentOptions.None);

            effect = Effect.FromFile(device, effectFileName, ShaderFlags.Debug | ShaderFlags.PartialPrecision);
            texture = Texture.FromFile(device, textureFileName);
        }

        public void Update(Vector3 position, Matrix viewMatrix, Matrix projectionMatrix)
        {
            worldMatrix = Matrix.Translation(position);

            this.viewMatrix = viewMatrix;
            this.projectionMatrix = projectionMatrix;
        }

        public virtual void Render(Device device)
        {
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                mesh.Dispose();
                texture.Dispose();
                effect.Dispose();
            }
        }
    }
}
