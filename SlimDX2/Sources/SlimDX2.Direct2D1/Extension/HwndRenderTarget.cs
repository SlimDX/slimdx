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
using SlimDX2.DXGI;

namespace SlimDX2.Direct2D1
{
    public partial class HwndRenderTarget
    {
        /// <summary>	
        /// Creates an <see cref="SlimDX2.Direct2D1.HwndRenderTarget"/>, a render target that renders to a window.	
        /// </summary>	
        /// <remarks>	
        /// When you create a render target and hardware acceleration is available, you allocate resources on the computer's GPU. By creating a render target once and retaining it as long as possible, you gain performance benefits. Your application should create render targets once and hold onto them for the life of the application or until the {{D2DERR_RECREATE_TARGET}} error is received. When you receive this error, you need to recreate the render target (and any resources it created).	
        /// </remarks>
        /// <param name="factory">an instance of <see cref = "SlimDX2.Direct2D1.Factory" /></param>
        /// <param name="renderTargetProperties">The rendering mode, pixel format, remoting options, DPI information, and the minimum DirectX support required for hardware rendering. For information about supported pixel formats, see  {{Supported Pixel  Formats and Alpha Modes}}.</param>
        /// <param name="hwndProperties">The window handle, initial size (in pixels), and present options.</param>
        public HwndRenderTarget(Factory factory, RenderTargetProperties renderTargetProperties, HwndRenderTargetProperties hwndProperties)
            : base(IntPtr.Zero)
        {
            HwndRenderTarget temp;
            factory.CreateHwndRenderTarget(ref renderTargetProperties, ref hwndProperties, out temp);
            NativePointer = temp.NativePointer;
        }
    }
}
