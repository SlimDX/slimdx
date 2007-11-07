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
#include <vcclr.h>

#include "GraphicsException.h"

#include "Texture2D.h"
#include "Device.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	Texture2D::Texture2D( ID3D10Texture2D* texture ) : Resource( texture )
	{
		D3D10_TEXTURE2D_DESC desc;
		texture->GetDesc( &desc );
		m_Width = desc.Width;
		m_Height = desc.Height;
		m_MipLevels = desc.MipLevels;
		m_ArraySize = desc.ArraySize;
		m_Format = ( SlimDX::Direct3D10::Format ) desc.Format;
		m_SampleDesc.Count = desc.SampleDesc.Count;
		m_SampleDesc.Quality = desc.SampleDesc.Quality;
		m_Usage = ( ResourceUsage ) desc.Usage;
		m_BindFlags = ( SlimDX::Direct3D10::BindFlags ) desc.BindFlags;
		m_AccessFlags = ( CpuAccessFlags ) desc.CPUAccessFlags;
		m_OptionFlags = ( ResourceOptionFlags ) desc.MiscFlags;
	}
	
	Texture2D::Texture2D( IntPtr texture )
	{
		if( texture == IntPtr::Zero )
			throw gcnew ArgumentNullException( "texture" );

		void* pointer;
		IUnknown* unknown = static_cast<IUnknown*>( texture.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_ID3D10Texture2D, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "QueryInterface() on user pointer failed." );

		m_Pointer = static_cast<ID3D10Resource*>( pointer );
		
		D3D10_TEXTURE2D_DESC desc;
		((ID3D10Texture2D*)m_Pointer)->GetDesc( &desc );
		m_Width = desc.Width;
		m_Height = desc.Height;
		m_MipLevels = desc.MipLevels;
		m_ArraySize = desc.ArraySize;
		m_Format = ( SlimDX::Direct3D10::Format ) desc.Format;
		m_SampleDesc.Count = desc.SampleDesc.Count;
		m_SampleDesc.Quality = desc.SampleDesc.Quality;
		m_Usage = ( ResourceUsage ) desc.Usage;
		m_BindFlags = ( SlimDX::Direct3D10::BindFlags ) desc.BindFlags;
		m_AccessFlags = ( CpuAccessFlags ) desc.CPUAccessFlags;
		m_OptionFlags = ( ResourceOptionFlags ) desc.MiscFlags;
	}
	
	Texture2D::Texture2D( Device^ device, int width, int height, int mipLevels, int arraySize, SlimDX::Direct3D10::Format format,
		int sampleCount, int sampleQuality, ResourceUsage usage, SlimDX::Direct3D10::BindFlags bindFlags, CpuAccessFlags accessFlags,
		ResourceOptionFlags optionFlags )
	{
		D3D10_TEXTURE2D_DESC desc;
		ZeroMemory( &desc, sizeof( desc ) );
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = mipLevels;
		desc.ArraySize = arraySize;
		desc.Format = ( DXGI_FORMAT ) format;
		desc.SampleDesc.Count = sampleCount;
		desc.SampleDesc.Quality = sampleQuality;
		desc.Usage = ( D3D10_USAGE ) usage;
		desc.BindFlags = ( UINT ) bindFlags;
		desc.CPUAccessFlags = ( UINT ) accessFlags;
		desc.MiscFlags = ( UINT ) optionFlags;
	
		ID3D10Texture2D* texture = 0;
		HRESULT hr = device->DevicePointer->CreateTexture2D( &desc, NULL, &texture );
		GraphicsException::CheckHResult( hr );
		
		m_Pointer = texture;
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
	
	SlimDX::Direct3D::LockedRect Texture2D::Map( int subResource, MapMode mode, MapFlags flags )
	{
		D3D10_MAPPED_TEXTURE2D mappedRect;
		HRESULT hr = ( (ID3D10Texture2D*) m_Pointer )->Map( subResource, (D3D10_MAP) mode, (UINT) flags, &mappedRect );
		GraphicsException::CheckHResult( hr );
		
		bool readOnly = mode == MapMode::Read;
		SlimDX::Direct3D::LockedRect rect;
		rect.Pitch = mappedRect.RowPitch;
		rect.Data = gcnew DataStream( mappedRect.pData, 0, true, !readOnly, false );
		
		return rect;
	}

	void Texture2D::Unmap( int subResource )
	{
		( (ID3D10Texture2D*) m_Pointer )->Unmap( subResource );
	}
	
	Texture2D^ Texture2D::FromFile( Device^ device, String^ fileName )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		ID3D10Resource* texture = 0;
		HRESULT hr = D3DX10CreateTextureFromFile( device->DevicePointer, pinnedName, NULL, NULL, &texture, NULL ); 
		GraphicsException::CheckHResult( hr );
		
		if( texture == NULL )
			return nullptr;
		return gcnew Texture2D( (ID3D10Texture2D*) texture );
	}
	
	Texture2D^ Texture2D::FromStream( Device^ device, Stream^ stream, int sizeInBytes )
	{
		array<Byte>^ memory = SlimDX::Utils::ReadStream( stream, sizeInBytes );
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		ID3D10Resource* texture;
		HRESULT hr = D3DX10CreateTextureFromMemory( device->DevicePointer, pinnedMemory, sizeInBytes, NULL, NULL, &texture, NULL ); 
		GraphicsException::CheckHResult( hr );
		
		if( texture == NULL )
			return nullptr;
		return gcnew Texture2D( (ID3D10Texture2D*) texture );
	}
}
}
