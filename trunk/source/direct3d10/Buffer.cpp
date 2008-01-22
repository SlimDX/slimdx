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

#include "Direct3D10ErrorHandler.h"

#include "Buffer.h"
#include "Device.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	Buffer::Buffer( ID3D10Buffer* buffer ) : Resource( buffer )
	{
		D3D10_BUFFER_DESC desc;
		buffer->GetDesc(&desc);
		
		m_SizeInBytes = desc.ByteWidth;
		m_Usage = (SlimDX::Direct3D10::ResourceUsage) desc.Usage;
		m_BindFlags = (SlimDX::Direct3D10::BindFlags) desc.BindFlags;
		m_AccessFlags = (SlimDX::Direct3D10::CpuAccessFlags) desc.CPUAccessFlags;
		m_OptionFlags = (SlimDX::Direct3D10::ResourceOptionFlags) desc.MiscFlags;
	}

	Buffer::Buffer( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}
	
	Buffer::Buffer( Device^ device, int sizeInBytes, ResourceUsage usage, SlimDX::Direct3D10::BindFlags bindFlags, CpuAccessFlags accessFlags, ResourceOptionFlags optionFlags )
	{
		if( sizeInBytes <= 0 )
			throw gcnew ArgumentException( "The sizeInBytes parameter must be greater than zero.", "sizeInBytes" );
		Construct(device,sizeInBytes,nullptr,usage,bindFlags,accessFlags,optionFlags);
	}
	
	Buffer::Buffer( Device^ device, int sizeInBytes, DataStream^ data, ResourceUsage usage, SlimDX::Direct3D10::BindFlags bindFlags, CpuAccessFlags accessFlags, ResourceOptionFlags optionFlags )
	{		
		if( data == nullptr )
			throw gcnew ArgumentNullException( "data" );
		Construct(device,sizeInBytes,data,usage,bindFlags,accessFlags,optionFlags);
	}
	
	DataStream^ Buffer::Map( MapMode mode, MapFlags flags )
	{
		void* mappedPtr;
		HRESULT hr = ( static_cast<ID3D10Buffer*>( InternalPointer ) )->Map( static_cast<D3D10_MAP>( mode ), static_cast<UINT>( flags ), &mappedPtr );
		Direct3D10ErrorHandler::TestForFailure( hr );

		bool readOnly = mode == MapMode::Read;
		DataStream^ stream = gcnew DataStream( mappedPtr, SizeInBytes, true, !readOnly, false );
		return stream;
	}

	void Buffer::Unmap()
	{
		( static_cast<ID3D10Buffer*>( InternalPointer ) )->Unmap();
	}
	
	void Buffer::Construct( Device^ device, int sizeInBytes, DataStream^ data, ResourceUsage usage, SlimDX::Direct3D10::BindFlags bindFlags, CpuAccessFlags accessFlags, ResourceOptionFlags optionFlags )
	{	
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
		
		m_SizeInBytes = sizeInBytes;
		m_Usage = usage;
		m_BindFlags = bindFlags;
		m_AccessFlags = accessFlags;
		m_OptionFlags = optionFlags;
		
		D3D10_BUFFER_DESC desc;
		ZeroMemory( &desc, sizeof(desc) );
		desc.ByteWidth = sizeInBytes;
		desc.Usage = static_cast<D3D10_USAGE>( usage );
		desc.BindFlags = static_cast<UINT>( bindFlags );
		desc.CPUAccessFlags = static_cast<UINT>( accessFlags );
		desc.MiscFlags = static_cast<UINT>( optionFlags );
		
		ID3D10Buffer* buffer = 0;
		HRESULT hr;
		if( data != nullptr )
		{
			if( sizeInBytes > data->Length - data->Position )
				throw gcnew InvalidOperationException( "Specified buffer size is greater than available data in specified data stream." );
		
			D3D10_SUBRESOURCE_DATA initData;
			ZeroMemory( &initData, sizeof(initData) );
			initData.pSysMem = data->RawPointer + data->Position;
			data->Position += sizeInBytes;
		
			hr = device->DevicePointer->CreateBuffer( &desc, &initData, &buffer );
		}
		else
		{
			hr = device->DevicePointer->CreateBuffer( &desc, NULL, &buffer );
		}
		Direct3D10ErrorHandler::TestForFailure( hr );
		
		Construct(buffer);
	}
}
}
