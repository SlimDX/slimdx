#pragma unmanaged
#include "stdafx.h"
#include "BatchProcessor.h"

namespace SlimMath { namespace Unmanaged {
	BatchProcessor::BatchProcessor() {}

	void BatchProcessor::Process(OpDescriptor *ops, int opCount) {
		for(int i = 0; i < opCount; ++i) {
			switch(ops->Op) {
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

	XMVECTOR BatchProcessor::GetVectorParameter(ParameterDescriptor const& param) {
		return XMLoadFloat4((XMFLOAT4*)param.HandleStorage);
	}
	XMMATRIX BatchProcessor::GetMatrixParameter(ParameterDescriptor const& param) {
		return XMLoadFloat4x4((XMFLOAT4X4*)param.HandleStorage);
	}

	void BatchProcessor::StoreVectorResult(ResultDescriptor const& result, CXMVECTOR vector) {
		XMStoreFloat4((XMFLOAT4*)result.HandleStorage, vector);
	}

	void BatchProcessor::StoreMatrixResult(ResultDescriptor const& result, CXMMATRIX matrix) {
		XMStoreFloat4x4((XMFLOAT4X4*)result.HandleStorage, matrix);
	}
}}