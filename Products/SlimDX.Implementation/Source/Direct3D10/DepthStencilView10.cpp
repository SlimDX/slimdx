#include "stdafx.h"

#include "DepthStencilView10.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D10
	{
		DepthStencilView::DepthStencilView( ID3D10DepthStencilView* native )
			: ComObject( native )
		{
		}

		DepthStencilView::DepthStencilView( IntPtr native )
			: ComObject( native )
		{
		}
	}
}