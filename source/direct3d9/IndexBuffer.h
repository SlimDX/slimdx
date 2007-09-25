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
#include "../Direct3D/..\DataStream.h"

using namespace SlimDX::Direct3D;

namespace SlimDX
{
	namespace Direct3D9
	{
		public ref class IndexBuffer : public Resource
		{
		internal:
			property IDirect3DIndexBuffer9* IbPointer
			{
				IDirect3DIndexBuffer9* get() { return (IDirect3DIndexBuffer9*) m_Pointer; }
			}

			IndexBuffer( IDirect3DIndexBuffer9* buffer );

		public:
			IndexBuffer( IntPtr buffer );
			IndexBuffer( Device^ device, int sizeBytes, Usage usage, Pool pool, bool sixteenBit );

			DataStream^ Lock( int offset, int size, LockFlags flags );
			DataStream^ Lock( int offset, LockFlags flags )	{ return Lock( offset, 0, flags ); }
			void Unlock();
		};
	}
}
