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

#include <d3d11.h>
#include <vector>

#include "../DataRectangle.h"
#include "../DataStream.h"

#include "Direct3D11Exception.h"

#include "Device.h"
#include "Texture2D.h"
#include "Texture2DDescription.h"

using namespace System;
using namespace System::IO;

namespace SlimDX
{
namespace Direct3D11
{ 
	Texture2D::Texture2D( ID3D11Texture2D* pointer )
	{
		Construct( pointer );
	}
	
	Texture2D::Texture2D( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}
	
	Texture2D::Texture2D( SlimDX::Direct3D11::Device^ device, Texture2DDescription description )
	{
		Construct( Build( device, description, 0 ) );	
	}
	
	Texture2D::Texture2D( SlimDX::Direct3D11::Device^ device, Texture2DDescription description, DataRectangle^ data )
	{
		if( data != nullptr )
		{
			D3D11_SUBRESOURCE_DATA initialData;
			initialData.pSysMem = data->Data->RawPointer;
			initialData.SysMemPitch = data->Pitch;
			Construct( Build( device, description, &initialData ) );	
		}
		else 
		{
			Construct( Build( device, description, 0 ) );	
		}
	}
	
	Texture2D::Texture2D( SlimDX::Direct3D11::Device^ device, Texture2DDescription description, array<DataRectangle^>^ data )
	{
		if( data != nullptr )
		{
			std::vector<D3D11_SUBRESOURCE_DATA> initialData( data->Length );
			for(unsigned int dataIndex = 0; dataIndex < initialData.size(); ++dataIndex ) 
			{
				initialData[dataIndex].pSysMem = data[dataIndex]->Data->RawPointer;
				initialData[dataIndex].SysMemPitch = data[dataIndex]->Pitch;
			}
			
			Construct( Build( device, description, &initialData[0] ) );	
		} 
		else
		{
			Construct( Build( device, description, 0 ) );	
		}
	}
	
	Texture2D^ Texture2D::FromPointer( ID3D11Texture2D* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		Texture2D^ tableEntry = safe_cast<Texture2D^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew Texture2D( pointer );
	}

	Texture2D^ Texture2D::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		Texture2D^ tableEntry = safe_cast<Texture2D^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew Texture2D( pointer );
	}
	
	ID3D11Texture2D* Texture2D::Build( SlimDX::Direct3D11::Device^ device, Texture2DDescription description, D3D11_SUBRESOURCE_DATA* data )
	{
		ID3D11Texture2D* texture = 0;
		D3D11_TEXTURE2D_DESC nativeDescription = description.CreateNativeVersion();
		
		if( RECORD_D3D11( device->InternalPointer->CreateTexture2D( &nativeDescription, data, &texture ) ).IsFailure )
			throw gcnew Direct3D11Exception( Result::Last );
		
		return texture;
	} 
	
	Texture2DDescription Texture2D::Description::get()
	{
		D3D11_TEXTURE2D_DESC nativeDescription;
		InternalPointer->GetDesc( &nativeDescription );
		return Texture2DDescription( nativeDescription );
	}
	
	// TODO: Fix
	/*
	SlimDX::DataRectangle^ Texture2D::Map( int mipSlice, MapMode mode, MapFlags flags )
	{
		int subresource = D3D11CalcSubresource( mipSlice, 0, Description.MipLevels );
		int mipHeight = GetMipSize( mipSlice, Description.Height );
		
		D3D11_MAPPED_TEXTURE2D mappedRect;
		if( RECORD_D3D11( InternalPointer->Map( subresource, static_cast<D3D11_MAP>( mode ), static_cast<UINT>( flags ), &mappedRect ) ).IsFailure )
			return nullptr;
			
		int lockedSize = mipHeight * mappedRect.RowPitch;
		return gcnew SlimDX::DataRectangle( mappedRect.RowPitch, gcnew DataStream( mappedRect.pData, lockedSize, true, true, false ) );
	}

	void Texture2D::Unmap( int subresource )
	{
		InternalPointer->Unmap( subresource );
	}
	*/

	Texture2D^ Texture2D::FromFile( SlimDX::Direct3D11::Device^ device, String^ fileName )
	{
		ID3D11Resource* resource = Texture::ConstructFromFile( device, fileName );
		if( resource == 0 )
			return nullptr;
			
		D3D11_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D11_RESOURCE_DIMENSION_TEXTURE2D )
			throw gcnew InvalidOperationException( "Could not load file as 2D texture." ); 
		return gcnew Texture2D( static_cast<ID3D11Texture2D*>( resource ) );
	}
	
	Texture2D^ Texture2D::FromMemory( SlimDX::Direct3D11::Device^ device, array<Byte>^ memory )
	{
		ID3D11Resource* resource = Texture::ConstructFromMemory( device, memory );
		if( resource == 0 )
			return nullptr;
			
		D3D11_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D11_RESOURCE_DIMENSION_TEXTURE2D )
			throw gcnew InvalidOperationException( "Could not load file as 2D texture." ); 
		return gcnew Texture2D( static_cast<ID3D11Texture2D*>( resource ) );
	}
	
	Texture2D^ Texture2D::FromStream( SlimDX::Direct3D11::Device^ device, Stream^ stream, int sizeInBytes )
	{
		ID3D11Resource* resource = Texture::ConstructFromStream( device, stream, sizeInBytes );
		if( resource == 0 )
			return nullptr;
			
		D3D11_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D11_RESOURCE_DIMENSION_TEXTURE2D )
			throw gcnew InvalidOperationException( "Could not load file as 2D texture." ); 
		return gcnew Texture2D( static_cast<ID3D11Texture2D*>( resource ) );
	}
}
}
