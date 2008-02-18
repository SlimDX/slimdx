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
	BoundingBox::BoundingBox( Vector3 minimum, Vector3 maximum )
	{
		Minimum = minimum;
		Maximum = maximum;
	}

	array<Vector3>^ BoundingBox::GetCorners()
	{
		array<Vector3>^ results = gcnew array<Vector3>( 8 );
		results[0] = Vector3(Minimum.X, Maximum.Y, Maximum.Z);
		results[1] = Vector3(Maximum.X, Maximum.Y, Maximum.Z);
		results[2] = Vector3(Maximum.X, Minimum.Y, Maximum.Z);
		results[3] = Vector3(Minimum.X, Minimum.Y, Maximum.Z);
		results[4] = Vector3(Minimum.X, Maximum.Y, Minimum.Z);
		results[5] = Vector3(Maximum.X, Maximum.Y, Minimum.Z);
		results[6] = Vector3(Maximum.X, Minimum.Y, Minimum.Z);
		results[7] = Vector3(Minimum.X, Minimum.Y, Minimum.Z);
		return results;
	}

	ContainmentType BoundingBox::Contains( BoundingBox box1, BoundingBox box2 )
	{
		if( box1.Maximum.X < box2.Minimum.X || box1.Minimum.X > box2.Maximum.X )
			return ContainmentType::Disjoint;

		if( box1.Maximum.Y < box2.Minimum.Y || box1.Minimum.Y > box2.Maximum.Y )
			return ContainmentType::Disjoint;

		if( box1.Maximum.Z < box2.Minimum.Z || box1.Minimum.Z > box2.Maximum.Z )
			return ContainmentType::Disjoint;

		if( box1.Minimum.X <= box2.Minimum.X && box2.Maximum.X <= box1.Maximum.X && box1.Minimum.Y <= box2.Minimum.Y && 
			box2.Maximum.Y <= box1.Maximum.Y && box1.Minimum.Z <= box2.Minimum.Z && box2.Maximum.Z <= box1.Maximum.Z )
			return ContainmentType::Contains;

		return ContainmentType::Intersects;
	}

	ContainmentType BoundingBox::Contains( BoundingBox box, BoundingSphere sphere )
	{
		float dist;
		Vector3 clamped;

		Vector3::Clamp( sphere.Center, box.Minimum, box.Maximum, clamped );

		float x = sphere.Center.X - clamped.X;
		float y = sphere.Center.Y - clamped.Y;
		float z = sphere.Center.Z - clamped.Z;

		dist = (x * x) + (y * y) + (z * z);
		float radius = sphere.Radius;

		if( dist > (radius * radius) )
			return ContainmentType::Disjoint;

		if( box.Minimum.X + radius <= sphere.Center.X && sphere.Center.X <= box.Maximum.X - radius && 
			box.Maximum.X - box.Minimum.X > radius && box.Minimum.Y + radius <= sphere.Center.Y && 
			sphere.Center.Y <= box.Maximum.Y - radius && box.Maximum.Y - box.Minimum.Y > radius && 
			box.Minimum.Z + radius <= sphere.Center.Z && sphere.Center.Z <= box.Maximum.Z - radius &&
			box.Maximum.X - box.Minimum.X > radius )
			return ContainmentType::Contains;

		return ContainmentType::Intersects;
	}

	ContainmentType BoundingBox::Contains( BoundingBox box, BoundingFrustum frustum )
	{
		if( !BoundingFrustum::Intersects( frustum, box ) )
			return ContainmentType::Disjoint;

		array<Vector3>^ corners = frustum.GetCorners();

		for each( Vector3 vector in corners )
		{
			if( BoundingBox::Contains( box, vector ) == ContainmentType::Disjoint )
				return ContainmentType::Intersects;
		}

		return ContainmentType::Contains;
	}

	ContainmentType BoundingBox::Contains( BoundingBox box, Vector3 vector )
	{
		if( box.Minimum.X <= vector.X && vector.X <= box.Maximum.X && box.Minimum.Y <= vector.Y && 
			vector.Y <= box.Maximum.Y && box.Minimum.Z <= vector.Z && vector.Z <= box.Maximum.Z )
			return ContainmentType::Contains;

		return ContainmentType::Disjoint;
	}

	BoundingBox BoundingBox::FromPoints( array<Vector3>^ points )
	{
		if( points == nullptr || points->Length <= 0 )
			throw gcnew ArgumentNullException();

		Vector3 min = Vector3( float::MaxValue );
		Vector3 max = Vector3( float::MinValue );

		for each( Vector3 vector in points )
		{
			Vector3::Minimize( min, vector, min );
			Vector3::Maximize( max, vector, max );
		}

		return BoundingBox( min, max );
	}

	BoundingBox BoundingBox::FromSphere( BoundingSphere sphere )
	{
		BoundingBox box;
		box.Minimum = Vector3( sphere.Center.X - sphere.Radius, sphere.Center.Y - sphere.Radius, sphere.Center.Z - sphere.Radius );
		box.Maximum = Vector3( sphere.Center.X + sphere.Radius, sphere.Center.Y + sphere.Radius, sphere.Center.Z + sphere.Radius );
		return box;
	}

	BoundingBox BoundingBox::Merge( BoundingBox box1, BoundingBox box2 )
	{
		BoundingBox box;
		Vector3::Minimize( box1.Minimum, box2.Minimum, box.Minimum );
		Vector3::Maximize( box1.Maximum, box2.Maximum, box.Maximum );
		return box;
	}

	bool BoundingBox::Intersects( BoundingBox box1, BoundingBox box2 )
	{
		if ( box1.Maximum.X < box2.Minimum.X || box1.Minimum.X > box2.Maximum.X )
			return false;

		if ( box1.Maximum.Y < box2.Minimum.Y || box1.Minimum.Y > box2.Maximum.Y )
			return false;

		return ( box1.Maximum.Z >= box2.Minimum.Z && box1.Minimum.Z <= box2.Maximum.Z );
	}

	bool BoundingBox::Intersects( BoundingBox box, BoundingSphere sphere )
	{
		float dist;
		Vector3 clamped;

		Vector3::Clamp( sphere.Center, box.Minimum, box.Maximum, clamped );

		float x = sphere.Center.X - clamped.X;
		float y = sphere.Center.Y - clamped.Y;
		float z = sphere.Center.Z - clamped.Z;

		dist = (x * x) + (y * y) + (z * z);

		return ( dist <= (sphere.Radius * sphere.Radius) );
	}

	bool BoundingBox::Intersects( BoundingBox box, BoundingFrustum frustum )
	{
		return BoundingBox::Contains( box, frustum ) == ContainmentType::Intersects;
	}

	bool BoundingBox::Intersects( BoundingBox box, Ray ray, [Out] float% distance )
	{
		return Ray::Intersects( ray, box, distance );
	}

	PlaneIntersectionType BoundingBox::Intersects( BoundingBox box, Plane plane )
	{
		return Plane::Intersects( plane, box );
	}

	bool BoundingBox::operator == ( BoundingBox left, BoundingBox right )
	{
		return BoundingBox::Equals( left, right );
	}

	bool BoundingBox::operator != ( BoundingBox left, BoundingBox right )
	{
		return !BoundingBox::Equals( left, right );
	}

	String^ BoundingBox::ToString()
	{
		return String::Format( CultureInfo::CurrentCulture, "Minimum:{0} Maximum:{1}", Minimum.ToString(), Maximum.ToString() );
	}

	int BoundingBox::GetHashCode()
	{
		return Minimum.GetHashCode() + Maximum.GetHashCode();
	}

	bool BoundingBox::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<BoundingBox>( value ) );
	}

	bool BoundingBox::Equals( BoundingBox value )
	{
		return ( Minimum == value.Minimum && Maximum == value.Maximum );
	}

	bool BoundingBox::Equals( BoundingBox% value1, BoundingBox% value2 )
	{
		return ( value1.Minimum == value2.Minimum && value1.Maximum == value2.Maximum );
	}

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

	BoundingSphere::BoundingSphere( Vector3 center, float radius )
	{
		Center = center;
		Radius = radius;
	}

	ContainmentType BoundingSphere::Contains( BoundingSphere sphere, BoundingBox box )
	{
		Vector3 vector;

		if( !BoundingBox::Intersects( box, sphere ) )
			return ContainmentType::Disjoint;

		float radius = sphere.Radius * sphere.Radius;
		vector.X = sphere.Center.X - box.Minimum.X;
		vector.Y = sphere.Center.Y - box.Maximum.Y;
		vector.Z = sphere.Center.Z - box.Maximum.Z;

		if( vector.LengthSquared() > radius )
			return ContainmentType::Intersects;

		vector.X = sphere.Center.X - box.Maximum.X;
		vector.Y = sphere.Center.Y - box.Maximum.Y;
		vector.Z = sphere.Center.Z - box.Maximum.Z;

		if( vector.LengthSquared() > radius )
			return ContainmentType::Intersects;

		vector.X = sphere.Center.X - box.Maximum.X;
		vector.Y = sphere.Center.Y - box.Minimum.Y;
		vector.Z = sphere.Center.Z - box.Maximum.Z;

		if( vector.LengthSquared() > radius )
			return ContainmentType::Intersects;

		vector.X = sphere.Center.X - box.Minimum.X;
		vector.Y = sphere.Center.Y - box.Minimum.Y;
		vector.Z = sphere.Center.Z - box.Maximum.Z;

		if( vector.LengthSquared() > radius )
			return ContainmentType::Intersects;

		vector.X = sphere.Center.X - box.Minimum.X;
		vector.Y = sphere.Center.Y - box.Maximum.Y;
		vector.Z = sphere.Center.Z - box.Minimum.Z;

		if( vector.LengthSquared() > radius )
			return ContainmentType::Intersects;

		vector.X = sphere.Center.X - box.Maximum.X;
		vector.Y = sphere.Center.Y - box.Maximum.Y;
		vector.Z = sphere.Center.Z - box.Minimum.Z;

		if( vector.LengthSquared() > radius )
			return ContainmentType::Intersects;

		vector.X = sphere.Center.X - box.Maximum.X;
		vector.Y = sphere.Center.Y - box.Minimum.Y;
		vector.Z = sphere.Center.Z - box.Minimum.Z;

		if( vector.LengthSquared() > radius )
			return ContainmentType::Intersects;

		vector.X = sphere.Center.X - box.Minimum.X;
		vector.Y = sphere.Center.Y - box.Minimum.Y;
		vector.Z = sphere.Center.Z - box.Minimum.Z;

		if( vector.LengthSquared() > radius )
			return ContainmentType::Intersects;

		return ContainmentType::Contains;
	}

	ContainmentType BoundingSphere::Contains( BoundingSphere sphere1, BoundingSphere sphere2 )
	{
		float distance;
		float x = sphere1.Center.X - sphere2.Center.X;
		float y = sphere1.Center.Y - sphere2.Center.Y;
		float z = sphere1.Center.Z - sphere2.Center.Z;

		distance = static_cast<float>( Math::Sqrt( (x * x) + (y * y) + (z * z) ) );
		float radius = sphere1.Radius;
		float radius2 = sphere2.Radius;

		if( radius + radius < distance )
			return ContainmentType::Disjoint;

		if( radius - radius2 < distance )
			return ContainmentType::Intersects;

		return ContainmentType::Contains;
	}

	ContainmentType BoundingSphere::Contains( BoundingSphere sphere, BoundingFrustum frustum )
	{
		if( !BoundingFrustum::Intersects( frustum, sphere ) )
			return ContainmentType::Disjoint;

		float radius = sphere.Radius * sphere.Radius;

		array<Vector3>^ corners = frustum.GetCorners();

		for each( Vector3 vector2 in corners )
		{
			Vector3 vector;
			vector.X = vector2.X - sphere.Center.X;
			vector.Y = vector2.Y - sphere.Center.Y;
			vector.Z = vector2.Z - sphere.Center.Z;

			if( vector.LengthSquared() > radius )
				return ContainmentType::Intersects;
		}

		return ContainmentType::Contains;
	}

	ContainmentType BoundingSphere::Contains( BoundingSphere sphere, Vector3 vector )
	{
		float x = vector.X - sphere.Center.X;
		float y = vector.Y - sphere.Center.Y;
		float z = vector.Z - sphere.Center.Z;

		float distance = (x * x) + (y * y) + (z * z);

		if( distance >= (sphere.Radius * sphere.Radius) )
			return ContainmentType::Disjoint;

		return ContainmentType::Contains;
	}

	BoundingSphere BoundingSphere::FromBox( BoundingBox box )
	{
		BoundingSphere sphere;
		Vector3::Lerp( box.Minimum, box.Maximum, 0.5f, sphere.Center );

		float x = box.Minimum.X - box.Maximum.X;
		float y = box.Minimum.Y - box.Maximum.Y;
		float z = box.Minimum.Z - box.Maximum.Z;

		float distance = static_cast<float>( Math::Sqrt( (x * x) + (y * y) + (z * z) ) );

		sphere.Radius = distance * 0.5f;

		return sphere;
	}

	BoundingSphere BoundingSphere::FromFrustum( BoundingFrustum frustum )
	{
		return FromPoints( frustum.GetCorners() );
	}

	BoundingSphere BoundingSphere::FromPoints( array<Vector3>^ points )
	{
		D3DXVECTOR3 center;
		FLOAT radius;
		pin_ptr<Vector3> pinnedPoints = &points[0];
		D3DXComputeBoundingSphere( reinterpret_cast<const D3DXVECTOR3*>( pinnedPoints ), points->Length, 0, &center, &radius );

		BoundingSphere sphere;
		sphere.Center = Vector3( center.x, center.y, center.z );
		sphere.Radius = radius;

		return sphere;
	}

	BoundingSphere BoundingSphere::Merge( BoundingSphere sphere1, BoundingSphere sphere2 )
	{
		BoundingSphere sphere;
		Vector3 difference = sphere2.Center - sphere1.Center;

		float length = difference.Length();
		float radius = sphere1.Radius;
		float radius2 = sphere2.Radius;

		if( radius + radius2 >= length)
		{
			if( radius - radius2 >= length )
				return sphere1;

			if( radius2 - radius >= length )
				return sphere2;
		}

		Vector3 vector = difference * ( 1.0f / length );
		float min = Math::Min( -radius, length - radius2 );
		float max = ( Math::Max( radius, length + radius2 ) - min ) * 0.5f;

		sphere.Center = sphere1.Center + vector * ( max + min );
		sphere.Radius = max;

		return sphere;
	}

	bool BoundingSphere::Intersects( BoundingSphere sphere, BoundingBox box )
	{
		return BoundingBox::Intersects( box, sphere );
	}

	bool BoundingSphere::Intersects( BoundingSphere sphere, BoundingFrustum frustum )
	{
		return BoundingFrustum::Intersects( frustum, sphere );
	}

	bool BoundingSphere::Intersects( BoundingSphere sphere1, BoundingSphere sphere2 )
	{
		float distance;
		distance = Vector3::DistanceSquared( sphere1.Center, sphere2.Center );
		float radius = sphere1.Radius;
		float radius2 = sphere2.Radius;

		if( (radius * radius) + (2.0f * radius * radius2) + (radius2 * radius2) <= distance )
			return false;

		return true;
	}

	bool BoundingSphere::Intersects( BoundingSphere sphere, Ray ray, [Out] float% distance )
	{
		return Ray::Intersects( ray, sphere, distance );
	}

	PlaneIntersectionType BoundingSphere::Intersects( BoundingSphere sphere, Plane plane )
	{
		return Plane::Intersects( plane, sphere );
	}

	bool BoundingSphere::operator == ( BoundingSphere left, BoundingSphere right )
	{
		return BoundingSphere::Equals( left, right );
	}

	bool BoundingSphere::operator != ( BoundingSphere left, BoundingSphere right )
	{
		return !BoundingSphere::Equals( left, right );
	}

	String^ BoundingSphere::ToString()
	{
		return String::Format( CultureInfo::CurrentCulture, "Center:{0} Radius:{1}", Center.ToString(), Radius.ToString(CultureInfo::CurrentCulture) );
	}

	int BoundingSphere::GetHashCode()
	{
		return Center.GetHashCode() + Radius.GetHashCode();
	}

	bool BoundingSphere::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<BoundingSphere>( value ) );
	}

	bool BoundingSphere::Equals( BoundingSphere value )
	{
		return ( Center == value.Center && Radius == value.Radius );
	}

	bool BoundingSphere::Equals( BoundingSphere% value1, BoundingSphere% value2 )
	{
		return ( value1.Center == value2.Center && value1.Radius == value2.Radius );
	}
}
