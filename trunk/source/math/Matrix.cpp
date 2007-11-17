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
	D3DXMATRIX Matrix::ToD3DXMATRIX( Matrix matrix )
	{
		D3DXMATRIX result;
		result._11 = matrix.M11;
		result._12 = matrix.M12;
		result._13 = matrix.M13;
		result._14 = matrix.M14;
		result._21 = matrix.M21;
		result._22 = matrix.M22;
		result._23 = matrix.M23;
		result._24 = matrix.M24;
		result._31 = matrix.M31;
		result._32 = matrix.M32;
		result._33 = matrix.M33;
		result._34 = matrix.M34;
		result._41 = matrix.M41;
		result._42 = matrix.M42;
		result._43 = matrix.M43;
		result._44 = matrix.M44;

		return result;
	}

	Matrix Matrix::FromD3DXMATRIX( const D3DXMATRIX &matrix )
	{
		Matrix result;
		result.M11 = matrix._11;
		result.M12 = matrix._12;
		result.M13 = matrix._13;
		result.M14 = matrix._14;
		result.M21 = matrix._21;
		result.M22 = matrix._22;
		result.M23 = matrix._23;
		result.M24 = matrix._24;
		result.M31 = matrix._31;
		result.M32 = matrix._32;
		result.M33 = matrix._33;
		result.M34 = matrix._34;
		result.M41 = matrix._41;
		result.M42 = matrix._42;
		result.M43 = matrix._43;
		result.M44 = matrix._44;

		return result;
	}

	Matrix Matrix::Identity::get()
	{
		Matrix result;
		result.M11 = 1.0f;
		result.M22 = 1.0f;
		result.M33 = 1.0f;
		result.M44 = 1.0f;

		return result;
	}

	bool Matrix::IsIdentity::get()
	{
		if( M11 != 1.0f|| M22 != 1.0f || M33 != 1.0f || M44 != 1.0f )
			return false;

		if( M12 != 0.0f || M13 != 0.0f || M14 != 0.0f ||
			M21 != 0.0f || M23 != 0.0f || M24 != 0.0f ||
			M31 != 0.0f || M32 != 0.0f || M34 != 0.0f ||
			M41 != 0.0f || M42 != 0.0f || M43 != 0.0f )
			return false;

		return true;
	}

	void Matrix::Invert()
	{
		pin_ptr<Matrix> pinnedThis = this;
		D3DXMatrixInverse( (D3DXMATRIX*) pinnedThis, NULL, (D3DXMATRIX*) pinnedThis );
	}

	bool Matrix::Decompose( [Out] Vector3% scale, [Out] Quaternion% rotation, [Out] Vector3% translation )
	{
		Vector3 localScale, localTrans;
		Quaternion localRot;
		pin_ptr<Matrix> pinnedThis = this;

		HRESULT hr = D3DXMatrixDecompose( (D3DXVECTOR3*) &localScale, (D3DXQUATERNION*) &localRot,
			(D3DXVECTOR3*) &localTrans, (D3DXMATRIX*) pinnedThis );

		scale = localScale;
		rotation = localRot;
		translation = localTrans;

		return hr == S_OK;
	}
	
	float Matrix::Determinant()
	{
		pin_ptr<Matrix> pinnedThis = this;
		return D3DXMatrixDeterminant( (D3DXMATRIX*) pinnedThis );
	}

	Matrix Matrix::Multiply( Matrix left, Matrix right )
	{
		Matrix result;
		D3DXMatrixMultiply( (D3DXMATRIX*) &result, (D3DXMATRIX*) &left, (D3DXMATRIX*) &right );
		return result;
	}

	void Matrix::Multiply( Matrix% left, Matrix% right, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinLeft = &left;
		pin_ptr<Matrix> pinRight = &right;
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixMultiply( (D3DXMATRIX*) pinResult, (D3DXMATRIX*) pinLeft, (D3DXMATRIX*) pinRight );
	}

	Matrix Matrix::Billboard( Vector3 objectPosition, Vector3 cameraPosition, Vector3 cameraUpVector, Vector3 cameraForwardVector )
	{
		Matrix result;
		Vector3 difference = objectPosition - cameraPosition;
		Vector3 crossed;
		Vector3 final;

		float lengthSq = difference.LengthSquared();
		if (lengthSq < 0.0001f)
			difference = -cameraForwardVector;
		else
			difference *= (float)( 1.0f / Math::Sqrt( lengthSq ) );

		Vector3::Cross( cameraUpVector, difference, crossed );
		crossed.Normalize();
		Vector3::Cross( difference, crossed, final );

		result.M11 = final.X;
		result.M12 = final.Y;
		result.M13 = final.Z;
		result.M14 = 0.0f;
		result.M21 = crossed.X;
		result.M22 = crossed.Y;
		result.M23 = crossed.Z;
		result.M24 = 0.0f;
		result.M31 = difference.X;
		result.M32 = difference.Y;
		result.M33 = difference.Z;
		result.M34 = 0.0f;
		result.M41 = objectPosition.X;
		result.M42 = objectPosition.Y;
		result.M43 = objectPosition.Z;
		result.M44 = 1.0f;

		return result;
	}

	void Matrix::Billboard( Vector3% objectPosition, Vector3% cameraPosition, Vector3% cameraUpVector, Vector3% cameraForwardVector, [Out] Matrix% result )
	{
		Vector3 difference = objectPosition - cameraPosition;
		Vector3 crossed;
		Vector3 final;

		float lengthSq = difference.LengthSquared();
		if (lengthSq < 0.0001f)
			difference = -cameraForwardVector;
		else
			difference *= static_cast<float>( 1.0f / Math::Sqrt( lengthSq ) );

		Vector3::Cross( cameraUpVector, difference, crossed );
		crossed.Normalize();
		Vector3::Cross( difference, crossed, final );

		result.M11 = final.X;
		result.M12 = final.Y;
		result.M13 = final.Z;
		result.M14 = 0.0f;
		result.M21 = crossed.X;
		result.M22 = crossed.Y;
		result.M23 = crossed.Z;
		result.M24 = 0.0f;
		result.M31 = difference.X;
		result.M32 = difference.Y;
		result.M33 = difference.Z;
		result.M34 = 0.0f;
		result.M41 = objectPosition.X;
		result.M42 = objectPosition.Y;
		result.M43 = objectPosition.Z;
		result.M44 = 1.0f;
	}

	Matrix Matrix::RotationX( float angle )
	{
		Matrix result;
		D3DXMatrixRotationX( (D3DXMATRIX*) &result, angle );
		return result;
	}

	void Matrix::RotationX( float angle, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixRotationX( (D3DXMATRIX*) pinResult, angle );
	}
	
	Matrix Matrix::RotationY( float angle )
	{
		Matrix result;
		D3DXMatrixRotationY( (D3DXMATRIX*) &result, angle );
		return result;
	}

	void Matrix::RotationY( float angle, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixRotationY( (D3DXMATRIX*) pinResult, angle );
	}
	
	Matrix Matrix::RotationZ( float angle )
	{
		Matrix result;
		D3DXMatrixRotationZ( (D3DXMATRIX*) &result, angle );
		return result;
	}

	void Matrix::RotationZ( float angle, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixRotationZ( (D3DXMATRIX*) pinResult, angle );
	}

	Matrix Matrix::RotationQuaternion( Quaternion quat )
	{
		Matrix result;
		D3DXMatrixRotationQuaternion( (D3DXMATRIX*) &result, (D3DXQUATERNION*) &quat );
		return result;
	}

	void Matrix::RotationQuaternion( Quaternion% rotation, [Out] Matrix% result )
	{
		pin_ptr<Quaternion> pinRotation = &rotation;
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixRotationQuaternion( (D3DXMATRIX*) pinResult, (D3DXQUATERNION*) pinRotation );
	}

	Matrix Matrix::RotationAxis( Vector3 axis, float angle )
	{
		Matrix result;
		D3DXMatrixRotationAxis( (D3DXMATRIX*) &result, (D3DXVECTOR3*) &axis, angle );
		return result;
	}

	void Matrix::RotationAxis( Vector3% axis, float angle, [Out] Matrix% result )
	{
		pin_ptr<Vector3> pinAxis = &axis;
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixRotationAxis( (D3DXMATRIX*) pinResult, (D3DXVECTOR3*) pinAxis, angle );
	}

	Matrix Matrix::RotationYawPitchRoll( float yaw, float pitch, float roll )
	{
		Matrix result;
		D3DXMatrixRotationYawPitchRoll( (D3DXMATRIX*) &result, yaw, pitch, roll );
		return result;
	}

	void Matrix::RotationYawPitchRoll( float yaw, float pitch, float roll, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixRotationYawPitchRoll( (D3DXMATRIX*) pinResult, yaw, pitch, roll );
	}

	Matrix Matrix::Translation( float x, float y, float z )
	{
		Matrix result;
		D3DXMatrixTranslation( (D3DXMATRIX*) &result, x, y, z );
		return result;
	}

	void Matrix::Translation( float x, float y, float z, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixTranslation( (D3DXMATRIX*) pinResult, x, y, z );
	}

	Matrix Matrix::Translation( Vector3 translation )
	{
		Matrix result;
		D3DXMatrixTranslation( (D3DXMATRIX*) &result, translation.X, translation.Y, translation.Z );
		return result;
	}

	void Matrix::Translation( Vector3% translation, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixTranslation( (D3DXMATRIX*) pinResult, translation.X, translation.Y, translation.Z );
	}

	Matrix Matrix::Scaling ( float x, float y, float z )
	{
		Matrix result;
		D3DXMatrixScaling( (D3DXMATRIX*) &result, x, y, z );
		return result;
	}

	void Matrix::Scaling( float x, float y, float z, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixScaling( (D3DXMATRIX*) pinResult, x, y, z );
	}

	Matrix Matrix::Scaling ( Vector3 scaling )
	{
		Matrix result;
		D3DXMatrixScaling( (D3DXMATRIX*) &result, scaling.X, scaling.Y, scaling.Z );
		return result;
	}

	void Matrix::Scaling( Vector3% scaling, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixScaling( (D3DXMATRIX*) pinResult, scaling.X, scaling.Y, scaling.Z );
	}

	Matrix Matrix::AffineTransformation( float scaling, Vector3 rotationCenter, Quaternion rotation, Vector3 translation )
	{
		Matrix result;
		D3DXMatrixAffineTransformation( (D3DXMATRIX*) &result, scaling, (D3DXVECTOR3*) &rotationCenter, (D3DXQUATERNION*) &rotation, (D3DXVECTOR3*) &translation );
		return result;
	}

	void Matrix::AffineTransformation( float scaling, Vector3% rotationCenter, Quaternion% rotation, Vector3% translation, [Out] Matrix% result )
	{
		pin_ptr<Vector3> pinRotationCenter = &rotationCenter;
		pin_ptr<Quaternion> pinRotation = &rotation;
		pin_ptr<Vector3> pinTranslation = &translation;
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixAffineTransformation( (D3DXMATRIX*) pinResult, scaling, (D3DXVECTOR3*) pinRotationCenter, (D3DXQUATERNION*) pinRotation, (D3DXVECTOR3*) pinTranslation );
	}
	
	Matrix Matrix::AffineTransformation2D( float scaling, Vector2 rotationCenter, float rotation, Vector2 translation )
	{
		Matrix result;
		D3DXMatrixAffineTransformation2D( (D3DXMATRIX*) &result, scaling, (D3DXVECTOR2*) &rotationCenter, rotation, (D3DXVECTOR2*) &translation );
		return result;
	}

	void Matrix::AffineTransformation2D( float scaling, Vector2% rotationCenter, float rotation, Vector2% translation, [Out] Matrix% result )
	{
		pin_ptr<Vector2> pinRotationCenter = &rotationCenter;
		pin_ptr<Vector2> pinTranslation = &translation;
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixAffineTransformation2D( (D3DXMATRIX*) pinResult, scaling, (D3DXVECTOR2*) pinRotationCenter, rotation, (D3DXVECTOR2*) pinTranslation );
	}
	
	Matrix Matrix::Transformation( Vector3 scalingCenter, Quaternion scalingRotation, Vector3 scaling, Vector3 rotationCenter, Quaternion rotation, Vector3 translation )
	{
		Matrix result;
		D3DXMatrixTransformation( (D3DXMATRIX*) &result, (D3DXVECTOR3*) &scalingCenter, (D3DXQUATERNION*) &scalingRotation, (D3DXVECTOR3*) &scaling, (D3DXVECTOR3*) &rotationCenter, (D3DXQUATERNION*) &rotation, (D3DXVECTOR3*) &translation );
		return result;
	}

	void Matrix::Transformation( Vector3% scalingCenter, Quaternion% scalingRotation, Vector3% scaling, Vector3% rotationCenter, Quaternion% rotation, Vector3% translation, [Out] Matrix% result )
	{
		pin_ptr<Vector3> pinScalingCenter = &scalingCenter;
		pin_ptr<Quaternion> pinScalingRotation = &scalingRotation;
		pin_ptr<Vector3> pinScaling = &scaling;
		pin_ptr<Vector3> pinRotationCenter = &rotationCenter;
		pin_ptr<Quaternion> pinRotation = &rotation;
		pin_ptr<Vector3> pinTranslation = &translation;
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixTransformation( (D3DXMATRIX*) pinResult, (D3DXVECTOR3*) pinScalingCenter, (D3DXQUATERNION*) pinScalingRotation, 
			(D3DXVECTOR3*) pinScaling, (D3DXVECTOR3*) pinRotationCenter, (D3DXQUATERNION*) pinRotation, (D3DXVECTOR3*) pinTranslation );
	}
	
	Matrix Matrix::Transformation2D( Vector2 scalingCenter, float scalingRotation, Vector2 scaling, Vector2 rotationCenter, float rotation, Vector2 translation )
	{
		Matrix result;
		D3DXMatrixTransformation2D( (D3DXMATRIX*) &result, (D3DXVECTOR2*) &scalingCenter, scalingRotation, (D3DXVECTOR2*) &scaling, (D3DXVECTOR2*) &rotationCenter, rotation, (D3DXVECTOR2*) &translation );
		return result;
	}

	void Matrix::Transformation2D( Vector2% scalingCenter, float scalingRotation, Vector2% scaling, Vector2% rotationCenter, float rotation, Vector2% translation, [Out] Matrix% result )
	{
		pin_ptr<Vector2> pinScalingCenter = &scalingCenter;
		pin_ptr<Vector2> pinScaling = &scaling;
		pin_ptr<Vector2> pinRotationCenter = &rotationCenter;
		pin_ptr<Vector2> pinTranslation = &translation;
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixTransformation2D( (D3DXMATRIX*) pinResult, (D3DXVECTOR2*) pinScalingCenter, scalingRotation, 
			(D3DXVECTOR2*) pinScaling, (D3DXVECTOR2*) pinRotationCenter, rotation, (D3DXVECTOR2*) pinTranslation );
	}
	
	Matrix Matrix::LookAtLH(Vector3 eye, Vector3 target, Vector3 up )
	{
		Matrix result;
		D3DXMatrixLookAtLH( (D3DXMATRIX*) &result, (D3DXVECTOR3*) &eye, (D3DXVECTOR3*) &target, (D3DXVECTOR3*) &up );
		return result;
	}

	void Matrix::LookAtLH(Vector3% eye, Vector3% target, Vector3% up, [Out] Matrix% result )
	{
		pin_ptr<Vector3> pinEye = &eye;
		pin_ptr<Vector3> pinTarget = &target;
		pin_ptr<Vector3> pinUp = &up;
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixLookAtLH( (D3DXMATRIX*) pinResult, (D3DXVECTOR3*) pinEye, (D3DXVECTOR3*) pinTarget, (D3DXVECTOR3*) pinUp );
	}
	
	Matrix Matrix::LookAtRH(Vector3 eye, Vector3 target, Vector3 up )
	{
		Matrix result;
		D3DXMatrixLookAtRH( (D3DXMATRIX*) &result, (D3DXVECTOR3*) &eye, (D3DXVECTOR3*) &target, (D3DXVECTOR3*) &up );
		return result;
	}

	void Matrix::LookAtRH(Vector3% eye, Vector3% target, Vector3% up, [Out] Matrix% result )
	{
		pin_ptr<Vector3> pinEye = &eye;
		pin_ptr<Vector3> pinTarget = &target;
		pin_ptr<Vector3> pinUp = &up;
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixLookAtRH( (D3DXMATRIX*) pinResult, (D3DXVECTOR3*) pinEye, (D3DXVECTOR3*) pinTarget, (D3DXVECTOR3*) pinUp );
	}
	
	Matrix Matrix::OrthoLH( float width, float height, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixOrthoLH( (D3DXMATRIX*) &result, width, height, znear, zfar );
		return result;
	}

	void Matrix::OrthoLH( float width, float height, float znear, float zfar, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixOrthoLH( (D3DXMATRIX*) pinResult, width, height, znear, zfar );
	}
	
	Matrix Matrix::OrthoRH( float width, float height, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixOrthoLH( (D3DXMATRIX*) &result, width, height, znear, zfar );
		return result;
	}

	void Matrix::OrthoRH( float width, float height, float znear, float zfar, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixOrthoRH( (D3DXMATRIX*) pinResult, width, height, znear, zfar );
	}
	
	Matrix Matrix::OrthoOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixOrthoOffCenterLH( (D3DXMATRIX*) &result, left, right, bottom, top, znear, zfar );
		return result;
	}

	void Matrix::OrthoOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixOrthoOffCenterLH( (D3DXMATRIX*) pinResult, left, right, bottom, top, znear, zfar );
	}
	
	Matrix Matrix::OrthoOffCenterRH( float left, float right, float bottom, float top, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixOrthoOffCenterRH( (D3DXMATRIX*) &result, left, right, bottom, top, znear, zfar );
		return result;
	}

	void Matrix::OrthoOffCenterRH( float left, float right, float bottom, float top, float znear, float zfar, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixOrthoOffCenterRH( (D3DXMATRIX*) pinResult, left, right, bottom, top, znear, zfar );
	}
	
	Matrix Matrix::PerspectiveLH( float width, float height, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixPerspectiveLH( (D3DXMATRIX*) &result, width, height, znear, zfar );
		return result;
	}

	void Matrix::PerspectiveLH( float width, float height, float znear, float zfar, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixPerspectiveLH( (D3DXMATRIX*) pinResult, width, height, znear, zfar );
	}
	
	Matrix Matrix::PerspectiveRH( float width, float height, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixPerspectiveRH( (D3DXMATRIX*) &result, width, height, znear, zfar );
		return result;
	}

	void Matrix::PerspectiveRH( float width, float height, float znear, float zfar, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixPerspectiveRH( (D3DXMATRIX*) pinResult, width, height, znear, zfar );
	}

	Matrix Matrix::PerspectiveFovLH( float fov, float aspect, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixPerspectiveFovLH( (D3DXMATRIX*) &result, fov, aspect, znear, zfar );
		return result;
	}

	void Matrix::PerspectiveFovLH( float fov, float aspect, float znear, float zfar, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixPerspectiveFovLH( (D3DXMATRIX*) pinResult, fov, aspect, znear, zfar );
	}
	
	Matrix Matrix::PerspectiveFovRH( float fov, float aspect, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixPerspectiveFovRH( (D3DXMATRIX*) &result, fov, aspect, znear, zfar );
		return result;
	}

	void Matrix::PerspectiveFovRH( float fov, float aspect, float znear, float zfar, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixPerspectiveFovRH( (D3DXMATRIX*) pinResult, fov, aspect, znear, zfar );
	}
	
	Matrix Matrix::PerspectiveOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixPerspectiveOffCenterLH( (D3DXMATRIX*) &result, left, right, bottom, top, znear, zfar );
		return result;
	}

	void Matrix::PerspectiveOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixPerspectiveOffCenterLH( (D3DXMATRIX*) pinResult, left, right, bottom, top, znear, zfar );
	}
	
	Matrix Matrix::PerspectiveOffCenterRH( float left, float right, float bottom, float top, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixPerspectiveOffCenterRH( (D3DXMATRIX*) &result, left, right, bottom, top, znear, zfar );
		return result;
	}

	void Matrix::PerspectiveOffCenterRH( float left, float right, float bottom, float top, float znear, float zfar, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixPerspectiveOffCenterRH( (D3DXMATRIX*) pinResult, left, right, bottom, top, znear, zfar );
	}

	Matrix Matrix::Reflection( Plane plane )
	{
		Matrix result;
		D3DXMatrixReflect( (D3DXMATRIX*) &result, (D3DXPLANE*) &plane );
		return result;
	}

	void Matrix::Reflection( Plane% plane, [Out] Matrix% result )
	{
		pin_ptr<Plane> pinPlane = &plane;
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixReflect( (D3DXMATRIX*) pinResult, (D3DXPLANE*) pinPlane );
	}
	
	Matrix Matrix::Shadow( Vector4 light, Plane plane )
	{
		Matrix result;
		D3DXMatrixShadow( (D3DXMATRIX*) &result, (D3DXVECTOR4*) &light, (D3DXPLANE*) &plane );
		return result;
	}

	void Matrix::Shadow( Vector4% light, Plane% plane, [Out] Matrix% result )
	{
		pin_ptr<Vector4> pinLight = &light;
		pin_ptr<Plane> pinPlane = &plane;
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixShadow( (D3DXMATRIX*) pinResult, (D3DXVECTOR4*) pinLight, (D3DXPLANE*) pinPlane );
	}

	Matrix Matrix::Invert( Matrix mat )
	{
		Matrix result;
		D3DXMatrixInverse( (D3DXMATRIX*) &result, NULL, (D3DXMATRIX*) &mat );
		return result;
	}

	void Matrix::Invert( Matrix% mat, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinMatrix = &mat;
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixInverse( (D3DXMATRIX*) pinResult, NULL, (D3DXMATRIX*) pinMatrix );
	}

	Matrix Matrix::Transpose( Matrix mat )
	{
		Matrix result;
		D3DXMatrixTranspose( (D3DXMATRIX*) &result, (D3DXMATRIX*) &mat );
		return result;
	}

	void Matrix::Transpose( Matrix% mat, [Out] Matrix% result )
	{
		pin_ptr<Matrix> pinMatrix = &mat;
		pin_ptr<Matrix> pinResult = &result;
		D3DXMatrixTranspose( (D3DXMATRIX*) pinResult, (D3DXMATRIX*) pinMatrix );
	}

	Matrix Matrix::operator * ( Matrix lhs, Matrix rhs )
	{
		Matrix result;
		D3DXMatrixMultiply( (D3DXMATRIX*) &result, (D3DXMATRIX*) &lhs, (D3DXMATRIX*) &rhs );
		return result;
	}

	bool Matrix::operator == ( Matrix left, Matrix right )
	{
		return Matrix::Equals( left, right );
	}

	bool Matrix::operator != ( Matrix left, Matrix right )
	{
		return !Matrix::Equals( left, right );
	}

	String^ Matrix::ToString()
	{
		return String::Format( CultureInfo::CurrentCulture, "{M11:{0} M12:{1} M13:{2} M14:{3}} {M21:{4} M22:{5} M23:{6} M24:{7}} {M31:{8} M32:{9} M33:{10} M34:{11}} {M41:{12} M42:{13} M43:{14} M44:{15}}",
			M11.ToString(CultureInfo::CurrentCulture), M12.ToString(CultureInfo::CurrentCulture), M13.ToString(CultureInfo::CurrentCulture), M14.ToString(CultureInfo::CurrentCulture),
			M21.ToString(CultureInfo::CurrentCulture), M22.ToString(CultureInfo::CurrentCulture), M23.ToString(CultureInfo::CurrentCulture), M24.ToString(CultureInfo::CurrentCulture),
			M31.ToString(CultureInfo::CurrentCulture), M32.ToString(CultureInfo::CurrentCulture), M33.ToString(CultureInfo::CurrentCulture), M34.ToString(CultureInfo::CurrentCulture),
			M41.ToString(CultureInfo::CurrentCulture), M42.ToString(CultureInfo::CurrentCulture), M43.ToString(CultureInfo::CurrentCulture), M44.ToString(CultureInfo::CurrentCulture) );
	}

	int Matrix::GetHashCode()
	{
		return M11.GetHashCode() + M12.GetHashCode() + M13.GetHashCode() + M14.GetHashCode() +
			   M21.GetHashCode() + M22.GetHashCode() + M23.GetHashCode() + M24.GetHashCode() +
			   M31.GetHashCode() + M32.GetHashCode() + M33.GetHashCode() + M34.GetHashCode() +
			   M41.GetHashCode() + M42.GetHashCode() + M43.GetHashCode() + M44.GetHashCode();
	}

	bool Matrix::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<Matrix>( value ) );
	}

	bool Matrix::Equals( Matrix value )
	{
		return ( M11 == value.M11 && M12 == value.M12 && M13 == value.M13 && M14 == value.M14 &&
				 M21 == value.M21 && M22 == value.M22 && M23 == value.M23 && M24 == value.M24 &&
				 M31 == value.M31 && M32 == value.M32 && M33 == value.M33 && M34 == value.M34 &&
				 M41 == value.M41 && M42 == value.M42 && M43 == value.M43 && M44 == value.M44 );
	}

	bool Matrix::Equals( Matrix% value1, Matrix% value2 )
	{
		return ( value1.M11 == value2.M11 && value1.M12 == value2.M12 && value1.M13 == value2.M13 && value1.M14 == value2.M14 &&
				 value1.M21 == value2.M21 && value1.M22 == value2.M22 && value1.M23 == value2.M23 && value1.M24 == value2.M24 &&
				 value1.M31 == value2.M31 && value1.M32 == value2.M32 && value1.M33 == value2.M33 && value1.M34 == value2.M34 &&
				 value1.M41 == value2.M41 && value1.M42 == value2.M42 && value1.M43 == value2.M43 && value1.M44 == value2.M44 );
	}
}
