namespace SlimMath { namespace Unmanaged {
	struct Operation {
		enum Ops {
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
			MatrixMultiplyTranspose
		};
	};

	struct ParameterDescriptor {
		enum ParameterType {
			Handle,
			Value
		};

		ParameterType Type;
		int HandleName;
	};

	struct ResultDescriptor {
		bool IsOutputResult;
		int HandleName;
	};

	struct OpDescriptor {
		Operation::Ops Op;

		ParameterDescriptor Parameters[16];

		ResultDescriptor Results[3];
	};
}}