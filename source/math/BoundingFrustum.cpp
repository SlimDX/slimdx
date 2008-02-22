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

#include <d3dx9.h>

#include "BoundingFrustum.h"

#include "BoundingBox.h"
#include "BoundingSphere.h"
#include "Ray.h"

using namespace System;
using namespace System::Globalization;

namespace SlimDX
{
	BoundingFrustum::BoundingFrustum( Matrix matrix )
	{
		FrustumMatrix = matrix;
	}

	void BoundingFrustum::FrustumMatrix::set( Matrix value )
	{
		frustumMatrix = value;
		
		corners = gcnew array<Vector3>( 8 );
		planes = gcnew array<Plane>( 6 );

		planes[2].Normal.X = -value.M14 - value.M11;
		planes[2].Normal.Y = -value.M24 - value.M21;
		planes[2].Normal.Z = -value.M34 - value.M31;
		planes[2].D = -value.M44 - value.M41;

		planes[3].Normal.X = -value.M14 + value.M11;
		planes[3].Normal.Y = -value.M24 + value.M21;
		planes[3].Normal.Z = -value.M34 + value.M31;
		planes[3].D = -value.M44 + value.M41;

		planes[4].Normal.X = -value.M14 + value.M12;
		planes[4].Normal.Y = -value.M24 + value.M22;
		planes[4].Normal.Z = -value.M34 + value.M32;
		planes[4].D = -value.M44 + value.M42;

		planes[5].Normal.X = -value.M14 - value.M12;
		planes[5].Normal.Y = -value.M24 - value.M22;
		planes[5].Normal.Z = -value.M34 - value.M32;
		planes[5].D = -value.M44 - value.M42;

		planes[0].Normal.X = -value.M13;
		planes[0].Normal.Y = -value.M23;
		planes[0].Normal.Z = -value.M33;
		planes[0].D = -value.M43;

		planes[1].Normal.X = -value.M14 + value.M13;
		planes[1].Normal.Y = -value.M24 + value.M23;
		planes[1].Normal.Z = -value.M34 + value.M33;
		planes[1].D = -value.M44 + value.M43;

		for( int i = 0; i < 6; i++ )
		{
			float length = planes[i].Normal.Length();
			planes[i].Normal /= length;
			planes[i].D /= length;
		}

		Ray ray = ComputeIntersectionLine( Near, Left );
		corners[0] = ComputeIntersection( Top, ray );
		corners[3] = ComputeIntersection( Bottom, ray );

		ray = ComputeIntersectionLine( Right, Near );
		corners[1] = ComputeIntersection( Top, ray );
		corners[2] = ComputeIntersection( Bottom, ray );

		ray = ComputeIntersectionLine( Left, Far );
		corners[4] = ComputeIntersection( Top, ray );
		corners[7] = ComputeIntersection( Bottom, ray );

		ray = ComputeIntersectionLine( Far, Right );
		corners[5] = ComputeIntersection( Top, ray );
		corners[6] = ComputeIntersection( Bottom, ray );
	}

	Ray BoundingFrustum::ComputeIntersectionLine( Plane% plane1, Plane% plane2 )
	{
		Ray ray;
		ray.Direction = Vector3::Cross( plane1.Normal, plane2.Normal );
		float length = ray.Direction.LengthSquared();
		ray.Position = Vector3::Cross( (-plane1.D * plane2.Normal) + (plane2.D * plane1.Normal), ray.Direction ) / length;
		return ray;
	}

	Vector3 BoundingFrustum::ComputeIntersection( Plane% plane, Ray% ray )
	{
		float dot = (-plane.D - Vector3::Dot( plane.Normal, ray.Position )) / Vector3::Dot( plane.Normal, ray.Direction );
		return ray.Position + (ray.Direction * dot);
	}

	array<Vector3>^ BoundingFrustum::GetCorners()
	{
		return corners;
	}

	array<Plane>^ BoundingFrustum::GetPlanes()
	{
		return planes;
	}

	ContainmentType BoundingFrustum::Contains( BoundingFrustum frustum, BoundingBox box )
	{
		bool flag = false;
		array<Plane>^ planes = frustum.GetPlanes();

		for each( Plane plane in planes )
		{
			switch( BoundingBox::Intersects( box, plane ) )
			{
				case PlaneIntersectionType::Front:
					return ContainmentType::Disjoint;

				case PlaneIntersectionType::Intersecting:
					flag = true;
					break;
			}
		}

		if( !flag )
			return ContainmentType::Contains;

		return ContainmentType::Intersects;
	}

	ContainmentType BoundingFrustum::Contains( BoundingFrustum frustum, BoundingSphere sphere )
	{
		Vector3 center = sphere.Center;
		float radius = sphere.Radius;
		int intersections = 0;

		array<Plane>^ planes = frustum.GetPlanes();

		for each( Plane plane in planes )
		{
			float dot = (plane.Normal.X * center.X) + (plane.Normal.Y * center.Y) + (plane.Normal.Z * center.Z);
			float dotD = dot + plane.D;

			if( dotD > radius )
				return ContainmentType::Disjoint;

			if( dotD < -radius )
				intersections++;
		}

		if( intersections != 6 )
			return ContainmentType::Intersects;

		return ContainmentType::Contains;
	}

	ContainmentType BoundingFrustum::Contains( BoundingFrustum frustum, Vector3 vector )
	{
		array<Plane>^ planes = frustum.GetPlanes();

		for each( Plane plane in planes )
		{
			float dot = (plane.Normal.X * vector.X) + (plane.Normal.Y * vector.Y) + (plane.Normal.Z * vector.Z) + plane.D;
			
			if( dot > 0.000001f )
				return ContainmentType::Disjoint;
		}

		return ContainmentType::Contains;
	}

	bool BoundingFrustum::Intersects( BoundingFrustum frustum, BoundingBox box )
	{
		return BoundingBox::Intersects( box, frustum );
	}

	bool BoundingFrustum::Intersects( BoundingFrustum frustum, BoundingSphere sphere )
	{
		return Contains( frustum, sphere ) == ContainmentType::Intersects;
	}

	bool BoundingFrustum::Intersects( BoundingFrustum frustum, Ray ray, [Out] float% distance )
	{
		return Ray::Intersects( ray, frustum, distance );
	}

	PlaneIntersectionType BoundingFrustum::Intersects( BoundingFrustum frustum, Plane plane )
	{
		return Plane::Intersects( plane, frustum );
	}

	bool BoundingFrustum::operator == ( BoundingFrustum left, BoundingFrustum right )
	{
		return BoundingFrustum::Equals( left, right );
	}

	bool BoundingFrustum::operator != ( BoundingFrustum left, BoundingFrustum right )
	{
		return !BoundingFrustum::Equals( left, right );
	}

	String^ BoundingFrustum::ToString()
	{
		return String::Format( CultureInfo::CurrentCulture, "Near:{0} Far:{1} Top:{2} Bottom:{3} Left:{4} Right:{5}", Near.ToString(),
			Far.ToString(), Top.ToString(), Bottom.ToString(), Left.ToString(), Right.ToString() );
	}

	int BoundingFrustum::GetHashCode()
	{
		return FrustumMatrix.GetHashCode();
	}

	bool BoundingFrustum::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<BoundingFrustum>( value ) );
	}

	bool BoundingFrustum::Equals( BoundingFrustum value )
	{
		return ( FrustumMatrix == value.FrustumMatrix );
	}

	bool BoundingFrustum::Equals( BoundingFrustum% value1, BoundingFrustum% value2 )
	{
		return ( value1.FrustumMatrix == value2.FrustumMatrix );
	}
}
