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

#include "../Utilities.h"

#include "Direct3D9ErrorHandler.h"
#include "Direct3D9Exception.h"

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

		D3DVERTEXBUFFER_DESC description;
		HRESULT hr = buffer->GetDesc( &description );
		Direct3D9ErrorHandler::TestForFailure( hr );
		
		Format = static_cast<SlimDX::Direct3D9::Format>( description.Format );
		Usage = static_cast<SlimDX::Direct3D9::Usage>( description.Usage );
		Pool = static_cast<SlimDX::Direct3D9::Pool>( description.Pool );
		SizeInBytes = description.Size;
		FVF = static_cast<VertexFormat>( description.FVF );

		Construct(buffer);
	}

	VertexBuffer::VertexBuffer( IntPtr buffer )
	{
		if( buffer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "buffer" );

		void* pointer;
		IUnknown* unknown = static_cast<IUnknown*>( buffer.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_IDirect3DVertexBuffer9, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		IDirect3DVertexBuffer9* vbPtr = static_cast<IDirect3DVertexBuffer9*>( pointer );

		D3DVERTEXBUFFER_DESC description;
		hr = vbPtr->GetDesc( &description );
		Direct3D9ErrorHandler::TestForFailure( hr );
		if( FAILED( hr ) )
			throw gcnew Direct3D9Exception( hr );
		
		Format = static_cast<SlimDX::Direct3D9::Format>( description.Format );
		Usage = static_cast<SlimDX::Direct3D9::Usage>( description.Usage );
		Pool = static_cast<SlimDX::Direct3D9::Pool>( description.Pool );
		SizeInBytes = description.Size;
		FVF = static_cast<VertexFormat>( description.FVF );

		Construct(vbPtr);
	}

	VertexBuffer::VertexBuffer( Device^ device, int sizeBytes, SlimDX::Direct3D9::Usage usage, VertexFormat format, SlimDX::Direct3D9::Pool pool )
	{
		IDirect3DVertexBuffer9* vb;
		HRESULT hr = device->InternalPointer->CreateVertexBuffer( sizeBytes, static_cast<DWORD>( usage ), 
			static_cast<DWORD>( format ), static_cast<D3DPOOL>( pool ), &vb, NULL );
		Direct3D9ErrorHandler::TestForFailure( hr );
		
		D3DVERTEXBUFFER_DESC description;
		hr = vb->GetDesc( &description );
		Direct3D9ErrorHandler::TestForFailure( hr );
		
		Format = static_cast<SlimDX::Direct3D9::Format>( description.Format );
		Usage = static_cast<SlimDX::Direct3D9::Usage>( description.Usage );
		Pool = static_cast<SlimDX::Direct3D9::Pool>( description.Pool );
		SizeInBytes = description.Size;
		FVF = static_cast<VertexFormat>( description.FVF );
		
		Construct(vb);
	}

	DataStream^ VertexBuffer::Lock( int offset, int size, LockFlags flags )
	{
		void* lockedPtr;
		HRESULT hr = VbPointer->Lock( offset, size, &lockedPtr, static_cast<DWORD>( flags ) );
		Direct3D9ErrorHandler::TestForFailure( hr );
		
		int lockedSize = size == 0 ? SizeInBytes : size;
		
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		DataStream^ stream = gcnew DataStream( lockedPtr, lockedSize, true, !readOnly, false );
		return stream;
	}

	void VertexBuffer::Unlock()
	{
		VbPointer->Unlock();
	}
}
}
