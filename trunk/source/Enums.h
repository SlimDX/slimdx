#pragma once

using namespace System;

namespace SlimDX
{
	namespace Direct3D
	{
		public enum class Format : Int32
		{
			R8G8B8 = D3DFMT_R8G8B8,
			A8R8G8B8 = D3DFMT_A8R8G8B8,
			X8R8G8B8 = D3DFMT_X8R8G8B8,
			R5G6B5 = D3DFMT_R5G6B5,
			X1R5G5B5 = D3DFMT_X1R5G5B5,
			A1R5G5B5 = D3DFMT_A1R5G5B5,
			A4R4G4B4 = D3DFMT_A4R4G4B4,
			R3G3B2 = D3DFMT_R3G3B2,
			A8 = D3DFMT_A8,
			A8R3G3B2 = D3DFMT_A8R3G3B2,
			X4R4G4B4 = D3DFMT_X4R4G4B4,
			A2B10G10R10 = D3DFMT_A2B10G10R10,
			A8B8G8R8 = D3DFMT_A8B8G8R8,
			X8B8G8R8 = D3DFMT_X8B8G8R8,
			G16R16 = D3DFMT_G16R16,
			A2R10G10B10 = D3DFMT_A2R10G10B10,
			A16B16G16R16 = D3DFMT_A16B16G16R16,

			A8P8 = D3DFMT_A8P8,
			P8 = D3DFMT_P8,

			L8 = D3DFMT_L8,
			A8L8 = D3DFMT_A8L8,
			A4L4 = D3DFMT_A4L4,

			V8U8 = D3DFMT_V8U8,
			L6V5U5 = D3DFMT_L6V5U5,
			X8L8V8U8 = D3DFMT_X8L8V8U8,
			Q8W8V8U8 = D3DFMT_Q8W8V8U8,
			V16U16 = D3DFMT_V16U16,
			A2W10V10U10 = D3DFMT_A2W10V10U10,

			Uyvy = D3DFMT_UYVY,
			Yuy2 = D3DFMT_YUY2,
			Dxt1 = D3DFMT_DXT1,
			Dxt2 = D3DFMT_DXT2,
			Dxt3 = D3DFMT_DXT3,
			Dxt4 = D3DFMT_DXT4,
			Dxt5 = D3DFMT_DXT5,

			Q16W16V16U16 = D3DFMT_Q16W16V16U16,

			Multi2Argb8 = D3DFMT_MULTI2_ARGB8,

			R16F = D3DFMT_R16F,
			G16R16F = D3DFMT_G16R16F,
			A16B16G16R16F = D3DFMT_A16B16G16R16F,

			R32F = D3DFMT_R32F,
			G32R32F = D3DFMT_G32R32F,
			A32B32G32R32F = D3DFMT_A32B32G32R32F,

			CxV8U8 = D3DFMT_CxV8U8,

			D15S1 = D3DFMT_D15S1,
			D16 = D3DFMT_D16,
			D16Lockable = D3DFMT_D16_LOCKABLE,
			D24S8 = D3DFMT_D24S8,
			D24SingleS8 = D3DFMT_D24FS8,
			D24X4S4 = D3DFMT_D24X4S4,
			D24X8 = D3DFMT_D24X8,
			D32 = D3DFMT_D32,
			D32SingleLockable = D3DFMT_D32F_LOCKABLE,
			L16 = D3DFMT_L16,

			VertexData = D3DFMT_VERTEXDATA,
			Index16 = D3DFMT_INDEX16,
			Index32 = D3DFMT_INDEX32,

			Unknown = D3DFMT_UNKNOWN,
		};

		public enum class DepthFormat : Int32
		{
			D15S1 = D3DFMT_D15S1,
			D16 = D3DFMT_D16,
			D16Lockable = D3DFMT_D16_LOCKABLE,
			D24S8 = D3DFMT_D24S8,
			D24SingleS8 = D3DFMT_D24FS8,
			D24X4S4 = D3DFMT_D24X4S4,
			D24X8 = D3DFMT_D24X8,
			D32 = D3DFMT_D32,
			D32SingleLockable = D3DFMT_D32F_LOCKABLE,
			L16 = D3DFMT_L16,
			Unknown = D3DFMT_UNKNOWN
		};

		[Flags]
		public enum class CreateFlags : Int32
		{
			AdapterGroupDevice = D3DCREATE_ADAPTERGROUP_DEVICE,
			DisableDriverManagement = D3DCREATE_DISABLE_DRIVER_MANAGEMENT,
			DisableDriverManagementEx = D3DCREATE_DISABLE_DRIVER_MANAGEMENT_EX,
			FpuPreserve = D3DCREATE_FPU_PRESERVE,
			HardwareVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING,
			MixedVertexProcessing = D3DCREATE_MIXED_VERTEXPROCESSING,
			MultiThreaded = D3DCREATE_MULTITHREADED,
			NoWindowChanges = D3DCREATE_NOWINDOWCHANGES,
			PureDevice = D3DCREATE_PUREDEVICE,
			SoftwareVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		};

		[Flags]
		public enum class Usage : Int32
		{
			None = 0,
			AutoGenerateMipMap = D3DUSAGE_AUTOGENMIPMAP,
			DepthStencil = D3DUSAGE_DEPTHSTENCIL,
			DoNotClip = D3DUSAGE_DONOTCLIP,
			Dynamic = D3DUSAGE_DYNAMIC,
			NPatches = D3DUSAGE_NPATCHES,
			Points = D3DUSAGE_POINTS,
			RenderTarget = D3DUSAGE_RENDERTARGET,
			WriteOnly = D3DUSAGE_WRITEONLY
		};

		public enum class Pool : Int32
		{
			Default = D3DPOOL_DEFAULT,
			Managed = D3DPOOL_MANAGED,
			SystemMem = D3DPOOL_SYSTEMMEM,
			Scratch = D3DPOOL_SCRATCH,
		};

		[Flags]
		public enum class Filter : Int32
		{
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

		[Flags]
		public enum class VertexFormats : Int32
		{
			None = 0,
			Position = D3DFVF_XYZ,
			PositionW = D3DFVF_XYZRHW,
			Normal = D3DFVF_NORMAL,
			PositionNormal = Position | Normal,
			Diffuse = D3DFVF_DIFFUSE,
			Texture0 = D3DFVF_TEX0,
			Texture1 = D3DFVF_TEX1,
			Texture2 = D3DFVF_TEX2,
			Texture3 = D3DFVF_TEX3,
			Texture4 = D3DFVF_TEX4,
			Texture5 = D3DFVF_TEX5,
			Texture6 = D3DFVF_TEX6,
			Texture7 = D3DFVF_TEX7,
			Texture8 = D3DFVF_TEX8,
		};

		public enum class PrimitiveType : Int32
		{
			PointList = D3DPT_POINTLIST,
			LineList = D3DPT_LINELIST,
			LineStrip = D3DPT_LINESTRIP,
			TriangleList = D3DPT_TRIANGLELIST,
			TriangleStrip = D3DPT_TRIANGLESTRIP,
			TriangleFan = D3DPT_TRIANGLEFAN
		};

		[Flags]
		public enum class ShaderFlags : Int32
		{
			None = 0,
			AvoidFlowControl = D3DXSHADER_AVOID_FLOW_CONTROL,
			Debug = D3DXSHADER_DEBUG,
			NoPreShader = D3DXSHADER_NO_PRESHADER,
			PartialPrecision = D3DXSHADER_PARTIALPRECISION,
			PreferFlowControl = D3DXSHADER_PREFER_FLOW_CONTROL,
			SkipOptimization = D3DXSHADER_SKIPOPTIMIZATION,
			SkipValdation = D3DXSHADER_SKIPVALIDATION,
		};

		[Flags]
		public enum class FX : Int32
		{
			None = 0,
			DoNotSaveState = D3DXFX_DONOTSAVESTATE,
			DoNotSaveShaderState = D3DXFX_DONOTSAVESHADERSTATE,
			DoNotSaveSamplerState = D3DXFX_DONOTSAVESAMPLERSTATE,
		};

		[Flags]
		public enum class LockFlags : Int32
		{
			Discard = D3DLOCK_DISCARD,
			DoNotWait = D3DLOCK_DONOTWAIT,
			NoDirtyUpdate = D3DLOCK_NO_DIRTY_UPDATE,
			None = 0,
			NoOverwrite = D3DLOCK_NOOVERWRITE,
			NoSystemLock = D3DLOCK_NOSYSLOCK,
			ReadOnly = D3DLOCK_READONLY
		};

		public enum class DeclarationMethod : Byte
		{
			Default = D3DDECLMETHOD_DEFAULT,
			PartialU = D3DDECLMETHOD_PARTIALU,
			PartialV = D3DDECLMETHOD_PARTIALV,
			CrossUV = D3DDECLMETHOD_CROSSUV,
			UV = D3DDECLMETHOD_UV,
			LookUp = D3DDECLMETHOD_LOOKUP,
			LookUpPresampled = D3DDECLMETHOD_LOOKUPPRESAMPLED
		};

		public enum class DeclarationType : Byte
		{
			Float1 = D3DDECLTYPE_FLOAT1,
			Float2 = D3DDECLTYPE_FLOAT2,
			Float3 = D3DDECLTYPE_FLOAT3,
			Float4 = D3DDECLTYPE_FLOAT4,
			Color = D3DDECLTYPE_D3DCOLOR,

			Ubyte4 = D3DDECLTYPE_UBYTE4,
			Short2 = D3DDECLTYPE_SHORT2,
			Short4 = D3DDECLTYPE_SHORT4,

			UByte4N = D3DDECLTYPE_UBYTE4N,
			Short2N = D3DDECLTYPE_SHORT2N,
			Short4N = D3DDECLTYPE_SHORT4N,
			UShort2N = D3DDECLTYPE_USHORT2N,
			UShort4N = D3DDECLTYPE_USHORT4N,
			UDec3 = D3DDECLTYPE_UDEC3,
			Dec3N = D3DDECLTYPE_DEC3N,
			Float16Two = D3DDECLTYPE_FLOAT16_2,
			Float16Four = D3DDECLTYPE_FLOAT16_4,

			Unused = D3DDECLTYPE_UNUSED
		};

		public enum class DeclarationUsage : Byte
		{
			Position = D3DDECLUSAGE_POSITION,
			BlendWeight = D3DDECLUSAGE_BLENDWEIGHT,
			BlendIndices = D3DDECLUSAGE_BLENDINDICES,
			Normal = D3DDECLUSAGE_NORMAL,
			PointSize = D3DDECLUSAGE_PSIZE,
			TextureCoordinate = D3DDECLUSAGE_TEXCOORD,
			Tangent = D3DDECLUSAGE_TANGENT,
			BiNormal = D3DDECLUSAGE_BINORMAL,
			TessellateFactor = D3DDECLUSAGE_TESSFACTOR,
			PositionTransformed = D3DDECLUSAGE_POSITIONT,
			Color = D3DDECLUSAGE_COLOR,
			Fog = D3DDECLUSAGE_FOG,
			Depth = D3DDECLUSAGE_DEPTH,
			Sample = D3DDECLUSAGE_SAMPLE
		};

		public enum class CubeMapFace : Int32
		{
			PositiveX = D3DCUBEMAP_FACE_POSITIVE_X,
			NegativeX = D3DCUBEMAP_FACE_NEGATIVE_X,
			PositiveY = D3DCUBEMAP_FACE_POSITIVE_Y,
			NegativeY = D3DCUBEMAP_FACE_NEGATIVE_Y,
			PositiveZ = D3DCUBEMAP_FACE_POSITIVE_Z,
			NegativeZ = D3DCUBEMAP_FACE_NEGATIVE_Z
		};

		[Flags]
		public enum class ClearFlags : Int32
		{
			Stencil = D3DCLEAR_STENCIL,
			Target = D3DCLEAR_TARGET,
			ZBuffer = D3DCLEAR_ZBUFFER
		};

		public enum class Cull : Int32
		{
			Clockwise = D3DCULL_CW,
			CounterClockwise = D3DCULL_CCW,
			None = D3DCULL_NONE
		};

		public enum class SwapEffect : Int32
		{
			Discard = D3DSWAPEFFECT_DISCARD,
			Flip = D3DSWAPEFFECT_FLIP,
			Copy = D3DSWAPEFFECT_COPY,
		};

		[Flags]
		public enum class PresentFlag : Int32
		{
			DeviceClip = D3DPRESENTFLAG_DEVICECLIP,
			DiscardDepthStencil = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL,
			LockableBackBuffer = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER,
			None = 0,
			Video = D3DPRESENTFLAG_VIDEO
		};

		public enum class PresentInterval : Int32
		{
			Default = D3DPRESENT_INTERVAL_DEFAULT,
			Immediate = (int) D3DPRESENT_INTERVAL_IMMEDIATE,
			One = D3DPRESENT_INTERVAL_ONE,
			Two = D3DPRESENT_INTERVAL_TWO,
			Three = D3DPRESENT_INTERVAL_THREE,
			Four = D3DPRESENT_INTERVAL_FOUR
		};

		public enum class MultiSampleType : Int32
		{
			None = D3DMULTISAMPLE_NONE,
			NonMaskable = D3DMULTISAMPLE_NONMASKABLE,
			TwoSamples = D3DMULTISAMPLE_2_SAMPLES,
			ThreeSamples = D3DMULTISAMPLE_3_SAMPLES,
			FourSamples = D3DMULTISAMPLE_4_SAMPLES,
			FiveSamples = D3DMULTISAMPLE_5_SAMPLES,
			SixSamples = D3DMULTISAMPLE_6_SAMPLES,
			SevenSamples = D3DMULTISAMPLE_7_SAMPLES,
			EightSamples = D3DMULTISAMPLE_8_SAMPLES,
			NineSamples = D3DMULTISAMPLE_9_SAMPLES,
			TenSamples = D3DMULTISAMPLE_10_SAMPLES,
			ElevenSamples = D3DMULTISAMPLE_11_SAMPLES,
			TwelveSamples = D3DMULTISAMPLE_12_SAMPLES,
			ThirteenSamples = D3DMULTISAMPLE_13_SAMPLES,
			FourteenSamples = D3DMULTISAMPLE_14_SAMPLES,
			FifteenSamples = D3DMULTISAMPLE_15_SAMPLES,
			SixteenSamples = D3DMULTISAMPLE_16_SAMPLES
		};

		public enum class DeviceType : Int32
		{
			Hardware = D3DDEVTYPE_HAL,
			NullReference = D3DDEVTYPE_NULLREF,
			Reference = D3DDEVTYPE_REF,
			Software = D3DDEVTYPE_SW
		};
	}
}
