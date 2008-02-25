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

#include "RasterizerStateDescription.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	RasterizerStateDescription::RasterizerStateDescription( const D3D10_RASTERIZER_DESC& native )
	{
		m_FillMode = static_cast<Direct3D10::FillMode>( native.FillMode );
		m_CullMode = static_cast<Direct3D10::CullMode>( native.CullMode );
		m_FrontCounterClockwise = native.FrontCounterClockwise ? true : false;
		m_DepthBias = native.DepthBias;
		m_DepthBiasClamp = native.DepthBiasClamp;
		m_SlopeScaledDepthBias = native.SlopeScaledDepthBias;
		m_DepthClipEnable = native.DepthClipEnable ? true : false;
		m_ScissorEnable = native.ScissorEnable ? true : false;
		m_MultisampleEnable = native.MultisampleEnable ? true : false;
		m_AntialiasedLineEnable = native.AntialiasedLineEnable ? true : false;
	}
	
	D3D10_RASTERIZER_DESC RasterizerStateDescription::CreateNativeVersion()
	{
		D3D10_RASTERIZER_DESC native;
		native.FillMode = static_cast<D3D10_FILL_MODE>( m_FillMode );
		native.CullMode = static_cast<D3D10_CULL_MODE>( m_CullMode );
		native.FrontCounterClockwise = m_FrontCounterClockwise;
		native.DepthBias = m_DepthBias;
		native.DepthBiasClamp = m_DepthBiasClamp;
		native.SlopeScaledDepthBias = m_SlopeScaledDepthBias;
		native.DepthClipEnable = m_DepthClipEnable;
		native.ScissorEnable = m_ScissorEnable;
		native.MultisampleEnable = m_MultisampleEnable;
		native.AntialiasedLineEnable = m_AntialiasedLineEnable;
		
		return native;
	}
	
	Direct3D10::FillMode RasterizerStateDescription::FillMode::get()
	{
		return m_FillMode;
	}
	
	void RasterizerStateDescription::FillMode::set( Direct3D10::FillMode value )
	{
		m_FillMode = value;	
	}
	
	Direct3D10::CullMode RasterizerStateDescription::CullMode::get()
	{
		return m_CullMode;
	}
	
	void RasterizerStateDescription::CullMode::set( Direct3D10::CullMode value )
	{
		m_CullMode = value;	
	}
	
	bool RasterizerStateDescription::IsFrontCounterclockwise::get()
	{
		return m_FrontCounterClockwise;
	}
	
	void RasterizerStateDescription::IsFrontCounterclockwise::set( bool value )
	{
		m_FrontCounterClockwise = value;	
	}
	
	int RasterizerStateDescription::DepthBias::get()
	{
		return m_DepthBias;
	}
	
	void RasterizerStateDescription::DepthBias::set( int value )
	{
		m_DepthBias = value;	
	}
	
	float RasterizerStateDescription::DepthBiasClamp::get()
	{
		return m_DepthBiasClamp;
	}
	
	void RasterizerStateDescription::DepthBiasClamp::set( float value )
	{
		m_DepthBiasClamp = value;	
	}
	
	float RasterizerStateDescription::SlopeScaledDepthBias::get()
	{
		return m_SlopeScaledDepthBias;
	}
	
	void RasterizerStateDescription::SlopeScaledDepthBias::set( float value )
	{
		m_SlopeScaledDepthBias = value;	
	}
	
	bool RasterizerStateDescription::IsDepthClipEnabled::get()
	{
		return m_DepthClipEnable;
	}
	
	void RasterizerStateDescription::IsDepthClipEnabled::set( bool value )
	{
		m_DepthClipEnable = value;	
	}
	
	bool RasterizerStateDescription::IsScissorEnabled::get()
	{
		return m_ScissorEnable;
	}
	
	void RasterizerStateDescription::IsScissorEnabled::set( bool value )
	{
		m_ScissorEnable = value;	
	}
	
	bool RasterizerStateDescription::IsMultisampleEnabled::get()
	{
		return m_MultisampleEnable;
	}
	
	void RasterizerStateDescription::IsMultisampleEnabled::set( bool value )
	{
		m_MultisampleEnable = value;	
	}
	
	bool RasterizerStateDescription::IsAntialiasedLineEnabled::get()
	{
		return m_AntialiasedLineEnable;
	}
	
	void RasterizerStateDescription::IsAntialiasedLineEnabled::set( bool value )
	{
		m_AntialiasedLineEnable = value;	
	}
}
}
