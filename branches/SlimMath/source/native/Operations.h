namespace SlimMath
{
	struct Operation
	{
		enum Ops
		{
			MatrixAffineTransformation,
			MatrixAffineTransformation2D,
			MatrixDecompose,
			MatrixDeterminant,
			MatrixIdentity,
			MatrixInverse,
			MatrixIsIdentity,
			MatrixIsInfinite,
			MatrixIsNaN,
			MatrixLookAtLH,
			MatrixLookAtRH,
			MatrixLookToLH,
			MatrixLookToRH,
			MatrixMultiply,
			MatrixMultiplyTranspose,
			MatrixTranslationFromVector,
			Vector4Transform
		};
	};

	struct ParameterDescriptor
	{
		float* HandleStorage;
	};

	struct ResultDescriptor
	{
		bool IsFutureParameter;
		float* HandleStorage;
	};

	struct OpDescriptor
	{
		Operation::Ops Op;

		ParameterDescriptor Parameters[16];

		ResultDescriptor Results[3];
	};
}
