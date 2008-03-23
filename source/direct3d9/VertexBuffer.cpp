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

#include "Direct3D9Exception.h"

#include "Device.h"
#include "VertexBuffer.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D9
{
	VertexBuffer::VertexBuffer( IDirect3DVertexBuffer9* buffer )
	{
		D3DVERTEXBUFFER_DESC description;
		HRESULT hr = buffer->GetDesc( &description );
		
		if( RECORD_D3D9(hr).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );
		
		Construct(buffer);
		InitDescription();
	}

	VertexBuffer::VertexBuffer( IntPtr buffer )
	{
		void* pointer;
		IUnknown* unknown = static_cast<IUnknown*>( buffer.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_IDirect3DVertexBuffer9, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		IDirect3DVertexBuffer9* vbPtr = static_cast<IDirect3DVertexBuffer9*>( pointer );

		Construct(vbPtr);
		InitDescription();
	}

	VertexBuffer^ VertexBuffer::FromPointer( IDirect3DVertexBuffer9* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		VertexBuffer^ tableEntry = safe_cast<VertexBuffer^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew VertexBuffer( pointer );
	}

	VertexBuffer^ VertexBuffer::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		VertexBuffer^ tableEntry = safe_cast<VertexBuffer^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew VertexBuffer( pointer );
	}

	VertexBuffer::VertexBuffer( SlimDX::Direct3D9::Device^ device, int sizeInBytes, SlimDX::Direct3D9::Usage usage, VertexFormat format, SlimDX::Direct3D9::Pool pool )
	{
		IDirect3DVertexBuffer9* vb;
		HRESULT hr = device->InternalPointer->CreateVertexBuffer( sizeInBytes, static_cast<DWORD>( usage ), 
			static_cast<DWORD>( format ), static_cast<D3DPOOL>( pool ), &vb, NULL );
		
		if( RECORD_D3D9(hr).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );
		
		if( RECORD_D3D9(hr).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );
		
		Construct(vb);

		//set description from local info instead of getting the desc
		m_Description.Format = Format::VertexData;
		m_Description.Type = SlimDX::Direct3D9::ResourceType::VertexBuffer;
		m_Description.Usage = usage;
		m_Description.Pool = pool;
		m_Description.SizeInBytes = sizeInBytes;
		m_Description.FVF = format;

		if( m_Description.Pool == Pool::Default )
			this->IsDefaultPool = true;
	}

	void VertexBuffer::InitDescription()
	{
		VertexBufferDescription desc;
		HRESULT hr = InternalPointer->GetDesc( reinterpret_cast<D3DVERTEXBUFFER_DESC*>( &desc ) );
		if( FAILED( hr ) )
		{
			//fail this silently
			return;
		}

		m_Description = desc;
		if( m_Description.Pool == Pool::Default )
			this->IsDefaultPool = true;
	}

	DataStream^ VertexBuffer::Lock( int offset, int size, LockFlags flags )
	{
		void* lockedPtr;
		HRESULT hr = InternalPointer->Lock( offset, size, &lockedPtr, static_cast<DWORD>( flags ) );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;
		
		int lockedSize = size == 0 ? m_Description.SizeInBytes : size;
		
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		DataStream^ stream = gcnew DataStream( lockedPtr, lockedSize, true, !readOnly, false );
		return stream;
	}

	Result VertexBuffer::Unlock()
	{
		return RECORD_D3D9( InternalPointer->Unlock() );
	}
}
}
