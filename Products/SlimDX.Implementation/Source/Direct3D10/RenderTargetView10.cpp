#include "stdafx.h"

#include "RenderTargetView10.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D10
	{
		RenderTargetView::RenderTargetView( ID3D10RenderTargetView* native )
		: ComObject( native )
		{
		}
		
		RenderTargetView::RenderTargetView( IntPtr native )
		: ComObject( native )
		{
		}
	}
}