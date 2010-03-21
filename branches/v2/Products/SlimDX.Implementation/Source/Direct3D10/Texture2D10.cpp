#include "stdafx.h"

#include "Texture2D10.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D10
	{
		Texture2D10::Texture2D10( ID3D10Texture2D* native )
		: ComObject( native )
		{
		}
		
		Texture2D10::Texture2D10( IntPtr native )
		: ComObject( native )
		{
		}
	}
}