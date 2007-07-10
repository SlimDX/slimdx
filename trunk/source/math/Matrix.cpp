#include <windows.h>
#include <d3dx9.h>

#include "Math.h"

namespace SlimDX
{
	Matrix Matrix::Identity::get()
	{
		Matrix result;
		result.M11 = result.M22 = result.M33 = result.M44 = 1;
		return result;
	}

	bool Matrix::IsIdentity::get()
	{
		pin_ptr<Matrix> pinnedThis = this;
		return D3DXMatrixIsIdentity( (D3DXMATRIX*) pinnedThis ) ? true : false;
	}

	void Matrix::Invert()
	{
		pin_ptr<Matrix> pinnedThis = this;
		D3DXMatrixInverse( (D3DXMATRIX*) pinnedThis, NULL, (D3DXMATRIX*) pinnedThis );
	}

	Matrix Matrix::Invert( Matrix mat )
	{
		Matrix result;
		D3DXMatrixInverse( (D3DXMATRIX*) &result, NULL, (D3DXMATRIX*) &mat );
		return result;
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

	Matrix Matrix::Transpose( Matrix mat )
	{
		Matrix result;
		D3DXMatrixTranspose( (D3DXMATRIX*) &result, (D3DXMATRIX*) &mat );
		return result;
	}

	Matrix Matrix::RotationX( float angle )
	{
		Matrix result;
		D3DXMatrixRotationX( (D3DXMATRIX*) &result, angle );
		return result;
	}
	
	Matrix Matrix::RotationY( float angle )
	{
		Matrix result;
		D3DXMatrixRotationY( (D3DXMATRIX*) &result, angle );
		return result;
	}
	
	Matrix Matrix::RotationZ( float angle )
	{
		Matrix result;
		D3DXMatrixRotationZ( (D3DXMATRIX*) &result, angle );
		return result;
	}

	Matrix Matrix::RotationQuaternion( Quaternion quat )
	{
		Matrix result;
		D3DXMatrixRotationQuaternion( (D3DXMATRIX*) &result, (D3DXQUATERNION*) &quat );
		return result;
	}

	Matrix Matrix::RotationAxis( Vector3 axis, float angle )
	{
		Matrix result;
		D3DXMatrixRotationAxis( (D3DXMATRIX*) &result, (D3DXVECTOR3*) &axis, angle );
		return result;
	}

	Matrix Matrix::RotationYawPitchRoll( float yaw, float pitch, float roll )
	{
		Matrix result;
		D3DXMatrixRotationYawPitchRoll( (D3DXMATRIX*) &result, yaw, pitch, roll );
		return result;
	}

	Matrix Matrix::Translation( float x, float y, float z )
	{
		Matrix result;
		D3DXMatrixTranslation( (D3DXMATRIX*) &result, x, y, z );
		return result;
	}

	Matrix Matrix::Translation( Vector3 translation )
	{
		Matrix result;
		D3DXMatrixTranslation( (D3DXMATRIX*) &result, translation.X, translation.Y, translation.Z );
		return result;
	}

	Matrix Matrix::Translation( Vector3% translation )
	{
		Matrix result;
		D3DXMatrixTranslation( (D3DXMATRIX*) &result, translation.X, translation.Y, translation.Z );
		return result;
	}
	
	Matrix Matrix::Scaling ( float x, float y, float z )
	{
		Matrix result;
		D3DXMatrixScaling( (D3DXMATRIX*) &result, x, y, z );
		return result;
	}

	Matrix Matrix::Scaling ( Vector3 scaling )
	{
		Matrix result;
		D3DXMatrixScaling( (D3DXMATRIX*) &result, scaling.X, scaling.Y, scaling.Z );
		return result;
	}
	
	Matrix Matrix::Scaling ( Vector3% scaling )
	{
		Matrix result;
		D3DXMatrixScaling( (D3DXMATRIX*) &result, scaling.X, scaling.Y, scaling.Z );
		return result;
	}

	Matrix Matrix::AffineTransformation( float scaling, Vector3 rotationCenter, Quaternion rotation, Vector3 translation )
	{
		Matrix result;
		D3DXMatrixAffineTransformation( (D3DXMATRIX*) &result, scaling, (D3DXVECTOR3*) &rotationCenter, (D3DXQUATERNION*) &rotation, (D3DXVECTOR3*) &translation );
		return result;
	}
	
	Matrix Matrix::AffineTransformation2D( float scaling, Vector2 rotationCenter, float rotation, Vector2 translation )
	{
		Matrix result;
		D3DXMatrixAffineTransformation2D( (D3DXMATRIX*) &result, scaling, (D3DXVECTOR2*) &rotationCenter, rotation, (D3DXVECTOR2*) &translation );
		return result;
	}
	
	Matrix Matrix::Transformation( Vector3 scalingCenter, Quaternion scalingRotation, Vector3 scaling, Vector3 rotationCenter, Quaternion rotation, Vector3 translation )
	{
		Matrix result;
		D3DXMatrixTransformation( (D3DXMATRIX*) &result, (D3DXVECTOR3*) &scalingCenter, (D3DXQUATERNION*) &scalingRotation, (D3DXVECTOR3*) &scaling, (D3DXVECTOR3*) &rotationCenter, (D3DXQUATERNION*) &rotation, (D3DXVECTOR3*) &translation );
		return result;
	}
	
	Matrix Matrix::Transformation2D( Vector2 scalingCenter, float scalingRotation, Vector2 scaling, Vector2 rotationCenter, float rotation, Vector2 translation )
	{
		Matrix result;
		D3DXMatrixTransformation2D( (D3DXMATRIX*) &result, (D3DXVECTOR2*) &scalingCenter, scalingRotation, (D3DXVECTOR2*) &scaling, (D3DXVECTOR2*) &rotationCenter, rotation, (D3DXVECTOR2*) &translation );
		return result;
	}	
	
	Matrix Matrix::LookAtLH(Vector3 eye, Vector3 target, Vector3 up )
	{
		Matrix result;
		D3DXMatrixLookAtLH( (D3DXMATRIX*) &result, (D3DXVECTOR3*) &eye, (D3DXVECTOR3*) &target, (D3DXVECTOR3*) &up );
		return result;
	}
	
	Matrix Matrix::LookAtRH(Vector3 eye, Vector3 target, Vector3 up )
	{
		Matrix result;
		D3DXMatrixLookAtRH( (D3DXMATRIX*) &result, (D3DXVECTOR3*) &eye, (D3DXVECTOR3*) &target, (D3DXVECTOR3*) &up );
		return result;
	}
	
	Matrix Matrix::OrthoLH( float width, float height, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixOrthoLH( (D3DXMATRIX*) &result, width, height, znear, zfar );
		return result;
	}
	
	Matrix Matrix::OrthoRH( float width, float height, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixOrthoLH( (D3DXMATRIX*) &result, width, height, znear, zfar );
		return result;
	}
	
	Matrix Matrix::OrthoOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixOrthoOffCenterLH( (D3DXMATRIX*) &result, left, right, bottom, top, znear, zfar );
		return result;
	}
	
	Matrix Matrix::OrthoOffCenterRH( float left, float right, float bottom, float top, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixOrthoOffCenterRH( (D3DXMATRIX*) &result, left, right, bottom, top, znear, zfar );
		return result;
	}
	
	Matrix Matrix::PerspectiveLH( float width, float height, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixPerspectiveLH( (D3DXMATRIX*) &result, width, height, znear, zfar );
		return result;
	}
	
	Matrix Matrix::PerspectiveRH( float width, float height, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixPerspectiveRH( (D3DXMATRIX*) &result, width, height, znear, zfar );
		return result;
	}
	
	Matrix Matrix::PerspectiveFovLH( float fov, float aspect, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixPerspectiveFovLH( (D3DXMATRIX*) &result, fov, aspect, znear, zfar );
		return result;
	}
	
	Matrix Matrix::PerspectiveFovRH( float fov, float aspect, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixPerspectiveFovRH( (D3DXMATRIX*) &result, fov, aspect, znear, zfar );
		return result;
	}
	
	Matrix Matrix::PerspectiveOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixPerspectiveOffCenterLH( (D3DXMATRIX*) &result, left, right, bottom, top, znear, zfar );
		return result;
	}
	
	Matrix Matrix::PerspectiveOffCenterRH( float left, float right, float bottom, float top, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixPerspectiveOffCenterRH( (D3DXMATRIX*) &result, left, right, bottom, top, znear, zfar );
		return result;
	}

	Matrix Matrix::Reflection( Plane plane )
	{
		Matrix result;
		D3DXMatrixReflect( (D3DXMATRIX*) &result, (D3DXPLANE*) &plane );
		return result;
	}
	
	Matrix Matrix::Shadow( Vector4 light, Plane plane )
	{
		Matrix result;
		D3DXMatrixShadow( (D3DXMATRIX*) &result, (D3DXVECTOR4*) &light, (D3DXPLANE*) &plane );
		return result;
	}

	Matrix Matrix::operator * ( Matrix lhs, Matrix rhs )
	{
		Matrix result;
		D3DXMatrixMultiply( (D3DXMATRIX*) &result, (D3DXMATRIX*) &lhs, (D3DXMATRIX*) &rhs );
		return result;
	}
}
