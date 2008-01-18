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
#include "GraphicsException.h"

#include "Texture2D.h"
#include "Device.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	Texture2D::Texture2D( ID3D10Texture2D* texture ) : Texture( texture )
	{
		D3D10_TEXTURE2D_DESC desc;
		texture->GetDesc( &desc );
		m_Width = desc.Width;
		m_Height = desc.Height;
		m_MipLevels = desc.MipLevels;
		m_ArraySize = desc.ArraySize;
		m_Format = static_cast<DXGI::Format>( desc.Format );
		m_SampleDesc.Count = desc.SampleDesc.Count;
		m_SampleDesc.Quality = desc.SampleDesc.Quality;
		m_Usage = static_cast<ResourceUsage>( desc.Usage );
		m_BindFlags = static_cast<SlimDX::Direct3D10::BindFlags>( desc.BindFlags );
		m_AccessFlags = static_cast<CpuAccessFlags>( desc.CPUAccessFlags );
		m_OptionFlags = static_cast<ResourceOptionFlags>( desc.MiscFlags );
	}
	
	Texture2D::Texture2D( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
		
		D3D10_TEXTURE2D_DESC desc;
		static_cast<ID3D10Texture2D*>( InternalPointer )->GetDesc( &desc );
		m_Width = desc.Width;
		m_Height = desc.Height;
		m_MipLevels = desc.MipLevels;
		m_ArraySize = desc.ArraySize;
		m_Format = static_cast<DXGI::Format>( desc.Format );
		m_SampleDesc.Count = desc.SampleDesc.Count;
		m_SampleDesc.Quality = desc.SampleDesc.Quality;
		m_Usage = static_cast<ResourceUsage>( desc.Usage );
		m_BindFlags = static_cast<SlimDX::Direct3D10::BindFlags>( desc.BindFlags );
		m_AccessFlags = static_cast<CpuAccessFlags>( desc.CPUAccessFlags );
		m_OptionFlags = static_cast<ResourceOptionFlags>( desc.MiscFlags );
	}
	
	Texture2D::Texture2D( Device^ device, int width, int height, int mipLevels, int arraySize, DXGI::Format format,
		int sampleCount, int sampleQuality, ResourceUsage usage, SlimDX::Direct3D10::BindFlags bindFlags, CpuAccessFlags accessFlags,
		ResourceOptionFlags optionFlags )
	{
		D3D10_TEXTURE2D_DESC desc;
		ZeroMemory( &desc, sizeof( desc ) );
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = mipLevels;
		desc.ArraySize = arraySize;
		desc.Format = static_cast<DXGI_FORMAT>( format );
		desc.SampleDesc.Count = sampleCount;
		desc.SampleDesc.Quality = sampleQuality;
		desc.Usage = static_cast<D3D10_USAGE>( usage );
		desc.BindFlags = static_cast<UINT>( bindFlags );
		desc.CPUAccessFlags = static_cast<UINT>( accessFlags );
		desc.MiscFlags = static_cast<UINT>( optionFlags );
	
		ID3D10Texture2D* texture = 0;
		HRESULT hr = device->DevicePointer->CreateTexture2D( &desc, NULL, &texture );
		GraphicsException::CheckHResult( hr );
		
		Construct(texture);
		m_Width = width;
		m_Height = height;
		m_MipLevels = mipLevels;
		m_ArraySize = arraySize;
		m_Format = format;
		m_SampleDesc.Count = sampleCount;
		m_SampleDesc.Quality = sampleQuality;
		m_Usage = usage;
		m_BindFlags = bindFlags;
		m_AccessFlags = accessFlags;
		m_OptionFlags = optionFlags;	
	}
	
	SlimDX::Direct3D::LockedRect Texture2D::Map( int mipSlice, MapMode mode, MapFlags flags )
	{
		int subResource = D3D10CalcSubresource( mipSlice, 0, MipLevels );
		int mipHeight = GetMipSize( mipSlice, Height );
		
		D3D10_MAPPED_TEXTURE2D mappedRect;
		HRESULT hr = static_cast<ID3D10Texture2D*>( InternalPointer )->Map( subResource, static_cast<D3D10_MAP>( mode ), static_cast<UINT>( flags ), &mappedRect );
		GraphicsException::CheckHResult( hr );
		
		int lockedSize = mipHeight * mappedRect.RowPitch;
		
		bool readOnly = mode == MapMode::Read;
		SlimDX::Direct3D::LockedRect rect( mappedRect.RowPitch, gcnew DataStream( mappedRect.pData, lockedSize, true, !readOnly, false ) );
		return rect;
	}

	void Texture2D::Unmap( int subResource )
	{
		static_cast<ID3D10Texture2D*>( InternalPointer )->Unmap( subResource );
	}
	
	Texture2D^ Texture2D::FromFile( Device^ device, String^ fileName )
	{
		Texture^ baseTexture = Texture::FromFile( device, fileName );
		if( baseTexture->Dimension != ResourceDimension::Texture2D )
			throw gcnew InvalidOperationException( "Could not load file as 2D texture." ); 
		return static_cast< Texture2D^ >( baseTexture );
	}
	
	Texture2D^ Texture2D::FromStream( Device^ device, Stream^ stream, int sizeInBytes )
	{
		Texture^ baseTexture = Texture::FromStream( device, stream, sizeInBytes );
		if( baseTexture->Dimension != ResourceDimension::Texture2D )
			throw gcnew InvalidOperationException( "Could not load file as 2D texture." ); 
		return static_cast< Texture2D^ >( baseTexture );
	}
}
}
