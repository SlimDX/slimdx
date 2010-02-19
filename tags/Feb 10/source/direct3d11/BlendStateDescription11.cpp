#include "stdafx.h"
/*
* Copyright (c) 2007-2010 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#include <d3d11.h>

#include "Enums11.h"
#include "BlendStateDescription11.h"

namespace SlimDX
{
namespace Direct3D11
{
	BlendStateDescription::BlendStateDescription( const D3D11_BLEND_DESC& native )
	{
		AlphaToCoverageEnable = native.AlphaToCoverageEnable ? true : false;
		IndependentBlendEnable = native.IndependentBlendEnable ? true : false;
		
		ConstructLazyProperties();
		for(int index = 0; index < 8; ++index)
		{
			m_RenderTargets[index] = RenderTargetBlendDescription(native.RenderTarget[index]);
		}
	}
	
	D3D11_BLEND_DESC BlendStateDescription::CreateNativeVersion()
	{
		D3D11_BLEND_DESC native;
		native.AlphaToCoverageEnable = AlphaToCoverageEnable;
		native.IndependentBlendEnable = IndependentBlendEnable;
		
		ConstructLazyProperties();
		for(int index = 0; index < 8; ++index)
		{
			native.RenderTarget[index] = m_RenderTargets[index].CreateNativeVersion();
		}
		
		return native;
	}
	
	void BlendStateDescription::ConstructLazyProperties()
	{
		if(m_RenderTargets == nullptr)
		{
			m_RenderTargets = gcnew array<RenderTargetBlendDescription>(8);
		}
	}

	array<RenderTargetBlendDescription>^ BlendStateDescription::RenderTargets::get()
	{
		ConstructLazyProperties();
		return m_RenderTargets;
	}
}
}
