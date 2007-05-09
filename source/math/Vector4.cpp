#include <windows.h>
#include <d3dx9.h>

#include "Math.h"

namespace SlimDX
{
	Vector4::Vector4( float x, float y, float z, float w ) : X( x ), Y( y ), Z( z ), W( w )
	{
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
