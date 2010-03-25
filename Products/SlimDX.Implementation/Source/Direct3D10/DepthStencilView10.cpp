#include "stdafx.h"

#include "DepthStencilView10.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D10
	{
		DepthStencilView10::DepthStencilView10( ID3D10DepthStencilView* native )
			: ComObject( native )
		{
		}

		DepthStencilView10::DepthStencilView10( IntPtr native )
			: ComObject( native )
		{
		}
	}
}