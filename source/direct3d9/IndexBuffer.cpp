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
#include "IndexBuffer.h"

namespace SlimDX
{
namespace Direct3D9
{
	IndexBuffer::IndexBuffer( IDirect3DIndexBuffer9* buffer )
	{
		if( buffer == NULL )
			throw gcnew ArgumentNullException( "buffer" );

		m_Pointer = buffer;
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
		m_Pointer = ibPtr;
	}

	IndexBuffer::IndexBuffer( Device^ device, int sizeBytes, Usage usage, Pool pool, bool sixteenBit )
	{
		IDirect3DIndexBuffer9* ib;
		D3DFORMAT format = sixteenBit ? D3DFMT_INDEX16 : D3DFMT_INDEX32;
		HRESULT hr = device->InternalPointer->CreateIndexBuffer( sizeBytes, static_cast<DWORD>( usage ), format, static_cast<D3DPOOL>( pool ), &ib, NULL );
		GraphicsException::CheckHResult( hr );

		m_Pointer = ib;
	}

	DataStream^ IndexBuffer::Lock( int offset, int size, LockFlags flags )
	{
		void* lockedPtr;
		HRESULT hr = IbPointer->Lock( offset, size, &lockedPtr, static_cast<DWORD>( flags ) );
		GraphicsException::CheckHResult( hr );

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		DataStream^ stream = gcnew DataStream( lockedPtr, 0, true, !readOnly, false );
		return stream;
	}

	void IndexBuffer::Unlock()
	{
		IbPointer->Unlock();
	}
}
}