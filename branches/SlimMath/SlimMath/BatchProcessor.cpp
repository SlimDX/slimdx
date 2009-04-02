#pragma unmanaged
#include "stdafx.h"
#include "BatchProcessor.h"

namespace SlimMath { namespace Unmanaged {
	BatchProcessor::BatchProcessor() {}

	void BatchProcessor::Process(OpDescriptor *ops, float *data, int opCount) {
		for(int i = 0; i < opCount; ++i) {
			ProcessOp(ops[i], data);
		}
	}

	void BatchProcessor::ProcessOp(OpDescriptor const& op, float*& data) {
		switch(op.Op) {
			case Operation::MatrixAffineTransformation: {
				XMVECTOR p1 = ResolveVector(op.Parameters[0], data);
				XMVECTOR p2 = ResolveVector(op.Parameters[0], data);
				XMVECTOR p3 = ResolveVector(op.Parameters[0], data);
				XMVECTOR p4 = ResolveVector(op.Parameters[0], data);
				HandleData result;
				result.Matrix = XMMatrixAffineTransformation(p1, p2, p3, p4);
				result.IsOutput = op.Results[0].IsOutputResult;
				handles.insert(std::make_pair(op.Results[0].HandleName, result));
			}
			case Operation::MatrixMultiply: {
				XMMATRIX p1 = ResolveMatrix(op.Parameters[0], data);
				XMMATRIX p2 = ResolveMatrix(op.Parameters[1], data);
				HandleData result;
				result.Matrix = XMMatrixMultiply(p1, p2);
				result.IsOutput = op.Results[0].IsOutputResult;
				handles.insert(std::make_pair(op.Results[0].HandleName, result));
			}
			case Operation::MatrixIdentity: {
				HandleData result;
				result.Matrix = XMMatrixIdentity();
				result.IsOutput = op.Results[0].IsOutputResult;
				handles.insert(std::make_pair(op.Results[0].HandleName, result));
			}
			case Operation::MatrixInverse: {
				XMMATRIX p1 = ResolveMatrix(op.Parameters[0], data);
				HandleData returnResult;
				HandleData detResult;
				returnResult.Matrix = XMMatrixInverse(&detResult.Vector, p1);
				
				returnResult.IsOutput = op.Results[0].IsOutputResult;
				detResult.IsOutput = op.Results[1].IsOutputResult;

				handles.insert(std::make_pair(op.Results[0].HandleName, returnResult));
				handles.insert(std::make_pair(op.Results[1].HandleName, detResult));
			}
		}
	}

	XMMATRIX BatchProcessor::ResolveMatrix(ParameterDescriptor const& descriptor, float*& data) {
		if(descriptor.Type == ParameterDescriptor::Handle) {
			return handles[descriptor.HandleName].Matrix;
		} else {
			XMMATRIX result = XMLoadFloat4x4((XMFLOAT4X4*)data);
			data += 16;
			return result;
		}
	}

	XMVECTOR BatchProcessor::ResolveVector(ParameterDescriptor const& descriptor, float*& data) {
		if(descriptor.Type == ParameterDescriptor::Handle) {
			return handles[descriptor.HandleName].Vector;
		} else {
			XMVECTOR result = XMLoadFloat4((XMFLOAT4*)data);
			data += 4;
			return result;
		}
	}
}}
