#include "stdafx.h"

#include "SwapChainDXGI.h"

#include "../Common/Utilities.h"

using namespace System;

namespace SlimDX
{
	namespace DXGI
	{
		SwapChainDXGI::SwapChainDXGI( IDXGISwapChain* native )
		: ComObject( native )
		{
		}
		
		SwapChainDXGI::SwapChainDXGI( IntPtr native )
		: ComObject( native )
		{
		}
		
		generic<typename T>
		T SwapChainDXGI::GetBuffer( int index )
		{
			void* result = 0;
			IID iid = Utilities::ToNative( Utilities::GetInterfaceID<T>() );
			Type^ target = Utilities::GetInterfaceImplementation<T>();
			HRESULT hr = NativePointer->GetBuffer( index, iid, &result );
			
			return (T)Activator::CreateInstance( target, IntPtr( result ) );
		}
	}
}