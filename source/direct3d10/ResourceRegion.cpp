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

#include "ResourceRegion.h"

namespace SlimDX
{
namespace Direct3D10
{ 	
	ResourceRegion::ResourceRegion( const D3D10_BOX& native )
	{
		m_Left = native.left;
		m_Top = native.top;
		m_Front = native.front;
		m_Right = native.right;
		m_Bottom = native.bottom;
		m_Back = native.back;
	}
	
	D3D10_BOX ResourceRegion::CreateNativeVersion()
	{
		D3D10_BOX native;
		native.left = m_Left;
		native.top = m_Top;
		native.front = m_Front;
		native.right = m_Right;
		native.bottom = m_Bottom;
		native.back = m_Back;
		
		return native;
	}
	
	int ResourceRegion::Left::get()
	{
		return m_Left;
	}
	
	void ResourceRegion::Left::set( int value )
	{
		m_Left = value;
	}
	
	int ResourceRegion::Top::get()
	{
		return m_Top;
	}
	
	void ResourceRegion::Top::set( int value )
	{
		m_Top = value;
	}
	
	int ResourceRegion::Front::get()
	{
		return m_Front;
	}
	
	void ResourceRegion::Front::set( int value )
	{
		m_Front = value;
	}
	
	int ResourceRegion::Right::get()
	{
		return m_Right;
	}
	
	void ResourceRegion::Right::set( int value )
	{
		m_Right = value;
	}
	
	int ResourceRegion::Bottom::get()
	{
		return m_Bottom;
	}
	
	void ResourceRegion::Bottom::set( int value )
	{
		m_Bottom = value;
	}
	
	int ResourceRegion::Back::get()
	{
		return m_Back;
	}
	
	void ResourceRegion::Back::set( int value )
	{
		m_Back = value;
	}
}
}
