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

		void Invert();
		static Matrix Invert( Matrix mat );
		static Matrix Transpose( Matrix mat );

		static Matrix RotationAxis( Vector3 axis, float angle );

		static Matrix Translation( float x, float y, float z );
		static Matrix Translation( Vector3 translation );
		static Matrix Translation( Vector3% translation );
		
		static Matrix Scaling ( float x, float y, float z );
		static Matrix Scaling ( Vector3 scaling );
		static Matrix Scaling ( Vector3% scaling );

		static Matrix LookAtLH(Vector3 eye, Vector3 target, Vector3 up );

		static Matrix OrthoOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar );
		static Matrix PerspectiveFovLH( float fov, float aspect, float znear, float zfar );

		static Matrix Reflection( Plane plane );

		static Matrix RotationQuaternion( Quaternion quat );

		static Matrix operator * ( Matrix lhs, Matrix rhs );
	};
}
