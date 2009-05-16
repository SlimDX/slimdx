#include "stdafx.h"
/*
* Copyright (c) 2007-2009 SlimDX Group
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
#include "Enums.h"
#include "RenderTargetBlendDescription1.h"

namespace SlimDX
{
namespace Direct3D10_1
{
	RenderTargetBlendDescription1::RenderTargetBlendDescription1( const D3D10_RENDER_TARGET_BLEND_DESC1& native )
	{
		BlendEnable = native.BlendEnable != FALSE;
		SourceBlend = static_cast<SlimDX::Direct3D10::BlendOption>( native.SrcBlend );
		DestinationBlend = static_cast<SlimDX::Direct3D10::BlendOption>( native.DestBlend );
		BlendOperation = static_cast<SlimDX::Direct3D10::BlendOperation>( native.BlendOp );
		SourceBlendAlpha = static_cast<SlimDX::Direct3D10::BlendOption>( native.SrcBlendAlpha );
		DestinationBlendAlpha = static_cast<SlimDX::Direct3D10::BlendOption>( native.DestBlendAlpha );
		BlendOperationAlpha = static_cast<SlimDX::Direct3D10::BlendOperation>( native.BlendOpAlpha );
		RenderTargetWriteMask = native.RenderTargetWriteMask;
	}

	bool RenderTargetBlendDescription1::operator == ( RenderTargetBlendDescription1 left, RenderTargetBlendDescription1 right )
	{
		return RenderTargetBlendDescription1::Equals( left, right );
	}

	bool RenderTargetBlendDescription1::operator != ( RenderTargetBlendDescription1 left, RenderTargetBlendDescription1 right )
	{
		return !RenderTargetBlendDescription1::Equals( left, right );
	}

	int RenderTargetBlendDescription1::GetHashCode()
	{
		return RenderTargetWriteMask.GetHashCode() + BlendOperationAlpha.GetHashCode() + DestinationBlendAlpha.GetHashCode() + SourceBlendAlpha.GetHashCode() + BlendOperation.GetHashCode() + DestinationBlend.GetHashCode() + SourceBlend.GetHashCode() + BlendEnable.GetHashCode();
	}

	bool RenderTargetBlendDescription1::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( safe_cast<RenderTargetBlendDescription1>( value ) );
	}

	bool RenderTargetBlendDescription1::Equals( RenderTargetBlendDescription1 value )
	{
		return ( RenderTargetWriteMask == value.RenderTargetWriteMask && BlendOperationAlpha == value.BlendOperationAlpha && DestinationBlendAlpha == value.DestinationBlendAlpha && SourceBlendAlpha == value.SourceBlendAlpha && BlendOperation == value.BlendOperation && DestinationBlend == value.DestinationBlend && SourceBlend == value.SourceBlend && BlendEnable == value.BlendEnable );
	}

	bool RenderTargetBlendDescription1::Equals( RenderTargetBlendDescription1% value1, RenderTargetBlendDescription1% value2 )
	{
		return value1.Equals( value2 );
	}
}
}