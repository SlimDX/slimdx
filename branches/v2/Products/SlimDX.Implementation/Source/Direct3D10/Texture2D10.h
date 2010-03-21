#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Texture2D10 : ITexture2D10, ComObject<ID3D10Texture2D>
		{
			public:
				Texture2D10( ID3D10Texture2D* native );
				Texture2D10( System::IntPtr native );
		};
	}
}