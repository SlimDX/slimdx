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

#include <d3d10.h>
#include <d3dx10.h>
#include <d3dx9.h>
#include <vcclr.h>
#include <cmath>

#include "Direct3D10Exception.h"

#include "../DataStream.h"

#include "Texture.h"
#include "Device.h"
#include "ThreadPump.h"
#include "DelayedResult.h"

using namespace System;
using namespace System::IO;

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

	Texture^ Texture::FromFile( SlimDX::Direct3D10::Device^ device, String^ fileName )
	{	
		ID3D10Resource* resource = ConstructFromFile( device, fileName, nullptr, nullptr );
		if( resource == 0 )
			return nullptr;
		return gcnew Texture( resource );
	}

	Texture^ Texture::FromMemory( SlimDX::Direct3D10::Device^ device, array<Byte>^ memory )
	{
		ID3D10Resource* resource = ConstructFromMemory( device, memory, nullptr, nullptr );
		if( resource == 0 )
			return nullptr;
		return gcnew Texture( resource );
	}

	void Texture::FromFile( SlimDX::Direct3D10::Device^ device, String^ fileName, ThreadPump^ threadPump, DelayedResult^ result )
	{	
		ConstructFromFile( device, fileName, threadPump, result );
	}

	void Texture::FromMemory( SlimDX::Direct3D10::Device^ device, array<Byte>^ memory, ThreadPump^ threadPump, DelayedResult^ result )
	{
		ConstructFromMemory( device, memory, threadPump, result );
	}

	Texture^ Texture::FromStream( SlimDX::Direct3D10::Device^ device, Stream^ stream, int sizeInBytes )
	{
		ID3D10Resource* resource = ConstructFromStream( device, stream, sizeInBytes );
		if( resource == 0 )
			return nullptr;
		return gcnew Texture( resource );
	}


	bool Texture::ToFile( Texture^ texture, ImageFileFormat format, String^ fileName )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		HRESULT hr = D3DX10SaveTextureToFile( texture->InternalPointer, (D3DX10_IMAGE_FILE_FORMAT) format, pinnedName );
		RECORD_D3D10( hr );
		
		return ( FAILED( hr ) );
	}
	
	bool Texture::ToStream( Texture^ texture, ImageFileFormat format, Stream^ stream )
	{
		ID3D10Blob* blob = 0;
		HRESULT hr = D3DX10SaveTextureToMemory( texture->InternalPointer, (D3DX10_IMAGE_FILE_FORMAT) format, &blob, 0 );
		if( RECORD_D3D10( hr ).IsFailure )
			return false;
		
		if( static_cast<SIZE_T>( stream->Length - stream->Position ) < blob->GetBufferSize() )
			throw gcnew InvalidOperationException( "The specified stream does not have sufficient capacity for the specified texture." );
		
		// Write byte-by-byte to avoid allocating a managed byte[] that will wastefully persist.
		unsigned char* bytes = reinterpret_cast<unsigned char*>( blob->GetBufferPointer() );
		for(SIZE_T byteIndex = 0; byteIndex < blob->GetBufferSize(); ++byteIndex)
			stream->WriteByte( bytes[byteIndex] );
		
		blob->Release();
		return true;
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
	
	ID3D10Resource* Texture::ConstructFromFile( SlimDX::Direct3D10::Device^ device, String^ fileName, ThreadPump^ threadPump, DelayedResult^ result )
	{	
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		HRESULT hr;
		ID3D10Resource* resource = 0;

		if(threadPump == nullptr) {
			hr = D3DX10CreateTextureFromFile( device->InternalPointer, pinnedName, 0, 0, &resource, 0 );
		} else {
			hr = D3DX10CreateTextureFromFile( device->InternalPointer, pinnedName, 0, threadPump->InternalPointer, reinterpret_cast<ID3D10Resource**>(result->deviceObject), reinterpret_cast<HRESULT*>(result->result));
		}

		RECORD_D3D10( hr );
			
		return resource;
	}
	
	ID3D10Resource* Texture::ConstructFromMemory( SlimDX::Direct3D10::Device^ device, array<Byte>^ memory, ThreadPump^ threadPump, DelayedResult^ result )
	{
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		HRESULT hr;
		ID3D10Resource* resource = 0;

		if(threadPump == nullptr) {
			hr = D3DX10CreateTextureFromMemory( device->InternalPointer, pinnedMemory, memory->Length, 0, 0, &resource, 0 );
		} else {
			hr = D3DX10CreateTextureFromMemory( device->InternalPointer, pinnedMemory, memory->Length, 0, threadPump->InternalPointer, reinterpret_cast<ID3D10Resource**>(result->deviceObject), reinterpret_cast<HRESULT*>(result->result));
		}
		
		RECORD_D3D10( hr );
		
		return resource;
	}
	
	ID3D10Resource* Texture::ConstructFromStream( SlimDX::Direct3D10::Device^ device, Stream^ stream, int sizeInBytes )
	{
		array<Byte>^ memory = SlimDX::Utilities::ReadStream( stream, sizeInBytes );
		return ConstructFromMemory( device, memory, nullptr, nullptr );
	}
}
}
