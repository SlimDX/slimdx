#include "stdafx.h"

#include "RenderTargetView10.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D10
	{
		RenderTargetView10::RenderTargetView10( ID3D10RenderTargetView* native )
		: ComObject( native )
		{
		}
		
		RenderTargetView10::RenderTargetView10( IntPtr native )
		: ComObject( native )
		{
		}
	}
}