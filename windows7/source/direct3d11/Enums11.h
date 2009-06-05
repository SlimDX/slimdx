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
		
		/// <summary>Optional flags that control the behavior of Asynchronous.GetData.</summary>
		/// <unmanaged>D3D11_ASYNC_GETDATA_FLAG</unmanaged>
		[System::Flags]
		public enum class AsynchronousFlags : System::Int32
		{
			/// <summary>
			/// Indicates no specific behavior.
			/// </summary>
			None = 0,

			/// <summary>
			/// Indicates the command buffer should not be flushed.
			/// Note that this can cause an infinite loop if GetData() is called repeatedly until 
			/// returning successfully: there may still be commands in the buffer than need
			/// to be processed in order for GetData() to return successfully. Since the buffer 
			/// will not be flushed, those commands will not be processed and GetData() will never
			/// return successfully.
			/// </summary>
			DoNotFlush = D3D11_ASYNC_GETDATA_DONOTFLUSH
		};
		
		/// <summary>Identifies how to bind a resource to the pipeline.</summary>
		/// <unmanaged>D3D11_BIND_FLAG</unmanaged>
		[System::Flags]
		public enum class BindFlags : System::Int32
		{
			/// <summary>
			/// Indicates no specific behavior.
			/// </summary>
			None = 0,

			/// <summary>
			/// Indicates the resource can be bound to the input-assembler stage as a vertex buffer. 
			/// </summary>
			VertexBuffer = D3D11_BIND_VERTEX_BUFFER,
			
			/// <summary>
			/// Indicates the resource can be bound to the input-assembler stage as an index buffer 
			/// </summary>
			IndexBuffer = D3D11_BIND_INDEX_BUFFER,

			/// <summary>
			/// Indicates the resource can be bound to the shader stage as a constant buffer 
			/// </summary>
			ConstantBuffer = D3D11_BIND_CONSTANT_BUFFER,

			/// <summary>
			/// Indicates the resource can be bound to the shader stage as a buffer or texture. 
			/// Note that it is invalid to specify this flag and subsequently map the resource
			/// using MapMode.WriteNoOverwrite.
			/// </summary>
			ShaderResource = D3D11_BIND_SHADER_RESOURCE, 

			/// <summary>
			/// Indicates the resource can be bound to the stream-output stage as an output buffer. 
			/// </summary>
			StreamOutput = D3D11_BIND_STREAM_OUTPUT,

			/// <summary>
			/// Indicates the resource can be bound to the output-merger stage as a render target. 
			/// </summary>
			RenderTarget = D3D11_BIND_RENDER_TARGET,

			/// <summary>
			/// Indicates the resource can be bound to the output-merger stage as a depth-stencil target. 
			/// </summary>
			DepthStencil = D3D11_BIND_DEPTH_STENCIL
		};
		
		/// <summary>RGB or alpha blending operation.</summary>
		/// <unmanaged>D3D11_BLEND_OP</unmanaged>
		public enum class BlendOperation : System::Int32
		{
			Add = D3D11_BLEND_OP_ADD,
			Subtract = D3D11_BLEND_OP_SUBTRACT,
			ReverseSubtract = D3D11_BLEND_OP_REV_SUBTRACT,
			Minimum = D3D11_BLEND_OP_MIN,
			Maximum = D3D11_BLEND_OP_MAX
		};
		
		/// <summary>Blend options. A blend option identifies the data source and an optional pre-blend operation.</summary>
		/// <unmanaged>D3D11_BLEND</unmanaged>
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
		
		/// <summary>Identify which components of each pixel of a render target are writable during blending.</summary>
		/// <unmanaged>D3D11_COLOR_WRITE_ENABLE</unmanaged>
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
		
		/// <summary>Comparison options.</summary>
		/// <unmanaged>D3D11_COMPARISON_FUNC</unmanaged>
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
		
		/// <summary>Performance counter types.</summary>
		/// <unmanaged>D3D11_COUNTER</unmanaged>
		public enum class CounterKind : System::Int32
		{
			DeviceDependent = D3D11_COUNTER_DEVICE_DEPENDENT_0
		};
		
		/// <summary>Data type of a performance counter.</summary>
		/// <unmanaged>D3D11_COUNTER_TYPE</unmanaged>
		public enum class CounterType : System::Int32
		{
			Float32 = D3D11_COUNTER_TYPE_FLOAT32,
			UnsignedInt16 = D3D11_COUNTER_TYPE_UINT16,
			UnsignedInt32 = D3D11_COUNTER_TYPE_UINT32, 
			UnsignedInt64 = D3D11_COUNTER_TYPE_UINT64
		};
		
		/// <summary>Specifies the types of CPU access allowed for a resource.</summary>
		/// <unmanaged>D3D11_CPU_ACCESS_FLAG</unmanaged>
		[System::Flags]
		public enum class CpuAccessFlags : System::Int32
		{
			None = 0,
			Write = D3D11_CPU_ACCESS_WRITE,
			Read = D3D11_CPU_ACCESS_READ
		};
		
		/// <summary>Indicates triangles facing a particular direction are not drawn.</summary>
		/// <unmanaged>D3D11_CULL_MODE</unmanaged>
		public enum class CullMode : System::Int32 
		{
			None = D3D11_CULL_NONE,
			Front = D3D11_CULL_FRONT,
			Back = D3D11_CULL_BACK
		};
		
		/// <summary></summary>
		/// <unmanaged href="bb173520">D3D11_DEBUG_FEATURE</unmanaged>
		[System::Flags]
		public enum class DebugFeatureFlags : System::Int32
		{
			FinishPerRender = D3D11_DEBUG_FEATURE_FINISH_PER_RENDER_OP,
			FlushPerRender = D3D11_DEBUG_FEATURE_FLUSH_PER_RENDER_OP,
			PresentPerRender = D3D11_DEBUG_FEATURE_PRESENT_PER_RENDER_OP
		};
		
		/// <summary>Specifies the parts of the depth stencil to clear.</summary>
		/// <unmanaged>D3D11_CLEAR_FLAG</unmanaged>
		[System::Flags]
		public enum class DepthStencilClearFlags : System::Int32
		{
			Depth = D3D11_CLEAR_DEPTH,
			Stencil = D3D11_CLEAR_STENCIL
		};
		
		/// <summary></summary>
		/// <unmanaged>D3D11_DSV_DIMENSION</unmanaged>
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
		
		/// <summary></summary>
		/// <unmanaged>D3D11_DEPTH_WRITE_MASK</unmanaged>
		public enum class DepthWriteMask : System::Int32
		{
			Zero = D3D11_DEPTH_WRITE_MASK_ZERO,
			All = D3D11_DEPTH_WRITE_MASK_ALL
		};

		public enum class DeviceContextType : System::Int32
		{
			Immediate = D3D11_DEVICE_CONTEXT_IMMEDIATE,
			Deferred = D3D11_DEVICE_CONTEXT_DEFERRED
		};
		
		/// <summary></summary>
		/// <unmanaged>D3D11_CREATE_DEVICE_FLAG</unmanaged>
		[System::Flags]
		public enum class DeviceCreationFlags : System::Int32
		{
			None = 0,
			SingleThreaded = D3D11_CREATE_DEVICE_SINGLETHREADED,
			Debug = D3D11_CREATE_DEVICE_DEBUG,
			SwitchToRef = D3D11_CREATE_DEVICE_SWITCH_TO_REF,
			PreventThreadingOptimizations = D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS
		};
	
		/// <summary></summary>
		/// <unmanaged>D3D11_DRIVER_TYPE</unmanaged>
		public enum class DriverType : System::Int32
		{
			Unknown = D3D_DRIVER_TYPE_UNKNOWN,
			Hardware = D3D_DRIVER_TYPE_HARDWARE,
			Reference = D3D_DRIVER_TYPE_REFERENCE,
			Null = D3D_DRIVER_TYPE_NULL,
			Software = D3D_DRIVER_TYPE_SOFTWARE,
			Warp = D3D_DRIVER_TYPE_WARP
		};

		public enum class Feature : System::Int32
		{
			ShaderDoubles,
			ComputeShaders
		};

		public enum class FeatureLevel : System::Int32
		{
			Level_11_0 = D3D_FEATURE_LEVEL_11_0,
			Level_10_0 = D3D_FEATURE_LEVEL_10_0,
			Level_10_1 = D3D_FEATURE_LEVEL_10_1,
			Level_9_1 = D3D_FEATURE_LEVEL_9_1,
			Level_9_2 = D3D_FEATURE_LEVEL_9_2,
			Level_9_3 = D3D_FEATURE_LEVEL_9_3
		};
		
		/// <summary></summary>
		/// <unmanaged>D3D11_FILL_MODE</unmanaged>
		public enum class FillMode : System::Int32
		{
			Wireframe = D3D11_FILL_WIREFRAME,
			Solid = D3D11_FILL_SOLID
		};

		[System::Flags]
		public enum class Filter : System::Int32
		{
			MinMagMipPoint = D3D11_FILTER_MIN_MAG_MIP_POINT,
			MinMagPointMipLinear = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR,
			MinPointMagLinearMipPoint = D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,
			MinPointMagMipLinear = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR,
			MinLinearMagMipPoint = D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT,
			MinLinearMagPointMipLinear = D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
			MinMagLinearMipPoint = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT,
			MinMagMipLinear = D3D11_FILTER_MIN_MAG_MIP_LINEAR,
			Anisotropic = D3D11_FILTER_ANISOTROPIC,
			ComparisonMinMagMipPoint = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT,
			ComparisonMinMagPointMipLinear = D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR,
			ComparisonMinPointMagLinearMipPoint = D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,
			ComparisonMinPointMagMipLinear = D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR,
			ComparisonMinLinearMagMipPoint = D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT,
			ComparisonMinLinearMagPointMipLinear = D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
			ComparisonMinMagLinearMipPoint = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
			ComparisonMinMagMipLinear = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR,
			ComparisonAnisotropic = D3D11_FILTER_COMPARISON_ANISOTROPIC
		};
		
		/// <summary></summary>
		/// <unmanaged>D3DX11_FILTER_FLAG</unmanaged>
		[System::Flags]
		public enum class FilterFlags : System::Int32
		{
			None = D3DX11_FILTER_NONE,
			Point = D3DX11_FILTER_POINT,
			Linear = D3DX11_FILTER_LINEAR,
			Triangle = D3DX11_FILTER_TRIANGLE,
			Box = D3DX11_FILTER_BOX,
			MirrorU = D3DX11_FILTER_MIRROR_U,
			MirrorV = D3DX11_FILTER_MIRROR_V,
			MirrowW = D3DX11_FILTER_MIRROR_W,
			Mirror = D3DX11_FILTER_MIRROR,
			Dither = D3DX11_FILTER_DITHER,
			DitherDiffusion = D3DX11_FILTER_DITHER_DIFFUSION,
			StandardRgbIn = D3DX11_FILTER_SRGB_IN,
			StandardRgbOut = D3DX11_FILTER_SRGB_OUT,
			StandardRgb = D3DX11_FILTER_SRGB,
		};
	
		/// <summary></summary>
		/// <unmanaged>CHARSET</unmanaged>
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

		/// <summary></summary>
		/// <unmanaged href="bb773199">DT</unmanaged>
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
		
		/// <summary></summary>
		/// <unmanaged>(various constants)</unmanaged>
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

		/// <summary></summary>
		/// <unmanaged href="cc215248">OutPrecision</unmanaged>
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

		/// <summary></summary>
		/// <unmanaged>QUALITY</unmanaged>
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

		/// <summary></summary>
		/// <unmanaged>FW</unmanaged>
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
		
		/// <summary></summary>
		/// <unmanaged>D3D11_FORMAT_SUPPORT</unmanaged>
		[System::Flags]
		public enum class FormatSupport : System::Int32
		{
			None = 0,
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
			FormatMultisampleLoadSupport = D3D11_FORMAT_SUPPORT_MULTISAMPLE_LOAD,
			ShaderGatherIntrinsic = D3D11_FORMAT_SUPPORT_SHADER_GATHER,
			BackBufferCast = D3D11_FORMAT_SUPPORT_BACK_BUFFER_CAST,
			UnorderedAccessView = D3D11_FORMAT_SUPPORT_TYPED_UNORDERED_ACCESS_VIEW,
			ShaderGatherComparisonIntrinsic = D3D11_FORMAT_SUPPORT_SHADER_GATHER_COMPARISON
		};

		[System::Flags]
		public enum class ComputeShaderFormatSupport : System::Int32
		{
			None = 0,
			AtomicAdd = D3D11_FORMAT_SUPPORT2_UAV_ATOMIC_ADD,
			AtomicBitwiseOperations = D3D11_FORMAT_SUPPORT2_UAV_ATOMIC_BITWISE_OPS,
			AtomicCompareStoreOrCompareExchange = D3D11_FORMAT_SUPPORT2_UAV_ATOMIC_COMPARE_STORE_OR_COMPARE_EXCHANGE,
			AtomicExchange = D3D11_FORMAT_SUPPORT2_UAV_ATOMIC_EXCHANGE,
			AtomicSignedMinMax = D3D11_FORMAT_SUPPORT2_UAV_ATOMIC_SIGNED_MIN_OR_MAX,
			AtomicUnsignedMinMax = D3D11_FORMAT_SUPPORT2_UAV_ATOMIC_UNSIGNED_MIN_OR_MAX,
			TypedLoad = D3D11_FORMAT_SUPPORT2_UAV_TYPED_LOAD,
			TypedStore = D3D11_FORMAT_SUPPORT2_UAV_TYPED_STORE
		};
		
		/// <summary></summary>
		/// <unmanaged>D3DX11_IMAGE_FILE_FORMAT</unmanaged>
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
		
		/// <summary>Type of data contained in an input slot.</summary>
		/// <unmanaged>D3D11_INPUT_CLASSIFICATION</unmanaged>
		public enum class InputClassification : System::Int32
		{
			PerVertexData = D3D11_INPUT_PER_VERTEX_DATA,
			PerInstanceData = D3D11_INPUT_PER_INSTANCE_DATA
		};
		
		/// <summary>Identifies a resource to be accessed for reading and writing by the CPU.</summary>
		/// <unmanaged>D3D11_MAP</unmanaged>
		public enum class MapMode : System::Int32
		{
			Read = D3D11_MAP_READ,
			Write = D3D11_MAP_WRITE,
			ReadWrite = D3D11_MAP_READ_WRITE,
			WriteDiscard = D3D11_MAP_WRITE_DISCARD,
			WriteNoOverwrite = D3D11_MAP_WRITE_NO_OVERWRITE
		};
		
		/// <summary></summary>
		/// <unmanaged>D3D11_MAP_FLAG</unmanaged>
		[System::Flags]
		public enum class MapFlags : System::Int32
		{
			None = 0,
			DoNotWait = D3D11_MAP_FLAG_DO_NOT_WAIT
		};
		
		/// <summary></summary>
		/// <unmanaged>D3D11_PRIMITIVE_TOPOLOGY</unmanaged>
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
		/// Flags for describing query options and behavior.
		/// </summary>
		/// <unmanaged>D3D11_QUERY_MISC_FLAG</unmanaged>
		[System::Flags]
		public enum class QueryFlags : System::Int32
		{
			None = 0,
			PredicateHint = D3D11_QUERY_MISC_PREDICATEHINT,
		};
		
		/// <summary>
		/// Values which description query types.
		/// </summary>
		/// <unmanaged>D3D11_QUERY</unmanaged>
		public enum class QueryType : System::Int32
		{
			Event = D3D11_QUERY_EVENT,
			Occlusion = D3D11_QUERY_OCCLUSION,
			Timestamp = D3D11_QUERY_TIMESTAMP,
			TimestampDisjoint = D3D11_QUERY_TIMESTAMP_DISJOINT,
			PipelineStatistics = D3D11_QUERY_PIPELINE_STATISTICS,
			Predicate = D3D11_QUERY_OCCLUSION_PREDICATE,
			StreamOutputStatistics = D3D11_QUERY_SO_STATISTICS,
			StreamOutputOverflowPredicate = D3D11_QUERY_SO_OVERFLOW_PREDICATE,
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
		/// <unmanaged>D3D11_RTV_DIMENSION</unmanaged>
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
		
		/// <summary></summary>
		/// <unmanaged>D3D11_RESOURCE_DIMENSION</unmanaged>
		public enum class ResourceDimension : System::Int32
		{
			Unknown = D3D11_RESOURCE_DIMENSION_UNKNOWN,
			Buffer = D3D11_RESOURCE_DIMENSION_BUFFER,
			Texture1D = D3D11_RESOURCE_DIMENSION_TEXTURE1D,
			Texture2D = D3D11_RESOURCE_DIMENSION_TEXTURE2D,
			Texture3D = D3D11_RESOURCE_DIMENSION_TEXTURE3D
		};
		
		/// <summary></summary>
		/// <unmanaged>D3D11_RESOURCE_MISC_FLAG</unmanaged>
		[System::Flags]
		public enum class ResourceOptionFlags : System::Int32
		{
			None = 0,
			GenerateMipMaps = D3D11_RESOURCE_MISC_GENERATE_MIPS,
			Shared = D3D11_RESOURCE_MISC_SHARED,
			TextureCube = D3D11_RESOURCE_MISC_TEXTURECUBE
		};

		/// <summary></summary>
		/// <unmanaged>D3D11_USAGE</unmanaged>
		public enum class ResourceUsage : System::Int32
		{
			Default = D3D11_USAGE_DEFAULT,
			Immutable = D3D11_USAGE_IMMUTABLE,
			Dynamic = D3D11_USAGE_DYNAMIC,
			Staging = D3D11_USAGE_STAGING
		};
		
		/// <summary></summary>
		/// <unmanaged>D3D11_RTV_DIMENSION</unmanaged>
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
		
		/// <summary>Identifies the type of the resource that will be viewed.</summary>
		/// <unmanaged>D3D11_SRV_DIMENSION</unmanaged>
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

		/// <summary>The stencil operations that can be performed during depth-stencil testing.</summary>
		/// <unmanaged>D3D11_STENCIL_OP</unmanaged>
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

		public enum class TextureAddressMode : System::Int32
		{
			Wrap = D3D11_TEXTURE_ADDRESS_WRAP,
			Mirror = D3D11_TEXTURE_ADDRESS_MIRROR,
			Clamp = D3D11_TEXTURE_ADDRESS_CLAMP,
			Border = D3D11_TEXTURE_ADDRESS_BORDER,
			MirrorOnce = D3D11_TEXTURE_ADDRESS_MIRROR_ONCE
		};

		public enum class UnorderedAccessViewDimension : System::Int32
		{
			Unknown = D3D11_UAV_DIMENSION_UNKNOWN,
			Buffer = D3D11_UAV_DIMENSION_BUFFER,
			Texture1D = D3D11_UAV_DIMENSION_TEXTURE1D ,
			Texture1DArray = D3D11_UAV_DIMENSION_TEXTURE1DARRAY,
			Texture2D = D3D11_UAV_DIMENSION_TEXTURE2D,
			Texture2DArray = D3D11_UAV_DIMENSION_TEXTURE2DARRAY,
			Texture3D = D3D11_UAV_DIMENSION_TEXTURE3D
		};

		[System::Flags]
		public enum class UnorderedAccessViewBufferFlags : System::Int32
		{
			None = 0,
			RawData = D3D11_BUFFER_UAV_FLAG_RAW,
			AllowAppend = D3D11_BUFFER_UAV_FLAG_APPEND
		};
	}
}