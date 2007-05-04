#include <d3d9.h>
#include <d3dx9.h>

#include "Device.h"
#include "Texture.h"
#include "Utils.h"

namespace SlimDX
{
namespace Direct3D
{
	Texture::Texture( IDirect3DTexture9* texture )
	{
		if( texture == NULL )
			throw gcnew ArgumentNullException( "texture" );

		m_Texture = texture;
		m_Disposed = false;
	}

	Texture::Texture( Device^ device, int width, int height, int numLevels, Usage usage, Format format, Pool pool )
	{
		IDirect3DTexture9* texture;
		HRESULT hr = device->InternalPointer->CreateTexture( width, height, numLevels, (DWORD) usage, 
			(D3DFORMAT) format, (D3DPOOL) pool, &texture, NULL );
		FAILED_THROW( hr );

		m_Texture = texture;
		m_Disposed = false;
	}

	generic<typename T>
	GraphicsStream<T>^ Texture::LockRectangle( int level, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;
		HRESULT hr = m_Texture->LockRect( level, &lockedRect, NULL, (DWORD) flags );
		FAILED_THROW( hr );

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		GraphicsStream<T>^ stream = gcnew GraphicsStream<T>( lockedRect.pBits, true, !readOnly );
		return stream;
	}

	void Texture::UnlockRectangle( int level )
	{
		HRESULT hr = m_Texture->UnlockRect( level );
		FAILED_THROW( hr );
	}


	CubeTexture::CubeTexture( IDirect3DCubeTexture9* texture )
	{
		if( texture == NULL )
			throw gcnew ArgumentNullException( "texture" );

		m_Texture = texture;
		m_Disposed = false;
	}

	CubeTexture::CubeTexture( Device^ device, int edgeLength, int numLevels, Usage usage, Format format, Pool pool )
	{
		IDirect3DCubeTexture9* texture;
		HRESULT hr = device->InternalPointer->CreateCubeTexture( edgeLength, numLevels, (DWORD) usage,
			(D3DFORMAT) format, (D3DPOOL) pool, &texture, NULL );
		FAILED_THROW( hr );

		m_Texture = texture;
		m_Disposed = false;
	}

	generic<typename T>
	GraphicsStream<T>^ CubeTexture::LockRectangle( CubeMapFace face, int level, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;
		HRESULT hr = m_Texture->LockRect( (D3DCUBEMAP_FACES) face, level, &lockedRect, NULL, (DWORD) flags );
		FAILED_THROW( hr );

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		GraphicsStream<T>^ stream = gcnew GraphicsStream<T>( lockedRect.pBits, true, !readOnly );
		return stream;
	}

	void CubeTexture::UnlockRectangle( CubeMapFace face, int level )
	{
		HRESULT hr = m_Texture->UnlockRect( (D3DCUBEMAP_FACES) face, level );
		FAILED_THROW( hr );
	}

	Texture^ TextureLoader::FromStream( Device^ device, Stream^ stream, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DTexture9* texture;

		array<Byte>^ data = Utils::ReadStream( stream, 0 );
		pin_ptr<unsigned char> pinned_data = &data[0];

		D3DXCreateTextureFromFileInMemoryEx( device->InternalPointer, pinned_data, data->Length, width, height, numLevels,
			(DWORD) usage, (D3DFORMAT) format, (D3DPOOL) pool, (DWORD) filter, (DWORD) mipFilter,
			(D3DCOLOR) colorKey, 0, 0, &texture );

		return gcnew Texture( texture );
	}

	CubeTexture^ TextureLoader::FromCubeStream( Device^ device, Stream^ stream, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DCubeTexture9* texture;

		array<Byte>^ data = Utils::ReadStream( stream, 0 );
		pin_ptr<unsigned char> pinned_data = &data[0];

		D3DXCreateCubeTextureFromFileInMemoryEx( device->InternalPointer, pinned_data, data->Length, size, numLevels,
			(DWORD) usage, (D3DFORMAT) format, (D3DPOOL) pool, (DWORD) filter, (DWORD) mipFilter,
			(D3DCOLOR) colorKey, 0, 0, &texture );

		return gcnew CubeTexture( texture );
	}
}
}