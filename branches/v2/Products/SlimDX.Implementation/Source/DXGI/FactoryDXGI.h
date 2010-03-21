#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace DXGI
	{
		ref class FactoryDXGI : IFactoryDXGI, ComObject<IDXGIFactory>
		{
			public:
				FactoryDXGI( IDXGIFactory* native );
				FactoryDXGI( System::IntPtr native );
				
				virtual ISwapChainDXGI^ CreateSwapChain( IComObject^ device, SwapChainDescription^ description );
		};
	}
}