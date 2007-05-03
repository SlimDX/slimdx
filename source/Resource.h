#pragma once

using namespace System;

namespace SlimDX
{
	namespace Direct3D
	{
		public ref class Resource abstract
		{
		internal:
			virtual property IDirect3DResource9* ResourcePointer
			{
				IDirect3DResource9* get() abstract;
			}

		public:
			virtual ~Resource() { };
		};
	}
}
