/*
* Copyright (c) 2007-2008 SlimDX Group
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
#include "Device.h"
#include "IndexBuffer.h"
#include "Direct3D9Exception.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D9
{
	IndexBuffer::IndexBuffer( IDirect3DIndexBuffer9* buffer )
	{
		if( buffer == NULL )
			throw gcnew ArgumentNullException( "buffer" );

		Construct(buffer);
		InitDescription();
	}

	IndexBuffer::IndexBuffer( IntPtr buffer )
	{
		if( buffer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "buffer" );

		void* pointer;
		IUnknown* unknown = static_cast<IUnknown*>( buffer.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_IDirect3DIndexBuffer9, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		IDirect3DIndexBuffer9* ibPtr = static_cast<IDirect3DIndexBuffer9*>( pointer );
		Construct(ibPtr);
		InitDescription();
	}

	IndexBuffer::IndexBuffer( Device^ device, int sizeBytes, SlimDX::Direct3D9::Usage usage, SlimDX::Direct3D9::Pool pool, bool sixteenBit )
	{
		IDirect3DIndexBuffer9* ib;
		D3DFORMAT format = sixteenBit ? D3DFMT_INDEX16 : D3DFMT_INDEX32;
		HRESULT hr = device->InternalPointer->CreateIndexBuffer( sizeBytes, static_cast<DWORD>( usage ), format, static_cast<D3DPOOL>( pool ), &ib, NULL );
		if( Result::Record( hr ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(ib);
		InitDescription();
	}
	
	void IndexBuffer::InitDescription()
	{
	  D3DINDEXBUFFER_DESC description;
		HRESULT hr = static_cast<IDirect3DIndexBuffer9*>( InternalPointer )->GetDesc( &description );
		Result::Record( hr );
		
		m_Format = static_cast<SlimDX::Direct3D9::Format>( description.Format );
		m_Type = static_cast<SlimDX::Direct3D9::ResourceType>( description.Type );
		m_Usage = static_cast<SlimDX::Direct3D9::Usage>( description.Usage );
		m_Pool = static_cast<SlimDX::Direct3D9::Pool>( description.Pool );
		m_SizeInBytes = description.Size;
	}
	
	DataStream^ IndexBuffer::Lock( int offset, int size, LockFlags flags )
	{
		void* lockedPtr;
		HRESULT hr = IbPointer->Lock( offset, size, &lockedPtr, static_cast<DWORD>( flags ) );
		Result::Record( hr );
		
		int lockedSize = size == 0 ? m_SizeInBytes : size;
		
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		DataStream^ stream = gcnew DataStream( lockedPtr, lockedSize, true, !readOnly, false );
		return stream;
	}

	Result IndexBuffer::Unlock()
	{
		return Result::Record( IbPointer->Unlock() );
	}
}
}