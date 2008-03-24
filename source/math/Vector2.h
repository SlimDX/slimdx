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

#include "Vector4.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	value class Quaternion;
	value class Matrix;
	value class Vector3;
    value class Viewport;

	/// <summary>
	/// Defines a two component vector.
	/// </summary>
	[System::Serializable]
	[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
	public value class Vector2 : System::IEquatable<Vector2>
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
		/// Gets a <see cref="SlimDX::Vector2"/> with all of its components set to zero.
		/// </summary>
		/// <value>A <see cref="SlimDX::Vector2"/> that has all of its components set to zero.</value>
		static property Vector2 Zero { Vector2 get() { return Vector2(0, 0); } }

		/// <summary>
		/// Gets the X unit <see cref="SlimDX::Vector2"/> (1, 0).
		/// </summary>
		/// <value>A <see cref="SlimDX::Vector2"/> that has a value of (1, 0).</value>
		static property Vector2 UnitX { Vector2 get() { return Vector2(1, 0); } }

		/// <summary>
		/// Gets the Y unit <see cref="SlimDX::Vector2"/> (0, 1).
		/// </summary>
		/// <value>A <see cref="SlimDX::Vector2"/> that has a value of (0, 1).</value>
		static property Vector2 UnitY { Vector2 get() { return Vector2(0, 1); } }

		Vector2( float value );		
		Vector2( float x, float y );	

		float Length();		
		float LengthSquared();		
		void Normalize();
		
		static Vector2 Add( Vector2 left, Vector2 right );
		static void Add( Vector2% left, Vector2% right, [Out] Vector2% result );
		
		static Vector2 Subtract( Vector2 left, Vector2 right );		
		static void Subtract( Vector2% left, Vector2% right, [Out] Vector2% result );
		
		static Vector2 Multiply( Vector2 value, float scale );		
		static void Multiply( Vector2% vector, float scale, [Out] Vector2% result );
		
		static Vector2 Modulate( Vector2 left, Vector2 right );		
		static void Modulate( Vector2% left, Vector2% right, [Out] Vector2% result );
		
		static Vector2 Divide( Vector2 value, float scale );		
		static void Divide( Vector2% vector, float scale, [Out] Vector2% result );
		
		static Vector2 Negate( Vector2 value );		
		static void Negate( Vector2% value, [Out] Vector2% result );
		
		static Vector2 Barycentric( Vector2 value1, Vector2 value2, Vector2 value3, float amount1, float amount2 );		
		static void Barycentric( Vector2% value1, Vector2% value2, Vector2% value3, float amount1, float amount2, [Out] Vector2% result );
		
		static Vector2 CatmullRom( Vector2 value1, Vector2 value2, Vector2 value3, Vector2 value4, float amount );		
		static void CatmullRom( Vector2% value1, Vector2% value2, Vector2% value3, Vector2% value4, float amount, [Out] Vector2% result );
		
		static Vector2 Clamp( Vector2 value, Vector2 min, Vector2 max );		
		static void Clamp( Vector2% value, Vector2% min, Vector2% max, [Out] Vector2% result );		
		
		static Vector2 Hermite( Vector2 value1, Vector2 tangent1, Vector2 value2, Vector2 tangent2, float amount );	
		static void Hermite( Vector2% value1, Vector2% tangent1, Vector2% value2, Vector2% tangent2, float amount, [Out] Vector2% result );
		
		static Vector2 Lerp( Vector2 start, Vector2 end, float amount );		
		static void Lerp( Vector2% start, Vector2% end, float amount, [Out] Vector2% result );		
		
		static Vector2 SmoothStep( Vector2 start, Vector2 end, float amount );		
		static void SmoothStep( Vector2% start, Vector2% end, float amount, [Out] Vector2% result );
		
		static float Distance( Vector2 value1, Vector2 value2 );
		static float DistanceSquared( Vector2 value1, Vector2 value2 );
		static float Dot( Vector2 left, Vector2 right );

		static Vector2 Normalize( Vector2 vector );
		static void Normalize( Vector2% vector, [Out] Vector2% result );

		static Vector4 Transform( Vector2 vector, Matrix transformation );
		static void Transform( Vector2% vector, Matrix% transformation, [Out] Vector4% result );
		static array<Vector4>^ Transform( array<Vector2>^ vectors, Matrix% transformation );

		static Vector4 Transform( Vector2 vector, Quaternion rotation );
		static void Transform( Vector2% vector, Quaternion% rotation, [Out] Vector4% result );
		static array<Vector4>^ Transform( array<Vector2>^ vectors, Quaternion% rotation );

		static Vector2 TransformCoordinate( Vector2 coordinate, Matrix transformation );
		static void TransformCoordinate( Vector2% coordinate, Matrix% transformation, [Out] Vector2% result );
		static array<Vector2>^ TransformCoordinate( array<Vector2>^ coordinates, Matrix% transformation );
		
		static Vector2 TransformNormal( Vector2 normal, Matrix transformation );
		static void TransformNormal( Vector2% normal, Matrix% transformation, [Out] Vector2% result );
		static array<Vector2>^ TransformNormal( array<Vector2>^ normals, Matrix% transformation );

		static Vector2 Minimize( Vector2 value1, Vector2 value2 );
		static void Minimize( Vector2% value1, Vector2% value2, [Out] Vector2% result );
		
		static Vector2 Maximize( Vector2 value1, Vector2 value2 );
		static void Maximize( Vector2% value1, Vector2% value2, [Out] Vector2% result );

		static Vector2 operator + ( Vector2 left, Vector2 right );
		static Vector2 operator - ( Vector2 left, Vector2 right );
		static Vector2 operator - ( Vector2 value );
		static Vector2 operator * ( Vector2 vector, float scale );
		static Vector2 operator * ( float scale, Vector2 vector );
		static Vector2 operator / ( Vector2 vector, float scale );

		static bool operator == ( Vector2 left, Vector2 right );
		static bool operator != ( Vector2 left, Vector2 right );

		virtual System::String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( System::Object^ obj ) override;
		virtual bool Equals( Vector2 other );
		static bool Equals( Vector2% value1, Vector2% value2 );
	};
}
