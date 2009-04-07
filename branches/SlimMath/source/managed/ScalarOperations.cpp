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
#include "ScalarOperations.h"

using namespace System;

namespace SlimMath
{
	Operation<Handle<float>^>^ ScalarOps::Acos(Handle<float>^ angle)
	{
		return gcnew Operation<Handle<float>^>(gcnew Handle<float>(), gcnew array<BaseHandle^>(1) { angle },
			NativeOperation::Scalar::ACos);
	}

	Operation<Handle<float>^>^ ScalarOps::AcosEstimate(Handle<float>^ angle)
	{
		return gcnew Operation<Handle<float>^>(gcnew Handle<float>(), gcnew array<BaseHandle^>(1) { angle },
			NativeOperation::Scalar::ACosEst);
	}

	Operation<Handle<float>^>^ ScalarOps::Asin(Handle<float>^ angle)
	{
		return gcnew Operation<Handle<float>^>(gcnew Handle<float>(), gcnew array<BaseHandle^>(1) { angle },
			NativeOperation::Scalar::ASin);
	}

	Operation<Handle<float>^>^ ScalarOps::AsinEstimate(Handle<float>^ angle)
	{
		return gcnew Operation<Handle<float>^>(gcnew Handle<float>(), gcnew array<BaseHandle^>(1) { angle },
			NativeOperation::Scalar::ASinEst);
	}

	Operation<Handle<float>^>^ ScalarOps::Cos(Handle<float>^ angle)
	{
		return gcnew Operation<Handle<float>^>(gcnew Handle<float>(), gcnew array<BaseHandle^>(1) { angle },
			NativeOperation::Scalar::Cos);
	}

	Operation<Handle<float>^>^ ScalarOps::CosEstimate(Handle<float>^ angle)
	{
		return gcnew Operation<Handle<float>^>(gcnew Handle<float>(), gcnew array<BaseHandle^>(1) { angle },
			NativeOperation::Scalar::CosEst);
	}

	Operation<Handle<float>^>^ ScalarOps::Sin(Handle<float>^ angle)
	{
		return gcnew Operation<Handle<float>^>(gcnew Handle<float>(), gcnew array<BaseHandle^>(1) { angle },
			NativeOperation::Scalar::Sin);
	}

	Operation<Handle<float>^>^ ScalarOps::SinEstimate(Handle<float>^ angle)
	{
		return gcnew Operation<Handle<float>^>(gcnew Handle<float>(), gcnew array<BaseHandle^>(1) { angle },
			NativeOperation::Scalar::SinEst);
	}

	Operation<Handle<float>^>^ ScalarOps::ModAngle(Handle<float>^ angle)
	{
		return gcnew Operation<Handle<float>^>(gcnew Handle<float>(), gcnew array<BaseHandle^>(1) { angle },
			NativeOperation::Scalar::ModAngle);
	}

	Operation<Handle<bool>^>^ ScalarOps::IsNearlyEqual(Handle<float>^ value1, Handle<float>^ value2, Handle<float>^ epsilon)
	{
		return gcnew Operation<Handle<bool>^>(gcnew Handle<bool>(), gcnew array<BaseHandle^>(3) { value1, value2, epsilon },
			NativeOperation::Scalar::NearEqual);
	}

	Operation<SinCosHandle^>^ ScalarOps::SinCos(Handle<float>^ angle)
	{
		return gcnew Operation<SinCosHandle^>(gcnew SinCosHandle(), gcnew array<BaseHandle^>(1) { angle },
			NativeOperation::Scalar::SinCos);
	}

	Operation<SinCosHandle^>^ ScalarOps::SinCosEstimate(Handle<float>^ angle)
	{
		return gcnew Operation<SinCosHandle^>(gcnew SinCosHandle(), gcnew array<BaseHandle^>(1) { angle },
			NativeOperation::Scalar::SinCosEst);
	}
}
