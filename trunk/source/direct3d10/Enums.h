/*
* Copyright (c) 2007 SlimDX Group
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

using namespace System;

namespace SlimDX
{
	namespace Direct3D10
	{
		// NOTE: The enumerations defined in this file are in alphabetical order. When
		//       adding new enumerations or renaming existing ones, please make sure
		//       the ordering is maintained.
	
		[Flags]
		public enum class BindFlags : Int32
		{
			None = 0,
			VertexBuffer = D3D10_BIND_VERTEX_BUFFER,
			IndexBuffer = D3D10_BIND_INDEX_BUFFER,
			ConstantBuffer = D3D10_BIND_CONSTANT_BUFFER,
			ShaderResource = D3D10_BIND_SHADER_RESOURCE, 
			StreamOutput = D3D10_BIND_STREAM_OUTPUT,
			RenderTarget = D3D10_BIND_RENDER_TARGET,
			DepthStencil = D3D10_BIND_DEPTH_STENCIL
		};
		
		public enum class BlendOperation : Int32
		{
			Add = D3D10_BLEND_OP_ADD,
			Subtract = D3D10_BLEND_OP_SUBTRACT,
			ReverseSubtract = D3D10_BLEND_OP_REV_SUBTRACT,
			Minimum = D3D10_BLEND_OP_MIN,
			Maximum = D3D10_BLEND_OP_MAX
		};
		
		public enum class BlendOption : Int32
		{
			Zero = D3D10_BLEND_ZERO,
			One = D3D10_BLEND_ONE,
			SourceColor = D3D10_BLEND_SRC_COLOR,
			InverseSourceColor = D3D10_BLEND_INV_SRC_COLOR,
			SourceAlpha = D3D10_BLEND_SRC_ALPHA,
			InverseSourceAlpha = D3D10_BLEND_INV_SRC_ALPHA,
			DestinationAlpha = D3D10_BLEND_DEST_ALPHA,
			InverseDestinationAlpha = D3D10_BLEND_INV_DEST_ALPHA,
			DestinationColor = D3D10_BLEND_DEST_COLOR,
			InverseDestinationColor = D3D10_BLEND_INV_DEST_COLOR,
			SourceAlphaSaturate = D3D10_BLEND_SRC_ALPHA_SAT,
			BlendFactor = D3D10_BLEND_BLEND_FACTOR,
			InverseBlendFactor = D3D10_BLEND_INV_BLEND_FACTOR,
			SecondarySourceColor = D3D10_BLEND_SRC1_COLOR,
			InverseSecondarySourceColor = D3D10_BLEND_INV_SRC1_COLOR,
			SecondarySourceAlpha = D3D10_BLEND_SRC1_ALPHA,
			InverseSecondarySourceAlpha = D3D10_BLEND_INV_SRC1_ALPHA
		};
		
		[Flags]
		public enum class ColorWriteMaskFlags
		{
			None = 0,
			Red = D3D10_COLOR_WRITE_ENABLE_RED,
			Green = D3D10_COLOR_WRITE_ENABLE_GREEN,
			Blue = D3D10_COLOR_WRITE_ENABLE_BLUE,
			Alpha = D3D10_COLOR_WRITE_ENABLE_ALPHA,
			All = D3D10_COLOR_WRITE_ENABLE_ALL
		};
		
		public enum class Comparison : Int32
		{
			Never = D3D10_COMPARISON_NEVER,
			Less = D3D10_COMPARISON_LESS,
			Equal = D3D10_COMPARISON_EQUAL,
			LessEqual = D3D10_COMPARISON_LESS_EQUAL,
			Greater = D3D10_COMPARISON_GREATER,
			NotEqual = D3D10_COMPARISON_NOT_EQUAL,
			GreaterEqual = D3D10_COMPARISON_GREATER_EQUAL,
			Always = D3D10_COMPARISON_ALWAYS
		};
		
		[Flags]
		public enum class CpuAccessFlags : Int32
		{
			None = 0,
			Write = D3D10_CPU_ACCESS_WRITE,
			Read = D3D10_CPU_ACCESS_READ
		};
		
		public enum class CullMode : Int32 
		{
			None = D3D10_CULL_NONE,
			Front = D3D10_CULL_FRONT,
			Back = D3D10_CULL_BACK
		};
		
		[Flags]
		public enum class DepthStencilClearFlags : Int32
		{
			Depth = D3D10_CLEAR_DEPTH,
			Stencil = D3D10_CLEAR_STENCIL
		};
		
		public enum class DepthWriteMask : Int32
		{
			Zero = D3D10_DEPTH_WRITE_MASK_ZERO,
			All = D3D10_DEPTH_WRITE_MASK_ALL
		};
		
		[Flags]
		public enum class DeviceCreationFlags : Int32
		{
			None = 0,
			SingleThreaded = D3D10_CREATE_DEVICE_SINGLETHREADED,
			Debug = D3D10_CREATE_DEVICE_DEBUG,
			SwitchToRef = D3D10_CREATE_DEVICE_SWITCH_TO_REF,
			PreventThreadingOptimizations = D3D10_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS
		};
	
		public enum class DisplayModeRotation : Int32
		{
			Unspecified = DXGI_MODE_ROTATION_UNSPECIFIED,
			Identity = DXGI_MODE_ROTATION_IDENTITY,
			Rotate90Degrees = DXGI_MODE_ROTATION_ROTATE90,
			Rotate180Degrees = DXGI_MODE_ROTATION_ROTATE180,
			Rotate270Degrees = DXGI_MODE_ROTATION_ROTATE270
		};

		public enum class DisplayModeScaling : Int32
		{
			Unspecified = DXGI_MODE_SCALING_UNSPECIFIED,
			Centered = DXGI_MODE_SCALING_CENTERED,
			Stretched = DXGI_MODE_SCALING_STRETCHED
		};

		public enum class DisplayModeScanlineOrdering : Int32
		{
			Unspecified = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
			Progressive = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE,
			UpperFieldFirst = DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST,
			LowerFieldFirst = DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST
		};
		
		public enum class DriverType : Int32
		{
			Hardware = D3D10_DRIVER_TYPE_HARDWARE,
			Reference = D3D10_DRIVER_TYPE_REFERENCE,
			Null = D3D10_DRIVER_TYPE_NULL,
			Software = D3D10_DRIVER_TYPE_SOFTWARE
		};

		[Flags]
		public enum class EffectFlags : Int32
		{
			None = 0,
			ChildEffect = D3D10_EFFECT_COMPILE_CHILD_EFFECT,
			AllowSlowOperations = D3D10_EFFECT_COMPILE_ALLOW_SLOW_OPS,
			SingleThreaded = D3D10_EFFECT_SINGLE_THREADED,
		};

		[Flags]
		public enum class EffectVariableFlags : Int32
		{
			None = 0,
			Annotation = D3D10_EFFECT_VARIABLE_ANNOTATION,
			Pooled = D3D10_EFFECT_VARIABLE_POOLED,
			ExplicitBindPoint = D3D10_EFFECT_VARIABLE_EXPLICIT_BIND_POINT,
		};
		
		public enum class FillMode : Int32
		{
			Wireframe = D3D10_FILL_WIREFRAME,
			Solid = D3D10_FILL_SOLID
		};
		
		public enum class Format : Int32
		{
			Unknown = DXGI_FORMAT_UNKNOWN,
			R32G32B32A32_Typeless = DXGI_FORMAT_R32G32B32A32_TYPELESS,
			R32G32B32A32_Float = DXGI_FORMAT_R32G32B32A32_FLOAT,
			R32G32B32A32_UInt = DXGI_FORMAT_R32G32B32A32_UINT,
			R32G32B32A32_SInt = DXGI_FORMAT_R32G32B32A32_SINT,
			R32G32B32_Typeless = DXGI_FORMAT_R32G32B32_TYPELESS,
			R32G32B32_Float = DXGI_FORMAT_R32G32B32_FLOAT,
			R32G32B32_UInt = DXGI_FORMAT_R32G32B32_UINT,
			R32G32B32_SInt = DXGI_FORMAT_R32G32B32_SINT,
			R16G16B16A16_Typeless = DXGI_FORMAT_R16G16B16A16_TYPELESS,
			R16G16B16A16_Float = DXGI_FORMAT_R16G16B16A16_FLOAT,
			R16G16B16A16_UNorm = DXGI_FORMAT_R16G16B16A16_UNORM,
			R16G16B16A16_UInt = DXGI_FORMAT_R16G16B16A16_UINT,
			R16G16B16A16_SNorm = DXGI_FORMAT_R16G16B16A16_SNORM,
			R16G16B16A16_SInt = DXGI_FORMAT_R16G16B16A16_SINT,
			R32G32_Typeless = DXGI_FORMAT_R32G32_TYPELESS,
			R32G32_Float = DXGI_FORMAT_R32G32_FLOAT,
			R32G32_UInt = DXGI_FORMAT_R32G32_UINT,
			R32G32_SInt = DXGI_FORMAT_R32G32_SINT,
			R32G8X24_Typeless = DXGI_FORMAT_R32G8X24_TYPELESS,
			D32_Float_S8X24_UInt = DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
			R32_Float_X8X24_Typeless = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,
			X32_Typeless_G8X24_UInt = DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,
			R10G10B10A2_Typeless = DXGI_FORMAT_R10G10B10A2_TYPELESS,
			R10G10B10A2_UNorm = DXGI_FORMAT_R10G10B10A2_UNORM,
			R10G10B10A2_UInt = DXGI_FORMAT_R10G10B10A2_UINT,
			R11G11B10_Float = DXGI_FORMAT_R11G11B10_FLOAT,
			R8G8B8A8_Typeless = DXGI_FORMAT_R8G8B8A8_TYPELESS,
			R8G8B8A8_UNorm = DXGI_FORMAT_R8G8B8A8_UNORM,
			R8G8B8A8_UNorm_SRGB = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
			R8G8B8A8_UInt = DXGI_FORMAT_R8G8B8A8_UINT,
			R8G8B8A8_SNorm = DXGI_FORMAT_R8G8B8A8_SNORM,
			R8G8B8A8_SInt = DXGI_FORMAT_R8G8B8A8_SINT,
			R16G16_Typeless = DXGI_FORMAT_R16G16_TYPELESS,
			R16G16_Float = DXGI_FORMAT_R16G16_FLOAT,
			R16G16_UNorm = DXGI_FORMAT_R16G16_UNORM,
			R16G16_UInt = DXGI_FORMAT_R16G16_UINT,
			R16G16_SNorm = DXGI_FORMAT_R16G16_SNORM,
			R16G16_SInt = DXGI_FORMAT_R16G16_SINT,
			R32_Typeless = DXGI_FORMAT_R32_TYPELESS,
			D32_Float = DXGI_FORMAT_D32_FLOAT,
			R32_Float = DXGI_FORMAT_R32_FLOAT,
			R32_UInt = DXGI_FORMAT_R32_UINT,
			R32_SInt = DXGI_FORMAT_R32_SINT,
			R24G8_Typeless = DXGI_FORMAT_R24G8_TYPELESS,
			D24_UNorm_S8_UInt = DXGI_FORMAT_D24_UNORM_S8_UINT,
			R24_UNorm_X8_Typeless = DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
			X24_Typeless_G8_UInt = DXGI_FORMAT_X24_TYPELESS_G8_UINT,
			R8G8_Typeless = DXGI_FORMAT_R8G8_TYPELESS,
			R8G8_UNorm = DXGI_FORMAT_R8G8_UNORM,
			R8G8_UInt = DXGI_FORMAT_R8G8_UINT,
			R8G8_SNorm = DXGI_FORMAT_R8G8_SNORM ,
			R8G8_SInt = DXGI_FORMAT_R8G8_SINT,
			R16_Typeless = DXGI_FORMAT_R16_TYPELESS,
			R16_Float = DXGI_FORMAT_R16_FLOAT,
			D16_UNorm = DXGI_FORMAT_D16_UNORM,
			R16_UNorm = DXGI_FORMAT_R16_UNORM,
			R16_UInt = DXGI_FORMAT_R16_UINT ,
			R16_SNorm = DXGI_FORMAT_R16_SNORM ,
			R16_SInt = DXGI_FORMAT_R16_SINT,
			R8_Typeless = DXGI_FORMAT_R8_TYPELESS,
			R8_UNorm = DXGI_FORMAT_R8_UNORM,
			R8_UInt = DXGI_FORMAT_R8_UINT,
			R8_SNorm = DXGI_FORMAT_R8_SNORM,
			R8_SInt = DXGI_FORMAT_R8_SINT,
			A8_UNorm = DXGI_FORMAT_A8_UNORM,
			R1_UNorm = DXGI_FORMAT_R1_UNORM,
			R9G9B9E5_SharedExp = DXGI_FORMAT_R9G9B9E5_SHAREDEXP,
			R8G8_B8G8_UNorm = DXGI_FORMAT_R8G8_B8G8_UNORM,
			G8R8_G8B8_UNorm = DXGI_FORMAT_G8R8_G8B8_UNORM,
			BC1_Typeless = DXGI_FORMAT_BC1_TYPELESS,
			BC1_UNorm = DXGI_FORMAT_BC1_UNORM,
			BC1_UNorm_SRGB = DXGI_FORMAT_BC1_UNORM_SRGB,
			BC2_Typeless = DXGI_FORMAT_BC2_TYPELESS,
			BC2_UNorm = DXGI_FORMAT_BC2_UNORM,
			BC2_UNorm_SRGB = DXGI_FORMAT_BC2_UNORM_SRGB,
			BC3_Typeless = DXGI_FORMAT_BC3_TYPELESS,
			BC3_UNorm = DXGI_FORMAT_BC3_UNORM,
			BC3_UNorm_SRGB = DXGI_FORMAT_BC3_UNORM_SRGB,
			BC4_Typeless = DXGI_FORMAT_BC4_TYPELESS,
			BC4_UNorm = DXGI_FORMAT_BC4_UNORM,
			BC4_SNorm = DXGI_FORMAT_BC4_SNORM,
			BC5_Typeless = DXGI_FORMAT_BC5_TYPELESS,
			BC5_UNorm = DXGI_FORMAT_BC5_UNORM,
			BC5_SNorm = DXGI_FORMAT_BC5_SNORM,
			B5G6R5_UNorm = DXGI_FORMAT_B5G6R5_UNORM,
			B5G5R5A1_UNorm = DXGI_FORMAT_B5G5R5A1_UNORM,
			B8G8R8A8_UNorm = DXGI_FORMAT_B8G8R8A8_UNORM,
			B8G8R8X8_UNorm = DXGI_FORMAT_B8G8R8X8_UNORM
		};

		public enum class InputClassification : Int32
		{
			PerVertexData = D3D10_INPUT_PER_VERTEX_DATA,
			PerInstanceData = D3D10_INPUT_PER_INSTANCE_DATA
		};
		
		public enum class MapMode : Int32
		{
			Read = D3D10_MAP_READ,
			Write = D3D10_MAP_WRITE,
			ReadWrite = D3D10_MAP_READ_WRITE,
			WriteDiscard = D3D10_MAP_WRITE_DISCARD,
			WriteNoOverwrite = D3D10_MAP_WRITE_NO_OVERWRITE
		};
		
		[Flags]
		public enum class MapFlags : Int32
		{
			None = 0,
			DoNotWait = D3D10_MAP_FLAG_DO_NOT_WAIT
		};

		[Flags]
		public enum class PresentFlags : Int32
		{
			None = 0,
			DoNotSequence = DXGI_PRESENT_DO_NOT_SEQUENCE,
			Restart = DXGI_PRESENT_RESTART,
			Test = DXGI_PRESENT_TEST
		};

		public enum class PresentResult : Int32
		{
			Okay = S_OK,
			Occluded = DXGI_STATUS_OCCLUDED,
			Failed
		};
		
		public enum class PrimitiveTopology : Int32
		{
			Undefined = D3D10_PRIMITIVE_TOPOLOGY_UNDEFINED,
			PointList = D3D10_PRIMITIVE_TOPOLOGY_POINTLIST,
			LineList = D3D10_PRIMITIVE_TOPOLOGY_LINELIST,
			LineStrip = D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP,
			TriangleList = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			TriangleStrip = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
			LineListWithAdjacency = D3D10_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
			LineStripWithAdjacency = D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
			TriangleListWithAdjacency = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
			TriangleStripWithAdjacency = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ
		};

		public enum class Residency : Int32
		{
			FullyResident = DXGI_RESIDENCY_FULLY_RESIDENT,
			ResidentInSharedMemory = DXGI_RESIDENCY_RESIDENT_IN_SHARED_MEMORY,
			EvictedToDisk = DXGI_RESIDENCY_EVICTED_TO_DISK
		};

		public enum class ResourceDimension : Int32
		{
			Unknown = D3D10_RESOURCE_DIMENSION_UNKNOWN,
			Buffer = D3D10_RESOURCE_DIMENSION_BUFFER,
			Texture1D = D3D10_RESOURCE_DIMENSION_TEXTURE1D,
			Texture2D = D3D10_RESOURCE_DIMENSION_TEXTURE2D,
			Texture3D = D3D10_RESOURCE_DIMENSION_TEXTURE3D
		};
		
		
		[Flags]
		public enum class ResourceOptionFlags : Int32
		{
			None = 0,
			GenerateMipMaps = D3D10_RESOURCE_MISC_GENERATE_MIPS,
			Shared = D3D10_RESOURCE_MISC_SHARED,
			TextureCube = D3D10_RESOURCE_MISC_TEXTURECUBE
		};
		
		public enum class ResourcePriority : UInt32
		{
			Minimum = DXGI_RESOURCE_PRIORITY_MINIMUM,
			Low = DXGI_RESOURCE_PRIORITY_LOW,
			Normal = DXGI_RESOURCE_PRIORITY_NORMAL,
			High = DXGI_RESOURCE_PRIORITY_HIGH,
			Maximum = DXGI_RESOURCE_PRIORITY_MAXIMUM
		};
		
		public enum class ResourceUsage : Int32
		{
			Default = D3D10_USAGE_DEFAULT,
			Immutable = D3D10_USAGE_IMMUTABLE,
			Dynamic = D3D10_USAGE_DYNAMIC,
			Staging = D3D10_USAGE_STAGING
		};
		
		public enum class ResourceViewDimension : Int32
		{
			Unknown = D3D10_RTV_DIMENSION_UNKNOWN,
			Buffer = D3D10_RTV_DIMENSION_BUFFER,
			Texture1D = D3D10_RTV_DIMENSION_TEXTURE1D,
			Texture1DArray = D3D10_RTV_DIMENSION_TEXTURE1DARRAY,
			Texture2D = D3D10_RTV_DIMENSION_TEXTURE2D,
			Texture2DArray = D3D10_RTV_DIMENSION_TEXTURE2DARRAY,
			Texture2DMultisampled = D3D10_RTV_DIMENSION_TEXTURE2DMS,
			Texture2DMultisampledArray = D3D10_RTV_DIMENSION_TEXTURE2DMSARRAY,
			Texture3D = D3D10_RTV_DIMENSION_TEXTURE3D
		};
		
		[Flags]
		public enum class ShaderFlags : Int32
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
		
		public enum class StencilOperation
		{
			Keep = D3D10_STENCIL_OP_KEEP,
			Zero = D3D10_STENCIL_OP_ZERO,
			Replace = D3D10_STENCIL_OP_REPLACE,
			IncrementAndClamp = D3D10_STENCIL_OP_INCR_SAT,
			DecrementAndClamp = D3D10_STENCIL_OP_DECR_SAT,
			Invert = D3D10_STENCIL_OP_INVERT,
			Increment = D3D10_STENCIL_OP_INCR,
			Decrement = D3D10_STENCIL_OP_DECR
		};

		public enum class SurfaceUsage : Int32
		{
			ShaderInput = DXGI_USAGE_SHADER_INPUT,
			RenderTargetOutput = DXGI_USAGE_RENDER_TARGET_OUTPUT,
			BackBuffer = DXGI_USAGE_BACK_BUFFER,
			Shared = DXGI_USAGE_SHARED,
			ReadOnly = DXGI_USAGE_READ_ONLY 
		};
		
		public enum class SwapChainFlags : Int32
		{
			None = 0,
			NonPrerotated = DXGI_SWAP_CHAIN_FLAG_NONPREROTATED,
			AllowModeSwitch = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
		};

		public enum class SwapEffect : Int32
		{
			Discard = DXGI_SWAP_EFFECT_DISCARD,
			Sequential = DXGI_SWAP_EFFECT_SEQUENTIAL
		};
		
		///@TODO D3D10: Not so sure about this. Can this be moved to the shared utils?
		ref class Utils sealed
		{
		private:
			Utils() { }

			static int ElementSizeOf( Format format )
			{
				const int size8 = sizeof( System::Byte );
				const int size16 = sizeof( System::Int16 );
				const int size32 = sizeof( System::Int32 );
				
				switch( format )
				{
					case Format::R32G32B32A32_Typeless:
					case Format::R32G32B32A32_Float:
					case Format::R32G32B32A32_UInt:
					case Format::R32G32B32A32_SInt:
						return size32 * 4;
					case Format::R32G32B32_Typeless:
					case Format::R32G32B32_Float:
					case Format::R32G32B32_UInt:
					case Format::R32G32B32_SInt:
						return size32 * 3;
					case Format::R32G32_Typeless:
					case Format::R32G32_Float:
					case Format::R32G32_UInt:
					case Format::R32G32_SInt:
					case Format::R32G8X24_Typeless:
					case Format::D32_Float_S8X24_UInt:
					case Format::R32_Float_X8X24_Typeless:
					case Format::X32_Typeless_G8X24_UInt:
					case Format::R16G16B16A16_Typeless:
					case Format::R16G16B16A16_Float:
					case Format::R16G16B16A16_UNorm:
					case Format::R16G16B16A16_UInt:
					case Format::R16G16B16A16_SNorm:
					case Format::R16G16B16A16_SInt:
						return size32 * 2;
					case Format::R10G10B10A2_Typeless:
					case Format::R10G10B10A2_UNorm:
					case Format::R10G10B10A2_UInt:
					case Format::R11G11B10_Float:
					case Format::R8G8B8A8_Typeless:
					case Format::R8G8B8A8_UNorm:
					case Format::R8G8B8A8_UNorm_SRGB:
					case Format::R8G8B8A8_UInt:
					case Format::R8G8B8A8_SNorm:
					case Format::R8G8B8A8_SInt:
					case Format::R16G16_Typeless:
					case Format::R16G16_Float:
					case Format::R16G16_UNorm:
					case Format::R16G16_UInt:
					case Format::R16G16_SNorm:
					case Format::R16G16_SInt:
					case Format::R32_Typeless:
					case Format::D32_Float:
					case Format::R32_Float:
					case Format::R32_UInt:
					case Format::R32_SInt:
					case Format::R24G8_Typeless:
					case Format::D24_UNorm_S8_UInt:
					case Format::R24_UNorm_X8_Typeless:
					case Format::X24_Typeless_G8_UInt:
					case Format::R9G9B9E5_SharedExp:
					case Format::R8G8_B8G8_UNorm:
					case Format::G8R8_G8B8_UNorm:
					case Format::B8G8R8A8_UNorm:
					case Format::B8G8R8X8_UNorm:
						return size32;
					case Format::R8G8_Typeless:
					case Format::R8G8_UNorm:
					case Format::R8G8_UInt:
					case Format::R8G8_SNorm:
					case Format::R8G8_SInt:
					case Format::R16_Typeless:
					case Format::R16_Float:
					case Format::D16_UNorm:
					case Format::R16_UNorm:
					case Format::R16_UInt:
					case Format::R16_SNorm:
					case Format::R16_SInt:
					case Format::B5G6R5_UNorm:
					case Format::B5G5R5A1_UNorm:
						return size16;
					case Format::R8_Typeless:
					case Format::R8_UNorm:
					case Format::R8_UInt:
					case Format::R8_SNorm:
					case Format::R8_SInt:
					case Format::A8_UNorm:
						return size8;
					case Format::R1_UNorm:
					case Format::BC1_Typeless:
					case Format::BC1_UNorm:
					case Format::BC1_UNorm_SRGB:
					case Format::BC2_Typeless:
					case Format::BC2_UNorm:
					case Format::BC2_UNorm_SRGB:
					case Format::BC3_Typeless:
					case Format::BC3_UNorm:
					case Format::BC3_UNorm_SRGB:
					case Format::BC4_Typeless:
					case Format::BC4_UNorm:
					case Format::BC4_SNorm:
					case Format::BC5_Typeless:
					case Format::BC5_UNorm:
					case Format::BC5_SNorm:
						return 0;
					default:
						return 0;
				}
			}
		};
	}
}