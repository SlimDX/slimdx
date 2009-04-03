#include "Operations.h"

namespace SlimMath { namespace Unmanaged {
	class BatchProcessor {
	public:
		BatchProcessor();
		void Process(OpDescriptor* ops, int opCount);
	private:
		XMVECTOR GetVectorParameter(ParameterDescriptor const& param);
		XMMATRIX GetMatrixParameter(ParameterDescriptor const& param);
		void StoreVectorResult(ResultDescriptor const& result, CXMVECTOR vector);
		void StoreMatrixResult(ResultDescriptor const& result, CXMMATRIX matrix);
	};
}}