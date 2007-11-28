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
	public enum class ContainmentType : Int32
	{
		Disjoint,
		Contains,
		Intersects
	};

	[Serializable]
	[StructLayout( LayoutKind::Sequential )]
	public value class BoundingBox : IEquatable<BoundingBox>
	{
	public:
		Vector3 Maximum;
		Vector3 Minimum;

		BoundingBox( Vector3 minimum, Vector3 maximum );

		array<Vector3>^ GetCorners();

		static ContainmentType Contains( BoundingBox box1, BoundingBox box2 );
		static ContainmentType Contains( BoundingBox box, BoundingSphere sphere );
		static ContainmentType Contains( BoundingBox box, BoundingFrustum frustum );
		static ContainmentType Contains( BoundingBox box, Vector3 vector );

		static BoundingBox FromPoints( array<Vector3>^ points );
		static BoundingBox FromSphere( BoundingSphere sphere );

		static BoundingBox Merge( BoundingBox box1, BoundingBox box2 );

		static bool Intersects( BoundingBox box1, BoundingBox box2 );
		static bool Intersects( BoundingBox box, BoundingSphere sphere );
		static bool Intersects( BoundingBox box, BoundingFrustum frustum );
		static bool Intersects( BoundingBox box, Ray ray, [Out] float% distance );

		static PlaneIntersectionType Intersects( BoundingBox box, Plane plane );

		static bool operator == ( BoundingBox left, BoundingBox right );
		static bool operator != ( BoundingBox left, BoundingBox right );

		virtual String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( Object^ obj ) override;
		virtual bool Equals( BoundingBox other );
		static bool Equals( BoundingBox% value1, BoundingBox% value2 );
	};

	[Serializable]
	[StructLayout( LayoutKind::Sequential )]
	public value class BoundingFrustum : IEquatable<BoundingFrustum>
	{
	private:
		array<Vector3>^ corners;
		array<Plane>^ planes;
		Matrix frustumMatrix;

		Ray ComputeIntersectionLine( Plane% plane1, Plane% plane2 );
		Vector3 ComputeIntersection( Plane% plane, Ray% ray );

	public:
		property Matrix FrustumMatrix { Matrix get() { return frustumMatrix; } void set( Matrix value ); }
		property Plane Bottom { Plane get() { return planes[5]; } }
		property Plane Far { Plane get() { return planes[1]; } }
		property Plane Left { Plane get() { return planes[2]; } }
		property Plane Near { Plane get() { return planes[0]; } }
		property Plane Right { Plane get() { return planes[3]; } }
		property Plane Top { Plane get() { return planes[4]; } }

		BoundingFrustum( Matrix matrix );

		array<Vector3>^ GetCorners();
		array<Plane>^ GetPlanes();

		static ContainmentType Contains( BoundingFrustum frustum, BoundingBox box );
		static ContainmentType Contains( BoundingFrustum frustum, BoundingSphere sphere );
		static ContainmentType Contains( BoundingFrustum frustum, Vector3 vector );

		static bool Intersects( BoundingFrustum frustum, BoundingBox box );
		static bool Intersects( BoundingFrustum frustum, BoundingSphere sphere );
		static bool Intersects( BoundingFrustum frustum, Ray ray, [Out] float% distance );

		static PlaneIntersectionType Intersects( BoundingFrustum frustum, Plane plane );

		static bool operator == ( BoundingFrustum left, BoundingFrustum right );
		static bool operator != ( BoundingFrustum left, BoundingFrustum right );

		virtual String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( Object^ obj ) override;
		virtual bool Equals( BoundingFrustum other );
		static bool Equals( BoundingFrustum% value1, BoundingFrustum% value2 );
	};

	[Serializable]
	[StructLayout( LayoutKind::Sequential )]
	public value class BoundingSphere : IEquatable<BoundingSphere>
	{
	public:
		Vector3 Center;
		float Radius;

		BoundingSphere( Vector3 center, float radius );

		static ContainmentType Contains( BoundingSphere sphere, BoundingBox box );
		static ContainmentType Contains( BoundingSphere sphere1, BoundingSphere sphere2 );
		static ContainmentType Contains( BoundingSphere sphere, BoundingFrustum frustum );
		static ContainmentType Contains( BoundingSphere sphere, Vector3 vector );

		static BoundingSphere FromBox( BoundingBox box );
		static BoundingSphere FromFrustum( BoundingFrustum frustum );
		static BoundingSphere FromPoints( array<Vector3>^ points );

		static BoundingSphere Merge( BoundingSphere sphere1, BoundingSphere sphere2 );

		static bool Intersects( BoundingSphere sphere, BoundingBox box );
		static bool Intersects( BoundingSphere sphere, BoundingFrustum frustum );
		static bool Intersects( BoundingSphere sphere1, BoundingSphere sphere2 );
		static bool Intersects( BoundingSphere sphere, Ray ray, [Out] float% distance );

		static PlaneIntersectionType Intersects( BoundingSphere sphere, Plane plane );

		static bool operator == ( BoundingSphere left, BoundingSphere right );
		static bool operator != ( BoundingSphere left, BoundingSphere right );

		virtual String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( Object^ obj ) override;
		virtual bool Equals( BoundingSphere other );
		static bool Equals( BoundingSphere% value1, BoundingSphere% value2 );
	};
}