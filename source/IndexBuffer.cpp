#include <d3d9.h>
#include <d3dx9.h>

#include "Device.h"
#include "IndexBuffer.h"
#include "Utils.h"

namespace SlimDX
{
namespace Direct3D
{
	IndexBuffer::IndexBuffer( IDirect3DIndexBuffer9* buffer )
	{
		if( buffer == NULL )
			throw gcnew ArgumentNullException( "buffer" );

		m_Buffer = buffer;
	}

	IndexBuffer::IndexBuffer( Device^ device, int sizeBytes, Usage usage, Pool pool, bool sixteenBit )
	{
		IDirect3DIndexBuffer9* ib;
		D3DFORMAT format = sixteenBit ? D3DFMT_INDEX16 : D3DFMT_INDEX32;
		HRESULT hr = device->InternalPointer->CreateIndexBuffer( sizeBytes, (DWORD) usage, format, (D3DPOOL) pool, &ib, NULL );
		GraphicsException::CheckHResult( hr );

		m_Buffer = ib;
	}

	GraphicsStream^ IndexBuffer::Lock( int offset, int size, LockFlags flags )
	{
		void* lockedPtr;
		HRESULT hr = m_Buffer->Lock( offset, size, &lockedPtr, (DWORD) flags );
		GraphicsException::CheckHResult( hr );

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		GraphicsStream^ stream = gcnew GraphicsStream( lockedPtr, true, !readOnly );
		return stream;
	}

	void IndexBuffer::Unlock()
	{
		m_Buffer->Unlock();
	}
}
}