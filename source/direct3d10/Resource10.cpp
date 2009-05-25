#include "stdafx.h"
/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include "../DataStream.h"
#include "../Utilities.h"

#include "Direct3D10Exception.h"

#include "Device10.h"
#include "Resource10.h"

using namespace System;
using namespace System::IO;

namespace SlimDX
{
namespace Direct3D10
{
	DXGI::ResourcePriority Resource::EvictionPriority::get()
	{
		return static_cast<DXGI::ResourcePriority>( InternalPointer->GetEvictionPriority() );
	}
	
	void Resource::EvictionPriority::set( DXGI::ResourcePriority value )
	{
		InternalPointer->SetEvictionPriority( static_cast<UINT>( value ) );
	}
	
	ResourceDimension Resource::Dimension::get()
	{
		D3D10_RESOURCE_DIMENSION type;
		InternalPointer->GetType(&type);
		return static_cast<ResourceDimension>( type );
	}

	int Resource::GetMipSize( int mipSlice, int baseSliceSize )
	{
		float size = static_cast<float>( baseSliceSize );
		
		while( mipSlice > 0 )
		{
			size = std::floorf(size / 2.0f);
			--mipSlice;
		}
		
		return (static_cast< int >(size));
	}
	
	ID3D10Resource* Resource::ConstructFromFile( SlimDX::Direct3D10::Device^ device, String^ fileName, D3DX10_IMAGE_LOAD_INFO* info )
	{	
		ID3D10Resource* resource = 0;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		HRESULT hr = D3DX10CreateTextureFromFile( device->InternalPointer, pinnedName, info, 0, &resource, 0 );
		RECORD_D3D10( hr );
		
		return resource;
	}
	
	ID3D10Resource* Resource::ConstructFromMemory( SlimDX::Direct3D10::Device^ device, array<Byte>^ memory, D3DX10_IMAGE_LOAD_INFO* info )
	{
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		ID3D10Resource* resource = 0;
		HRESULT hr = D3DX10CreateTextureFromMemory( device->InternalPointer, pinnedMemory, memory->Length, info, 0, &resource, 0 ); 
		RECORD_D3D10( hr );
		
		return resource;
	}
	
	ID3D10Resource* Resource::ConstructFromStream( SlimDX::Direct3D10::Device^ device, Stream^ stream, int sizeInBytes, D3DX10_IMAGE_LOAD_INFO* info )
	{
		DataStream^ ds = nullptr;
		array<Byte>^ memory = SlimDX::Utilities::ReadStream( stream, sizeInBytes, &ds );
		
		if( memory == nullptr )
		{
			ID3D10Resource* resource = NULL;
			SIZE_T size = static_cast<SIZE_T>( ds->RemainingLength );
			HRESULT hr = D3DX10CreateTextureFromMemory( device->InternalPointer, ds->SeekToEnd(), size,
				info, NULL, &resource, NULL );
			RECORD_D3D10( hr );

			return resource;
		}

		return ConstructFromMemory( device, memory, info );
	}
}
}
