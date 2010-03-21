#include "stdafx.h"

#include "AdapterDXGI.h"

using namespace System;

namespace SlimDX
{
	namespace DXGI
	{
		AdapterDXGI::AdapterDXGI( IDXGIAdapter* native )
		: ComObject( native )
		{
		}
		
		AdapterDXGI::AdapterDXGI( IntPtr native )
		: ComObject( native )
		{
		}
	}
}