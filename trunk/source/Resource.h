#pragma once

using namespace System;

#include "DirectXObject.h"

namespace SlimDX
{
	namespace Direct3D
	{
		public ref class Resource abstract : public DirectXObject
		{
		internal:
			virtual property IDirect3DResource9* ResourcePointer
			{
				IDirect3DResource9* get() abstract;
			}
		};
	}
}
