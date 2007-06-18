#include <windows.h>
#include <d3dx9.h>

#include "Math.h"

namespace SlimDX
{
	Quaternion::Quaternion(float x,float y,float z,float w)
		: X(x), Y(y), Z(z), W(w)
	{
	}

	Quaternion Quaternion::Identity::get()
	{
		Quaternion result;
		result.X = result.Y = result.Z = 0.0f;
		result.W = 1.0f;
		return result;
	}

	float Quaternion::Magnitude()
	{
		return (float) Math::Sqrt( (X * X) + (Y * Y) + (Z * Z) + (W * W) );
	}

	void Quaternion::Normalize()
	{
		float magnitude = Magnitude();
		X /= magnitude;
		Y /= magnitude;
		Z /= magnitude;
		W /= magnitude;
	}

	Quaternion Quaternion::Normalize( Quaternion quat )
	{
		quat.Normalize();
		return quat;
	}

	Quaternion Quaternion::RotationAxis( Vector3 axis, float angle )
	{
		Quaternion result;
		D3DXQuaternionRotationAxis( (D3DXQUATERNION*) &result, (D3DXVECTOR3*) &axis, angle );
		return result;
	}

	Quaternion Quaternion::RotationYawPitchRoll( float yaw, float pitch, float roll )
	{
		Quaternion result;
		D3DXQuaternionRotationYawPitchRoll( (D3DXQUATERNION*) &result, yaw, pitch, roll );
		return result;
	}

	Quaternion Quaternion::Slerp( Quaternion q1, Quaternion q2, float t )
	{
		Quaternion result;
		D3DXQuaternionSlerp( (D3DXQUATERNION*) &result, (D3DXQUATERNION*) &q1, (D3DXQUATERNION*) &q2, t );
		return result;
	}

	Quaternion Quaternion::operator * (Quaternion lhs, Quaternion rhs)
	{
		Quaternion result;
		D3DXQuaternionMultiply( (D3DXQUATERNION*) &result, (const D3DXQUATERNION*) &lhs, (const D3DXQUATERNION*) &rhs );
		return result;
	}
}
