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

#include "Texture3D.h"
#include "Device.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	Texture3D::Texture3D( ID3D10Texture3D* texture ) : Texture( texture )
	{
		Construct( texture );
	}
	
	Texture3D::Texture3D( IntPtr nativeObject )
	{
		if( nativeObject == IntPtr::Zero )
			throw gcnew ArgumentNullException( "nativeObject" );

		void* pointer;
		IUnknown* unknown = static_cast<IUnknown*>( nativeObject.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_ID3D10Texture3D, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "QueryInterface() on user pointer failed." );

		Construct( static_cast<ID3D10Texture3D*>( pointer ) );
	}
	
	void Texture3D::Construct( ID3D10Texture3D* pointer )
	{
		m_Pointer = pointer;
		
		D3D10_TEXTURE3D_DESC desc;
		static_cast<ID3D10Texture3D*>( m_Pointer )->GetDesc( &desc );
		
		m_Width = desc.Width;
		m_Height = desc.Height;
		m_Depth = desc.Depth;
		m_MipLevels = desc.MipLevels;
		m_Format = static_cast<SlimDX::Direct3D10::Format>( desc.Format );
		m_Usage = static_cast<ResourceUsage>( desc.Usage );
		m_BindFlags = static_cast<SlimDX::Direct3D10::BindFlags>( desc.BindFlags );
		m_AccessFlags = static_cast<CpuAccessFlags>( desc.CPUAccessFlags );
		m_OptionFlags = static_cast<ResourceOptionFlags>( desc.MiscFlags );
	}
	
	Texture3D::Texture3D( Device^ device, int width, int height, int depth, int mipLevels, SlimDX::Direct3D10::Format format,
		ResourceUsage usage, SlimDX::Direct3D10::BindFlags bindFlags, CpuAccessFlags accessFlags, ResourceOptionFlags optionFlags )
	{
		D3D10_TEXTURE3D_DESC desc;
		ZeroMemory( &desc, sizeof( desc ) );
		desc.Width = width;
		desc.Height = height;
		desc.Depth = depth;
		desc.MipLevels = mipLevels;
		desc.Format = static_cast<DXGI_FORMAT>( format );
		desc.Usage = static_cast<D3D10_USAGE>( usage );
		desc.BindFlags = static_cast<UINT>( bindFlags );
		desc.CPUAccessFlags = static_cast<UINT>( accessFlags );
		desc.MiscFlags = static_cast<UINT>( optionFlags );
	
		ID3D10Texture3D* texture;
		HRESULT hr = device->DevicePointer->CreateTexture3D( &desc, NULL, &texture );
		GraphicsException::CheckHResult( hr );
		
		Construct( texture );	
	}
	
	SlimDX::Direct3D::LockedBox Texture3D::Map( int mipSlice, MapMode mode, MapFlags flags )
	{
		int subResource = D3D10CalcSubresource( mipSlice, 0, MipLevels );
		int mipHeight = GetMipSize( mipSlice, Height );
		
		D3D10_MAPPED_TEXTURE3D mappedBox;
		HRESULT hr = static_cast<ID3D10Texture3D*>( m_Pointer )->Map( subResource, static_cast<D3D10_MAP>( mode ), static_cast<UINT>( flags ), &mappedBox );
		GraphicsException::CheckHResult( hr );
		
		int lockedSize = mipHeight * mappedBox.RowPitch * mappedBox.DepthPitch;
		
		bool readOnly = mode == MapMode::Read;
		SlimDX::Direct3D::LockedBox box( mappedBox.RowPitch, mappedBox.DepthPitch, gcnew DataStream( mappedBox.pData, lockedSize, true, !readOnly, false ) );
		
		return box;
	}

	void Texture3D::Unmap( int subResource )
	{
		static_cast<ID3D10Texture3D*>( m_Pointer )->Unmap( subResource );
	}
	
	Texture3D^ Texture3D::FromFile( Device^ device, String^ fileName )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		ID3D10Resource* texture = 0;
		HRESULT hr = D3DX10CreateTextureFromFile( device->DevicePointer, pinnedName, NULL, NULL, &texture, NULL ); 
		GraphicsException::CheckHResult( hr );
		
		if( texture == NULL )
			return nullptr;
		return gcnew Texture3D( static_cast<ID3D10Texture3D*>( texture ) );
	}
	
	Texture3D^ Texture3D::FromStream( Device^ device, Stream^ stream, int sizeInBytes )
	{
		array<Byte>^ memory = SlimDX::Utils::ReadStream( stream, sizeInBytes );
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		ID3D10Resource* texture;
		HRESULT hr = D3DX10CreateTextureFromMemory( device->DevicePointer, pinnedMemory, sizeInBytes, NULL, NULL, &texture, NULL ); 
		GraphicsException::CheckHResult( hr );
		
		if( texture == NULL )
			return nullptr;
		return gcnew Texture3D( static_cast<ID3D10Texture3D*>( texture ) );
	}
}
}
