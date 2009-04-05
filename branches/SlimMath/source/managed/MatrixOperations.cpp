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
#include <memory>

#include "..\native\NativeOperations.h"

#include "Handle.h"
#include "MatrixOperations.h"

using namespace System;

namespace SlimMath
{
	Operation<Matrix>^ MatrixOps::Multiply(Handle<Matrix>^ value1, Handle<Matrix>^ value2)
	{
		Handle<Matrix>^ result = gcnew Handle<Matrix>();

		return gcnew Operation<Matrix>(result, gcnew array<IntPtr>(2) { value1->RawData, value2->RawData }, NativeOperation::MatrixMultiply);
	}

	Operation<Matrix>^ MatrixOps::Identity()
	{
		Handle<Matrix>^ result = gcnew Handle<Matrix>();

		return gcnew Operation<Matrix>(result, gcnew array<IntPtr>(0), NativeOperation::MatrixIdentity);
	}

	CompoundOperation^ MatrixOps::Inverse(Handle<Matrix>^ matrix)
	{
		Handle<Matrix>^ firstResult = gcnew Handle<Matrix>();
		Handle<float>^ secondResult = gcnew Handle<float>();

		CompoundHandle^ result = gcnew CompoundHandle(gcnew array<IHandle^>(2) { firstResult, secondResult });

		return gcnew CompoundOperation(result, gcnew array<IntPtr>(1) { matrix->RawData }, NativeOperation::MatrixInverse);
	}
}