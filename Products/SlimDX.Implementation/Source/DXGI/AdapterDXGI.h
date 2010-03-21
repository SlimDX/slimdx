#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace DXGI
	{
		ref class AdapterDXGI : IAdapterDXGI, ComObject<IDXGIAdapter>
		{
			public:
				AdapterDXGI( IDXGIAdapter* native );
				AdapterDXGI( System::IntPtr native );
		};
	}
}