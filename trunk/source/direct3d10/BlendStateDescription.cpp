/*
* Copyright (c) 2007-2008 SlimDX Group
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

#include "BlendStateDescription.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;

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

	BlendStateDescription::BlendStateDescription( const D3D10_BLEND_DESC& description )
	{
		AlphaToCoverageEnabled = description.AlphaToCoverageEnable ? true : false;
		SourceBlend = static_cast<BlendOption>( description.SrcBlend );
		DestinationBlend = static_cast<BlendOption>( description.DestBlend );
		BlendOperation = static_cast<SlimDX::Direct3D10::BlendOperation>( description.BlendOp );
		SourceAlphaBlend = static_cast<BlendOption>( description.SrcBlend );
		DestinationAlphaBlend = static_cast<BlendOption>( description.DestBlend );
		AlphaBlendOperation = static_cast<SlimDX::Direct3D10::BlendOperation>( description.BlendOp );
		
		renderTargetBlendEnabled = gcnew List<bool>();
		renderTargetWriteMask = gcnew List<ColorWriteMaskFlags>();
		for(int i = 0; i < 8; ++i)
		{
			renderTargetBlendEnabled->Add( false );
			renderTargetWriteMask->Add( ColorWriteMaskFlags::All );
		}
	}
	
	void BlendStateDescription::FillNativeObject( D3D10_BLEND_DESC& description )
	{
		ZeroMemory( &description, sizeof( description ) );
		description.SrcBlend = static_cast<D3D10_BLEND>( SourceBlend );
		description.DestBlend = static_cast<D3D10_BLEND>( DestinationBlend );
		description.BlendOp = static_cast<D3D10_BLEND_OP>( BlendOperation );
		description.SrcBlendAlpha = static_cast<D3D10_BLEND>( SourceAlphaBlend );
		description.DestBlendAlpha = static_cast<D3D10_BLEND>( DestinationAlphaBlend );
		description.BlendOpAlpha = static_cast<D3D10_BLEND_OP>( AlphaBlendOperation );
		
		for(int i = 0; i < 8; ++i)
		{
			description.BlendEnable[i] = RenderTargetBlendEnabled[i];
			description.RenderTargetWriteMask[i] = static_cast<UINT8>( RenderTargetWriteMask[i] );
		}
	}
}
}
