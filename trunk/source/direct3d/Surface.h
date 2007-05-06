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

using namespace System;

namespace SlimDX
{
	ref class GraphicsStream;

	namespace Direct3D
	{
		public value class SurfaceDescription
		{
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
		private:
			IDirect3DSurface9* m_Surface;

		internal:
			property IDirect3DSurface9* InternalPointer
			{
				IDirect3DSurface9* get() { return m_Surface; }
			}

			property IDirect3DResource9* ResourcePointer
			{
				virtual IDirect3DResource9* get() override { return m_Surface; }
			}

			property IUnknown* ComPointer
			{
				virtual IUnknown* get() override { return m_Surface; }
				virtual void set( IUnknown* value ) override { m_Surface = (IDirect3DSurface9*) value; }
			}

		public:
			Surface( IDirect3DSurface9* Surface );

			GraphicsStream^ LockRectangle( LockFlags flags );
			void UnlockRectangle();

			SurfaceDescription GetDesc();
			IntPtr GetDC();
			void ReleaseDC( IntPtr hdc );
		};
	}
}
