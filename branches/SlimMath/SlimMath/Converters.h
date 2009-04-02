#include "Primitives.h"

#pragma managed(push, off)

namespace SlimMath {
	class Converters {
	public:
		static void LoadMatrix(XMMATRIX* destMatrix, float* sourceMatrix) {
			LoadMatrixes(destMatrix, sourceMatrix, 1);
		}

		static void LoadMatrixes(XMMATRIX* destMatrixes, float* sourceMatrixes, int matrixCount) {
			for(int i = 0; i < matrixCount; ++i) {
				destMatrixes[i] = XMLoadFloat4x4(((XMFLOAT4X4*)sourceMatrixes) + i);
			}
		}

		static void LoadVector4(XMVECTOR* destVector, float* sourceVector) {
			LoadVector4s(destVector, sourceVector, 1);
		}

		static void LoadVector4s(XMVECTOR* destVectors, float* sourceVectors, int vectorCount) {
			for(int i = 0; i < vectorCount; ++i) {
				destVectors[i] = XMLoadFloat4(((XMFLOAT4*)sourceVectors) + i);
			}
		}

		static void LoadVector3(XMVECTOR* destVector, float* sourceVector) {
			LoadVector3s(destVector, sourceVector, 1);
		}

		static void LoadVector3s(XMVECTOR* destVectors, float* sourceVectors, int vectorCount) {
			for(int i = 0; i < vectorCount; ++i) {
				destVectors[i] = XMLoadFloat3(((XMFLOAT3*)sourceVectors) + i);
			}
		}

		static void LoadVector2(XMVECTOR* destVector, float* sourceVector) {
			LoadVector2s(destVector, sourceVector, 1);
		}

		static void LoadVector2s(XMVECTOR* destVectors, float* sourceVectors, int vectorCount) {
			for(int i = 0; i < vectorCount; ++i) {
				destVectors[i] = XMLoadFloat2(((XMFLOAT2*)sourceVectors) + i);
			}
		}
	};
}

#pragma managed(pop)