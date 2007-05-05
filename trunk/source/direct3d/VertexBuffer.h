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
#include "GraphicsStream.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D
	{
		public ref class VertexBuffer sealed : public Resource
		{
		private:
			IDirect3DVertexBuffer9* m_Buffer;

		internal:
			property IDirect3DVertexBuffer9* InternalPointer
			{
				IDirect3DVertexBuffer9* get() { return m_Buffer; }
			}

			property IDirect3DResource9* ResourcePointer
			{
				virtual IDirect3DResource9* get() override { return m_Buffer; }
			}

			property IUnknown* ComPointer
			{
				virtual IUnknown* get() override { return m_Buffer; }
				virtual void set( IUnknown* value ) override { m_Buffer = (IDirect3DVertexBuffer9*) value; }
			}

		public:
			VertexBuffer( IDirect3DVertexBuffer9* buffer );
			VertexBuffer( Device^ device, int sizeBytes, Usage usage, VertexFormats format, Pool pool );

			GraphicsStream^ Lock( int offset, int size, LockFlags flags );
			GraphicsStream^ Lock( int offset, LockFlags flags ) { return Lock( offset, 0, flags ); }
			void Unlock();
		};
	}
}
