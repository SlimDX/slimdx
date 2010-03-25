#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace DXGI
	{
		ref class SwapChainDXGI : ISwapChainDXGI, ComObject<IDXGISwapChain>
		{
			public:
				SwapChainDXGI( IDXGISwapChain* native );
				SwapChainDXGI( System::IntPtr native );
				
				generic<typename T>
				virtual T GetBuffer( int index );

				virtual void Present(int syncInterval, PresentFlags presentFlags);
		};
	}
}