#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class InputLayout : IInputLayout, ComObject<ID3D10InputLayout>
		{
			public:
				InputLayout( ID3D10InputLayout* native );
				InputLayout( System::IntPtr native );
		};
	}
}