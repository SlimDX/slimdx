#include "Operations.h"

namespace SlimMath { namespace Unmanaged {
	struct HandleData {
		XMVECTOR Vector;
		XMMATRIX Matrix;
		bool IsOutput;
	};

	class BatchProcessor {
	public:
		BatchProcessor();
		void Process(OpDescriptor* ops, float* data, int opCount);
	private:
		void ProcessOp(OpDescriptor const& op, float*& data);
		XMMATRIX ResolveMatrix(ParameterDescriptor const&, float*&);
		XMVECTOR ResolveVector(ParameterDescriptor const&, float*&);
	private:
		std::tr1::unordered_map<int, HandleData> handles;
	};
}}