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
    public interface IDevice10 : IComObject {
        IRenderTargetView10 CreateRenderTargetView( IResource10 resource );
        IBuffer10 CreateBuffer<T>(BufferDescription10 bufferDescription10, T[] bufferData) where T : struct;
        IBuffer10 CreateEmptyBuffer(BufferDescription10 bufferDescription10);

        void ClearRenderTargetView(IRenderTargetView10 renderTargetView, Color clearColor);

        void IASetPrimitiveTopology(PrimitiveTopology10 primitiveTopology);
        void IASetVertexBuffer(int startSlot, VertexBufferBinding10 vertexBufferBinding);
        void IASetVertexBuffers(int startSlot, VertexBufferBinding10[] vertexBufferBindings);

        void RSSetViewport(Viewport10 viewport);
        void RSSetViewports(Viewport10[] viewports);

        void OMSetRenderTargets(IRenderTargetView10[] renderTargetViews, IDepthStencilView10 depthStencilView);
        void OMSetRenderTarget(IRenderTargetView10 renderTargetView, IDepthStencilView10 depthStencilView);
    }
}
