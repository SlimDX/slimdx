#include "Operations.h"

namespace SlimMath { namespace Unmanaged {
	class BatchProcessor {
	public:
		BatchProcessor();
		void Process(OpDescriptor* ops, int opCount);
	};
}}