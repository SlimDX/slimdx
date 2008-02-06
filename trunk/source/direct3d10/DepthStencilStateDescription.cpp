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

//#include "Direct3D10ErrorHandler.h"

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
	
	DepthStencilStateDescription::DepthStencilStateDescription( const D3D10_DEPTH_STENCIL_DESC& description )
	{
		DepthEnabled = description.DepthEnable ? true : false;
		DepthWriteMask = static_cast<SlimDX::Direct3D10::DepthWriteMask>( description.DepthWriteMask );
		DepthComparison = static_cast<Comparison>( description.DepthFunc );
		StencilEnabled = description.StencilEnable ? true : false;
		StencilReadMask = description.StencilReadMask;
		StencilWriteMask = description.StencilWriteMask;
		FrontStencilComparison = static_cast<Comparison>( description.FrontFace.StencilFunc );
		FrontStencilFailureOperation = static_cast<StencilOperation>( description.FrontFace.StencilFailOp );
		FrontStencilDepthFailureOperation = static_cast<StencilOperation>( description.FrontFace.StencilDepthFailOp );
		FrontStencilPassOperation = static_cast<StencilOperation>( description.FrontFace.StencilPassOp );
		BackStencilComparison = static_cast<Comparison>( description.BackFace.StencilFunc );
		BackStencilFailureOperation = static_cast<StencilOperation>( description.BackFace.StencilFailOp );
		BackStencilDepthFailureOperation = static_cast<StencilOperation>( description.BackFace.StencilDepthFailOp );
		BackStencilPassOperation = static_cast<StencilOperation>( description.BackFace.StencilPassOp );
	}
	
	void DepthStencilStateDescription::FillNativeObject( D3D10_DEPTH_STENCIL_DESC& description )
	{
		ZeroMemory( &description, sizeof( description ) );
		
		description.DepthEnable = DepthEnabled;
		description.DepthWriteMask = static_cast<D3D10_DEPTH_WRITE_MASK>( DepthWriteMask );
		description.DepthFunc = static_cast<D3D10_COMPARISON_FUNC>( DepthComparison );
		description.StencilEnable = StencilEnabled;
		description.StencilReadMask = StencilReadMask;
		description.StencilWriteMask = StencilWriteMask;
		description.FrontFace.StencilFunc = static_cast<D3D10_COMPARISON_FUNC>( FrontStencilComparison );
		description.FrontFace.StencilFailOp = static_cast<D3D10_STENCIL_OP>( FrontStencilFailureOperation );
		description.FrontFace.StencilDepthFailOp = static_cast< D3D10_STENCIL_OP>( FrontStencilDepthFailureOperation );
		description.FrontFace.StencilPassOp = static_cast<D3D10_STENCIL_OP>( FrontStencilPassOperation );
		description.BackFace.StencilFunc = static_cast<D3D10_COMPARISON_FUNC>( BackStencilComparison );
		description.BackFace.StencilFailOp = static_cast<D3D10_STENCIL_OP>( BackStencilFailureOperation );
		description.BackFace.StencilDepthFailOp = static_cast<D3D10_STENCIL_OP>( BackStencilDepthFailureOperation );
		description.BackFace.StencilPassOp = static_cast<D3D10_STENCIL_OP>( BackStencilPassOperation );
	}
}
}
