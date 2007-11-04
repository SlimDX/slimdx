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

#include "Texture1D.h"
#include "Device.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	Texture1D::Texture1D( ID3D10Texture1D* texture ) : Resource( texture )
	{
		Construct( texture );
	}
	
	Texture1D::Texture1D( IntPtr nativeObject )
	{
		if( nativeObject == IntPtr::Zero )
			throw gcnew ArgumentNullException( "nativeObject" );

		void* pointer;
		IUnknown* unknown = (IUnknown*) nativeObject.ToPointer();
		HRESULT hr = unknown->QueryInterface( IID_ID3D10Texture1D, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "QueryInterface() on user pointer failed." );

		Construct( (ID3D10Texture1D*) pointer );
	}
	
	void Texture1D::Construct( ID3D10Texture1D* pointer )
	{
		m_Pointer = pointer;
		
		D3D10_TEXTURE1D_DESC desc;
		( (ID3D10Texture1D*) m_Pointer )->GetDesc( &desc );
		
		m_Width = desc.Width;
		m_MipLevels = desc.MipLevels;
		m_ArraySize = desc.ArraySize;
		m_Format = (SlimDX::Direct3D10::Format) desc.Format;
		m_Usage = (ResourceUsage) desc.Usage;
		m_BindFlags = (SlimDX::Direct3D10::BindFlags) desc.BindFlags;
		m_AccessFlags = (CpuAccessFlags) desc.CPUAccessFlags;
		m_OptionFlags = (ResourceOptionFlags) desc.MiscFlags;
	}
	
	Texture1D::Texture1D( Device^ device, int width, int mipLevels, int arraySize, SlimDX::Direct3D10::Format format,
		ResourceUsage usage, SlimDX::Direct3D10::BindFlags bindFlags, CpuAccessFlags accessFlags, ResourceOptionFlags optionFlags )
	{
		D3D10_TEXTURE1D_DESC desc;
		ZeroMemory( &desc, sizeof( desc ) );
		desc.Width = width;
		desc.MipLevels = mipLevels;
		desc.ArraySize = arraySize;
		desc.Format = (DXGI_FORMAT) format;
		desc.Usage = (D3D10_USAGE) usage;
		desc.BindFlags = (UINT) bindFlags;
		desc.CPUAccessFlags = (UINT) accessFlags;
		desc.MiscFlags = (UINT) optionFlags;
	
		ID3D10Texture1D* texture;
		HRESULT hr = device->DevicePointer->CreateTexture1D( &desc, NULL, &texture );
		GraphicsException::CheckHResult( hr );
		
		Construct( texture );	
	}
	
	DataStream^ Texture1D::Map( int subResource, MapMode mode, MapFlags flags )
	{
		void* mappedArray;
		HRESULT hr = ( (ID3D10Texture1D*) m_Pointer )->Map( subResource, (D3D10_MAP) mode, (UINT) flags, &mappedArray );
		GraphicsException::CheckHResult( hr );
		
		bool readOnly = mode == MapMode::Read;
		return gcnew DataStream( mappedArray, 0, true, !readOnly, false );
	}

	void Texture1D::Unmap( int subResource )
	{
		( (ID3D10Texture1D*) m_Pointer )->Unmap( subResource );
	}
	
	Texture1D^ Texture1D::FromFile( Device^ device, String^ fileName )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		ID3D10Resource* texture = 0;
		HRESULT hr = D3DX10CreateTextureFromFile( device->DevicePointer, pinnedName, NULL, NULL, &texture, NULL ); 
		GraphicsException::CheckHResult( hr );
		
		if( texture == NULL )
			return nullptr;
		return gcnew Texture1D( (ID3D10Texture1D*) texture );
	}
	
	Texture1D^ Texture1D::FromStream( Device^ device, Stream^ stream, int sizeInBytes )
	{
		array<Byte>^ memory = SlimDX::Utils::ReadStream( stream, sizeInBytes );
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		ID3D10Resource* texture;
		HRESULT hr = D3DX10CreateTextureFromMemory( device->DevicePointer, pinnedMemory, sizeInBytes, NULL, NULL, &texture, NULL ); 
		GraphicsException::CheckHResult( hr );
		
		if( texture == NULL )
			return nullptr;
		return gcnew Texture1D( (ID3D10Texture1D*) texture );
	}
}
}
