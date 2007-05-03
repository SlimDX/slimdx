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

	Texture::~Texture()
	{
		Utils::MarkDisposed( m_Disposed, this );

		m_Texture->Release();
		m_Texture = NULL;
	}

	Texture::!Texture()
	{
		Utils::ReportNotDisposed( this );
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

	CubeTexture::~CubeTexture()
	{
		Utils::MarkDisposed( m_Disposed, this );

		m_Texture->Release();
		m_Texture = NULL;
	}

	CubeTexture::!CubeTexture()
	{
		Utils::ReportNotDisposed( this );
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