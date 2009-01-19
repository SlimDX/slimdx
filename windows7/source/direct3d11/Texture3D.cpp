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

#include "Direct3D11Exception.h"

#include "Device.h"
#include "Texture3D.h"
#include "Texture3DDescription.h"

using namespace System;
using namespace System::IO;

namespace SlimDX
{
namespace Direct3D11
{ 
	Texture3D::Texture3D( ID3D11Texture3D* pointer )
	{
		Construct( pointer );
	}
	
	Texture3D::Texture3D( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}
	
	Texture3D::Texture3D( SlimDX::Direct3D11::Device^ device, Texture3DDescription description )
	{
		Construct( Build( device, description, 0 ) );
	}

	Texture3D::Texture3D( SlimDX::Direct3D11::Device^ device, Texture3DDescription description, DataBox^ data )
	{
		if( data != nullptr )
		{
			D3D11_SUBRESOURCE_DATA initialData;
			initialData.pSysMem = data->Data->RawPointer;
			initialData.SysMemPitch = data->RowPitch;
			initialData.SysMemSlicePitch = data->SlicePitch;
			Construct( Build( device, description, &initialData ) );	
		}
		else 
		{
			Construct( Build( device, description, 0 ) );	
		}
	}
	
	Texture3D::Texture3D( SlimDX::Direct3D11::Device^ device, Texture3DDescription description, array<DataBox^>^ data )
	{
		if( data != nullptr )
		{
			std::vector<D3D11_SUBRESOURCE_DATA> initialData( data->Length );
			for(unsigned int dataIndex = 0; dataIndex < initialData.size(); ++dataIndex ) 
			{
				initialData[dataIndex].pSysMem = data[dataIndex]->Data->RawPointer;
				initialData[dataIndex].SysMemPitch = data[dataIndex]->RowPitch;
				initialData[dataIndex].SysMemSlicePitch = data[dataIndex]->SlicePitch;
			}
			
			Construct( Build( device, description, &initialData[0] ) );	
		} 
		else
		{
			Construct( Build( device, description, 0 ) );	
		}
	}

	Texture3D^ Texture3D::FromPointer( ID3D11Texture3D* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		Texture3D^ tableEntry = safe_cast<Texture3D^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew Texture3D( pointer );
	}

	Texture3D^ Texture3D::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		Texture3D^ tableEntry = safe_cast<Texture3D^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew Texture3D( pointer );
	}
	
	ID3D11Texture3D* Texture3D::Build( SlimDX::Direct3D11::Device^ device, Texture3DDescription description, D3D11_SUBRESOURCE_DATA* data )
	{
		ID3D11Texture3D* texture = 0;
		D3D11_TEXTURE3D_DESC nativeDescription = description.CreateNativeVersion();
		
		if( RECORD_D3D11( device->InternalPointer->CreateTexture3D( &nativeDescription, data, &texture ) ).IsFailure )
			throw gcnew Direct3D11Exception( Result::Last );
		
		return texture;
	} 
	
	Texture3DDescription Texture3D::Description::get()
	{
		D3D11_TEXTURE3D_DESC nativeDescription;
		InternalPointer->GetDesc( &nativeDescription );
		return Texture3DDescription( nativeDescription );
	}
	
	// TODO: Fix
	/*
	SlimDX::DataBox^ Texture3D::Map( int mipSlice, MapMode mode, MapFlags flags )
	{
		int subresource = D3D11CalcSubresource( mipSlice, 0, Description.MipLevels );
		int mipHeight = GetMipSize( mipSlice, Description.Height );
		
		D3D11_MAPPED_TEXTURE3D mappedBox;
		if( RECORD_D3D11( InternalPointer->Map( subresource, static_cast<D3D11_MAP>( mode ), static_cast<UINT>( flags ), &mappedBox ) ).IsFailure )
			return nullptr;
			
		int lockedSize = mipHeight * mappedBox.DepthPitch;
		return gcnew SlimDX::DataBox( mappedBox.RowPitch, mappedBox.DepthPitch, gcnew DataStream( mappedBox.pData, lockedSize, true, true, false ) );
	}

	void Texture3D::Unmap( int subresource )
	{
		InternalPointer->Unmap( subresource );
	}
	*/
	
	Texture3D^ Texture3D::FromFile( SlimDX::Direct3D11::Device^ device, String^ fileName )
	{
		ID3D11Resource* resource = Texture::ConstructFromFile( device, fileName );
		if( resource == 0 )
			return nullptr;
			
		D3D11_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D11_RESOURCE_DIMENSION_TEXTURE3D )
			throw gcnew InvalidOperationException( "Could not load file as 3D texture." ); 
		return gcnew Texture3D( static_cast<ID3D11Texture3D*>( resource ) );
	}
	
	Texture3D^ Texture3D::FromMemory( SlimDX::Direct3D11::Device^ device, array<Byte>^ memory )
	{
		ID3D11Resource* resource = Texture::ConstructFromMemory( device, memory );
		if( resource == 0 )
			return nullptr;
			
		D3D11_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D11_RESOURCE_DIMENSION_TEXTURE3D )
			throw gcnew InvalidOperationException( "Could not load file as 3D texture." ); 
		return gcnew Texture3D( static_cast<ID3D11Texture3D*>( resource ) );
	}
	
	Texture3D^ Texture3D::FromStream( SlimDX::Direct3D11::Device^ device, Stream^ stream, int sizeInBytes )
	{
		ID3D11Resource* resource = Texture::ConstructFromStream( device, stream, sizeInBytes );
		if( resource == 0 )
			return nullptr;
			
		D3D11_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D11_RESOURCE_DIMENSION_TEXTURE3D )
			throw gcnew InvalidOperationException( "Could not load file as 3D texture." ); 
		return gcnew Texture3D( static_cast<ID3D11Texture3D*>( resource ) );
	}
}
}
