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

	float Plane::Dot( Vector3 point )
	{
		return A * point.X + B * point.Y + C * point.Z + D;
	}

	Plane Plane::Transform( SlimDX::Plane plane, SlimDX::Matrix transform )
	{
		Plane result;
		D3DXPlaneTransform( (D3DXPLANE*) &result, (const D3DXPLANE*) &plane, (const D3DXMATRIX*) &transform );
		return result;
	}
}
