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

#include <d3d11.h>

#include "BlendStateDescription.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;

namespace SlimDX
{
namespace Direct3D11
{ 
	BlendStateDescription::BlendStateDescription( const D3D11_BLEND_DESC& native )
	{
		m_AlphaToCoverageEnable = native.AlphaToCoverageEnable ? true : false;
		m_IndependentBlendEnable = native.IndependentBlendEnable ? true : false;

		ConstructLazyProperties();

		// TODO: Use #define
		// TODO: Revise class use
		for (int rendertargetIndex = 0; rendertargetIndex < 8; ++rendertargetIndex)
		{
			m_Rendertargets[rendertargetIndex] = BlendStateRendertargetDescription(native.RenderTarget[rendertargetIndex]);
		}
	}
	
	D3D11_BLEND_DESC BlendStateDescription::CreateNativeVersion()
	{
		D3D11_BLEND_DESC native;
		// TODO: Use #define
		// TODO: Revise class use
		native.AlphaToCoverageEnable = m_AlphaToCoverageEnable;
		native.IndependentBlendEnable = m_IndependentBlendEnable;
		for(int rendertargetIndex = 0; rendertargetIndex < 8; ++rendertargetIndex)
		{
			native.RenderTarget[rendertargetIndex] = m_Rendertargets[rendertargetIndex].CreateNativeVersion();
		}
		
		return native;
	}

	BlendStateRendertargetDescription::BlendStateRendertargetDescription( const D3D11_RENDER_TARGET_BLEND_DESC& native )
	{
		// TODO: Use #define
		// TODO: Revise class use

		m_BlendEnable = native.BlendEnable ? true : false;
		m_SrcBlend = static_cast<BlendOption>( native.SrcBlend );
		m_DestBlend = static_cast<BlendOption>( native.DestBlend );
		m_BlendOp = static_cast<Direct3D11::BlendOperation>( native.BlendOp );
		m_SrcBlendAlpha = static_cast<BlendOption>( native.SrcBlendAlpha );
		m_DestBlendAlpha = static_cast<BlendOption>( native.DestBlendAlpha );
		m_BlendOpAlpha = static_cast<Direct3D11::BlendOperation>( native.BlendOpAlpha );
		m_RenderTargetWriteMask = static_cast<Direct3D11::ColorWriteMaskFlags>( native.RenderTargetWriteMask );
	}
	
	D3D11_RENDER_TARGET_BLEND_DESC BlendStateRendertargetDescription::CreateNativeVersion()
	{
		D3D11_RENDER_TARGET_BLEND_DESC native;
		// TODO: Use #define
		// TODO: Revise class use

		native.SrcBlend = static_cast<D3D11_BLEND>( m_SrcBlend );
		native.DestBlend = static_cast<D3D11_BLEND>( m_DestBlend );
		native.BlendOp = static_cast<D3D11_BLEND_OP>( m_BlendOp );
		native.SrcBlendAlpha = static_cast<D3D11_BLEND>( m_SrcBlendAlpha );
		native.DestBlendAlpha = static_cast<D3D11_BLEND>( m_DestBlendAlpha );
		native.BlendOpAlpha = static_cast<D3D11_BLEND_OP>( m_BlendOpAlpha );

		native.BlendEnable = m_BlendEnable;
		native.RenderTargetWriteMask = static_cast<UINT8>( m_RenderTargetWriteMask );

		
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
	
	bool BlendStateDescription::IsIndependentBlendEnabled::get()
	{
		return m_IndependentBlendEnable;
	}
	
	void BlendStateDescription::IsIndependentBlendEnabled::set( bool value )
	{
		m_IndependentBlendEnable = value;
	}
	
	bool BlendStateRendertargetDescription::BlendEnable::get()
	{
		return m_BlendEnable;
	}
	
	void BlendStateRendertargetDescription::BlendEnable::set( bool value )
	{
		m_BlendEnable = value;
	}
	
	ColorWriteMaskFlags BlendStateRendertargetDescription::RenderTargetWriteMask::get()
	{
		return m_RenderTargetWriteMask;
	}
	
	void BlendStateRendertargetDescription::RenderTargetWriteMask::set( ColorWriteMaskFlags value )
	{
		m_RenderTargetWriteMask = value;
	}
	
	BlendOption BlendStateRendertargetDescription::SourceBlend::get()
	{
		return m_SrcBlend;
	}
	
	void BlendStateRendertargetDescription::SourceBlend::set( BlendOption value )
	{
		m_SrcBlend = value;
	}
	
	BlendOption BlendStateRendertargetDescription::DestinationBlend::get()
	{
		return m_DestBlend;
	}
	
	void BlendStateRendertargetDescription::DestinationBlend::set( BlendOption value )
	{
		m_DestBlend = value;
	}

	BlendOperation BlendStateRendertargetDescription::BlendOperation::get()
	{
		return m_BlendOp;
	}

	void BlendStateRendertargetDescription::BlendOperation::set( Direct3D11::BlendOperation value )
	{
		m_BlendOp = value;
	}
	
	Direct3D11::BlendOption BlendStateRendertargetDescription::SourceAlphaBlend::get()
	{
		return m_SrcBlendAlpha;
	}
	
	void BlendStateRendertargetDescription::SourceAlphaBlend::set( Direct3D11::BlendOption value )
	{
		m_SrcBlendAlpha = value;
	}

	Direct3D11::BlendOption BlendStateRendertargetDescription::DestinationAlphaBlend::get()
	{
		return m_DestBlendAlpha;
	}
	
	void BlendStateRendertargetDescription::DestinationAlphaBlend::set( BlendOption value )
	{
		m_DestBlendAlpha = value;
	}
	
	Direct3D11::BlendOperation BlendStateRendertargetDescription::AlphaBlendOperation::get()
	{
		return m_BlendOpAlpha;
	}
	
	void BlendStateRendertargetDescription::AlphaBlendOperation::set( Direct3D11::BlendOperation value )
	{
		m_BlendOpAlpha = value;
	}

	// TODO: Remove
	/*
	bool BlendStateDescription::GetBlendEnable( UInt32 index )
	{
		ConstructLazyProperties();
		return m_BlendEnable[ index ];
	}
	
	void BlendStateDescription::SetBlendEnable( UInt32 index, bool value )
	{
		ConstructLazyProperties();
		m_BlendEnable[ index ] = value;
	}
	
	ColorWriteMaskFlags BlendStateDescription::GetWriteMask( UInt32 index )
	{
		ConstructLazyProperties();
		return m_RenderTargetWriteMask[ index ];
	}
	
	void BlendStateDescription::SetWriteMask( UInt32 index, ColorWriteMaskFlags value )
	{
		ConstructLazyProperties();
		m_RenderTargetWriteMask[ index ] = value;
	}
	*/

	void BlendStateDescription::ConstructLazyProperties()
	{
		if (m_Rendertargets == nullptr)
		{
			m_Rendertargets = gcnew array<BlendStateRendertargetDescription>(8);
		}
	}

	bool BlendStateDescription::operator == ( BlendStateDescription left, BlendStateDescription right )
	{
		return BlendStateDescription::Equals( left, right );
	}

	bool BlendStateDescription::operator != ( BlendStateDescription left, BlendStateDescription right )
	{
		return !BlendStateDescription::Equals( left, right );
	}

	int BlendStateDescription::GetHashCode()
	{
		int tempHashCode = m_AlphaToCoverageEnable.GetHashCode() + m_IndependentBlendEnable.GetHashCode();
		for (int index = 0; index < 8; index++)
		{
			tempHashCode += m_Rendertargets[ index ].GetHashCode();
		}
		return tempHashCode;
	}

	bool BlendStateDescription::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( safe_cast<BlendStateDescription>( value ) );
	}

	bool BlendStateDescription::Equals( BlendStateDescription value )
	{
		for (int index = 0; index < 8; ++index)
		{
			if (!m_Rendertargets[ index ].Equals(value.m_Rendertargets[ index ]))
			{
				return false;
			}
		}
		return ( m_AlphaToCoverageEnable == value.m_AlphaToCoverageEnable && m_IndependentBlendEnable == value.m_IndependentBlendEnable );
	}

	bool BlendStateDescription::Equals( BlendStateDescription% value1, BlendStateDescription% value2 )
	{
		for (int index = 0; index < 8; ++index)
		{
			if (!value1.m_Rendertargets[ index ].Equals(value2.m_Rendertargets[ index ]))
			{
				return false;
			}
		}
		return ( value1.m_AlphaToCoverageEnable == value2.m_AlphaToCoverageEnable && value1.m_IndependentBlendEnable == value2.m_IndependentBlendEnable );
	}
}
}
