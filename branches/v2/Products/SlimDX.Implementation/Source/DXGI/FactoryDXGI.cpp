#include "stdafx.h"

#include "FactoryDXGI.h"

#include "../Common/ArgumentMacros.h"
#include "../Common/Utilities.h"
#include "AdapterDXGI.h"
#include "SwapChainDXGI.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::InteropServices;

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
		
		IAdapter^ Factory::CreateSoftwareAdapter( Module^ module )
		{
			return CreateSoftwareAdapter( Marshal::GetHINSTANCE( module ) );
		}

		IAdapter^ Factory::CreateSoftwareAdapter( IntPtr module )
		{
			SDX_THROW_IF_NULL( module );
			
			HINSTANCE instance = reinterpret_cast<HINSTANCE>( module.ToPointer() );
			IDXGIAdapter* adapter = 0;
			SDX_RECORD_HR( NativePointer->CreateSoftwareAdapter( instance, &adapter ) );
			
			SDX_RETURN( Adapter, adapter );
		}

		ISwapChain^ Factory::CreateSwapChain( IComObject^ device, SwapChainDescription^ description )
		{
			SDX_THROW_IF_NULL( device );
			SDX_THROW_IF_NULL( description );

			IDXGISwapChain* swapChain = 0;
			DXGI_SWAP_CHAIN_DESC swapChainDescription = Utilities::ToNative( description );
			SDX_RECORD_HR( NativePointer->CreateSwapChain( Utilities::ToUnknown( device ), &swapChainDescription, &swapChain ) );
			
			SDX_RETURN( SwapChain, swapChain );
		}

		System::IntPtr Factory::GetWindowAssociation()
		{
			HWND window = 0;
			SDX_RECORD_HR( NativePointer->GetWindowAssociation( &window ) );

			return IntPtr( window );
		}

		Result Factory::SetWindowAssociation( IntPtr window, WindowAssociationFlags flags )
		{
			return SDX_RECORD_HR( NativePointer->MakeWindowAssociation( reinterpret_cast<HWND>( window.ToPointer() ), static_cast<UINT>( flags ) ) );
		}
	}
}