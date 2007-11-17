/*
* Copyright (c) 2007 SlimDX Group
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

#include <d3d10.h>
#include <d3dx10.h>

#include "GraphicsException.h"

#include "RasterizerStateDescription.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	RasterizerStateDescription::RasterizerStateDescription()
	{
		FillMode = SlimDX::Direct3D10::FillMode::Solid;
		CullMode = SlimDX::Direct3D10::CullMode::None;
		FrontIsCounterClockwise = true;
		DepthBias = 0;
		DepthBiasClamp = 0.0f;
		SlopeScaledDepthBias = 0.0f;
		DepthClipEnabled = false;
		ScissorEnabled = false;
		MultisampleEnabled = false;
		AntialiasedLineEnabled = false;
	}
	
	RasterizerStateDescription::RasterizerStateDescription( const D3D10_RASTERIZER_DESC& desc )
	{
		FillMode = static_cast<SlimDX::Direct3D10::FillMode>( desc.FillMode );
		CullMode = static_cast<SlimDX::Direct3D10::CullMode>( desc.CullMode );
		FrontIsCounterClockwise = desc.FrontCounterClockwise ? true : false;
		DepthBias = desc.DepthBias;
		DepthBiasClamp = desc.DepthBiasClamp;
		SlopeScaledDepthBias = desc.SlopeScaledDepthBias;
		DepthClipEnabled = desc.DepthClipEnable ? true : false;
		ScissorEnabled = desc.ScissorEnable ? true : false;
		MultisampleEnabled = desc.MultisampleEnable ? true : false;
		AntialiasedLineEnabled = desc.AntialiasedLineEnable ? true : false;
	}
	
	void RasterizerStateDescription::FillNativeObject( D3D10_RASTERIZER_DESC& desc )
	{
		ZeroMemory( &desc, sizeof( desc ) );
		desc.FillMode = static_cast<D3D10_FILL_MODE>( FillMode );
		desc.CullMode = static_cast<D3D10_CULL_MODE>( CullMode );
		desc.FrontCounterClockwise = FrontIsCounterClockwise;
		desc.DepthBias = DepthBias;
		desc.DepthBiasClamp = DepthBiasClamp;
		desc.SlopeScaledDepthBias = SlopeScaledDepthBias;
		desc.DepthClipEnable = DepthClipEnabled;
		desc.ScissorEnable = ScissorEnabled;
		desc.MultisampleEnable = MultisampleEnabled;
		desc.AntialiasedLineEnable = AntialiasedLineEnabled;
	}
}
}
