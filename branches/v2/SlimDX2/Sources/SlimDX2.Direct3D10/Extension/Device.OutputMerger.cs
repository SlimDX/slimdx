// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

namespace SlimDX2.Direct3D10
{
    public partial class Device
    {
        public partial class OutputMergerStage
        {
            /// <summary>
            ///   Binds a set of render targets to the output-merger stage.
            /// </summary>
            /// <param name = "renderTargetViews">A set of render target views to bind.</param>
            public void SetTargets(params RenderTargetView[] renderTargetViews)
            {
                SetTargets((DepthStencilView) null, renderTargetViews);
            }

            /// <summary>
            ///   Binds a single render target to the output-merger stage.
            /// </summary>
            /// <param name = "renderTargetView">A view of the render target to bind.</param>
            public void SetTargets(RenderTargetView renderTargetView)
            {
                SetTargets((DepthStencilView) null, renderTargetView);
            }

            /// <summary>
            ///   Binds a depth-stencil buffer and a set of render targets to the output-merger stage.
            /// </summary>
            /// <param name = "depthStencilView">A view of the depth-stencil buffer to bind.</param>
            /// <param name = "renderTargetViews">A set of render target views to bind.</param>
            public void SetTargets(DepthStencilView depthStencilView, params RenderTargetView[] renderTargetViews)
            {
                SetRenderTargets(renderTargetViews.Length, renderTargetViews, depthStencilView);
            }

            /// <summary>
            ///   Binds a depth-stencil buffer and a single render target to the output-merger stage.
            /// </summary>
            /// <param name = "depthStencilView">A view of the depth-stencil buffer to bind.</param>
            /// <param name = "renderTargetView">A view of the render target to bind.</param>
            public void SetTargets(DepthStencilView depthStencilView, RenderTargetView renderTargetView)
            {
                SetTargets(depthStencilView, new[] {renderTargetView});
            }
        }
    }
}