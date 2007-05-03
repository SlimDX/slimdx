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

		static Quaternion RotationYawPitchRoll( float yaw, float pitch, float roll )
		{
			Quaternion result;
			D3DXQuaternionRotationYawPitchRoll( (D3DXQUATERNION*) &result, yaw, pitch, roll );
			return result;
		}
	};

	inline Vector3 Vector3::TransformCoordinate( SlimDX::Vector3 coord, SlimDX::Matrix transform )
	{
		Vector3 result;
		D3DXVec3TransformCoord( (D3DXVECTOR3*) &result, (D3DXVECTOR3*) &coord, (D3DXMATRIX*) &transform );
		return result;
	}

	inline Matrix Matrix::RotationQuaternion( Quaternion quat )
	{
		Matrix result;
		D3DXMatrixRotationQuaternion( (D3DXMATRIX*) &result, (D3DXQUATERNION*) &quat );
		return result;
	}
}
