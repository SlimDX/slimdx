/* Copyright (c) 2007-2010 SlimDX Group
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
using System.Drawing;

namespace SlimDX.Direct3D10 {
    [InterfaceID( "9B7E4C0F-342C-4106-A19F-4F2704F689F0" )]
    public interface IDevice : IComObject {
        IRenderTargetView CreateRenderTargetView( IResource resource );
        IBuffer CreateBuffer<T>(BufferDescription bufferDescription, T[] bufferData) where T : struct;
        IBuffer CreateEmptyBuffer(BufferDescription bufferDescription);
        IInputLayout CreateInputLayout(InputElement[] elements, ShaderSignature signature);

        void ClearRenderTargetView(IRenderTargetView renderTargetView, Color clearColor);

        void IASetPrimitiveTopology(PrimitiveTopology primitiveTopology);
        void IASetVertexBuffer(int startSlot, VertexBufferBinding vertexBufferBinding);
        void IASetVertexBuffers(int startSlot, VertexBufferBinding[] vertexBufferBindings);
        void IASetInputLayout(IInputLayout inputLayout);

        void RSSetViewport(Viewport viewport);
        void RSSetViewports(Viewport[] viewports);

        void OMSetRenderTargets(IRenderTargetView[] renderTargetViews, IDepthStencilView depthStencilView);
        void OMSetRenderTarget(IRenderTargetView renderTargetView, IDepthStencilView depthStencilView);

        void Draw(int vertexCount, int startLocation);
    }
}
