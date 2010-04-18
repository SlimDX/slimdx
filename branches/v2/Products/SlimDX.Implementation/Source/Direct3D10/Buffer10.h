#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Buffer : IBuffer, ComObject<ID3D10Buffer>
		{
			public:
				Buffer( ID3D10Buffer* native );
				Buffer( System::IntPtr native );

				property BufferDescription Description {
					virtual BufferDescription get();
				}

				virtual IMemoryBuffer^ Map(MapMode mapMode);
				virtual void Unmap();
		};
	}
}