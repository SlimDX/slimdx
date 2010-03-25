#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class RenderTargetView10 : IRenderTargetView10, ComObject<ID3D10RenderTargetView>
		{
			public:
				RenderTargetView10( ID3D10RenderTargetView* native );
				RenderTargetView10( System::IntPtr native );
		};
	}
}