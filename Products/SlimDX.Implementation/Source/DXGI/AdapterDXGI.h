#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace DXGI
	{
		ref class Adapter : IAdapter, ComObject<IDXGIAdapter>
		{
			public:
				Adapter( IDXGIAdapter* native );
				Adapter( System::IntPtr native );
		};
	}
}