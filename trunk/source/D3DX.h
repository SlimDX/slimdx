#pragma once

using namespace System;

namespace SlimDX
{
	namespace Direct3D
	{
		public ref class D3DX sealed
		{
		public:
			literal int Default = D3DX_DEFAULT;
			literal int DefaultNonPowerOf2 = D3DX_DEFAULT_NONPOW2;
			literal int FromFile = D3DX_FROM_FILE;
			literal int FormatFromFile = D3DFMT_FROM_FILE;
		};
	}
}
