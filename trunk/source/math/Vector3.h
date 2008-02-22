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
	namespace Direct3D
	{
		value class Viewport;
	}
	
	value class Matrix;
	value class Vector2;
	
	/// <summary>
	/// Defines a vector with three components.
	/// </summary>
	[System::Serializable]
	[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
	public value class Vector3 : System::IEquatable<Vector3>
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
		/// Gets a <see cref="SlimDX::Vector3"/> with all of its components set to zero.
		/// </summary>
		/// <value>A <see cref="SlimDX::Vector3"/> that has all of its components set to zero.</value>
		static property Vector3 Zero { Vector3 get() { return Vector3(0, 0, 0); } }

		/// <summary>
		/// Gets the X unit <see cref="SlimDX::Vector3"/> (1, 0, 0).
		/// </summary>
		/// <value>A <see cref="SlimDX::Vector3"/> that has a value of (1, 0, 0).</value>
		static property Vector3 UnitX { Vector3 get() { return Vector3(1, 0, 0); } }

		/// <summary>
		/// Gets the Y unit <see cref="SlimDX::Vector3"/> (0, 1, 0).
		/// </summary>
		/// <value>A <see cref="SlimDX::Vector3"/> that has a value of (0, 1, 0).</value>
		static property Vector3 UnitY { Vector3 get() { return Vector3(0, 1, 0); } }

		/// <summary>
		/// Gets the Z unit <see cref="SlimDX::Vector3"/> (0, 0, 1).
		/// </summary>
		/// <value>A <see cref="SlimDX::Vector3"/> that has a value of (0, 0, 1).</value>
		static property Vector3 UnitZ { Vector3 get() { return Vector3(0, 0, 1); } }

		Vector3( float value );		
		Vector3( Vector2 value, float z );		
		Vector3( float x, float y, float z );	

		float Length();		
		float LengthSquared();		
		void Normalize();
		
		static Vector3 Add( Vector3 left, Vector3 right );
		static void Add( Vector3% left, Vector3% right, [Out] Vector3% result );
		
		static Vector3 Subtract( Vector3 left, Vector3 right );		
		static void Subtract( Vector3% left, Vector3% right, [Out] Vector3% result );
		
		static Vector3 Multiply( Vector3 value, float scale );		
		static void Multiply( Vector3% vector, float scale, [Out] Vector3% result );
		
		static Vector3 Modulate( Vector3 left, Vector3 right );		
		static void Modulate( Vector3% left, Vector3% right, [Out] Vector3% result );
		
		static Vector3 Divide( Vector3 value, float scale );		
		static void Divide( Vector3% vector, float scale, [Out] Vector3% result );
		
		static Vector3 Negate( Vector3 value );		
		static void Negate( Vector3% value, [Out] Vector3% result );
		
		static Vector3 Barycentric( Vector3 value1, Vector3 value2, Vector3 value3, float amount1, float amount2 );		
		static void Barycentric( Vector3% value1, Vector3% value2, Vector3% value3, float amount1, float amount2, [Out] Vector3% result );
		
		static Vector3 CatmullRom( Vector3 value1, Vector3 value2, Vector3 value3, Vector3 value4, float amount );		
		static void CatmullRom( Vector3% value1, Vector3% value2, Vector3% value3, Vector3% value4, float amount, [Out] Vector3% result );
		
		static Vector3 Clamp( Vector3 value, Vector3 min, Vector3 max );		
		static void Clamp( Vector3% value, Vector3% min, Vector3% max, [Out] Vector3% result );		
		
		static Vector3 Hermite( Vector3 value1, Vector3 tangent1, Vector3 value2, Vector3 tangent2, float amount );	
		static void Hermite( Vector3% value1, Vector3% tangent1, Vector3% value2, Vector3% tangent2, float amount, [Out] Vector3% result );
		
		static Vector3 Lerp( Vector3 start, Vector3 end, float amount );		
		static void Lerp( Vector3% start, Vector3% end, float amount, [Out] Vector3% result );		
		
		static Vector3 SmoothStep( Vector3 start, Vector3 end, float amount );		
		static void SmoothStep( Vector3% start, Vector3% end, float amount, [Out] Vector3% result );
		
		static float Distance( Vector3 value1, Vector3 value2 );
		static float DistanceSquared( Vector3 value1, Vector3 value2 );
		static float Dot( Vector3 left, Vector3 right );
		
		static Vector3 Cross( Vector3 left, Vector3 right );		
		static void Cross( Vector3% left, Vector3% right, [Out] Vector3% result );

		static Vector3 Reflect( Vector3 vector, Vector3 normal );
		static void Reflect( Vector3% vector, Vector3% normal, [Out] Vector3% result );

		static Vector3 Normalize( Vector3 vector );
		static void Normalize( Vector3% vector, [Out] Vector3% result );

		static Vector4 Transform( Vector3 vector, Matrix transformation );
		static void Transform( Vector3% vector, Matrix% transformation, [Out] Vector4% result );
		static array<Vector4>^ Transform( array<Vector3>^ vectors, Matrix% transformation );

		static Vector4 Transform( Vector3 vector, Quaternion rotation );
		static void Transform( Vector3% vector, Quaternion% rotation, [Out] Vector4% result );
		static array<Vector4>^ Transform( array<Vector3>^ vectors, Quaternion% rotation );

		static Vector3 TransformCoordinate( Vector3 coordinate, Matrix transformation );
		static void TransformCoordinate( Vector3% coordinate, Matrix% transformation, [Out] Vector3% result );
		static array<Vector3>^ TransformCoordinate( array<Vector3>^ coordinates, Matrix% transformation );
		
		static Vector3 TransformNormal( Vector3 normal, Matrix transformation );
		static void TransformNormal( Vector3% normal, Matrix% transformation, [Out] Vector3% result );
		static array<Vector3>^ TransformNormal( array<Vector3>^ normals, Matrix% transformation );

		static Vector3 Project( Vector3 vector, Direct3D::Viewport viewport, Matrix projection, Matrix view, Matrix world );
		static void Project( Vector3% vector, Direct3D::Viewport% viewport, Matrix% projection, Matrix% view, Matrix% world, [Out] Vector3% result );
		
		static Vector3 Unproject( Vector3 vector, Direct3D::Viewport viewport, Matrix projection, Matrix view, Matrix world );
		static void Unproject( Vector3% vector, Direct3D::Viewport% viewport, Matrix% projection, Matrix% view, Matrix% world, [Out] Vector3% result );
		
		static Vector3 Minimize( Vector3 value1, Vector3 value2 );
		static void Minimize( Vector3% value1, Vector3% value2, [Out] Vector3% result );
		
		static Vector3 Maximize( Vector3 value1, Vector3 value2 );
		static void Maximize( Vector3% value1, Vector3% value2, [Out] Vector3% result );

		static Vector3 operator + ( Vector3 left, Vector3 right );
		static Vector3 operator - ( Vector3 left, Vector3 right );
		static Vector3 operator - ( Vector3 value );
		static Vector3 operator * ( Vector3 vector, float scale );
		static Vector3 operator * ( float scale, Vector3 vector );
		static Vector3 operator / ( Vector3 vector, float scale );

		static bool operator == ( Vector3 left, Vector3 right );
		static bool operator != ( Vector3 left, Vector3 right );

		virtual System::String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( System::Object^ obj ) override;
		virtual bool Equals( Vector3 other );
		static bool Equals( Vector3% value1, Vector3% value2 );
	};
}
