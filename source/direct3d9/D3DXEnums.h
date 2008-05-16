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

namespace SlimDX
{
	namespace Direct3D9
	{
		// NOTE: The enumerations defined in this file are in alphabetical order. When
		//       adding new enumerations or renaming existing ones, please make sure
		//       the ordering is maintained.

		[System::Flags]
		public enum class AnimationOutputFlags : System::Int32
		{
			None,
			Transformation,
			Translation,
			Scale,
			Rotation
		};

		public enum class CallbackSearchFlags : System::Int32
		{
			SearchExcludingInitialPosition = D3DXCALLBACK_SEARCH_EXCLUDING_INITIAL_POSITION,
			SearchBehindInitialPosition = D3DXCALLBACK_SEARCH_BEHIND_INITIAL_POSITION
		};

		[System::Flags]
		public enum class Channel : System::Int32
		{
			Red = D3DX_CHANNEL_RED,
			Blue = D3DX_CHANNEL_BLUE,
			Green = D3DX_CHANNEL_GREEN,
			Alpha = D3DX_CHANNEL_ALPHA,
			Luminance = D3DX_CHANNEL_LUMINANCE
		};

		[System::Flags]
		public enum class CleanType : System::Int32
		{
			BackFacing = D3DXCLEAN_BACKFACING,
			Bowties = D3DXCLEAN_BOWTIES,
			Skinning = D3DXCLEAN_SKINNING,
			Optimization = D3DXCLEAN_OPTIMIZATION,
			Simplification = D3DXCLEAN_SIMPLIFICATION
		};

		public enum class EffectDefaultType : System::Int32
		{
			String = D3DXEDT_STRING,
			Floats = D3DXEDT_FLOATS,
			Dword = D3DXEDT_DWORD,
		};

		public enum class EventType : System::Int32
		{
			TrackSpeed = D3DXEVENT_TRACKSPEED,
			TrackWeight = D3DXEVENT_TRACKWEIGHT,
			TrackPosition = D3DXEVENT_TRACKPOSITION,
			TrackEnable = D3DXEVENT_TRACKENABLE,
			PriorityBlend = D3DXEVENT_PRIORITYBLEND
		};

		[System::Flags]
		public enum class Filter : System::Int32
		{
			Default = (int) D3DX_DEFAULT,
			None = D3DX_FILTER_NONE,
			Point = D3DX_FILTER_POINT,
			Linear = D3DX_FILTER_LINEAR,
			Triangle = D3DX_FILTER_TRIANGLE,
			Box = D3DX_FILTER_BOX,
			MirrorU = D3DX_FILTER_MIRROR_U,
			MirrorV = D3DX_FILTER_MIRROR_V,
			MirrorW = D3DX_FILTER_MIRROR_W,
			Mirror = D3DX_FILTER_MIRROR,
			Dither = D3DX_FILTER_DITHER,
			Srgb = D3DX_FILTER_SRGB,
			SrgbIn = D3DX_FILTER_SRGB_IN,
			SrgbOut = D3DX_FILTER_SRGB_OUT
		};

		[System::Flags]
		public enum class FX : System::Int32
		{
			None = 0,
			DoNotSaveState = D3DXFX_DONOTSAVESTATE,
			DoNotSaveShaderState = D3DXFX_DONOTSAVESHADERSTATE,
			DoNotSaveSamplerState = D3DXFX_DONOTSAVESAMPLERSTATE,
		};

		public enum class ImageFileFormat : System::Int32
		{
			Bmp = D3DXIFF_BMP,
			Jpg = D3DXIFF_JPG,
			Tga = D3DXIFF_TGA,
			Png = D3DXIFF_PNG,
			Dds = D3DXIFF_DDS,
			Ppm = D3DXIFF_PPM,
			Dib = D3DXIFF_DIB,
			Hdr = D3DXIFF_HDR,
			Pfm = D3DXIFF_PFM,
		};

		public enum class IncludeType : System::Int32
		{
			Local = D3DXINC_LOCAL,
			System = D3DXINC_SYSTEM,
		};

		public enum class MeshDataType : System::Int32
		{
			Mesh = D3DXMESHTYPE_MESH,
			ProgressiveMesh = D3DXMESHTYPE_PMESH,
			PatchMesh = D3DXMESHTYPE_PATCHMESH
		};

		[System::Flags]
		public enum class MeshFlags : System::Int32
		{
			Use32Bit = D3DXMESH_32BIT,
			DoNotClip = D3DXMESH_DONOTCLIP,
			Points = D3DXMESH_POINTS,
			RTPatches = D3DXMESH_RTPATCHES,
			NPatches = D3DXMESH_NPATCHES,
			VertexBufferSystemMemory = D3DXMESH_VB_SYSTEMMEM,
			VertexBufferManaged = D3DXMESH_VB_MANAGED,
			VertexBufferWriteOnly = D3DXMESH_VB_WRITEONLY,
			VertexBufferDynamic = D3DXMESH_VB_DYNAMIC,
			VertexBufferSoftware = D3DXMESH_VB_SOFTWAREPROCESSING,
			IndexBufferSystemMemory = D3DXMESH_IB_SYSTEMMEM,
			IndexBufferManaged = D3DXMESH_IB_MANAGED,
			IndexBufferWriteOnly = D3DXMESH_IB_WRITEONLY,
			IndexBufferDynamic = D3DXMESH_IB_DYNAMIC,
			IndexBufferSoftware = D3DXMESH_IB_SOFTWAREPROCESSING,

			VertexBufferShare = D3DXMESH_VB_SHARE,

			UseHardwareOnly = D3DXMESH_USEHWONLY,

			// Helper options
			SystemMemory = D3DXMESH_SYSTEMMEM,
			Managed = D3DXMESH_MANAGED,
			WriteOnly = D3DXMESH_WRITEONLY,
			Dynamic = D3DXMESH_DYNAMIC,
			Software = D3DXMESH_SOFTWAREPROCESSING,
		};

		[System::Flags]
		public enum class MeshOptimizeFlags : System::Int32
		{
			Compact = D3DXMESHOPT_COMPACT,
			AttributeSort = D3DXMESHOPT_ATTRSORT,
			VertexCache = D3DXMESHOPT_VERTEXCACHE,
			StripReorder = D3DXMESHOPT_STRIPREORDER,
			IgnoreVertices = D3DXMESHOPT_IGNOREVERTS,
			DoNotSplit = D3DXMESHOPT_DONOTSPLIT,
			DeviceIndependent = D3DXMESHOPT_DEVICEINDEPENDENT,
		};

		public enum class MeshSimplification : System::Int32
		{
			Vertex = D3DXMESHSIMP_VERTEX,
			Face = D3DXMESHSIMP_FACE
		};

		[System::Flags]
		public enum class NormalMapFlags : System::Int32
		{
			MirrorU = D3DX_NORMALMAP_MIRROR_U,
			MirrorV = D3DX_NORMALMAP_MIRROR_V,
			Mirror = D3DX_NORMALMAP_MIRROR,
			InvertSign = D3DX_NORMALMAP_INVERTSIGN,
			ComputeOcclusion = D3DX_NORMALMAP_COMPUTE_OCCLUSION
		};
		
		public enum class ParameterClass : System::Int32
		{
			Scalar = D3DXPC_SCALAR,
			Vector = D3DXPC_VECTOR,
			MatrixRows = D3DXPC_MATRIX_ROWS,
			MatrixColumns = D3DXPC_MATRIX_COLUMNS,
			Object = D3DXPC_OBJECT,
			Struct = D3DXPC_STRUCT,
		};

		[System::Flags]
		public enum class ParameterFlags : System::Int32
		{
			None = 0,
			Shared = D3DX_PARAMETER_SHARED,
			Literal = D3DX_PARAMETER_LITERAL,
			Annotation = D3DX_PARAMETER_ANNOTATION,
		};

		public enum class ParameterType : System::Int32
		{
			Void = D3DXPT_VOID,
			Bool = D3DXPT_BOOL,
			Int = D3DXPT_INT,
			Float = D3DXPT_FLOAT,
			String = D3DXPT_STRING,
			Texture = D3DXPT_TEXTURE,
			Texture1D = D3DXPT_TEXTURE1D,
			Texture2D = D3DXPT_TEXTURE2D,
			Texture3D = D3DXPT_TEXTURE3D,
			TextureCube = D3DXPT_TEXTURECUBE,
			Sampler = D3DXPT_SAMPLER,
			Sampler1D = D3DXPT_SAMPLER1D,
			Sampler2D = D3DXPT_SAMPLER2D,
			Sampler3D = D3DXPT_SAMPLER3D,
			SamplerCube = D3DXPT_SAMPLERCUBE,
			PixelShader = D3DXPT_PIXELSHADER,
			VertexShader = D3DXPT_VERTEXSHADER,
			PixelFragment = D3DXPT_PIXELFRAGMENT,
			VertexFragment = D3DXPT_VERTEXFRAGMENT,
			X = D3DX_PARAMETER_ANNOTATION
		};

		public enum class PatchMeshType : System::Int32
		{
			Rectangle = D3DXPATCHMESH_RECT,
			Triangle = D3DXPATCHMESH_TRI,
			NPatch = D3DXPATCHMESH_NPATCH
		};

		public enum class PlaybackType : System::Int32
		{
			Loop = D3DXPLAY_LOOP,
			Once = D3DXPLAY_ONCE,
			PingPong = D3DXPLAY_PINGPONG
		};

		public enum class RegisterSet : System::Int32
		{
			Bool = D3DXRS_BOOL,
			Int4 = D3DXRS_INT4,
			Float4 = D3DXRS_FLOAT4,
			Sampler = D3DXRS_SAMPLER,
		};

		[System::Flags]
		public enum class ShaderFlags : System::Int32
		{
			None = 0,

			PackMatrixColumnMajor = D3DXSHADER_PACKMATRIX_COLUMNMAJOR,
			PackMatrixRowMajor = D3DXSHADER_PACKMATRIX_ROWMAJOR,

			AvoidFlowControl = D3DXSHADER_AVOID_FLOW_CONTROL,
			Debug = D3DXSHADER_DEBUG,
			EnableBackwardsCompatibility = D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY,
			ForcePSSoftwareNoOpt = D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT,
			ForceVSSoftwareNoOpt = D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT,
			IeeeStrictness = D3DXSHADER_IEEE_STRICTNESS,
			NoPreshader = D3DXSHADER_NO_PRESHADER,
			OptimizationLevel0 = D3DXSHADER_OPTIMIZATION_LEVEL0,
			OptimizationLevel1 = D3DXSHADER_OPTIMIZATION_LEVEL1,
			OptimizationLevel2 = D3DXSHADER_OPTIMIZATION_LEVEL2,
			OptimizationLevel3 = D3DXSHADER_OPTIMIZATION_LEVEL3,
			PartialPrecision = D3DXSHADER_PARTIALPRECISION,
			PreferFlowControl = D3DXSHADER_PREFER_FLOW_CONTROL,
			SkipValidation = D3DXSHADER_SKIPVALIDATION,
			SkipOptimization = D3DXSHADER_SKIPOPTIMIZATION,
		};

		[System::Flags]
		public enum class SpriteFlags : System::Int32
		{
			None = 0,
			DoNotSaveState = D3DXSPRITE_DONOTSAVESTATE,
			DoNotModifyRenderState = D3DXSPRITE_DONOTMODIFY_RENDERSTATE,
			ObjectSpace = D3DXSPRITE_OBJECTSPACE,
			Billboard = D3DXSPRITE_BILLBOARD,
			AlphaBlend = D3DXSPRITE_ALPHABLEND,
			Texture = D3DXSPRITE_SORT_TEXTURE,
			SortDepthFrontToBack = D3DXSPRITE_SORT_DEPTH_FRONTTOBACK,
			SortDepthBackToFront = D3DXSPRITE_SORT_DEPTH_BACKTOFRONT,
		};

		[System::Flags]
		public enum class TangentOptions : System::Int32
		{
			None = 0,
			WrapU = D3DXTANGENT_WRAP_U,
			WrapV = D3DXTANGENT_WRAP_V,
			WrapUV = D3DXTANGENT_WRAP_UV,
			DontNormalizePartials = D3DXTANGENT_DONT_NORMALIZE_PARTIALS,
			DontOrthogonalize = D3DXTANGENT_DONT_ORTHOGONALIZE,
			OrthogonalizeFromV = D3DXTANGENT_ORTHOGONALIZE_FROM_V,
			OrthogonalizeFromU = D3DXTANGENT_ORTHOGONALIZE_FROM_U,
			WeightByArea = D3DXTANGENT_WEIGHT_BY_AREA,
			WeightEqual = D3DXTANGENT_WEIGHT_EQUAL,
			WindCW = D3DXTANGENT_WIND_CW,
			CalculateNormals = D3DXTANGENT_CALCULATE_NORMALS,
			GenerateInPlace = D3DXTANGENT_GENERATE_IN_PLACE,
		};

		public enum class TrackPriority : System::Int32
		{
			Low = D3DXPRIORITY_LOW,
			High = D3DXPRIORITY_HIGH
		};

		public enum class TransitionType : System::Int32
		{
			Linear = D3DXTRANSITION_LINEAR,
			EaseInEaseOut = D3DXTRANSITION_EASEINEASEOUT
		};
	}
}