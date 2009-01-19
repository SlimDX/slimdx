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
#include <d3d11.h>
#include <d3dx11.h>

namespace SlimDX
{
	namespace Direct3D11
	{
#ifdef XMLDOCS
		ref class Sprite;
#endif
	
		// NOTE: The enumerations defined in this file are in alphabetical order. When
		//       adding new enumerations or renaming existing ones, please make sure
		//       the ordering is maintained.
		
		[System::Flags]
		public enum class AsynchronousFlags : System::Int32
		{
			None = 0,
			DoNotFlush = D3D11_ASYNC_GETDATA_DONOTFLUSH
		};
		
		[System::Flags]
		public enum class BindFlags : System::Int32
		{
			None = 0,
			VertexBuffer = D3D11_BIND_VERTEX_BUFFER,
			IndexBuffer = D3D11_BIND_INDEX_BUFFER,
			ConstantBuffer = D3D11_BIND_CONSTANT_BUFFER,
			ShaderResource = D3D11_BIND_SHADER_RESOURCE, 
			StreamOutput = D3D11_BIND_STREAM_OUTPUT,
			RenderTarget = D3D11_BIND_RENDER_TARGET,
			DepthStencil = D3D11_BIND_DEPTH_STENCIL
		};
		
		public enum class BlendOperation : System::Int32
		{
			Add = D3D11_BLEND_OP_ADD,
			Subtract = D3D11_BLEND_OP_SUBTRACT,
			ReverseSubtract = D3D11_BLEND_OP_REV_SUBTRACT,
			Minimum = D3D11_BLEND_OP_MIN,
			Maximum = D3D11_BLEND_OP_MAX
		};
		
		public enum class BlendOption : System::Int32
		{
			Zero = D3D11_BLEND_ZERO,
			One = D3D11_BLEND_ONE,
			SourceColor = D3D11_BLEND_SRC_COLOR,
			InverseSourceColor = D3D11_BLEND_INV_SRC_COLOR,
			SourceAlpha = D3D11_BLEND_SRC_ALPHA,
			InverseSourceAlpha = D3D11_BLEND_INV_SRC_ALPHA,
			DestinationAlpha = D3D11_BLEND_DEST_ALPHA,
			InverseDestinationAlpha = D3D11_BLEND_INV_DEST_ALPHA,
			DestinationColor = D3D11_BLEND_DEST_COLOR,
			InverseDestinationColor = D3D11_BLEND_INV_DEST_COLOR,
			SourceAlphaSaturate = D3D11_BLEND_SRC_ALPHA_SAT,
			BlendFactor = D3D11_BLEND_BLEND_FACTOR,
			InverseBlendFactor = D3D11_BLEND_INV_BLEND_FACTOR,
			SecondarySourceColor = D3D11_BLEND_SRC1_COLOR,
			InverseSecondarySourceColor = D3D11_BLEND_INV_SRC1_COLOR,
			SecondarySourceAlpha = D3D11_BLEND_SRC1_ALPHA,
			InverseSecondarySourceAlpha = D3D11_BLEND_INV_SRC1_ALPHA
		};
		
		[System::Flags]
		public enum class ColorWriteMaskFlags : System::Int32
		{
			None = 0,
			Red = D3D11_COLOR_WRITE_ENABLE_RED,
			Green = D3D11_COLOR_WRITE_ENABLE_GREEN,
			Blue = D3D11_COLOR_WRITE_ENABLE_BLUE,
			Alpha = D3D11_COLOR_WRITE_ENABLE_ALPHA,
			All = D3D11_COLOR_WRITE_ENABLE_ALL
		};
		
		public enum class Comparison : System::Int32
		{
			Never = D3D11_COMPARISON_NEVER,
			Less = D3D11_COMPARISON_LESS,
			Equal = D3D11_COMPARISON_EQUAL,
			LessEqual = D3D11_COMPARISON_LESS_EQUAL,
			Greater = D3D11_COMPARISON_GREATER,
			NotEqual = D3D11_COMPARISON_NOT_EQUAL,
			GreaterEqual = D3D11_COMPARISON_GREATER_EQUAL,
			Always = D3D11_COMPARISON_ALWAYS
		};
		
		// TODO: Fix
		public enum class CounterKind : System::Int32
		{
			DeviceDependent = D3D11_COUNTER_DEVICE_DEPENDENT_0
			/*
			Idle = D3D11_COUNTER_GPU_IDLE,
			VertexProcessing = D3D11_COUNTER_VERTEX_PROCESSING,
			GeometryProcessing = D3D11_COUNTER_GEOMETRY_PROCESSING,
			PixelProcessing = D3D11_COUNTER_PIXEL_PROCESSING,
			OtherProcessing = D3D11_COUNTER_OTHER_GPU_PROCESSING,
			HostAdapterBandwidth = D3D11_COUNTER_HOST_ADAPTER_BANDWIDTH_UTILIZATION,
			LocalVideoMemoryBandwidth = D3D11_COUNTER_LOCAL_VIDMEM_BANDWIDTH_UTILIZATION,
			VertexThroughput = D3D11_COUNTER_VERTEX_THROUGHPUT_UTILIZATION,
			TriangleSetupThroughput = D3D11_COUNTER_TRIANGLE_SETUP_THROUGHPUT_UTILIZATION,
			FillRateThroughput = D3D11_COUNTER_FILLRATE_THROUGHPUT_UTILIZATION,
			VertexShaderMemoryLimited = D3D11_COUNTER_VS_MEMORY_LIMITED,
			VertexShaderComputationLimited = D3D11_COUNTER_VS_COMPUTATION_LIMITED,
			GeometryShaderMemoryLimited = D3D11_COUNTER_GS_MEMORY_LIMITED,
			GeometryShaderComputationLimited = D3D11_COUNTER_GS_COMPUTATION_LIMITED,
			PixelShaderMemoryLimited = D3D11_COUNTER_PS_MEMORY_LIMITED,
			PixelShaderComputationLimited = D3D11_COUNTER_PS_COMPUTATION_LIMITED,
			PostTransformCacheHitRate = D3D11_COUNTER_POST_TRANSFORM_CACHE_HIT_RATE,
			TextureCacheHitRate = D3D11_COUNTER_TEXTURE_CACHE_HIT_RATE
			*/
		};
		
		public enum class CounterType : System::Int32
		{
			Float32 = D3D11_COUNTER_TYPE_FLOAT32,
			UnsignedInt16 = D3D11_COUNTER_TYPE_UINT16,
			UnsignedInt32 = D3D11_COUNTER_TYPE_UINT32, 
			UnsignedInt64 = D3D11_COUNTER_TYPE_UINT64
		};
		
		
		[System::Flags]
		public enum class CpuAccessFlags : System::Int32
		{
			None = 0,
			Write = D3D11_CPU_ACCESS_WRITE,
			Read = D3D11_CPU_ACCESS_READ
		};
		
		public enum class CullMode : System::Int32 
		{
			None = D3D11_CULL_NONE,
			Front = D3D11_CULL_FRONT,
			Back = D3D11_CULL_BACK
		};
		
		[System::Flags]
		public enum class DebugFeatureFlags : System::Int32
		{
			FinishPerRender = D3D11_DEBUG_FEATURE_FINISH_PER_RENDER_OP,
			FlushPerRender = D3D11_DEBUG_FEATURE_FLUSH_PER_RENDER_OP,
			PresentPerRender = D3D11_DEBUG_FEATURE_PRESENT_PER_RENDER_OP
		};
		
		[System::Flags]
		public enum class DepthStencilClearFlags : System::Int32
		{
			Depth = D3D11_CLEAR_DEPTH,
			Stencil = D3D11_CLEAR_STENCIL
		};
		
		public enum class DepthStencilViewDimension : System::Int32
		{
			Unknown = D3D11_DSV_DIMENSION_UNKNOWN,
			Texture1D = D3D11_DSV_DIMENSION_TEXTURE1D,
			Texture1DArray = D3D11_DSV_DIMENSION_TEXTURE1DARRAY,
			Texture2D = D3D11_DSV_DIMENSION_TEXTURE2D,
			Texture2DArray = D3D11_DSV_DIMENSION_TEXTURE2DARRAY,
			Texture2DMultisampled = D3D11_DSV_DIMENSION_TEXTURE2DMS,
			Texture2DMultisampledArray = D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY
		};
		
		public enum class DepthWriteMask : System::Int32
		{
			Zero = D3D11_DEPTH_WRITE_MASK_ZERO,
			All = D3D11_DEPTH_WRITE_MASK_ALL
		};
		
		[System::Flags]
		public enum class DeviceCreationFlags : System::Int32
		{
			None = 0,
			SingleThreaded = D3D11_CREATE_DEVICE_SINGLETHREADED,
			Debug = D3D11_CREATE_DEVICE_DEBUG,
			SwitchToRef = D3D11_CREATE_DEVICE_SWITCH_TO_REF,
			PreventThreadingOptimizations = D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS
		};
	
		public enum class DriverType : System::Int32
		{
			Hardware = D3D_DRIVER_TYPE_HARDWARE,
			Reference = D3D_DRIVER_TYPE_REFERENCE,
			Null = D3D_DRIVER_TYPE_NULL,
			Software = D3D_DRIVER_TYPE_SOFTWARE
		};

		// TODO: Remove
		/*
		[System::Flags]
		public enum class EffectFlags : System::Int32
		{
			None = 0,
			ChildEffect = D3D11_EFFECT_COMPILE_CHILD_EFFECT,
			AllowSlowOperations = D3D11_EFFECT_COMPILE_ALLOW_SLOW_OPS,
			SingleThreaded = D3D11_EFFECT_SINGLE_THREADED,
		};

		[System::Flags]
		public enum class EffectVariableFlags : System::Int32
		{
			None = 0,
			Annotation = D3D11_EFFECT_VARIABLE_ANNOTATION,
			Pooled = D3D11_EFFECT_VARIABLE_POOLED,
			ExplicitBindPoint = D3D11_EFFECT_VARIABLE_EXPLICIT_BIND_POINT,
		};
		*/

		public enum class FillMode : System::Int32
		{
			Wireframe = D3D11_FILL_WIREFRAME,
			Solid = D3D11_FILL_SOLID
		};
	
		// TODO: Remove
		/*
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
		*/
		
		[System::Flags]
		public enum class FormatSupport : System::Int32
		{
			Buffer = D3D11_FORMAT_SUPPORT_BUFFER,
			VertexBuffer = D3D11_FORMAT_SUPPORT_IA_VERTEX_BUFFER,
			IndexBuffer = D3D11_FORMAT_SUPPORT_IA_INDEX_BUFFER,
			StreamOutputBuffer = D3D11_FORMAT_SUPPORT_SO_BUFFER,
			Texture1D = D3D11_FORMAT_SUPPORT_TEXTURE1D,
			Texture2D = D3D11_FORMAT_SUPPORT_TEXTURE2D,
			Texture3D = D3D11_FORMAT_SUPPORT_TEXTURE3D,
			TextureCube = D3D11_FORMAT_SUPPORT_TEXTURECUBE,
			ShaderLoadIntrinsic = D3D11_FORMAT_SUPPORT_SHADER_LOAD,
			ShaderSampleIntrinsic = D3D11_FORMAT_SUPPORT_SHADER_SAMPLE,
			ShaderSampleComparisonIntrinsic = D3D11_FORMAT_SUPPORT_SHADER_SAMPLE_COMPARISON,
			Reserved = D3D11_FORMAT_SUPPORT_SHADER_SAMPLE_MONO_TEXT,
			MipMap = D3D11_FORMAT_SUPPORT_MIP,
			MipMapAutoGeneration = D3D11_FORMAT_SUPPORT_MIP_AUTOGEN,
			RenderTarget = D3D11_FORMAT_SUPPORT_RENDER_TARGET,
			BlendOperation = D3D11_FORMAT_SUPPORT_BLENDABLE,
			DepthStencil = D3D11_FORMAT_SUPPORT_DEPTH_STENCIL,
			CpuLocking = D3D11_FORMAT_SUPPORT_CPU_LOCKABLE,
			MultisampleResolve = D3D11_FORMAT_SUPPORT_MULTISAMPLE_RESOLVE,
			FormatDisplaySupport = D3D11_FORMAT_SUPPORT_DISPLAY,
			FormatCastSupport = D3D11_FORMAT_SUPPORT_CAST_WITHIN_BIT_LAYOUT,
			FormatMultisampleRenderTargetSupport = D3D11_FORMAT_SUPPORT_MULTISAMPLE_RENDERTARGET,
			FormatMultisampleLoadSupport = D3D11_FORMAT_SUPPORT_MULTISAMPLE_LOAD
		};
		
		public enum class ImageFileFormat : System::Int32
		{
			Bmp = D3DX11_IFF_BMP,
			Jpg = D3DX11_IFF_JPG,
			Png = D3DX11_IFF_PNG,
			Dds = D3DX11_IFF_DDS,
			Tiff = D3DX11_IFF_TIFF,
			Gif = D3DX11_IFF_GIF,
			Wmp = D3DX11_IFF_WMP,
		};
		
		// TODO: Remove
		/*
		/// <summary>
		/// Flags that indicate the location of an include file.
		/// </summary>
		[System::Flags]
		public enum class IncludeType : System::Int32
		{
			/// <summary>
			/// Indicates that the include is in the local path (or paths).
			/// </summary>
			Local = D3D11_INCLUDE_LOCAL,
			
			/// <summary>
			/// Indicates that the include is in the system path (or paths).
			/// </summary>
			System = D3D11_INCLUDE_SYSTEM
		};
		*/

		public enum class InputClassification : System::Int32
		{
			PerVertexData = D3D11_INPUT_PER_VERTEX_DATA,
			PerInstanceData = D3D11_INPUT_PER_INSTANCE_DATA
		};
		
		public enum class MapMode : System::Int32
		{
			Read = D3D11_MAP_READ,
			Write = D3D11_MAP_WRITE,
			ReadWrite = D3D11_MAP_READ_WRITE,
			WriteDiscard = D3D11_MAP_WRITE_DISCARD,
			WriteNoOverwrite = D3D11_MAP_WRITE_NO_OVERWRITE
		};
		
		[System::Flags]
		public enum class MapFlags : System::Int32
		{
			None = 0,
			DoNotWait = D3D11_MAP_FLAG_DO_NOT_WAIT
		};

		// TODO: Remove
		/*
		[System::Flags]
		public enum class MeshFlags : System::Int32
		{
			None = 0,
			Has32BitIndices = D3DX11_MESH_32_BIT,
			HasAdjacency = D3DX11_MESH_GS_ADJACENCY
		};

		[System::Flags]
		public enum class MeshDiscardFlags : System::Int32
		{
			DiscardAttributeBuffer = D3DX11_MESH_DISCARD_ATTRIBUTE_BUFFER,
			DiscardAttributeTable = D3DX11_MESH_DISCARD_ATTRIBUTE_TABLE,
			DiscardPointRepresentation = D3DX11_MESH_DISCARD_POINTREPS,
			DiscardAdjacency = D3DX11_MESH_DISCARD_ADJACENCY,
			DiscardDeviceBuffers = D3DX11_MESH_DISCARD_DEVICE_BUFFERS
		};
		
		/// <summary>
		/// Values that indicate how to alter mesh data during an optimization operation.
		/// </summary>
		[System::Flags]
		public enum class MeshOptimizeFlags : System::Int32
		{
			/// <summary>
			/// Reorders faces to remove unused vertices and faces.
			/// </summary>
			Compact = D3DX11_MESHOPT_COMPACT,
			
			/// <summary>
			/// Reorders faces to optimize for fewer attribute bundle state changes and enhanced draw performance.
			/// </summary>
			AttributeSort = D3DX11_MESHOPT_ATTR_SORT,
	    
			/// <summary>
			/// Reorders faces to increase the cache hit rate of vertex caches.
			/// </summary>
			VertexCache = D3DX11_MESHOPT_VERTEX_CACHE,
	    
			/// <summary>
			/// Reorders faces to maximize length of adjacent triangles.
			/// </summary>
			StripReorder = D3DX11_MESHOPT_STRIP_REORDER,
	    
			/// <summary>
			/// Optimize the faces only; do not optimize the vertices.
			/// </summary>
			IgnoreVertices = D3DX11_MESHOPT_IGNORE_VERTS,
			
			/// <summary>
			/// While attribute sorting, do not split vertices that are shared between attribute groups.
			/// </summary>
			DoNotSplit = D3DX11_MESHOPT_DO_NOT_SPLIT,
			
			/// <summary>
			/// Affects the vertex cache size. Using this flag specifies a default vertex cache size that works well on legacy hardware.
			/// </summary>
			DeviceIndependent = D3DX11_MESHOPT_DEVICE_INDEPENDENT,
		};
		*/
		
		public enum class PrimitiveTopology : System::Int32
		{
			Undefined = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED,
			PointList = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
			LineList = D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
			LineStrip = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
			TriangleList = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			TriangleStrip = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
			LineListWithAdjacency = D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
			LineStripWithAdjacency = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
			TriangleListWithAdjacency = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
			TriangleStripWithAdjacency = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ
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
		
		// TODO: Remove
		/*
		public enum class RegisterComponentType : System::Int32
		{
			Unknown = D3D11_REGISTER_COMPONENT_UNKNOWN,
			UInt32 = D3D11_REGISTER_COMPONENT_UINT32,
			SInt32 = D3D11_REGISTER_COMPONENT_SINT32,
			Float32 = D3D11_REGISTER_COMPONENT_FLOAT32
		};
		*/
		
		public enum class RenderTargetViewDimension : System::Int32
		{
			Unknown = D3D11_RTV_DIMENSION_UNKNOWN,
			Buffer = D3D11_RTV_DIMENSION_BUFFER,
			Texture1D = D3D11_RTV_DIMENSION_TEXTURE1D ,
			Texture1DArray = D3D11_RTV_DIMENSION_TEXTURE1DARRAY,
			Texture2D = D3D11_RTV_DIMENSION_TEXTURE2D,
			Texture2DArray = D3D11_RTV_DIMENSION_TEXTURE2DARRAY,
			Texture2DMultisampled = D3D11_RTV_DIMENSION_TEXTURE2DMS,
			Texture2DMultisampledArray = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY,
			Texture3D = D3D11_RTV_DIMENSION_TEXTURE3D
		};
		
		public enum class ResourceDimension : System::Int32
		{
			Unknown = D3D11_RESOURCE_DIMENSION_UNKNOWN,
			Buffer = D3D11_RESOURCE_DIMENSION_BUFFER,
			Texture1D = D3D11_RESOURCE_DIMENSION_TEXTURE1D,
			Texture2D = D3D11_RESOURCE_DIMENSION_TEXTURE2D,
			Texture3D = D3D11_RESOURCE_DIMENSION_TEXTURE3D
		};
		
		[System::Flags]
		public enum class ResourceOptionFlags : System::Int32
		{
			None = 0,
			GenerateMipMaps = D3D11_RESOURCE_MISC_GENERATE_MIPS,
			Shared = D3D11_RESOURCE_MISC_SHARED,
			TextureCube = D3D11_RESOURCE_MISC_TEXTURECUBE
		};

		public enum class ResourceUsage : System::Int32
		{
			Default = D3D11_USAGE_DEFAULT,
			Immutable = D3D11_USAGE_IMMUTABLE,
			Dynamic = D3D11_USAGE_DYNAMIC,
			Staging = D3D11_USAGE_STAGING
		};
		
		public enum class ResourceViewDimension : System::Int32
		{
			Unknown = D3D11_RTV_DIMENSION_UNKNOWN,
			Buffer = D3D11_RTV_DIMENSION_BUFFER,
			Texture1D = D3D11_RTV_DIMENSION_TEXTURE1D,
			Texture1DArray = D3D11_RTV_DIMENSION_TEXTURE1DARRAY,
			Texture2D = D3D11_RTV_DIMENSION_TEXTURE2D,
			Texture2DArray = D3D11_RTV_DIMENSION_TEXTURE2DARRAY,
			Texture2DMultisampled = D3D11_RTV_DIMENSION_TEXTURE2DMS,
			Texture2DMultisampledArray = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY,
			Texture3D = D3D11_RTV_DIMENSION_TEXTURE3D
		};
		
		// TODO: Remove
		/*
		[System::Flags]
		public enum class ShaderFlags : System::Int32
		{
			None = 0,
			Debug = D3D11_SHADER_DEBUG,
			SkipValidation = D3D11_SHADER_SKIP_VALIDATION,
			SkipOptimization = D3D11_SHADER_SKIP_OPTIMIZATION,
			PackMatrixRowMajor = D3D11_SHADER_PACK_MATRIX_ROW_MAJOR,
			PackMatrixColumnMajor = D3D11_SHADER_PACK_MATRIX_COLUMN_MAJOR,
			PartialPrecision = D3D11_SHADER_PARTIAL_PRECISION,
			ForceSoftwareVertexShader = D3D11_SHADER_FORCE_VS_SOFTWARE_NO_OPT,
			ForceSoftwarePixelShader = D3D11_SHADER_FORCE_PS_SOFTWARE_NO_OPT,
			NoPreshader = D3D11_SHADER_NO_PRESHADER,
			AvoidFlowControl = D3D11_SHADER_AVOID_FLOW_CONTROL,
			PreferFlowControl = D3D11_SHADER_PREFER_FLOW_CONTROL,
			EnableStrictness = D3D11_SHADER_ENABLE_STRICTNESS,
			EnableBackwardsCompatibility = D3D11_SHADER_ENABLE_BACKWARDS_COMPATIBILITY,
			EnableIEEEStrictness = D3D11_SHADER_IEEE_STRICTNESS,
			OptimizationLevel0 = D3D11_SHADER_OPTIMIZATION_LEVEL0,
			OptimizationLevel1 = D3D11_SHADER_OPTIMIZATION_LEVEL1,
			OptimizationLevel2 = D3D11_SHADER_OPTIMIZATION_LEVEL2,
			OptimizationLevel3 = D3D11_SHADER_OPTIMIZATION_LEVEL3
		};
		*/
		
		public enum class ShaderResourceViewDimension : System::Int32
		{
			Unknown = D3D11_SRV_DIMENSION_UNKNOWN,
			Buffer = D3D11_SRV_DIMENSION_BUFFER,
			Texture1D = D3D11_SRV_DIMENSION_TEXTURE1D,
			Texture1DArray = D3D11_SRV_DIMENSION_TEXTURE1DARRAY,
			Texture2D = D3D11_SRV_DIMENSION_TEXTURE2D,
			Texture2DArray = D3D11_SRV_DIMENSION_TEXTURE2DARRAY,
			Texture2DMultisampled = D3D11_SRV_DIMENSION_TEXTURE2DMS,
			Texture2DMultisampledArray = D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY,
			Texture3D = D3D11_SRV_DIMENSION_TEXTURE3D,
			TextureCube = D3D11_SRV_DIMENSION_TEXTURECUBE
		};

		// TODO: Remove
		/*
		/// <summary>
		/// Flags that control the behavior of <see cref="Sprite"/> rendering.
		/// </summary>
		/// <unmanaged>D3DX11_SPRITE_FLAG</unmanaged>
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
			GroupByTexture = D3DX11_SPRITE_SORT_TEXTURE,
			
			/// <summary>
			/// Sort the sprites from back to front based on their depth; sprites further away from the
			/// camera will be rendered first.
			/// </summary>
			SortBackToFront = D3DX11_SPRITE_SORT_DEPTH_BACK_TO_FRONT,
			
			/// <summary>
			/// Sort the sprites from front to back based on their depth; sprites closer to the
			/// camera will be rendered first.
			/// </summary>
			SortFrontToBack = D3DX11_SPRITE_SORT_DEPTH_FRONT_TO_BACK,
			
			/// <summary>
			/// Saves render state when sprites are rendered, and restores the previous state once rendering
			/// is complete.
			/// </summary>
			SaveState = D3DX11_SPRITE_SAVE_STATE,
			
			/// <summary>
			/// Increases the reference count of textures when DrawSpritesBuffered is called.
			/// </summary>
			IncreaseTextureReferenceCount = D3DX11_SPRITE_ADDREF_TEXTURES
		};
		*/

		public enum class StencilOperation : System::Int32
		{
			Keep = D3D11_STENCIL_OP_KEEP,
			Zero = D3D11_STENCIL_OP_ZERO,
			Replace = D3D11_STENCIL_OP_REPLACE,
			IncrementAndClamp = D3D11_STENCIL_OP_INCR_SAT,
			DecrementAndClamp = D3D11_STENCIL_OP_DECR_SAT,
			Invert = D3D11_STENCIL_OP_INVERT,
			Increment = D3D11_STENCIL_OP_INCR,
			Decrement = D3D11_STENCIL_OP_DECR
		};
		
		// TODO: Remove
		
		public enum class SystemValueType : System::Int32
		{
			
			/*
			Undefined = D3D11_NAME_UNDEFINED,
			Position = D3D11_NAME_POSITION,
			ClipDistance = D3D11_NAME_CLIP_DISTANCE,
			CullDistance = D3D11_NAME_CULL_DISTANCE,
			RenderTargetArrayIndex = D3D11_NAME_RENDER_TARGET_ARRAY_INDEX,
			ViewportArrayIndex = D3D11_NAME_VIEWPORT_ARRAY_INDEX,
			VertexId = D3D11_NAME_VERTEX_ID,
			PrimitiveId = D3D11_NAME_PRIMITIVE_ID,
			InstanceId = D3D11_NAME_INSTANCE_ID,
			FrontFaceFlag = D3D11_NAME_IS_FRONT_FACE,
			SampleIndex =D3D11_NAME_SAMPLE_INDEX,
			Target = D3D11_NAME_TARGET,
			Depth = D3D11_NAME_DEPTH
			*/
		};
		
	}
}