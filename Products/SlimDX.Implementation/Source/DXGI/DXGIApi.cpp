#include "stdafx.h"

#include "DXGIApi.h"

namespace SlimDX
{
	namespace DXGI
	{
		DXGIApi::DXGIApi()
		{
		}
		
		IFactory^ DXGIApi::CreateFactory() {
			return nullptr;// gcnew FactoryDXGI( this, 0 );
		}
	}
}