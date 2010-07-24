#include "stdafx.h"

#include "SwapChainDXGI.h"

#include "../Common/Utility.h"

using namespace System;

namespace SlimDX
{
	namespace DXGI
	{
		SwapChain::SwapChain( IDXGISwapChain* native )
		: ComObject( native )
		{
		}
		
		SwapChain::SwapChain( IntPtr native )
		: ComObject( native )
		{
		}
		
		generic<typename T>
		T SwapChain::GetBuffer( int index )
		{
			void* result = 0;
			IID iid = Utilities::ToNative( Utilities::GetInterfaceID<T>() );
			Type^ target = Utilities::GetInterfaceImplementation<T>();
			HRESULT hr = NativePointer->GetBuffer( index, iid, &result );
			
			return (T)Activator::CreateInstance( target, IntPtr( result ) );
		}

		void SwapChain::Present(int syncInterval, PresentFlags presentFlags) {
			HRESULT hr = NativePointer->Present(syncInterval, static_cast<UINT>(presentFlags));
		}
	}
}