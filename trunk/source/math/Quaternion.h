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
	[StructLayout( LayoutKind::Sequential )]
	public value class Quaternion
	{
	public:
		property float X;
		property float Y;
		property float Z;
		property float W;

		static property Quaternion Identity
		{
			Quaternion get();
		}

		Quaternion(float x,float y,float z,float w);

		float Magnitude();
		float MagnitudeSquared();
		
		void Normalize();

		static Quaternion Invert( Quaternion quat );
		static Quaternion Normalize( Quaternion quat );
		static Quaternion Conjugate( Quaternion quat );
		static Quaternion Exponential( Quaternion quat );
		static Quaternion Logarithm( Quaternion quat );

		static Quaternion RotationAxis( Vector3 axis, float angle );
		static Quaternion RotationMatrix( Matrix matrix );
		static Quaternion RotationYawPitchRoll( float yaw, float pitch, float roll );
		static Quaternion BaryCentric( Quaternion q1, Quaternion q2, Quaternion q3, float f, float g );

		static Quaternion Slerp( Quaternion q1, Quaternion q2, float t);
		static Quaternion Squad( Quaternion q1, Quaternion a, Quaternion b, Quaternion c, float t );		

		static float Dot( Quaternion q1, Quaternion q2 );
		static Quaternion operator * (Quaternion lhs, Quaternion rhs);
		static Quaternion operator * (Quaternion lhs, float rhs);
		static Quaternion operator / (Quaternion lhs, float rhs);
		static Quaternion operator + (Quaternion lhs, Quaternion rhs);
		static Quaternion operator - (Quaternion lhs, Quaternion rhs);
	};
}
