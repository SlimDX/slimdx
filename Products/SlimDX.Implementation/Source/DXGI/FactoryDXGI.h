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
				
				virtual ISwapChain^ CreateSwapChain( IComObject^ device, SwapChainDescription^ description );
		};
	}
}