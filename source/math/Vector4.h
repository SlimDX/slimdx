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

//using namespace System;
//using namespace System::Globalization;
//using namespace System::Runtime::InteropServices;

namespace SlimDX
{
    namespace Direct3D
    {
        value class Viewport;
		value class Vector4;
    }

	/// <summary>
	/// Defines a vector with four components.
	/// </summary>
	[System::Serializable]
	[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
	public value class Vector4 : System::IEquatable<Vector4>
	{
	public:
		/// <summary>
		/// Gets or sets the X component of the vector.
		/// </summary>
		/// <value>The X component of the vector.</value>
		property float X;

		/// <summary>
		/// Gets or sets the Y component of the vector.
		/// </summary>
		/// <value>The Y component of the vector.</value>
		property float Y;

		/// <summary>
		/// Gets or sets the Z component of the vector.
		/// </summary>
		/// <value>The Z component of the vector.</value>
		property float Z;

		/// <summary>
		/// Gets or sets the W component of the vector.
		/// </summary>
		/// <value>The W component of the vector.</value>
		property float W;

		/// <summary>
		/// Gets a <see cref="SlimDX::Vector4"/> with all of its components set to zero.
		/// </summary>
		/// <value>A <see cref="SlimDX::Vector4"/> that has all of its components set to zero.</value>
		static property Vector4 Zero { Vector4 get() { return Vector4(0, 0, 0, 0); } }

		/// <summary>
		/// Gets the X unit <see cref="SlimDX::Vector4"/> (1, 0, 0, 0).
		/// </summary>
		/// <value>A <see cref="SlimDX::Vector4"/> that has a value of (1, 0, 0, 0).</value>
		static property Vector4 UnitX { Vector4 get() { return Vector4(1, 0, 0, 0); } }

		/// <summary>
		/// Gets the Y unit <see cref="SlimDX::Vector4"/> (0, 1, 0, 0).
		/// </summary>
		/// <value>A <see cref="SlimDX::Vector4"/> that has a value of (0, 1, 0, 0).</value>
		static property Vector4 UnitY { Vector4 get() { return Vector4(0, 1, 0, 0); } }

		/// <summary>
		/// Gets the Z unit <see cref="SlimDX::Vector4"/> (0, 0, 1, 0).
		/// </summary>
		/// <value>A <see cref="SlimDX::Vector4"/> that has a value of (0, 0, 1, 0).</value>
		static property Vector4 UnitZ { Vector4 get() { return Vector4(0, 0, 1, 0); } }

		/// <summary>
		/// Gets the W unit <see cref="SlimDX::Vector4"/> (0, 0, 0, 1).
		/// </summary>
		/// <value>A <see cref="SlimDX::Vector4"/> that has a value of (0, 0, 0, 1).</value>
		static property Vector4 UnitW { Vector4 get() { return Vector4(0, 0, 0, 1); } }

		Vector4( float value );		
		Vector4( Vector2 value, float z, float w );
		Vector4( Vector3 value, float w );
		Vector4( float x, float y, float z, float w );	

		float Length();		
		float LengthSquared();		
		void Normalize();
		
		static Vector4 Add( Vector4 left, Vector4 right );
		static void Add( Vector4% left, Vector4% right, [Out] Vector4% result );
		
		static Vector4 Subtract( Vector4 left, Vector4 right );		
		static void Subtract( Vector4% left, Vector4% right, [Out] Vector4% result );
		
		static Vector4 Multiply( Vector4 value, float scale );		
		static void Multiply( Vector4% vector, float scale, [Out] Vector4% result );
		
		static Vector4 Modulate( Vector4 left, Vector4 right );		
		static void Modulate( Vector4% left, Vector4% right, [Out] Vector4% result );
		
		static Vector4 Divide( Vector4 value, float scale );		
		static void Divide( Vector4% vector, float scale, [Out] Vector4% result );
		
		static Vector4 Negate( Vector4 value );		
		static void Negate( Vector4% value, [Out] Vector4% result );
		
		static Vector4 Barycentric( Vector4 value1, Vector4 value2, Vector4 value3, float amount1, float amount2 );		
		static void Barycentric( Vector4% value1, Vector4% value2, Vector4% value3, float amount1, float amount2, [Out] Vector4% result );
		
		static Vector4 CatmullRom( Vector4 value1, Vector4 value2, Vector4 value3, Vector4 value4, float amount );		
		static void CatmullRom( Vector4% value1, Vector4% value2, Vector4% value3, Vector4% value4, float amount, [Out] Vector4% result );
		
		static Vector4 Clamp( Vector4 value, Vector4 min, Vector4 max );		
		static void Clamp( Vector4% value, Vector4% min, Vector4% max, [Out] Vector4% result );		
		
		static Vector4 Hermite( Vector4 value1, Vector4 tangent1, Vector4 value2, Vector4 tangent2, float amount );	
		static void Hermite( Vector4% value1, Vector4% tangent1, Vector4% value2, Vector4% tangent2, float amount, [Out] Vector4% result );
		
		static Vector4 Lerp( Vector4 start, Vector4 end, float amount );		
		static void Lerp( Vector4% start, Vector4% end, float amount, [Out] Vector4% result );		
		
		static Vector4 SmoothStep( Vector4 start, Vector4 end, float amount );		
		static void SmoothStep( Vector4% start, Vector4% end, float amount, [Out] Vector4% result );
		
		static float Distance( Vector4 value1, Vector4 value2 );
		static float DistanceSquared( Vector4 value1, Vector4 value2 );
		static float Dot( Vector4 left, Vector4 right );

		static Vector4 Normalize( Vector4 vector );
		static void Normalize( Vector4% vector, [Out] Vector4% result );

		static Vector4 Transform( Vector4 vector, Matrix transformation );
		static void Transform( Vector4% vector, Matrix% transformation, [Out] Vector4% result );
		static array<Vector4>^ Transform( array<Vector4>^ vectors, Matrix% transformation );

		static Vector4 Transform( Vector4 vector, Quaternion rotation );
		static void Transform( Vector4% vector, Quaternion% rotation, [Out] Vector4% result );
		static array<Vector4>^ Transform( array<Vector4>^ vectors, Quaternion% rotation );

		static Vector4 Minimize( Vector4 value1, Vector4 value2 );
		static void Minimize( Vector4% value1, Vector4% value2, [Out] Vector4% result );
		
		static Vector4 Maximize( Vector4 value1, Vector4 value2 );
		static void Maximize( Vector4% value1, Vector4% value2, [Out] Vector4% result );

		static Vector4 operator + ( Vector4 left, Vector4 right );
		static Vector4 operator - ( Vector4 left, Vector4 right );
		static Vector4 operator - ( Vector4 value );
		static Vector4 operator * ( Vector4 vector, float scale );
		static Vector4 operator * ( float scale, Vector4 vector );
		static Vector4 operator / ( Vector4 vector, float scale );

		static bool operator == ( Vector4 left, Vector4 right );
		static bool operator != ( Vector4 left, Vector4 right );

		virtual System::String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( System::Object^ obj ) override;
		virtual bool Equals( Vector4 other );
		static bool Equals( Vector4% value1, Vector4% value2 );
	};
}
