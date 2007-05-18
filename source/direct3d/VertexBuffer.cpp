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
#include <d3d9.h>
#include <d3dx9.h>

#include "../Utils.h"
#include "Device.h"
#include "VertexBuffer.h"

namespace SlimDX
{
namespace Direct3D
{
	VertexBuffer::VertexBuffer( IDirect3DVertexBuffer9* buffer )
	{
		if( buffer == NULL )
			throw gcnew ArgumentNullException( "buffer" );

		m_Pointer = buffer;
	}

	VertexBuffer::VertexBuffer( Device^ device, int sizeBytes, Usage usage, VertexFormat format, Pool pool )
	{
		IDirect3DVertexBuffer9* vb;
		HRESULT hr = device->InternalPointer->CreateVertexBuffer( sizeBytes, (DWORD) usage, 
			(DWORD) format, (D3DPOOL) pool, &vb, NULL );
		GraphicsException::CheckHResult( hr );
		
		m_Pointer = vb;
	}

	GraphicsStream^ VertexBuffer::Lock( int offset, int size, LockFlags flags )
	{
		void* lockedPtr;
		HRESULT hr = VbPointer->Lock( offset, size, &lockedPtr, (DWORD) flags );
		GraphicsException::CheckHResult( hr );

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		GraphicsStream^ stream = gcnew GraphicsStream( lockedPtr, true, !readOnly );
		return stream;
	}

	void VertexBuffer::Unlock()
	{
		VbPointer->Unlock();
	}
}
}
