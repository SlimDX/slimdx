#include "stdafx.h"

#include "FactoryDXGI.h"

#include "../Common/Utilities.h"
#include "SwapChainDXGI.h"

using namespace System;

namespace SlimDX
{
	namespace DXGI
	{
		FactoryDXGI::FactoryDXGI( IDXGIFactory* native )
		: ComObject( native )
		{
		}
		
		FactoryDXGI::FactoryDXGI( IntPtr native )
		: ComObject( native )
		{
		}
		
		ISwapChainDXGI^ FactoryDXGI::CreateSwapChain( IComObject^ device, SwapChainDescription^ description )
		{
			IDXGISwapChain* object = 0;
			DXGI_SWAP_CHAIN_DESC nativeDescription = Utilities::ToNative( description );
			HRESULT hr = NativePointer->CreateSwapChain( Utilities::ToUnknown( device ), &nativeDescription, &object );
			return gcnew SwapChainDXGI( object );
		}
	}
}