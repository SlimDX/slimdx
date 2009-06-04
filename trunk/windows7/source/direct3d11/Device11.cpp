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
#include "stdafx.h"

#include "../../../source/stack_array.h"

#include "Direct3D11Exception.h"

#include "Buffer11.h"
#include "CounterCapabilities11.h"
#include "CounterDescription11.h"
#include "CounterMetadata11.h"
#include "DepthStencilView11.h"
#include "Device11.h"
#include "InputLayout11.h"
#include "Predicate11.h"
#include "RenderTargetView11.h"
#include "Resource11.h"
#include "ResourceRegion11.h"
#include "ShaderResourceView11.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{
	Device::Device( DXGI::Adapter^ adapter )
	{
		Initialize( adapter, DriverType::Unknown, DeviceCreationFlags::None, NULL, 0 );
	}

	Device::Device( DXGI::Adapter^ adapter, DeviceCreationFlags flags )
	{
		Initialize( adapter, DriverType::Unknown, flags, NULL, 0 );
	}

	Device::Device( DXGI::Adapter^ adapter, DeviceCreationFlags flags, ... array<FeatureLevel>^ featureLevels )
	{
		if( featureLevels == nullptr || featureLevels->Length == 0 )
			Initialize( adapter, DriverType::Unknown, flags, NULL, 0 );
		else
		{
			pin_ptr<FeatureLevel> pinnedLevels = &featureLevels[0];
			Initialize( adapter, DriverType::Unknown, flags, reinterpret_cast<const D3D_FEATURE_LEVEL*>( pinnedLevels ), featureLevels->Length );
		}
	}

	Device::Device( DriverType driverType )
	{
		Initialize( nullptr, driverType, DeviceCreationFlags::None, NULL, 0 );
	}

	Device::Device( DriverType driverType, DeviceCreationFlags flags )
	{
		Initialize( nullptr, driverType, flags, NULL, 0 );
	}

	Device::Device( DriverType driverType, DeviceCreationFlags flags, ... array<FeatureLevel>^ featureLevels )
	{
		if( featureLevels == nullptr || featureLevels->Length == 0 )
			Initialize( nullptr, driverType, flags, NULL, 0 );
		else
		{
			pin_ptr<FeatureLevel> pinnedLevels = &featureLevels[0];
			Initialize( nullptr, driverType, flags, reinterpret_cast<const D3D_FEATURE_LEVEL*>( pinnedLevels ), featureLevels->Length );
		}
	}

	void Device::Initialize( DXGI::Adapter^ adapter, DriverType driverType, DeviceCreationFlags flags, const D3D_FEATURE_LEVEL *featureLevels, int count )
	{
		IDXGIAdapter* nativeAdapter = adapter == nullptr ? 0 : adapter->InternalPointer;
		ID3D11Device* device = 0;

		HRESULT hr = D3D11CreateDevice( nativeAdapter, static_cast<D3D_DRIVER_TYPE>( driverType ), NULL, static_cast<UINT>( flags ), 
			featureLevels, count, D3D11_SDK_VERSION, &device, NULL, NULL );

		if( RECORD_D3D11( hr ).IsFailure )
			throw gcnew Direct3D11Exception( Result::Last );

		Construct( device );
	}

	DeviceCreationFlags Device::CreationFlags::get()
	{
		return static_cast<DeviceCreationFlags>( InternalPointer->GetCreationFlags() );
	}

	Result Device::DeviceRemovedReason::get()
	{
		return Result( InternalPointer->GetDeviceRemovedReason() );
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
		
		stack_array<char> nameChars = stackalloc( char, nameLength );
		stack_array<char> unitsChars = stackalloc( char, unitsLength );
		stack_array<char> descriptionChars = stackalloc( char, descriptionLength );

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
		return CreateWithSwapChain( adapter, driverType, flags, nullptr, swapChainDescription, device, swapChain );
	}

	Result Device::CreateWithSwapChain( DXGI::Adapter^ adapter, DriverType driverType, DeviceCreationFlags flags, 
		array<FeatureLevel>^ featureLevels, DXGI::SwapChainDescription swapChainDescription, [Out] Device^ %device, [Out] DXGI::SwapChain^ %swapChain )
	{
		IDXGIAdapter* nativeAdapter = adapter == nullptr ? 0 : adapter->InternalPointer;
		ID3D11Device* resultDevice = 0;
		IDXGISwapChain* resultSwapChain = 0;
		DXGI_SWAP_CHAIN_DESC nativeDescription = swapChainDescription.CreateNativeVersion();

		const D3D_FEATURE_LEVEL* nativeLevels = NULL;
		pin_ptr<FeatureLevel> pinnedLevels;

		if( featureLevels != nullptr && featureLevels->Length > 0 )
		{
			pinnedLevels = &featureLevels[0];
			nativeLevels = reinterpret_cast<const D3D_FEATURE_LEVEL*>( pinnedLevels );
		}
		
		HRESULT hr = D3D11CreateDeviceAndSwapChain( nativeAdapter, static_cast<D3D_DRIVER_TYPE>( driverType ), 0, static_cast<UINT>( flags ), 
			nativeLevels, featureLevels->Length, D3D11_SDK_VERSION, 
			&nativeDescription, &resultSwapChain, &resultDevice, NULL, NULL );

		if( RECORD_D3D11( hr ).IsFailure )
		{
			device = nullptr;
			swapChain = nullptr;
		}
		else
		{
			device = FromPointer( resultDevice );
			swapChain = DXGI::SwapChain::FromPointer( resultSwapChain );
		}
		
		return Result::Last;
	}
}
}
