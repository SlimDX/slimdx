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
	namespace Direct3D9
	{
		public enum class D3DErrorCode : Int32
		{
			Ok = D3D_OK,

			WrongTextureFormat = D3DERR_WRONGTEXTUREFORMAT,
			UnsupportedColorOperation = D3DERR_UNSUPPORTEDCOLOROPERATION,
			UnsupportedColorArgument = D3DERR_UNSUPPORTEDCOLORARG,
			UnsupportedAlphaOperation = D3DERR_UNSUPPORTEDALPHAOPERATION,
			UnsupportedAlphaArgument = D3DERR_UNSUPPORTEDALPHAARG,
			TooManyOperations = D3DERR_TOOMANYOPERATIONS,
			ConflictingTextureFilter = D3DERR_CONFLICTINGTEXTUREFILTER,
			UnsupportedFactorValue = D3DERR_UNSUPPORTEDFACTORVALUE,
			ConflictingRenderState = D3DERR_CONFLICTINGRENDERSTATE,
			UnsupportedTextureFilter = D3DERR_UNSUPPORTEDTEXTUREFILTER,
			ConflictingTexturePalette = D3DERR_CONFLICTINGTEXTUREPALETTE,
			DriverInternalError = D3DERR_DRIVERINTERNALERROR,

			NotFound = D3DERR_NOTFOUND,
			MoreData = D3DERR_MOREDATA,
			DeviceLost = D3DERR_DEVICELOST,
			DeviceNotReset = D3DERR_DEVICENOTRESET,
			NotAvailable = D3DERR_NOTAVAILABLE,
			OutOfVideoMemory = D3DERR_OUTOFVIDEOMEMORY,
			InvalidDevice = D3DERR_INVALIDDEVICE,
			InvalidCall = D3DERR_INVALIDCALL,
			DriverInvalidCall = D3DERR_DRIVERINVALIDCALL,
			WasStillDrawing = D3DERR_WASSTILLDRAWING,
			NoAutoGen = D3DOK_NOAUTOGEN,
		};

		public enum class D3DXFileErrorCode : Int32
		{
			BadObject = D3DXFERR_BADOBJECT,
			BadValue = D3DXFERR_BADVALUE,
			BadType = D3DXFERR_BADTYPE,
			NotFound = D3DXFERR_NOTFOUND,
			NotDoneYet = D3DXFERR_NOTDONEYET,
			FileNotFound = D3DXFERR_FILENOTFOUND,
			ResourceNotFound = D3DXFERR_RESOURCENOTFOUND,
			BadResource = D3DXFERR_BADRESOURCE,
			BadFileType = D3DXFERR_BADFILETYPE,
			BadFileVersion = D3DXFERR_BADFILEVERSION,
			BadFileFloatSize = D3DXFERR_BADFILEFLOATSIZE,
			BadFile = D3DXFERR_BADFILE,
			ParseError = D3DXFERR_PARSEERROR,
			BadArraySize = D3DXFERR_BADARRAYSIZE,
			BadDataReference = D3DXFERR_BADDATAREFERENCE,
			NoMoreObjects = D3DXFERR_NOMOREOBJECTS,
			NoMoreData = D3DXFERR_NOMOREDATA,
			BadCacheFile = D3DXFERR_BADCACHEFILE,
		};

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
			WriteOnly = D3DUSAGE_WRITEONLY,
			SoftwareProcessing = D3DUSAGE_SOFTWAREPROCESSING
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

		public enum class TextureFilter : Int32
		{
			None = D3DTEXF_NONE,
			Point = D3DTEXF_POINT,
			Linear = D3DTEXF_LINEAR,
			Anisotropic = D3DTEXF_ANISOTROPIC,
			PyramidalQuad = D3DTEXF_PYRAMIDALQUAD,
			GaussianQuad = D3DTEXF_GAUSSIANQUAD,
		};

		[Flags]
		public enum class VertexFormat : Int32
		{
			None = 0,

			PositionMask = D3DFVF_POSITION_MASK,
			Position = D3DFVF_XYZ,
			PositionRhw = D3DFVF_XYZRHW,
			PositionBlend1 = D3DFVF_XYZB1,
			PositionBlend2 = D3DFVF_XYZB2,
			PositionBlend3 = D3DFVF_XYZB3,
			PositionBlend4 = D3DFVF_XYZB4,
			PositionBlend5 = D3DFVF_XYZB5,
			PositionW = D3DFVF_XYZW,

			Normal = D3DFVF_NORMAL,
			PointSize = D3DFVF_PSIZE,
			Diffuse = D3DFVF_DIFFUSE,
			Specular = D3DFVF_SPECULAR,

			TextureCountMask = D3DFVF_TEXCOUNT_MASK,
			TextureCountShift = D3DFVF_TEXCOUNT_SHIFT,
			Texture0 = D3DFVF_TEX0,
			Texture1 = D3DFVF_TEX1,
			Texture2 = D3DFVF_TEX2,
			Texture3 = D3DFVF_TEX3,
			Texture4 = D3DFVF_TEX4,
			Texture5 = D3DFVF_TEX5,
			Texture6 = D3DFVF_TEX6,
			Texture7 = D3DFVF_TEX7,
			Texture8 = D3DFVF_TEX8,

			LastBetaUByte4 = D3DFVF_LASTBETA_UBYTE4,
			LastBetaColor = D3DFVF_LASTBETA_D3DCOLOR,

			PositionNormal = Position | Normal
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

		[Flags]
		public enum class PresentInterval : Int32
		{
			Default = D3DPRESENT_INTERVAL_DEFAULT,
			Immediate = (int) D3DPRESENT_INTERVAL_IMMEDIATE,
			One = D3DPRESENT_INTERVAL_ONE,
			Two = D3DPRESENT_INTERVAL_TWO,
			Three = D3DPRESENT_INTERVAL_THREE,
			Four = D3DPRESENT_INTERVAL_FOUR,
		};

		[Flags]
		public enum class Present : Int32
		{
			DoNotWait = D3DPRESENT_DONOTWAIT,
			LinearContent = D3DPRESENT_LINEAR_CONTENT
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

		public enum class Blend : Int32
		{
			Zero = D3DBLEND_ZERO,
			One = D3DBLEND_ONE,
			SourceColor = D3DBLEND_SRCCOLOR,
			InvSourceColor = D3DBLEND_INVSRCCOLOR,
			SourceAlpha = D3DBLEND_SRCALPHA,
			InvSourceAlpha = D3DBLEND_INVSRCALPHA,
			DestAlpha = D3DBLEND_DESTALPHA,
			InvDestAlpha = D3DBLEND_INVDESTALPHA,
			DestColor = D3DBLEND_DESTCOLOR,
			InvDestColor = D3DBLEND_INVDESTCOLOR,
			SourceAlphaSat = D3DBLEND_SRCALPHASAT,
			BothSourceAlpha = D3DBLEND_BOTHSRCALPHA,
			BothInvSourceAlpha = D3DBLEND_BOTHINVSRCALPHA,
			BlendFactor = D3DBLEND_BLENDFACTOR,
			InvBlendFactor = D3DBLEND_INVBLENDFACTOR,
		};

		public enum class ColorSource : Int32
		{
			Material = D3DMCS_MATERIAL,
			Color1 = D3DMCS_COLOR1,
			Color2 = D3DMCS_COLOR2,
		};

		public enum class CooperativeLevel : Int32
		{
			Ok = D3D_OK,
			DeviceLost = D3DERR_DEVICELOST,
			DeviceNotReset = D3DERR_DEVICENOTRESET,
			DriverInternalError = D3DERR_DRIVERINTERNALERROR,
		};

		public enum class QueryType : Int32
		{
			VCache = D3DQUERYTYPE_VCACHE,
			ResourceManager = D3DQUERYTYPE_RESOURCEMANAGER,
			VertexStats = D3DQUERYTYPE_VERTEXSTATS,
			Event = D3DQUERYTYPE_EVENT,
			Occlusion = D3DQUERYTYPE_OCCLUSION,
			Timestamp = D3DQUERYTYPE_TIMESTAMP,
			TimestampDisjoint = D3DQUERYTYPE_TIMESTAMPDISJOINT,
			TimestampFreq = D3DQUERYTYPE_TIMESTAMPFREQ,
			PipelineTimings = D3DQUERYTYPE_PIPELINETIMINGS,
			InterfaceTimings = D3DQUERYTYPE_INTERFACETIMINGS,
			VertexTimings = D3DQUERYTYPE_VERTEXTIMINGS,
			PixelTimings = D3DQUERYTYPE_PIXELTIMINGS,
			BandwidthTimings = D3DQUERYTYPE_BANDWIDTHTIMINGS,
			CacheUtilization = D3DQUERYTYPE_CACHEUTILIZATION,
		};

		public enum class FillMode : Int32
		{
			Point = D3DFILL_POINT,
			Wireframe = D3DFILL_WIREFRAME,
			Solid = D3DFILL_SOLID
		};

		public enum class RenderState : Int32
		{
			ZEnable = D3DRS_ZENABLE,
			FillMode = D3DRS_FILLMODE,
			ShadeMode = D3DRS_SHADEMODE,
			ZWriteEnable = D3DRS_ZWRITEENABLE,
			AlphaTestEnable = D3DRS_ALPHATESTENABLE,
			LastPixel = D3DRS_LASTPIXEL,
			SourceBlend = D3DRS_SRCBLEND,
			DestBlend = D3DRS_DESTBLEND,
			CullMode = D3DRS_CULLMODE,
			ZFunc = D3DRS_ZFUNC,
			AlphaRef = D3DRS_ALPHAREF,
			AlphaFunc = D3DRS_ALPHAFUNC,
			DitherEnable = D3DRS_DITHERENABLE,
			AlphaBlendEnable = D3DRS_ALPHABLENDENABLE,
			FogEnable = D3DRS_FOGENABLE,
			SpecularEnable = D3DRS_SPECULARENABLE,
			FogColor = D3DRS_FOGCOLOR,
			FogTableMode = D3DRS_FOGTABLEMODE,
			FogStart = D3DRS_FOGSTART,
			FogEnd = D3DRS_FOGEND,
			FogDensity = D3DRS_FOGDENSITY,
			RangeFogEnable = D3DRS_RANGEFOGENABLE,
			StencilEnable = D3DRS_STENCILENABLE,
			StencilFail = D3DRS_STENCILFAIL,
			StencilZFail = D3DRS_STENCILZFAIL,
			StencilPass = D3DRS_STENCILPASS,
			StencilFunc = D3DRS_STENCILFUNC,
			StencilRef = D3DRS_STENCILREF,
			StencilMask = D3DRS_STENCILMASK,
			StencilWriteMask = D3DRS_STENCILWRITEMASK,
			TextureFactor = D3DRS_TEXTUREFACTOR,
			Wrap0 = D3DRS_WRAP0,
			Wrap1 = D3DRS_WRAP1,
			Wrap2 = D3DRS_WRAP2,
			Wrap3 = D3DRS_WRAP3,
			Wrap4 = D3DRS_WRAP4,
			Wrap5 = D3DRS_WRAP5,
			Wrap6 = D3DRS_WRAP6,
			Wrap7 = D3DRS_WRAP7,
			Clipping = D3DRS_CLIPPING,
			Lighting = D3DRS_LIGHTING,
			Ambient = D3DRS_AMBIENT,
			FogVertexMode = D3DRS_FOGVERTEXMODE,
			ColorVertex = D3DRS_COLORVERTEX,
			LocalViewer = D3DRS_LOCALVIEWER,
			NormalizeNormals = D3DRS_NORMALIZENORMALS,
			DiffuseMaterialSource = D3DRS_DIFFUSEMATERIALSOURCE,
			SpecularMaterialSource = D3DRS_SPECULARMATERIALSOURCE,
			AmbientMaterialSource = D3DRS_AMBIENTMATERIALSOURCE,
			EmissiveMaterialSource = D3DRS_EMISSIVEMATERIALSOURCE,
			VertexBlend = D3DRS_VERTEXBLEND,
			ClipPlaneEnable = D3DRS_CLIPPLANEENABLE,
			PointSize = D3DRS_POINTSIZE,
			PointSizeMin = D3DRS_POINTSIZE_MIN,
			PointSpriteEnable = D3DRS_POINTSPRITEENABLE,
			PointScaleEnable = D3DRS_POINTSCALEENABLE,
			PointScaleA = D3DRS_POINTSCALE_A,
			PointScaleB = D3DRS_POINTSCALE_B,
			PointScaleC = D3DRS_POINTSCALE_C,
			MultiSampleAntialias = D3DRS_MULTISAMPLEANTIALIAS,
			MultiSampleMask = D3DRS_MULTISAMPLEMASK,
			PatchEdgeStyle = D3DRS_PATCHEDGESTYLE,
			DebugMonitorToken = D3DRS_DEBUGMONITORTOKEN,
			PointSizeMax = D3DRS_POINTSIZE_MAX,
			IndexedVertexBlendEnable = D3DRS_INDEXEDVERTEXBLENDENABLE,
			ColorWriteEnable = D3DRS_COLORWRITEENABLE,
			TweenFactor = D3DRS_TWEENFACTOR,
			BlendOp = D3DRS_BLENDOP,
			PositionDegree = D3DRS_POSITIONDEGREE,
			NormalDegree = D3DRS_NORMALDEGREE,
			ScissorTestEnable = D3DRS_SCISSORTESTENABLE,
			SlopeScaleDepthBias = D3DRS_SLOPESCALEDEPTHBIAS,
			AntialiasedLineEnable = D3DRS_ANTIALIASEDLINEENABLE,
			MinTessellationLevel = D3DRS_MINTESSELLATIONLEVEL,
			MaxTessellationLevel = D3DRS_MAXTESSELLATIONLEVEL,
			AdaptiveTessX = D3DRS_ADAPTIVETESS_X,
			AdaptiveTessY = D3DRS_ADAPTIVETESS_Y,
			AdaptiveTessZ = D3DRS_ADAPTIVETESS_Z,
			AdaptiveTessW = D3DRS_ADAPTIVETESS_W,
			EnableAdaptiveTessellation = D3DRS_ENABLEADAPTIVETESSELLATION,
			TwoSidedStencilMode = D3DRS_TWOSIDEDSTENCILMODE,
			CcwStencilFail = D3DRS_CCW_STENCILFAIL,
			CcwStencilZFail = D3DRS_CCW_STENCILZFAIL,
			CcwStencilPass = D3DRS_CCW_STENCILPASS,
			CcwStencilFunc = D3DRS_CCW_STENCILFUNC,
			ColorWriteEnable1 = D3DRS_COLORWRITEENABLE1,
			ColorWriteEnable2 = D3DRS_COLORWRITEENABLE2,
			ColorWriteEnable3 = D3DRS_COLORWRITEENABLE3,
			BlendFactor = D3DRS_BLENDFACTOR,
			SrgbWriteEnable = D3DRS_SRGBWRITEENABLE,
			DepthBias = D3DRS_DEPTHBIAS,
			Wrap8 = D3DRS_WRAP8,
			Wrap9 = D3DRS_WRAP9,
			Wrap10 = D3DRS_WRAP10,
			Wrap11 = D3DRS_WRAP11,
			Wrap12 = D3DRS_WRAP12,
			Wrap13 = D3DRS_WRAP13,
			Wrap14 = D3DRS_WRAP14,
			Wrap15 = D3DRS_WRAP15,
			SeparateAlphaBlendEnable = D3DRS_SEPARATEALPHABLENDENABLE,
			SourceBlendAlpha = D3DRS_SRCBLENDALPHA,
			DestBlendAlpha = D3DRS_DESTBLENDALPHA,
			BlendOpAlpha = D3DRS_BLENDOPALPHA,
		};

		public enum class TransformState : Int32
		{
			View = D3DTS_VIEW,
			Projection = D3DTS_PROJECTION,
			World = D3DTS_WORLD,
			World1 = D3DTS_WORLD1,
			World2 = D3DTS_WORLD2,
			World3 = D3DTS_WORLD3,
			Texture0 = D3DTS_TEXTURE0,
			Texture1 = D3DTS_TEXTURE1,
			Texture2 = D3DTS_TEXTURE2,
			Texture3 = D3DTS_TEXTURE3,
			Texture4 = D3DTS_TEXTURE4,
			Texture5 = D3DTS_TEXTURE5,
			Texture6 = D3DTS_TEXTURE6,
			Texture7 = D3DTS_TEXTURE7,
		};

		public enum class TextureStage : Int32
		{
			ColorOp = D3DTSS_COLOROP,
			ColorArg1 = D3DTSS_COLORARG1,
			ColorArg2 = D3DTSS_COLORARG2,
			AlphaOp = D3DTSS_ALPHAOP,
			AlphaArg1 = D3DTSS_ALPHAARG1,
			AlphaArg2 = D3DTSS_ALPHAARG2,
			BumpEnvMat00 = D3DTSS_BUMPENVMAT00,
			BumpEnvMat01 = D3DTSS_BUMPENVMAT01,
			BumpEnvMat10 = D3DTSS_BUMPENVMAT10,
			BumpEnvMat11 = D3DTSS_BUMPENVMAT11,
			TexCoordIndex = D3DTSS_TEXCOORDINDEX,
			BumpEnvLScale = D3DTSS_BUMPENVLSCALE,
			BumpEnvLOffset = D3DTSS_BUMPENVLOFFSET,
			TextureTransformFlags = D3DTSS_TEXTURETRANSFORMFLAGS,
			ColorArg0 = D3DTSS_COLORARG0,
			AlphaArg0 = D3DTSS_ALPHAARG0,
			ResultArg = D3DTSS_RESULTARG,
			Constant = D3DTSS_CONSTANT,
		};

		[Flags]
		public enum class TextureCoordIndex : Int32
		{
			PassThru = D3DTSS_TCI_PASSTHRU,
			CameraSpaceNormal = D3DTSS_TCI_CAMERASPACENORMAL,
			CameraSpacePosition = D3DTSS_TCI_CAMERASPACEPOSITION,
			CameraSpaceReflectionVector = D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR,
			SphereMap = D3DTSS_TCI_SPHEREMAP,
		};

		public enum class TextureArgument : Int32
		{
			SelectMask = D3DTA_SELECTMASK,
			Diffuse = D3DTA_DIFFUSE,
			Current = D3DTA_CURRENT,
			Texture = D3DTA_TEXTURE,
			TFactor = D3DTA_TFACTOR,
			Specular = D3DTA_SPECULAR,
			Temp = D3DTA_TEMP,
			Constant = D3DTA_CONSTANT,
			Complement = D3DTA_COMPLEMENT,
			AlphaReplicate = D3DTA_ALPHAREPLICATE,
		};

		public enum class TextureOperation : Int32
		{
			Disable = D3DTOP_DISABLE,
			SelectArg1 = D3DTOP_SELECTARG1,
			SelectArg2 = D3DTOP_SELECTARG2,

			Modulate = D3DTOP_MODULATE,
			Modulate2X = D3DTOP_MODULATE2X,
			Modulate4X = D3DTOP_MODULATE4X,

			Add = D3DTOP_ADD,
			AddSigned = D3DTOP_ADDSIGNED,
			AddSigned2X = D3DTOP_ADDSIGNED2X,
			Subtract = D3DTOP_SUBTRACT,
			AddSmooth = D3DTOP_ADDSMOOTH,

			BlendDiffuseAlpha = D3DTOP_BLENDDIFFUSEALPHA,
			BlendTextureAlpha = D3DTOP_BLENDTEXTUREALPHA,
			BlendFactorAlpha = D3DTOP_BLENDFACTORALPHA,

			BlendTextureAlphaPM = D3DTOP_BLENDTEXTUREALPHAPM,
			BlendCurrentAlpha = D3DTOP_BLENDCURRENTALPHA,

			Premodulate = D3DTOP_PREMODULATE,
			ModulateAlphaAddColor = D3DTOP_MODULATEALPHA_ADDCOLOR,
			ModulateColorAddAlpha = D3DTOP_MODULATECOLOR_ADDALPHA,
			ModulateInvAlphaAddColor = D3DTOP_MODULATEINVALPHA_ADDCOLOR,
			ModulateInvColorAddAlpha = D3DTOP_MODULATEINVCOLOR_ADDALPHA,

			BumpEnvMap = D3DTOP_BUMPENVMAP,
			BumpEnvMapLuminance = D3DTOP_BUMPENVMAPLUMINANCE,

			DotProduct3 = D3DTOP_DOTPRODUCT3,

			MultiplyAdd = D3DTOP_MULTIPLYADD,
			Lerp = D3DTOP_LERP,
		};

		public enum class SamplerState : Int32
		{
			AddressU = D3DSAMP_ADDRESSU,
			AddressV = D3DSAMP_ADDRESSV,
			AddressW = D3DSAMP_ADDRESSW,
			BorderColor = D3DSAMP_BORDERCOLOR,
			MagFilter = D3DSAMP_MAGFILTER,
			MinFilter = D3DSAMP_MINFILTER,
			MipFilter = D3DSAMP_MIPFILTER,
			MipMapLodBias = D3DSAMP_MIPMAPLODBIAS,
			MaxMipLevel = D3DSAMP_MAXMIPLEVEL,
			MaxAnisotropy = D3DSAMP_MAXANISOTROPY,
			SrgbTexture = D3DSAMP_SRGBTEXTURE,
			ElementIndex = D3DSAMP_ELEMENTINDEX,
			DMapOffset = D3DSAMP_DMAPOFFSET,
		};

		public enum class TextureAddress : Int32
		{
			Wrap = D3DTADDRESS_WRAP,
			Mirror = D3DTADDRESS_MIRROR,
			Clamp = D3DTADDRESS_CLAMP,
			Border = D3DTADDRESS_BORDER,
			MirrorOnce = D3DTADDRESS_MIRRORONCE,
		};

		public enum class TextureTransform : Int32
		{
			Disable = D3DTTFF_DISABLE,
			Count1 = D3DTTFF_COUNT1,
			Count2 = D3DTTFF_COUNT2,
			Count3 = D3DTTFF_COUNT3,
			Count4 = D3DTTFF_COUNT4,
			Projected = D3DTTFF_PROJECTED,
		};

		public enum class ResourceType : Int32
		{
			Surface = D3DRTYPE_SURFACE,
			Volume = D3DRTYPE_VOLUME,
			Texture = D3DRTYPE_TEXTURE,
			VolumeTexture = D3DRTYPE_VOLUMETEXTURE,
			CubeTexture = D3DRTYPE_CUBETEXTURE,
			VertexBuffer = D3DRTYPE_VERTEXBUFFER,
			IndexBuffer = D3DRTYPE_INDEXBUFFER,
		};

		public enum class ImageFileFormat : Int32
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

		/// <summary>
		/// Shading modes.
		/// </summary>
		public enum class ShadeMode : Int32
		{
			/// <summary>Flat shading.</summary>
			Flat = D3DSHADE_FLAT,
			/// <summary>Gouraud shading.</summary>
			Gouraud = D3DSHADE_GOURAUD
		};

		/// <summary>
		/// Comparison operations.
		/// </summary>
		public enum class Compare
		{
			/// <summary>Never accept</summary>
			Never = D3DCMP_NEVER,
			/// <summary>Accept if less than.</summary>
			Less = D3DCMP_LESS,
			/// <summary>Accept if equal.</summary>
			Equal = D3DCMP_EQUAL,
			/// <summary>Accept if equal or less than.</summary>
			LessEqual = D3DCMP_LESSEQUAL,
			/// <summary>Accept if greater than.</summary>
			Greater = D3DCMP_GREATER,
			/// <summary>Accept if not equal.</summary>
			NotEqual = D3DCMP_NOTEQUAL,
			/// <summary>Accept if greater than or equal</summary>
			GreaterEqual = D3DCMP_GREATEREQUAL,
			/// <summary>Always accept.</summary>
			Always = D3DCMP_ALWAYS
		};

		/// <summary>
		/// Stencil operations.
		/// </summary>
		public enum class StencilOperation
		{
			/// <summary>Keep the stencil value.</summary>
			Keep = D3DSTENCILOP_KEEP,
			/// <summary>Zero the stencil value.</summary>
			Zero = D3DSTENCILOP_ZERO,
			/// <summary>Replace the stencil value.</summary>
			Replace = D3DSTENCILOP_REPLACE,
			/// <summary>Increment and clamp stencil value.</summary>
			IncrSat = D3DSTENCILOP_INCRSAT,
			/// <summary>Decrement and clamp stencil value.</summary>
			DecrSat = D3DSTENCILOP_DECRSAT,
			/// <summary>Invert the stencil value.</summary>
			Invert = D3DSTENCILOP_INVERT,
			/// <summary>Increment the stencil value.</summary>
			Incr = D3DSTENCILOP_INCR,
			/// <summary>Decrement the stencil value.</summary>
			Decr = D3DSTENCILOP_DECR
		};

		/// <summary>
		/// ZBuffer usage types.
		/// </summary>
		public enum class ZBufferType
		{
			/// <summary>Used to enable the depth buffer.</summary>
			UseZB_True = D3DZB_TRUE,
			/// <summary>Used to disable the depth buffer.</summary>
			UseZB_False = D3DZB_FALSE,
			/// <summary>Used to enable a W-buffer.</summary>
			UseWBuffer = D3DZB_USEW
		};

		//enums related to effects
		public enum class ParameterClass : Int32
		{
			Scalar = D3DXPC_SCALAR,
			Vector = D3DXPC_VECTOR,
			MatrixRows = D3DXPC_MATRIX_ROWS,
			MatrixColumns = D3DXPC_MATRIX_COLUMNS,
			Object = D3DXPC_OBJECT,
			Struct = D3DXPC_STRUCT,
		};

		public enum class ParameterType : Int32
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

		[Flags]
		public enum class ParameterFlags : Int32
		{
			Shared = D3DX_PARAMETER_SHARED,
			Literal = D3DX_PARAMETER_LITERAL,
			Annotation = D3DX_PARAMETER_ANNOTATION,
		};
	}
}
