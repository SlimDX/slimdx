/*
* Copyright (c) 2007-2008 SlimDX Group
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

struct D3DXMATRIX;

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	value class Plane;
	value class Quaternion;
	value class Vector2;
	value class Vector3;
	value class Vector4;
	
	[System::Serializable]
	[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
	public value class Matrix : System::IEquatable<Matrix>
	{
	internal:
		static D3DXMATRIX ToD3DXMATRIX( Matrix matrix );
		static Matrix FromD3DXMATRIX( const D3DXMATRIX &matrix );

	public:
		property float M11; property float M12; property float M13; property float M14;
		property float M21; property float M22; property float M23; property float M24;
		property float M31; property float M32; property float M33; property float M34;
		property float M41; property float M42; property float M43; property float M44;

		static property Matrix Identity { Matrix get(); }
		property bool IsIdentity { bool get(); }

		void Invert();
		bool Decompose( [Out] Vector3% scale, [Out] Quaternion% rotation, [Out] Vector3% translation );
		float Determinant();

		static Matrix Add( Matrix left, Matrix right );
		static void   Add( Matrix% left, Matrix% right, [Out] Matrix% result );

		static Matrix Subtract( Matrix left, Matrix right );
		static void   Subtract( Matrix% left, Matrix% right, [Out] Matrix% result );

		static Matrix Multiply( Matrix left, Matrix right );
		static void   Multiply( Matrix% left, Matrix% right, [Out] Matrix% result );

		static Matrix Multiply( Matrix left, float right );
		static void   Multiply( Matrix% left, float right, [Out] Matrix% result );

		static Matrix Divide( Matrix left, Matrix right );
		static void   Divide( Matrix% left, Matrix% right, [Out] Matrix% result );

		static Matrix Divide( Matrix left, float right );
		static void   Divide( Matrix% left, float right, [Out] Matrix% result );

		static Matrix Negate( Matrix matrix );
		static void   Negate( Matrix% matrix, [Out] Matrix% result );

		static Matrix Lerp( Matrix value1, Matrix value2, float amount );
		static void   Lerp( Matrix% value1, Matrix% value2, float amount, [Out] Matrix% result );

		static Matrix Billboard( Vector3 objectPosition, Vector3 cameraPosition, Vector3 cameraUpVector, Vector3 cameraForwardVector );
		static void   Billboard( Vector3% objectPosition, Vector3% cameraPosition, Vector3% cameraUpVector, Vector3% cameraForwardVector, [Out] Matrix% result );

		static Matrix RotationX( float angle );
		static void   RotationX( float angle, [Out] Matrix% result );

		static Matrix RotationY( float angle );
		static void   RotationY( float angle, [Out] Matrix% result );

		static Matrix RotationZ( float angle );
		static void   RotationZ( float angle, [Out] Matrix% result );

		static Matrix RotationAxis( Vector3 axis, float angle );
		static void   RotationAxis( Vector3% axis, float angle, [Out] Matrix% result );

		static Matrix RotationQuaternion( Quaternion rotation );
		static void   RotationQuaternion( Quaternion% rotation, [Out] Matrix% result );

		static Matrix RotationYawPitchRoll( float yaw, float pitch, float roll );
		static void   RotationYawPitchRoll( float yaw, float pitch, float roll, [Out] Matrix% result );

		static Matrix LookAtLH( Vector3 eye, Vector3 target, Vector3 up );
		static void   LookAtLH( Vector3% eye, Vector3% target, Vector3% up, [Out] Matrix% result );

		static Matrix LookAtRH( Vector3 eye, Vector3 target, Vector3 up );
		static void   LookAtRH( Vector3% eye, Vector3% target, Vector3% up, [Out] Matrix% result );

		static Matrix OrthoLH( float width, float height, float znear, float zfar );
		static void   OrthoLH( float width, float height, float znear, float zfar, [Out] Matrix% result );

		static Matrix OrthoRH( float width, float height, float znear, float zfar );
		static void   OrthoRH( float width, float height, float znear, float zfar, [Out] Matrix% result );

		static Matrix OrthoOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar );
		static void   OrthoOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar, [Out] Matrix% result );

		static Matrix OrthoOffCenterRH( float left, float right, float bottom, float top, float znear, float zfar );
		static void   OrthoOffCenterRH( float left, float right, float bottom, float top, float znear, float zfar, [Out] Matrix% result );

		static Matrix PerspectiveLH( float width, float height, float znear, float zfar );
		static void   PerspectiveLH( float width, float height, float znear, float zfar, [Out] Matrix% result );

		static Matrix PerspectiveRH( float width, float height, float znear, float zfar );
		static void   PerspectiveRH( float width, float height, float znear, float zfar, [Out] Matrix% result );

		static Matrix PerspectiveFovLH( float fov, float aspect, float znear, float zfar );
		static void   PerspectiveFovLH( float fov, float aspect, float znear, float zfar, [Out] Matrix% result );

		static Matrix PerspectiveFovRH( float fov, float aspect, float znear, float zfar );
		static void   PerspectiveFovRH( float fov, float aspect, float znear, float zfar, [Out] Matrix% result );

		static Matrix PerspectiveOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar );
		static void   PerspectiveOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar, [Out] Matrix% result );
		
		static Matrix PerspectiveOffCenterRH( float left, float right, float bottom, float top, float znear, float zfar );
		static void   PerspectiveOffCenterRH( float left, float right, float bottom, float top, float znear, float zfar, [Out] Matrix% result );

		static Matrix Reflection( Plane plane );
		static void   Reflection( Plane% plane, [Out] Matrix% result );

		static Matrix Scaling( float x, float y, float z );
		static void   Scaling( float x, float y, float z, [Out] Matrix% result );

		static Matrix Scaling( Vector3 scale );
		static void   Scaling( Vector3% scale, [Out] Matrix% result );

		static Matrix Shadow( Vector4 light, Plane plane );
		static void   Shadow( Vector4% light, Plane% plane, [Out] Matrix% result );

		static Matrix Translation( float x, float y, float z );
		static void   Translation( float x, float y, float z, [Out] Matrix% result );

		static Matrix Translation( Vector3 amount );
		static void   Translation( Vector3% amount, [Out] Matrix% result );

		static Matrix Invert( Matrix matrix );
		static void   Invert( Matrix% matrix, [Out] Matrix% result );

		static Matrix Transpose( Matrix matrix );
		static void   Transpose( Matrix% matrix, [Out] Matrix% result );

		static Matrix AffineTransformation( float scaling, Vector3 rotationCenter, Quaternion rotation, Vector3 translation );
		static void   AffineTransformation( float scaling, Vector3% rotationCenter, Quaternion% rotation, Vector3% translation, [Out] Matrix% result );
		
		static Matrix AffineTransformation2D( float scaling, Vector2 rotationCenter, float rotation, Vector2 translation );
		static void   AffineTransformation2D( float scaling, Vector2% rotationCenter, float rotation, Vector2% translation, [Out] Matrix% result );

		static Matrix Transformation( Vector3 scalingCenter, Quaternion scalingRotation, Vector3 scaling, Vector3 rotationCenter, Quaternion rotation, Vector3 translation );
		static void   Transformation( Vector3% scalingCenter, Quaternion% scalingRotation, Vector3% scaling, Vector3% rotationCenter, Quaternion% rotation, Vector3% translation, [Out] Matrix% result );
		
		static Matrix Transformation2D( Vector2 scalingCenter, float scalingRotation, Vector2 scaling, Vector2 rotationCenter, float rotation, Vector2 translation );
		static void   Transformation2D( Vector2% scalingCenter, float scalingRotation, Vector2% scaling, Vector2% rotationCenter, float rotation, Vector2% translation, [Out] Matrix% result );
		
		static Matrix operator - ( Matrix matrix );
		static Matrix operator + ( Matrix left, Matrix right );
		static Matrix operator - ( Matrix left, Matrix right );
		static Matrix operator / ( Matrix left, Matrix right );
		static Matrix operator / ( Matrix left, float right );
		static Matrix operator * ( Matrix left, Matrix right );
		static Matrix operator * ( Matrix left, float right );
		static Matrix operator * ( float left, Matrix right );
		static bool operator == ( Matrix left, Matrix right );
		static bool operator != ( Matrix left, Matrix right );
		
		virtual System::String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( System::Object^ obj ) override;
		virtual bool Equals( Matrix other );
		static bool Equals( Matrix% value1, Matrix% value2 );
	};
}
