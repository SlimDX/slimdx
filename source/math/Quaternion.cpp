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

	Quaternion Quaternion::RotationYawPitchRoll( float yaw, float pitch, float roll )
	{
		Quaternion result;
		D3DXQuaternionRotationYawPitchRoll( (D3DXQUATERNION*) &result, yaw, pitch, roll );
		return result;
	}

	Quaternion Quaternion::operator * (Quaternion lhs, Quaternion rhs)
	{
		Quaternion result;
		D3DXQuaternionMultiply( (D3DXQUATERNION*) &result, (const D3DXQUATERNION*) &lhs, (const D3DXQUATERNION*) &rhs );
		return result;
	}
}
