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

#include "../DataStream.h"
#include "../DirectXObject.h"
#include "../Utils.h"

#include "Device.h"
#include "D3DX.h"
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
		buffer = Utils::ReadStream( stream, static_cast<int>( stream->Length ) );

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

		HRESULT hr = D3DXGetImageInfoFromFile( pinnedName, reinterpret_cast<D3DXIMAGE_INFO*>( &info ) );
		GraphicsException::CheckHResult( hr );

		return info;
	}

	ImageInformation ImageInformation::FromMemory( array<Byte>^ memory )
	{
		ImageInformation info;
		pin_ptr<const unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXGetImageInfoFromFileInMemory( pinnedMemory, memory->Length, reinterpret_cast<D3DXIMAGE_INFO*>( &info ) );
		GraphicsException::CheckHResult( hr );

		return info;
	}

	Texture::Texture( IDirect3DTexture9* texture )
	{
		if( texture == NULL )
			throw gcnew ArgumentNullException( "texture" );

		m_Pointer = texture;
	}

	Texture::Texture( IntPtr texture )
	{
		if( texture == IntPtr::Zero )
			throw gcnew ArgumentNullException( "texture" );

		void* pointer;
		IUnknown* unknown = static_cast<IUnknown*>( texture.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_IDirect3DTexture9, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<IDirect3DTexture9*>( pointer );
	}

	Texture::Texture( Device^ device, int width, int height, int numLevels, Usage usage, Format format, Pool pool )
	{
		IDirect3DTexture9* texture;
		HRESULT hr = device->InternalPointer->CreateTexture( width, height, numLevels, static_cast<DWORD>( usage ), 
			static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), &texture, NULL );
		GraphicsException::CheckHResult( hr );

		m_Pointer = texture;
	}

	TextureRequirements Texture::CheckRequirements(Device^ device, int width, int height,
		int numMipLevels, Usage usage, Format format, Pool pool)
	{
		TextureRequirements result;					// Result.
		D3DFORMAT d3dFormat = static_cast<D3DFORMAT>( format );	// Format.
		HRESULT hr;									// Error code.

		// Get texture requirements.
		hr = D3DXCheckTextureRequirements(device->InternalPointer, reinterpret_cast<UINT*>( &width ), 
			reinterpret_cast<UINT*>( &height ), reinterpret_cast<UINT*>( &numMipLevels ), static_cast<DWORD>( usage ),
			&d3dFormat, static_cast<D3DPOOL>( pool ) );
		GraphicsException::CheckHResult(hr);

		// Return proposed values.
		result.Width = width;
		result.Height = height;
		result.Format = static_cast<Format>( d3dFormat );
		result.MipLevelCount = numMipLevels;

		return result;
	}

	Texture^ Texture::FromMemory( Device^ device, array<Byte>^ memory, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, 
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		IDirect3DTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];

		HRESULT hr = D3DXCreateTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length, width,
			height, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ),
			static_cast<D3DCOLOR>( colorKey ), reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), 
			reinterpret_cast<PALETTEENTRY*>( pinnedPalette ), &texture );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			palette = nullptr;
			return nullptr;
		}

		return gcnew Texture( texture );
	}

	Texture^ Texture::FromMemory( Device^ device, array<Byte>^ memory, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, 
		[Out] ImageInformation% imageInformation )
	{
		IDirect3DTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;

		HRESULT hr = D3DXCreateTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length, width,
			height, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ),
			static_cast<D3DCOLOR>( colorKey ), reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), 
			NULL, &texture );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Texture( texture );
	}

	Texture^ Texture::FromMemory( Device^ device, array<Byte>^ memory, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXCreateTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length, width,
			height, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ),
			static_cast<D3DCOLOR>( colorKey ), 0, 0, &texture );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

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
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		array<Byte>^ data = Utils::ReadStream( stream, sizeBytes );
		return Texture::FromMemory( device, data, width, height, numLevels, usage, format, pool, filter, 
			mipFilter, colorKey, imageInformation, palette );
	}

	Texture^ Texture::FromStream( Device^ device, Stream^ stream, int sizeBytes, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation )
	{
		array<Byte>^ data = Utils::ReadStream( stream, sizeBytes );
		return Texture::FromMemory( device, data, width, height, numLevels, usage, format, pool, filter, 
			mipFilter, colorKey, imageInformation );
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
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		IDirect3DTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];

		HRESULT hr = D3DXCreateTextureFromFileEx( device->InternalPointer, pinnedName, width, height, 
			numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), 
			colorKey, reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), reinterpret_cast<PALETTEENTRY*>( pinnedPalette ), &texture );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			palette = nullptr;
			return nullptr;
		}

		return gcnew Texture( texture );
	}

	Texture^ Texture::FromFile( Device^ device, String^ fileName, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation )
	{
		IDirect3DTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;

		HRESULT hr = D3DXCreateTextureFromFileEx( device->InternalPointer, pinnedName, width, height, 
			numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), 
			colorKey, reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), NULL, &texture );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew Texture( texture );
	}

	Texture^ Texture::FromFile( Device^ device, String^ fileName, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXCreateTextureFromFileEx( device->InternalPointer, pinnedName, width, height, 
			numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), 
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

	void Texture::ComputeNormalMap( Texture^ texture, Texture^ sourceTexture, array<PaletteEntry>^ palette, NormalMapFlags flags, Channel channel, float amplitude )
	{
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];

		HRESULT hr = D3DXComputeNormalMap( texture->TexturePointer, sourceTexture->TexturePointer, reinterpret_cast<const PALETTEENTRY*>( pinnedPalette ),
			static_cast<DWORD>( flags ), static_cast<DWORD>( channel ), amplitude );
		GraphicsException::CheckHResult( hr );
	}

	void Texture::ComputeNormalMap( Texture^ texture, Texture^ sourceTexture, NormalMapFlags flags, Channel channel, float amplitude )
	{
		HRESULT hr = D3DXComputeNormalMap( texture->TexturePointer, sourceTexture->TexturePointer, NULL,
			static_cast<DWORD>( flags ), static_cast<DWORD>( channel ), amplitude );
		GraphicsException::CheckHResult( hr );
	}

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

	// Native callback used by FillTexture.
	void WINAPI NativeD3DXFill3D(D3DXVECTOR4 *out, CONST D3DXVECTOR3 *pTexCoord, CONST D3DXVECTOR3 *pTexelSize, LPVOID data)
	{
		Fill3DCallback^ callback = nullptr;									// Our callback.
		Vector3 coordinate = Vector3(pTexCoord->x, pTexCoord->y, pTexCoord->z);			// Managed coordinate.
		Vector3 size = Vector3(pTexelSize->x, pTexelSize->y, pTexelSize->z);				// Managed size.
		Vector4 result;														// Result vector.

		// Get the delegate.
		callback = safe_cast<Fill3DCallback^>(Marshal::GetDelegateForFunctionPointer(IntPtr::IntPtr(data), Fill3DCallback::typeid));			

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

	void Texture::Fill( TextureShader^ shader )
	{
		HRESULT hr = D3DXFillTextureTX( TexturePointer, shader->InternalPointer );
		GraphicsException::CheckHResult( hr );
	}

	LockedRect Texture::LockRectangle( int level, System::Drawing::Rectangle rect, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;
		RECT nativeRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };

		HRESULT hr = TexturePointer->LockRect( level, &lockedRect, &nativeRect, static_cast<DWORD>( flags ) );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return LockedRect();
		
		int lockedSize = lockedRect.Pitch * GetLevelDescription( level ).Height;
		
		LockedRect outRect;
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;

		outRect.Data = gcnew DataStream( lockedRect.pBits, lockedSize, true, !readOnly, false );
		outRect.Pitch = lockedRect.Pitch;
		return outRect;
	}

	LockedRect Texture::LockRectangle( int level, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;

		HRESULT hr = TexturePointer->LockRect( level, &lockedRect, NULL, static_cast<DWORD>( flags ) );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return LockedRect();
		
		int lockedSize = lockedRect.Pitch * GetLevelDescription( level ).Height;
		
		LockedRect outRect;
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;

		outRect.Data = gcnew DataStream( lockedRect.pBits, lockedSize, true, !readOnly, false );
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

	SurfaceDescription Texture::GetLevelDescription( int level )
	{
		SurfaceDescription desc;
		HRESULT hr = TexturePointer->GetLevelDesc( level, reinterpret_cast<D3DSURFACE_DESC*>( &desc ) );
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

	CubeTexture::CubeTexture( IDirect3DCubeTexture9* texture )
	{
		if( texture == NULL )
			throw gcnew ArgumentNullException( "texture" );

		m_Pointer = texture;
	}

	CubeTexture::CubeTexture( IntPtr cubeTexture )
	{
		if( cubeTexture == IntPtr::Zero )
			throw gcnew ArgumentNullException( "cubeTexture" );

		void* pointer;
		IUnknown* unknown = static_cast<IUnknown*>( cubeTexture.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_IDirect3DCubeTexture9, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<IDirect3DCubeTexture9*>( pointer );
	}

	CubeTexture::CubeTexture( Device^ device, int edgeLength, int numLevels, Usage usage, Format format, Pool pool )
	{
		IDirect3DCubeTexture9* texture;
		HRESULT hr = device->InternalPointer->CreateCubeTexture( edgeLength, numLevels, static_cast<DWORD>( usage ),
			static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), &texture, NULL );
		GraphicsException::CheckHResult( hr );

		m_Pointer = texture;
	}

	CubeTextureRequirements CubeTexture::CheckRequirements(Device^ device, int size,
		int numMipLevels, Usage usage, Format format, Pool pool)
	{
		CubeTextureRequirements result;					// Result.
		D3DFORMAT d3dFormat = static_cast<D3DFORMAT>( format );	// Format.
		HRESULT hr;									// Error code.

		// Get texture requirements.
		hr = D3DXCheckCubeTextureRequirements(device->InternalPointer, reinterpret_cast<UINT*>( &size ), 
			reinterpret_cast<UINT*>( &numMipLevels ),
			static_cast<DWORD>( usage ), reinterpret_cast<D3DFORMAT*>( &d3dFormat ), static_cast<D3DPOOL>( pool ) );
		GraphicsException::CheckHResult(hr);

		// Return proposed values.
		result.Size = size;
		result.Format = format;
		result.MipLevelCount = numMipLevels;

		return result;
	}

	CubeTexture^ CubeTexture::FromMemory( Device^ device, array<Byte>^ memory, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		IDirect3DCubeTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];

		HRESULT hr = D3DXCreateCubeTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length, size, numLevels,
			static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ),
			static_cast<D3DCOLOR>( colorKey ), reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), 
			reinterpret_cast<PALETTEENTRY*>( pinnedPalette ), &texture );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			palette = nullptr;
			return nullptr;
		}

		return gcnew CubeTexture( texture );
	}

	CubeTexture^ CubeTexture::FromMemory( Device^ device, array<Byte>^ memory, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation )
	{
		IDirect3DCubeTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;

		HRESULT hr = D3DXCreateCubeTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length, size, numLevels,
			static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ),
			static_cast<D3DCOLOR>( colorKey ), reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), 
			NULL, &texture );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew CubeTexture( texture );
	}

	CubeTexture^ CubeTexture::FromMemory( Device^ device, array<Byte>^ memory, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DCubeTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXCreateCubeTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length, size, numLevels,
			static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ),
			static_cast<D3DCOLOR>( colorKey ), 0, 0, &texture );
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
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		array<Byte>^ data = Utils::ReadStream( stream, sizeBytes );
		return CubeTexture::FromMemory( device, data, size, numLevels, usage, format, pool, filter, mipFilter, 
			colorKey, imageInformation, palette );
	}

	CubeTexture^ CubeTexture::FromStream( Device^ device, Stream^ stream, int sizeBytes, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation )
	{
		array<Byte>^ data = Utils::ReadStream( stream, sizeBytes );
		return CubeTexture::FromMemory( device, data, size, numLevels, usage, format, pool, filter, mipFilter, 
			colorKey, imageInformation );
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
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		IDirect3DCubeTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];

		HRESULT hr = D3DXCreateCubeTextureFromFileEx( device->InternalPointer, pinnedName, size, 
			numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), 
			colorKey, reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), reinterpret_cast<PALETTEENTRY*>( pinnedPalette ), &texture );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			palette = nullptr;
			return nullptr;
		}

		return gcnew CubeTexture( texture );
	}

	CubeTexture^ CubeTexture::FromFile( Device^ device, String^ fileName, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation )
	{
		IDirect3DCubeTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;

		HRESULT hr = D3DXCreateCubeTextureFromFileEx( device->InternalPointer, pinnedName, size, 
			numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), 
			colorKey, reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), NULL, &texture );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew CubeTexture( texture );
	}

	CubeTexture^ CubeTexture::FromFile( Device^ device, String^ fileName, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DCubeTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXCreateCubeTextureFromFileEx( device->InternalPointer, pinnedName, size, 
			numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), 
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
		HRESULT hr = TexturePointer->LockRect( static_cast<D3DCUBEMAP_FACES>( face ), level, &lockedRect, &nativeRect, static_cast<DWORD>( flags ) );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return LockedRect();
		
		int lockedSize = lockedRect.Pitch * GetLevelDescription( level ).Height;
		
		LockedRect outRect;
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		outRect.Data = gcnew DataStream( lockedRect.pBits, lockedSize, true, !readOnly, false );
		outRect.Pitch = lockedRect.Pitch;
		return outRect;
	}

	LockedRect CubeTexture::LockRectangle( CubeMapFace face, int level, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;
		HRESULT hr = TexturePointer->LockRect( static_cast<D3DCUBEMAP_FACES>( face ), level, &lockedRect, NULL, static_cast<DWORD>( flags ) );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return LockedRect();
		
		int lockedSize = lockedRect.Pitch * GetLevelDescription( level ).Height;
		
		LockedRect outRect;
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;

		outRect.Data = gcnew DataStream( lockedRect.pBits, lockedSize, true, !readOnly, false );
		outRect.Pitch = lockedRect.Pitch;
		return outRect;
	}

	void CubeTexture::UnlockRectangle( CubeMapFace face, int level )
	{
		HRESULT hr = TexturePointer->UnlockRect( static_cast<D3DCUBEMAP_FACES>( face ), level );
		GraphicsException::CheckHResult( hr );
	}

	void CubeTexture::AddDirtyRect( CubeMapFace face, System::Drawing::Rectangle rect )
	{
		RECT nativeRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };
		HRESULT hr = TexturePointer->AddDirtyRect( static_cast<D3DCUBEMAP_FACES>( face ), &nativeRect );
		GraphicsException::CheckHResult( hr );
	}

	SurfaceDescription CubeTexture::GetLevelDescription( int level )
	{
		SurfaceDescription desc;
		HRESULT hr = TexturePointer->GetLevelDesc( level, reinterpret_cast<D3DSURFACE_DESC*>( &desc ) );
		GraphicsException::CheckHResult( hr );
		return desc;
	}

	Surface^ CubeTexture::GetCubeMapSurface( CubeMapFace face, int level )
	{
		IDirect3DSurface9* surface;
		HRESULT hr = TexturePointer->GetCubeMapSurface( static_cast<D3DCUBEMAP_FACES>( face ), level, &surface );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;
		return gcnew Surface( surface );
	}

	void CubeTexture::Fill(Fill3DCallback^ callback)
	{
		HRESULT hr;		// Error code.

		// Call the function.
		hr = D3DXFillCubeTexture(TexturePointer, NativeD3DXFill3D, Marshal::GetFunctionPointerForDelegate(callback).ToPointer());

		GraphicsException::CheckHResult(hr);
	}

	void CubeTexture::Fill( TextureShader^ shader )
	{
		HRESULT hr = D3DXFillCubeTextureTX( TexturePointer, shader->InternalPointer );
		GraphicsException::CheckHResult( hr );
	}

	VolumeTexture::VolumeTexture( IDirect3DVolumeTexture9* texture )
	{
		if( texture == NULL )
			throw gcnew ArgumentNullException( "texture" );

		m_Pointer = texture;
	}

	VolumeTexture::VolumeTexture( IntPtr volumeTexture )
	{
		if( volumeTexture == IntPtr::Zero )
			throw gcnew ArgumentNullException( "volumeTexture" );

		void* pointer;
		IUnknown* unknown = static_cast<IUnknown*>( volumeTexture.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_IDirect3DVolumeTexture9, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<IDirect3DVolumeTexture9*>( pointer );
	}

	VolumeTexture::VolumeTexture( Device^ device, int width, int height, int depth, int numLevels, Usage usage, Format format, Pool pool )
	{
		IDirect3DVolumeTexture9* texture;
		HRESULT hr = device->InternalPointer->CreateVolumeTexture( width, height, depth, numLevels,
			static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), &texture, NULL );
		GraphicsException::CheckHResult( hr );

		m_Pointer = texture;
	}

	VolumeTextureRequirements VolumeTexture::CheckRequirements(Device^ device, int width, int height, int depth,
		int numMipLevels, Usage usage, Format format, Pool pool)
	{
		VolumeTextureRequirements result;					// Result.
		D3DFORMAT d3dFormat = static_cast<D3DFORMAT>( format );	// Format.
		HRESULT hr;									// Error code.

		// Get texture requirements.
		hr = D3DXCheckVolumeTextureRequirements(device->InternalPointer,
			reinterpret_cast<UINT*>( &width ),
			reinterpret_cast<UINT*>( &height ),
			reinterpret_cast<UINT*>( &depth ),
			reinterpret_cast<UINT*>( &numMipLevels ),
			static_cast<DWORD>( usage ),
			&d3dFormat,
			static_cast<D3DPOOL>( pool ) );
		GraphicsException::CheckHResult(hr);

		// Return proposed values.
		result.Width = width;
		result.Height = height;
		result.Depth = depth;
		result.Format = format;
		result.MipLevelCount = numMipLevels;

		return result;
	}

	VolumeTexture^ VolumeTexture::FromMemory( Device^ device, array<Byte>^ memory, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		IDirect3DVolumeTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];

		HRESULT hr = D3DXCreateVolumeTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length,
			width, height, depth, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ),
			static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), static_cast<D3DCOLOR>( colorKey ), 
			reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), reinterpret_cast<PALETTEENTRY*>( pinnedPalette ), &texture );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			palette = nullptr;
			return nullptr;
		}

		return gcnew VolumeTexture( texture );
	}

	VolumeTexture^ VolumeTexture::FromMemory( Device^ device, array<Byte>^ memory, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation )
	{
		IDirect3DVolumeTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;

		HRESULT hr = D3DXCreateVolumeTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length,
			width, height, depth, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ),
			static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), static_cast<D3DCOLOR>( colorKey ), 
			reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), NULL, &texture );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew VolumeTexture( texture );
	}

	VolumeTexture^ VolumeTexture::FromMemory( Device^ device, array<Byte>^ memory, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DVolumeTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXCreateVolumeTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length,
			width, height, depth, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ),
			static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), static_cast<D3DCOLOR>( colorKey ), 0, 0, &texture );
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
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		array<Byte>^ data = Utils::ReadStream( stream, sizeBytes );
		return VolumeTexture::FromMemory( device, data, width, height, depth, numLevels,
			usage, format, pool, filter, mipFilter, colorKey, imageInformation, palette );
	}

	VolumeTexture^ VolumeTexture::FromStream( Device^ device, Stream^ stream, int sizeBytes, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation )
	{
		array<Byte>^ data = Utils::ReadStream( stream, sizeBytes );
		return VolumeTexture::FromMemory( device, data, width, height, depth, numLevels,
			usage, format, pool, filter, mipFilter, colorKey, imageInformation );
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
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		IDirect3DVolumeTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];

		HRESULT hr = D3DXCreateVolumeTextureFromFileEx( device->InternalPointer, pinnedName, width, height,
			depth, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ),
			static_cast<DWORD>( mipFilter ), colorKey, reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), 
			reinterpret_cast<PALETTEENTRY*>( pinnedPalette ), &texture );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			palette = nullptr;
			return nullptr;
		}

		return gcnew VolumeTexture( texture );
	}

	VolumeTexture^ VolumeTexture::FromFile( Device^ device, String^ fileName, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation )
	{
		IDirect3DVolumeTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;

		HRESULT hr = D3DXCreateVolumeTextureFromFileEx( device->InternalPointer, pinnedName, width, height,
			depth, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ),
			static_cast<DWORD>( mipFilter ), colorKey, reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), 
			NULL, &texture );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew VolumeTexture( texture );
	}

	VolumeTexture^ VolumeTexture::FromFile( Device^ device, String^ fileName, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DVolumeTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXCreateVolumeTextureFromFileEx( device->InternalPointer, pinnedName, width, height,
			depth, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ),
			static_cast<DWORD>( mipFilter ), colorKey, NULL, NULL, &texture );
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
		HRESULT hr = TexturePointer->LockBox( level, &lockedBox, reinterpret_cast<D3DBOX*>( &box ),
			static_cast<DWORD>( flags ) );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return LockedBox();
		
		int lockedSize = lockedBox.RowPitch * lockedBox.SlicePitch * GetLevelDescription( level ).Height;
		
		LockedBox outBox;
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		outBox.Data = gcnew DataStream( lockedBox.pBits, lockedSize, true, !readOnly, false );
		outBox.RowPitch = lockedBox.RowPitch;
		outBox.SlicePitch = lockedBox.SlicePitch;
		return outBox;
	}

	LockedBox VolumeTexture::LockBox( int level, LockFlags flags )
	{
		D3DLOCKED_BOX lockedBox;
		HRESULT hr = TexturePointer->LockBox( level, &lockedBox, NULL, static_cast<DWORD>( flags ) );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return LockedBox();

		LockedBox outBox;
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		outBox.Data = gcnew DataStream( lockedBox.pBits, 0, true, !readOnly, false );
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
		HRESULT hr = TexturePointer->AddDirtyBox( reinterpret_cast<D3DBOX*>( &box ) );
		GraphicsException::CheckHResult( hr );
	}
	
	VolumeDescription VolumeTexture::GetLevelDescription( int level )
	{
		D3DVOLUME_DESC desc;
		HRESULT hr = TexturePointer->GetLevelDesc( level, &desc );
		GraphicsException::CheckHResult( hr );
		
		VolumeDescription outDesc;
		outDesc.Format = static_cast<Format>( desc.Format );
		outDesc.Type = static_cast<SlimDX::Direct3D9::ResourceType>( desc.Type );
		outDesc.Usage = static_cast<Usage>( desc.Usage );
		outDesc.Pool = static_cast<Pool>( desc.Pool );
		outDesc.Width = desc.Width;
		outDesc.Height = desc.Height;
		outDesc.Depth = desc.Depth;
		
		return outDesc;
	}

	Volume^ VolumeTexture::GetVolumeLevel( int level )
	{
		IDirect3DVolume9 *result;

		HRESULT hr = TexturePointer->GetVolumeLevel( level, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Volume( result );
	}

	void VolumeTexture::Fill(Fill3DCallback^ callback)
	{
		HRESULT hr;		// Error code.

		// Call the function.
		hr = D3DXFillVolumeTexture(TexturePointer, NativeD3DXFill3D, Marshal::GetFunctionPointerForDelegate(callback).ToPointer());

		GraphicsException::CheckHResult(hr);
	}

	void VolumeTexture::Fill( TextureShader^ shader )
	{
		HRESULT hr = D3DXFillVolumeTextureTX( TexturePointer, shader->InternalPointer );
		GraphicsException::CheckHResult( hr );
	}
}
}