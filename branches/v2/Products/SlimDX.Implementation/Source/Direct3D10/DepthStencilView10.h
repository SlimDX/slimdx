#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class DepthStencilView : IDepthStencilView, ComObject<ID3D10DepthStencilView>
		{
			public:
				DepthStencilView( ID3D10DepthStencilView* native );
				DepthStencilView( System::IntPtr native );
		};
	}
}