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
	/// <summary>
	/// Defines a 3D mathematical plane.
	/// </summary>
	[Serializable]
	[StructLayout( LayoutKind::Sequential )]
	public value class Plane : IEquatable<Plane>
	{
	public:
		/// <summary>
		/// Gets or sets the normal vector of the plane.
		/// </summary>
		/// <value>The normal vector of the plane.</value>
		property Vector3 Normal;

		/// <summary>
		/// Gets or sets the distance of the plane along its normal from the origin.
		/// </summary>
		/// <value>The distance of the plane along its normal from the origin.</value>
		property float D;

		Plane( float a, float b, float c, float d );
		Plane( Vector3 normal, float d );
		Plane( Vector3 point1, Vector3 point2, Vector3 point3 );
		Plane( Vector4 value );

		static float Dot( Plane plane, Vector4 point );
		static float Dot( Plane% plane, Vector4% point );

		static float DotCoordinate( Plane plane, Vector3 point );
		static float DotCoordinate( Plane% plane, Vector3% point );

		static float DotNormal( Plane plane, Vector3 point );
		static float DotNormal( Plane% plane, Vector3% point );

		void Normalize();

		static Plane Normalize( Plane plane );
		static void Normalize( Plane% plane, [Out] Plane% result );

		static Plane Transform( Plane plane, Matrix transformation );
		static void Transform( Plane% plane, Matrix% transformation, [Out] Plane% result );
		static array<Plane>^ Transform( array<Plane>^ planes, Matrix% transformation );

		static Plane Transform( Plane plane, Quaternion rotation );
		static void Transform( Plane% plane, Quaternion% rotation, [Out] Plane% result );
		static array<Plane>^ Transform( array<Plane>^ planes, Quaternion% rotation );

		static bool Intersects( Plane plane, Vector3 start, Vector3 end, [Out] Vector3% intersectPoint );
		static bool Intersects( Plane% plane, Vector3% start, Vector3% end, [Out] Vector3% intersectPoint );

		static Plane operator * ( Plane plane, float scale );
		static Plane operator * ( float scale, Plane plane );

		static bool operator == ( Plane left, Plane right );
		static bool operator != ( Plane left, Plane right );

		virtual String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( Object^ obj ) override;
		virtual bool Equals( Plane other );
		static bool Equals( Plane% value1, Plane% value2 );
	};
}
