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

		/// <summary>Specifies compile- or run-time options during effect creation.</summary>
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

		/// <summary>
		/// Flags that indicate which components of a value are valid.
		/// </summary>
		[System::Flags]
		public enum class RegisterComponentMaskFlags : System::Int32
		{
			/// <summary>
			/// Indicates that no components are valid.
			/// </summary>
			None = 0,
			
			/// <summary>
			/// Indicates that the X (or R) component is valid.
			/// </summary>
			ComponentX = 1,
			
			/// <summary>
			/// Indicates that the Y (or G) component is valid.
			/// </summary>
			ComponentY = 2,
			
			/// <summary>
			/// Indicates that the Z (or B) component is valid.
			/// </summary>
			ComponentZ = 4,
			
			/// <summary>
			/// Indicates that the W (or A) component is valid.
			/// </summary>
			ComponentW = 8,
			
			/// <summary>
			/// Indicates that all components are valid.
			/// </summary>
			All = ComponentX | ComponentY | ComponentZ | ComponentW
		};
		
		/// <summary></summary>
		/// <unmanaged>D3D10_REGISTER_COMPONENT_TYPE</unmanaged>
		public enum class RegisterComponentType : System::Int32
		{
			Unknown = D3D10_REGISTER_COMPONENT_UNKNOWN,
			UInt32 = D3D10_REGISTER_COMPONENT_UINT32,
			SInt32 = D3D10_REGISTER_COMPONENT_SINT32,
			Float32 = D3D10_REGISTER_COMPONENT_FLOAT32
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

		[System::Flags]
		public enum class ShaderInputFlags : System::Int32
		{
			UserPacked = D3D10_SIF_USERPACKED,
			ComparisonSampler = D3D10_SIF_COMPARISON_SAMPLER,
			TextureComponent0 = D3D10_SIF_TEXTURE_COMPONENT_0,
			TextureComponent1 = D3D10_SIF_TEXTURE_COMPONENT_1,
			TextureComponents = D3D10_SIF_TEXTURE_COMPONENTS
		};

		public enum class ShaderInputType : System::Int32
		{
			ConstantBuffer = D3D10_SIT_CBUFFER,
			TextureBuffer = D3D10_SIT_TBUFFER,
			Texture = D3D10_SIT_TEXTURE,
			Sampler = D3D10_SIT_SAMPLER,
			Structured = D3D11_SIT_STRUCTURED,
			RWStructured = D3D11_SIT_UAV_RWSTRUCTURED,
			ByteAddress = D3D11_SIT_BYTEADDRESS,
			RWByteAddress = D3D11_SIT_UAV_RWBYTEADDRESS,
			AppendStructured = D3D11_SIT_UAV_APPEND_STRUCTURED,
			ConsumeStructured = D3D11_SIT_UAV_CONSUME_STRUCTURED,
			RWStructuredWithCounter = D3D11_SIT_UAV_RWSTRUCTURED_WITH_COUNTER
		};

		public enum class ShaderVariableClass : System::Int32
		{
			Scalar = D3D10_SVC_SCALAR,
			Vector = D3D10_SVC_VECTOR,
			MatrixRows = D3D10_SVC_MATRIX_ROWS,
			MatrixColumns = D3D10_SVC_MATRIX_COLUMNS,
			Object = D3D10_SVC_OBJECT,
			Struct = D3D10_SVC_STRUCT,
			InterfaceClass = D3D11_SVC_INTERFACE_CLASS,
			InterfacePointer = D3D11_SVC_INTERFACE_POINTER,
		};

		[System::Flags]
		public enum class ShaderVariableFlags : System::Int32
		{
			UserPacked = D3D10_SVF_USERPACKED,
			Used = D3D10_SVF_USED,
		};

		public enum class ShaderVariableType : System::Int32
		{
			Void = D3D10_SVT_VOID,
			Bool = D3D10_SVT_BOOL,
			Int = D3D10_SVT_INT,
			Float = D3D10_SVT_FLOAT,
			String = D3D10_SVT_STRING,
			Texture = D3D10_SVT_TEXTURE,
			Texture1D = D3D10_SVT_TEXTURE1D,
			Texture2D = D3D10_SVT_TEXTURE2D,
			Texture3D = D3D10_SVT_TEXTURE3D,
			TextureCube = D3D10_SVT_TEXTURECUBE,
			Sampler = D3D10_SVT_SAMPLER,
			PixelShader = D3D10_SVT_PIXELSHADER,
			VertexShader = D3D10_SVT_VERTEXSHADER,
			UInt = D3D10_SVT_UINT,
			UInt8 = D3D10_SVT_UINT8,
			GeometryShader = D3D10_SVT_GEOMETRYSHADER,
			Rasterizer = D3D10_SVT_RASTERIZER,
			DepthStencil = D3D10_SVT_DEPTHSTENCIL,
			Blend = D3D10_SVT_BLEND,
			Buffer = D3D10_SVT_BUFFER,
			CBuffer = D3D10_SVT_CBUFFER,
			TBuffer = D3D10_SVT_TBUFFER,
			Texture1DArray = D3D10_SVT_TEXTURE1DARRAY,
			Texture2DArray = D3D10_SVT_TEXTURE2DARRAY,
			RenderTargetView = D3D10_SVT_RENDERTARGETVIEW,
			DepthStencilView = D3D10_SVT_DEPTHSTENCILVIEW,
			Texture2DMS = D3D10_SVT_TEXTURE2DMS,
			Texture2DMSArray = D3D10_SVT_TEXTURE2DMSARRAY,
			TextureCubeArray = D3D10_SVT_TEXTURECUBEARRAY,
			HullShader = D3D11_SVT_HULLSHADER,
			DomainShader = D3D11_SVT_DOMAINSHADER,
			InterfacePointer = D3D11_SVT_INTERFACE_POINTER,
			ComputeShader = D3D11_SVT_COMPUTESHADER,
			Double = D3D11_SVT_DOUBLE,
			RWTexture1D = D3D11_SVT_RWTEXTURE1D,
			RWTexture1DArray = D3D11_SVT_RWTEXTURE1DARRAY,
			RWTexture2D = D3D11_SVT_RWTEXTURE2D,
			RWTexture2DArray = D3D11_SVT_RWTEXTURE2DARRAY,
			RWTexture3D = D3D11_SVT_RWTEXTURE3D,
			RWBuffer = D3D11_SVT_RWBUFFER,
			ByteAddressBuffer = D3D11_SVT_BYTEADDRESS_BUFFER,
			RWByteAddressBuffer = D3D11_SVT_RWBYTEADDRESS_BUFFER,
			StructuredBuffer = D3D11_SVT_STRUCTURED_BUFFER,
			RWStructuredBuffer = D3D11_SVT_RWSTRUCTURED_BUFFER,
			AppendStructuredBuffer = D3D11_SVT_APPEND_STRUCTURED_BUFFER,
			ConsumeStructuredBuffer = D3D11_SVT_CONSUME_STRUCTURED_BUFFER,
		};

		/// <summary>These flags identify shader parameters that use system-value semantics.</summary>
		/// <unmanaged>D3D10_NAME</unmanaged>
		public enum class SystemValueType : System::Int32
		{
			Undefined = D3D10_NAME_UNDEFINED,
			Position = D3D10_NAME_POSITION,
			ClipDistance = D3D10_NAME_CLIP_DISTANCE,
			CullDistance = D3D10_NAME_CULL_DISTANCE,
			RenderTargetArrayIndex = D3D10_NAME_RENDER_TARGET_ARRAY_INDEX,
			ViewportArrayIndex = D3D10_NAME_VIEWPORT_ARRAY_INDEX,
			VertexId = D3D10_NAME_VERTEX_ID,
			PrimitiveId = D3D10_NAME_PRIMITIVE_ID,
			InstanceId = D3D10_NAME_INSTANCE_ID,
			FrontFaceFlag = D3D10_NAME_IS_FRONT_FACE,
			SampleIndex =D3D10_NAME_SAMPLE_INDEX,
			Target = D3D10_NAME_TARGET,
			Depth = D3D10_NAME_DEPTH
		};
	}
}