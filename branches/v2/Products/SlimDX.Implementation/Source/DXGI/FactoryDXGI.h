#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace DXGI
	{
		ref class Factory : IFactory, ComObject<IDXGIFactory>
		{
			public:
				Factory( IDXGIFactory* native );
				Factory( System::IntPtr native );

				virtual IAdapter^ CreateSoftwareAdapter( System::Reflection::Module^ module );
				virtual IAdapter^ CreateSoftwareAdapter( System::IntPtr module );
				virtual ISwapChain^ CreateSwapChain( IComObject^ device, SwapChainDescription^ description );
				virtual System::IntPtr GetWindowAssociation();
				virtual Result SetWindowAssociation( System::IntPtr window, WindowAssociationFlags flags );
		};
	}
}