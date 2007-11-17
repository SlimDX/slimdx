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

#include "BlendStateDescription.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	BlendStateDescription::BlendStateDescription()
	{
		AlphaToCoverageEnabled = false;
		SourceBlend = BlendOption::One;
		DestinationBlend = BlendOption::Zero;
		BlendOperation = SlimDX::Direct3D10::BlendOperation::Add;
		SourceAlphaBlend = BlendOption::One;
		DestinationAlphaBlend = BlendOption::Zero;
		AlphaBlendOperation = SlimDX::Direct3D10::BlendOperation::Add;
		
		renderTargetBlendEnabled = gcnew List<bool>();
		renderTargetWriteMask = gcnew List<ColorWriteMaskFlags>();
		for(int i = 0; i < 8; ++i)
		{
			renderTargetBlendEnabled->Add( false );
			renderTargetWriteMask->Add( ColorWriteMaskFlags::All );
		}
	}

	BlendStateDescription::BlendStateDescription( const D3D10_BLEND_DESC& desc )
	{
		AlphaToCoverageEnabled = desc.AlphaToCoverageEnable ? true : false;
		SourceBlend = static_cast<BlendOption>( desc.SrcBlend );
		DestinationBlend = static_cast<BlendOption>( desc.DestBlend );
		BlendOperation = static_cast<SlimDX::Direct3D10::BlendOperation>( desc.BlendOp );
		SourceAlphaBlend = static_cast<BlendOption>( desc.SrcBlend );
		DestinationAlphaBlend = static_cast<BlendOption>( desc.DestBlend );
		AlphaBlendOperation = static_cast<SlimDX::Direct3D10::BlendOperation>( desc.BlendOp );
		
		renderTargetBlendEnabled = gcnew List<bool>();
		renderTargetWriteMask = gcnew List<ColorWriteMaskFlags>();
		for(int i = 0; i < 8; ++i)
		{
			renderTargetBlendEnabled->Add( false );
			renderTargetWriteMask->Add( ColorWriteMaskFlags::All );
		}
	}
	
	void BlendStateDescription::FillNativeObject( D3D10_BLEND_DESC& desc )
	{
		ZeroMemory( &desc, sizeof( desc ) );
		desc.SrcBlend = static_cast<D3D10_BLEND>( SourceBlend );
		desc.DestBlend = static_cast<D3D10_BLEND>( DestinationBlend );
		desc.BlendOp = static_cast<D3D10_BLEND_OP>( BlendOperation );
		desc.SrcBlendAlpha = static_cast<D3D10_BLEND>( SourceAlphaBlend );
		desc.DestBlendAlpha = static_cast<D3D10_BLEND>( DestinationAlphaBlend );
		desc.BlendOpAlpha = static_cast<D3D10_BLEND_OP>( AlphaBlendOperation );
		
		for(int i = 0; i < 8; ++i)
		{
			desc.BlendEnable[i] = RenderTargetBlendEnabled[i];
			desc.RenderTargetWriteMask[i] = static_cast<UINT8>( RenderTargetWriteMask[i] );
		}
	}
}
}
