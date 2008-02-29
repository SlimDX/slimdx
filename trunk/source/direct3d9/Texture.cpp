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
	bool ImageInformation::operator == ( ImageInformation left, ImageInformation right )
	{
		return ImageInformation::Equals( left, right );
	}

	bool ImageInformation::operator != ( ImageInformation left, ImageInformation right )
	{
		return !ImageInformation::Equals( left, right );
	}

	int ImageInformation::GetHashCode()
	{
		return Width.GetHashCode() + Height.GetHashCode() + Depth.GetHashCode()
			 + MipLevels.GetHashCode() + Format.GetHashCode() + ResourceType.GetHashCode()
			 + ImageFileFormat.GetHashCode();
	}

	bool ImageInformation::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<ImageInformation>( value ) );
	}

	bool ImageInformation::Equals( ImageInformation value )
	{
		return ( Width == value.Width && Height == value.Height && Depth == value.Depth
			 && MipLevels == value.MipLevels && Format == value.Format && ResourceType == value.ResourceType
			 && ImageFileFormat == value.ImageFileFormat );
	}

	bool ImageInformation::Equals( ImageInformation% value1, ImageInformation% value2 )
	{
		return ( value1.Width == value2.Width && value1.Height == value2.Height && value1.Depth == value2.Depth
			 && value1.MipLevels == value2.MipLevels && value1.Format == value2.Format && value1.ResourceType == value2.ResourceType
			 && value1.ImageFileFormat == value2.ImageFileFormat );
	}

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
		buffer = Utilities::ReadStream( stream, static_cast<int>( stream->Length ) );

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
		RECORD_D3D9( hr );

		return info;
	}

	ImageInformation ImageInformation::FromMemory( array<Byte>^ memory )
	{
		ImageInformation info;
		pin_ptr<const unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXGetImageInfoFromFileInMemory( pinnedMemory, memory->Length, reinterpret_cast<D3DXIMAGE_INFO*>( &info ) );
		RECORD_D3D9( hr );

		return info;
	}

	bool TextureRequirements::operator == ( TextureRequirements left, TextureRequirements right )
	{
		return TextureRequirements::Equals( left, right );
	}

	bool TextureRequirements::operator != ( TextureRequirements left, TextureRequirements right )
	{
		return !TextureRequirements::Equals( left, right );
	}

	int TextureRequirements::GetHashCode()
	{
		return Width.GetHashCode() + Height.GetHashCode() + Format.GetHashCode()
			 + MipLevelCount.GetHashCode();
	}

	bool TextureRequirements::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<TextureRequirements>( value ) );
	}

	bool TextureRequirements::Equals( TextureRequirements value )
	{
		return ( Width == value.Width && Height == value.Height && Format == value.Format
			 && MipLevelCount == value.MipLevelCount );
	}

	bool TextureRequirements::Equals( TextureRequirements% value1, TextureRequirements% value2 )
	{
		return ( value1.Width == value2.Width && value1.Height == value2.Height && value1.Format == value2.Format
			 && value1.MipLevelCount == value2.MipLevelCount );
	}

	bool CubeTextureRequirements::operator == ( CubeTextureRequirements left, CubeTextureRequirements right )
	{
		return CubeTextureRequirements::Equals( left, right );
	}

	bool CubeTextureRequirements::operator != ( CubeTextureRequirements left, CubeTextureRequirements right )
	{
		return !CubeTextureRequirements::Equals( left, right );
	}

	int CubeTextureRequirements::GetHashCode()
	{
		return Size.GetHashCode() + Format.GetHashCode() + MipLevelCount.GetHashCode();
	}

	bool CubeTextureRequirements::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<CubeTextureRequirements>( value ) );
	}

	bool CubeTextureRequirements::Equals( CubeTextureRequirements value )
	{
		return ( Size == value.Size && Format == value.Format && MipLevelCount == value.MipLevelCount );
	}

	bool CubeTextureRequirements::Equals( CubeTextureRequirements% value1, CubeTextureRequirements% value2 )
	{
		return ( value1.Size == value2.Size && value1.Format == value2.Format && value1.MipLevelCount == value2.MipLevelCount );
	}

	bool VolumeTextureRequirements::operator == ( VolumeTextureRequirements left, VolumeTextureRequirements right )
	{
		return VolumeTextureRequirements::Equals( left, right );
	}

	bool VolumeTextureRequirements::operator != ( VolumeTextureRequirements left, VolumeTextureRequirements right )
	{
		return !VolumeTextureRequirements::Equals( left, right );
	}

	int VolumeTextureRequirements::GetHashCode()
	{
		return Width.GetHashCode() + Height.GetHashCode() + Depth.GetHashCode()
			 + Format.GetHashCode() + MipLevelCount.GetHashCode();
	}

	bool VolumeTextureRequirements::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<VolumeTextureRequirements>( value ) );
	}

	bool VolumeTextureRequirements::Equals( VolumeTextureRequirements value )
	{
		return ( Width == value.Width && Height == value.Height && Depth == value.Depth
			 && Format == value.Format && MipLevelCount == value.MipLevelCount );
	}

	bool VolumeTextureRequirements::Equals( VolumeTextureRequirements% value1, VolumeTextureRequirements% value2 )
	{
		return ( value1.Width == value2.Width && value1.Height == value2.Height && value1.Depth == value2.Depth
			 && value1.Format == value2.Format && value1.MipLevelCount == value2.MipLevelCount );
	}

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
			ObjectTable::FlagAsDefaultPool( this );
	}

	Texture^ Texture::FromPointer( IDirect3DTexture9* pointer )
	{
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
			ObjectTable::FlagAsDefaultPool( result );
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
			ObjectTable::FlagAsDefaultPool( result );
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
			ObjectTable::FlagAsDefaultPool( result );
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
			ObjectTable::FlagAsDefaultPool( result );
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
			ObjectTable::FlagAsDefaultPool( result );
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
			ObjectTable::FlagAsDefaultPool( result );
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

	Result Texture::AddDirtyRect( System::Drawing::Rectangle rect )
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

	CubeTexture::CubeTexture( IDirect3DCubeTexture9* texture )
	{
		Construct(texture);
	}

	CubeTexture::CubeTexture( IntPtr cubeTexture )
	{
		Construct( cubeTexture, NativeInterface );
	}

	CubeTexture::CubeTexture( SlimDX::Direct3D9::Device^ device, int edgeLength, int numLevels, Usage usage, Format format, Pool pool )
	{
		IDirect3DCubeTexture9* texture;
		HRESULT hr = device->InternalPointer->CreateCubeTexture( edgeLength, numLevels, static_cast<DWORD>( usage ),
			static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), &texture, NULL );
		
		if( RECORD_D3D9(hr).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(texture);
		if( pool == Pool::Default )
			ObjectTable::FlagAsDefaultPool( this );
	}

	CubeTexture^ CubeTexture::FromPointer( IDirect3DCubeTexture9* pointer )
	{
		CubeTexture^ tableEntry = safe_cast<CubeTexture^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew CubeTexture( pointer );
	}

	CubeTexture^ CubeTexture::FromPointer( IntPtr pointer )
	{
		CubeTexture^ tableEntry = safe_cast<CubeTexture^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew CubeTexture( pointer );
	}

	CubeTextureRequirements CubeTexture::CheckRequirements(SlimDX::Direct3D9::Device^ device, int size,
		int numMipLevels, Usage usage, Format format, Pool pool)
	{
		CubeTextureRequirements result;					// Result.
		D3DFORMAT d3dFormat = static_cast<D3DFORMAT>( format );	// Format.
		HRESULT hr;									// Error code.

		// Get texture requirements.
		hr = D3DXCheckCubeTextureRequirements(device->InternalPointer, reinterpret_cast<UINT*>( &size ), 
			reinterpret_cast<UINT*>( &numMipLevels ),
			static_cast<DWORD>( usage ), reinterpret_cast<D3DFORMAT*>( &d3dFormat ), static_cast<D3DPOOL>( pool ) );
		
		if( RECORD_D3D9(hr).IsFailure )
			return CubeTextureRequirements();

		// Return proposed values.
		result.Size = size;
		result.Format = format;
		result.MipLevelCount = numMipLevels;

		return result;
	}

	CubeTexture^ CubeTexture::FromMemory( SlimDX::Direct3D9::Device^ device, array<Byte>^ memory, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		IDirect3DCubeTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		imageInformation = ImageInformation();
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		palette = gcnew array<PaletteEntry>( 256 );
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];

		HRESULT hr = D3DXCreateCubeTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length, size, numLevels,
			static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ),
			static_cast<D3DCOLOR>( colorKey ), reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), 
			reinterpret_cast<PALETTEENTRY*>( pinnedPalette ), &texture );
		
		if( RECORD_D3D9(hr).IsFailure )
		{
			palette = nullptr;
			return nullptr;
		}

		CubeTexture^ result = gcnew CubeTexture( texture );
		if( pool == Pool::Default )
			ObjectTable::FlagAsDefaultPool( result );
		return result;
	}

	CubeTexture^ CubeTexture::FromMemory( SlimDX::Direct3D9::Device^ device, array<Byte>^ memory, int size, int numLevels,
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
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		CubeTexture^ result = gcnew CubeTexture( texture );
		if( pool == Pool::Default )
			ObjectTable::FlagAsDefaultPool( result );
		return result;
	}

	CubeTexture^ CubeTexture::FromMemory( SlimDX::Direct3D9::Device^ device, array<Byte>^ memory, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DCubeTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXCreateCubeTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length, size, numLevels,
			static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ),
			static_cast<D3DCOLOR>( colorKey ), 0, 0, &texture );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		CubeTexture^ result = gcnew CubeTexture( texture );
		if( pool == Pool::Default )
			ObjectTable::FlagAsDefaultPool( result );
		return result;
	}

	CubeTexture^ CubeTexture::FromMemory( SlimDX::Direct3D9::Device^ device, array<Byte>^ memory, Usage usage, Pool pool )
	{
		return CubeTexture::FromMemory( device, memory, D3DX::Default, D3DX::Default,
			usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	CubeTexture^ CubeTexture::FromMemory( SlimDX::Direct3D9::Device^ device, array<Byte>^ memory )
	{
		return CubeTexture::FromMemory( device, memory, Usage::None, Pool::Managed );
	}

	CubeTexture^ CubeTexture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream, int sizeBytes, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, sizeBytes );
		return CubeTexture::FromMemory( device, data, size, numLevels, usage, format, pool, filter, mipFilter, 
			colorKey, imageInformation, palette );
	}

	CubeTexture^ CubeTexture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream, int sizeBytes, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, sizeBytes );
		return CubeTexture::FromMemory( device, data, size, numLevels, usage, format, pool, filter, mipFilter, 
			colorKey, imageInformation );
	}

	CubeTexture^ CubeTexture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream, int sizeBytes, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, sizeBytes );
		return CubeTexture::FromMemory( device, data, size, numLevels, usage, format, pool, filter, mipFilter, colorKey );
	}

	CubeTexture^ CubeTexture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		return CubeTexture::FromStream( device, stream, 0, size, numLevels, usage, format, pool, filter, mipFilter, colorKey );
	}

	CubeTexture^ CubeTexture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream, Usage usage, Pool pool )
	{
		return CubeTexture::FromStream( device, stream, D3DX::Default, D3DX::Default,
			usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	CubeTexture^ CubeTexture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream )
	{
		return CubeTexture::FromStream( device, stream, Usage::None, Pool::Managed );
	}

	CubeTexture^ CubeTexture::FromFile( SlimDX::Direct3D9::Device^ device, String^ fileName, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		IDirect3DCubeTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		imageInformation = ImageInformation();
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		palette = gcnew array<PaletteEntry>( 256 );
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];

		HRESULT hr = D3DXCreateCubeTextureFromFileEx( device->InternalPointer, pinnedName, size, 
			numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), 
			colorKey, reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), reinterpret_cast<PALETTEENTRY*>( pinnedPalette ), &texture );
		
		if( RECORD_D3D9(hr).IsFailure )
		{
			palette = nullptr;
			return nullptr;
		}

		CubeTexture^ result = gcnew CubeTexture( texture );
		if( pool == Pool::Default )
			ObjectTable::FlagAsDefaultPool( result );
		return result;
	}

	CubeTexture^ CubeTexture::FromFile( SlimDX::Direct3D9::Device^ device, String^ fileName, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation )
	{
		IDirect3DCubeTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;

		HRESULT hr = D3DXCreateCubeTextureFromFileEx( device->InternalPointer, pinnedName, size, 
			numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), 
			colorKey, reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), NULL, &texture );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		CubeTexture^ result = gcnew CubeTexture( texture );
		if( pool == Pool::Default )
			ObjectTable::FlagAsDefaultPool( result );
		return result;
	}

	CubeTexture^ CubeTexture::FromFile( SlimDX::Direct3D9::Device^ device, String^ fileName, int size, int numLevels,
		Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DCubeTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXCreateCubeTextureFromFileEx( device->InternalPointer, pinnedName, size, 
			numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), 
			colorKey, NULL, NULL, &texture );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		CubeTexture^ result = gcnew CubeTexture( texture );
		if( pool == Pool::Default )
			ObjectTable::FlagAsDefaultPool( result );
		return result;
	}

	CubeTexture^ CubeTexture::FromFile( SlimDX::Direct3D9::Device^ device, String^ fileName, Usage usage, Pool pool )
	{
		return CubeTexture::FromFile( device, fileName, D3DX::Default, D3DX::Default,
			usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	CubeTexture^ CubeTexture::FromFile( SlimDX::Direct3D9::Device^ device, String^ fileName )
	{
		return CubeTexture::FromFile( device, fileName, Usage::None, Pool::Managed );
	}

	DataRectangle^ CubeTexture::LockRectangle( CubeMapFace face, int level, System::Drawing::Rectangle rect, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;
		RECT nativeRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };
		HRESULT hr = InternalPointer->LockRect( static_cast<D3DCUBEMAP_FACES>( face ), level, &lockedRect, &nativeRect, static_cast<DWORD>( flags ) );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;
		
		int lockedSize = lockedRect.Pitch * GetLevelDescription( level ).Height;
		
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		DataRectangle^ outRect = gcnew DataRectangle( lockedRect.Pitch, gcnew DataStream( lockedRect.pBits, lockedSize, true, !readOnly, false ) );
		return outRect;
	}

	DataRectangle^ CubeTexture::LockRectangle( CubeMapFace face, int level, LockFlags flags )
	{
		D3DLOCKED_RECT lockedRect;
		HRESULT hr = InternalPointer->LockRect( static_cast<D3DCUBEMAP_FACES>( face ), level, &lockedRect, NULL, static_cast<DWORD>( flags ) );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;
		
		int lockedSize = lockedRect.Pitch * GetLevelDescription( level ).Height;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		DataRectangle^ outRect = gcnew DataRectangle( lockedRect.Pitch, gcnew DataStream( lockedRect.pBits, lockedSize, true, !readOnly, false ) );
		return outRect;
	}

	Result CubeTexture::UnlockRectangle( CubeMapFace face, int level )
	{
		HRESULT hr = InternalPointer->UnlockRect( static_cast<D3DCUBEMAP_FACES>( face ), level );
		return RECORD_D3D9( hr );
	}

	Result CubeTexture::AddDirtyRect( CubeMapFace face, System::Drawing::Rectangle rect )
	{
		RECT nativeRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };
		HRESULT hr = InternalPointer->AddDirtyRect( static_cast<D3DCUBEMAP_FACES>( face ), &nativeRect );
		return RECORD_D3D9( hr );
	}

	SurfaceDescription CubeTexture::GetLevelDescription( int level )
	{
		SurfaceDescription description;
		HRESULT hr = InternalPointer->GetLevelDesc( level, reinterpret_cast<D3DSURFACE_DESC*>( &description ) );
		RECORD_D3D9( hr );
		return description;
	}

	Surface^ CubeTexture::GetCubeMapSurface( CubeMapFace face, int level )
	{
		IDirect3DSurface9* surface;
		HRESULT hr = InternalPointer->GetCubeMapSurface( static_cast<D3DCUBEMAP_FACES>( face ), level, &surface );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;
		return Surface::FromPointer( surface );
	}

	Result CubeTexture::Fill(Fill3DCallback^ callback)
	{
		HRESULT hr;		// Error code.

		// Call the function.
		hr = D3DXFillCubeTexture(InternalPointer, NativeD3DXFill3D, Marshal::GetFunctionPointerForDelegate(callback).ToPointer());

		return RECORD_D3D9(hr);
	}

	Result CubeTexture::Fill( TextureShader^ shader )
	{
		HRESULT hr = D3DXFillCubeTextureTX( InternalPointer, shader->InternalPointer );
		return RECORD_D3D9( hr );
	}

	VolumeTexture::VolumeTexture( IDirect3DVolumeTexture9* texture )
	{
		Construct(texture);
	}

	VolumeTexture::VolumeTexture( IntPtr volumeTexture )
	{
		Construct( volumeTexture, NativeInterface );
	}

	VolumeTexture::VolumeTexture( SlimDX::Direct3D9::Device^ device, int width, int height, int depth, int numLevels, Usage usage, Format format, Pool pool )
	{
		IDirect3DVolumeTexture9* texture;
		HRESULT hr = device->InternalPointer->CreateVolumeTexture( width, height, depth, numLevels,
			static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), &texture, NULL );
		
		if( RECORD_D3D9(hr).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(texture);
		if( pool == Pool::Default )
			ObjectTable::FlagAsDefaultPool( this );
	}

	VolumeTexture^ VolumeTexture::FromPointer( IDirect3DVolumeTexture9* pointer )
	{
		VolumeTexture^ tableEntry = safe_cast<VolumeTexture^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew VolumeTexture( pointer );
	}

	VolumeTexture^ VolumeTexture::FromPointer( IntPtr pointer )
	{
		VolumeTexture^ tableEntry = safe_cast<VolumeTexture^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew VolumeTexture( pointer );
	}

	VolumeTextureRequirements VolumeTexture::CheckRequirements(SlimDX::Direct3D9::Device^ device, int width, int height, int depth,
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
		
		if( RECORD_D3D9(hr).IsFailure )
			return VolumeTextureRequirements();

		// Return proposed values.
		result.Width = width;
		result.Height = height;
		result.Depth = depth;
		result.Format = format;
		result.MipLevelCount = numMipLevels;

		return result;
	}

	VolumeTexture^ VolumeTexture::FromMemory( SlimDX::Direct3D9::Device^ device, array<Byte>^ memory, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		IDirect3DVolumeTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		imageInformation = ImageInformation();
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		palette = gcnew array<PaletteEntry>( 256 );
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];

		HRESULT hr = D3DXCreateVolumeTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length,
			width, height, depth, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ),
			static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), static_cast<D3DCOLOR>( colorKey ), 
			reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), reinterpret_cast<PALETTEENTRY*>( pinnedPalette ), &texture );
		
		if( RECORD_D3D9(hr).IsFailure )
		{
			palette = nullptr;
			return nullptr;
		}

		VolumeTexture^ result = gcnew VolumeTexture( texture );
		if( pool == Pool::Default )
			ObjectTable::FlagAsDefaultPool( result );
		return result;
	}

	VolumeTexture^ VolumeTexture::FromMemory( SlimDX::Direct3D9::Device^ device, array<Byte>^ memory, int width, int height, int depth,
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
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		VolumeTexture^ result = gcnew VolumeTexture( texture );
		if( pool == Pool::Default )
			ObjectTable::FlagAsDefaultPool( result );
		return result;
	}

	VolumeTexture^ VolumeTexture::FromMemory( SlimDX::Direct3D9::Device^ device, array<Byte>^ memory, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DVolumeTexture9* texture;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXCreateVolumeTextureFromFileInMemoryEx( device->InternalPointer, pinnedMemory, memory->Length,
			width, height, depth, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ),
			static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ), static_cast<D3DCOLOR>( colorKey ), 0, 0, &texture );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		VolumeTexture^ result = gcnew VolumeTexture( texture );
		if( pool == Pool::Default )
			ObjectTable::FlagAsDefaultPool( result );
		return result;
	}

	VolumeTexture^ VolumeTexture::FromMemory( SlimDX::Direct3D9::Device^ device, array<Byte>^ memory, Usage usage, Pool pool )
	{
		return VolumeTexture::FromMemory( device, memory, D3DX::Default, D3DX::Default, D3DX::Default, D3DX::Default,
			usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	VolumeTexture^ VolumeTexture::FromMemory( SlimDX::Direct3D9::Device^ device, array<Byte>^ memory )
	{
		return VolumeTexture::FromMemory( device, memory, Usage::None, Pool::Managed );
	}

	VolumeTexture^ VolumeTexture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream, int sizeBytes, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, sizeBytes );
		return VolumeTexture::FromMemory( device, data, width, height, depth, numLevels,
			usage, format, pool, filter, mipFilter, colorKey, imageInformation, palette );
	}

	VolumeTexture^ VolumeTexture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream, int sizeBytes, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, sizeBytes );
		return VolumeTexture::FromMemory( device, data, width, height, depth, numLevels,
			usage, format, pool, filter, mipFilter, colorKey, imageInformation );
	}

	VolumeTexture^ VolumeTexture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream, int sizeBytes, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, sizeBytes );
		return VolumeTexture::FromMemory( device, data, width, height, depth, numLevels,
			usage, format, pool, filter, mipFilter, colorKey );
	}

	VolumeTexture^ VolumeTexture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		return VolumeTexture::FromStream( device, stream, 0, width, height, depth,
			numLevels, usage, format, pool, filter, mipFilter, colorKey );
	}

	VolumeTexture^ VolumeTexture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream, Usage usage, Pool pool )
	{
		return VolumeTexture::FromStream( device, stream, D3DX::Default, D3DX::Default, D3DX::Default,
			D3DX::Default, usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	VolumeTexture^ VolumeTexture::FromStream( SlimDX::Direct3D9::Device^ device, Stream^ stream )
	{
		return VolumeTexture::FromStream( device, stream, Usage::None, Pool::Managed );
	}

	VolumeTexture^ VolumeTexture::FromFile( SlimDX::Direct3D9::Device^ device, String^ fileName, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey,
		[Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette )
	{
		IDirect3DVolumeTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		imageInformation = ImageInformation();
		pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;
		palette = gcnew array<PaletteEntry>( 256 );
		pin_ptr<PaletteEntry> pinnedPalette = &palette[0];

		HRESULT hr = D3DXCreateVolumeTextureFromFileEx( device->InternalPointer, pinnedName, width, height,
			depth, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ),
			static_cast<DWORD>( mipFilter ), colorKey, reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), 
			reinterpret_cast<PALETTEENTRY*>( pinnedPalette ), &texture );
		
		if( RECORD_D3D9(hr).IsFailure )
		{
			palette = nullptr;
			return nullptr;
		}

		VolumeTexture^ result = gcnew VolumeTexture( texture );
		if( pool == Pool::Default )
			ObjectTable::FlagAsDefaultPool( result );
		return result;
	}

	VolumeTexture^ VolumeTexture::FromFile( SlimDX::Direct3D9::Device^ device, String^ fileName, int width, int height, int depth,
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
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		VolumeTexture^ result = gcnew VolumeTexture( texture );
		if( pool == Pool::Default )
			ObjectTable::FlagAsDefaultPool( result );
		return result;
	}

	VolumeTexture^ VolumeTexture::FromFile( SlimDX::Direct3D9::Device^ device, String^ fileName, int width, int height, int depth,
		int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey )
	{
		IDirect3DVolumeTexture9* texture;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXCreateVolumeTextureFromFileEx( device->InternalPointer, pinnedName, width, height,
			depth, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ),
			static_cast<DWORD>( mipFilter ), colorKey, NULL, NULL, &texture );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		VolumeTexture^ result = gcnew VolumeTexture( texture );
		if( pool == Pool::Default )
			ObjectTable::FlagAsDefaultPool( result );
		return result;
	}

	VolumeTexture^ VolumeTexture::FromFile( SlimDX::Direct3D9::Device^ device, String^ fileName, Usage usage, Pool pool )
	{
		return VolumeTexture::FromFile( device, fileName, D3DX::Default, D3DX::Default, D3DX::Default,
			D3DX::Default, usage, Format::Unknown, pool, Filter::Default, Filter::Default, 0 );
	}

	VolumeTexture^ VolumeTexture::FromFile( SlimDX::Direct3D9::Device^ device, String^ fileName )
	{
		return VolumeTexture::FromFile( device, fileName, Usage::None, Pool::Managed );
	}

	DataBox^ VolumeTexture::LockBox( int level, Box box, LockFlags flags )
	{
		D3DLOCKED_BOX lockedBox;
		HRESULT hr = InternalPointer->LockBox( level, &lockedBox, reinterpret_cast<D3DBOX*>( &box ),
			static_cast<DWORD>( flags ) );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;
		
		int lockedSize = lockedBox.RowPitch * lockedBox.SlicePitch * GetLevelDescription( level ).Height;
		
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		DataBox^ outBox = gcnew DataBox( lockedBox.RowPitch, lockedBox.SlicePitch, gcnew DataStream( lockedBox.pBits, lockedSize, true, !readOnly, false ) );
		return outBox;
	}

	DataBox^ VolumeTexture::LockBox( int level, LockFlags flags )
	{
		D3DLOCKED_BOX lockedBox;
		HRESULT hr = InternalPointer->LockBox( level, &lockedBox, NULL, static_cast<DWORD>( flags ) );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;
		
		int lockedSize = lockedBox.RowPitch * lockedBox.SlicePitch * GetLevelDescription( level ).Height;
		
		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		DataBox^ outBox = gcnew DataBox( lockedBox.RowPitch, lockedBox.SlicePitch, gcnew DataStream( lockedBox.pBits, lockedSize, true, !readOnly, false ) );
		return outBox;
	}

	Result VolumeTexture::UnlockBox( int level )
	{
		HRESULT hr = InternalPointer->UnlockBox( level );
		return RECORD_D3D9( hr );
	}

	Result VolumeTexture::AddDirtyBox( Box box )
	{
		HRESULT hr = InternalPointer->AddDirtyBox( reinterpret_cast<D3DBOX*>( &box ) );
		return RECORD_D3D9( hr );
	}
	
	VolumeDescription VolumeTexture::GetLevelDescription( int level )
	{
		D3DVOLUME_DESC description;
		HRESULT hr = InternalPointer->GetLevelDesc( level, &description );
		
		if( RECORD_D3D9(hr).IsFailure )
			return VolumeDescription();
		
		VolumeDescription outDesc;
		outDesc.Format = static_cast<Format>( description.Format );
		outDesc.Type = static_cast<SlimDX::Direct3D9::ResourceType>( description.Type );
		outDesc.Usage = static_cast<Usage>( description.Usage );
		outDesc.Pool = static_cast<Pool>( description.Pool );
		outDesc.Width = description.Width;
		outDesc.Height = description.Height;
		outDesc.Depth = description.Depth;
		
		return outDesc;
	}

	Volume^ VolumeTexture::GetVolumeLevel( int level )
	{
		IDirect3DVolume9* result;

		HRESULT hr = InternalPointer->GetVolumeLevel( level, &result );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		return Volume::FromPointer( result );
	}

	Result VolumeTexture::Fill(Fill3DCallback^ callback)
	{
		HRESULT hr;		// Error code.

		// Call the function.
		hr = D3DXFillVolumeTexture(InternalPointer, NativeD3DXFill3D, Marshal::GetFunctionPointerForDelegate(callback).ToPointer());

		return RECORD_D3D9(hr);
	}

	Result VolumeTexture::Fill( TextureShader^ shader )
	{
		HRESULT hr = D3DXFillVolumeTextureTX( InternalPointer, shader->InternalPointer );
		return RECORD_D3D9( hr );
	}
}
}