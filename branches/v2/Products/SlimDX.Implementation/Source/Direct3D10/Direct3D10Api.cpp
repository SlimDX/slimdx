#include "stdafx.h"

#include "Direct3D10Api.h"
#include "Direct3D10Recorder.h"

#include "../Common/Utilities.h"
#include "../DXGI/SwapChainDXGI.h"

#include "Device10.h"
#include "Texture2D10.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Reflection;

namespace SlimDX
{
	namespace Direct3D10
	{
		Direct3D10Api::Direct3D10Api()
		{
		}
		
		generic< typename T >
		T Direct3D10Api::CreateWrapper( IntPtr pointer )
		{
			Type^ target = Utilities::GetInterfaceImplementation<T>();
			return (T)Activator::CreateInstance( target, pointer );
		}
		
		IDevice10^ Direct3D10Api::CreateDevice()
		{
			return nullptr;//gcnew Device10();
		}

		SlimDX::Result Direct3D10Api::CreateDeviceAndSwapChain( SlimDX::DXGI::IAdapterDXGI^ adapter, DriverType driverType, DeviceCreationFlags creationFlags, SlimDX::DXGI::SwapChainDescription^ swapChainDescription, [Out] IDevice10^% device, [Out] SlimDX::DXGI::ISwapChainDXGI^% swapChain )
		{
			ID3D10Device* nativeDevice = 0;
			IDXGISwapChain* nativeSwapChain = 0;
			DXGI_SWAP_CHAIN_DESC nativeSwapChainDescription = Utilities::ToNative( swapChainDescription );
			
			HRESULT hr = D3D10CreateDeviceAndSwapChain(
				0,
				static_cast<D3D10_DRIVER_TYPE>( driverType ),
				0,
				static_cast<UINT>( creationFlags ),
				D3D10_SDK_VERSION,
				&nativeSwapChainDescription,
				&nativeSwapChain,
				&nativeDevice
			);
			
			if( RecordResult( hr ).IsSuccess )
			{
				device = gcnew Device10( nativeDevice );
				swapChain = gcnew SlimDX::DXGI::SwapChainDXGI( nativeSwapChain );
			}
			else
			{
				device = nullptr;
				swapChain = nullptr;
			}
			
			return Result::Last;
		}
	}
}