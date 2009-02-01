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

#include "Buffer.h"
#include "CounterCapabilities.h"
#include "CounterDescription.h"
#include "CounterMetadata.h"
#include "DepthStencilView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "InputAssemblerWrapper.h"
#include "InputLayout.h"
#include "OutputMergerWrapper.h"
#include "RasterizerWrapper.h"
#include "RenderTargetView.h"
#include "Resource.h"
#include "ResourceRegion.h"
#include "ShaderResourceView.h"
#include "StreamOutputWrapper.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{
	Device::Device( ID3D11Device* pointer )
	{
		Construct( pointer );
	}
	
	Device::Device( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}
	
	Device::Device( DeviceCreationFlags flags )
	{
		ID3D11Device* device = 0;
		ID3D11DeviceContext* immediateContext = 0;
		RECORD_D3D11( D3D11CreateDevice( 0, D3D_DRIVER_TYPE_HARDWARE, 0, static_cast<UINT>( flags ), 0, 0, D3D11_SDK_VERSION, &device, 0, &immediateContext ) );
		if( Result::Last.IsFailure )
			throw gcnew Direct3D11Exception( Result::Last );
		
		Construct( device );

		m_ImmediateContext = DeviceContext::FromPointer( immediateContext );
	}
	
	Device::Device( DriverType driverType, DeviceCreationFlags flags )
	{
		ID3D11Device* device = 0;
		ID3D11DeviceContext* immediateContext = 0;
		RECORD_D3D11( D3D11CreateDevice( 0, static_cast<D3D_DRIVER_TYPE>( driverType ), 0, static_cast<UINT>( flags ), 0, 0, D3D11_SDK_VERSION, &device, 0, &immediateContext ) );
		if( Result::Last.IsFailure )
			throw gcnew Direct3D11Exception( Result::Last );
		
		Construct( device );

		m_ImmediateContext = DeviceContext::FromPointer( immediateContext );
	}
	
	Device::Device( DXGI::Adapter^ adapter, DriverType driverType, DeviceCreationFlags flags )
	{
		IDXGIAdapter* nativeAdapter = adapter == nullptr ? 0 : adapter->InternalPointer;
		ID3D11Device* device = 0;
		ID3D11DeviceContext* immediateContext = 0;
		RECORD_D3D11( D3D11CreateDevice( nativeAdapter, static_cast<D3D_DRIVER_TYPE>( driverType ), 0, static_cast<UINT>( flags ), 0, 0, D3D11_SDK_VERSION, &device, 0, &immediateContext ) );
		if( Result::Last.IsFailure )
			throw gcnew Direct3D11Exception( Result::Last );
		
		Construct( device );

		m_ImmediateContext = DeviceContext::FromPointer( immediateContext );
	}
	
	DeviceCreationFlags Device::CreationFlags::get()
	{
		return static_cast<DeviceCreationFlags>( InternalPointer->GetCreationFlags() );
	}
	
	DeviceContext^ Device::ImmediateContext::get()
	{
		return m_ImmediateContext;
	}

	DeviceContext^ Device::CreateDeferredContext()
	{
		ID3D11DeviceContext *context;
		HRESULT hr = InternalPointer->CreateDeferredContext( 0, &context);
		RECORD_D3D11(hr);
		if( Result::Last.IsFailure )
		{
			return nullptr;
		}
		return DeviceContext::FromPointer( context );
	}
	
	CounterCapabilities Device::GetCounterCapabilities()
	{
		D3D11_COUNTER_INFO info;
		InternalPointer->CheckCounterInfo( &info );
		return CounterCapabilities( info );
	}
	
	CounterMetadata Device::GetCounterMetadata( CounterDescription description )
	{
		D3D11_COUNTER_DESC nativeDescription = description.CreateNativeVersion();
		D3D11_COUNTER_TYPE type;
		UINT count = 0;
		UINT nameLength = 0;
		UINT unitsLength = 0;
		UINT descriptionLength = 0;
		if( RECORD_D3D11( InternalPointer->CheckCounter( &nativeDescription, &type, &count, 0, &nameLength, 0, &unitsLength, 0, &descriptionLength ) ).IsFailure )
			return CounterMetadata();
		
		std::vector<char> nameChars( nameLength );
		std::vector<char> unitsChars( unitsLength );
		std::vector<char> descriptionChars( descriptionLength );
		if( RECORD_D3D11( InternalPointer->CheckCounter( &nativeDescription, &type, &count, &nameChars[ 0 ], &nameLength, &unitsChars[ 0 ], &unitsLength, &descriptionChars[ 0 ], &descriptionLength ) ).IsFailure )
			return CounterMetadata();
			
		return CounterMetadata( static_cast<CounterType>( type ), count, gcnew String( &nameChars[ 0 ] ), gcnew String( &unitsChars[ 0 ] ), gcnew String( &descriptionChars[ 0 ] ) );	
	}
	
	FormatSupport Device::CheckFormatSupport( DXGI::Format format )
	{
		UINT support = 0;
		InternalPointer->CheckFormatSupport( static_cast<DXGI_FORMAT>( format ), &support );
		return static_cast<FormatSupport>( support );
	}
	
	int Device::CheckMultisampleQualityLevels( DXGI::Format format, int sampleCount )
	{
		UINT result = 0;
		InternalPointer->CheckMultisampleQualityLevels( static_cast<DXGI_FORMAT>( format ), sampleCount, &result );
		return result;
	}
	
	Result Device::CreateWithSwapChain( DXGI::Adapter^ adapter, DriverType driverType, DeviceCreationFlags flags, DXGI::SwapChainDescription swapChainDescription, [Out] Device^ %device, [Out] DXGI::SwapChain^ %swapChain )
	{
		IDXGIAdapter* nativeAdapter = adapter == nullptr ? 0 : adapter->InternalPointer;
		ID3D11Device* resultDevice = 0;
		IDXGISwapChain* resultSwapChain = 0;
		DXGI_SWAP_CHAIN_DESC nativeDescription = swapChainDescription.CreateNativeVersion();
		
		ID3D11DeviceContext* immediateContext = 0;
		if( RECORD_D3D11( D3D11CreateDeviceAndSwapChain( nativeAdapter, static_cast<D3D_DRIVER_TYPE>( driverType ), 0, static_cast<UINT>( flags ), 0, 0, D3D11_SDK_VERSION, &nativeDescription, &resultSwapChain, &resultDevice, 0, &immediateContext ) ).IsSuccess )
		{
			device = FromPointer( resultDevice );
			swapChain = DXGI::SwapChain::FromPointer( resultSwapChain );
			device->m_ImmediateContext = DeviceContext::FromPointer( immediateContext );
		}
		else {
			device = nullptr;
			swapChain = nullptr;
		}	
	
		return Result::Last;
	}
}
}
