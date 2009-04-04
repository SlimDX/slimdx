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
		float* results = ops->Results;
		float* parameters = ops->Parameters;

		for(int i = 0; i < opCount; ++i)
		{
			switch(ops->Op)
			{
				case Operation::MatrixIdentity:
					StoreMatrixResult(results, XMMatrixIdentity());
					break;
				case Operation::MatrixMultiply:
				{
					XMMATRIX p1 = GetMatrixParameter(parameters);
					XMMATRIX p2 = GetMatrixParameter(parameters + 16);
					StoreMatrixResult(results, XMMatrixMultiply(p1, p2));
					break;
				}
				case Operation::MatrixInverse:
				{
					XMMATRIX p1 = GetMatrixParameter(parameters);
					XMVECTOR det;
					StoreMatrixResult(results, XMMatrixInverse(&det, p1));
					StoreVectorResult(results + 16, det);
					break;
				}
				case Operation::MatrixTranslationFromVector:
					StoreMatrixResult(results, XMMatrixTranslationFromVector(GetVectorParameter(parameters)));
					break;
				case Operation::Vector4Transform:
					StoreVectorResult(results, XMVector4Transform(GetVectorParameter(parameters), GetMatrixParameter(parameters + 4)));
					break;
			}
		}
	}

	XMVECTOR BatchProcessor::GetVectorParameter(float* data)
	{
		XMVECTOR result = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(data));
		return result;
	}
	XMMATRIX BatchProcessor::GetMatrixParameter(float* data)
	{
		XMMATRIX result = XMLoadFloat4x4(reinterpret_cast<XMFLOAT4X4*>(data));
		return result;
	}

	void BatchProcessor::StoreVectorResult(float* data, CXMVECTOR vector)
	{
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(data), vector);
	}

	void BatchProcessor::StoreMatrixResult(float* data, CXMMATRIX matrix)
	{
		XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(data), matrix);
	}
}
