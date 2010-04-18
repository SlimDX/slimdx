#include "stdafx.h"

#include "Texture2D10.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D10
	{
		Texture2D::Texture2D( ID3D10Texture2D* native )
		: ComObject( native )
		{
		}
		
		Texture2D::Texture2D( IntPtr native )
		: ComObject( native )
		{
		}
	}
}