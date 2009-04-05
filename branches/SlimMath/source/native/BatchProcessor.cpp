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

namespace SlimMath {
	BatchProcessor::BatchProcessor() {}

	void BatchProcessor::Process(OpDescriptor *ops, int opCount) {
		for(int i = 0; i < opCount; ++i) {
			switch(ops[i].Op) {
				case NativeOperation::MatrixIdentity:
					StoreMatrixResult(ops[i].Results[0].Data, XMMatrixIdentity());
					break;
				case NativeOperation::MatrixMultiply:
				{
					XMMATRIX p1 = GetMatrixParameter(ops[i].Parameters[0].Data);
					XMMATRIX p2 = GetMatrixParameter(ops[i].Parameters[1].Data);
					StoreMatrixResult(ops[i].Results[0].Data, XMMatrixMultiply(p1, p2));
					break;
				}
				case NativeOperation::MatrixInverse:
				{
					XMMATRIX p1 = GetMatrixParameter(ops[i].Parameters[0].Data);
					XMVECTOR det;
					StoreMatrixResult(ops[i].Results[0].Data, XMMatrixInverse(&det, p1));
					XMStoreFloat(ops[i].Results[1].Data, det);
					break;
				}
				case NativeOperation::MatrixTranslationFromVector:
					StoreMatrixResult(ops[i].Results[0].Data, XMMatrixTranslationFromVector(GetVectorParameter(ops[i].Parameters[0].Data)));
					break;
				case NativeOperation::Vector4Transform:
					StoreVectorResult(ops[i].Results[0].Data, XMVector4Transform(GetVectorParameter(ops[i].Parameters[0].Data), GetMatrixParameter(ops[i].Parameters[1].Data)));
					break;
			}
		}
	}

	__forceinline XMVECTOR BatchProcessor::GetVectorParameter(float* data) {
		XMVECTOR result = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(data));
		return result;
	}
	__forceinline XMMATRIX BatchProcessor::GetMatrixParameter(float* data) {
		XMMATRIX result = XMLoadFloat4x4(reinterpret_cast<XMFLOAT4X4*>(data));
		return result;
	}

	__forceinline void BatchProcessor::StoreVectorResult(float* data, CXMVECTOR vector) {
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(data), vector);
	}

	__forceinline void BatchProcessor::StoreMatrixResult(float* data, CXMMATRIX matrix) {
		XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(data), matrix);
	}
}
