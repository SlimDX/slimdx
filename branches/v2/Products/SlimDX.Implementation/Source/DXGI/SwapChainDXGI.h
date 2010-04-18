#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace DXGI
	{
		ref class SwapChain : ISwapChain, ComObject<IDXGISwapChain>
		{
			public:
				SwapChain( IDXGISwapChain* native );
				SwapChain( System::IntPtr native );
				
				generic<typename T>
				virtual T GetBuffer( int index );

				virtual void Present(int syncInterval, PresentFlags presentFlags);
		};
	}
}