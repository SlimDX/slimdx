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
    public partial class Bitmap
    {
        /// <summary>	
        /// Creates a Direct2D bitmap from a pointer to in-memory source data.	
        /// </summary>	
        /// <param name="renderTarget">an instance of <see cref = "SlimDX2.Direct2D1.RenderTarget" /></param>
        /// <param name="size">The dimension of the bitmap to create in pixels.</param>
        /// <unmanaged>HRESULT CreateBitmap([None] D2D1_SIZE_U size,[In, Optional] const void* srcData,[None] UINT32 pitch,[In] const D2D1_BITMAP_PROPERTIES* bitmapProperties,[Out] ID2D1Bitmap** bitmap)</unmanaged>
        public Bitmap(RenderTarget renderTarget, System.Drawing.Size size)
            : this(renderTarget, size, null, 0, new BitmapProperties(new PixelFormat(Format.Unknown, AlphaMode.Unknown)))
        {
        }

        /// <summary>	
        /// Creates a Direct2D bitmap from a pointer to in-memory source data.	
        /// </summary>	
        /// <param name="renderTarget">an instance of <see cref = "SlimDX2.Direct2D1.RenderTarget" /></param>
        /// <param name="size">The dimension of the bitmap to create in pixels.</param>
        /// <param name="dataStream">A pointer to the memory location of the image data, or NULL to create an uninitialized bitmap.</param>
        /// <param name="pitch">The byte count of each scanline, which is equal to (the image width in pixels * the number of bytes per pixel) + memory padding. If srcData is NULL, this value is ignored. (Note that pitch is also sometimes called stride.)</param>
        /// <param name="bitmapProperties">The pixel format and dots per inch (DPI) of the bitmap to create.</param>
        /// <unmanaged>HRESULT CreateBitmap([None] D2D1_SIZE_U size,[In, Optional] const void* srcData,[None] UINT32 pitch,[In] const D2D1_BITMAP_PROPERTIES* bitmapProperties,[Out] ID2D1Bitmap** bitmap)</unmanaged>
        public Bitmap(RenderTarget renderTarget, System.Drawing.Size size, SlimDX2.Direct2D1.BitmapProperties bitmapProperties)
            : this(renderTarget, size, null, 0, bitmapProperties)
        {
        }

        /// <summary>	
        /// Creates a Direct2D bitmap from a pointer to in-memory source data.	
        /// </summary>	
        /// <param name="renderTarget">an instance of <see cref = "SlimDX2.Direct2D1.RenderTarget" /></param>
        /// <param name="size">The dimension of the bitmap to create in pixels.</param>
        /// <param name="dataStream">A pointer to the memory location of the image data, or NULL to create an uninitialized bitmap.</param>
        /// <param name="pitch">The byte count of each scanline, which is equal to (the image width in pixels * the number of bytes per pixel) + memory padding. If srcData is NULL, this value is ignored. (Note that pitch is also sometimes called stride.)</param>
        /// <unmanaged>HRESULT CreateBitmap([None] D2D1_SIZE_U size,[In, Optional] const void* srcData,[None] UINT32 pitch,[In] const D2D1_BITMAP_PROPERTIES* bitmapProperties,[Out] ID2D1Bitmap** bitmap)</unmanaged>
        public Bitmap(RenderTarget renderTarget, System.Drawing.Size size, DataStream dataStream, int pitch)
            : this(renderTarget, size, dataStream, pitch, new BitmapProperties(new PixelFormat(Format.Unknown, AlphaMode.Unknown)))
        {
        }

        /// <summary>	
        /// Creates a Direct2D bitmap from a pointer to in-memory source data.	
        /// </summary>	
        /// <param name="renderTarget">an instance of <see cref = "SlimDX2.Direct2D1.RenderTarget" /></param>
        /// <param name="size">The dimension of the bitmap to create in pixels.</param>
        /// <param name="dataStream">A pointer to the memory location of the image data, or NULL to create an uninitialized bitmap.</param>
        /// <param name="pitch">The byte count of each scanline, which is equal to (the image width in pixels * the number of bytes per pixel) + memory padding. If srcData is NULL, this value is ignored. (Note that pitch is also sometimes called stride.)</param>
        /// <param name="bitmapProperties">The pixel format and dots per inch (DPI) of the bitmap to create.</param>
        /// <unmanaged>HRESULT CreateBitmap([None] D2D1_SIZE_U size,[In, Optional] const void* srcData,[None] UINT32 pitch,[In] const D2D1_BITMAP_PROPERTIES* bitmapProperties,[Out] ID2D1Bitmap** bitmap)</unmanaged>
        public Bitmap(RenderTarget renderTarget, System.Drawing.Size size, DataStream dataStream, int pitch, SlimDX2.Direct2D1.BitmapProperties bitmapProperties) : base(IntPtr.Zero)
        {
            Bitmap bitmap;
            renderTarget.CreateBitmap(size, dataStream==null?IntPtr.Zero:dataStream.PositionPointer, pitch, bitmapProperties, out bitmap);
            NativePointer = bitmap.NativePointer;
        }


        /// <summary>	
        /// Creates an <see cref="SlimDX2.Direct2D1.Bitmap"/> whose data is shared with another resource.	
        /// </summary>	
        /// <param name="renderTarget">an instance of <see cref = "SlimDX2.Direct2D1.RenderTarget" /></param>
        /// <param name="bitmap">An <see cref="SlimDX2.Direct2D1.Bitmap"/> that contains the data to share with the new ID2D1Bitmap. For more information, see the Remarks section.</param>
        /// <unmanaged>HRESULT CreateSharedBitmap([In] REFIID riid,[InOut] void* data,[In, Optional] const D2D1_BITMAP_PROPERTIES* bitmapProperties,[Out] ID2D1Bitmap** bitmap)</unmanaged>
        public Bitmap(RenderTarget renderTarget, Bitmap bitmap) : this(renderTarget, bitmap, null)
        {
        }

        /// <summary>	
        /// Creates an <see cref="SlimDX2.Direct2D1.Bitmap"/> whose data is shared with another resource.	
        /// </summary>	
        /// <param name="renderTarget">an instance of <see cref = "SlimDX2.Direct2D1.RenderTarget" /></param>
        /// <param name="bitmap">An <see cref="SlimDX2.Direct2D1.Bitmap"/> that contains the data to share with the new ID2D1Bitmap. For more information, see the Remarks section.</param>
        /// <param name="bitmapProperties">The pixel format  and DPI of the bitmap to create . The <see cref="SlimDX2.DXGI.Format"/> portion of the pixel format  must match the <see cref="SlimDX2.DXGI.Format"/> of data or the method will fail, but the alpha modes don't have to match. To prevent a  mismatch, you can pass NULL or the value obtained from the {{D2D1::PixelFormat}} helper function. The DPI settings do not have to match those of data. If both dpiX and dpiY are  0.0f, the default DPI, 96, is used.</param>
        /// <unmanaged>HRESULT CreateSharedBitmap([In] REFIID riid,[InOut] void* data,[In, Optional] const D2D1_BITMAP_PROPERTIES* bitmapProperties,[Out] ID2D1Bitmap** bitmap)</unmanaged>
        public Bitmap(RenderTarget renderTarget, Bitmap bitmap, SlimDX2.Direct2D1.BitmapProperties? bitmapProperties) : base(IntPtr.Zero)
        {
            Bitmap temp;
            renderTarget.CreateSharedBitmap(typeof(Bitmap).GUID, bitmap.NativePointer, bitmapProperties, out temp);
            NativePointer = temp.NativePointer;
        }

        /// <summary>	
        /// Creates an <see cref="SlimDX2.Direct2D1.Bitmap"/> whose data is shared with another resource.	
        /// </summary>	
        /// <param name="renderTarget">an instance of <see cref = "SlimDX2.Direct2D1.RenderTarget" /></param>
        /// <param name="surface">An <see cref="SlimDX2.DXGI.Surface"/> that contains the data to share with the new ID2D1Bitmap. For more information, see the Remarks section.</param>
        /// <unmanaged>HRESULT CreateSharedBitmap([In] REFIID riid,[InOut] void* data,[In, Optional] const D2D1_BITMAP_PROPERTIES* bitmapProperties,[Out] ID2D1Bitmap** bitmap)</unmanaged>
        public Bitmap(RenderTarget renderTarget, Surface surface) : this(renderTarget, surface, null)
        {
        }

        /// <summary>	
        /// Creates an <see cref="SlimDX2.Direct2D1.Bitmap"/> whose data is shared with another resource.	
        /// </summary>	
        /// <param name="renderTarget">an instance of <see cref = "SlimDX2.Direct2D1.RenderTarget" /></param>
        /// <param name="surface">An <see cref="SlimDX2.DXGI.Surface"/> that contains the data to share with the new ID2D1Bitmap. For more information, see the Remarks section.</param>
        /// <param name="bitmapProperties">The pixel format  and DPI of the bitmap to create . The <see cref="SlimDX2.DXGI.Format"/> portion of the pixel format  must match the <see cref="SlimDX2.DXGI.Format"/> of data or the method will fail, but the alpha modes don't have to match. To prevent a  mismatch, you can pass NULL or the value obtained from the {{D2D1::PixelFormat}} helper function. The DPI settings do not have to match those of data. If both dpiX and dpiY are  0.0f, the default DPI, 96, is used.</param>
        /// <unmanaged>HRESULT CreateSharedBitmap([In] REFIID riid,[InOut] void* data,[In, Optional] const D2D1_BITMAP_PROPERTIES* bitmapProperties,[Out] ID2D1Bitmap** bitmap)</unmanaged>
        public Bitmap(RenderTarget renderTarget, Surface surface, SlimDX2.Direct2D1.BitmapProperties? bitmapProperties) : base(IntPtr.Zero)
        {
            Bitmap temp;
            renderTarget.CreateSharedBitmap(typeof(Surface).GUID, surface.NativePointer, bitmapProperties, out temp);
            NativePointer = temp.NativePointer;
        }

    }
}
