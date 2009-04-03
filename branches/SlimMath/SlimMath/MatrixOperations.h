#include "Primitives.h"

namespace SlimMath {
	public ref class MatrixOps {
	public:
		[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential, Pack = 4)]
		value class AffineTransformation {
		public:
			Vector^ Scaling;
			Vector^ RotationOrigin;
			Vector^ RotationQuaterion;
			Vector^ Translation;
		};

		[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential, Pack = 4)]
		value class AffineTransformation2D {
		public:
			Vector Scaling;
			Vector RotationOrigin;
			float Rotation;
			Vector Translation;
		};
	};
}