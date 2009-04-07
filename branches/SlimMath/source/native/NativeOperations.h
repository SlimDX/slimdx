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
		enum Ops
		{
			//Color Operations
			ColorAdjustContrast,
			ColorAdjustSaturation,
			ColorEqual,
			ColorGreater,
			ColorGreaterOrEqual,
			ColorIsInfinite,
			ColorIsNaN,
			ColorLess,
			ColorLessOrEqual,
			ColorModulate,
			ColorNearEqual,
			ColorNegative,
			ColorNotEqual,
			//Matrix Operations
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
			MatrixOrthographicLH,
			MatrixOrthographicOffCenterLH,
			MatrixOrthographicOffCenterRH,
			MatrixOrthographicRH,
			MatrixPerspectiveFovLH,
			MatrixPerspectiveFovRH,
			MatrixPerspectiveLH,
			MatrixPerspectiveOffCenterLH,
			MatrixPerspectiveOffCenterRH,
			MatrixPerspectiveRH,
			MatrixReflect,
			MatrixRotationAxis,
			MatrixRotationNormal,
			MatrixRotationQuaternion,
			MatrixRotationRollPitchYaw,
			MatrixRotationRollPitchYawFromVector,
			MatrixRotationX,
			MatrixRotationY,
			MatrixRotationZ,
			MatrixScaling,
			MatrixScalingFromVector,
			MatrixSet,
			MatrixShadow,
			MatrixTransformation,
			MatrixTransformation2D,
			MatrixTranslation,
			MatrixTranslationFromVector,
			MatrixTranspose,
			//Plane Operations
			PlaneDot,
			PlaneDotCoord,
			PlaneDotNormal,
			PlaneEqual,
			PlaneFromPointNormal,
			PlaneFromPoints,
			PlaneIntersectLine,
			PlaneIntersectPlane,
			PlaneIsInfinite,
			PlaneIsNaN,
			PlaneNearEqual,
			PlaneNormalize,
			PlaneNormalizeEst,
			PlaneNotEqual,
			PlaneTransform,
			PlaneTransformStream,
			//Quaternion Operations
			QuaternionBaryCentric,
			QuaternionBaryCentricV,
			QuaternionConjugate,
			QuaternionDot,
			QuaternionEqual,
			QuaternionExp,
			QuaternionIdentity,
			QuaternionInverse,
			QuaternionIsIdentity,
			QuaternionIsInfinite,
			QuaternionIsNaN,
			QuaternionLength,
			QuaternionLengthSq,
			QuaternionLn,
			QuaternionMultiply,
			QuaternionNormalize,
			QuaternionNormalizeEst,
			QuaternionNotEqual,
			QuaternionReciprocalLength,
			QuaternionRotationAxis,
			QuaternionRotationMatrix,
			QuaternionRotationNormal,
			QuaternionRotationRollPitchYaw,
			QuaternionRotationRollPitchYawFromVector,
			QuaternionSlerp,
			QuaternionSlerpV,
			QuaternionSquad,
			QuaternionSquadSetup,
			QuaternionSquadV,
			QuaternionToAxisAngle,
			//Scalar Operations
			ScalarACos,
			ScalarACosEst,
			ScalarASin,
			ScalarASinEst,
			ScalarCos,
			ScalarCosEst,
			ScalarModAngle,
			ScalarNearEqual,
			ScalarSin,
			ScalarSinCos,
			ScalarSinCosEst,
			ScalarSinEst,
			//Vector Arithmetic Operations
			VectorAbs,
			VectorAdd,
			VectorAddAngles,
			VectorCeiling,
			VectorClamp,
			VectorFloor,
			VectorInsert,
			VectorIsInfinite,
			VectorIsNaN,
			VectorMax,
			VectorMin,
			VectorMod,
			VectorModAngles,
			VectorMultiply,
			VectorMultiplyAdd,
			VectorNegate,
			VectorNegativeMultiplySubstract,
			VectorPow,
			VectorPowEst,
			VectorReciprocal,
			VectorReciprocalEst,
			VectorReciprocalSqrt,
			VectorReciprocalSqrtEst,
			VectorRotateLeft,
			VectorRotateRight,
			VectorRound,
			VectorSaturate,
			VectorScale,
			VectorShiftLeft,
			VectorSqrt,
			VectorSqrtEst,
			VectorSubtract,
			VectorSubtractAngles,
			VectorTruncate,
			//Vector Bit-Wise Operations
			VectorAndCInt,
			VectorAndInt,
			VectorNorInt,
			VectorNotEqual,
			VectorNotEqualInt,
			VectorOrInt,
			VectorXorInt,
			//Vector Comparison Operations
			VectorEqual,
			VectorEqualInt,
			VectorEqualIntR,
			VectorEqualR,
			VectorGreater,
			VectorGreaterOrEqual,
			VectorGreaterOrEqualR,
			VectorGreaterR,
			VectorLess,
			VectorLessOrEqual,
			VectorNearEqual,
			//Vector Component-Wise Operations
			VectorMergeXY,
			VectorMergeZQ,
			VertorPermute,
			VectorPermuteControl,
			VectorSelect,
			VectorSelectControl,
			VectorSplatW,
			VectorSplatX,
			VectorSplatY,
			VectorSplatZ,
			//Vector Geometric Operations
			VectorBaryCentric,
			VectorBaryCentricV,
			VectorCatmullRom,
			VectorCatmullRomV,
			VectorHermite,
			VectorHermiteV,
			VectorInBounds,
			VectorInBoundsR,
			VectorLerp,
			VectorLerpV,
			//Vector4 Operations
			Vector4Transform,
			Vector4TransformStream
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
		NativeOperation::Ops Op;

		ParameterDescriptor Parameters[16];

		ResultDescriptor Result;
	};
}
