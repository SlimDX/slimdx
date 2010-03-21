#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Device10 : IDevice10, ComObject<ID3D10Device>
		{
			public:
				Device10( ID3D10Device* native );
				Device10( System::IntPtr native );
				
			private:
				ID3D10Device* m_Native;
		};
	}
}