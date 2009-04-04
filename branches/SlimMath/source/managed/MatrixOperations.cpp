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

#include <memory>
#include "MatrixOperations.h"
#include "..\native\operations.h"
#include <windows.h>
#include <xnamath.h>
using namespace System;

namespace SlimMath
{
	MatrixOps::Multiply::Multiply( Matrix value1, Matrix value2 )
	{
		int size = sizeof(float) * 16;
		float *data = new float[32];

		memcpy(data, &value1.M11, size);
		memcpy(data + 16, &value2.M11, size);

		handle = gcnew Handle(data, 16, Operation::MatrixMultiply);
	}

	MatrixOps::Identity::Identity()
	{
		handle = gcnew Handle(0, 16, Operation::MatrixIdentity);
	}

	MatrixOps::Inverse::Inverse(Matrix matrix)
	{
		float* data = new float[16];

		memcpy(data, &matrix.M11, 16 * sizeof(float));

		handle = gcnew Handle(data, 20, Operation::MatrixInverse);
	}
}