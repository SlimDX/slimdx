namespace SlimMath
{
	public ref class MatrixOps
	{
	public:
		[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential, Pack = 4)]
		ref class AffineTransformation
		{
		public:
			array<float>^ Scaling;
			array<float>^ RotationOrigin;
			array<float>^ RotationQuaterion;
			array<float>^ Translation;
		};

		[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential, Pack = 4)]
		ref class AffineTransformation2D
		{
		public:
			array<float>^ Scaling;
			array<float>^ RotationOrigin;
			float Rotation;
			array<float>^ Translation;
		};
	};
}
