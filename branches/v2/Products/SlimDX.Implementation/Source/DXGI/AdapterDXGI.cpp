#include "stdafx.h"

#include "AdapterDXGI.h"

using namespace System;

namespace SlimDX
{
	namespace DXGI
	{
		Adapter::Adapter( IDXGIAdapter* native )
		: ComObject( native )
		{
		}
		
		Adapter::Adapter( IntPtr native )
		: ComObject( native )
		{
		}
	}
}