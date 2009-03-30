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

#include <d3d11.h>
#include <vector>

#include "Direct3D11Exception.h"

#include "Device.h"
#include "Texture1D.h"
#include "Texture1DDescription.h"

using namespace System;
using namespace System::IO;

namespace SlimDX
{
namespace Direct3D11
{
	Texture1D::Texture1D( SlimDX::Direct3D11::Device^ device, Texture1DDescription description )
	{
		Construct( Build( device, description, 0 ) );	
	}
	
	Texture1D::Texture1D( SlimDX::Direct3D11::Device^ device, Texture1DDescription description, DataStream^ data )
	{
		if( data != nullptr )
		{
			D3D11_SUBRESOURCE_DATA initialData;
			initialData.pSysMem = data->RawPointer;
			Construct( Build( device, description, &initialData ) );	
		}
		else 
		{
			Construct( Build( device, description, 0 ) );	
		}
	}
	
	Texture1D::Texture1D( SlimDX::Direct3D11::Device^ device, Texture1DDescription description, array<DataStream^>^ data )
	{
		if( data != nullptr )
		{
			std::vector<D3D11_SUBRESOURCE_DATA> initialData( data->Length );
			for(unsigned int dataIndex = 0; dataIndex < initialData.size(); ++dataIndex ) 
				initialData[dataIndex].pSysMem = data[dataIndex]->RawPointer;
			
			Construct( Build( device, description, &initialData[0] ) );	
		} 
		else
		{
			Construct( Build( device, description, 0 ) );	
		}
	}

	ID3D11Texture1D* Texture1D::Build( SlimDX::Direct3D11::Device^ device, Texture1DDescription description, D3D11_SUBRESOURCE_DATA* data )
	{
		ID3D11Texture1D* texture = 0;
		D3D11_TEXTURE1D_DESC nativeDescription = description.CreateNativeVersion();
		
		if( RECORD_D3D11( device->InternalPointer->CreateTexture1D( &nativeDescription, data, &texture ) ).IsFailure )
			throw gcnew Direct3D11Exception( Result::Last );
		
		return texture;
	}
	
	Texture1DDescription Texture1D::Description::get()
	{
		D3D11_TEXTURE1D_DESC nativeDescription;
		InternalPointer->GetDesc( &nativeDescription );
		return Texture1DDescription( nativeDescription );
	}
	
	// TODO: Fix
	/*
	SlimDX::DataStream^ Texture1D::Map( int mipSlice, MapMode mode, MapFlags flags )
	{
		int subresource = D3D11CalcSubresource( mipSlice, 0, Description.MipLevels );
		int mipWidth = GetMipSize( mipSlice, Description.Width );
		int bufferSize = mipWidth * Utilities::SizeOfFormatElement( static_cast<DXGI_FORMAT>( Description.Format ) );
		
		void* mappedArray = 0;
		if( RECORD_D3D11( InternalPointer->Map( subresource, static_cast<D3D11_MAP>( mode ), static_cast<UINT>( flags ), &mappedArray ) ).IsFailure )
			return nullptr;
			
		return gcnew SlimDX::DataStream( mappedArray, bufferSize, true, true, false );
	}

	void Texture1D::Unmap( int subresource )
	{
		InternalPointer->Unmap( subresource );
	}
	*/
	
	Texture1D^ Texture1D::FromFile( SlimDX::Direct3D11::Device^ device, String^ fileName )
	{
		ID3D11Resource* resource = Texture::ConstructFromFile( device, fileName );
		if( resource == 0 )
			return nullptr;
			
		D3D11_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D11_RESOURCE_DIMENSION_TEXTURE1D )
			throw gcnew InvalidOperationException( "Could not load file as 1D texture." ); 
		return FromPointer( static_cast<ID3D11Texture1D*>( resource ) );
	}
	
	Texture1D^ Texture1D::FromMemory( SlimDX::Direct3D11::Device^ device, array<Byte>^ memory )
	{
		ID3D11Resource* resource = Texture::ConstructFromMemory( device, memory );
		if( resource == 0 )
			return nullptr;
			
		D3D11_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D11_RESOURCE_DIMENSION_TEXTURE1D )
			throw gcnew InvalidOperationException( "Could not load file as 1D texture." ); 
		return FromPointer( static_cast<ID3D11Texture1D*>( resource ) );
	}
	
	Texture1D^ Texture1D::FromStream( SlimDX::Direct3D11::Device^ device, Stream^ stream, int sizeInBytes )
	{
		ID3D11Resource* resource = Texture::ConstructFromStream( device, stream, sizeInBytes );
		if( resource == 0 )
			return nullptr;
			
		D3D11_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D11_RESOURCE_DIMENSION_TEXTURE1D )
			throw gcnew InvalidOperationException( "Could not load file as 1D texture." ); 
		return FromPointer( static_cast<ID3D11Texture1D*>( resource ) );
	}
}
}
