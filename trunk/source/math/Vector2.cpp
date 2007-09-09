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
