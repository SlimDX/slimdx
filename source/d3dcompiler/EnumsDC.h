/*
* Copyright (c) 2007-2010 SlimDX Group
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
#pragma once

namespace SlimDX
{
	namespace D3DCompiler
	{
		// NOTE: The enumerations defined in this file are in alphabetical order. When
		//       adding new enumerations or renaming existing ones, please make sure
		//       the ordering is maintained.

		/// <summary>Specifies compile- or run-time options during <see cref="SlimDX::Direct3D11::Effect">Effect</see> creation.</summary>
		/// <unmanaged>D3D10_EFFECT</unmanaged>
		[System::Flags]
		public enum class EffectFlags : System::Int32
		{
			/// <summary>
			/// Standard compile- and run-time behavior.
			/// </summary>
			None = 0,
			
			/// <summary>
			/// Compile the .fx file to a child effect. Child effects do not initialize shared values
			/// (as those values are instead initialized by the effect pool).
			/// </summary>
			ChildEffect = D3D10_EFFECT_COMPILE_CHILD_EFFECT,
			
			/// <summary>
			/// Allow mutable state objects (non-literal expressions may appear in state object definitions). This
			/// has a negative impact on run-time performance.
			/// </summary>
			AllowSlowOperations = D3D10_EFFECT_COMPILE_ALLOW_SLOW_OPS,
			
			/// <summary>
			/// Do not attempt to synchronize with other threads loading effects into the same pool.
			/// </summary>
			SingleThreaded = D3D10_EFFECT_SINGLE_THREADED,
		};

		/// <summary>
		/// Flags that indicate the location of an include file.
		/// </summary>
		/// <unmanaged>D3D10_INCLUDE_TYPE</unmanaged>
		[System::Flags]
		public enum class IncludeType : System::Int32
		{
			/// <summary>
			/// Indicates that the include is in the local path (or paths).
			/// </summary>
			Local = D3D10_INCLUDE_LOCAL,
			
			/// <summary>
			/// Indicates that the include is in the system path (or paths).
			/// </summary>
			System = D3D10_INCLUDE_SYSTEM
		};

		/// <summary></summary>
		/// <unmanaged>D3D10_SHADER</unmanaged>
		[System::Flags]
		public enum class ShaderFlags : System::Int32
		{
			None = 0,
			Debug = D3D10_SHADER_DEBUG,
			SkipValidation = D3D10_SHADER_SKIP_VALIDATION,
			SkipOptimization = D3D10_SHADER_SKIP_OPTIMIZATION,
			PackMatrixRowMajor = D3D10_SHADER_PACK_MATRIX_ROW_MAJOR,
			PackMatrixColumnMajor = D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR,
			PartialPrecision = D3D10_SHADER_PARTIAL_PRECISION,
			ForceSoftwareVertexShader = D3D10_SHADER_FORCE_VS_SOFTWARE_NO_OPT,
			ForceSoftwarePixelShader = D3D10_SHADER_FORCE_PS_SOFTWARE_NO_OPT,
			NoPreshader = D3D10_SHADER_NO_PRESHADER,
			AvoidFlowControl = D3D10_SHADER_AVOID_FLOW_CONTROL,
			PreferFlowControl = D3D10_SHADER_PREFER_FLOW_CONTROL,
			EnableStrictness = D3D10_SHADER_ENABLE_STRICTNESS,
			EnableBackwardsCompatibility = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY,
			EnableIEEEStrictness = D3D10_SHADER_IEEE_STRICTNESS,
			OptimizationLevel0 = D3D10_SHADER_OPTIMIZATION_LEVEL0,
			OptimizationLevel1 = D3D10_SHADER_OPTIMIZATION_LEVEL1,
			OptimizationLevel2 = D3D10_SHADER_OPTIMIZATION_LEVEL2,
			OptimizationLevel3 = D3D10_SHADER_OPTIMIZATION_LEVEL3
		};
	}
}