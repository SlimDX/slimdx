#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class DepthStencilView10 : IDepthStencilView10, ComObject<ID3D10DepthStencilView>
		{
			public:
				DepthStencilView10( ID3D10DepthStencilView* native );
				DepthStencilView10( System::IntPtr native );
		};
	}
}