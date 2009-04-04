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
#include "Handle.h"
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
		data = new float[48];

		memcpy(data, &value1.M11, size);
		memcpy(data + 16, &value2.M11, size);

		array<Handle::ParameterData>^ parameters = gcnew array<Handle::ParameterData>(2);
		array<Handle::ResultsData>^ results = gcnew array<Handle::ResultsData>(1);
		results[0].Data = data + 32;
		parameters[0].Data = data;
		parameters[1].Data = data + 16;
		handle = gcnew Handle(parameters, results, Operation::MatrixMultiply);
	}

	MatrixOps::Multiply::Multiply( Handle^ value1, Matrix value2, int resultIndex)
	{
		data = new float[32];
		memcpy(data, &value2.M11, sizeof(float) * 16);

		array<Handle::ParameterData>^ parameters = gcnew array<Handle::ParameterData>(2);
		array<Handle::ResultsData>^ results = gcnew array<Handle::ResultsData>(1);
		results[0].Data = data + 16;
		parameters[0].Data = value1->Results[resultIndex].Data;
		parameters[1].Data = data;

		handle = gcnew Handle(parameters, results, Operation::MatrixMultiply);
	}
	MatrixOps::Multiply::Multiply( Matrix value1, Handle^ value2, int resultIndex)
	{
		data = new float[32];
		memcpy(data, &value1.M11, sizeof(float) * 16);

		array<Handle::ParameterData>^ parameters = gcnew array<Handle::ParameterData>(2);
		array<Handle::ResultsData>^ results = gcnew array<Handle::ResultsData>(1);
		results[0].Data = data + 16;
		parameters[0].Data = data;
		parameters[1].Data = value2->Results[resultIndex].Data;

		handle = gcnew Handle(parameters, results, Operation::MatrixMultiply);
	}
	MatrixOps::Multiply::Multiply( Handle^ value1, Handle^ value2, int firstHandleResultIndex, int secondHandleResultIndex)
	{
		data = new float[16];

		array<Handle::ParameterData>^ parameters = gcnew array<Handle::ParameterData>(2);
		array<Handle::ResultsData>^ results = gcnew array<Handle::ResultsData>(1);
		results[0].Data = data;
		parameters[0].Data = value1->Results[firstHandleResultIndex].Data;
		parameters[1].Data = value2->Results[secondHandleResultIndex].Data;

		handle = gcnew Handle(parameters, results, Operation::MatrixMultiply);
	}

	MatrixOps::Identity::Identity()
	{
		data = new float[16];

		array<Handle::ParameterData>^ parameters = gcnew array<Handle::ParameterData>(0);
		array<Handle::ResultsData>^ results = gcnew array<Handle::ResultsData>(1);
		results[0].Data = data;
		handle = gcnew Handle(parameters, results, Operation::MatrixIdentity);
	}

	MatrixOps::Inverse::Inverse(Matrix matrix)
	{
		data = new float[36];

		memcpy(data, &matrix.M11, 16 * sizeof(float));

		array<Handle::ParameterData>^ parameters = gcnew array<Handle::ParameterData>(1);
		array<Handle::ResultsData>^ results = gcnew array<Handle::ResultsData>(2);
		results[0].Data = data + 16;
		results[1].Data = data + 32;
		parameters[0].Data = data;
		handle = gcnew Handle(parameters, results, Operation::MatrixInverse);
	}

	MatrixOps::Inverse::Inverse(Handle^ matrix, int resultIndex)
	{
		data = new float[20];
		array<Handle::ParameterData>^ parameters = gcnew array<Handle::ParameterData>(1);
		array<Handle::ResultsData>^ results = gcnew array<Handle::ResultsData>(2);
		results[0].Data = data;
		results[1].Data = data+16;
		parameters[0].Data = matrix->Results[resultIndex].Data;
		handle = gcnew Handle(parameters, results, Operation::MatrixInverse);
	}
}