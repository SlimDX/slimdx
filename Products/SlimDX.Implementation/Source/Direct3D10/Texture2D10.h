#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Texture2D : ITexture2D, ComObject<ID3D10Texture2D>
		{
			public:
				Texture2D( ID3D10Texture2D* native );
				Texture2D( System::IntPtr native );
		};
	}
}