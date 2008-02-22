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
}