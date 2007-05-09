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

	Matrix Matrix::Transpose( Matrix mat )
	{
		Matrix result;
		D3DXMatrixTranspose( (D3DXMATRIX*) &result, (D3DXMATRIX*) &mat );
		return result;
	}

	Matrix Matrix::RotationAxis( Vector3 axis, float angle )
	{
		Matrix result;
		D3DXMatrixRotationAxis( (D3DXMATRIX*) &result, (D3DXVECTOR3*) &axis, angle );
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

	Matrix Matrix::LookAtLH(Vector3 eye, Vector3 target, Vector3 up )
	{
		Matrix result;
		D3DXMatrixLookAtLH( (D3DXMATRIX*) &result, (D3DXVECTOR3*) &eye, (D3DXVECTOR3*) &target, (D3DXVECTOR3*) &up );
		return (result);
	}

	Matrix Matrix::OrthoOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixOrthoOffCenterLH( (D3DXMATRIX*) &result, left, right, bottom, top, znear, zfar );
		return result;
	}

	Matrix Matrix::PerspectiveFovLH( float fov, float aspect, float znear, float zfar )
	{
		Matrix result;
		D3DXMatrixPerspectiveFovLH( (D3DXMATRIX*) &result, fov, aspect, znear, zfar );
		return result;
	}

	Matrix Matrix::Reflection( Plane plane )
	{
		Matrix result;
		D3DXMatrixReflect( (D3DXMATRIX*) &result, (const D3DXPLANE*) &plane );
		return result;
	}

	Matrix Matrix::operator * ( Matrix lhs, Matrix rhs )
	{
		Matrix result;
		D3DXMatrixMultiply( (D3DXMATRIX*) &result, (D3DXMATRIX*) &lhs, (D3DXMATRIX*) &rhs );
		return result;
	}

	Matrix Matrix::RotationQuaternion( Quaternion quat )
	{
		Matrix result;
		D3DXMatrixRotationQuaternion( (D3DXMATRIX*) &result, (const D3DXQUATERNION*) &quat );
		return result;
	}
}
