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

#include "Texture2DDescription.h"

namespace SlimDX
{
namespace Direct3D10
{ 	
	Texture2DDescription::Texture2DDescription( const D3D10_TEXTURE2D_DESC& native )
	{
		m_Width = native.Width;
		m_Height = native.Height;
		m_MipLevels = native.MipLevels;
		m_ArraySize = native.ArraySize;
		m_Format = static_cast<DXGI::Format>( native.Format );
		m_Usage = static_cast<ResourceUsage>( native.Usage );
		m_BindFlags = static_cast<Direct3D10::BindFlags>( native.BindFlags );
		m_CPUAccessFlags = static_cast<Direct3D10::CpuAccessFlags>( native.CPUAccessFlags );
		m_MiscFlags = static_cast<ResourceOptionFlags>( native.MiscFlags );
	}

	D3D10_TEXTURE2D_DESC Texture2DDescription::CreateNativeVersion()
	{
		D3D10_TEXTURE2D_DESC native;
		native.Width = m_Width;
		native.Height = m_Height;
		native.MipLevels = m_MipLevels;
		native.ArraySize = m_ArraySize;
		native.Format = static_cast<DXGI_FORMAT>( m_Format );
		native.Usage = static_cast<D3D10_USAGE>( m_Usage );
		native.BindFlags = static_cast<UINT>( m_BindFlags );
		native.CPUAccessFlags = static_cast<UINT>( m_CPUAccessFlags );
		native.MiscFlags = static_cast<UINT>( m_MiscFlags );
		
		return native;
	}
	
	int Texture2DDescription::Width::get()
	{
		return m_Width;
	}

	void Texture2DDescription::Width::set( int value )
	{
		m_Width = value;
	}
	
	int Texture2DDescription::Height::get()
	{
		return m_Height;
	}

	void Texture2DDescription::Height::set( int value )
	{
		m_Height = value;
	}
	
	int Texture2DDescription::MipLevels::get()
	{
		return m_MipLevels;
	}

	void Texture2DDescription::MipLevels::set( int value )
	{
		m_MipLevels = value;
	}
	
	int Texture2DDescription::ArraySize::get()
	{
		return m_ArraySize;
	}

	void Texture2DDescription::ArraySize::set( int value )
	{
		m_ArraySize = value;
	}
	
	DXGI::Format Texture2DDescription::Format::get()
	{
		return m_Format;
	}

	void Texture2DDescription::Format::set( DXGI::Format value )
	{
		m_Format = value;
	}
	
	ResourceUsage Texture2DDescription::Usage::get()
	{
		return m_Usage;
	}

	void Texture2DDescription::Usage::set( ResourceUsage value )
	{
		m_Usage = value;
	}
	
	Direct3D10::BindFlags Texture2DDescription::BindFlags::get()
	{
		return m_BindFlags;
	}

	void Texture2DDescription::BindFlags::set( Direct3D10::BindFlags value )
	{
		m_BindFlags = value;
	}
	
	Direct3D10::CpuAccessFlags Texture2DDescription::CpuAccessFlags::get()
	{
		return m_CPUAccessFlags;
	}

	void Texture2DDescription::CpuAccessFlags::set( Direct3D10::CpuAccessFlags value )
	{
		m_CPUAccessFlags = value;
	}
	
	ResourceOptionFlags Texture2DDescription::OptionFlags::get()
	{
		return m_MiscFlags;
	}

	void Texture2DDescription::OptionFlags::set( ResourceOptionFlags value )
	{
		m_MiscFlags = value;
	}
}
}
