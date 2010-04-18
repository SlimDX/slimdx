#include "stdafx.h"
#include "inputlayout10.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		InputLayout::InputLayout( ID3D10InputLayout* native ) : ComObject<ID3D10InputLayout>(native) {
		}
		
		InputLayout::InputLayout( System::IntPtr native ) : ComObject<ID3D10InputLayout>(native) {
		}
	}
}