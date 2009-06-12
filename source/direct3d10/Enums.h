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
#include <d3d10.h>
#include <d3dx10.h>

namespace SlimDX
{
#ifdef XMLDOCS
	namespace DXGI
	{
		ref class SwapChain;
	}
#endif

	namespace Direct3D10
	{
#ifdef XMLDOCS
		ref class Device;
		ref class Sprite;
		ref class Debug;
#endif
	
		// NOTE: The enumerations defined in this file are in alphabetical order. When
		//       adding new enumerations or renaming existing ones, please make sure
		//       the ordering is maintained.
		
		/// <summary>Optional flags that control the behavior of Asynchronous.GetData.</summary>
		/// <unmanaged>D3D10_ASYNC_GETDATA_FLAG</unmanaged>
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
			DoNotFlush = D3D10_ASYNC_GETDATA_DONOTFLUSH
		};
		
		/// <summary>Identifies how to bind a resource to the pipeline.</summary>
		/// <unmanaged>D3D10_BIND_FLAG</unmanaged>
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
			VertexBuffer = D3D10_BIND_VERTEX_BUFFER,
			
			/// <summary>
			/// Indicates the resource can be bound to the input-assembler stage as an index buffer 
			/// </summary>
			IndexBuffer = D3D10_BIND_INDEX_BUFFER,

			/// <summary>
			/// Indicates the resource can be bound to the shader stage as a constant buffer 
			/// </summary>
			ConstantBuffer = D3D10_BIND_CONSTANT_BUFFER,

			/// <summary>
			/// Indicates the resource can be bound to the shader stage as a buffer or texture. 
			/// Note that it is invalid to specify this flag and subsequently map the resource
			/// using MapMode.WriteNoOverwrite.
			/// </summary>
			ShaderResource = D3D10_BIND_SHADER_RESOURCE, 

			/// <summary>
			/// Indicates the resource can be bound to the stream-output stage as an output buffer. 
			/// </summary>
			StreamOutput = D3D10_BIND_STREAM_OUTPUT,

			/// <summary>
			/// Indicates the resource can be bound to the output-merger stage as a render target. 
			/// </summary>
			RenderTarget = D3D10_BIND_RENDER_TARGET,

			/// <summary>
			/// Indicates the resource can be bound to the output-merger stage as a depth-stencil target. 
			/// </summary>
			DepthStencil = D3D10_BIND_DEPTH_STENCIL
		};
		
		/// <summary>RGB or alpha blending operation.</summary>
		/// <unmanaged>D3D10_BLEND_OP</unmanaged>
		public enum class BlendOperation : System::Int32
		{
			/// <summary>
			/// Adds the source to the destination.
			/// </summary>
			Add = D3D10_BLEND_OP_ADD,
			
			/// <summary>
			/// Subtracts the source from the destination.
			/// </summary>
			Subtract = D3D10_BLEND_OP_SUBTRACT,
			
			/// <summary>
			/// Subtracts the destination from the source.
			/// </summary>
			ReverseSubtract = D3D10_BLEND_OP_REV_SUBTRACT,
			
			/// <summary>
			/// Takes the lesser of the source and destination values.
			/// </summary>
			Minimum = D3D10_BLEND_OP_MIN,
			
			/// <summary>
			/// Takes the greater of the source and destination values.
			/// </summary>
			Maximum = D3D10_BLEND_OP_MAX
		};
		
		/// <summary>Blend options. A blend option identifies the data source and an optional pre-blend operation.</summary>
		/// <unmanaged>D3D10_BLEND</unmanaged>
		public enum class BlendOption : System::Int32
		{
			/// <summary>
			/// The source is the color (0,0,0,0) with no pre-blend.
			/// </summary>
			Zero = D3D10_BLEND_ZERO,
			
			/// <summary>
			/// The source is the color (1,1,1,1) with no pre-blend.
			/// </summary>
			One = D3D10_BLEND_ONE,
			
			/// <summary>
			/// The source is the color (RGB) from a pixel shader with no pre-blend.
			/// </summary>
			SourceColor = D3D10_BLEND_SRC_COLOR,
			
			/// <summary>
			/// The source is the color (RGB) from a pixel shader with an inverting pre-blend (1 - RGB).
			/// </summary>
			InverseSourceColor = D3D10_BLEND_INV_SRC_COLOR,
			
			/// <summary>
			/// The source is the alpha (A) from a pixel shader with no pre-blend.
			/// </summary>
			SourceAlpha = D3D10_BLEND_SRC_ALPHA,
			
			/// <summary>
			/// The source is the alpha (A) from a pixel shader with an inverting pre-blend (1 - A).
			/// </summary>
			InverseSourceAlpha = D3D10_BLEND_INV_SRC_ALPHA,
			
			/// <summary>
			/// The source is the alpha (A) from a rendertarget with no pre-blend.
			/// </summary>
			DestinationAlpha = D3D10_BLEND_DEST_ALPHA,
			
			/// <summary>
			/// The source is the alpha (A) from a rendertarget with an inverting pre-blend (1 - A).
			/// </summary>
			InverseDestinationAlpha = D3D10_BLEND_INV_DEST_ALPHA,
			
			/// <summary>
			/// The source is the color (RGB) from a rendertarget with no pre-blend.
			/// </summary>
			DestinationColor = D3D10_BLEND_DEST_COLOR,
			
			/// <summary>
			/// The source is the color (RGB) from a rendertarget with an inverting pre-blend (1 - A).
			/// </summary>
			InverseDestinationColor = D3D10_BLEND_INV_DEST_COLOR,
			
			/// <summary>
			/// The source is the alpha (A) from a render target with a saturation pre-blend (clamping to 1 or less).
			/// </summary>
			SourceAlphaSaturate = D3D10_BLEND_SRC_ALPHA_SAT,
			
			/// <summary>
			/// The source is the blend factor (F) from the current blend state with no pre-blend operation.
			/// </summary>
			BlendFactor = D3D10_BLEND_BLEND_FACTOR,
			
			/// <summary>
			/// The source is the blend factor (F) from the current blend state with an inverting pre-blend (1 - F).
			/// </summary>
			InverseBlendFactor = D3D10_BLEND_INV_BLEND_FACTOR,
			
			/// <summary>
			/// The sources are both color (RGB) outputs from a pixel shader. There is no pre-blend operation. This option
			/// allows for dual-source blending.
			/// </summary>
			SecondarySourceColor = D3D10_BLEND_SRC1_COLOR,
			
			/// <summary>
			/// The sources are both color (RGB) outputs from a pixel shader. There is an inverting pre-blend (1 - RGB). This option
			/// allows for dual-source blending.
			/// </summary>
			InverseSecondarySourceColor = D3D10_BLEND_INV_SRC1_COLOR,
			
			/// <summary>
			/// The sources are both alpha (A) outputs from a pixel shader. There is no pre-blend. This option
			/// allows for dual-source blending.
			/// </summary>
			SecondarySourceAlpha = D3D10_BLEND_SRC1_ALPHA,
			
			/// <summary>
			/// The sources are both alpha (A) outputs from a pixel shader. There is an inverting pre-blend (1 - A). This option
			/// allows for dual-source blending.
			/// </summary>
			InverseSecondarySourceAlpha = D3D10_BLEND_INV_SRC1_ALPHA
		};
		
		/// <summary>Identifies mask values for writing to a render target.</summary>
		/// <unmanaged>D3D10_COLOR_WRITE_ENABLE</unmanaged>
		[System::Flags]
		public enum class ColorWriteMaskFlags : System::Int32
		{
			/// <summary>
			/// Indicates that writes to the red component should be enabled.
			/// </summary>
			Red = D3D10_COLOR_WRITE_ENABLE_RED,
			
			/// <summary>
			/// Indicates that writes to the green component should be enabled.
			/// </summary>
			Green = D3D10_COLOR_WRITE_ENABLE_GREEN,
			
			/// <summary>
			/// Indicates that writes to the blue component should be enabled.
			/// </summary>
			Blue = D3D10_COLOR_WRITE_ENABLE_BLUE,
			
			/// <summary>
			/// Indicates that writes to the alpha component should be enabled.
			/// </summary>
			Alpha = D3D10_COLOR_WRITE_ENABLE_ALPHA,
			
			/// <summary>
			/// Indicates that writes to all components should be enabled.
			/// </summary>
			All = D3D10_COLOR_WRITE_ENABLE_ALL
		};
		
		/// <summary>Comparison options.</summary>
		/// <unmanaged>D3D10_COMPARISON_FUNC</unmanaged>
		public enum class Comparison : System::Int32
		{
			/// <summary>
			/// The test never passes.
			/// </summary>
			Never = D3D10_COMPARISON_NEVER,
			
			/// <summary>
			/// The test passes if (source &lt; destination).
			/// </summary>
			Less = D3D10_COMPARISON_LESS,
			
			/// <summary>
			/// The test passes if (source == destination).
			/// </summary>
			Equal = D3D10_COMPARISON_EQUAL,
			
			/// <summary>
			/// The test passes if (source &lt;= destination).
			/// </summary>
			LessEqual = D3D10_COMPARISON_LESS_EQUAL,
			
			/// <summary>
			/// The test passes if (source &gt; destination).
			/// </summary>
			Greater = D3D10_COMPARISON_GREATER,
			
			/// <summary>
			/// The test passes if (source != destination).
			/// </summary>
			NotEqual = D3D10_COMPARISON_NOT_EQUAL,
			
			/// <summary>
			/// The test passes if (source &gt;= destination).
			/// </summary>
			GreaterEqual = D3D10_COMPARISON_GREATER_EQUAL,
			
			/// <summary>
			/// The test always passes.
			/// </summary>
			Always = D3D10_COMPARISON_ALWAYS
		};
		
		/// <summary>Performance counter types.</summary>
		/// <unmanaged>D3D10_COUNTER</unmanaged>
		public enum class CounterKind : System::Int32
		{
			/// <summary>
			/// The counter for the percentage of time the GPU is idle.
			/// </summary>
			Idle = D3D10_COUNTER_GPU_IDLE,
			
			/// <summary>
			/// The counter for the percentage of time the GPU is processing vertices.
			/// </summary>
			VertexProcessing = D3D10_COUNTER_VERTEX_PROCESSING,
			
			/// <summary>
			/// The counter for the percentage of time the GPU is processing geometry.
			/// </summary>
			GeometryProcessing = D3D10_COUNTER_GEOMETRY_PROCESSING,
			
			/// <summary>
			/// The counter for the percentage of time the GPU is processing pixels. 
			/// </summary>
			PixelProcessing = D3D10_COUNTER_PIXEL_PROCESSING,
			
			/// <summary>
			/// The counter for the percentage of time the GPU is performing processing that is not vertex, pixel or geometry processing.
			/// </summary>
			OtherProcessing = D3D10_COUNTER_OTHER_GPU_PROCESSING,
			
			/// <summary>
			/// The counter for the percentage of bandwidth used on a host adapter.
			/// </summary>
			HostAdapterBandwidth = D3D10_COUNTER_HOST_ADAPTER_BANDWIDTH_UTILIZATION,
			
			/// <summary>
			/// The counter for the percentage of bandwidth used by local video memory.
			/// </summary>
			LocalVideoMemoryBandwidth = D3D10_COUNTER_LOCAL_VIDMEM_BANDWIDTH_UTILIZATION,
			
			/// <summary>
			/// The counter for the percentage of throughput for vertices.
			/// </summary>
			VertexThroughput = D3D10_COUNTER_VERTEX_THROUGHPUT_UTILIZATION,
			
			/// <summary>
			/// The counter for the percentage of throughput used for triangle setup.
			/// </summary>
			TriangleSetupThroughput = D3D10_COUNTER_TRIANGLE_SETUP_THROUGHPUT_UTILIZATION,
			
			/// <summary>
			/// The counter for the percentage of throughput used for fillrate.
			/// </summary>
			FillRateThroughput = D3D10_COUNTER_FILLRATE_THROUGHPUT_UTILIZATION,
			
			/// <summary>
			/// The counter for the percentage of time the vertex shader spends sampling resources.
			/// </summary>
			VertexShaderMemoryLimited = D3D10_COUNTER_VS_MEMORY_LIMITED,
			
			/// <summary>
			/// The counter for the percentage of time the vertex shader spends performing computations.
			/// </summary>
			VertexShaderComputationLimited = D3D10_COUNTER_VS_COMPUTATION_LIMITED,
			
			/// <summary>
			/// The counter for the percentage of time the geometry shader spends sampling resources.
			/// </summary>
			GeometryShaderMemoryLimited = D3D10_COUNTER_GS_MEMORY_LIMITED,
			
			/// <summary>
			/// The counter for the percentage of time the geometry shader spends performing computations.
			/// </summary>
			GeometryShaderComputationLimited = D3D10_COUNTER_GS_COMPUTATION_LIMITED,
			
			/// <summary>
			/// The counter for the percentage of time the pixel shader spends sampling resources.
			/// </summary>
			PixelShaderMemoryLimited = D3D10_COUNTER_PS_MEMORY_LIMITED,
			
			/// <summary>
			/// The counter for the percentage of time the pixel shader spends performing computations.
			/// </summary>
			PixelShaderComputationLimited = D3D10_COUNTER_PS_COMPUTATION_LIMITED,
			
			/// <summary>
			/// The counter for the percentage of vertex data that was read from the cache.
			/// </summary>
			PostTransformCacheHitRate = D3D10_COUNTER_POST_TRANSFORM_CACHE_HIT_RATE,
			
			/// <summary>
			/// The counter for the percentage of texel data that was read from the cache.
			/// </summary>
			TextureCacheHitRate = D3D10_COUNTER_TEXTURE_CACHE_HIT_RATE
		};
		
		/// <summary>Data type of a performance counter.</summary>
		/// <unmanaged>D3D10_COUNTER_TYPE</unmanaged>
		public enum class CounterType : System::Int32
		{
			/// <summary>
			/// 32-bit floating point.
			/// </summary>
			Float32 = D3D10_COUNTER_TYPE_FLOAT32,
			
			/// <summary>
			/// 16-bit unsigned integer.
			/// </summary>
			UnsignedInt16 = D3D10_COUNTER_TYPE_UINT16,
			
			/// <summary>
			/// 32-bit unsigned integer.
			/// </summary>
			UnsignedInt32 = D3D10_COUNTER_TYPE_UINT32, 
			
			/// <summary>
			/// 64-bit unsigned integer.
			/// </summary>
			UnsignedInt64 = D3D10_COUNTER_TYPE_UINT64
		};
		
		/// <summary>Specifies the types of CPU access allowed for a resource.</summary>
		/// <unmanaged>D3D10_CPU_ACCESS_FLAG</unmanaged>
		[System::Flags]
		public enum class CpuAccessFlags : System::Int32
		{
			/// <summary>
			/// No access is required on the CPU.
			/// </summary>
			None = 0,
			
			/// <summary>
			/// Write access is required on the CPU.
			/// </summary>
			Write = D3D10_CPU_ACCESS_WRITE,
			
			/// <summary>
			/// Read access is required on the CPU.
			/// </summary>
			Read = D3D10_CPU_ACCESS_READ
		};
		
		/// <summary>Indicates triangles facing a particular direction are not drawn.</summary>
		/// <unmanaged>D3D10_CULL_MODE</unmanaged>
		public enum class CullMode : System::Int32 
		{
			/// <summary>
			/// Do not cull; all triangles are rendered.
			/// </summary>
			None = D3D10_CULL_NONE,
			
			/// <summary>
			/// Cull triangles that are front-facing.
			/// </summary>
			Front = D3D10_CULL_FRONT,
			
			/// <summary>
			/// Cull triangles that are back-facing.
			/// </summary>
			Back = D3D10_CULL_BACK
		};
		
		/// <summary>Flags controlling which debug features are enabled.</summary>
		/// <unmanaged href="bb173520">D3D10_DEBUG_FEATURE</unmanaged>
		[System::Flags]
		public enum class DebugFeatureFlags : System::Int32
		{
			/// <summary>
			/// The application will wait for the GPU to complete the render operation before continuing.
			/// </summary>
			FinishPerRender = D3D10_DEBUG_FEATURE_FINISH_PER_RENDER_OP,
			
			/// <summary>
			/// The runtime will call <see cref="SlimDX::Direct3D10::Device">Device.Flush</see> after the render operation.
			/// </summary>
			FlushPerRender = D3D10_DEBUG_FEATURE_FLUSH_PER_RENDER_OP,
			
			/// <summary>
			/// The runtime will call <see cref="SlimDX::DXGI::SwapChain">SwapChain.Present</see> after the render operation.
			/// Presentation of buffers will occur according to the settings specified by the 
			/// <see cref="SlimDX::Direct3D10::Debug">Debug.SwapChain</see> and <see cref="SlimDX::Direct3D10::Debug">Debug.PresentDelay</see> properties.
			/// </summary>
			PresentPerRender = D3D10_DEBUG_FEATURE_PRESENT_PER_RENDER_OP
		};
		
		/// <summary>Specifies which parts of the depth stencil buffer to clear.</summary>
		/// <unmanaged>D3D10_CLEAR_FLAG</unmanaged>
		[System::Flags]
		public enum class DepthStencilClearFlags : System::Int32
		{
			/// <summary>
			/// Indicates the depth buffer should be cleared.
			/// </summary>
			Depth = D3D10_CLEAR_DEPTH,
			
			/// <summary>
			/// Indicates the stencil buffer should be cleared.
			/// </summary>
			Stencil = D3D10_CLEAR_STENCIL
		};
		
		/// <summary>Specified the dimension (and access methodology) for depth-stencil resource views.</summary>
		/// <unmanaged>D3D10_DSV_DIMENSION</unmanaged>
		public enum class DepthStencilViewDimension : System::Int32
		{
			/// <summary>
			/// The resource will be accessed according to its type, determined by the actual resource specified
			/// during the creation of the view.
			/// </summary>
			Unknown = D3D10_DSV_DIMENSION_UNKNOWN,
			
			/// <summary>
			/// The resource will be accessed as a 1D texture.
			/// </summary>
			Texture1D = D3D10_DSV_DIMENSION_TEXTURE1D,
			
			/// <summary>
			/// The resource will be accessed as an array of 1D textures.
			/// </summary>
			Texture1DArray = D3D10_DSV_DIMENSION_TEXTURE1DARRAY,
			
			/// <summary>
			/// The resource will be accessed as a 2D texture.
			/// </summary>
			Texture2D = D3D10_DSV_DIMENSION_TEXTURE2D,
			
			/// <summary>
			/// The resource will be accessed as an array of 2D textures.
			/// </summary>
			Texture2DArray = D3D10_DSV_DIMENSION_TEXTURE2DARRAY,
			
			/// <summary>
			/// The resource will be accessed as a 2D texture with multisampling support.
			/// </summary>
			Texture2DMultisampled = D3D10_DSV_DIMENSION_TEXTURE2DMS,
			
			/// <summary>
			/// The resource will be accessed as an array of 2D textures with multisampling support.
			/// </summary>
			Texture2DMultisampledArray = D3D10_DSV_DIMENSION_TEXTURE2DMSARRAY
		};
		
		/// <summary>Identifies mask values for writing to a depth-stencil buffer.</summary>
		/// <unmanaged>D3D10_DEPTH_WRITE_MASK</unmanaged>
		public enum class DepthWriteMask : System::Int32
		{
			/// <summary>
			/// Disables all writes to the depth-stencil buffer.
			/// </summary>
			Zero = D3D10_DEPTH_WRITE_MASK_ZERO,
			
			/// <summary>
			/// Enables all writes to the depth-stencil buffer.
			/// </summary>
			All = D3D10_DEPTH_WRITE_MASK_ALL
		};
		
		/// <summary>Flags controlling the creation of a device.</summary>
		/// <unmanaged>D3D10_CREATE_DEVICE_FLAG</unmanaged>
		[System::Flags]
		public enum class DeviceCreationFlags : System::Int32
		{
			/// <summary>
			/// Indicates no specific behavior.
			/// </summary>
			None = 0,
			
			/// <summary>
			/// Indicates that a single-threaded device should be created; by default, Direct3D 10 devices are
			/// thread-safe. Specifying this flag causes thread-safety to be disabled.
			/// </summary>
			SingleThreaded = D3D10_CREATE_DEVICE_SINGLETHREADED,
			
			/// <summary>
			/// Indicates that the device should support the debug layer.
			/// </summary>
			Debug = D3D10_CREATE_DEVICE_DEBUG,
			
			/// <summary>
			/// Indicates that both a REF and HAL device should be created, allowing the application to toggle
			/// between them.
			/// </summary>
			SwitchToRef = D3D10_CREATE_DEVICE_SWITCH_TO_REF,
			
			/// <summary>
			/// Reserved. Do not use.
			/// </summary>
			PreventThreadingOptimizations = D3D10_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS
		};
	
		/// <summary>Specifies a device driver type.</summary>
		/// <unmanaged>D3D10_DRIVER_TYPE</unmanaged>
		public enum class DriverType : System::Int32
		{	
			/// <summary>
			/// A hardware (HAL) device.
			/// </summary>
			Hardware = D3D10_DRIVER_TYPE_HARDWARE,
			
			/// <summary>
			/// A software reference (REF) device.
			/// </summary>
			Reference = D3D10_DRIVER_TYPE_REFERENCE,
		
			/// <summary>
			/// A null device (a REF device with no rendering capability).
			/// </summary>
			Null = D3D10_DRIVER_TYPE_NULL,
			
			/// <summary>
			/// Reserved. Do not use.
			/// </summary>
			Software = D3D10_DRIVER_TYPE_SOFTWARE
		};

		/// <summary></summary>
		/// <unmanaged>D3D10_EFFECT</unmanaged>
		[System::Flags]
		public enum class EffectFlags : System::Int32
		{
			None = 0,
			ChildEffect = D3D10_EFFECT_COMPILE_CHILD_EFFECT,
			AllowSlowOperations = D3D10_EFFECT_COMPILE_ALLOW_SLOW_OPS,
			SingleThreaded = D3D10_EFFECT_SINGLE_THREADED,
		};

		/// <summary></summary>
		/// <unmanaged>D3D10_EFFECT_VARIABLE</unmanaged>
		[System::Flags]
		public enum class EffectVariableFlags : System::Int32
		{
			None = 0,
			Annotation = D3D10_EFFECT_VARIABLE_ANNOTATION,
			Pooled = D3D10_EFFECT_VARIABLE_POOLED,
			ExplicitBindPoint = D3D10_EFFECT_VARIABLE_EXPLICIT_BIND_POINT,
		};
		
		/// <summary></summary>
		/// <unmanaged>D3D10_FILL_MODE</unmanaged>
		public enum class FillMode : System::Int32
		{
			Wireframe = D3D10_FILL_WIREFRAME,
			Solid = D3D10_FILL_SOLID
		};

		[System::Flags]
		public enum class Filter : System::Int32
		{
			MinMagMipPoint = D3D10_FILTER_MIN_MAG_MIP_POINT,
			MinMagPointMipLinear = D3D10_FILTER_MIN_MAG_POINT_MIP_LINEAR,
			MinPointMagLinearMipPoint = D3D10_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,
			MinPointMagMipLinear = D3D10_FILTER_MIN_POINT_MAG_MIP_LINEAR,
			MinLinearMagMipPoint = D3D10_FILTER_MIN_LINEAR_MAG_MIP_POINT,
			MinLinearMagPointMipLinear = D3D10_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
			MinMagLinearMipPoint = D3D10_FILTER_MIN_MAG_LINEAR_MIP_POINT,
			MinMagMipLinear = D3D10_FILTER_MIN_MAG_MIP_LINEAR,
			Anisotropic = D3D10_FILTER_ANISOTROPIC,
			ComparisonMinMagMipPoint = D3D10_FILTER_COMPARISON_MIN_MAG_MIP_POINT,
			ComparisonMinMagPointMipLinear = D3D10_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR,
			ComparisonMinPointMagLinearMipPoint = D3D10_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,
			ComparisonMinPointMagMipLinear = D3D10_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR,
			ComparisonMinLinearMagMipPoint = D3D10_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT,
			ComparisonMinLinearMagPointMipLinear = D3D10_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
			ComparisonMinMagLinearMipPoint = D3D10_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
			ComparisonMinMagMipLinear = D3D10_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR,
			ComparisonAnisotropic = D3D10_FILTER_COMPARISON_ANISOTROPIC,
			Texture1Bit = D3D10_FILTER_TEXT_1BIT
		};
		
		/// <summary></summary>
		/// <unmanaged>D3DX10_FILTER_FLAG</unmanaged>
		[System::Flags]
		public enum class FilterFlags : System::Int32
		{
			None = D3DX10_FILTER_NONE,
			Point = D3DX10_FILTER_POINT,
			Linear = D3DX10_FILTER_LINEAR,
			Triangle = D3DX10_FILTER_TRIANGLE,
			Box = D3DX10_FILTER_BOX,
			MirrorU = D3DX10_FILTER_MIRROR_U,
			MirrorV = D3DX10_FILTER_MIRROR_V,
			MirrowW = D3DX10_FILTER_MIRROR_W,
			Mirror = D3DX10_FILTER_MIRROR,
			Dither = D3DX10_FILTER_DITHER,
			DitherDiffusion = D3DX10_FILTER_DITHER_DIFFUSION,
			StandardRgbIn = D3DX10_FILTER_SRGB_IN,
			StandardRgbOut = D3DX10_FILTER_SRGB_OUT,
			StandardRgb = D3DX10_FILTER_SRGB,
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
		/// <unmanaged>D3D10_FORMAT_SUPPORT</unmanaged>
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
		
		/// <summary></summary>
		/// <unmanaged>D3DX10_IMAGE_FILE_FORMAT</unmanaged>
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
		
		/// <summary>Type of data contained in an input slot.</summary>
		/// <unmanaged>D3D10_INPUT_CLASSIFICATION</unmanaged>
		public enum class InputClassification : System::Int32
		{
			PerVertexData = D3D10_INPUT_PER_VERTEX_DATA,
			PerInstanceData = D3D10_INPUT_PER_INSTANCE_DATA
		};
		
		/// <summary>Identifies a resource to be accessed for reading and writing by the CPU.</summary>
		/// <unmanaged>D3D10_MAP</unmanaged>
		public enum class MapMode : System::Int32
		{
			Read = D3D10_MAP_READ,
			Write = D3D10_MAP_WRITE,
			ReadWrite = D3D10_MAP_READ_WRITE,
			WriteDiscard = D3D10_MAP_WRITE_DISCARD,
			WriteNoOverwrite = D3D10_MAP_WRITE_NO_OVERWRITE
		};
		
		/// <summary></summary>
		/// <unmanaged>D3D10_MAP_FLAG</unmanaged>
		[System::Flags]
		public enum class MapFlags : System::Int32
		{
			None = 0,
			DoNotWait = D3D10_MAP_FLAG_DO_NOT_WAIT
		};

		/// <summary></summary>
		/// <unmanaged>D3DX10_MESH</unmanaged>
		[System::Flags]
		public enum class MeshFlags : System::Int32
		{
			None = 0,
			Has32BitIndices = D3DX10_MESH_32_BIT,
			HasAdjacency = D3DX10_MESH_GS_ADJACENCY
		};

		/// <summary></summary>
		/// <unmanaged>D3DX10_MESH_DISCARD_FLAGS</unmanaged>
		[System::Flags]
		public enum class MeshDiscardFlags : System::Int32
		{
			DiscardAttributeBuffer = D3DX10_MESH_DISCARD_ATTRIBUTE_BUFFER,
			DiscardAttributeTable = D3DX10_MESH_DISCARD_ATTRIBUTE_TABLE,
			DiscardPointRepresentation = D3DX10_MESH_DISCARD_POINTREPS,
			DiscardAdjacency = D3DX10_MESH_DISCARD_ADJACENCY,
			DiscardDeviceBuffers = D3DX10_MESH_DISCARD_DEVICE_BUFFERS
		};
		
		/// <summary>
		/// Values that indicate how to alter mesh data during an optimization operation.
		/// </summary>
		/// <unmanaged>D3DX10_MESHOPT</unmanaged>
		[System::Flags]
		public enum class MeshOptimizeFlags : System::Int32
		{
			/// <summary>
			/// Reorders faces to remove unused vertices and faces.
			/// </summary>
			Compact = D3DX10_MESHOPT_COMPACT,
			
			/// <summary>
			/// Reorders faces to optimize for fewer attribute bundle state changes and enhanced draw performance.
			/// </summary>
			AttributeSort = D3DX10_MESHOPT_ATTR_SORT,
	    
			/// <summary>
			/// Reorders faces to increase the cache hit rate of vertex caches.
			/// </summary>
			VertexCache = D3DX10_MESHOPT_VERTEX_CACHE,
	    
			/// <summary>
			/// Reorders faces to maximize length of adjacent triangles.
			/// </summary>
			StripReorder = D3DX10_MESHOPT_STRIP_REORDER,
	    
			/// <summary>
			/// Optimize the faces only; do not optimize the vertices.
			/// </summary>
			IgnoreVertices = D3DX10_MESHOPT_IGNORE_VERTS,
			
			/// <summary>
			/// While attribute sorting, do not split vertices that are shared between attribute groups.
			/// </summary>
			DoNotSplit = D3DX10_MESHOPT_DO_NOT_SPLIT,
			
			/// <summary>
			/// Affects the vertex cache size. Using this flag specifies a default vertex cache size that works well on legacy hardware.
			/// </summary>
			DeviceIndependent = D3DX10_MESHOPT_DEVICE_INDEPENDENT,
		};
		
		/// <summary></summary>
		/// <unmanaged>D3D10_PRIMITIVE_TOPOLOGY</unmanaged>
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
		
		/// <summary>
		/// Flags for describing query options and behavior.
		/// </summary>
		/// <unmanaged>D3D10_QUERY_MISC_FLAG</unmanaged>
		[System::Flags]
		public enum class QueryFlags : System::Int32
		{
			None = 0,
			PredicateHint = D3D10_QUERY_MISC_PREDICATEHINT,
		};
		
		/// <summary>
		/// Values which description query types.
		/// </summary>
		/// <unmanaged>D3D10_QUERY</unmanaged>
		public enum class QueryType : System::Int32
		{
			Event = D3D10_QUERY_EVENT,
			Occlusion = D3D10_QUERY_OCCLUSION,
			Timestamp = D3D10_QUERY_TIMESTAMP,
			TimestampDisjoint = D3D10_QUERY_TIMESTAMP_DISJOINT,
			PipelineStatistics = D3D10_QUERY_PIPELINE_STATISTICS,
			Predicate = D3D10_QUERY_OCCLUSION_PREDICATE,
			StreamOutputStatistics = D3D10_QUERY_SO_STATISTICS,
			StreamOutputOverflowPredicate = D3D10_QUERY_SO_OVERFLOW_PREDICATE,
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
		/// <unmanaged>D3D10_RTV_DIMENSION</unmanaged>
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
		
		/// <summary></summary>
		/// <unmanaged>D3D10_RESOURCE_DIMENSION</unmanaged>
		public enum class ResourceDimension : System::Int32
		{
			Unknown = D3D10_RESOURCE_DIMENSION_UNKNOWN,
			Buffer = D3D10_RESOURCE_DIMENSION_BUFFER,
			Texture1D = D3D10_RESOURCE_DIMENSION_TEXTURE1D,
			Texture2D = D3D10_RESOURCE_DIMENSION_TEXTURE2D,
			Texture3D = D3D10_RESOURCE_DIMENSION_TEXTURE3D
		};
		
		/// <summary></summary>
		/// <unmanaged>D3D10_RESOURCE_MISC_FLAG</unmanaged>
		[System::Flags]
		public enum class ResourceOptionFlags : System::Int32
		{
			None = 0,
			GenerateMipMaps = D3D10_RESOURCE_MISC_GENERATE_MIPS,
			Shared = D3D10_RESOURCE_MISC_SHARED,
			TextureCube = D3D10_RESOURCE_MISC_TEXTURECUBE
		};

		/// <summary></summary>
		/// <unmanaged>D3D10_USAGE</unmanaged>
		public enum class ResourceUsage : System::Int32
		{
			Default = D3D10_USAGE_DEFAULT,
			Immutable = D3D10_USAGE_IMMUTABLE,
			Dynamic = D3D10_USAGE_DYNAMIC,
			Staging = D3D10_USAGE_STAGING
		};
		
		/// <summary></summary>
		/// <unmanaged>D3D10_RTV_DIMENSION</unmanaged>
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
		
		/// <summary>Identifies the type of the resource that will be viewed.</summary>
		/// <unmanaged>D3D10_SRV_DIMENSION</unmanaged>
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

		/// <summary>The stencil operations that can be performed during depth-stencil testing.</summary>
		/// <unmanaged>D3D10_STENCIL_OP</unmanaged>
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

		public enum class TextureAddressMode : System::Int32
		{
			Wrap = D3D10_TEXTURE_ADDRESS_WRAP,
			Mirror = D3D10_TEXTURE_ADDRESS_MIRROR,
			Clamp = D3D10_TEXTURE_ADDRESS_CLAMP,
			Border = D3D10_TEXTURE_ADDRESS_BORDER,
			MirrorOnce = D3D10_TEXTURE_ADDRESS_MIRROR_ONCE
		};
	}
}