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
#include "Matrix.h"
#include "Plane.h"
#include "Vector3.h"

namespace SlimDX
{
	value class Ray;

	ref class SupportPointHelper
	{
	private:
		static array<int>^ bitsToIndices;
		
		Vector3 closestPoint;
		array<array<float>^>^ det;
		array<array<float>^>^ edgeLengthSquared;
		array<array<Vector3>^>^ edges;
		float maxLengthSquared;
		int simplexBits;
		array<Vector3>^ y;
		array<float>^ yLengthSquared;

		static SupportPointHelper()
		{
			bitsToIndices = gcnew array<int>( 16 );
			bitsToIndices[0] = 0;
			bitsToIndices[1] = 1;
			bitsToIndices[2] = 2;
			bitsToIndices[3] = 0x11;
			bitsToIndices[4] = 3;
			bitsToIndices[5] = 0x19;
			bitsToIndices[6] = 0x1a;
			bitsToIndices[7] = 0xd1;
			bitsToIndices[8] = 4;
			bitsToIndices[9] = 0x21;
			bitsToIndices[10] = 0x22;
			bitsToIndices[11] = 0x111;
			bitsToIndices[12] = 0x23;
			bitsToIndices[13] = 0x119;
			bitsToIndices[14] = 0x11a;
			bitsToIndices[15] = 0x8d1;
		}

		void UpdateDeterminant( int index );
		void UpdateSimplex( int index );

		bool SatisfiesRule( int xBits, int yBits );
		Vector3 ComputeClosestPoint();

	public:
		SupportPointHelper();

		void AddSupportPoint( Vector3 point );

		property Vector3 ClosestPoint
		{
			Vector3 get() { return closestPoint; }
		}

		property bool FullSimplex
		{
			bool get() { return ( simplexBits == 15 ); }
		}

		property float MaxLengthSquared
		{
			float get() { return maxLengthSquared; }
		}
	};
	
	[System::Serializable]
	[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
	public value class BoundingFrustum : System::IEquatable<BoundingFrustum>
	{
	private:
		array<Vector3>^ corners;
		array<Plane>^ planes;
		Matrix frustumMatrix;

		Vector3 SupportMapping( Vector3 value );

		static Ray ComputeIntersectionLine( Plane% plane1, Plane% plane2 );
		static Vector3 ComputeIntersection( Plane% plane, Ray% ray );

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
		static ContainmentType Contains( BoundingFrustum frustum1, BoundingFrustum frustum2 );

		static bool Intersects( BoundingFrustum frustum, BoundingBox box );
		static bool Intersects( BoundingFrustum frustum, BoundingSphere sphere );
		static bool Intersects( BoundingFrustum frustum, Ray ray, [Out] float% distance );
		static bool Intersects( BoundingFrustum frustum1, BoundingFrustum frustum2 );

		static PlaneIntersectionType Intersects( BoundingFrustum frustum, Plane plane );

		static bool operator == ( BoundingFrustum left, BoundingFrustum right );
		static bool operator != ( BoundingFrustum left, BoundingFrustum right );

		virtual System::String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( System::Object^ obj ) override;
		virtual bool Equals( BoundingFrustum other );
		static bool Equals( BoundingFrustum% value1, BoundingFrustum% value2 );
	};
}