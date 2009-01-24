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
    class WaterEntity : Entity
    {
        CubeTexture cubeTexture;
        float waterTime;

        public WaterEntity(Device device, string meshFileName, string effectFileName, string textureFileName, string cubeTextureFileName)
            : base(device, meshFileName, effectFileName, textureFileName)
        {
            cubeTexture = CubeTexture.FromFile(device, cubeTextureFileName);
        }

        public override void Render(Device device)
        {
            Matrix modelViewProjection = WorldMatrix * ViewMatrix * ProjectionMatrix;

            Effect.Technique = "water";

            Effect.SetTexture("texture0", Texture);
            Effect.SetTexture("texture1", cubeTexture);

            Effect.SetValue("ModelViewProj", modelViewProjection);
            Effect.SetValue("ModelWorld", WorldMatrix);

            Effect.SetValue("eyePos", new Vector4(450.0f, 250.0f, 750.0f, 1.0f));

            float time = Environment.TickCount * 0.001f;
            Effect.SetValue("lightPos", new Vector4((float)(300 * Math.Sin(time)), 40.0f, (float)(300 * Math.Cos(time)), 1.0f));

            waterTime += 0.002f;
            Effect.SetValue("time", waterTime);

            device.SetRenderState(RenderState.AlphaBlendEnable, true);
            Effect.Begin(FX.None);
            Effect.BeginPass(0);

            Mesh.DrawSubset(0);

            Effect.EndPass();
            Effect.End();
            device.SetRenderState(RenderState.AlphaBlendEnable, false);
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                cubeTexture.Dispose();
            }

            base.Dispose(disposing);
        }
    }
}
