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
using SlimDX.Direct3D10;
using SlimDX.DXGI;
using SlimDX.SampleFramework;
using Resource=SlimDX.Direct3D10.Resource;

namespace SimpleModel10 {
    class SimpleModel10Sample : Sample {
        protected override void Dispose(bool disposeManagedResources) {
            if(disposeManagedResources) {
                jupiterTexture.Dispose();
                jupiterMesh.Dispose();
                effect.Dispose();
                renderTargetView.Dispose();
            }

            base.Dispose(disposeManagedResources);
        }

        protected override void OnInitialize() {
            var settings10 = new DeviceSettings10() {
                AdapterOrdinal = 0,
                CreationFlags = DeviceCreationFlags.None,
                Width = WindowWidth,
                Height = WindowHeight
            };

            InitializeDevice(settings10);

            using(var swapChainBuffer = Resource.FromSwapChain<Texture2D>(Context10.SwapChain, 0)) {
                renderTargetView = new RenderTargetView(Context10.Device, swapChainBuffer);
            }

            InputElement[] elements;
            using(var meshLoader = new XLoader()) {
                jupiterMesh = meshLoader.LoadFile(Context10.Device, "jupiter.X", out elements);
            }

            jupiterTexture = Texture2D.FromFile(Context10.Device, "jupiter.jpg");

            string compilationErrors;
            effect = Effect.FromFile(Context10.Device, "SimpleModel10.fx", "fx_4_0", ShaderFlags.None, EffectFlags.None, null, null, out compilationErrors);
            technique = effect.GetTechniqueByIndex(0);
            pass = technique.GetPassByIndex(0);

            var signature = pass.Description.Signature;
            layout = new InputLayout(Context10.Device, signature, elements);

            proj = Matrix.PerspectiveFovLH(45.0f, (float) WindowWidth/(float) WindowHeight, 1.0f, 1000.0f);
            view = Matrix.LookAtLH(new Vector3(0, 0, 160), new Vector3(0, 0, -128.0f), Vector3.UnitY);
            var world = Matrix.Identity; 

            effect.GetVariableByName("jupiterTexture").AsResource().SetResource(new ShaderResourceView(Context10.Device, jupiterTexture));
            effect.GetVariableByName("view").AsMatrix().SetMatrix(view);
            effect.GetVariableByName("proj").AsMatrix().SetMatrix(proj);
        }

        protected override void OnResize() {
            Context10.Device.ClearState();
            renderTargetView.Dispose();

            Context10.SwapChain.ResizeBuffers(1, WindowWidth, WindowHeight, Format.R8G8B8A8_UNorm, SwapChainFlags.AllowModeSwitch);
            using (var texture = Resource.FromSwapChain<Texture2D>(Context10.SwapChain, 0)) {
                renderTargetView = new RenderTargetView(Context10.Device, texture);
            }

            proj = Matrix.PerspectiveFovLH(45.0f, (float)WindowWidth / (float)WindowHeight, 1.0f, 1000.0f);
            effect.GetVariableByName("proj").AsMatrix().SetMatrix(proj);
        }

        protected override void OnRenderBegin() {
            Context10.Device.OutputMerger.SetTargets(renderTargetView);
            Context10.Device.Rasterizer.SetViewports(new Viewport(0, 0, WindowWidth, WindowHeight, 0.0f, 1.0f));
            Context10.Device.ClearRenderTargetView(renderTargetView, new Color4(0.0f, 0.0f, 0.0f));
        }

        protected override void OnRender() {
            rotation += (float)(Math.PI / 4.0f * FrameDelta);

            if (rotation > 2 * Math.PI)
                rotation = 0;

            Matrix rotationMatrix;
            Matrix.RotationY(rotation, out rotationMatrix);
            var world = Matrix.Identity;
            Matrix.Multiply(ref world, ref rotationMatrix, out world);

            effect.GetVariableByName("world").AsMatrix().SetMatrix(world);

            Context10.Device.InputAssembler.SetInputLayout(layout);
            pass.Apply();
            jupiterMesh.DrawSubset(0);
        }

        protected override void OnRenderEnd() {
            Context10.SwapChain.Present(0, PresentFlags.None);
        }

        #region Implementation Detail
        private RenderTargetView renderTargetView;
        private Mesh jupiterMesh;
        private Texture2D jupiterTexture;
        private Effect effect;
        private EffectTechnique technique;
        private EffectPass pass;
        private Matrix view;
        private Matrix proj;
        private InputLayout layout;
        private float rotation;
        #endregion
    }
}
