#include "Operations.h"

namespace SlimMath
{
	class BatchProcessor
	{
	public:
		BatchProcessor();
		void Process(OpDescriptor* ops, int opCount);
	};
}}
