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

#include "../DataStream.h"
//#include "Direct3D10ErrorHandler.h"

#include "Texture3D.h"
#include "Device.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	Texture3D::Texture3D( ID3D10Texture3D* texture ) : Texture( texture )
	{
		D3D10_TEXTURE3D_DESC description;
		static_cast<ID3D10Texture3D*>( InternalPointer )->GetDesc( &description );
		
		m_Width = description.Width;
		m_Height = description.Height;
		m_Depth = description.Depth;
		m_MipLevels = description.MipLevels;
		m_Format = static_cast<DXGI::Format>( description.Format );
		m_Usage = static_cast<ResourceUsage>( description.Usage );
		m_BindFlags = static_cast<SlimDX::Direct3D10::BindFlags>( description.BindFlags );
		m_AccessFlags = static_cast<CpuAccessFlags>( description.CPUAccessFlags );
		m_OptionFlags = static_cast<ResourceOptionFlags>( description.MiscFlags );
	}
	
	Texture3D::Texture3D( IntPtr nativeObject )
	{
		Construct( nativeObject, NativeInterface );
	}
	
	Texture3D::Texture3D( Device^ device, int width, int height, int depth, int mipLevels, DXGI::Format format,
		ResourceUsage usage, SlimDX::Direct3D10::BindFlags bindFlags, CpuAccessFlags accessFlags, ResourceOptionFlags optionFlags )
	{
		D3D10_TEXTURE3D_DESC description;
		ZeroMemory( &description, sizeof( description ) );
		description.Width = width;
		description.Height = height;
		description.Depth = depth;
		description.MipLevels = mipLevels;
		description.Format = static_cast<DXGI_FORMAT>( format );
		description.Usage = static_cast<D3D10_USAGE>( usage );
		description.BindFlags = static_cast<UINT>( bindFlags );
		description.CPUAccessFlags = static_cast<UINT>( accessFlags );
		description.MiscFlags = static_cast<UINT>( optionFlags );
	
		ID3D10Texture3D* texture;
		HRESULT hr = device->InternalPointer->CreateTexture3D( &description, NULL, &texture );
		Result::Record( hr );
		
		Construct( texture );	
	}
	
	SlimDX::Direct3D::LockedBox Texture3D::Map( int mipSlice, MapMode mode, MapFlags flags )
	{
		int subResource = D3D10CalcSubresource( mipSlice, 0, MipLevels );
		int mipHeight = GetMipSize( mipSlice, Height );
		
		D3D10_MAPPED_TEXTURE3D mappedBox;
		HRESULT hr = static_cast<ID3D10Texture3D*>( InternalPointer )->Map( subResource, static_cast<D3D10_MAP>( mode ), static_cast<UINT>( flags ), &mappedBox );
		Result::Record( hr );
		
		int lockedSize = mipHeight * mappedBox.RowPitch * mappedBox.DepthPitch;
		
		bool readOnly = mode == MapMode::Read;
		SlimDX::Direct3D::LockedBox box( mappedBox.RowPitch, mappedBox.DepthPitch, gcnew DataStream( mappedBox.pData, lockedSize, true, !readOnly, false ) );
		
		return box;
	}

	void Texture3D::Unmap( int subResource )
	{
		static_cast<ID3D10Texture3D*>( InternalPointer )->Unmap( subResource );
	}
	
	Texture3D^ Texture3D::FromFile( Device^ device, String^ fileName )
	{
		Texture^ baseTexture = Texture::FromFile( device, fileName );
		if( baseTexture->Dimension != ResourceDimension::Texture3D )
			throw gcnew InvalidOperationException( "Could not load file as 3D texture." ); 
		return static_cast< Texture3D^ >( baseTexture );
	}
	
	Texture3D^ Texture3D::FromStream( Device^ device, Stream^ stream, int sizeInBytes )
	{
		Texture^ baseTexture = Texture::FromStream( device, stream, sizeInBytes );
		if( baseTexture->Dimension != ResourceDimension::Texture3D )
			throw gcnew InvalidOperationException( "Could not load file as 3D texture." ); 
		return static_cast< Texture3D^ >( baseTexture );
	}
}
}
