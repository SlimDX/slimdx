/*
* Copyright (c) 2007-2009 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
namespace SlimMath
{
	struct NativeOperation
	{
		struct Color {
			enum {
				AdjustContrast = 0x00000000,
				AdjustSaturation,
				Equal,
				Greater,
				GreaterOrEqual,
				IsInfinite,
				IsNaN,
				Less,
				LessOrEqual,
				Modulate,
				NearEqual,
				Negative,
				NotEqual,
			};
		};

		struct Matrix {
			enum {
				AffineTransformation = 0x00001000,
				AffineTransformation2D,
				Decompose,
				Determinant,
				Identity,
				Inverse,
				IsIdentity,
				IsInfinite,
				IsNaN,
				LookAtLH,
				LookAtRH,
				LookToLH,
				LookToRH,
				Multiply,
				MultiplyTranspose,
				OrthographicLH,
				OrthographicOffCenterLH,
				OrthographicOffCenterRH,
				OrthographicRH,
				PerspectiveFovLH,
				PerspectiveFovRH,
				PerspectiveLH,
				PerspectiveOffCenterLH,
				PerspectiveOffCenterRH,
				PerspectiveRH,
				Reflect,
				RotationAxis,
				RotationNormal,
				RotationQuaternion,
				RotationRollPitchYaw,
				RotationRollPitchYawFromVector,
				RotationX,
				RotationY,
				RotationZ,
				Scaling,
				ScalingFromVector,
				Set,
				Shadow,
				Transformation,
				Transformation2D,
				Translation,
				TranslationFromVector,
				Transpose,
			};
		};

		struct Plane {
			enum {
				Dot = 0x00002000,
				DotCoord,
				DotNormal,
				Equal,
				FromPointNormal,
				FromPoints,
				IntersectLine,
				IntersectPlane,
				IsInfinite,
				IsNaN,
				NearEqual,
				Normalize,
				NormalizeEst,
				NotEqual,
				Transform,
				TransformStream,
			};
		};

		struct Quaternion {
			enum {
				BaryCentric = 0x00003000,
				BaryCentricV,
				Conjugate,
				Dot,
				Equal,
				Exp,
				Identity,
				Inverse,
				IsIdentity,
				IsInfinite,
				IsNaN,
				Length,
				LengthSq,
				Ln,
				Multiply,
				Normalize,
				NormalizeEst,
				NotEqual,
				ReciprocalLength,
				RotationAxis,
				RotationMatrix,
				RotationNormal,
				RotationRollPitchYaw,
				RotationRollPitchYawFromVector,
				Slerp,
				SlerpV,
				Squad,
				SquadSetup,
				SquadV,
				ToAxisAngle,
			};
		};

		struct Scalar {
			enum {
				ACos = 0x00004000,
				ACosEst,
				ASin,
				ASinEst,
				Cos,
				CosEst,
				ModAngle,
				NearEqual,
				Sin,
				SinCos,
				SinCosEst,
				SinEst,
			};
		};

		struct Vector {
			enum {
				Abs = 0x00005000,
				Add,
				AddAngles,
				Ceiling,
				Clamp,
				Floor,
				Insert,
				IsInfinite,
				IsNaN,
				Max,
				Min,
				Mod,
				ModAngles,
				Multiply,
				MultiplyAdd,
				Negate,
				NegativeMultiplySubstract,
				Pow,
				PowEst,
				Reciprocal,
				ReciprocalEst,
				ReciprocalSqrt,
				ReciprocalSqrtEst,
				RotateLeft,
				RotateRight,
				Round,
				Saturate,
				Scale,
				ShiftLeft,
				Sqrt,
				SqrtEst,
				Subtract,
				SubtractAngles,
				Truncate,
				// Bit-Wise Operations
				AndCInt,
				AndInt,
				NorInt,
				NotEqual,
				NotEqualInt,
				OrInt,
				XorInt,
				// Comparison Operations
				Equal,
				EqualInt,
				EqualIntR,
				EqualR,
				Greater,
				GreaterOrEqual,
				GreaterOrEqualR,
				GreaterR,
				Less,
				LessOrEqual,
				NearEqual,
				// Component-Wise Operations
				MergeXY,
				MergeZQ,
				VertorPermute,
				PermuteControl,
				Select,
				SelectControl,
				SplatW,
				SplatX,
				SplatY,
				SplatZ,
				// Geometric Operations
				BaryCentric,
				BaryCentricV,
				CatmullRom,
				CatmullRomV,
				Hermite,
				HermiteV,
				InBounds,
				InBoundsR,
				Lerp,
				LerpV,
			};
		};

		struct Vector4 {
			enum {
				Transform = 0x00006000,
				TransformStream
			};
		};
	};

	struct ParameterDescriptor
	{
		float* Data;
	};

	struct ResultDescriptor
	{
		float* Data;
	};

	struct OpDescriptor
	{
		int Op;

		ParameterDescriptor Parameters[16];

		ResultDescriptor Result;
	};
}
