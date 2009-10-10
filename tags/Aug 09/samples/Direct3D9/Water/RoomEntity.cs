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
using System;
using SlimDX;
using SlimDX.Direct3D9;

namespace Water
{
    class RoomEntity : Entity
    {
        Texture bumpTexture;

        public RoomEntity(Device device, string meshFileName, string effectFileName, string textureFileName, string bumpTextureFileName)
            : base(device, meshFileName, effectFileName, textureFileName)
        {
            bumpTexture = Texture.FromFile(device, bumpTextureFileName);
        }

        public override void Render(Device device)
        {
            Matrix modelViewProjection = WorldMatrix * ViewMatrix * ProjectionMatrix;
            Matrix inverted = Matrix.Transpose(Matrix.Invert(modelViewProjection));

            Effect.Technique = "bump";

            Effect.SetTexture("texture0", Texture);
            Effect.SetTexture("texture1", bumpTexture);

            Effect.SetValue("ModelViewProj", modelViewProjection);
            Effect.SetValue("ModelViewIT", inverted);
            Effect.SetValue("ModelWorld", WorldMatrix);

            float time = Environment.TickCount * 0.001f;
            Effect.SetValue("lightPos", new Vector4((float)(300 * Math.Sin(time)), 40.0f, (float)(300 * Math.Cos(time)), 1.0f));

            Effect.Begin(FX.None);
            Effect.BeginPass(0);

            Mesh.DrawSubset(0);

            Effect.EndPass();
            Effect.End();
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                bumpTexture.Dispose();
            }

            base.Dispose(disposing);
        }
    }
}
