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

#include "Color3.h"

using namespace System;

namespace SlimDX
{
	Color3::Color3( float red, float green, float blue )
	: m_Red( red ), m_Green( green ), m_Blue( blue )
	{
	}
	
	float Color3::Red::get()
	{
		return m_Red;
	}
	
	void Color3::Red::set( float value )
	{
		m_Red = value;
	}
	
	float Color3::Green::get()
	{
		return m_Green;
	}
	
	void Color3::Green::set( float value )
	{
		m_Green = value;
	}
	
	float Color3::Blue::get()
	{
		return m_Blue;
	}
	
	void Color3::Blue::set( float value )
	{
		m_Blue = value;
	}

		bool Color3::operator == ( Color3 left, Color3 right )
	{
		return Color3::Equals( left, right );
	}

	bool Color3::operator != ( Color3 left, Color3 right )
	{
		return !Color3::Equals( left, right );
	}

	int Color3::GetHashCode()
	{
		return m_Red.GetHashCode() + m_Green.GetHashCode() + m_Blue.GetHashCode();
	}

	bool Color3::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<Color3>( value ) );
	}

	bool Color3::Equals( Color3 value )
	{
		return ( m_Red == value.m_Red && m_Green == value.m_Green && m_Blue == value.m_Blue );
	}

	bool Color3::Equals( Color3% value1, Color3% value2 )
	{
		return ( value1.m_Red == value2.m_Red && value1.m_Green == value2.m_Green && value1.m_Blue == value2.m_Blue );
	}
}