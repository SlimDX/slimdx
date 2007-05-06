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
#include <vcclr.h>

#include "../DirectXObject.h"
#include "../Utils.h"

#include "Device.h"
#include "D3DX.h"
#include "GraphicsStream.h"
#include "Texture.h"

namespace SlimDX
{
namespace Direct3D
{
	Texture::Texture( IDirect3DTexture9* texture )
	{
		if( texture == NULL )
			throw gcnew ArgumentNullException( "texture" );

		m_Texture = texture;
	}

	Texture::Texture( Device^ device, int width, int height, int numLevels, Usage usage, Format format, Pool pool )
	{
		IDirect3DTexture9* texture;
		HRESULT hr = device->InternalPointer->CreateTexture( width, height, numLevels, (DWORD) usage, 
			(D3DFORMAT) format, (D3DPOOL) pool, &texture, NULL );
		GraphicsException::CheckHResult( hr );

		m_Texture = texture;
	}

	Texture^ Texture::FromStream( Device^ device, Stream^ stream, int width, int height, int numLevels,
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

	Texture^ Texture::FromStream( Device^ device, Stream^ stream, Usage usage, Pool pool )
	{
		return Texture::FromStream( device, stream, D3DX::Default, D3DX::Default, D3DX::Default,
			usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	Texture^ Texture::FromStream( Device^ device, Stream^ stream )
	{
		return Texture::FromStream( device, stream, Usage::None, Pool::Managed );
	}

	Texture^ Texture::FromFile( Device^ device, String^ fileName, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DTexture9* texture;
		pin_ptr<const wchar_t> pinned_name = PtrToStringChars( fileName );

		HRESULT hr = D3DXCreateTextureFromFileEx( device->InternalPointer, pinned_name, width, height, 
			numLevels, (DWORD) usage, (D3DFORMAT) format, (D3DPOOL) pool, (DWORD) filter, (DWORD) mipFilter, 
			colorKey, NULL, NULL, &texture );
		GraphicsException::CheckHResult( hr );

		return gcnew Texture( texture );
	}

	Texture^ Texture::FromFile( Device^ device, String^ fileName, Usage usage, Pool pool )
	{
		return Texture::FromFile( device, fileName, D3DX::Default, D3DX::Default, D3DX::Default,
			usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	Texture^ Texture::FromFile( Device^ device, String^ fileName )
	{
		return Texture::FromFile( device, fileName, Usage::None, Pool::Managed );
	}

	GraphicsStream^ Texture::LockRectangle( int level, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;
		HRESULT hr = m_Texture->LockRect( level, &lockedRect, NULL, (DWORD) flags );
		GraphicsException::CheckHResult( hr );

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		GraphicsStream^ stream = gcnew GraphicsStream( lockedRect.pBits, true, !readOnly );
		return stream;
	}

	void Texture::UnlockRectangle( int level )
	{
		HRESULT hr = m_Texture->UnlockRect( level );
		GraphicsException::CheckHResult( hr );
	}

	SurfaceDescription Texture::GetLevelDesc( int level )
	{
		SurfaceDescription desc;
		HRESULT hr = m_Texture->GetLevelDesc( level, (D3DSURFACE_DESC*) &desc );
		GraphicsException::CheckHResult( hr );
		return desc;
	}

	Surface^ Texture::GetSurfaceLevel( int level )
	{
		IDirect3DSurface9* surface;
		HRESULT hr = m_Texture->GetSurfaceLevel( level, &surface );
		GraphicsException::CheckHResult( hr );
		return gcnew Surface( surface );
	}

	CubeTexture::CubeTexture( IDirect3DCubeTexture9* texture )
	{
		if( texture == NULL )
			throw gcnew ArgumentNullException( "texture" );

		m_Texture = texture;
	}

	CubeTexture::CubeTexture( Device^ device, int edgeLength, int numLevels, Usage usage, Format format, Pool pool )
	{
		IDirect3DCubeTexture9* texture;
		HRESULT hr = device->InternalPointer->CreateCubeTexture( edgeLength, numLevels, (DWORD) usage,
			(D3DFORMAT) format, (D3DPOOL) pool, &texture, NULL );
		GraphicsException::CheckHResult( hr );

		m_Texture = texture;
	}

	CubeTexture^ CubeTexture::FromStream( Device^ device, Stream^ stream, int size, int numLevels,
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

	CubeTexture^ CubeTexture::FromFile( Device^ device, String^ fileName, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DCubeTexture9* texture;
		pin_ptr<const wchar_t> pinned_name = PtrToStringChars( fileName );

		HRESULT hr = D3DXCreateCubeTextureFromFileEx( device->InternalPointer, pinned_name, size, 
			numLevels, (DWORD) usage, (D3DFORMAT) format, (D3DPOOL) pool, (DWORD) filter, (DWORD) mipFilter, 
			colorKey, NULL, NULL, &texture );
		GraphicsException::CheckHResult( hr );

		return gcnew CubeTexture( texture );
	}

	CubeTexture^ CubeTexture::FromFile( Device^ device, String^ fileName, Usage usage, Pool pool )
	{
		return CubeTexture::FromFile( device, fileName, D3DX::Default, D3DX::Default,
			usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	CubeTexture^ CubeTexture::FromFile( Device^ device, String^ fileName )
	{
		return CubeTexture::FromFile( device, fileName, Usage::None, Pool::Managed );
	}

	GraphicsStream^ CubeTexture::LockRectangle( CubeMapFace face, int level, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;
		HRESULT hr = m_Texture->LockRect( (D3DCUBEMAP_FACES) face, level, &lockedRect, NULL, (DWORD) flags );
		GraphicsException::CheckHResult( hr );

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		GraphicsStream^ stream = gcnew GraphicsStream( lockedRect.pBits, true, !readOnly );
		return stream;
	}

	void CubeTexture::UnlockRectangle( CubeMapFace face, int level )
	{
		HRESULT hr = m_Texture->UnlockRect( (D3DCUBEMAP_FACES) face, level );
		GraphicsException::CheckHResult( hr );
	}
}
}