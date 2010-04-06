#include "stdafx.h"
#include "inputlayout10.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		InputLayout10::InputLayout10( ID3D10InputLayout* native ) : ComObject<ID3D10InputLayout>(native) {
		}
		InputLayout10::InputLayout10( System::IntPtr native ) : ComObject<ID3D10InputLayout>(native) {
		}
	}
}