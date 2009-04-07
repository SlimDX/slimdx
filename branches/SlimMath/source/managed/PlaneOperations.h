/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include "Operation.h"
#include "Primitives.h"
#include "StreamHandle.h"
#include "PlaneIntersectionHandle.h"

namespace SlimMath
{
	public ref class PlaneOps sealed
	{
	private:
		PlaneOps() { }

	public:
		static Operation<Handle<float>^>^ Dot(Handle<Plane>^ plane, Handle<Vector>^ point);
		static Operation<Handle<float>^>^ DotCoordinate(Handle<Plane>^ plane, Handle<Vector>^ point);
		static Operation<Handle<float>^>^ DotNormal(Handle<Plane>^ plane, Handle<Vector>^ point);
		static Operation<Handle<Plane>^>^ FromPointNormal(Handle<Vector>^ point, Handle<Vector>^ normal);
		static Operation<Handle<Plane>^>^ FromPoints(Handle<Vector>^ point1, Handle<Vector>^ point2, Handle<Vector>^ point3);
		static Operation<Handle<bool>^>^ IsEqual(Handle<Plane>^ plane1, Handle<Plane>^ plane2);
		static Operation<Handle<bool>^>^ IsNotEqual(Handle<Plane>^ plane1, Handle<Plane>^ plane2);
		static Operation<Handle<bool>^>^ IsNearlyEqual(Handle<Plane>^ plane1, Handle<Plane>^ plane2, Handle<float>^ epsilon);
		static Operation<Handle<bool>^>^ IsInfinite(Handle<Plane>^ plane);
		static Operation<Handle<bool>^>^ IsNaN(Handle<Plane>^ plane);
		static Operation<Handle<Vector>^>^ IntersectLine(Handle<Plane>^ plane, Handle<Vector>^ point1, Handle<Vector>^ point2);
		static Operation<PlaneIntersectionHandle^>^ IntersectPlane(Handle<Plane>^ plane1, Handle<Plane>^ plane2);
		static Operation<Handle<Plane>^>^ Normalize(Handle<Plane>^ plane);
		static Operation<Handle<Plane>^>^ NormalizeEstimate(Handle<Plane>^ plane);
		static Operation<Handle<Plane>^>^ Transform(Handle<Plane>^ plane, Handle<Matrix>^ transform);
		static Operation<StreamHandle<Plane>^>^ TransformStream(array<Plane>^ input, Handle<Matrix>^ transform);
	};
}