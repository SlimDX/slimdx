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

#include "../DataRectangle.h"
#include "../DataStream.h"

#include "Direct3D10Exception.h"

#include "Device.h"
#include "Texture2D.h"
#include "Texture2DDescription.h"

using namespace System;
using namespace System::IO;

namespace SlimDX
{
namespace Direct3D10
{ 
	Texture2D::Texture2D( ID3D10Texture2D* pointer )
	{
		Construct( pointer );
	}
	
	Texture2D::Texture2D( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}
	
	Texture2D::Texture2D( SlimDX::Direct3D10::Device^ device, Texture2DDescription description )
	{
		ID3D10Texture2D* texture = 0;
		D3D10_TEXTURE2D_DESC nativeDescription = description.CreateNativeVersion();
		if( RECORD_D3D10( device->InternalPointer->CreateTexture2D( &nativeDescription, 0, &texture ) ).IsFailure )
			throw gcnew Direct3D10Exception( Result::Last );
		
		Construct( texture );	
	}

	Texture2D^ Texture2D::FromPointer( ID3D10Texture2D* pointer )
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

	Texture2DDescription Texture2D::Description::get()
	{
		D3D10_TEXTURE2D_DESC nativeDescription;
		InternalPointer->GetDesc( &nativeDescription );
		return Texture2DDescription( nativeDescription );
	}
	
	SlimDX::DataRectangle^ Texture2D::Map( int mipSlice, MapMode mode, MapFlags flags )
	{
		int subresource = D3D10CalcSubresource( mipSlice, 0, Description.MipLevels );
		int mipHeight = GetMipSize( mipSlice, Description.Height );
		
		D3D10_MAPPED_TEXTURE2D mappedRect;
		if( RECORD_D3D10( InternalPointer->Map( subresource, static_cast<D3D10_MAP>( mode ), static_cast<UINT>( flags ), &mappedRect ) ).IsFailure )
			return nullptr;
			
		int lockedSize = mipHeight * mappedRect.RowPitch;
		return gcnew SlimDX::DataRectangle( mappedRect.RowPitch, gcnew DataStream( mappedRect.pData, lockedSize, true, true, false ) );
	}

	void Texture2D::Unmap( int subresource )
	{
		InternalPointer->Unmap( subresource );
	}
	
	Texture2D^ Texture2D::FromFile( SlimDX::Direct3D10::Device^ device, String^ fileName )
	{
		ID3D10Resource* resource = Texture::ConstructFromFile( device, fileName );
		if( resource == 0 )
			return nullptr;
			
		D3D10_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D10_RESOURCE_DIMENSION_TEXTURE2D )
			throw gcnew InvalidOperationException( "Could not load file as 2D texture." ); 
		return gcnew Texture2D( static_cast<ID3D10Texture2D*>( resource ) );
	}
	
	Texture2D^ Texture2D::FromMemory( SlimDX::Direct3D10::Device^ device, array<Byte>^ memory )
	{
		ID3D10Resource* resource = Texture::ConstructFromMemory( device, memory );
		if( resource == 0 )
			return nullptr;
			
		D3D10_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D10_RESOURCE_DIMENSION_TEXTURE2D )
			throw gcnew InvalidOperationException( "Could not load file as 2D texture." ); 
		return gcnew Texture2D( static_cast<ID3D10Texture2D*>( resource ) );
	}
	
	Texture2D^ Texture2D::FromStream( SlimDX::Direct3D10::Device^ device, Stream^ stream, int sizeInBytes )
	{
		ID3D10Resource* resource = Texture::ConstructFromStream( device, stream, sizeInBytes );
		if( resource == 0 )
			return nullptr;
			
		D3D10_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D10_RESOURCE_DIMENSION_TEXTURE2D )
			throw gcnew InvalidOperationException( "Could not load file as 2D texture." ); 
		return gcnew Texture2D( static_cast<ID3D10Texture2D*>( resource ) );
	}
}
}
