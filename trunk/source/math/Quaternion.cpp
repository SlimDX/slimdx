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
	Quaternion::Quaternion(float x, float y, float z, float w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}

	Quaternion Quaternion::Identity::get()
	{
		Quaternion result;
		result.X = 0.0f;
		result.Y = 0.0f;
		result.Z = 0.0f;
		result.W = 1.0f;
		return result;
	}

	float Quaternion::Magnitude()
	{
		return (float) Math::Sqrt( (X * X) + (Y * Y) + (Z * Z) + (W * W) );
	}
	
	float Quaternion::MagnitudeSquared()
	{
		return (X * X) + (Y * Y) + (Z * Z) + (W * W);
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

	Quaternion Quaternion::Conjugate( Quaternion quat )
	{
		Quaternion result;
		D3DXQuaternionConjugate( (D3DXQUATERNION*) &result, (D3DXQUATERNION*) &quat );
		return result;
	}

	Quaternion Quaternion::Exponential( Quaternion quat )
	{
		Quaternion result;
		D3DXQuaternionExp( (D3DXQUATERNION*) &result, (D3DXQUATERNION*) &quat );
		return result;
	}

	Quaternion Quaternion::Logarithm( Quaternion quat )
	{
		Quaternion result;
		D3DXQuaternionLn( (D3DXQUATERNION*) &result, (D3DXQUATERNION*) &quat );
		return result;
	}

	Quaternion Quaternion::RotationAxis( Vector3 axis, float angle )
	{
		Quaternion result;
		D3DXQuaternionRotationAxis( (D3DXQUATERNION*) &result, (D3DXVECTOR3*) &axis, angle );
		return result;
	}
	
	Quaternion Quaternion::RotationMatrix( Matrix matrix )
	{
		Quaternion result;
		D3DXQuaternionRotationMatrix( (D3DXQUATERNION*) &result, (D3DXMATRIX*) &matrix );
		return result;
	}

	Quaternion Quaternion::RotationYawPitchRoll( float yaw, float pitch, float roll )
	{
		Quaternion result;
		D3DXQuaternionRotationYawPitchRoll( (D3DXQUATERNION*) &result, yaw, pitch, roll );
		return result;
	}

	Quaternion Quaternion::BaryCentric( Quaternion q1, Quaternion q2, Quaternion q3, float f, float g )
	{
		Quaternion result;
		D3DXQuaternionBaryCentric( (D3DXQUATERNION*) &result, (D3DXQUATERNION*) &q1,\
			(D3DXQUATERNION*) &q2, (D3DXQUATERNION*) &q3, f, g );
		return result;
	}

	Quaternion Quaternion::Invert( Quaternion quat )
	{
		Quaternion result;
		D3DXQuaternionInverse( (D3DXQUATERNION*) &result, (D3DXQUATERNION*) &quat );
		return result;
	}

	Quaternion Quaternion::Slerp( Quaternion q1, Quaternion q2, float t )
	{
		Quaternion result;
		D3DXQuaternionSlerp( (D3DXQUATERNION*) &result, (D3DXQUATERNION*) &q1, (D3DXQUATERNION*) &q2, t );
		return result;
	}

	Quaternion Quaternion::Squad( Quaternion q1, Quaternion a, Quaternion b, Quaternion c, float t )
	{
		Quaternion result;
		D3DXQuaternionSquad( (D3DXQUATERNION*) &result, (D3DXQUATERNION*) &q1, (D3DXQUATERNION*) &a,
			(D3DXQUATERNION*) &b, (D3DXQUATERNION*) &c, t );
		return result;
	}

	float Quaternion::Dot(Quaternion lhs, Quaternion rhs)
	{
		return D3DXQuaternionDot( (const D3DXQUATERNION*) &lhs, (const D3DXQUATERNION*) &rhs );
	}

	Quaternion Quaternion::operator * (Quaternion lhs, Quaternion rhs)
	{
		Quaternion result;
		D3DXQuaternionMultiply( (D3DXQUATERNION*) &result, (const D3DXQUATERNION*) &lhs, (const D3DXQUATERNION*) &rhs );
		return result;
	}

	Quaternion Quaternion::operator * (Quaternion lhs, float rhs)
	{
		Quaternion result;
		result.X = lhs.X * rhs;
		result.Y = lhs.Y * rhs;
		result.Z = lhs.Z * rhs;
		result.W = lhs.W * rhs;
		return result;
	}

	Quaternion Quaternion::operator / (Quaternion lhs, float rhs)
	{
		Quaternion result;
		result.X = lhs.X / rhs;
		result.Y = lhs.Y / rhs;
		result.Z = lhs.Z / rhs;
		result.W = lhs.W / rhs;
		return result;
	}

	Quaternion Quaternion::operator + (Quaternion lhs, Quaternion rhs)
	{
		Quaternion result;
		result.X = lhs.X + rhs.X;
		result.Y = lhs.Y + rhs.Y;
		result.Z = lhs.Z + rhs.Z;
		result.W = lhs.W + rhs.W;
		return result;
	}

	Quaternion Quaternion::operator - (Quaternion lhs, Quaternion rhs)
	{
		Quaternion result;
		result.X = lhs.X * rhs.X;
		result.Y = lhs.Y * rhs.Y;
		result.Z = lhs.Z * rhs.Z;
		result.W = lhs.W * rhs.W;
		return result;
	}
}
