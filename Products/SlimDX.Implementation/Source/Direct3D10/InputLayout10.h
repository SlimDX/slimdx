#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class InputLayout10 : IInputLayout10, ComObject<ID3D10InputLayout>
		{
			public:
				InputLayout10( ID3D10InputLayout* native );
				InputLayout10( System::IntPtr native );
		};
	}
}