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

#include "BatchProcessor.h"

namespace SlimMath
{
	BatchProcessor::BatchProcessor() {}

	void BatchProcessor::Process(OpDescriptor *ops, int opCount)
	{
		for(int i = 0; i < opCount; ++i)
		{
			switch(ops->Op)
			{
				case Operation::MatrixIsIdentity:
					StoreMatrixResult(ops->Results[0], XMMatrixIdentity());
					break;
				case Operation::MatrixMultiply:
				{
					XMMATRIX p1 = GetMatrixParameter(ops->Parameters[0]);
					XMMATRIX p2 = GetMatrixParameter(ops->Parameters[1]);
					StoreMatrixResult(ops->Results[0], XMMatrixMultiply(p1, p2));
					break;
				}
				case Operation::MatrixInverse:
				{
					XMMATRIX p1 = GetMatrixParameter(ops->Parameters[0]);
					XMVECTOR det;
					StoreMatrixResult(ops->Results[0], XMMatrixInverse(&det, p1));
					StoreVectorResult(ops->Results[1], det);
					break;
				}
				case Operation::MatrixTranslationFromVector:
					StoreMatrixResult(ops->Results[0], XMMatrixTranslationFromVector(GetVectorParameter(ops->Parameters[0])));
					break;
				case Operation::Vector4Transform:
					StoreVectorResult(ops->Results[0], XMVector4Transform(GetVectorParameter(ops->Parameters[0]), GetMatrixParameter(ops->Parameters[1])));
					break;
			}
		}
	}

	XMVECTOR BatchProcessor::GetVectorParameter(ParameterDescriptor const& param)
	{
		return XMLoadFloat4((XMFLOAT4*)param.HandleStorage);
	}
	XMMATRIX BatchProcessor::GetMatrixParameter(ParameterDescriptor const& param)
	{
		return XMLoadFloat4x4((XMFLOAT4X4*)param.HandleStorage);
	}

	void BatchProcessor::StoreVectorResult(ResultDescriptor const& result, CXMVECTOR vector)
	{
		XMStoreFloat4((XMFLOAT4*)result.HandleStorage, vector);
	}

	void BatchProcessor::StoreMatrixResult(ResultDescriptor const& result, CXMMATRIX matrix)
	{
		XMStoreFloat4x4((XMFLOAT4X4*)result.HandleStorage, matrix);
	}
}
