#include <windows.h>
#include <d3dx9.h>

#include "../Direct3D/MiscTypes.h"
#include "Math.h"

namespace SlimDX
{
	Vector3::Vector3( float x, float y, float z ) : X( x ), Y( y ), Z( z )
	{
	}

	float Vector3::Length()
	{
		return (float) Math::Sqrt( (X * X) + (Y * Y) + (Z * Z) );
	}

	void Vector3::Normalize()
	{
		float length = Length();
		X /= length;
		Y /= length;
		Z /= length;
	}

	Vector3 Vector3::Normalize( Vector3 vec )
	{
		vec.Normalize();
		return vec;
	}

	float Vector3::Dot( Vector3 lhs, Vector3 rhs )
	{
		return (lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z);
	}

	Vector3 Vector3::Cross( Vector3 lhs, Vector3 rhs )
	{
		Vector3 result;
		result.X = lhs.Y * rhs.Z - lhs.Z * rhs.Y;
		result.Y = lhs.Z * rhs.X - lhs.X * rhs.Z;
		result.Z = lhs.X * rhs.Y - lhs.Y * rhs.X;
		return result;
	}

	Vector3 Vector3::Lerp( Vector3 start, Vector3 end, float factor )
	{
		Vector3 result;
		D3DXVec3Lerp( (D3DXVECTOR3*) &result, (D3DXVECTOR3*) &start, (D3DXVECTOR3*) &end, factor );
		return result;
	}

	Vector3 Vector3::operator + ( Vector3 lhs, Vector3 rhs )
	{
		Vector3 result;
		D3DXVec3Add( (D3DXVECTOR3*) &result, (D3DXVECTOR3*) &lhs, (D3DXVECTOR3*) &rhs );
		return result;
	}

	Vector3 Vector3::operator - ( Vector3 lhs, Vector3 rhs )
	{
		Vector3 result;
		D3DXVec3Subtract( (D3DXVECTOR3*) &result, (D3DXVECTOR3*) &lhs, (D3DXVECTOR3*) &rhs );
		return result;
	}

	Vector3 Vector3::operator * ( Vector3 vec, float scale )
	{
		Vector3 result;
		D3DXVec3Scale( (D3DXVECTOR3*) &result, (D3DXVECTOR3*) &vec, scale );
		return result;
	}

	Vector3 Vector3::operator * ( float scale, Vector3 vec )
	{
		return vec * scale;
	}

	Vector3 Vector3::TransformCoordinate( Vector3 coord, Matrix transform )
	{
		Vector3 result;
		D3DXVec3TransformCoord( (D3DXVECTOR3*) &result, (const D3DXVECTOR3*) &coord, (const D3DXMATRIX*) &transform );
		return result;
	}

	Vector3 Vector3::TransformNormal( Vector3 normal, Matrix transform )
	{
		Vector3 result;
		D3DXVec3TransformNormal( (D3DXVECTOR3*) &result, (const D3DXVECTOR3*) &normal, (const D3DXMATRIX*) &transform );
		return result;
	}

    Vector3 Vector3::Project( Direct3D::Viewport viewport, Matrix projection, Matrix view, Matrix world )
    {
        Vector3 result;
        pin_ptr<Vector3> pinnedThis = this;

        D3DXVec3Project( (D3DXVECTOR3*) &result, (D3DXVECTOR3*) pinnedThis, (D3DVIEWPORT9*) &viewport,
            (D3DXMATRIX*) &projection, (D3DXMATRIX*) &view, (D3DXMATRIX*) &world );

        return result;
    }

    Vector3 Vector3::Unproject( Direct3D::Viewport viewport, Matrix projection, Matrix view, Matrix world )
    {
        Vector3 result;
        pin_ptr<Vector3> pinnedThis = this;

        D3DXVec3Unproject( (D3DXVECTOR3*) &result, (D3DXVECTOR3*) pinnedThis, (D3DVIEWPORT9*) &viewport,
            (D3DXMATRIX*) &projection, (D3DXMATRIX*) &view, (D3DXMATRIX*) &world );

        return result;
    }
}
