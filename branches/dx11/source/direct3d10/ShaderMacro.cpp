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

#include "ShaderMacro.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{ 
	String^ ShaderMacro::Name::get()
	{
		return m_Name;
	}
	
	String^ ShaderMacro::Value::get()
	{
		return m_Value;
	}

	bool ShaderMacro::operator == ( ShaderMacro left, ShaderMacro right )
	{
		return ShaderMacro::Equals( left, right );
	}

	bool ShaderMacro::operator != ( ShaderMacro left, ShaderMacro right )
	{
		return !ShaderMacro::Equals( left, right );
	}

	int ShaderMacro::GetHashCode()
	{
		return m_Name->GetHashCode() + m_Value->GetHashCode();
	}

	bool ShaderMacro::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( safe_cast<ShaderMacro>( value ) );
	}

	bool ShaderMacro::Equals( ShaderMacro value )
	{
		return ( m_Name == value.m_Name && m_Value == value.m_Value );
	}

	bool ShaderMacro::Equals( ShaderMacro% value1, ShaderMacro% value2 )
	{
		return ( value1.m_Name == value2.m_Name && value1.m_Value == value2.m_Value );
	}
}
}
