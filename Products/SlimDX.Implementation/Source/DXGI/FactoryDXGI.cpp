#include "stdafx.h"

#include "FactoryDXGI.h"

#include "../Common/Utilities.h"
#include "SwapChainDXGI.h"

using namespace System;

namespace SlimDX
{
	namespace DXGI
	{
		Factory::Factory( IDXGIFactory* native )
		: ComObject( native )
		{
		}
		
		Factory::Factory( IntPtr native )
		: ComObject( native )
		{
		}
		
		ISwapChain^ Factory::CreateSwapChain( IComObject^ device, SwapChainDescription^ description )
		{
			IDXGISwapChain* object = 0;
			DXGI_SWAP_CHAIN_DESC nativeDescription = Utilities::ToNative( description );
			HRESULT hr = NativePointer->CreateSwapChain( Utilities::ToUnknown( device ), &nativeDescription, &object );
			return gcnew SwapChain( object );
		}
	}
}