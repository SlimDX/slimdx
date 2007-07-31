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

	Vector2 Vector2::operator + ( Vector2 lhs, Vector2 rhs )
	{
		Vector2 result;
		D3DXVec2Add( (D3DXVECTOR2*) &result, (D3DXVECTOR2*) &lhs, (D3DXVECTOR2*) &rhs );
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
