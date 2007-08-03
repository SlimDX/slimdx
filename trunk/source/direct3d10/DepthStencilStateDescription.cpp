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

#include "DepthStencilStateDescription.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	DepthStencilStateDescription::DepthStencilStateDescription()
	{
		DepthEnabled = true;
		DepthWriteMask = SlimDX::Direct3D10::DepthWriteMask::All;
		DepthComparison = Comparison::Less;
		StencilEnabled = false;
		StencilReadMask = D3D10_DEFAULT_STENCIL_READ_MASK;
		StencilWriteMask = D3D10_DEFAULT_STENCIL_WRITE_MASK;
		FrontStencilComparison = Comparison::Always;
		FrontStencilFailureOperation = StencilOperation::Keep;
		FrontStencilDepthFailureOperation = StencilOperation::Keep;
		FrontStencilPassOperation = StencilOperation::Keep;
		BackStencilComparison = Comparison::Always;
		BackStencilFailureOperation = StencilOperation::Keep;
		BackStencilDepthFailureOperation = StencilOperation::Keep;
		BackStencilPassOperation = StencilOperation::Keep;
	}
	
	DepthStencilStateDescription::DepthStencilStateDescription( const D3D10_DEPTH_STENCIL_DESC& desc )
	{
		DepthEnabled = desc.DepthEnable ? true : false;
		DepthWriteMask = (SlimDX::Direct3D10::DepthWriteMask) desc.DepthWriteMask;
		DepthComparison = (Comparison) desc.DepthFunc;
		StencilEnabled = desc.StencilEnable ?(true): false;
		StencilReadMask = desc.StencilReadMask;
		StencilWriteMask = desc.StencilWriteMask;
		FrontStencilComparison = (Comparison) desc.FrontFace.StencilFunc;
		FrontStencilFailureOperation = (StencilOperation) desc.FrontFace.StencilFailOp;
		FrontStencilDepthFailureOperation = (StencilOperation) desc.FrontFace.StencilDepthFailOp;
		FrontStencilPassOperation = (StencilOperation) desc.FrontFace.StencilPassOp;
		BackStencilComparison = (Comparison) desc.BackFace.StencilFunc;
		BackStencilFailureOperation = (StencilOperation) desc.BackFace.StencilFailOp;
		BackStencilDepthFailureOperation = (StencilOperation) desc.BackFace.StencilDepthFailOp;
		BackStencilPassOperation = (StencilOperation) desc.BackFace.StencilPassOp;
	}
	
	void DepthStencilStateDescription::FillNativeObject( D3D10_DEPTH_STENCIL_DESC& desc )
	{
		ZeroMemory( &desc, sizeof( desc ) );
		
		desc.DepthEnable = DepthEnabled;
		desc.DepthWriteMask = (D3D10_DEPTH_WRITE_MASK) DepthWriteMask;
		desc.DepthFunc = (D3D10_COMPARISON_FUNC) DepthComparison;
		desc.StencilEnable = StencilEnabled;
		desc.StencilReadMask = StencilReadMask;
		desc.StencilWriteMask = StencilWriteMask;
		desc.FrontFace.StencilFunc = (D3D10_COMPARISON_FUNC) FrontStencilComparison;
		desc.FrontFace.StencilFailOp = (D3D10_STENCIL_OP) FrontStencilFailureOperation;
		desc.FrontFace.StencilDepthFailOp = ( D3D10_STENCIL_OP) FrontStencilDepthFailureOperation;
		desc.FrontFace.StencilPassOp = (D3D10_STENCIL_OP) FrontStencilPassOperation;
		desc.BackFace.StencilFunc = (D3D10_COMPARISON_FUNC) BackStencilComparison;
		desc.BackFace.StencilFailOp = (D3D10_STENCIL_OP) BackStencilFailureOperation;
		desc.BackFace.StencilDepthFailOp = (D3D10_STENCIL_OP) BackStencilDepthFailureOperation;
		desc.BackFace.StencilPassOp = (D3D10_STENCIL_OP) BackStencilPassOperation;
	}
}
}
