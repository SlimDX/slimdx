/*
* Copyright (c) 2007-2008 SlimDX Group
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

#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>

namespace SlimDX
{
	namespace Direct3D10
	{
		// NOTE: The enumerations defined in this file are in alphabetical order. When
		//       adding new enumerations or renaming existing ones, please make sure
		//       the ordering is maintained.
		
		[System::Flags]
		public enum class AsynchronousFlags : System::Int32
		{
			None = 0,
			DoNotFlush = D3D10_ASYNC_GETDATA_DONOTFLUSH
		};
		
		[System::Flags]
		public enum class BindFlags : System::Int32
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
		
		public enum class BlendOperation : System::Int32
		{
			Add = D3D10_BLEND_OP_ADD,
			Subtract = D3D10_BLEND_OP_SUBTRACT,
			ReverseSubtract = D3D10_BLEND_OP_REV_SUBTRACT,
			Minimum = D3D10_BLEND_OP_MIN,
			Maximum = D3D10_BLEND_OP_MAX
		};
		
		public enum class BlendOption : System::Int32
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
		
		[System::Flags]
		public enum class ColorWriteMaskFlags : System::Int32
		{
			None = 0,
			Red = D3D10_COLOR_WRITE_ENABLE_RED,
			Green = D3D10_COLOR_WRITE_ENABLE_GREEN,
			Blue = D3D10_COLOR_WRITE_ENABLE_BLUE,
			Alpha = D3D10_COLOR_WRITE_ENABLE_ALPHA,
			All = D3D10_COLOR_WRITE_ENABLE_ALL
		};
		
		public enum class Comparison : System::Int32
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
		
		public enum class CounterKind : System::Int32
		{
			Idle = D3D10_COUNTER_GPU_IDLE,
			VertexProcessing = D3D10_COUNTER_VERTEX_PROCESSING,
			GeometryProcessing = D3D10_COUNTER_GEOMETRY_PROCESSING,
			PixelProcessing = D3D10_COUNTER_PIXEL_PROCESSING,
			OtherProcessing = D3D10_COUNTER_OTHER_GPU_PROCESSING,
			HostAdapterBandwidth = D3D10_COUNTER_HOST_ADAPTER_BANDWIDTH_UTILIZATION,
			LocalVideoMemoryBandwidth = D3D10_COUNTER_LOCAL_VIDMEM_BANDWIDTH_UTILIZATION,
			VertexThroughput = D3D10_COUNTER_VERTEX_THROUGHPUT_UTILIZATION,
			TriangleSetupThroughput = D3D10_COUNTER_TRIANGLE_SETUP_THROUGHPUT_UTILIZATION,
			FillRateThroughput = D3D10_COUNTER_FILLRATE_THROUGHPUT_UTILIZATION,
			VertexShaderMemoryLimited = D3D10_COUNTER_VS_MEMORY_LIMITED,
			VertexShaderComputationLimited = D3D10_COUNTER_VS_COMPUTATION_LIMITED,
			GeometryShaderMemoryLimited = D3D10_COUNTER_GS_MEMORY_LIMITED,
			GeometryShaderComputationLimited = D3D10_COUNTER_GS_COMPUTATION_LIMITED,
			PixelShaderMemoryLimited = D3D10_COUNTER_PS_MEMORY_LIMITED,
			PixelShaderComputationLimited = D3D10_COUNTER_PS_COMPUTATION_LIMITED,
			PostTransformCacheHitRate = D3D10_COUNTER_POST_TRANSFORM_CACHE_HIT_RATE,
			TextureCacheHitRate = D3D10_COUNTER_TEXTURE_CACHE_HIT_RATE
		};
		
		public enum class CounterType : System::Int32
		{
			Float32 = D3D10_COUNTER_TYPE_FLOAT32,
			UnsignedInt16 = D3D10_COUNTER_TYPE_UINT16,
			UnsignedInt32 = D3D10_COUNTER_TYPE_UINT32, 
			UnsignedInt64 = D3D10_COUNTER_TYPE_UINT64
		};
		
		[System::Flags]
		public enum class CpuAccessFlags : System::Int32
		{
			None = 0,
			Write = D3D10_CPU_ACCESS_WRITE,
			Read = D3D10_CPU_ACCESS_READ
		};
		
		public enum class CullMode : System::Int32 
		{
			None = D3D10_CULL_NONE,
			Front = D3D10_CULL_FRONT,
			Back = D3D10_CULL_BACK
		};
		
		[System::Flags]
		public enum class DebugFeatureFlags : System::Int32
		{
			FinishPerRender = D3D10_DEBUG_FEATURE_FINISH_PER_RENDER_OP,
			FlushPerRender = D3D10_DEBUG_FEATURE_FLUSH_PER_RENDER_OP,
			PresentPerRender = D3D10_DEBUG_FEATURE_PRESENT_PER_RENDER_OP
		};
		
		[System::Flags]
		public enum class DepthStencilClearFlags : System::Int32
		{
			Depth = D3D10_CLEAR_DEPTH,
			Stencil = D3D10_CLEAR_STENCIL
		};
		
		public enum class DepthStencilViewDimension : System::Int32
		{
			Unknown = D3D10_DSV_DIMENSION_UNKNOWN,
			Texture1D = D3D10_DSV_DIMENSION_TEXTURE1D,
			Texture1DArray = D3D10_DSV_DIMENSION_TEXTURE1DARRAY,
			Texture2D = D3D10_DSV_DIMENSION_TEXTURE2D,
			Texture2DArray = D3D10_DSV_DIMENSION_TEXTURE2DARRAY,
			Texture2DMultisampled = D3D10_DSV_DIMENSION_TEXTURE2DMS,
			Texture2DMultisampledArray = D3D10_DSV_DIMENSION_TEXTURE2DMSARRAY
		};
		
		public enum class DepthWriteMask : System::Int32
		{
			Zero = D3D10_DEPTH_WRITE_MASK_ZERO,
			All = D3D10_DEPTH_WRITE_MASK_ALL
		};
		
		[System::Flags]
		public enum class DeviceCreationFlags : System::Int32
		{
			None = 0,
			SingleThreaded = D3D10_CREATE_DEVICE_SINGLETHREADED,
			Debug = D3D10_CREATE_DEVICE_DEBUG,
			SwitchToRef = D3D10_CREATE_DEVICE_SWITCH_TO_REF,
			PreventThreadingOptimizations = D3D10_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS
		};
	
		public enum class DriverType : System::Int32
		{
			Hardware = D3D10_DRIVER_TYPE_HARDWARE,
			Reference = D3D10_DRIVER_TYPE_REFERENCE,
			Null = D3D10_DRIVER_TYPE_NULL,
			Software = D3D10_DRIVER_TYPE_SOFTWARE
		};

		[System::Flags]
		public enum class EffectFlags : System::Int32
		{
			None = 0,
			ChildEffect = D3D10_EFFECT_COMPILE_CHILD_EFFECT,
			AllowSlowOperations = D3D10_EFFECT_COMPILE_ALLOW_SLOW_OPS,
			SingleThreaded = D3D10_EFFECT_SINGLE_THREADED,
		};

		[System::Flags]
		public enum class EffectVariableFlags : System::Int32
		{
			None = 0,
			Annotation = D3D10_EFFECT_VARIABLE_ANNOTATION,
			Pooled = D3D10_EFFECT_VARIABLE_POOLED,
			ExplicitBindPoint = D3D10_EFFECT_VARIABLE_EXPLICIT_BIND_POINT,
		};
		
		public enum class FillMode : System::Int32
		{
			Wireframe = D3D10_FILL_WIREFRAME,
			Solid = D3D10_FILL_SOLID
		};
	
		public enum class FontCharacterSet : System::Int32
		{
			Ansi = ANSI_CHARSET,
			Default = DEFAULT_CHARSET,
			Symbol = SYMBOL_CHARSET,
			ShiftJIS = SHIFTJIS_CHARSET,
			Hangul = HANGUL_CHARSET,
			GB2312 = GB2312_CHARSET,
			ChineseBig5 = CHINESEBIG5_CHARSET,
			Oem = OEM_CHARSET,

			Johab = JOHAB_CHARSET,
			Hebrew = HEBREW_CHARSET,
			Arabic = ARABIC_CHARSET,
			Greek = GREEK_CHARSET,
			Turkish = TURKISH_CHARSET,
			Vietnamese = VIETNAMESE_CHARSET,
			Thai = THAI_CHARSET,
			EastEurope = EASTEUROPE_CHARSET,
			Russian = RUSSIAN_CHARSET,

			Baltic = BALTIC_CHARSET,
			Mac = MAC_CHARSET
		};

		[System::Flags]
		public enum class FontDrawFlags : System::Int32
		{
			Bottom = DT_BOTTOM,
			CalculateBounds = DT_CALCRECT,
			Center = DT_CENTER,
			ExpandTabs = DT_EXPANDTABS,
			Left = DT_LEFT,
			NoClip = DT_NOCLIP,
			Right = DT_RIGHT,
			RightToLeftReading = DT_RTLREADING,
			SingleLine = DT_SINGLELINE,
			Top = DT_TOP,
			VerticalCenter = DT_VCENTER,
			Wordbreak = DT_WORDBREAK
		};
		
		[System::Flags]
		public enum class FontPitchAndFamily : System::Int32
		{
			Default = DEFAULT_PITCH,
			Fixed = FIXED_PITCH,
			Variable = VARIABLE_PITCH,
			Mono = MONO_FONT,

			DoNotCare = FF_DONTCARE,
			Roman = FF_ROMAN,
			Swiss = FF_SWISS,
			Modern = FF_MODERN,
			Script = FF_SCRIPT,
			Decorative = FF_DECORATIVE
		};

		public enum class FontPrecision : System::Int32
		{
			Default = OUT_DEFAULT_PRECIS,
			String = OUT_STRING_PRECIS,
			Character = OUT_CHARACTER_PRECIS,
			Stroke = OUT_STROKE_PRECIS,
			TrueType = OUT_TT_PRECIS,
			Device = OUT_DEVICE_PRECIS,
			Raster = OUT_RASTER_PRECIS,
			TrueTypeOnly = OUT_TT_ONLY_PRECIS,
			Outline = OUT_OUTLINE_PRECIS,
			ScreenOutline = OUT_SCREEN_OUTLINE_PRECIS,
			PostScriptOnly = OUT_PS_ONLY_PRECIS
		};

		public enum class FontQuality : System::Int32
		{
			Default = DEFAULT_QUALITY,
			Draft = DRAFT_QUALITY,
			Proof = PROOF_QUALITY,
			NonAntialiased = NONANTIALIASED_QUALITY,
			Antialiased = ANTIALIASED_QUALITY,
			ClearType = CLEARTYPE_QUALITY,
			ClearTypeNatural = CLEARTYPE_NATURAL_QUALITY
		};

		public enum class FontWeight : System::Int32
		{
			DoNotCare = FW_DONTCARE,
			Thin = FW_THIN,
			ExtraLight = FW_EXTRALIGHT,
			UltraLight = FW_ULTRALIGHT,
			Light = FW_LIGHT,
			Normal = FW_NORMAL,
			Regular = FW_REGULAR,
			Medium = FW_MEDIUM,
			SemiBold = FW_SEMIBOLD,
			DemiBold = FW_DEMIBOLD,
			Bold = FW_BOLD,
			ExtraBold = FW_EXTRABOLD,
			UltraBold = FW_ULTRABOLD,
			Heavy = FW_HEAVY,
			Black = FW_BLACK
		};
		
		[System::Flags]
		public enum class FormatSupport : System::Int32
		{
			Buffer = D3D10_FORMAT_SUPPORT_BUFFER,
			VertexBuffer = D3D10_FORMAT_SUPPORT_IA_VERTEX_BUFFER,
			IndexBuffer = D3D10_FORMAT_SUPPORT_IA_INDEX_BUFFER,
			StreamOutputBuffer = D3D10_FORMAT_SUPPORT_SO_BUFFER,
			Texture1D = D3D10_FORMAT_SUPPORT_TEXTURE1D,
			Texture2D = D3D10_FORMAT_SUPPORT_TEXTURE2D,
			Texture3D = D3D10_FORMAT_SUPPORT_TEXTURE3D,
			TextureCube = D3D10_FORMAT_SUPPORT_TEXTURECUBE,
			ShaderLoadIntrinsic = D3D10_FORMAT_SUPPORT_SHADER_LOAD,
			ShaderSampleIntrinsic = D3D10_FORMAT_SUPPORT_SHADER_SAMPLE,
			ShaderSampleComparisonIntrinsic = D3D10_FORMAT_SUPPORT_SHADER_SAMPLE_COMPARISON,
			Reserved = D3D10_FORMAT_SUPPORT_SHADER_SAMPLE_MONO_TEXT,
			MipMap = D3D10_FORMAT_SUPPORT_MIP,
			MipMapAutoGeneration = D3D10_FORMAT_SUPPORT_MIP_AUTOGEN,
			RenderTarget = D3D10_FORMAT_SUPPORT_RENDER_TARGET,
			BlendOperation = D3D10_FORMAT_SUPPORT_BLENDABLE,
			DepthStencil = D3D10_FORMAT_SUPPORT_DEPTH_STENCIL,
			CpuLocking = D3D10_FORMAT_SUPPORT_CPU_LOCKABLE,
			MultisampleResolve = D3D10_FORMAT_SUPPORT_MULTISAMPLE_RESOLVE,
			FormatDisplaySupport = D3D10_FORMAT_SUPPORT_DISPLAY,
			FormatCastSupport = D3D10_FORMAT_SUPPORT_CAST_WITHIN_BIT_LAYOUT,
			FormatMultisampleRenderTargetSupport = D3D10_FORMAT_SUPPORT_MULTISAMPLE_RENDERTARGET,
			FormatMultisampleLoadSupport = D3D10_FORMAT_SUPPORT_MULTISAMPLE_LOAD
		};
		
		public enum class ImageFileFormat : System::Int32
		{
			Bmp = D3DX10_IFF_BMP,
			Jpg = D3DX10_IFF_JPG,
			Png = D3DX10_IFF_PNG,
			Dds = D3DX10_IFF_DDS,
			Tiff = D3DX10_IFF_TIFF,
			Gif = D3DX10_IFF_GIF,
			Wmp = D3DX10_IFF_WMP,
		};

		public enum class InputClassification : System::Int32
		{
			PerVertexData = D3D10_INPUT_PER_VERTEX_DATA,
			PerInstanceData = D3D10_INPUT_PER_INSTANCE_DATA
		};
		
		public enum class MapMode : System::Int32
		{
			Read = D3D10_MAP_READ,
			Write = D3D10_MAP_WRITE,
			ReadWrite = D3D10_MAP_READ_WRITE,
			WriteDiscard = D3D10_MAP_WRITE_DISCARD,
			WriteNoOverwrite = D3D10_MAP_WRITE_NO_OVERWRITE
		};
		
		[System::Flags]
		public enum class MapFlags : System::Int32
		{
			None = 0,
			DoNotWait = D3D10_MAP_FLAG_DO_NOT_WAIT
		};
		
		public enum class PrimitiveTopology : System::Int32
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
		
		public enum class RegisterComponentType : System::Int32
		{
			Unknown = D3D10_REGISTER_COMPONENT_UNKNOWN,
			UInt32 = D3D10_REGISTER_COMPONENT_UINT32,
			SInt32 = D3D10_REGISTER_COMPONENT_SINT32,
			Float32 = D3D10_REGISTER_COMPONENT_FLOAT32
		};
		
		public enum class RenderTargetViewDimension : System::Int32
		{
			Unknown = D3D10_RTV_DIMENSION_UNKNOWN,
			Buffer = D3D10_RTV_DIMENSION_BUFFER,
			Texture1D = D3D10_RTV_DIMENSION_TEXTURE1D ,
			Texture1DArray = D3D10_RTV_DIMENSION_TEXTURE1DARRAY,
			Texture2D = D3D10_RTV_DIMENSION_TEXTURE2D,
			Texture2DArray = D3D10_RTV_DIMENSION_TEXTURE2DARRAY,
			Texture2DMultisampled = D3D10_RTV_DIMENSION_TEXTURE2DMS,
			Texture2DMultisampledArray = D3D10_RTV_DIMENSION_TEXTURE2DMSARRAY,
			Texture3D = D3D10_RTV_DIMENSION_TEXTURE3D
		};
		
		public enum class ResourceDimension : System::Int32
		{
			Unknown = D3D10_RESOURCE_DIMENSION_UNKNOWN,
			Buffer = D3D10_RESOURCE_DIMENSION_BUFFER,
			Texture1D = D3D10_RESOURCE_DIMENSION_TEXTURE1D,
			Texture2D = D3D10_RESOURCE_DIMENSION_TEXTURE2D,
			Texture3D = D3D10_RESOURCE_DIMENSION_TEXTURE3D
		};
		
		[System::Flags]
		public enum class ResourceOptionFlags : System::Int32
		{
			None = 0,
			GenerateMipMaps = D3D10_RESOURCE_MISC_GENERATE_MIPS,
			Shared = D3D10_RESOURCE_MISC_SHARED,
			TextureCube = D3D10_RESOURCE_MISC_TEXTURECUBE
		};

		public enum class ResourceUsage : System::Int32
		{
			Default = D3D10_USAGE_DEFAULT,
			Immutable = D3D10_USAGE_IMMUTABLE,
			Dynamic = D3D10_USAGE_DYNAMIC,
			Staging = D3D10_USAGE_STAGING
		};
		
		public enum class ResourceViewDimension : System::Int32
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
		
		public enum class ShaderResourceViewDimension : System::Int32
		{
			Unknown = D3D10_SRV_DIMENSION_UNKNOWN,
			Buffer = D3D10_SRV_DIMENSION_BUFFER,
			Texture1D = D3D10_SRV_DIMENSION_TEXTURE1D,
			Texture1DArray = D3D10_SRV_DIMENSION_TEXTURE1DARRAY,
			Texture2D = D3D10_SRV_DIMENSION_TEXTURE2D,
			Texture2DArray = D3D10_SRV_DIMENSION_TEXTURE2DARRAY,
			Texture2DMultisampled = D3D10_SRV_DIMENSION_TEXTURE2DMS,
			Texture2DMultisampledArray = D3D10_SRV_DIMENSION_TEXTURE2DMSARRAY,
			Texture3D = D3D10_SRV_DIMENSION_TEXTURE3D,
			TextureCube = D3D10_SRV_DIMENSION_TEXTURECUBE
		};
		
#ifdef XMLDOCS
		ref class Sprite;
#endif

		/// <summary>
		/// Flags that control the behavior of <see cref="Sprite"/> rendering.
		/// </summary>
		/// <unmanaged>D3DX10_SPRITE_FLAG</unmanaged>
		[System::Flags]
		public enum class SpriteFlags : System::Int32
		{
			/// <summary>
			/// No flags.
			/// </summary>
			None = 0,

			/// <summary>
			/// Group sprites by texture before rendering; improves performance when many sprites
			/// share textures.
			/// </summary>
			GroupByTexture = D3DX10_SPRITE_SORT_TEXTURE,
			
			/// <summary>
			/// Sort the sprites from back to front based on their depth; sprites further away from the
			/// camera will be rendered first.
			/// </summary>
			SortBackToFront = D3DX10_SPRITE_SORT_DEPTH_BACK_TO_FRONT,
			
			/// <summary>
			/// Sort the sprites from front to back based on their depth; sprites closer to the
			/// camera will be rendered first.
			/// </summary>
			SortFrontToBack = D3DX10_SPRITE_SORT_DEPTH_FRONT_TO_BACK,
			
			/// <summary>
			/// Saves render state when sprites are rendered, and restores the previous state once rendering
			/// is complete.
			/// </summary>
			SaveState = D3DX10_SPRITE_SAVE_STATE,
			
			/// <summary>
			/// Increases the reference count of textures when DrawSpritesBuffered is called.
			/// </summary>
			IncreaseTextureReferenceCount = D3DX10_SPRITE_ADDREF_TEXTURES
		};

		public enum class StencilOperation : System::Int32
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