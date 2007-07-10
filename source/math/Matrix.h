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

namespace SlimDX
{
	[StructLayout( LayoutKind::Sequential )]
	public value class Matrix
	{
	public:
		float M11, M12, M13, M14;
		float M21, M22, M23, M24;
		float M31, M32, M33, M34;
		float M41, M42, M43, M44;

		static property Matrix Identity
		{
			Matrix get();
		}
		
		property bool IsIdentity
		{
			bool get();
		}

		void Invert();
		bool Decompose( [Out] Vector3% scale, [Out] Quaternion% rotation, [Out] Vector3% translation );

		float Determinant();

		static Matrix Invert( Matrix mat );
		static Matrix Transpose( Matrix mat );
		
		static Matrix RotationX( float angle );
		static Matrix RotationY( float angle );
		static Matrix RotationZ( float angle );
		static Matrix RotationQuaternion( Quaternion quat );
		static Matrix RotationAxis( Vector3 axis, float angle );
		static Matrix RotationYawPitchRoll( float yaw, float pitch, float roll );

		static Matrix Translation( float x, float y, float z );
		static Matrix Translation( Vector3 translation );
		static Matrix Translation( Vector3% translation );
		
		static Matrix Scaling ( float x, float y, float z );
		static Matrix Scaling ( Vector3 scaling );
		static Matrix Scaling ( Vector3% scaling );
		
		static Matrix AffineTransformation( float scaling, Vector3 rotationCenter, Quaternion rotation, Vector3 translation );
		static Matrix AffineTransformation2D( float scaling, Vector2 rotationCenter, float rotation, Vector2 translation );
		static Matrix Transformation( Vector3 scalingCenter, Quaternion scalingRotation, Vector3 scaling, Vector3 rotationCenter, Quaternion rotation, Vector3 translation );
		static Matrix Transformation2D( Vector2 scalingCenter, float scalingRotation, Vector2 scaling, Vector2 rotationCenter, float rotation, Vector2 translation );
		
		static Matrix LookAtLH(Vector3 eye, Vector3 target, Vector3 up );
		static Matrix LookAtRH(Vector3 eye, Vector3 target, Vector3 up );
		
		static Matrix OrthoLH( float width, float height, float znear, float zfar );
		static Matrix OrthoRH( float width, float height, float znear, float zfar );
		static Matrix OrthoOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar );
		static Matrix OrthoOffCenterRH( float left, float right, float bottom, float top, float znear, float zfar );
		static Matrix PerspectiveLH( float width, float height, float znear, float zfar );
		static Matrix PerspectiveRH( float width, float height, float znear, float zfar );
		static Matrix PerspectiveFovLH( float fov, float aspect, float znear, float zfar );
		static Matrix PerspectiveFovRH( float fov, float aspect, float znear, float zfar );
		static Matrix PerspectiveOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar );
		static Matrix PerspectiveOffCenterRH( float left, float right, float bottom, float top, float znear, float zfar );
	
		static Matrix Reflection( Plane plane );
		static Matrix Shadow( Vector4 light, Plane plane );
		
		static Matrix operator * ( Matrix lhs, Matrix rhs );
		
	};
}
