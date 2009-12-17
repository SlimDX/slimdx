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

using System.Drawing;
using System.Runtime.InteropServices;

using SlimDX;
using SlimDX.Direct3D10;

using SlimDX.SampleFramework;

namespace SimpleTriangle10 {
    /// <summary>
    /// Demonstrates how to render a simple colored triangle with Direct3D10.
    /// </summary>
    class SimpleTriangle10Sample : Sample {
        /// <summary>
        /// Disposes of object resources.
        /// </summary>
        /// <param name="disposeManagedResources">If true, managed resources should be
        /// disposed of in addition to unmanaged resources.</param>
        protected override void Dispose(bool disposeManagedResources) {
            if (disposeManagedResources) {
                effect.Dispose();
                inputLayout.Dispose();
                renderTargetView.Dispose();
                vertexBuffer.Dispose();
            }

            base.Dispose(disposeManagedResources);
        }

        /// <summary>
        /// In a derived class, implements logic to initialize the sample.
        /// </summary>
        protected override void OnInitialize() {
            DeviceSettings10 settings = new DeviceSettings10 {
                AdapterOrdinal = 0,
                CreationFlags = DeviceCreationFlags.None,
                Width = WindowWidth,
                Height = WindowHeight
            };

            context = InitializeDevice(settings);
            using (Texture2D texture = Texture2D.FromSwapChain<Texture2D>(context.SwapChain, 0)) {
                renderTargetView = new RenderTargetView(context.Device, texture);
            }

            effect = Effect.FromFile(context.Device, "SimpleTriangle10.fx", "fx_4_0", ShaderFlags.None, EffectFlags.None, null, null);
            technique = effect.GetTechniqueByIndex(0);
            pass = technique.GetPassByIndex(0);

            ShaderSignature signature = pass.Description.Signature;
            inputLayout = new InputLayout(context.Device, signature, new[] {
				new InputElement("POSITION", 0, SlimDX.DXGI.Format.R32G32B32A32_Float, 0, 0),
                new InputElement("COLOR", 0, SlimDX.DXGI.Format.R32G32B32A32_Float, 16, 0) 
			});
            signature.Dispose();

            vertexBuffer = new Buffer(
                context.Device,
                3 * 32,
                ResourceUsage.Dynamic,
                BindFlags.VertexBuffer,
                CpuAccessFlags.Write,
                ResourceOptionFlags.None
            );

            DataStream stream = vertexBuffer.Map(MapMode.WriteDiscard, MapFlags.None);
            stream.WriteRange(new[] {
				new Vector4(0.0f, 0.5f, 0.5f, 1.0f), new Vector4(1.0f, 0.0f, 0.0f, 1.0f),
				new Vector4(0.5f, -0.5f, 0.5f, 1.0f), new Vector4(0.0f, 1.0f, 0.0f, 1.0f),
				new Vector4(-0.5f, -0.5f, 0.5f, 1.0f), new Vector4(0.0f, 0.0f, 1.0f, 1.0f)
			});
            vertexBuffer.Unmap();
        }

        protected override void OnRenderBegin() {
            context.Device.OutputMerger.SetTargets(renderTargetView);
            context.Device.Rasterizer.SetViewports(new Viewport(0, 0, WindowWidth, WindowHeight, 0.0f, 1.0f));
            context.Device.ClearRenderTargetView(renderTargetView, new Color4(0.3f, 0.3f, 0.3f));
        }

        protected override void OnRender() {
            context.Device.InputAssembler.SetInputLayout(inputLayout);
            context.Device.InputAssembler.SetPrimitiveTopology(SlimDX.Direct3D10.PrimitiveTopology.TriangleList);
            context.Device.InputAssembler.SetVertexBuffers(0, new VertexBufferBinding(vertexBuffer, 32, 0));

            pass.Apply();
            context.Device.Draw(3, 0);
        }

        protected override void OnRenderEnd() {
            context.SwapChain.Present(0, SlimDX.DXGI.PresentFlags.None);
        }

        #region Implementation Detail

        DeviceContext10 context;
        RenderTargetView renderTargetView;
        Effect effect;
        EffectTechnique technique;
        EffectPass pass;
        InputLayout inputLayout;
        Buffer vertexBuffer;

        #endregion
    }
}
