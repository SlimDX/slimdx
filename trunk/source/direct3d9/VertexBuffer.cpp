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
namespace Direct3D9
{
	VertexBuffer::VertexBuffer( IDirect3DVertexBuffer9* buffer )
	{
		if( buffer == NULL )
			throw gcnew ArgumentNullException( "buffer" );

		D3DVERTEXBUFFER_DESC desc;
		HRESULT hr = buffer->GetDesc( &desc );
		GraphicsException::CheckHResult( hr );
		
		Format = ( SlimDX::Direct3D9::Format ) desc.Format;
		Usage = ( SlimDX::Direct3D9::Usage ) desc.Usage;
		Pool = ( SlimDX::Direct3D9::Pool ) desc.Pool;
		SizeInBytes = desc.Size;
		FVF = ( VertexFormat ) desc.FVF;

		m_Pointer = buffer;
	}

	VertexBuffer::VertexBuffer( IntPtr buffer )
	{
		if( buffer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "buffer" );

		void* pointer;
		IUnknown* unknown = (IUnknown*) buffer.ToPointer();
		HRESULT hr = unknown->QueryInterface( IID_IDirect3DVertexBuffer9, &pointer );
		if( FAILED( hr ) )
			throw gcnew GraphicsException( "Failed to QueryInterface on user-supplied pointer." );

		IDirect3DVertexBuffer9* vbPtr = (IDirect3DVertexBuffer9*) pointer;

		D3DVERTEXBUFFER_DESC desc;
		hr = vbPtr->GetDesc( &desc );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			throw gcnew GraphicsException( "Could not get vertex buffer description." );
		
		Format = ( SlimDX::Direct3D9::Format ) desc.Format;
		Usage = ( SlimDX::Direct3D9::Usage ) desc.Usage;
		Pool = ( SlimDX::Direct3D9::Pool ) desc.Pool;
		SizeInBytes = desc.Size;
		FVF = ( VertexFormat ) desc.FVF;

		m_Pointer = vbPtr;
	}

	VertexBuffer::VertexBuffer( Device^ device, int sizeBytes, SlimDX::Direct3D9::Usage usage, VertexFormat format, SlimDX::Direct3D9::Pool pool )
	{
		IDirect3DVertexBuffer9* vb;
		HRESULT hr = device->InternalPointer->CreateVertexBuffer( sizeBytes, (DWORD) usage, 
			(DWORD) format, (D3DPOOL) pool, &vb, NULL );
		GraphicsException::CheckHResult( hr );
		
		D3DVERTEXBUFFER_DESC desc;
		hr = vb->GetDesc( &desc );
		GraphicsException::CheckHResult( hr );
		
		Format = ( SlimDX::Direct3D9::Format ) desc.Format;
		Usage = ( SlimDX::Direct3D9::Usage ) desc.Usage;
		Pool = ( SlimDX::Direct3D9::Pool ) desc.Pool;
		SizeInBytes = desc.Size;
		FVF = ( VertexFormat ) desc.FVF;
		
		m_Pointer = vb;
	}

	DataStream^ VertexBuffer::Lock( int offset, int size, LockFlags flags )
	{
		void* lockedPtr;
		HRESULT hr = VbPointer->Lock( offset, size, &lockedPtr, (DWORD) flags );
		GraphicsException::CheckHResult( hr );
		
		int lockedSize = size == 0 ? SizeInBytes : size;
		
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		DataStream^ stream = gcnew DataStream( lockedPtr, lockedSize, true, !readOnly );
		return stream;
	}
	
	DataStream^ VertexBuffer::Lock( int offset, LockFlags flags )
	{
		return Lock( offset, 0, flags );
	}

	void VertexBuffer::Unlock()
	{
		VbPointer->Unlock();
	}
}
}
