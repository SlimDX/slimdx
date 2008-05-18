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
#include <vcclr.h>

#include "../DataStream.h"
#include "../ComObject.h"
#include "../Utilities.h"

#include "../math/Vector2.h"

#include "Device.h"
#include "D3DX.h"
#include "Texture.h"

#include "Direct3D9Exception.h"

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace Direct3D9
{
	Texture::Texture( IDirect3DTexture9* texture )
	{
		Construct(texture);
	}

	Texture::Texture( IntPtr texture )
	{
		Construct( texture, NativeInterface );
	}

	Texture::Texture( SlimDX::Direct3D9::Device^ device, int width, int height, int numLevels, Usage usage, Format format, Pool pool )
	{
		IDirect3DTexture9* texture;
		HRESULT hr = device->InternalPointer->CreateTexture( width, height, numLevels, static_cast<DWORD>( usage ), 
			static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), &texture, NULL );
		
		if( RECORD_D3D9( hr ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(texture);
		if( pool == Pool::Default )
			this->IsDefaultPool = true;
	}

	Texture^ Texture::FromPointer( IDirect3DTexture9* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		Texture^ tableEntry = safe_cast<Texture^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew Texture( pointer );
	}

	Texture^ Texture::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		Texture^ tableEntry = safe_cast<Texture^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew Texture( pointer );
	}

	TextureRequirements Texture::CheckRequirements(SlimDX::Direct3D9::Device^ device, int width, int height,
		int numMipLevels, Usage usage, Format format, Pool pool)
	{
		TextureRequirements result;					// Result.
		D3DFORMAT d3dFormat = static_cast<D3DFORMAT>( format );	// Format.
		HRESULT hr;									// Error code.

		// Get texture requirements.
		hr = D3DXCheckTextureRequirements(device->InternalPointer, reinterpret_cast<UINT*>( &width ), 
			reinterpret_cast<UINT*>( &height ), reinterpret_cast<UINT*>( &numMipLevels ), static_cast<DWORD>( usage ),
			&d3dFormat, static_cast<D3DPOOL>( pool ) );
		
		if( RECORD_D3D9(hr).IsFailure )
			return TextureRequirements();

		// Return proposed values.
		result.Width = width;
		result.Height = height;
		result.Format = static_cast<Format>( d3dFormat );
		result.MipLevelCount = numMipLevels;

		return result;
	}

	Texture^ Texture::FromMemory( SlimDX::Direct3D9::Device^ device, array<Byte>^ memory, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, 
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		IDirect3DTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		imageInformation = ImageInformation();
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		palette = gcnew array<PaletteEntry>( 256 );
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];

		HRESULT hr = D3DXCreateTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length, width,
			height, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ),
			static_cast<D3DCOLOR>( colorKey ), reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), 
			reinterpret_cast<PALETTEENTRY*>( pinnedPalette ), &texture );
		
		if( RECORD_D3D9(hr).IsFailure )
		{
			palette = nullptr;
			return nullptr;
		}

		Texture^ result = gcnew Texture( texture );
		if( pool == Pool::Default )
			result->IsDefaultPool = true;
		return result;
	}

	Texture^ Texture::FromMemory( SlimDX::Direct3D9::Device^ device, array<Byte>^ memory, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, 
		[Out] ImageInformation% imageInformation )
	{
		IDirect3DTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		imageInformation = ImageInformation();
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;

		HRESULT hr = D3DXCreateTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length, width,
			height, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ),
			static_cast<D3DCOLOR>( colorKey ), reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), 
			NULL, &texture );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		Texture^ result = gcnew Texture( texture );
		if( pool == Pool::Default )
			result->IsDefaultPool = true;
		return result;
	}

	Texture^ Texture::FromMemory( SlimDX::Direct3D9::Device^ device, array<Byte>^ memory, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXCreateTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length, width,
			height, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ),
			static_cast<D3DCOLOR>( colorKey ), 0, 0, &texture );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		Texture^ result = gcnew Texture( texture );
		if( pool == Pool::Default )
			result->IsDefaultPool = true;
		return result;
	}

	Texture^ Texture::FromMemory( SlimDX::Direct3D9::Device^ device, array<Byte>^ memory, Usage usage, Pool pool )
	{
		return Texture::FromMemory( device, memory, D3DX::Default, D3DX::Default, D3DX::Default,
			usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	Texture^ Texture::FromMemory( SlimDX::Direct3D9::Device^ device, array<Byte>^ memory )
	{
		return Texture::FromMemory( device, memory, Usage::None, Pool::Managed );
	}

	Texture^ Texture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream, int sizeBytes, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, sizeBytes );
		return Texture::FromMemory( device, data, width, height, numLevels, usage, format, pool, filter, 
			mipFilter, colorKey, imageInformation, palette );
	}

	Texture^ Texture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream, int sizeBytes, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, sizeBytes );
		return Texture::FromMemory( device, data, width, height, numLevels, usage, format, pool, filter, 
			mipFilter, colorKey, imageInformation );
	}

	Texture^ Texture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream, int sizeBytes, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, sizeBytes );
		return Texture::FromMemory( device, data, width, height, numLevels, usage, format, pool, filter, mipFilter, colorKey );
	}

	Texture^ Texture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		return Texture::FromStream( device, stream, 0, width, height, numLevels, usage, format, pool, filter, mipFilter, colorKey );
	}

	Texture^ Texture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream, Usage usage, Pool pool )
	{
		return Texture::FromStream( device, stream, D3DX::Default, D3DX::Default, D3DX::Default,
			usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	Texture^ Texture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream )
	{
		return Texture::FromStream( device, stream, Usage::None, Pool::Managed );
	}

	Texture^ Texture::FromFile( SlimDX::Direct3D9::Device^ device, String^ fileName, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		IDirect3DTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		imageInformation = ImageInformation();
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		palette = gcnew array<PaletteEntry>( 256 );
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];

		HRESULT hr = D3DXCreateTextureFromFileEx( device->InternalPointer, pinnedName, width, height, 
			numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), 
			colorKey, reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), reinterpret_cast<PALETTEENTRY*>( pinnedPalette ), &texture );
		
		if( RECORD_D3D9(hr).IsFailure )
		{
			palette = nullptr;
			return nullptr;
		}

		Texture^ result = gcnew Texture( texture );
		if( pool == Pool::Default )
			result->IsDefaultPool = true;
		return result;
	}

	Texture^ Texture::FromFile( SlimDX::Direct3D9::Device^ device, String^ fileName, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation )
	{
		IDirect3DTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;

		HRESULT hr = D3DXCreateTextureFromFileEx( device->InternalPointer, pinnedName, width, height, 
			numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), 
			colorKey, reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), NULL, &texture );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		Texture^ result = gcnew Texture( texture );
		if( pool == Pool::Default )
			result->IsDefaultPool = true;
		return result;
	}

	Texture^ Texture::FromFile( SlimDX::Direct3D9::Device^ device, String^ fileName, int width, int height, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXCreateTextureFromFileEx( device->InternalPointer, pinnedName, width, height, 
			numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), 
			colorKey, NULL, NULL, &texture );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		Texture^ result = gcnew Texture( texture );
		if( pool == Pool::Default )
			result->IsDefaultPool = true;
		return result;
	}

	Texture^ Texture::FromFile( SlimDX::Direct3D9::Device^ device, String^ fileName, Usage usage, Pool pool )
	{
		return Texture::FromFile( device, fileName, D3DX::Default, D3DX::Default, D3DX::Default,
			usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	Texture^ Texture::FromFile( SlimDX::Direct3D9::Device^ device, String^ fileName )
	{
		return Texture::FromFile( device, fileName, Usage::None, Pool::Managed );
	}

	Result Texture::ComputeNormalMap( Texture^ texture, Texture^ sourceTexture, array<PaletteEntry>^ palette, NormalMapFlags flags, Channel channel, float amplitude )
	{
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];

		HRESULT hr = D3DXComputeNormalMap( texture->InternalPointer, sourceTexture->InternalPointer, reinterpret_cast<const PALETTEENTRY*>( pinnedPalette ),
			static_cast<DWORD>( flags ), static_cast<DWORD>( channel ), amplitude );
		return RECORD_D3D9( hr );
	}

	Result Texture::ComputeNormalMap( Texture^ texture, Texture^ sourceTexture, NormalMapFlags flags, Channel channel, float amplitude )
	{
		HRESULT hr = D3DXComputeNormalMap( texture->InternalPointer, sourceTexture->InternalPointer, NULL,
			static_cast<DWORD>( flags ), static_cast<DWORD>( channel ), amplitude );
		return RECORD_D3D9( hr );
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
	Result Texture::Fill(Fill2DCallback^ callback)
	{
		HRESULT hr;		// Error code.

		// Call the function.
		hr = D3DXFillTexture(InternalPointer, NativeD3DXFill2D, Marshal::GetFunctionPointerForDelegate(callback).ToPointer());

		return RECORD_D3D9(hr);
	}

	Result Texture::Fill( TextureShader^ shader )
	{
		HRESULT hr = D3DXFillTextureTX( InternalPointer, shader->InternalPointer );
		return RECORD_D3D9( hr );
	}

	DataRectangle^ Texture::LockRectangle( int level, System::Drawing::Rectangle rect, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;
		RECT nativeRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };

		HRESULT hr = InternalPointer->LockRect( level, &lockedRect, &nativeRect, static_cast<DWORD>( flags ) );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;
		
		int lockedSize = lockedRect.Pitch * GetLevelDescription( level ).Height;
		
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		DataRectangle^ outRect = gcnew DataRectangle( lockedRect.Pitch, gcnew DataStream( lockedRect.pBits, lockedSize, true, !readOnly, false ) );
		return outRect;
	}

	DataRectangle^ Texture::LockRectangle( int level, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;

		HRESULT hr = InternalPointer->LockRect( level, &lockedRect, NULL, static_cast<DWORD>( flags ) );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;
		
		int lockedSize = lockedRect.Pitch * GetLevelDescription( level ).Height;
		
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		DataRectangle^ outRect = gcnew DataRectangle( lockedRect.Pitch, gcnew DataStream( lockedRect.pBits, lockedSize, true, !readOnly, false ) );
		return outRect;
	}

	Result Texture::UnlockRectangle( int level )
	{
		HRESULT hr = InternalPointer->UnlockRect( level );
		return RECORD_D3D9( hr );
	}

	Result Texture::AddDirtyRectangle()
	{
		HRESULT hr = InternalPointer->AddDirtyRect( NULL );
		return RECORD_D3D9( hr );
	}

	Result Texture::AddDirtyRectangle( System::Drawing::Rectangle rect )
	{
		RECT nativeRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };
		HRESULT hr = InternalPointer->AddDirtyRect( &nativeRect );
		return RECORD_D3D9( hr );
	}

	SurfaceDescription Texture::GetLevelDescription( int level )
	{
		SurfaceDescription description;
		HRESULT hr = InternalPointer->GetLevelDesc( level, reinterpret_cast<D3DSURFACE_DESC*>( &description ) );
		RECORD_D3D9( hr );
		return description;
	}

	Surface^ Texture::GetSurfaceLevel( int level )
	{
		IDirect3DSurface9* surface;
		HRESULT hr = InternalPointer->GetSurfaceLevel( level, &surface );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;
		return Surface::FromPointer( surface );
	}
}
}