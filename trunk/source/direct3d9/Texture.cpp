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
#include "../Direct3D/..\DataStream.h"
#include "Texture.h"

namespace SlimDX
{
namespace Direct3D9
{
	/// <summary>
	/// Function to extract image information from a stream.
	/// </summary>
	/// <param name="stream">Stream containing the image.</param>
	/// <param name="peek">TRUE to preserve the stream position, FALSE will move the stream pointer.</param>
	/// <returns>Information about the image.</returns>
	ImageInformation ImageInformation::FromStream(Stream^ stream, bool peek)
	{
		array<Byte>^ buffer = nullptr;			// Buffer for the data.
		Int64 prevPosition = 0;				// Previous stream position.

		if (stream == nullptr)
			throw gcnew ArgumentNullException("stream");

		if (peek)
			prevPosition = stream->Position;

		// Create buffer.
		buffer = Utils::ReadStream( stream, (int) stream->Length );

		if (peek)
			stream->Position = prevPosition;

		// Extract from the byte buffer.
		return FromMemory(buffer);
	}

	/// <summary>
	/// Function to extract image information from a stream.
	/// </summary>
	/// <param name="stream">Stream containing the image.</param>
	/// <returns>Information about the image.</returns>
	ImageInformation ImageInformation::FromStream(Stream^ stream)
	{
		return FromStream(stream, true);
	}

	ImageInformation ImageInformation::FromFile( String^ fileName )
	{
		ImageInformation info;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXGetImageInfoFromFile( pinnedName, (D3DXIMAGE_INFO*) &info );
		GraphicsException::CheckHResult( hr );

		return info;
	}

	ImageInformation ImageInformation::FromMemory( array<Byte>^ memory )
	{
		ImageInformation info;
		pin_ptr<const unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXGetImageInfoFromFileInMemory( pinnedMemory, memory->Length, (D3DXIMAGE_INFO*) &info );
		GraphicsException::CheckHResult( hr );

		return info;
	}

	Texture::Texture( IDirect3DTexture9* texture )
	{
		if( texture == NULL )
			throw gcnew ArgumentNullException( "texture" );

		m_Pointer = texture;
	}

	Texture::Texture( Device^ device, int width, int height, int numLevels, Usage usage, Format format, Pool pool )
	{
		IDirect3DTexture9* texture;
		HRESULT hr = device->InternalPointer->CreateTexture( width, height, numLevels, (DWORD) usage, 
			(D3DFORMAT) format, (D3DPOOL) pool, &texture, NULL );
		GraphicsException::CheckHResult( hr );

		m_Pointer = texture;
	}

	/// <summary>
	/// Checks texture-creation parameters.
	/// </summary>
	/// <param name="device">Device associated with the texture.</param>
	/// <param name="width">Requested width of the texture.</param>
	/// <param name="height">Requested height of the texture.</param>
	/// <param name="numMipLevels">Requested number of mip-map levels for the texture.</param>
	/// <param name="usage">Usage.None or Usage.RenderTarget.</param>
	/// <param name="format">Requested format for the texture.</param>
	/// <param name="pool">Memory class where the resource will be placed.</param>
	/// <returns>A value type containing the proposed values to pass to the texture creation functions.</returns>
	TextureRequirements Texture::CheckRequirements(Device^ device, int width, int height,
		int numMipLevels, Usage usage, Format format, Pool pool)
	{
		TextureRequirements result;					// Result.
		D3DFORMAT d3dFormat = (D3DFORMAT)format;	// Format.
		HRESULT hr;									// Error code.

		// Get texture requirements.
		hr = D3DXCheckTextureRequirements(device->InternalPointer, (UINT *)&width, (UINT *)&height, (UINT *)&numMipLevels, (DWORD)usage, (D3DFORMAT *)&d3dFormat, (D3DPOOL)pool);
		GraphicsException::CheckHResult(hr);

		// Return proposed values.
		result.Width = width;
		result.Height = height;
		result.Format = format;
		result.NumOfMipLevels = numMipLevels;

		return result;
	}

	Texture^ Texture::FromMemory( Device^ device, array<Byte>^ memory, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		D3DXCreateTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length, width, height, numLevels,
			(DWORD) usage, (D3DFORMAT) format, (D3DPOOL) pool, (DWORD) filter, (DWORD) mipFilter,
			(D3DCOLOR) colorKey, 0, 0, &texture );

		return gcnew Texture( texture );
	}

	Texture^ Texture::FromMemory( Device^ device, array<Byte>^ memory, Usage usage, Pool pool )
	{
		return Texture::FromMemory( device, memory, D3DX::Default, D3DX::Default, D3DX::Default,
			usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	Texture^ Texture::FromMemory( Device^ device, array<Byte>^ memory )
	{
		return Texture::FromMemory( device, memory, Usage::None, Pool::Managed );
	}

	Texture^ Texture::FromStream( Device^ device, Stream^ stream, int sizeBytes, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		array<Byte>^ data = Utils::ReadStream( stream, sizeBytes );
		return Texture::FromMemory( device, data, width, height, numLevels, usage, format, pool, filter, mipFilter, colorKey );
	}

	Texture^ Texture::FromStream( Device^ device, Stream^ stream, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		return Texture::FromStream( device, stream, 0, width, height, numLevels, usage, format, pool, filter, mipFilter, colorKey );
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
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXCreateTextureFromFileEx( device->InternalPointer, pinnedName, width, height, 
			numLevels, (DWORD) usage, (D3DFORMAT) format, (D3DPOOL) pool, (DWORD) filter, (DWORD) mipFilter, 
			colorKey, NULL, NULL, &texture );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

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

	//TODO: Evaluate if there's a nicer way to handle the interop mess here with Fill.

	// Native callback used by FillTexture.
	void WINAPI NativeD3DXFill2D(D3DXVECTOR4 *out, CONST D3DXVECTOR2 *pTexCoord, CONST D3DXVECTOR2 *pTexelSize, LPVOID data)
	{
		Fill2DCallback^ callback = nullptr;									// Our callback.
		Vector2 coordinate = Vector2::Vector2(pTexCoord->x, pTexCoord->y);	// Managed coordinate.
		Vector2 size = Vector2::Vector2(pTexelSize->x, pTexelSize->y);		// Managed size.
		Vector4 result;														// Result vector.

		// Get the delegate.
		callback = safe_cast<Fill2DCallback^>(Marshal::GetDelegateForFunctionPointer(IntPtr::IntPtr(data), Fill2DCallback::typeid));			

		// Call the callback delegate.
		result = callback(coordinate, size);

		// Return the 4D vector.
		out->x = result.X;
		out->y = result.Y;
		out->z = result.Z;
		out->w = result.W;
	}

	/// <summary>
	/// Uses a user-provided function to fill each texel of each mip level of a given texture.
	/// </summary>
	/// <param name="callback">A function that uses the signature of the Fill2DCallback delegate.</param>
	void Texture::Fill(Fill2DCallback^ callback)
	{
		HRESULT hr;		// Error code.

		// Call the function.
		hr = D3DXFillTexture(TexturePointer, NativeD3DXFill2D, Marshal::GetFunctionPointerForDelegate(callback).ToPointer());

		GraphicsException::CheckHResult(hr);
	}

	LockedRect Texture::LockRectangle( int level, System::Drawing::Rectangle rect, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;
		RECT nativeRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };

		HRESULT hr = TexturePointer->LockRect( level, &lockedRect, &nativeRect, (DWORD) flags );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return LockedRect();

		LockedRect outRect;
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;

		outRect.Data = gcnew DataStream( lockedRect.pBits, 0, true, !readOnly );
		outRect.Pitch = lockedRect.Pitch;
		return outRect;
	}

	LockedRect Texture::LockRectangle( int level, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;

		HRESULT hr = TexturePointer->LockRect( level, &lockedRect, NULL, (DWORD) flags );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return LockedRect();

		LockedRect outRect;
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;

		outRect.Data = gcnew DataStream( lockedRect.pBits, 0, true, !readOnly );
		outRect.Pitch = lockedRect.Pitch;
		return outRect;
	}

	void Texture::UnlockRectangle( int level )
	{
		HRESULT hr = TexturePointer->UnlockRect( level );
		GraphicsException::CheckHResult( hr );
	}

	void Texture::AddDirtyRect( System::Drawing::Rectangle rect )
	{
		RECT nativeRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };
		HRESULT hr = TexturePointer->AddDirtyRect( &nativeRect );
		GraphicsException::CheckHResult( hr );
	}

	SurfaceDescription Texture::GetLevelDesc( int level )
	{
		SurfaceDescription desc;
		HRESULT hr = TexturePointer->GetLevelDesc( level, (D3DSURFACE_DESC*) &desc );
		GraphicsException::CheckHResult( hr );
		return desc;
	}

	Surface^ Texture::GetSurfaceLevel( int level )
	{
		IDirect3DSurface9* surface;
		HRESULT hr = TexturePointer->GetSurfaceLevel( level, &surface );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;
		return gcnew Surface( surface );
	}

	/// <summary>
	/// Function to save the texture to a stream.
	/// </summary>
	/// <param name="format">File format used to encode the image.</param>
	/// <returns>A graphics stream containing the texture data.</returns>
	DataStream^ Texture::SaveToStream(ImageFileFormat format)
	{
		HRESULT hr;															// Error code.
		ID3DXBuffer *buffer = NULL;											// Buffer to hold the encoded image.
		
		hr = D3DXSaveTextureToFileInMemory(&buffer, (D3DXIMAGE_FILEFORMAT)format, BaseTexturePointer, NULL);
		GraphicsException::CheckHResult(hr);

		// Clean up on failure.
		if (FAILED(hr))
		{
			if (buffer != NULL)
				buffer->Release();
			buffer = NULL;

			return nullptr;
		}

		return gcnew DataStream(buffer->GetBufferPointer(), 0, true, true);
	}

	/// <summary>
	/// Function to save the texture to a file.
	/// </summary>
	/// <param name="fileName">Filename and path for the texture.</param>
	/// <param name="format">File format used to encode the image.</param>
	void Texture::SaveToFile(String^ fileName, ImageFileFormat format)
	{
		HRESULT hr;															// Error code.
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars(fileName);		// Native name.

		hr = D3DXSaveTextureToFile(pinnedName, (D3DXIMAGE_FILEFORMAT)format, BaseTexturePointer, NULL);

		GraphicsException::CheckHResult(hr);
	}

	CubeTexture::CubeTexture( IDirect3DCubeTexture9* texture )
	{
		if( texture == NULL )
			throw gcnew ArgumentNullException( "texture" );

		m_Pointer = texture;
	}

	CubeTexture::CubeTexture( Device^ device, int edgeLength, int numLevels, Usage usage, Format format, Pool pool )
	{
		IDirect3DCubeTexture9* texture;
		HRESULT hr = device->InternalPointer->CreateCubeTexture( edgeLength, numLevels, (DWORD) usage,
			(D3DFORMAT) format, (D3DPOOL) pool, &texture, NULL );
		GraphicsException::CheckHResult( hr );

		m_Pointer = texture;
	}

	CubeTextureRequirements CubeTexture::CheckRequirements(Device^ device, int size,
		int numMipLevels, Usage usage, Format format, Pool pool)
	{
		CubeTextureRequirements result;					// Result.
		D3DFORMAT d3dFormat = (D3DFORMAT)format;	// Format.
		HRESULT hr;									// Error code.

		// Get texture requirements.
		hr = D3DXCheckCubeTextureRequirements(device->InternalPointer, (UINT *)&size, (UINT *)&numMipLevels,
			(DWORD)usage, (D3DFORMAT *)&d3dFormat, (D3DPOOL)pool);
		GraphicsException::CheckHResult(hr);

		// Return proposed values.
		result.Size = size;
		result.Format = format;
		result.NumOfMipLevels = numMipLevels;

		return result;
	}

	CubeTexture^ CubeTexture::FromMemory( Device^ device, array<Byte>^ memory, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DCubeTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXCreateCubeTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length, size, numLevels,
			(DWORD) usage, (D3DFORMAT) format, (D3DPOOL) pool, (DWORD) filter, (DWORD) mipFilter,
			(D3DCOLOR) colorKey, 0, 0, &texture );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew CubeTexture( texture );
	}

	CubeTexture^ CubeTexture::FromMemory( Device^ device, array<Byte>^ memory, Usage usage, Pool pool )
	{
		return CubeTexture::FromMemory( device, memory, D3DX::Default, D3DX::Default,
			usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	CubeTexture^ CubeTexture::FromMemory( Device^ device, array<Byte>^ memory )
	{
		return CubeTexture::FromMemory( device, memory, Usage::None, Pool::Managed );
	}

	CubeTexture^ CubeTexture::FromStream( Device^ device, Stream^ stream, int sizeBytes, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		array<Byte>^ data = Utils::ReadStream( stream, sizeBytes );
		return CubeTexture::FromMemory( device, data, size, numLevels, usage, format, pool, filter, mipFilter, colorKey );
	}

	CubeTexture^ CubeTexture::FromStream( Device^ device, Stream^ stream, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		return CubeTexture::FromStream( device, stream, 0, size, numLevels, usage, format, pool, filter, mipFilter, colorKey );
	}

	CubeTexture^ CubeTexture::FromStream( Device^ device, Stream^ stream, Usage usage, Pool pool )
	{
		return CubeTexture::FromStream( device, stream, D3DX::Default, D3DX::Default,
			usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	CubeTexture^ CubeTexture::FromStream( Device^ device, Stream^ stream )
	{
		return CubeTexture::FromStream( device, stream, Usage::None, Pool::Managed );
	}

	CubeTexture^ CubeTexture::FromFile( Device^ device, String^ fileName, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DCubeTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXCreateCubeTextureFromFileEx( device->InternalPointer, pinnedName, size, 
			numLevels, (DWORD) usage, (D3DFORMAT) format, (D3DPOOL) pool, (DWORD) filter, (DWORD) mipFilter, 
			colorKey, NULL, NULL, &texture );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

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

	LockedRect CubeTexture::LockRectangle( CubeMapFace face, int level, System::Drawing::Rectangle rect, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;
		RECT nativeRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };
		HRESULT hr = TexturePointer->LockRect( (D3DCUBEMAP_FACES) face, level, &lockedRect, &nativeRect, (DWORD) flags );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return LockedRect();

		LockedRect outRect;
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		outRect.Data = gcnew DataStream( lockedRect.pBits, 0, true, !readOnly );
		outRect.Pitch = lockedRect.Pitch;
		return outRect;
	}

	LockedRect CubeTexture::LockRectangle( CubeMapFace face, int level, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;
		HRESULT hr = TexturePointer->LockRect( (D3DCUBEMAP_FACES) face, level, &lockedRect, NULL, (DWORD) flags );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return LockedRect();

		LockedRect outRect;
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;

		outRect.Data = gcnew DataStream( lockedRect.pBits, 0, true, !readOnly );
		outRect.Pitch = lockedRect.Pitch;
		return outRect;
	}

	void CubeTexture::UnlockRectangle( CubeMapFace face, int level )
	{
		HRESULT hr = TexturePointer->UnlockRect( (D3DCUBEMAP_FACES) face, level );
		GraphicsException::CheckHResult( hr );
	}

	void CubeTexture::AddDirtyRect( CubeMapFace face, System::Drawing::Rectangle rect )
	{
		RECT nativeRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };
		HRESULT hr = TexturePointer->AddDirtyRect( (D3DCUBEMAP_FACES) face, &nativeRect );
		GraphicsException::CheckHResult( hr );
	}

	SurfaceDescription CubeTexture::GetLevelDesc( int level )
	{
		SurfaceDescription desc;
		HRESULT hr = TexturePointer->GetLevelDesc( level, (D3DSURFACE_DESC*) &desc );
		GraphicsException::CheckHResult( hr );
		return desc;
	}

	Surface^ CubeTexture::GetCubeMapSurface( CubeMapFace face, int level )
	{
		IDirect3DSurface9* surface;
		HRESULT hr = TexturePointer->GetCubeMapSurface( (D3DCUBEMAP_FACES) face, level, &surface );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;
		return gcnew Surface( surface );
	}


	VolumeTexture::VolumeTexture( IDirect3DVolumeTexture9* texture )
	{
		if( texture == NULL )
			throw gcnew ArgumentNullException( "texture" );

		m_Pointer = texture;
	}

	VolumeTexture::VolumeTexture( Device^ device, int width, int height, int depth, int numLevels, Usage usage, Format format, Pool pool )
	{
		IDirect3DVolumeTexture9* texture;
		HRESULT hr = device->InternalPointer->CreateVolumeTexture( width, height, depth, numLevels,
			(DWORD) usage, (D3DFORMAT) format, (D3DPOOL) pool, &texture, NULL );
		GraphicsException::CheckHResult( hr );

		m_Pointer = texture;
	}

	VolumeTextureRequirements VolumeTexture::CheckRequirements(Device^ device, int width, int height, int depth,
		int numMipLevels, Usage usage, Format format, Pool pool)
	{
		VolumeTextureRequirements result;					// Result.
		D3DFORMAT d3dFormat = (D3DFORMAT)format;	// Format.
		HRESULT hr;									// Error code.

		// Get texture requirements.
		hr = D3DXCheckVolumeTextureRequirements(device->InternalPointer, (UINT *)&width, (UINT *)&height, (UINT*) &depth,
			(UINT *)&numMipLevels, (DWORD)usage, (D3DFORMAT *)&d3dFormat, (D3DPOOL)pool);
		GraphicsException::CheckHResult(hr);

		// Return proposed values.
		result.Width = width;
		result.Height = height;
		result.Depth = depth;
		result.Format = format;
		result.NumOfMipLevels = numMipLevels;

		return result;
	}

	VolumeTexture^ VolumeTexture::FromMemory( Device^ device, array<Byte>^ memory, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DVolumeTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXCreateVolumeTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length,
			width, height, depth, numLevels, (DWORD) usage, (D3DFORMAT) format, (D3DPOOL) pool,
			(DWORD) filter, (DWORD) mipFilter, (D3DCOLOR) colorKey, 0, 0, &texture );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew VolumeTexture( texture );
	}

	VolumeTexture^ VolumeTexture::FromMemory( Device^ device, array<Byte>^ memory, Usage usage, Pool pool )
	{
		return VolumeTexture::FromMemory( device, memory, D3DX::Default, D3DX::Default, D3DX::Default, D3DX::Default,
			usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	VolumeTexture^ VolumeTexture::FromMemory( Device^ device, array<Byte>^ memory )
	{
		return VolumeTexture::FromMemory( device, memory, Usage::None, Pool::Managed );
	}

	VolumeTexture^ VolumeTexture::FromStream( Device^ device, Stream^ stream, int sizeBytes, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		array<Byte>^ data = Utils::ReadStream( stream, sizeBytes );
		return VolumeTexture::FromMemory( device, data, width, height, depth, numLevels,
			usage, format, pool, filter, mipFilter, colorKey );
	}

	VolumeTexture^ VolumeTexture::FromStream( Device^ device, Stream^ stream, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		return VolumeTexture::FromStream( device, stream, 0, width, height, depth,
			numLevels, usage, format, pool, filter, mipFilter, colorKey );
	}

	VolumeTexture^ VolumeTexture::FromStream( Device^ device, Stream^ stream, Usage usage, Pool pool )
	{
		return VolumeTexture::FromStream( device, stream, D3DX::Default, D3DX::Default, D3DX::Default,
			D3DX::Default, usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	VolumeTexture^ VolumeTexture::FromStream( Device^ device, Stream^ stream )
	{
		return VolumeTexture::FromStream( device, stream, Usage::None, Pool::Managed );
	}

	VolumeTexture^ VolumeTexture::FromFile( Device^ device, String^ fileName, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DVolumeTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXCreateVolumeTextureFromFileEx( device->InternalPointer, pinnedName, width, height,
			depth, numLevels, (DWORD) usage, (D3DFORMAT) format, (D3DPOOL) pool, (DWORD) filter,
			(DWORD) mipFilter, colorKey, NULL, NULL, &texture );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew VolumeTexture( texture );
	}

	VolumeTexture^ VolumeTexture::FromFile( Device^ device, String^ fileName, Usage usage, Pool pool )
	{
		return VolumeTexture::FromFile( device, fileName, D3DX::Default, D3DX::Default, D3DX::Default,
			D3DX::Default, usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	VolumeTexture^ VolumeTexture::FromFile( Device^ device, String^ fileName )
	{
		return VolumeTexture::FromFile( device, fileName, Usage::None, Pool::Managed );
	}

	LockedBox VolumeTexture::LockBox( int level, Box box, LockFlags flags )
	{
		D3DLOCKED_BOX lockedBox;
		HRESULT hr = TexturePointer->LockBox( level, &lockedBox, (D3DBOX*) &box, (DWORD) flags );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return LockedBox();

		LockedBox outBox;
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		outBox.Data = gcnew DataStream( lockedBox.pBits, 0, true, !readOnly );
		outBox.RowPitch = lockedBox.RowPitch;
		outBox.SlicePitch = lockedBox.SlicePitch;
		return outBox;
	}

	LockedBox VolumeTexture::LockBox( int level, LockFlags flags )
	{
		D3DLOCKED_BOX lockedBox;
		HRESULT hr = TexturePointer->LockBox( level, &lockedBox, NULL, (DWORD) flags );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return LockedBox();

		LockedBox outBox;
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		outBox.Data = gcnew DataStream( lockedBox.pBits, 0, true, !readOnly );
		outBox.RowPitch = lockedBox.RowPitch;
		outBox.SlicePitch = lockedBox.SlicePitch;
		return outBox;
	}

	void VolumeTexture::UnlockBox( int level )
	{
		HRESULT hr = TexturePointer->UnlockBox( level );
		GraphicsException::CheckHResult( hr );
	}

	void VolumeTexture::AddDirtyBox( Box box )
	{
		HRESULT hr = TexturePointer->AddDirtyBox( (D3DBOX*) &box );
		GraphicsException::CheckHResult( hr );
	}
}
}