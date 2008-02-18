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
#include <windows.h>
#include <d3dx9.h>

#include "Math.h"

using namespace System;
using namespace System::Globalization;

namespace SlimDX
{
	/// <summary>
	/// Initializes a new instance of the <see cref="SlimDX::Plane"/> class.
	/// </summary>
	/// <param name="a">X component of the normal defining the plane.</param>
	/// <param name="b">Y component of the normal defining the plane.</param>
	/// <param name="c">Z component of the normal defining the plane.</param>
	/// <param name="d">Distance of the plane along its normal from the origin.</param>
	Plane::Plane( float a, float b, float c, float d )
	{
		Normal = Vector3( a, b, c );
		D = d;
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="SlimDX::Plane"/> class.
	/// </summary>
	/// <param name="normal">The normal vector to the plane.</param>
	/// <param name="d">Distance of the plane along its normal from the origin.</param>
	Plane::Plane( Vector3 normal, float d )
	{
		Normal = normal;
		D = d;
	}

	Plane::Plane( Vector3 point, Vector3 normal )
	{
		Normal = normal;
		D = -Vector3::Dot( normal, point );
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="SlimDX::Plane"/> class.
	/// </summary>
	/// <param name="point1">First point of a triangle defining the plane.</param>
	/// <param name="point2">Second point of a triangle defining the plane.</param>
	/// <param name="point3">Third point of a triangle defining the plane.</param>
	Plane::Plane( Vector3 point1, Vector3 point2, Vector3 point3 )
	{
		float x1 = point2.X - point1.X;
		float y1 = point2.Y - point1.Y;
		float z1 = point2.Z - point1.Z;
		float x2 = point3.X - point1.X;
		float y2 = point3.Y - point1.Y;
		float z2 = point3.Z - point1.Z;
		float yz = (y1 * z2) - (z1 * y2);
		float xz = (z1 * x2) - (x1 * z2);
		float xy = (x1 * y2) - (y1 * x2);
		float invPyth = 1.0f / static_cast<float>( Math::Sqrt((yz * yz) + (xz * xz) + (xy * xy)) );

		Normal.X = yz * invPyth;
		Normal.Y = xz * invPyth;
		Normal.Z = xy * invPyth;
		D = -((Normal.X * point1.X) + (Normal.Y * point1.Y) + (Normal.Z * point1.Z));
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="SlimDX::Plane"/> class.
	/// </summary>
	/// <param name="value">
	/// A vector with the X, Y, and Z components defining the normal to the plane.
	/// The W component defines the distance of the plane along its normal from the origin.
	/// </param>
	Plane::Plane( Vector4 value )
	{
		Normal = Vector3( value.X, value.Y, value.Z );
		D = value.W;
	}

	/// <summary>
	/// Calculates the dot product of the specified vector and plane.
	/// </summary>
	/// <param name="plane">The source plane.</param>
	/// <param name="point">The source vector.</param>
	/// <returns>The dot product of the specified vector and plane.</returns>
	float Plane::Dot( Plane plane, Vector4 point )
	{
		return (plane.Normal.X * point.X) + (plane.Normal.Y * point.Y) + (plane.Normal.Z * point.Z) + (plane.D * point.W);
	}

	/// <summary>
	/// Calculates the dot product of a specified vector and the normal of the plane plus the distance value of the plane.
	/// </summary>
	/// <param name="plane">The source plane.</param>
	/// <param name="point">The source vector.</param>
	/// <returns>The dot product of a specified vector and the normal of the Plane plus the distance value of the plane.</returns>
	float Plane::DotCoordinate( Plane plane, Vector3 point )
	{
		return (plane.Normal.X * point.X) + (plane.Normal.Y * point.Y) + (plane.Normal.Z * point.Z) + plane.D;
	}

	/// <summary>
	/// Calculates the dot product of the specified vector and the normal of the plane.
	/// </summary>
	/// <param name="plane">The source plane.</param>
	/// <param name="point">The source vector.</param>
	/// <returns>The dot product of the specified vector and the normal of the plane.</returns>
	float Plane::DotNormal( Plane plane, Vector3 point )
	{
		return (plane.Normal.X * point.X) + (plane.Normal.Y * point.Y) + (plane.Normal.Z * point.Z);
	}

	/// <summary>
	/// Changes the coefficients of the normal vector of the plane to make it of unit length.
	/// </summary>
	void Plane::Normalize()
	{
		float magnitude = 1.0f / static_cast<float>( Math::Sqrt( (Normal.X * Normal.X) + (Normal.Y * Normal.Y) + (Normal.Z * Normal.Z) ) );

		Normal.X *= magnitude;
		Normal.Y *= magnitude;
		Normal.Z *= magnitude;
		D *= magnitude;
	}

	/// <summary>
	/// Changes the coefficients of the normal vector of the plane to make it of unit length.
	/// </summary>
	/// <param name="plane">The source plane.</param>
	/// <returns>The normalized plane.</returns>
	Plane Plane::Normalize( Plane plane )
	{
		float magnitude = 1.0f / static_cast<float>( Math::Sqrt( (plane.Normal.X * plane.Normal.X) + (plane.Normal.Y * plane.Normal.Y) + (plane.Normal.Z * plane.Normal.Z) ) );

		return Plane( plane.Normal.X * magnitude, plane.Normal.Y * magnitude, plane.Normal.Z * magnitude, plane.D * magnitude );
	}

	/// <summary>
	/// Changes the coefficients of the normal vector of the plane to make it of unit length.
	/// </summary>
	/// <param name="plane">The source plane.</param>
	/// <param name="result">When the method completes, contains the normalized plane.</param>
	void Plane::Normalize( Plane% plane, [Out] Plane% result )
	{
		float magnitude = 1.0f / static_cast<float>( Math::Sqrt( (plane.Normal.X * plane.Normal.X) + (plane.Normal.Y * plane.Normal.Y) + (plane.Normal.Z * plane.Normal.Z) ) );

		result = Plane( plane.Normal.X * magnitude, plane.Normal.Y * magnitude, plane.Normal.Z * magnitude, plane.D * magnitude );
	}

	/// <summary>
	/// Transforms a normalized plane by a matrix.
	/// </summary>
	/// <param name="plane">The normalized source plane.</param>
	/// <param name="transformation">The transformation matrix.</param>
	/// <returns>The transformed plane.</returns>
	Plane Plane::Transform( Plane plane, Matrix transformation )
	{
		Plane result;
		float x = plane.Normal.X;
		float y = plane.Normal.Y;
		float z = plane.Normal.Z;
		float d = plane.D;

		transformation.Invert();
		result.Normal.X = (((x * transformation.M11) + (y * transformation.M12)) + (z * transformation.M13)) + (d * transformation.M14);
		result.Normal.Y = (((x * transformation.M21) + (y * transformation.M22)) + (z * transformation.M23)) + (d * transformation.M24);
		result.Normal.Z = (((x * transformation.M31) + (y * transformation.M32)) + (z * transformation.M33)) + (d * transformation.M34);
		result.D		= (((x * transformation.M41) + (y * transformation.M42)) + (z * transformation.M43)) + (d * transformation.M44);

		return result;
	}

	/// <summary>
	/// Transforms a normalized plane by a matrix.
	/// </summary>
	/// <param name="plane">The normalized source plane.</param>
	/// <param name="transformation">The transformation matrix.</param>
	/// <param name="result">When the method completes, contains the transformed plane.</param>
	void Plane::Transform( Plane% plane, Matrix% temp, [Out] Plane% result )
	{
		float x = plane.Normal.X;
		float y = plane.Normal.Y;
		float z = plane.Normal.Z;
		float d = plane.D;

		Matrix transformation = Matrix::Invert( temp );

		Plane r;
		r.Normal.X = (((x * transformation.M11) + (y * transformation.M12)) + (z * transformation.M13)) + (d * transformation.M14);
		r.Normal.Y = (((x * transformation.M21) + (y * transformation.M22)) + (z * transformation.M23)) + (d * transformation.M24);
		r.Normal.Z = (((x * transformation.M31) + (y * transformation.M32)) + (z * transformation.M33)) + (d * transformation.M34);
		r.D		= (((x * transformation.M41) + (y * transformation.M42)) + (z * transformation.M43)) + (d * transformation.M44);
	
		result = r;
	}

	/// <summary>
	/// Transforms an array of normalized planes by a matrix.
	/// </summary>
	/// <param name="planes">The normalized source planes.</param>
	/// <param name="transformation">The transformation matrix.</param>
	/// <returns>The transformed planes.</returns>
	array<Plane>^ Plane::Transform( array<Plane>^ planes, Matrix% temp )
	{
		if( planes == nullptr )
			throw gcnew ArgumentNullException( "planes" );

		int count = planes->Length;
		array<Plane>^ results = gcnew array<Plane>( count );
		Matrix transformation = Matrix::Invert( temp );

		for( int i = 0; i < count; i++ )
		{
			float x = planes[i].Normal.X;
			float y = planes[i].Normal.Y;
			float z = planes[i].Normal.Z;
			float d = planes[i].D;

			Plane r;
			r.Normal.X = (((x * transformation.M11) + (y * transformation.M12)) + (z * transformation.M13)) + (d * transformation.M14);
			r.Normal.Y = (((x * transformation.M21) + (y * transformation.M22)) + (z * transformation.M23)) + (d * transformation.M24);
			r.Normal.Z = (((x * transformation.M31) + (y * transformation.M32)) + (z * transformation.M33)) + (d * transformation.M34);
			r.D		= (((x * transformation.M41) + (y * transformation.M42)) + (z * transformation.M43)) + (d * transformation.M44);
		
			results[i] = r;
		}

		return results;
	}

	/// <summary>
	/// Transforms a normalized plane by a quaternion rotation.
	/// </summary>
	/// <param name="plane">The normalized source plane.</param>
	/// <param name="rotation">The quaternion rotation.</param>
	/// <returns>The transformed plane.</returns>
	Plane Plane::Transform( Plane plane, Quaternion rotation )
	{
		Plane result;
		float x2 = rotation.X + rotation.X;
		float y2 = rotation.Y + rotation.Y;
		float z2 = rotation.Z + rotation.Z;
		float wx = rotation.W * x2;
		float wy = rotation.W * y2;
		float wz = rotation.W * z2;
		float xx = rotation.X * x2;
		float xy = rotation.X * y2;
		float xz = rotation.X * z2;
		float yy = rotation.Y * y2;
		float yz = rotation.Y * z2;
		float zz = rotation.Z * z2;

		float x = plane.Normal.X;
		float y = plane.Normal.Y;
		float z = plane.Normal.Z;

		result.Normal.X = ((x * ((1.0f - yy) - zz)) + (y * (xy - wz))) + (z * (xz + wy));
		result.Normal.Y = ((x * (xy + wz)) + (y * ((1.0f - xx) - zz))) + (z * (yz - wx));
		result.Normal.Z = ((x * (xz - wy)) + (y * (yz + wx))) + (z * ((1.0f - xx) - yy));
		result.D = plane.D;
		return result;
	}

	/// <summary>
	/// Transforms a normalized plane by a quaternion rotation.
	/// </summary>
	/// <param name="plane">The normalized source plane.</param>
	/// <param name="rotation">The quaternion rotation.</param>
	/// <param name="result">When the method completes, contains the transformed plane.</param>
	void Plane::Transform( Plane% plane, Quaternion% rotation, [Out] Plane% result )
	{
		float x2 = rotation.X + rotation.X;
		float y2 = rotation.Y + rotation.Y;
		float z2 = rotation.Z + rotation.Z;
		float wx = rotation.W * x2;
		float wy = rotation.W * y2;
		float wz = rotation.W * z2;
		float xx = rotation.X * x2;
		float xy = rotation.X * y2;
		float xz = rotation.X * z2;
		float yy = rotation.Y * y2;
		float yz = rotation.Y * z2;
		float zz = rotation.Z * z2;

		float x = plane.Normal.X;
		float y = plane.Normal.Y;
		float z = plane.Normal.Z;

		Plane r;
		r.Normal.X = ((x * ((1.0f - yy) - zz)) + (y * (xy - wz))) + (z * (xz + wy));
		r.Normal.Y = ((x * (xy + wz)) + (y * ((1.0f - xx) - zz))) + (z * (yz - wx));
		r.Normal.Z = ((x * (xz - wy)) + (y * (yz + wx))) + (z * ((1.0f - xx) - yy));
		r.D = plane.D;

		result = r;
	}

	/// <summary>
	/// Transforms an array of normalized planes by a quaternion rotation.
	/// </summary>
	/// <param name="planes">The normalized source planes.</param>
	/// <param name="rotation">The quaternion rotation.</param>
	/// <returns>The transformed planes.</returns>
	array<Plane>^ Plane::Transform( array<Plane>^ planes, Quaternion% rotation )
	{
		if( planes == nullptr )
			throw gcnew ArgumentNullException( "planes" );

		int count = planes->Length;
		array<Plane>^ results = gcnew array<Plane>( count );

		float x2 = rotation.X + rotation.X;
		float y2 = rotation.Y + rotation.Y;
		float z2 = rotation.Z + rotation.Z;
		float wx = rotation.W * x2;
		float wy = rotation.W * y2;
		float wz = rotation.W * z2;
		float xx = rotation.X * x2;
		float xy = rotation.X * y2;
		float xz = rotation.X * z2;
		float yy = rotation.Y * y2;
		float yz = rotation.Y * z2;
		float zz = rotation.Z * z2;

		for( int i = 0; i < count; i++ )
		{
			float x = planes[i].Normal.X;
			float y = planes[i].Normal.Y;
			float z = planes[i].Normal.Z;

			Plane r;
			r.Normal.X = ((x * ((1.0f - yy) - zz)) + (y * (xy - wz))) + (z * (xz + wy));
			r.Normal.Y = ((x * (xy + wz)) + (y * ((1.0f - xx) - zz))) + (z * (yz - wx));
			r.Normal.Z = ((x * (xz - wy)) + (y * (yz + wx))) + (z * ((1.0f - xx) - yy));
			r.D = planes[i].D;

			results[i] = r;
		}

		return results;
	}

	/// <summary>
	/// Finds the intersection between a plane and a line.
	/// </summary>
	/// <param name="plane">The source plane.</param>
	/// <param name="start">The start point of the line.</param>
	/// <param name="end">The end point of the line.</param>
	/// <param name="intersectPoint">If an intersection is found, contains the intersection point between the line and the plane.</param>
	/// <returns><c>true</c> if an intersection is found; <c>false</c> otherwise.</returns>
	bool Plane::Intersects( Plane plane, Vector3 start, Vector3 end, [Out] Vector3% intersectPoint )
	{
		D3DXVECTOR3 nativePoint;
		D3DXVECTOR3* result = D3DXPlaneIntersectLine( &nativePoint, reinterpret_cast<D3DXPLANE*>( &plane ), reinterpret_cast<D3DXVECTOR3*>( &start ), reinterpret_cast<D3DXVECTOR3*>( &end ) );
		if( result == NULL )
		{
			intersectPoint = Vector3( 0, 0, 0 );
			return false;
		}

		intersectPoint = Vector3( nativePoint.x, nativePoint.y, nativePoint.z );
		return true;
	}

	PlaneIntersectionType Plane::Intersects( Plane plane, BoundingBox box )
	{
		Vector3 min;
		Vector3 max;
		max.X = (plane.Normal.X >= 0.0f) ? box.Minimum.X : box.Maximum.X;
		max.Y = (plane.Normal.Y >= 0.0f) ? box.Minimum.Y : box.Maximum.Y;
		max.Z = (plane.Normal.Z >= 0.0f) ? box.Minimum.Z : box.Maximum.Z;
		min.X = (plane.Normal.X >= 0.0f) ? box.Maximum.X : box.Minimum.X;
		min.Y = (plane.Normal.Y >= 0.0f) ? box.Maximum.Y : box.Minimum.Y;
		min.Z = (plane.Normal.Z >= 0.0f) ? box.Maximum.Z : box.Minimum.Z;

		float dot = (plane.Normal.X * max.X) + (plane.Normal.Y * max.Y) + (plane.Normal.Z * max.Z);

		if( dot + plane.D > 0.0f )
			return PlaneIntersectionType::Front;

		dot = (plane.Normal.X * min.X) + (plane.Normal.Y * min.Y) + (plane.Normal.Z * min.Z);

		if ( dot + plane.D < 0.0f)
			return PlaneIntersectionType::Back;

		return PlaneIntersectionType::Intersecting;
	}

	PlaneIntersectionType Plane::Intersects( Plane plane, BoundingSphere sphere )
	{
		float dot = (sphere.Center.X * plane.Normal.X) + (sphere.Center.Y * plane.Normal.Y) + (sphere.Center.Z * plane.Normal.Z) + plane.D;
		
		if( dot > sphere.Radius )
			return PlaneIntersectionType::Front;

		if( dot < -sphere.Radius )
			return PlaneIntersectionType::Back;

		return PlaneIntersectionType::Intersecting;
	}

	PlaneIntersectionType Plane::Intersects( Plane plane, BoundingFrustum frustum )
	{
		int location = 0;
		array<Vector3>^ corners = frustum.GetCorners();

		for (int i = 0; i < 8; i++)
		{
			float dot = (corners[i].X * plane.Normal.X) + (corners[i].Y * plane.Normal.Y) + (corners[i].Z * plane.Normal.Z);

			if( ( dot + plane.D ) > 0.0f )
				location |= 1;
			else
				location |= 2;

			if( location == 3 )
				return PlaneIntersectionType::Intersecting;
		}

		if( location != 1 )
			return PlaneIntersectionType::Back;

		return PlaneIntersectionType::Front;
	}

	/// <summary>
	/// Scales the plane by the given scaling factor.
	/// </summary>
	/// <param name="plane">The source plane.</param>
	/// <param name="scale">The scaling factor.</param>
	/// <returns>The scaled plane.</returns>
	Plane Plane::operator * ( Plane plane, float scale )
	{
		Plane result;
		D3DXPlaneScale( reinterpret_cast<D3DXPLANE*>( &result ), reinterpret_cast<D3DXPLANE*>( &plane ), scale );
		return result;
	}

	/// <summary>
	/// Scales the plane by the given scaling factor.
	/// </summary>
	/// <param name="plane">The source plane.</param>
	/// <param name="scale">The scaling factor.</param>
	/// <returns>The scaled plane.</returns>
	Plane Plane::operator * ( float scale, Plane plane )
	{
		return plane * scale;
	}

	/// <summary>
	/// Tests planes for equality. 
	/// </summary>
	/// <param name="left">The first source plane.</param>
	/// <param name="right">The second source plane.</param>
	/// <returns><c>true</c> if the planes are equal; <c>false</c> otherwise.</returns>
	bool Plane::operator == ( Plane left, Plane right )
	{
		return Plane::Equals( left, right );
	}

	/// <summary>
	/// Tests planes for inequality. 
	/// </summary>
	/// <param name="left">The first source plane.</param>
	/// <param name="right">The second source plane.</param>
	/// <returns><c>true</c> if the planes are not equal; <c>false</c> otherwise.</returns>
	bool Plane::operator != ( Plane left, Plane right )
	{
		return !Plane::Equals( left, right );
	}

	/// <summary>
	/// Retrieves a string representation of the current object. 
	/// </summary>
	/// <returns>A string that represents the object.</returns>
	String^ Plane::ToString()
	{
		return String::Format( CultureInfo::CurrentCulture, "Normal:{0} D:{1}", Normal.ToString(), D.ToString(CultureInfo::CurrentCulture) );
	}

	/// <summary>
	/// Gets the hash code of the plane object. 
	/// </summary>
	/// <returns>Hash code of the plane object.</returns>
	int Plane::GetHashCode()
	{
		return Normal.GetHashCode() + D.GetHashCode();
	}

	/// <summary>
	/// Returns a value that indicates whether the current instance is equal to a specified object. 
	/// </summary>
	/// <param name="obj">Object to make the comparison with.</param>
	/// <returns><c>true</c> if the current instance is equal to the specified object; <c>false</c> otherwise.</returns>
	bool Plane::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<Plane>( value ) );
	}

	/// <summary>
	/// Returns a value that indicates whether the current instance is equal to the specified object. 
	/// </summary>
	/// <param name="other">Object to make the comparison with.</param>
	/// <returns><c>true</c> if the current instance is equal to the specified object; <c>false</c> otherwise.</returns>
	bool Plane::Equals( Plane value )
	{
		return ( Normal == value.Normal && D == value.D );
	}

	/// <summary>
	/// Determines whether the specified Object instances are considered equal. 
	/// </summary>
	/// <param name="value1"></param>
	/// <param name="value2"></param>
	/// <returns><c>true</c> if <paramref name="value1"/> is the same instance as <paramref name="value2"/> or 
	/// if both are <c>null</c> references or if <c>objA.Equals(objB)</c> returns <c>true</c>; otherwise, <c>false</c>.</returns>
	bool Plane::Equals( Plane% value1, Plane% value2 )
	{
		return ( value1.Normal == value2.Normal && value1.D == value2.D );
	}
}
