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

#include <windows.h>
#include <xnamath.h>

#include "..\native\NativeOperations.h"

#include "Handle.h"
#include "PlaneOperations.h"

using namespace System;

namespace SlimMath
{
	Operation<Handle<float>^>^ PlaneOps::Dot(Handle<Plane>^ plane, Handle<Vector>^ point)
	{
		return gcnew Operation<Handle<float>^>(gcnew Handle<float>(), gcnew array<BaseHandle^>(2) { plane, point },
			NativeOperation::Plane::Dot);
	}

	Operation<Handle<float>^>^ PlaneOps::DotCoordinate(Handle<Plane>^ plane, Handle<Vector>^ point)
	{
		return gcnew Operation<Handle<float>^>(gcnew Handle<float>(), gcnew array<BaseHandle^>(2) { plane, point },
			NativeOperation::Plane::DotCoord);
	}

	Operation<Handle<float>^>^ PlaneOps::DotNormal(Handle<Plane>^ plane, Handle<Vector>^ point)
	{
		return gcnew Operation<Handle<float>^>(gcnew Handle<float>(), gcnew array<BaseHandle^>(2) { plane, point },
			NativeOperation::Plane::DotNormal);
	}

	Operation<Handle<Plane>^>^ PlaneOps::FromPointNormal(Handle<Vector>^ point, Handle<Vector>^ normal)
	{
		return gcnew Operation<Handle<Plane>^>(gcnew Handle<Plane>(), gcnew array<BaseHandle^>(2) { point, normal },
			NativeOperation::Plane::FromPointNormal);
	}

	Operation<Handle<Plane>^>^ PlaneOps::FromPoints(Handle<Vector>^ point1, Handle<Vector>^ point2, Handle<Vector>^ point3)
	{
		return gcnew Operation<Handle<Plane>^>(gcnew Handle<Plane>(), gcnew array<BaseHandle^>(3) { point1, point2, point3 },
			NativeOperation::Plane::FromPoints);
	}

	Operation<Handle<bool>^>^ PlaneOps::IsEqual(Handle<Plane>^ plane1, Handle<Plane>^ plane2)
	{
		return gcnew Operation<Handle<bool>^>(gcnew Handle<bool>(), gcnew array<BaseHandle^>(2) { plane1, plane2 },
			NativeOperation::Plane::Equal);
	}

	Operation<Handle<bool>^>^ PlaneOps::IsNotEqual(Handle<Plane>^ plane1, Handle<Plane>^ plane2)
	{
		return gcnew Operation<Handle<bool>^>(gcnew Handle<bool>(), gcnew array<BaseHandle^>(2) { plane1, plane2 },
			NativeOperation::Plane::NotEqual);
	}

	Operation<Handle<bool>^>^ PlaneOps::IsNearlyEqual(Handle<Plane>^ plane1, Handle<Plane>^ plane2, Handle<float>^ epsilon)
	{
		return gcnew Operation<Handle<bool>^>(gcnew Handle<bool>(), gcnew array<BaseHandle^>(3) { plane1, plane2, epsilon },
			NativeOperation::Plane::NearEqual);
	}

	Operation<Handle<bool>^>^ PlaneOps::IsInfinite(Handle<Plane>^ plane)
	{
		return gcnew Operation<Handle<bool>^>(gcnew Handle<bool>(), gcnew array<BaseHandle^>(1) { plane },
			NativeOperation::Plane::IsInfinite);
	}

	Operation<Handle<bool>^>^ PlaneOps::IsNaN(Handle<Plane>^ plane)
	{
		return gcnew Operation<Handle<bool>^>(gcnew Handle<bool>(), gcnew array<BaseHandle^>(1) { plane },
			NativeOperation::Plane::IsNaN);
	}

	Operation<Handle<Vector>^>^ PlaneOps::IntersectLine(Handle<Plane>^ plane, Handle<Vector>^ point1, Handle<Vector>^ point2)
	{
		return gcnew Operation<Handle<Vector>^>(gcnew Handle<Vector>(), gcnew array<BaseHandle^>(3) { plane, point1, point2 },
			NativeOperation::Plane::IntersectLine);
	}

	Operation<PlaneIntersectionHandle^>^ PlaneOps::IntersectPlane(Handle<Plane>^ plane1, Handle<Plane>^ plane2)
	{
		return gcnew Operation<PlaneIntersectionHandle^>(gcnew PlaneIntersectionHandle(), gcnew array<BaseHandle^>(2) { plane1, plane2 },
			NativeOperation::Plane::IntersectPlane);
	}

	Operation<Handle<Plane>^>^ PlaneOps::Normalize(Handle<Plane>^ plane)
	{
		return gcnew Operation<Handle<Plane>^>(gcnew Handle<Plane>(), gcnew array<BaseHandle^>(1) { plane },
			NativeOperation::Plane::Normalize);
	}

	Operation<Handle<Plane>^>^ PlaneOps::NormalizeEstimate(Handle<Plane>^ plane)
	{
		return gcnew Operation<Handle<Plane>^>(gcnew Handle<Plane>(), gcnew array<BaseHandle^>(1) { plane },
			NativeOperation::Plane::NormalizeEst);
	}

	Operation<Handle<Plane>^>^ PlaneOps::Transform(Handle<Plane>^ plane, Handle<Matrix>^ transform)
	{
		return gcnew Operation<Handle<Plane>^>(gcnew Handle<Plane>(), gcnew array<BaseHandle^>(2) { plane, transform },
			NativeOperation::Plane::Transform);
	}

	Operation<StreamHandle<Plane>^>^ PlaneOps::TransformStream(array<Plane>^ input, Handle<Matrix>^ transform)
	{
		StreamHandle<Plane>^ inputHandle = gcnew StreamHandle<Plane>(input);
		Handle<int>^ lengthHandle = gcnew Handle<int>(input->Length);

		return gcnew Operation<StreamHandle<Plane>^>(gcnew StreamHandle<Plane>(input->Length),
			gcnew array<BaseHandle^>(3) { inputHandle, transform, lengthHandle },
			NativeOperation::Plane::TransformStream);
	}
}