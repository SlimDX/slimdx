/*
* Copyright (c) 2007 SlimDX Group
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
#include <windows.h>
#include <d3dx9.h>

#include "Math.h"
#include "../Direct3D/Viewport.h"

namespace SlimDX
{
	Float16::Float16( float value )
	{
		Float16 temp;
		D3DXFloat32To16Array( reinterpret_cast<D3DXFLOAT16*>( &temp ), &value, 1 );
		m_Value = temp.m_Value;
	}

	array<float>^ Float16::ConvertToFloat( array<Float16>^ values )
	{
		array<float>^ results = gcnew array<float>( values->Length );
		pin_ptr<float> pinnedResults = &results[0];
		pin_ptr<Float16> pinnedValues = &values[0];

		D3DXFloat16To32Array( reinterpret_cast<FLOAT*>( pinnedResults ), 
			reinterpret_cast<const D3DXFLOAT16*>( pinnedValues ), values->Length );

		return results;
	}

	array<Float16>^ Float16::ConvertToFloat16( array<float>^ values )
	{
		array<Float16>^ results = gcnew array<Float16>( values->Length );
		pin_ptr<Float16> pinnedResults = &results[0];
		pin_ptr<float> pinnedValues = &values[0];

		D3DXFloat32To16Array( reinterpret_cast<D3DXFLOAT16*>( pinnedResults ), 
			reinterpret_cast<const FLOAT*>( pinnedValues ), values->Length );

		return results;
	}

	Float16::operator Float16( float value )
	{
		return Float16( value );
	}

	Float16::operator float( Float16 value )
	{
		float result;
		D3DXFloat16To32Array( &result, reinterpret_cast<D3DXFLOAT16*>( &value ), 1 );
		return result;
	}

	bool Float16::operator == ( Float16 left, Float16 right )
	{
		return Float16::Equals( left, right );
	}

	bool Float16::operator != ( Float16 left, Float16 right )
	{
		return !Float16::Equals( left, right );
	}

	String^ Float16::ToString()
	{
		Float16 temp = Float16( m_Value );
		return ( static_cast<float>( temp ) ).ToString( CultureInfo::CurrentCulture );
	}

	int Float16::GetHashCode()
	{
		return (m_Value * 3 / 2) ^ m_Value;
	}

	bool Float16::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<Float16>( value ) );
	}

	bool Float16::Equals( Float16 value )
	{
		return ( value.m_Value == m_Value );
	}

	bool Float16::Equals( Float16% value1, Float16% value2 )
	{
		return ( value1.m_Value == value2.m_Value );
	}
}