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

#include "BlendStateDescription.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;

namespace SlimDX
{
namespace Direct3D10
{ 
	BlendStateDescription::BlendStateDescription( const D3D10_BLEND_DESC& native )
	{
		m_AlphaToCoverageEnable = native.AlphaToCoverageEnable ? true : false;
		m_SrcBlend = static_cast<BlendOption>( native.SrcBlend );
		m_DestBlend = static_cast<BlendOption>( native.DestBlend );
		m_BlendOp = static_cast<Direct3D10::BlendOperation>( native.BlendOp );
		m_SrcBlendAlpha = static_cast<BlendOption>( native.SrcBlendAlpha );
		m_DestBlendAlpha = static_cast<BlendOption>( native.DestBlendAlpha );
		m_BlendOpAlpha = static_cast<Direct3D10::BlendOperation>( native.BlendOpAlpha );
		
		m_BlendEnable = gcnew List<bool>(8);
		m_RenderTargetWriteMask = gcnew List<ColorWriteMaskFlags>(8);
		for(int index = 0; index < 8; ++index)
		{
			m_BlendEnable->Add( false );
			m_RenderTargetWriteMask->Add( ColorWriteMaskFlags::All );
		}
	}
	
	D3D10_BLEND_DESC BlendStateDescription::CreateNativeVersion()
	{
		D3D10_BLEND_DESC native;
		native.AlphaToCoverageEnable = m_AlphaToCoverageEnable;
		native.SrcBlend = static_cast<D3D10_BLEND>( m_SrcBlend );
		native.DestBlend = static_cast<D3D10_BLEND>( m_DestBlend );
		native.BlendOp = static_cast<D3D10_BLEND_OP>( m_BlendOp );
		native.SrcBlendAlpha = static_cast<D3D10_BLEND>( m_SrcBlendAlpha );
		native.DestBlendAlpha = static_cast<D3D10_BLEND>( m_DestBlendAlpha );
		native.BlendOpAlpha = static_cast<D3D10_BLEND_OP>( m_BlendOpAlpha );
		
		for(int index = 0; index < 8; ++index)
		{
			native.BlendEnable[ index ] = m_BlendEnable[ index ];
			native.RenderTargetWriteMask[ index ] = static_cast<UINT8>( m_RenderTargetWriteMask[ index ] );
		}
		
		return native;
	}
	
	bool BlendStateDescription::IsAlphaToCoverageEnabled::get()
	{
		return m_AlphaToCoverageEnable;
	}
	
	void BlendStateDescription::IsAlphaToCoverageEnabled::set( bool value )
	{
		m_AlphaToCoverageEnable = value;
	}

	ReadOnlyCollection<bool>^ BlendStateDescription::IsRenderTargetBlendEnabled::get()
	{
		return gcnew ReadOnlyCollection<bool>( m_BlendEnable );
	}

	BlendOption BlendStateDescription::SourceBlend::get()
	{
		return m_SrcBlend;
	}
	
	void BlendStateDescription::SourceBlend::set( BlendOption value )
	{
		m_SrcBlend = value;
	}
	
	BlendOption BlendStateDescription::DestinationBlend::get()
	{
		return m_DestBlend;
	}
	
	void BlendStateDescription::DestinationBlend::set( BlendOption value )
	{
		m_DestBlend = value;
	}

	Direct3D10::BlendOperation BlendStateDescription::BlendOperation::get()
	{
		return m_BlendOp;
	}

	void BlendStateDescription::BlendOperation::set( Direct3D10::BlendOperation value )
	{
		m_BlendOp = value;
	}
	
	BlendOption BlendStateDescription::SourceAlphaBlend::get()
	{
		return m_SrcBlendAlpha;
	}
	
	void BlendStateDescription::SourceAlphaBlend::set( BlendOption value )
	{
		m_SrcBlendAlpha = value;
	}

	BlendOption BlendStateDescription::DestinationAlphaBlend::get()
	{
		return m_DestBlendAlpha;
	}
	
	void BlendStateDescription::DestinationAlphaBlend::set( BlendOption value )
	{
		m_DestBlendAlpha = value;
	}
	
	Direct3D10::BlendOperation BlendStateDescription::AlphaBlendOperation::get()
	{
		return m_BlendOpAlpha;
	}
	
	void BlendStateDescription::AlphaBlendOperation::set( Direct3D10::BlendOperation value )
	{
		m_BlendOpAlpha = value;
	}

	ReadOnlyCollection<ColorWriteMaskFlags>^ BlendStateDescription::RenderTargetWriteMask::get()
	{
		return gcnew ReadOnlyCollection<ColorWriteMaskFlags>( m_RenderTargetWriteMask );
	}
}
}
