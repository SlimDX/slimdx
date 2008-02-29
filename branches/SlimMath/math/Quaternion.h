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

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	value class Matrix;
	value class Vector3;
	
	[System::Serializable]
	[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
	public value class Quaternion : System::IEquatable<Quaternion>
	{
	public:
		property float X;
		property float Y;
		property float Z;
		property float W;

		Quaternion( float x, float y, float z, float w );
		Quaternion( Vector3 value, float w );

		static property Quaternion Identity { Quaternion get(); }
		property bool IsIdentity { bool get(); }
		property Vector3 Axis { Vector3 get(); }
		property float Angle { float get(); }

		float Length();
		float LengthSquared();
		void Normalize();
		void Conjugate();
		void Invert();

		static Quaternion Add( Quaternion left, Quaternion right );
		static void Add( Quaternion% left, Quaternion% right, [Out] Quaternion% result );

		static Quaternion Barycentric( Quaternion source1, Quaternion source2, Quaternion source3, float weight1, float weight2 );
		static void Barycentric( Quaternion% source1, Quaternion% source2, Quaternion% source3, float weight1, float weight2, [Out] Quaternion% result );

		static Quaternion Concatenate( Quaternion left, Quaternion right );
		static void Concatenate( Quaternion% left, Quaternion% right, [Out] Quaternion% result );

		static Quaternion Conjugate( Quaternion quaternion );
		static void Conjugate( Quaternion% quaternion, [Out] Quaternion% result );

		static Quaternion Divide( Quaternion left, Quaternion right );
		static void Divide( Quaternion% left, Quaternion% right, [Out] Quaternion% result );

		static float Dot( Quaternion left, Quaternion right );

		static Quaternion Exponential( Quaternion quaternion );
		static void Exponential( Quaternion% quaternion, [Out] Quaternion% result );

		static Quaternion Invert( Quaternion quaternion );
		static void Invert( Quaternion% quaternion, [Out] Quaternion% result );

		static Quaternion Lerp( Quaternion left, Quaternion right, float amount );
		static void Lerp( Quaternion% left, Quaternion% right, float amount, [Out] Quaternion% result );

		static Quaternion Logarithm( Quaternion quaternion );
		static void Logarithm( Quaternion% quaternion, [Out] Quaternion% result );

		static Quaternion Multiply( Quaternion left, Quaternion right );
		static void Multiply( Quaternion% left, Quaternion% right, [Out] Quaternion% result );

		static Quaternion Multiply( Quaternion quaternion, float scale );
		static void Multiply( Quaternion% quaternion, float scale, [Out] Quaternion% result );

		static Quaternion Negate( Quaternion quaternion );
		static void Negate( Quaternion% quaternion, [Out] Quaternion% result );

		static Quaternion Normalize( Quaternion quaternion );
		static void Normalize( Quaternion% quaternion, [Out] Quaternion% result );

		static Quaternion RotationAxis( Vector3 axis, float angle );
		static void RotationAxis( Vector3% axis, float angle, [Out] Quaternion% result );

		static Quaternion RotationMatrix( Matrix matrix );
		static void RotationMatrix( Matrix% matrix, [Out] Quaternion% result );

		static Quaternion RotationYawPitchRoll( float yaw, float pitch, float roll );
		static void RotationYawPitchRoll( float yaw, float pitch, float roll, [Out] Quaternion% result );

		static Quaternion Slerp( Quaternion left, Quaternion right, float amount );
		static void Slerp( Quaternion% left, Quaternion% right, float amount, [Out] Quaternion% result );

		static Quaternion Squad( Quaternion source1, Quaternion source2, Quaternion source3, Quaternion source4, float amount );
		static void Squad( Quaternion% source1, Quaternion% source2, Quaternion% source3, Quaternion% source4, float amount, [Out] Quaternion% result );

		static array<Quaternion>^ SquadSetup( Quaternion source1, Quaternion source2, Quaternion source3, Quaternion source4 );
		static array<Quaternion>^ SquadSetup( Quaternion% source1, Quaternion% source2, Quaternion% source3, Quaternion% source4 );

		static Quaternion Subtract( Quaternion left, Quaternion right );
		static void Subtract( Quaternion% left, Quaternion% right, [Out] Quaternion% result );

		static Quaternion operator * ( Quaternion left, Quaternion right );
		static Quaternion operator * ( Quaternion left, float right );
		static Quaternion operator * ( float left, Quaternion right );
		static Quaternion operator / ( Quaternion left, float right );
		static Quaternion operator + ( Quaternion left, Quaternion right );
		static Quaternion operator - ( Quaternion left, Quaternion right );
		static Quaternion operator - ( Quaternion quaternion );

		static bool operator == ( Quaternion left, Quaternion right );
		static bool operator != ( Quaternion left, Quaternion right );

		virtual System::String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( System::Object^ obj ) override;
		virtual bool Equals( Quaternion other );
		static bool Equals( Quaternion% value1, Quaternion% value2 );
	};
}
