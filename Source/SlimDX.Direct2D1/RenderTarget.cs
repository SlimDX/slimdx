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
using System;
using SlimDX.DXGI;

namespace SlimDX.Direct2D1
{
    public partial class RenderTarget
    {
        /// <summary>	
        /// Creates a render target that draws to a DirectX Graphics Infrastructure (DXGI) surface. 	
        /// </summary>	
        /// <remarks>	
        /// To write to a Direct3D surface, you obtain an <see cref="SlimDX.DXGI.Surface"/> and pass it to the {{CreateDxgiSurfaceRenderTarget}} method to create a DXGI surface render target; you can then use the DXGI surface render target to draw 2-D content to the DXGI surface.  A DXGI surface render target is a type of <see cref="SlimDX.Direct2D1.RenderTarget"/>. Like other Direct2D render targets, you can use it to create resources and issue drawing commands. The DXGI surface render target and the DXGI surface must use the same DXGI format. If you specify the {{DXGI_FORMAT_UNKOWN}} format when you create the render target, it will automatically use the surface's format.The DXGI surface render target does not perform DXGI surface synchronization. To work with Direct2D, the Direct3D device that provides the <see cref="SlimDX.DXGI.Surface"/> must be created with the D3D10_CREATE_DEVICE_BGRA_SUPPORT flag.For more information about creating and using DXGI surface render targets, see the {{Direct2D and Direct3D Interoperability Overview}}.When you create a render target and hardware acceleration is available, you allocate resources on the computer's GPU. By creating a render target once and retaining it as long as possible, you gain performance benefits. Your application should create render targets once and hold onto them for the life of the application or until the render target's {{EndDraw}} method returns the {{D2DERR_RECREATE_TARGET}} error. When you receive this error, you need to recreate the render target (and any resources it created). 	
        /// </remarks>	
        /// <param name="factory">an instance of <see cref = "SlimDX.Direct2D1.Factory" /></param>
        /// <param name="properties">The rendering mode, pixel format, remoting options, DPI information, and the minimum DirectX support required for hardware rendering. For information about supported pixel formats, see  {{Supported Pixel  Formats and Alpha Modes}}.</param>
        public RenderTarget(Factory factory, Surface dxgiSurface,  RenderTargetProperties properties)
            : base(IntPtr.Zero)
        {
            RenderTarget temp;
            factory.CreateDxgiSurfaceRenderTarget(dxgiSurface, ref properties, out temp);
            NativePointer = temp.NativePointer;
        }


        /// <summary>	
        /// Ends drawing operations  on the render target and indicates the current error state and associated tags. 	
        /// </summary>	
        /// <remarks>	
        /// Drawing operations can only be issued between a {{BeginDraw}} and EndDraw call.BeginDraw and EndDraw are use to indicate that a render target is in use by the Direct2D system. Different implementations of <see cref="SlimDX.Direct2D1.RenderTarget"/> might behave differently when {{BeginDraw}} is called. An <see cref="SlimDX.Direct2D1.BitmapRenderTarget"/> may be locked between BeginDraw/EndDraw calls, a DXGI surface render target might be acquired on BeginDraw and released on EndDraw, while an <see cref="SlimDX.Direct2D1.HwndRenderTarget"/> may begin batching at BeginDraw and may present on EndDraw, for example. The BeginDraw method must be called before rendering operations can be called, though state-setting and state-retrieval operations can be performed even outside of {{BeginDraw}}/EndDraw. After {{BeginDraw}} is called, a render target will normally build up a batch of rendering commands, but defer processing of these commands until either an internal buffer is full, the {{Flush}} method is called, or until EndDraw is called. The EndDraw method causes any batched drawing operations to complete, and then returns an HRESULT indicating the success of the operations and, optionally, the tag state of the render target at the time the error occurred. The EndDraw method always succeeds: it should not be called twice even if a previous EndDraw resulted in a failing HRESULT. If EndDraw is called without a matched call to {{BeginDraw}}, it returns an error indicating that BeginDraw must be called before EndDraw. Calling BeginDraw twice on a render target puts the target into an error state where nothing further is drawn, and returns an appropriate HRESULT and error information when EndDraw is called.	
        /// </remarks>	
        /// <returns>If the method succeeds, it returns S_OK. Otherwise, it returns an HRESULT error code and sets tag1 and tag2 to the tags that were active when the error occurred. </returns>
        public SlimDX.Result EndDraw()
        {
            long tag1;
            long tag2;
            return EndDraw(out tag1, out tag2);
        }

        /// <summary>	
        /// Paints the interior of the specified geometry. 	
        /// </summary>	
        /// <remarks>	
        /// If the opacityBrush parameter is not NULL, the alpha value of each pixel of the mapped opacityBrush is used to determine the resulting opacity of each corresponding pixel of the geometry. Only the alpha value of each color in the brush is used for this processing; all other color information is ignored.  The alpha value specified by the brush is multiplied by the alpha value of the geometry after the geometry has been painted by brush.  	
        /// When this method fails, it does not return an error code. To determine whether a drawing operation (such as FillGeometry) failed, check the result returned by the <see cref="SlimDX.Direct2D1.RenderTarget.EndDraw"/> or <see cref="SlimDX.Direct2D1.RenderTarget.Flush"/> method. 	
        /// </remarks>	
        /// <param name="geometry">The geometry to paint.</param>
        /// <param name="brush">The brush used to paint the geometry's interior.</param>
        /// <unmanaged>void FillGeometry([In] ID2D1Geometry* geometry,[In] ID2D1Brush* brush,[In, Optional] ID2D1Brush* opacityBrush)</unmanaged>
        public void FillGeometry(SlimDX.Direct2D1.Geometry geometry, SlimDX.Direct2D1.Brush brush)
        {
            FillGeometry(geometry, brush, null);
        }

    }
}
