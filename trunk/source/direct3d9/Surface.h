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
#pragma once

#include "Resource.h"

namespace SlimDX
{
	ref class GraphicsStream;

	namespace Direct3D9
	{
		public value class SurfaceDescription
		{
		public:
			Format Format;
			ResourceType Type;
			Usage Usage;
			Pool Pool;
			MultiSampleType MultiSampleType;
			int MultiSampleQuality;
			int Width;
			int Height;
		};

		public ref class Surface : public Resource
		{
		internal:
			property IDirect3DSurface9* SurfacePointer
			{
				IDirect3DSurface9* get() { return (IDirect3DSurface9*) m_Pointer; }
			}

		public:
			Surface( IDirect3DSurface9* Surface );

			static Surface^ CreateRenderTarget( Device^ device, int width, int height, Format format,
				MultiSampleType multiSampleType, int multiSampleQuality, bool lockable );
			static Surface^ CreateOffscreenPlain( Device^ device, int width, int height, Format format, Pool pool );
			static Surface^ CreateDepthStencil( Device^ device, int width, int height, Format format,
				MultiSampleType multiSampleType, int multiSampleQuality, bool discard );

			GraphicsStream^ LockRectangle( LockFlags flags );
			void UnlockRectangle();

			SurfaceDescription GetDesc();
			IntPtr GetDC();
			void ReleaseDC( IntPtr hdc );
		};
	}
}
