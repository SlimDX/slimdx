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

namespace SlimDX
{
	Vector2::Vector2( float x, float y )
	{
		X = x;
		Y = y;
	}

	float Vector2::Length()
	{
		return (float) Math::Sqrt( X * X + Y * Y );
	}

	void Vector2::Normalize()
	{
		float length = Length();
		if( length == 0 )
			return;

		X /= length;
		Y /= length;
	}

	Vector2 Vector2::Normalize( Vector2 vec )
	{
		vec.Normalize();
		return vec;
	}

	Vector2 Vector2::operator + ( Vector2 lhs, Vector2 rhs )
	{
		Vector2 result;
		D3DXVec2Add( (D3DXVECTOR2*) &result, (D3DXVECTOR2*) &lhs, (D3DXVECTOR2*) &rhs );
		return result;
	}
	
	Vector2 Vector2::Minimize( Vector2 left, Vector2 right )
	{
		Vector2 result;
		D3DXVec2Minimize( (D3DXVECTOR2*) &result, (D3DXVECTOR2*) &left, (D3DXVECTOR2*) &right );
		return result;
	}
	
	Vector2 Vector2::Maximize( Vector2 left, Vector2 right )
	{
		Vector2 result;
		D3DXVec2Maximize( (D3DXVECTOR2*) &result, (D3DXVECTOR2*) &left, (D3DXVECTOR2*) &right );
		return result;
	}

	Vector2 Vector2::operator - ( Vector2 lhs, Vector2 rhs )
	{
		Vector2 result;
		D3DXVec2Subtract( (D3DXVECTOR2*) &result, (D3DXVECTOR2*) &lhs, (D3DXVECTOR2*) &rhs );
		return result;
	}

	Vector2 Vector2::operator * ( Vector2 vec, float scale )
	{
		Vector2 result;
		D3DXVec2Scale( (D3DXVECTOR2*) &result, (D3DXVECTOR2*) &vec, scale );
		return result;
	}

	Vector2 Vector2::operator * ( float scale, Vector2 vec )
	{
		return vec * scale;
	}
}
