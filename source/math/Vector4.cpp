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
	Vector4::Vector4( float x, float y, float z, float w )
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}

	float Vector4::Length()
	{
		return (float) Math::Sqrt( (X * X) + (Y * Y) + (Z * Z) + (W * W) );
	}

	void Vector4::Normalize()
	{
		float length = Length();
		X /= length;
		Y /= length;
		Z /= length;
		W /= length;
	}

	Vector4 Vector4::operator * ( Vector4 vec, float scale )
	{
		Vector4 result;
		D3DXVec4Scale( (D3DXVECTOR4*) &result, (D3DXVECTOR4*) &vec, scale );
		return result;
	}

	Vector4 Vector4::operator * ( float scale, Vector4 vec )
	{
		return vec * scale;
	}
}
