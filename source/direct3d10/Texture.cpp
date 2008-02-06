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

#include <d3d10.h>
#include <d3dx10.h>
#include <d3dx9.h>
#include <vcclr.h>
#include <cmath>

#include "../DataStream.h"
//#include "Direct3D10ErrorHandler.h"

#include "Texture.h"
#include "Device.h"


namespace SlimDX
{
namespace Direct3D10
{ 
	Texture::Texture()
	{
	}

	Texture::Texture( ID3D10Resource* pointer )
	: Resource( pointer )
	{
	}

	Texture^ Texture::FromFile( Device^ device, String^ fileName )
	{	
		ID3D10Resource* resource = 0;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		HRESULT hr = D3DX10CreateTextureFromFile( device->InternalPointer, pinnedName, 0, 0, &resource, 0 );
		Result::Record( hr );
		
		if( resource == 0 )
			return nullptr;
		return gcnew Texture( resource );
	}

	Texture^ Texture::FromMemory( Device^ device, array<Byte>^ memory )
	{
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		ID3D10Resource* resource = 0;
		HRESULT hr = D3DX10CreateTextureFromMemory( device->InternalPointer, pinnedMemory, memory->Length, 0, 0, &resource, 0 ); 
		Result::Record( hr );
		
		if( resource == 0 )
			return nullptr;
		return gcnew Texture( static_cast<ID3D10Resource*>( resource ) );
	}

	Texture^ Texture::FromStream( Device^ device, Stream^ stream, int sizeInBytes )
	{
		array<Byte>^ memory = SlimDX::Utilities::ReadStream( stream, sizeInBytes );
		return FromMemory( device, memory );
	}


	bool Texture::ToFile( Texture^ texture, ImageFileFormat format, String^ fileName )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		HRESULT hr = D3DX10SaveTextureToFile( texture->InternalPointer, (D3DX10_IMAGE_FILE_FORMAT) format, pinnedName );
		Result::Record( hr );
		
		return ( FAILED( hr ) );
	}

	int Texture::GetMipSize( int mipSlice, int baseSliceSize )
	{
		float size = static_cast<float>( baseSliceSize );
		
		while( mipSlice > 0 )
		{
			size = std::floorf(size / 2.0f);
			--mipSlice;
		}
		
		return (static_cast< int >(size));
	}
	
	int Texture::GetElementSize( DXGI::Format format )
	{
		int size8 = sizeof( System::Byte );
		int size16 = sizeof( System::Int16 );
		int size32 = sizeof( System::Int32 );
		int size64 = sizeof( System::Int64 );
		int size96 = size64 + size32;
		int size128 = size64 + size64;
		
		switch( format )
		{
			case DXGI::Format::R32G32B32A32_Typeless:
			case DXGI::Format::R32G32B32A32_Float:
			case DXGI::Format::R32G32B32A32_UInt:
			case DXGI::Format::R32G32B32A32_SInt:
				return size128;
			case DXGI::Format::R32G32B32_Typeless:
			case DXGI::Format::R32G32B32_Float:
			case DXGI::Format::R32G32B32_UInt:
			case DXGI::Format::R32G32B32_SInt:
				return size96;
			case DXGI::Format::R32G32_Typeless:
			case DXGI::Format::R32G32_Float:
			case DXGI::Format::R32G32_UInt:
			case DXGI::Format::R32G32_SInt:
			case DXGI::Format::R32G8X24_Typeless:
			case DXGI::Format::D32_Float_S8X24_UInt:
			case DXGI::Format::R32_Float_X8X24_Typeless:
			case DXGI::Format::X32_Typeless_G8X24_UInt:
			case DXGI::Format::R16G16B16A16_Typeless:
			case DXGI::Format::R16G16B16A16_Float:
			case DXGI::Format::R16G16B16A16_UNorm:
			case DXGI::Format::R16G16B16A16_UInt:
			case DXGI::Format::R16G16B16A16_SNorm:
			case DXGI::Format::R16G16B16A16_SInt:
				return size64;
			case DXGI::Format::R10G10B10A2_Typeless:
			case DXGI::Format::R10G10B10A2_UNorm:
			case DXGI::Format::R10G10B10A2_UInt:
			case DXGI::Format::R11G11B10_Float:
			case DXGI::Format::R8G8B8A8_Typeless:
			case DXGI::Format::R8G8B8A8_UNorm:
			case DXGI::Format::R8G8B8A8_UNorm_SRGB:
			case DXGI::Format::R8G8B8A8_UInt:
			case DXGI::Format::R8G8B8A8_SNorm:
			case DXGI::Format::R8G8B8A8_SInt:
			case DXGI::Format::R16G16_Typeless:
			case DXGI::Format::R16G16_Float:
			case DXGI::Format::R16G16_UNorm:
			case DXGI::Format::R16G16_UInt:
			case DXGI::Format::R16G16_SNorm:
			case DXGI::Format::R16G16_SInt:
			case DXGI::Format::R32_Typeless:
			case DXGI::Format::D32_Float:
			case DXGI::Format::R32_Float:
			case DXGI::Format::R32_UInt:
			case DXGI::Format::R32_SInt:
			case DXGI::Format::R24G8_Typeless:
			case DXGI::Format::D24_UNorm_S8_UInt:
			case DXGI::Format::R24_UNorm_X8_Typeless:
			case DXGI::Format::X24_Typeless_G8_UInt:
			case DXGI::Format::R9G9B9E5_SharedExp:
			case DXGI::Format::R8G8_B8G8_UNorm:
			case DXGI::Format::G8R8_G8B8_UNorm:
			case DXGI::Format::B8G8R8A8_UNorm:
			case DXGI::Format::B8G8R8X8_UNorm:
				return size32;
			case DXGI::Format::R8G8_Typeless:
			case DXGI::Format::R8G8_UNorm:
			case DXGI::Format::R8G8_UInt:
			case DXGI::Format::R8G8_SNorm:
			case DXGI::Format::R8G8_SInt:
			case DXGI::Format::R16_Typeless:
			case DXGI::Format::R16_Float:
			case DXGI::Format::D16_UNorm:
			case DXGI::Format::R16_UNorm:
			case DXGI::Format::R16_UInt:
			case DXGI::Format::R16_SNorm:
			case DXGI::Format::R16_SInt:
			case DXGI::Format::B5G6R5_UNorm:
			case DXGI::Format::B5G5R5A1_UNorm:
				return size16;
			case DXGI::Format::R8_Typeless:
			case DXGI::Format::R8_UNorm:
			case DXGI::Format::R8_UInt:
			case DXGI::Format::R8_SNorm:
			case DXGI::Format::R8_SInt:
			case DXGI::Format::A8_UNorm:
				return size8;
			case DXGI::Format::R1_UNorm:
			case DXGI::Format::BC1_Typeless:
			case DXGI::Format::BC1_UNorm:
			case DXGI::Format::BC1_UNorm_SRGB:
			case DXGI::Format::BC2_Typeless:
			case DXGI::Format::BC2_UNorm:
			case DXGI::Format::BC2_UNorm_SRGB:
			case DXGI::Format::BC3_Typeless:
			case DXGI::Format::BC3_UNorm:
			case DXGI::Format::BC3_UNorm_SRGB:
			case DXGI::Format::BC4_Typeless:
			case DXGI::Format::BC4_UNorm:
			case DXGI::Format::BC4_SNorm:
			case DXGI::Format::BC5_Typeless:
			case DXGI::Format::BC5_UNorm:
			case DXGI::Format::BC5_SNorm:
				return 0;
			default:
				return 0;
		}
	}
}
}
