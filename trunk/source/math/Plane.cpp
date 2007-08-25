#include <windows.h>
#include <d3dx9.h>

#include "Math.h"

namespace SlimDX
{
	void Plane::Normalize()
	{
		float magnitude = (A * A) + (B * B) + (C * C);
		magnitude = (float) Math::Sqrt( magnitude );

		A /= magnitude;
		B /= magnitude;
		C /= magnitude;
	}

	Plane Plane::FromPointNormal( Vector3 point, Vector3 normal )
	{
		Plane plane;
		D3DXPlaneFromPointNormal( (D3DXPLANE*) &plane, (D3DXVECTOR3*) &point, (D3DXVECTOR3*) &normal );
		return plane;
	}

	Plane Plane::FromPoints( Vector3 p1, Vector3 p2, Vector3 p3 )
	{
		Plane plane;
		D3DXPlaneFromPoints( (D3DXPLANE*) &plane, (D3DXVECTOR3*) &p1, (D3DXVECTOR3*) &p2, (D3DXVECTOR3*) &p3 );
		return plane;
	}

	float Plane::Dot( Vector3 point )
	{
		return A * point.X + B * point.Y + C * point.Z + D;
	}

	float Plane::Dot( Vector4 point )
	{
		return A * point.X + B * point.Y + C * point.Z + point.Z * D;
	}

	Plane Plane::Transform( SlimDX::Plane plane, SlimDX::Matrix transform )
	{
		Plane result;
		D3DXPlaneTransform( (D3DXPLANE*) &result, (const D3DXPLANE*) &plane, (const D3DXMATRIX*) &transform );
		return result;
	}

	bool Plane::IntersectLine( Plane plane, Vector3 start, Vector3 end, [Out] Vector3% intersectPoint )
	{
		D3DXVECTOR3 nativePoint;
		D3DXVECTOR3* result = D3DXPlaneIntersectLine( &nativePoint, (D3DXPLANE*) &plane, (D3DXVECTOR3*) &start, (D3DXVECTOR3*) &end );
		if( result == NULL )
		{
			intersectPoint = Vector3( 0, 0, 0 );
			return false;
		}

		intersectPoint = Vector3( nativePoint.x, nativePoint.y, nativePoint.z );
		return true;
	}

	Plane Plane::operator * ( Plane plane, float scale )
	{
		Plane result;
		D3DXPlaneScale( (D3DXPLANE*) &result, (D3DXPLANE*) &plane, scale );
		return result;
	}
}
