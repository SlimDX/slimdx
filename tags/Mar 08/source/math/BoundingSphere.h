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

#include "Enums.h"
#include "Vector3.h"

namespace SlimDX
{
	value class BoundingBox;
	value class Plane;
	value class Ray;
	
	/// <summary>
	/// A bounding sphere, specified by a center vector and a radius.
	/// </summary>
	[System::Serializable]
	[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
	public value class BoundingSphere : System::IEquatable<BoundingSphere>
	{
	public:
		Vector3 Center;
		float Radius;

		BoundingSphere( Vector3 center, float radius );

		static ContainmentType Contains( BoundingSphere sphere, BoundingBox box );
		static ContainmentType Contains( BoundingSphere sphere1, BoundingSphere sphere2 );
		static ContainmentType Contains( BoundingSphere sphere, Vector3 vector );

		static BoundingSphere FromBox( BoundingBox box );
		static BoundingSphere FromPoints( array<Vector3>^ points );

		static BoundingSphere Merge( BoundingSphere sphere1, BoundingSphere sphere2 );

		static bool Intersects( BoundingSphere sphere, BoundingBox box );
		static bool Intersects( BoundingSphere sphere1, BoundingSphere sphere2 );
		static bool Intersects( BoundingSphere sphere, Ray ray, [Out] float% distance );

		static PlaneIntersectionType Intersects( BoundingSphere sphere, Plane plane );

		static bool operator == ( BoundingSphere left, BoundingSphere right );
		static bool operator != ( BoundingSphere left, BoundingSphere right );

		virtual System::String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( System::Object^ obj ) override;
		virtual bool Equals( BoundingSphere other );
		static bool Equals( BoundingSphere% value1, BoundingSphere% value2 );
	};
}