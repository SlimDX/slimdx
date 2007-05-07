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
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

#include <d3dx9.h>

namespace SlimDX
{
	value class Matrix;

	[StructLayout( LayoutKind::Sequential )]
	public value class Vector2
	{
	public:
		float X, Y;

		Vector2( float x, float y ) : X( x ), Y( y )
		{ }

		static Vector2 operator + ( Vector2 lhs, Vector2 rhs )
		{
			Vector2 result;
			D3DXVec2Add( (D3DXVECTOR2*) &result, (D3DXVECTOR2*) &lhs, (D3DXVECTOR2*) &rhs );
			return result;
		}

		static Vector2 operator - ( Vector2 lhs, Vector2 rhs )
		{
			Vector2 result;
			D3DXVec2Subtract( (D3DXVECTOR2*) &result, (D3DXVECTOR2*) &lhs, (D3DXVECTOR2*) &rhs );
			return result;
		}

		static Vector2 operator * ( Vector2 vec, float scale )
		{
			Vector2 result;
			D3DXVec2Scale( (D3DXVECTOR2*) &result, (D3DXVECTOR2*) &vec, scale );
			return result;
		}

		static Vector2 operator * ( float scale, Vector2 vec )
		{
			return vec * scale;
		}
	};

	[StructLayout( LayoutKind::Sequential )]
	public value class Vector3
	{
	public:
		float X, Y, Z;

		Vector3( float x, float y, float z ) : X( x ), Y( y ), Z( z )
		{ }

		float Length()
		{
			return (float) Math::Sqrt( (X * X) + (Y * Y) + (Z * Z) );
		}

		void Normalize()
		{
			float length = Length();
			X /= length;
			Y /= length;
			Z /= length;
		}

		static Vector3 Normalize( Vector3 vec )
		{
			vec.Normalize();
			return vec;
		}

		static Vector3 TransformCoordinate( Vector3 coord, Matrix transform );

		static float Dot( Vector3 lhs, Vector3 rhs )
		{
			return (lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z);
		}

		static Vector3 Cross( Vector3 lhs, Vector3 rhs )
		{
			Vector3 result;
			result.X = lhs.Y * rhs.Z - lhs.Z * rhs.Y;
			result.Y = lhs.Z * rhs.X - lhs.X * rhs.Z;
			result.Z = lhs.X * rhs.Y - lhs.Y * rhs.X;
			return result;
		}

		static Vector3 Lerp( Vector3 start, Vector3 end, float factor )
		{
			Vector3 result;
			D3DXVec3Lerp( (D3DXVECTOR3*) &result, (D3DXVECTOR3*) &start, (D3DXVECTOR3*) &end, factor );
			return result;
		}

		static Vector3 operator + ( Vector3 lhs, Vector3 rhs )
		{
			Vector3 result;
			D3DXVec3Add( (D3DXVECTOR3*) &result, (D3DXVECTOR3*) &lhs, (D3DXVECTOR3*) &rhs );
			return result;
		}

		static Vector3 operator - ( Vector3 lhs, Vector3 rhs )
		{
			Vector3 result;
			D3DXVec3Subtract( (D3DXVECTOR3*) &result, (D3DXVECTOR3*) &lhs, (D3DXVECTOR3*) &rhs );
			return result;
		}

		static Vector3 operator * ( Vector3 vec, float scale )
		{
			Vector3 result;
			D3DXVec3Scale( (D3DXVECTOR3*) &result, (D3DXVECTOR3*) &vec, scale );
			return result;
		}

		static Vector3 operator * ( float scale, Vector3 vec )
		{
			return vec * scale;
		}
	};

	[StructLayout( LayoutKind::Sequential )]
	public value class Vector4
	{
	public:
		float X, Y, Z, W;

		Vector4( float x, float y, float z, float w ) : X( x ), Y( y ), Z( z ), W( w )
		{ }

		float Length()
		{
			return (float) Math::Sqrt( (X * X) + (Y * Y) + (Z * Z) + (W * W) );
		}

		void Normalize()
		{
			float length = Length();
			X /= length;
			Y /= length;
			Z /= length;
			W /= length;
		}

		static Vector3 Normalize( Vector3 vec )
		{
			vec.Normalize();
			return vec;
		}

		static Vector4 operator * ( Vector4 vec, float scale )
		{
			Vector4 result;
			D3DXVec4Scale( (D3DXVECTOR4*) &result, (D3DXVECTOR4*) &vec, scale );
			return result;
		}

		static Vector4 operator * ( float scale, Vector4 vec )
		{
			return vec * scale;
		}
	};

	[StructLayout( LayoutKind::Sequential )]
	public value class Plane
	{
	public:
		float A, B, C, D;

		void Normalize()
		{
			float magnitude = (A * A) + (B * B) + (C * C);
			magnitude = (float) Math::Sqrt( magnitude );

			A /= magnitude;
			B /= magnitude;
			C /= magnitude;
		}

		static Plane Transform( Plane coord, Matrix transform );

		float Dot( Vector3 point )
		{
			return A * point.X + B * point.Y + C * point.Z + D;
		}
	};

	value class Quaternion;

	[StructLayout( LayoutKind::Sequential )]
	public value class Matrix
	{
	public:
		float M11, M12, M13, M14;
		float M21, M22, M23, M24;
		float M31, M32, M33, M34;
		float M41, M42, M43, M44;

		void Invert()
		{
			pin_ptr<Matrix> pinnedThis = this;
			D3DXMatrixInverse( (D3DXMATRIX*) pinnedThis, NULL, (D3DXMATRIX*) pinnedThis );
		}

		static property Matrix Identity
		{
			Matrix get()
			{
				Matrix result;
				result.M11 = result.M22 = result.M33 = result.M44 = 1;
				return result;
			}
		}

		static Matrix Invert( Matrix mat )
		{
			Matrix result;
			D3DXMatrixInverse( (D3DXMATRIX*) &result, NULL, (D3DXMATRIX*) &mat );
			return result;
		}

		static Matrix Transpose( Matrix mat )
		{
			Matrix result;
			D3DXMatrixTranspose( (D3DXMATRIX*) &result, (D3DXMATRIX*) &mat );
			return result;
		}

		static Matrix RotationAxis( Vector3 axis, float angle )
		{
			Matrix result;
			D3DXMatrixRotationAxis( (D3DXMATRIX*) &result, (D3DXVECTOR3*) &axis, angle );
			return result;
		}

		static Matrix Translation( float x, float y, float z )
		{
			Matrix result;
			D3DXMatrixTranslation( (D3DXMATRIX*) &result, x, y, z );
			return result;
		}

		static Matrix Translation( Vector3 translation )
		{
			Matrix result;
			D3DXMatrixTranslation( (D3DXMATRIX*) &result, translation.X, translation.Y, translation.Z );
			return result;
		}

		static Matrix Translation( Vector3% translation )
		{
			Matrix result;
			D3DXMatrixTranslation( (D3DXMATRIX*) &result, translation.X, translation.Y, translation.Z );
			return result;
		}
		
		static Matrix Scaling ( float x, float y, float z )
		{
			Matrix result;
			D3DXMatrixScaling( (D3DXMATRIX*) &result, x, y, z );
			return result;
		}

		static Matrix Scaling ( Vector3 scaling )
		{
			Matrix result;
			D3DXMatrixScaling( (D3DXMATRIX*) &result, scaling.X, scaling.Y, scaling.Z );
			return result;
		}
		
		static Matrix Scaling ( Vector3% scaling )
		{
			Matrix result;
			D3DXMatrixScaling( (D3DXMATRIX*) &result, scaling.X, scaling.Y, scaling.Z );
			return result;
		}

		static Matrix LookAtLH(Vector3 eye, Vector3 target, Vector3 up )
		{
			Matrix result;
			D3DXMatrixLookAtLH( (D3DXMATRIX*) &result, (D3DXVECTOR3*) &eye, (D3DXVECTOR3*) &target, (D3DXVECTOR3*) &up );
			return (result);
		}

		static Matrix OrthoOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar )
		{
			Matrix result;
			D3DXMatrixOrthoOffCenterLH( (D3DXMATRIX*) &result, left, right, bottom, top, znear, zfar );
			return result;
		}

		static Matrix PerspectiveFovLH( float fov, float aspect, float znear, float zfar )
		{
			Matrix result;
			D3DXMatrixPerspectiveFovLH( (D3DXMATRIX*) &result, fov, aspect, znear, zfar );
			return result;
		}

		static Matrix Reflection( Plane plane )
		{
			Matrix result;
			D3DXMatrixReflect( (D3DXMATRIX*) &result, (const D3DXPLANE*) &plane );
			return result;
		}

		static Matrix RotationQuaternion( Quaternion quat );

		static Matrix operator * ( Matrix lhs, Matrix rhs )
		{
			Matrix result;
			D3DXMatrixMultiply( (D3DXMATRIX*) &result, (D3DXMATRIX*) &lhs, (D3DXMATRIX*) &rhs );
			return result;
		}
	};

	[StructLayout( LayoutKind::Sequential )]
	public value class Quaternion
	{
	public:
		float X, Y, Z, W;

		static property Quaternion Identity
		{
			Quaternion get()
			{
				Quaternion result;
				result.X = result.Y = result.Z = 0.0f;
				result.W = 1.0f;
				return result;
			}
		}

		Quaternion(float x,float y,float z,float w)
			: X(x), Y(y), Z(z), W(w)
		{
		}

		static Quaternion RotationYawPitchRoll( float yaw, float pitch, float roll )
		{
			Quaternion result;
			D3DXQuaternionRotationYawPitchRoll( (D3DXQUATERNION*) &result, yaw, pitch, roll );
			return result;
		}

		static Quaternion operator * (Quaternion lhs, Quaternion rhs)
		{
			Quaternion result;
			D3DXQuaternionMultiply( (D3DXQUATERNION*) &result, (const D3DXQUATERNION*) &lhs, (const D3DXQUATERNION*) &rhs );
			return result;
		}
	};

	inline Vector3 Vector3::TransformCoordinate( Vector3 coord, Matrix transform )
	{
		Vector3 result;
		D3DXVec3TransformCoord( (D3DXVECTOR3*) &result, (const D3DXVECTOR3*) &coord, (const D3DXMATRIX*) &transform );
		return result;
	}
	
	inline Plane Plane::Transform( SlimDX::Plane plane, SlimDX::Matrix transform )
	{
		Plane result;
		D3DXPlaneTransform( (D3DXPLANE*) &result, (const D3DXPLANE*) &plane, (const D3DXMATRIX*) &transform );
		return result;
	}

	inline Matrix Matrix::RotationQuaternion( Quaternion quat )
	{
		Matrix result;
		D3DXMatrixRotationQuaternion( (D3DXMATRIX*) &result, (const D3DXQUATERNION*) &quat );
		return result;
	}
}
