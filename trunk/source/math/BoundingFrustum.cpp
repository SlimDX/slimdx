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

	ContainmentType BoundingFrustum::Contains( BoundingFrustum frustum1, BoundingFrustum frustum2 )
	{
		ContainmentType result = ContainmentType::Disjoint;

		if( Intersects( frustum1, frustum2 ) )
		{
			result = ContainmentType::Contains;
			array<Vector3>^ corners = frustum1.GetCorners();
			array<Vector3>^ otherCorners = frustum2.GetCorners();

			for( int i = 0; i < corners->Length; i++ )
			{
				if( Contains( frustum1, otherCorners[i] ) == ContainmentType::Disjoint )
					return ContainmentType::Intersects;
			}
		}

		return result;
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

	Vector3 BoundingFrustum::SupportMapping( Vector3 value )
	{
		array<Vector3>^ corners = GetCorners();
		int index = 0;

		float dot = Vector3::Dot( corners[0], value );

		for( int i = 1; i < corners->Length; i++ )
		{
			float temp = Vector3::Dot( corners[i], value );
			if( temp > dot )
			{
				index = i;
				dot = temp;
			}
		}

		return corners[index];
	}

	bool BoundingFrustum::Intersects( BoundingFrustum frustum1, BoundingFrustum frustum2 )
	{
		SupportPointHelper^ helper = gcnew SupportPointHelper();

		array<Vector3>^ frustum1Corners = frustum1.GetCorners();
		array<Vector3>^ frustum2Corners = frustum2.GetCorners();

		Vector3 closestPoint = frustum1Corners[0] - frustum2Corners[0];
		if( closestPoint.LengthSquared() < 0.00001f )
			closestPoint = frustum1Corners[0] - frustum2Corners[1];

		float maxValue = float::MaxValue;
		float currentValue = 0.0f;

		do
		{
			Vector3 difference = frustum1.SupportMapping( -closestPoint ) - frustum2.SupportMapping( closestPoint );
			float dot = Vector3::Dot( closestPoint, difference );
			if( dot > 0.0f )
				return false;

			helper->AddSupportPoint( difference );
			closestPoint = helper->ClosestPoint;

			float temp = maxValue;
			maxValue = closestPoint.LengthSquared();
			currentValue = 0.00004f * helper->MaxLengthSquared;
			
			if( temp - maxValue <= 0.00001f * temp )
				return false;
		}
		while( !helper->FullSimplex && maxValue >= currentValue );

		return true;
	}

	bool BoundingFrustum::Intersects( BoundingFrustum frustum, BoundingBox box )
	{
		return Contains( frustum, box ) == ContainmentType::Intersects;
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

	SupportPointHelper::SupportPointHelper()
	{
		y = gcnew array<Vector3>( 4 );
		yLengthSquared = gcnew array<float>( 4 );

		edges = gcnew array<array<Vector3>^>( 4 );
		edges[0] = gcnew array<Vector3>( 4 );
		edges[1] = gcnew array<Vector3>( 4 );
		edges[2] = gcnew array<Vector3>( 4 );
		edges[3] = gcnew array<Vector3>( 4 );
		
		edgeLengthSquared = gcnew array<array<float>^>( 4 );
		edgeLengthSquared[0] = gcnew array<float>( 4 );
		edgeLengthSquared[1] = gcnew array<float>( 4 );
		edgeLengthSquared[2] = gcnew array<float>( 4 );
		edgeLengthSquared[3] = gcnew array<float>( 4 );

		det = gcnew array<array<float>^>( 16 );
		for( int i = 0; i < 16; i++ )
			det[i] = gcnew array<float>( 4 );
	}

	void SupportPointHelper::AddSupportPoint( Vector3 point )
	{
		int index = ( bitsToIndices[simplexBits ^ 15] & 7 ) - 1;
		y[index] = point;
		yLengthSquared[index] = point.LengthSquared();

		for( int i = bitsToIndices[simplexBits]; i != 0; i = i >> 3 )
		{
			int temp = ( i & 7 ) - 1;
			Vector3 vector = y[temp] - point;
			edges[temp][index] = vector;
			edges[index][temp] = -vector;
			edgeLengthSquared[index][temp] = edgeLengthSquared[temp][index] = vector.LengthSquared();
		}

		UpdateDeterminant( index );
		UpdateSimplex( index );
	}

	void SupportPointHelper::UpdateDeterminant( int inputIndex )
	{
		int index = 1 << inputIndex;
		det[index][inputIndex] = 1.0f;

		int bits = bitsToIndices[simplexBits];
		int currentBits = bits;
		for (int i = 0; currentBits != 0; i++)
		{
			int shift = (currentBits & 7) - 1;
			int shifted = 1 << shift;
			int index2 = shifted | index;
			det[index2][shift] = Vector3::Dot(edges[inputIndex][shift], y[inputIndex]);
			det[index2][inputIndex] = Vector3::Dot(edges[shift][inputIndex], y[shift]);
			
			int loop = bits;
			for (int j = 0; j < i; j++)
			{
				int det1 = (loop & 7) - 1;
				int det2 = 1 << det1;
				int det3 = index2 | det2;
				int det4 = (edgeLengthSquared[shift][det1] < edgeLengthSquared[inputIndex][det1]) ? shift : inputIndex;
				det[det3][det1] = (det[index2][shift] * Vector3::Dot(edges[det4][det1], y[shift])) + (det[index2][inputIndex] * Vector3::Dot(edges[det4][det1], y[inputIndex]));
				det4 = (edgeLengthSquared[det1][shift] < edgeLengthSquared[inputIndex][shift]) ? det1 : inputIndex;
				det[det3][shift] = (det[det2 | index][det1] * Vector3::Dot(edges[det4][shift], y[det1])) + (det[det2 | index][inputIndex] * Vector3::Dot(edges[det4][shift], y[inputIndex]));
				det4 = (edgeLengthSquared[shift][inputIndex] < edgeLengthSquared[det1][inputIndex]) ? shift : det1;
				det[det3][inputIndex] = (det[shifted | det2][det1] * Vector3::Dot(edges[det4][inputIndex], y[det1])) + (det[shifted | det2][shift] * Vector3::Dot(edges[det4][inputIndex], y[shift]));
				loop = loop >> 3;
			}

			currentBits = currentBits >> 3;
		}

		if ((simplexBits | index) == 15)
		{
			int length = (edgeLengthSquared[1][0] < edgeLengthSquared[2][0]) ? ((edgeLengthSquared[1][0] < edgeLengthSquared[3][0]) ? 1 : 3) : ((edgeLengthSquared[2][0] < edgeLengthSquared[3][0]) ? 2 : 3);
			det[15][0] = ((det[14][1] * Vector3::Dot(edges[length][0], y[1])) + (det[14][2] * Vector3::Dot(edges[length][0], y[2]))) + (det[14][3] * Vector3::Dot(edges[length][0], y[3]));
			length = (edgeLengthSquared[0][1] < edgeLengthSquared[2][1]) ? ((edgeLengthSquared[0][1] < edgeLengthSquared[3][1]) ? 0 : 3) : ((edgeLengthSquared[2][1] < edgeLengthSquared[3][1]) ? 2 : 3);
			det[15][1] = ((det[13][0] * Vector3::Dot(edges[length][1], y[0])) + (det[13][2] * Vector3::Dot(edges[length][1], y[2]))) + (det[13][3] * Vector3::Dot(edges[length][1], y[3]));
			length = (edgeLengthSquared[0][2] < edgeLengthSquared[1][2]) ? ((edgeLengthSquared[0][2] < edgeLengthSquared[3][2]) ? 0 : 3) : ((edgeLengthSquared[1][2] < edgeLengthSquared[3][2]) ? 1 : 3);
			det[15][2] = ((det[11][0] * Vector3::Dot(edges[length][2], y[0])) + (det[11][1] * Vector3::Dot(edges[length][2], y[1]))) + (det[11][3] * Vector3::Dot(edges[length][2], y[3]));
			length = (edgeLengthSquared[0][3] < edgeLengthSquared[1][3]) ? ((edgeLengthSquared[0][3] < edgeLengthSquared[2][3]) ? 0 : 2) : ((edgeLengthSquared[1][3] < edgeLengthSquared[2][3]) ? 1 : 2);
			det[15][3] = ((det[7][0] * Vector3::Dot(edges[length][3], y[0])) + (det[7][1] * Vector3::Dot(edges[length][3], y[1]))) + (det[7][2] * Vector3::Dot(edges[length][3], y[2]));
		}
	}

	void SupportPointHelper::UpdateSimplex( int newIndex )
	{
		int yBits = simplexBits | ( 1 << newIndex );
		int xBits = ( 1 << newIndex );

		for( int i = simplexBits; i != 0; i-- )
		{
			if( (i & yBits) == i && SatisfiesRule( i | xBits, yBits ) )
			{
				simplexBits = i | xBits;
				closestPoint = ComputeClosestPoint();
				return;
			}
		}

		if( SatisfiesRule( xBits, yBits ) )
		{
			simplexBits = xBits;
			closestPoint = y[newIndex];
			maxLengthSquared = yLengthSquared[newIndex];
		}
	}

	bool SupportPointHelper::SatisfiesRule( int xBits, int yBits )
	{
		for( int i = bitsToIndices[yBits]; i != 0; i = i >> 3 )
		{
			int index1 = (i & 7) - 1;
			int index2 = 1 << index1;

			if( (index2 & xBits) != 0 )
			{
				if( det[xBits][index1] <= 0.0f )
					return false;
			}
			else if( det[xBits | index2][index1] > 0.0f )
				return false;
		}

		return true;
	}

	Vector3 SupportPointHelper::ComputeClosestPoint()
	{
		float total = 0.0f;
		maxLengthSquared = 0.0f;
		Vector3 zero = Vector3::Zero;

		for( int i = bitsToIndices[simplexBits]; i != 0; i = i >> 3 )
		{
			int index = (i & 7) - 1;
			float value = det[simplexBits][index];

			total += value;

			zero += ( y[index] * value );

			maxLengthSquared = Math::Max( maxLengthSquared, yLengthSquared[index] );
		}

		return ( zero / total );
	}
}
