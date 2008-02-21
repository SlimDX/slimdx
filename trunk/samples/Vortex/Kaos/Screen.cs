/*
* Copyright (c) 2007 SlimDX Group
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
using System.Collections.Generic;
using System.Text;
using SlimDX;
using SlimDX.Direct3D9;

namespace Demo.Kaos
{
	class ScreenTexture
	{
		public ScreenTexture(Device device, int width, int height)
		{
			mTexture = new SlimDX.Direct3D9.Texture(device, width, height, 1, Usage.RenderTarget, Format.A8R8G8B8, Pool.Default);
			mSurface = mTexture.GetSurfaceLevel(0);
			// todo: handle lost device
		}

		~ScreenTexture()
		{
			mTexture.Dispose();
			if(mSurface != null)
				mSurface.Dispose();
		}


		public void Stretch(Device device)
		{
			System.Drawing.Rectangle myRect = new System.Drawing.Rectangle(0, 0, 1024, 1024);

			Surface backBuffer = device.GetRenderTarget(0);
			System.Drawing.Rectangle backBufferRect = new System.Drawing.Rectangle(0, 0, backBuffer.Description.Width, backBuffer.Description.Height);
			device.ColorFill(mSurface, myRect, (Color4)0);
			device.StretchRect(backBuffer, backBufferRect, mSurface, myRect, TextureFilter.Linear);
		}

		public Texture Texture
		{
			get { return mTexture; }
		}

		private Texture mTexture;
		private Surface mSurface;
	}
}
