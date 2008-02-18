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

#include "BufferDescription.h"

namespace SlimDX
{
namespace Direct3D10
{ 	
	BufferDescription::BufferDescription( int sizeInBytes, ResourceUsage usage, Direct3D10::BindFlags bindFlags, Direct3D10::CpuAccessFlags accessFlags, ResourceOptionFlags optionFlags )
	: m_ByteWidth( sizeInBytes), m_Usage( usage ), m_BindFlags( bindFlags ), m_CPUAccessFlags( accessFlags ), m_MiscFlags( optionFlags )
	{
	}
	
	BufferDescription::BufferDescription( const D3D10_BUFFER_DESC& native )
	{
		m_ByteWidth = native.ByteWidth;
		m_Usage = static_cast<ResourceUsage>( native.Usage );
		m_BindFlags = static_cast<Direct3D10::BindFlags>( native.BindFlags );
		m_CPUAccessFlags = static_cast<Direct3D10::CpuAccessFlags>( native.CPUAccessFlags );
		m_MiscFlags = static_cast<ResourceOptionFlags>( native.MiscFlags );
	}
	
	D3D10_BUFFER_DESC BufferDescription::CreateNativeVersion()
	{
		D3D10_BUFFER_DESC native;
		native.ByteWidth = m_ByteWidth;
		native.Usage = static_cast<D3D10_USAGE>( m_Usage );
		native.BindFlags = static_cast<UINT>( m_CPUAccessFlags );
		native.CPUAccessFlags = static_cast<UINT>( m_CPUAccessFlags );
		native.MiscFlags = static_cast<UINT>( m_MiscFlags );
		
		return native;
	}

	int BufferDescription::SizeInBytes::get()
	{
		return m_ByteWidth;
	}

	void BufferDescription::SizeInBytes::set( int value )
	{
		m_ByteWidth = value;
	}
	
	ResourceUsage BufferDescription::Usage::get()
	{
		return m_Usage;
	}

	void BufferDescription::Usage::set( ResourceUsage value )
	{
		m_Usage = value;
	}
	
	Direct3D10::BindFlags BufferDescription::BindFlags::get()
	{
		return m_BindFlags;
	}

	void BufferDescription::BindFlags::set( Direct3D10::BindFlags value )
	{
		m_BindFlags = value;
	}
	
	Direct3D10::CpuAccessFlags BufferDescription::CpuAccessFlags::get()
	{
		return m_CPUAccessFlags;
	}

	void BufferDescription::CpuAccessFlags::set( Direct3D10::CpuAccessFlags value )
	{
		m_CPUAccessFlags = value;
	}
	
	ResourceOptionFlags BufferDescription::OptionFlags::get()
	{
		return m_MiscFlags;
	}

	void BufferDescription::OptionFlags::set( ResourceOptionFlags value )
	{
		m_MiscFlags = value;
	}
}
}
