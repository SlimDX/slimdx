#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Buffer10 : IBuffer10, ComObject<ID3D10Buffer>
		{
			public:
				Buffer10( ID3D10Buffer* native );
				Buffer10( System::IntPtr native );

				property BufferDescription10 Description {
					virtual BufferDescription10 get();
				}

				virtual IMemoryBuffer^ Map(MapMode10 mapMode);
				virtual void Unmap();
		};
	}
}