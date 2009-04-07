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
#include "VectorOperations.h"

using namespace System;

namespace SlimMath
{
	Operation<Handle<Vector>^>^ VectorOps::Transform(Handle<Vector>^ value1, Handle<Matrix>^ value2)
	{
		return gcnew Operation<Handle<Vector>^>(gcnew Handle<Vector>(), gcnew array<BaseHandle^>(2) { value1, value2 }, 
			NativeOperation::Vector4::Transform);
	}

	Operation<StreamHandle<Vector>^>^ VectorOps::TransformStream(array<Vector>^ input, Handle<Matrix>^ transform)
	{
		StreamHandle<Vector>^ inputHandle = gcnew StreamHandle<Vector>(input);
		Handle<int>^ lengthHandle = gcnew Handle<int>(input->Length);

		return gcnew Operation<StreamHandle<Vector>^>(gcnew StreamHandle<Vector>(input->Length), 
			gcnew array<BaseHandle^>(3) { inputHandle, transform, lengthHandle },
			NativeOperation::Vector4::TransformStream);
	}
}
