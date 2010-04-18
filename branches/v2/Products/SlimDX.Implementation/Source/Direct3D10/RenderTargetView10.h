#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class RenderTargetView : IRenderTargetView, ComObject<ID3D10RenderTargetView>
		{
			public:
				RenderTargetView( ID3D10RenderTargetView* native );
				RenderTargetView( System::IntPtr native );
		};
	}
}