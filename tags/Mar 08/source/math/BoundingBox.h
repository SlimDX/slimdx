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

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	value class BoundingSphere;
	value class Plane;
	value class Ray;

	/// <summary>
	/// An axis aligned bounding box, specified by minimum and maximum vectors.
	/// </summary>
	[System::Serializable]
	[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
	public value class BoundingBox : System::IEquatable<BoundingBox>
	{
	public:
		Vector3 Maximum;
		Vector3 Minimum;

		BoundingBox( Vector3 minimum, Vector3 maximum );

		array<Vector3>^ GetCorners();

		static ContainmentType Contains( BoundingBox box1, BoundingBox box2 );
		static ContainmentType Contains( BoundingBox box, BoundingSphere sphere );
		static ContainmentType Contains( BoundingBox box, Vector3 vector );

		static BoundingBox FromPoints( array<Vector3>^ points );
		static BoundingBox FromSphere( BoundingSphere sphere );

		static BoundingBox Merge( BoundingBox box1, BoundingBox box2 );

		static bool Intersects( BoundingBox box1, BoundingBox box2 );
		static bool Intersects( BoundingBox box, BoundingSphere sphere );
		static bool Intersects( BoundingBox box, Ray ray, [Out] float% distance );

		static PlaneIntersectionType Intersects( BoundingBox box, Plane plane );

		static bool operator == ( BoundingBox left, BoundingBox right );
		static bool operator != ( BoundingBox left, BoundingBox right );

		virtual System::String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( System::Object^ obj ) override;
		virtual bool Equals( BoundingBox other );
		static bool Equals( BoundingBox% value1, BoundingBox% value2 );
	};
}