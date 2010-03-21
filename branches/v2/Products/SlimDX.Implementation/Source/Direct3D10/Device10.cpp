#include "stdafx.h"

#include "Device10.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D10
	{
		Device10::Device10( ID3D10Device* native )
		: ComObject( native )
		{
		}
		
		Device10::Device10( IntPtr native )
		: ComObject( native )
		{
		}
	}
}