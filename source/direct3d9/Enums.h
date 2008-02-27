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

#include "external/atir2vb.h"

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
		
		public enum class Basis : System::Int32
		{
			Bezier = D3DBASIS_BEZIER,
			BSpline = D3DBASIS_BSPLINE,
			CatmullRom = D3DBASIS_CATMULL_ROM,
		};
		
		public enum class Blend : System::Int32
		{
			Zero = D3DBLEND_ZERO,
			One = D3DBLEND_ONE,
			SourceColor = D3DBLEND_SRCCOLOR,
			InvSourceColor = D3DBLEND_INVSRCCOLOR,
			SourceAlpha = D3DBLEND_SRCALPHA,
			InvSourceAlpha = D3DBLEND_INVSRCALPHA,
			DestinationAlpha = D3DBLEND_DESTALPHA,
			InvDestinationAlpha = D3DBLEND_INVDESTALPHA,
			DestinationColor = D3DBLEND_DESTCOLOR,
			InvDestinationColor = D3DBLEND_INVDESTCOLOR,
			SourceAlphaSat = D3DBLEND_SRCALPHASAT,
			BothSourceAlpha = D3DBLEND_BOTHSRCALPHA,
			BothInvSourceAlpha = D3DBLEND_BOTHINVSRCALPHA,
			BlendFactor = D3DBLEND_BLENDFACTOR,
			InvBlendFactor = D3DBLEND_INVBLENDFACTOR,
		};

		[System::Flags]
		public enum class BlendCaps : System::Int32
		{
			Zero = D3DPBLENDCAPS_ZERO,
			One = D3DPBLENDCAPS_ONE,
			SourceColor = D3DPBLENDCAPS_SRCCOLOR,
			InvSourceColor = D3DPBLENDCAPS_INVSRCCOLOR,
			SourceAlpha = D3DPBLENDCAPS_SRCALPHA,
			InvSourceAlpha = D3DPBLENDCAPS_INVSRCALPHA,
			DestinationAlpha = D3DPBLENDCAPS_DESTALPHA,
			InvDestinationAlpha = D3DPBLENDCAPS_INVDESTALPHA,
			DestinationColor = D3DPBLENDCAPS_DESTCOLOR,
			InvDestinationColor = D3DPBLENDCAPS_INVDESTCOLOR,
			SourceAlphaSaturated = D3DPBLENDCAPS_SRCALPHASAT,
			BothSourceAlpha = D3DPBLENDCAPS_BOTHSRCALPHA,
			BothInvSourceAlpha = D3DPBLENDCAPS_BOTHINVSRCALPHA,
			BlendFactor = D3DPBLENDCAPS_BLENDFACTOR,
		};
		
		public enum class BlendOperation : System::Int32
		{
			Add = D3DBLENDOP_ADD,
			Subtract = D3DBLENDOP_SUBTRACT,
			ReverseSubtract = D3DBLENDOP_REVSUBTRACT,
			Minimum = D3DBLENDOP_MIN,
			Maximum = D3DBLENDOP_MAX,
		};

		public enum class CallbackSearchFlags : System::Int32
		{
			SearchExcludingInitialPosition = D3DXCALLBACK_SEARCH_EXCLUDING_INITIAL_POSITION,
			SearchBehindInitialPosition = D3DXCALLBACK_SEARCH_BEHIND_INITIAL_POSITION
		};

		[System::Flags]
		public enum class Caps : System::Int32
		{
			ReadScanline = D3DCAPS_READ_SCANLINE,
		};

		[System::Flags]
		public enum class Caps2 : System::Int32
		{
			FullScreenGamma = D3DCAPS2_FULLSCREENGAMMA,
			CanCalibrateGamma = D3DCAPS2_CANCALIBRATEGAMMA,
			CanManageResource = D3DCAPS2_CANMANAGERESOURCE,
			DynamicTextures = D3DCAPS2_DYNAMICTEXTURES,
			CanAutoGenMipMap = D3DCAPS2_CANAUTOGENMIPMAP
		};

		[System::Flags]
		public enum class Caps3 : System::Int32
		{
			AlphaFullScreenFlipOrDiscard = D3DCAPS3_ALPHA_FULLSCREEN_FLIP_OR_DISCARD,
			LinearToSrgbPresentation = D3DCAPS3_LINEAR_TO_SRGB_PRESENTATION,
			CopyToVideoMemory = D3DCAPS3_COPY_TO_VIDMEM,
			CopyToSystemMemory = D3DCAPS3_COPY_TO_SYSTEMMEM,
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

		public enum class CharacterSet : System::Int32
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
			Mac = MAC_CHARSET,
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

		[System::Flags]
		public enum class ClearFlags : System::Int32
		{
			None = 0,
			Stencil = D3DCLEAR_STENCIL,
			Target = D3DCLEAR_TARGET,
			ZBuffer = D3DCLEAR_ZBUFFER
		};
		
		public enum class ColorSource : System::Int32
		{
			Material = D3DMCS_MATERIAL,
			Color1 = D3DMCS_COLOR1,
			Color2 = D3DMCS_COLOR2,
		};
		
		[System::Flags]
		public enum class ColorWriteEnable : System::Int32
		{
			Alpha = D3DCOLORWRITEENABLE_ALPHA,
			Blue = D3DCOLORWRITEENABLE_BLUE,
			Green = D3DCOLORWRITEENABLE_GREEN,
			Red = D3DCOLORWRITEENABLE_RED,
			All = Alpha | Blue | Green | Red
		};

		/// <summary>
		/// Comparison operations.
		/// </summary>
		public enum class Compare
		{
			/// <summary>
			/// Never accept
			/// </summary>
			Never = D3DCMP_NEVER,

			/// <summary>
			/// Accept if less than.
			/// </summary>
			Less = D3DCMP_LESS,

			/// <summary>
			/// Accept if equal.
			/// </summary>
			Equal = D3DCMP_EQUAL,

			/// <summary>
			/// Accept if equal or less than.
			/// </summary>
			LessEqual = D3DCMP_LESSEQUAL,

			/// <summary>
			/// Accept if greater than.
			/// </summary>
			Greater = D3DCMP_GREATER,

			/// <summary>
			/// Accept if not equal.
			/// </summary>
			NotEqual = D3DCMP_NOTEQUAL,

			/// <summary>
			/// Accept if greater than or equal
			/// </summary>
			GreaterEqual = D3DCMP_GREATEREQUAL,

			/// <summary>
			/// Always accept.
			/// </summary>
			Always = D3DCMP_ALWAYS
		};

		[System::Flags]
		public enum class CompareCaps : System::Int32
		{
			Never = D3DPCMPCAPS_NEVER,
			Less = D3DPCMPCAPS_LESS,
			Equal = D3DPCMPCAPS_EQUAL,
			LessEqual = D3DPCMPCAPS_LESSEQUAL,
			Greater = D3DPCMPCAPS_GREATER,
			NotEqual = D3DPCMPCAPS_NOTEQUAL,
			GreaterEqual = D3DPCMPCAPS_GREATEREQUAL,
			Always = D3DPCMPCAPS_ALWAYS,
		};

		[System::Flags]
		public enum class CreateFlags : System::Int32
		{
			None = 0,
			AdapterGroupDevice = D3DCREATE_ADAPTERGROUP_DEVICE,
			DisableDriverManagement = D3DCREATE_DISABLE_DRIVER_MANAGEMENT,
			DisableExtendedDriverManagement = D3DCREATE_DISABLE_DRIVER_MANAGEMENT_EX,
			FpuPreserve = D3DCREATE_FPU_PRESERVE,
			HardwareVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING,
			MixedVertexProcessing = D3DCREATE_MIXED_VERTEXPROCESSING,
			Multithreaded = D3DCREATE_MULTITHREADED,
			NoWindowChanges = D3DCREATE_NOWINDOWCHANGES,
			PureDevice = D3DCREATE_PUREDEVICE,
			SoftwareVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		};
		
		public enum class CubeMapFace : System::Int32
		{
			PositiveX = D3DCUBEMAP_FACE_POSITIVE_X,
			NegativeX = D3DCUBEMAP_FACE_NEGATIVE_X,
			PositiveY = D3DCUBEMAP_FACE_POSITIVE_Y,
			NegativeY = D3DCUBEMAP_FACE_NEGATIVE_Y,
			PositiveZ = D3DCUBEMAP_FACE_POSITIVE_Z,
			NegativeZ = D3DCUBEMAP_FACE_NEGATIVE_Z
		};
		
		public enum class Cull : System::Int32
		{
			Clockwise = D3DCULL_CW,
			Counterclockwise = D3DCULL_CCW,
			None = D3DCULL_NONE
		};

		[System::Flags]
		public enum class CursorCaps : System::Int32
		{
			Color = D3DCURSORCAPS_COLOR,
			LowRes = D3DCURSORCAPS_LOWRES,
		};
		
		public enum class DeclarationMethod : System::Byte
		{
			Default = D3DDECLMETHOD_DEFAULT,
			PartialU = D3DDECLMETHOD_PARTIALU,
			PartialV = D3DDECLMETHOD_PARTIALV,
			CrossUV = D3DDECLMETHOD_CROSSUV,
			UV = D3DDECLMETHOD_UV,
			Lookup = D3DDECLMETHOD_LOOKUP,
			LookupPresampled = D3DDECLMETHOD_LOOKUPPRESAMPLED
		};

		public enum class DeclarationType : System::Byte
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
			HalfTwo = D3DDECLTYPE_FLOAT16_2,
			HalfFour = D3DDECLTYPE_FLOAT16_4,

			Unused = D3DDECLTYPE_UNUSED
		};

		[System::Flags]
		public enum class DeclarationTypeCaps
		{
			UByte4 = D3DDTCAPS_UBYTE4,
			UByte4N = D3DDTCAPS_UBYTE4N,
			Short2N = D3DDTCAPS_SHORT2N,
			Short4N = D3DDTCAPS_SHORT4N,
			UShort2N = D3DDTCAPS_USHORT2N,
			UShort4N = D3DDTCAPS_USHORT4N,
			UDec3 = D3DDTCAPS_UDEC3,
			Dec3N = D3DDTCAPS_DEC3N,
			Float16_2 = D3DDTCAPS_FLOAT16_2,
			Float16_4 = D3DDTCAPS_FLOAT16_4,
		};

		public enum class DeclarationUsage : System::Byte
		{
			Position = D3DDECLUSAGE_POSITION,
			BlendWeight = D3DDECLUSAGE_BLENDWEIGHT,
			BlendIndices = D3DDECLUSAGE_BLENDINDICES,
			Normal = D3DDECLUSAGE_NORMAL,
			PointSize = D3DDECLUSAGE_PSIZE,
			TextureCoordinate = D3DDECLUSAGE_TEXCOORD,
			Tangent = D3DDECLUSAGE_TANGENT,
			Binormal = D3DDECLUSAGE_BINORMAL,
			TessellateFactor = D3DDECLUSAGE_TESSFACTOR,
			PositionTransformed = D3DDECLUSAGE_POSITIONT,
			Color = D3DDECLUSAGE_COLOR,
			Fog = D3DDECLUSAGE_FOG,
			Depth = D3DDECLUSAGE_DEPTH,
			Sample = D3DDECLUSAGE_SAMPLE
		};
		
		public enum class Degree : System::Int32
		{
			Linear = D3DDEGREE_LINEAR,
			Quadratic = D3DDEGREE_QUADRATIC,
			Cubic = D3DDEGREE_CUBIC,
			Quintic = D3DDEGREE_QUINTIC,
		};

		[System::Flags]
		public enum class DevCaps2
		{
			StreamOffset = D3DDEVCAPS2_STREAMOFFSET,
			DMapNPatch = D3DDEVCAPS2_DMAPNPATCH,
			AdaptiveTessRTPatch = D3DDEVCAPS2_ADAPTIVETESSRTPATCH,
			AdaptiveTessNPatch = D3DDEVCAPS2_ADAPTIVETESSNPATCH,
			CanStretchRectFromTextures = D3DDEVCAPS2_CAN_STRETCHRECT_FROM_TEXTURES,
			PresampledMapNPatch = D3DDEVCAPS2_PRESAMPLEDDMAPNPATCH,
			VertexElementsCanShareStreamOffset = D3DDEVCAPS2_VERTEXELEMENTSCANSHARESTREAMOFFSET,
		};

		[System::Flags]
		public enum class DeviceCaps : System::Int32
		{
			ExecuteSystemMemory = D3DDEVCAPS_EXECUTESYSTEMMEMORY,
			ExecuteVideoMemory = D3DDEVCAPS_EXECUTEVIDEOMEMORY,
			TLVertexSystemMemory = D3DDEVCAPS_TLVERTEXSYSTEMMEMORY,
			TLVertexVideoMemory = D3DDEVCAPS_TLVERTEXVIDEOMEMORY,
			TextureSystemMemory = D3DDEVCAPS_TEXTURESYSTEMMEMORY,
			TextureVideoMemory = D3DDEVCAPS_TEXTUREVIDEOMEMORY,
			DrawPrimTLVertex = D3DDEVCAPS_DRAWPRIMTLVERTEX,
			CanRenderAfterFlip = D3DDEVCAPS_CANRENDERAFTERFLIP,
			TextureNonLocalVideoMemory = D3DDEVCAPS_TEXTURENONLOCALVIDMEM,
			DrawPrimitives2 = D3DDEVCAPS_DRAWPRIMITIVES2,
			SeparateTextureMemory = D3DDEVCAPS_SEPARATETEXTUREMEMORIES,
			DrawPrimitives2Extended = D3DDEVCAPS_DRAWPRIMITIVES2EX,
			HWTransformAndLight = D3DDEVCAPS_HWTRANSFORMANDLIGHT,
			CanBlitSysToNonLocal = D3DDEVCAPS_CANBLTSYSTONONLOCAL,
			HWRasterization = D3DDEVCAPS_HWRASTERIZATION,
			PureDevice = D3DDEVCAPS_PUREDEVICE,
			QuinticRTPatches = D3DDEVCAPS_QUINTICRTPATCHES,
			RTPatches = D3DDEVCAPS_RTPATCHES,
			RTPatchHandleZero = D3DDEVCAPS_RTPATCHHANDLEZERO,
			NPatches = D3DDEVCAPS_NPATCHES,
		};
		
		public enum class DeviceType : System::Int32
		{
			Hardware = D3DDEVTYPE_HAL,
			NullReference = D3DDEVTYPE_NULLREF,
			Reference = D3DDEVTYPE_REF,
			Software = D3DDEVTYPE_SW
		};
		
		[System::Flags]
		public enum class DrawTextFormat : System::Int32
		{
			Top = DT_TOP,
			Left = DT_LEFT,
			Center = DT_CENTER,
			Right = DT_RIGHT,
			VCenter = DT_VCENTER,
			Bottom = DT_BOTTOM,
			Wordbreak = DT_WORDBREAK,
			SingleLine = DT_SINGLELINE,
			ExpandTabs = DT_EXPANDTABS,
			NoClip = DT_NOCLIP,
			CalcRect = DT_CALCRECT,
			RtlReading = DT_RTLREADING,
		};
		
		public enum class DriverLevel : System::Int32
		{
			Direct3D7 = 700,
			Direct3D8 = 800,
			Direct3D9 = 900,
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
		
		public enum class FillMode : System::Int32
		{
			Point = D3DFILL_POINT,
			Wireframe = D3DFILL_WIREFRAME,
			Solid = D3DFILL_SOLID
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
		public enum class FilterCaps : System::Int32
		{
			MinPoint = D3DPTFILTERCAPS_MINFPOINT,
			MinLinear = D3DPTFILTERCAPS_MINFLINEAR,
			MinAnisotropic = D3DPTFILTERCAPS_MINFANISOTROPIC,
			MinPyramidalQuad = D3DPTFILTERCAPS_MINFPYRAMIDALQUAD,
			MinGaussianQuad = D3DPTFILTERCAPS_MINFGAUSSIANQUAD,
			MipPoint = D3DPTFILTERCAPS_MIPFPOINT,
			MipLinear = D3DPTFILTERCAPS_MIPFLINEAR,
			MagPoint = D3DPTFILTERCAPS_MAGFPOINT,
			MagLinear = D3DPTFILTERCAPS_MAGFLINEAR,
			MagAnisotropic = D3DPTFILTERCAPS_MAGFANISOTROPIC,
			MagPyramidalQuad = D3DPTFILTERCAPS_MAGFPYRAMIDALQUAD,
			MagGaussianQuad = D3DPTFILTERCAPS_MAGFGAUSSIANQUAD,
		};
		
		public enum class FontQuality : System::Int32
		{
			Default = DEFAULT_QUALITY,
			Draft = DRAFT_QUALITY,
			Proof = PROOF_QUALITY,
			NonAntialiased = NONANTIALIASED_QUALITY,
			Antialiased = ANTIALIASED_QUALITY,
			ClearType = CLEARTYPE_QUALITY,
			ClearTypeNatural = CLEARTYPE_NATURAL_QUALITY,
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
			Black = FW_BLACK,
		};

		public enum class Format : System::Int32
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
			D24FS8 = D3DFMT_D24FS8,
			D32 = D3DFMT_D32,
			D32SingleLockable = D3DFMT_D32F_LOCKABLE,
			S8Lockable = D3DFMT_S8_LOCKABLE,
			L16 = D3DFMT_L16,

			VertexData = D3DFMT_VERTEXDATA,
			Index16 = D3DFMT_INDEX16,
			Index32 = D3DFMT_INDEX32,

			// extensions
			ATI_R2VB = R2VB_FOURCC_R2VB,

			Unknown = D3DFMT_UNKNOWN,
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

		[System::Flags]
		public enum class Issue
		{
			Begin = D3DISSUE_BEGIN,
			End = D3DISSUE_END
		};
		
		public enum class LightType : System::Int32
		{
			Point = D3DLIGHT_POINT,
			Spot = D3DLIGHT_SPOT,
			Directional = D3DLIGHT_DIRECTIONAL,
		};

		[System::Flags]
		public enum class LineCaps : System::Int32
		{
			Texture = D3DLINECAPS_TEXTURE,
			DepthTest = D3DLINECAPS_ZTEST,
			Blend = D3DLINECAPS_BLEND,
			AlphaCompare = D3DLINECAPS_ALPHACMP,
			Fog = D3DLINECAPS_FOG,
			Antialias = D3DLINECAPS_ANTIALIAS,
		};
		
		[System::Flags]
		public enum class LockFlags : System::Int32
		{
			Discard = D3DLOCK_DISCARD,
			DoNotWait = D3DLOCK_DONOTWAIT,
			NoDirtyUpdate = D3DLOCK_NO_DIRTY_UPDATE,
			None = 0,
			NoOverwrite = D3DLOCK_NOOVERWRITE,
			NoSystemLock = D3DLOCK_NOSYSLOCK,
			ReadOnly = D3DLOCK_READONLY,

			// this just exists for ProcessVertices
			DoNotCopyData = D3DPV_DONOTCOPYDATA,
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
		
		public enum class MultisampleType : System::Int32
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
		
		[System::Flags]
		public enum class PitchAndFamily : System::Int32
		{
			Default = DEFAULT_PITCH,
			Fixed = FIXED_PITCH,
			Variable = VARIABLE_PITCH,
			Mono = MONO_FONT,

			DontCare = FF_DONTCARE,
			Roman = FF_ROMAN,
			Swiss = FF_SWISS,
			Modern = FF_MODERN,
			Script = FF_SCRIPT,
			Decorative = FF_DECORATIVE,
		};

		public enum class PlaybackType : System::Int32
		{
			Loop = D3DXPLAY_LOOP,
			Once = D3DXPLAY_ONCE,
			PingPong = D3DXPLAY_PINGPONG
		};
		
		public enum class Pool : System::Int32
		{
			Default = D3DPOOL_DEFAULT,
			Managed = D3DPOOL_MANAGED,
			SystemMemory = D3DPOOL_SYSTEMMEM,
			Scratch = D3DPOOL_SCRATCH,
		};

		public enum class Precision : System::Int32
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
			PostScriptOnly = OUT_PS_ONLY_PRECIS,
		};
		
		[System::Flags]
		public enum class Present : System::Int32
		{
			None = 0,
			DoNotWait = D3DPRESENT_DONOTWAIT,
			LinearContent = D3DPRESENT_LINEAR_CONTENT
		};
		
		[System::Flags]
		public enum class PresentFlags : System::Int32
		{
			DeviceClip = D3DPRESENTFLAG_DEVICECLIP,
			DiscardDepthStencil = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL,
			LockableBackBuffer = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER,
			None = 0,
			Video = D3DPRESENTFLAG_VIDEO
		};

		[System::Flags]
		public enum class PresentInterval : System::Int32
		{
			Default = D3DPRESENT_INTERVAL_DEFAULT,
			Immediate = (int) D3DPRESENT_INTERVAL_IMMEDIATE,
			One = D3DPRESENT_INTERVAL_ONE,
			Two = D3DPRESENT_INTERVAL_TWO,
			Three = D3DPRESENT_INTERVAL_THREE,
			Four = D3DPRESENT_INTERVAL_FOUR,
		};

		[System::Flags]
		public enum class PrimitiveMiscCaps : System::Int32
		{
			MaskZ = D3DPMISCCAPS_MASKZ,
			CullNone = D3DPMISCCAPS_CULLNONE,
			CullCW = D3DPMISCCAPS_CULLCW,
			CullCCW = D3DPMISCCAPS_CULLCCW,
			ColorWriteEnable = D3DPMISCCAPS_COLORWRITEENABLE,
			ClipPlanesScaledPoints = D3DPMISCCAPS_CLIPPLANESCALEDPOINTS,
			ClipTLVertices = D3DPMISCCAPS_CLIPTLVERTS,
			TssArgTemp = D3DPMISCCAPS_TSSARGTEMP,
			BlendOperation = D3DPMISCCAPS_BLENDOP,
			NullReference = D3DPMISCCAPS_NULLREFERENCE,
			IndependentWriteMasks = D3DPMISCCAPS_INDEPENDENTWRITEMASKS,
			PerStateConstant = D3DPMISCCAPS_PERSTAGECONSTANT,
			FogAndSpecularAlpha = D3DPMISCCAPS_FOGANDSPECULARALPHA,
			SeparateAlphaBlend = D3DPMISCCAPS_SEPARATEALPHABLEND,
			MrtIndependentBitDepths = D3DPMISCCAPS_MRTINDEPENDENTBITDEPTHS,
			MrtPostPixelShaderBlending = D3DPMISCCAPS_MRTPOSTPIXELSHADERBLENDING,
			FogVertexClamped = D3DPMISCCAPS_FOGVERTEXCLAMPED,
		};
		
		public enum class PrimitiveType : System::Int32
		{
			PointList = D3DPT_POINTLIST,
			LineList = D3DPT_LINELIST,
			LineStrip = D3DPT_LINESTRIP,
			TriangleList = D3DPT_TRIANGLELIST,
			TriangleStrip = D3DPT_TRIANGLESTRIP,
			TriangleFan = D3DPT_TRIANGLEFAN
		};

		public enum class QueryType : System::Int32
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

		public enum class R2VBSampler : System::Int32
		{
			OverrideDMap = R2VB_VSMP_OVR_DMAP,
			OverrideVtx0 = R2VB_VSMP_OVR_VTX0,
			OverrideVtx1 = R2VB_VSMP_OVR_VTX1,
			OverrideVtx2 = R2VB_VSMP_OVR_VTX2,
			OverrideVtx3 = R2VB_VSMP_OVR_VTX3,

			Count = R2VB_VSMP_NUM,
		};

		[System::Flags]
		public enum class RasterCaps : System::Int32
		{
			Dither = D3DPRASTERCAPS_DITHER,
			DepthTest = D3DPRASTERCAPS_ZTEST,
			FogVertex = D3DPRASTERCAPS_FOGVERTEX,
			FogTable = D3DPRASTERCAPS_FOGTABLE,
			MipMapLodBias = D3DPRASTERCAPS_MIPMAPLODBIAS,
			ZBufferLessHsr = D3DPRASTERCAPS_ZBUFFERLESSHSR,
			FogRange = D3DPRASTERCAPS_FOGRANGE,
			Anisotropy = D3DPRASTERCAPS_ANISOTROPY,
			WBuffer = D3DPRASTERCAPS_WBUFFER,
			WFog = D3DPRASTERCAPS_WFOG,
			ZFog = D3DPRASTERCAPS_ZFOG,
			ColorPerspective = D3DPRASTERCAPS_COLORPERSPECTIVE,
			ScissorTest = D3DPRASTERCAPS_SCISSORTEST,
			SlopeScaleDepthBias = D3DPRASTERCAPS_SLOPESCALEDEPTHBIAS,
			DepthBias = D3DPRASTERCAPS_DEPTHBIAS,
			MultisampleToggle = D3DPRASTERCAPS_MULTISAMPLE_TOGGLE,
		};

		public enum class RegisterSet : System::Int32
		{
			Bool = D3DXRS_BOOL,
			Int4 = D3DXRS_INT4,
			Float4 = D3DXRS_FLOAT4,
			Sampler = D3DXRS_SAMPLER,
		};
		
		public enum class RenderState : System::Int32
		{
			ZEnable = D3DRS_ZENABLE,
			FillMode = D3DRS_FILLMODE,
			ShadeMode = D3DRS_SHADEMODE,
			ZWriteEnable = D3DRS_ZWRITEENABLE,
			AlphaTestEnable = D3DRS_ALPHATESTENABLE,
			LastPixel = D3DRS_LASTPIXEL,
			SourceBlend = D3DRS_SRCBLEND,
			DestinationBlend = D3DRS_DESTBLEND,
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
			MultisampleAntialias = D3DRS_MULTISAMPLEANTIALIAS,
			MultisampleMask = D3DRS_MULTISAMPLEMASK,
			PatchEdgeStyle = D3DRS_PATCHEDGESTYLE,
			DebugMonitorToken = D3DRS_DEBUGMONITORTOKEN,
			PointSizeMax = D3DRS_POINTSIZE_MAX,
			IndexedVertexBlendEnable = D3DRS_INDEXEDVERTEXBLENDENABLE,
			ColorWriteEnable = D3DRS_COLORWRITEENABLE,
			TweenFactor = D3DRS_TWEENFACTOR,
			BlendOperation = D3DRS_BLENDOP,
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
			DestinationBlendAlpha = D3DRS_DESTBLENDALPHA,
			BlendOperationAlpha = D3DRS_BLENDOPALPHA,
		};
		
		public enum class ResourceType : System::Int32
		{
			Surface = D3DRTYPE_SURFACE,
			Volume = D3DRTYPE_VOLUME,
			Texture = D3DRTYPE_TEXTURE,
			VolumeTexture = D3DRTYPE_VOLUMETEXTURE,
			CubeTexture = D3DRTYPE_CUBETEXTURE,
			VertexBuffer = D3DRTYPE_VERTEXBUFFER,
			IndexBuffer = D3DRTYPE_INDEXBUFFER,
		};
		
		public enum class SamplerState : System::Int32
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

		[System::Flags]
		public enum class ShadeCaps : System::Int32
		{
			ColorGouraudRgb = D3DPSHADECAPS_COLORGOURAUDRGB,
			SpecularGouraudRgb = D3DPSHADECAPS_SPECULARGOURAUDRGB,
			AlphaGouraudBlend = D3DPSHADECAPS_ALPHAGOURAUDBLEND,
			FogGouraud = D3DPSHADECAPS_FOGGOURAUD,
		};
		
		/// <summary>
		/// Shading modes.
		/// </summary>
		public enum class ShadeMode : System::Int32
		{
			/// <summary>
			/// Flat shading.
			/// </summary>
			Flat = D3DSHADE_FLAT,

			/// <summary>
			/// Gouraud shading.
			/// </summary>
			Gouraud = D3DSHADE_GOURAUD
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

		public enum class StateBlockType : System::Int32
		{
			All = D3DSBT_ALL,
			PixelState = D3DSBT_PIXELSTATE,
			VertexState = D3DSBT_VERTEXSTATE,
		};

		[System::Flags]
		public enum class StencilCaps : System::Int32
		{
			Keep = D3DSTENCILCAPS_KEEP,
			Zero = D3DSTENCILCAPS_ZERO,
			Replace = D3DSTENCILCAPS_REPLACE,
			IncrementClamp = D3DSTENCILCAPS_INCRSAT,
			DecrementClamp = D3DSTENCILCAPS_DECRSAT,
			Invert = D3DSTENCILCAPS_INVERT,
			Increment = D3DSTENCILCAPS_INCR,
			Decrement = D3DSTENCILCAPS_DECR,
			TwoSided = D3DSTENCILCAPS_TWOSIDED,
		};
		
		/// <summary>
		/// Stencil operations.
		/// </summary>
		public enum class StencilOperation
		{
			/// <summary>
			/// Keep the stencil value.
			/// </summary>
			Keep = D3DSTENCILOP_KEEP,

			/// <summary>
			/// Zero the stencil value.
			/// </summary>
			Zero = D3DSTENCILOP_ZERO,

			/// <summary>
			/// Replace the stencil value.
			/// </summary>
			Replace = D3DSTENCILOP_REPLACE,

			/// <summary>
			/// Increment and clamp stencil value.
			/// </summary>
			IncrementSaturate = D3DSTENCILOP_INCRSAT,

			/// <summary>
			/// Decrement and clamp stencil value.
			/// </summary>
			DecrementSaturate = D3DSTENCILOP_DECRSAT,

			/// <summary>
			/// Invert the stencil value.
			/// </summary>
			Invert = D3DSTENCILOP_INVERT,

			/// <summary>
			/// Increment the stencil value.
			/// </summary>
			Increment = D3DSTENCILOP_INCR,

			/// <summary>
			/// Decrement the stencil value.
			/// </summary>
			Decrement = D3DSTENCILOP_DECR
		};
		
		public enum class SwapEffect : System::Int32
		{
			Discard = D3DSWAPEFFECT_DISCARD,
			Flip = D3DSWAPEFFECT_FLIP,
			Copy = D3DSWAPEFFECT_COPY,
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
		
		public enum class TextureAddress : System::Int32
		{
			Wrap = D3DTADDRESS_WRAP,
			Mirror = D3DTADDRESS_MIRROR,
			Clamp = D3DTADDRESS_CLAMP,
			Border = D3DTADDRESS_BORDER,
			MirrorOnce = D3DTADDRESS_MIRRORONCE,
		};

		[System::Flags]
		public enum class TextureAddressCaps : System::Int32
		{
			Wrap = D3DPTADDRESSCAPS_WRAP,
			Mirror = D3DPTADDRESSCAPS_MIRROR,
			Clamp = D3DPTADDRESSCAPS_CLAMP,
			Border = D3DPTADDRESSCAPS_BORDER,
			IndependentUV = D3DPTADDRESSCAPS_INDEPENDENTUV,
			MirrorOnce = D3DPTADDRESSCAPS_MIRRORONCE,
		};
		
		public enum class TextureArgument : System::Int32
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

		[System::Flags]
		public enum class TextureCaps : System::Int32
		{
			Perspective = D3DPTEXTURECAPS_PERSPECTIVE,
			Pow2 = D3DPTEXTURECAPS_POW2,
			Alpha = D3DPTEXTURECAPS_ALPHA,
			SquareOnly = D3DPTEXTURECAPS_SQUAREONLY,
			TextureRepeatNotScaledBySize = D3DPTEXTURECAPS_TEXREPEATNOTSCALEDBYSIZE,
			AlphaPalette = D3DPTEXTURECAPS_ALPHAPALETTE,
			NonPow2Conditional = D3DPTEXTURECAPS_NONPOW2CONDITIONAL,
			Projected = D3DPTEXTURECAPS_PROJECTED,
			CubeMap = D3DPTEXTURECAPS_CUBEMAP,
			VolumeMap = D3DPTEXTURECAPS_VOLUMEMAP,
			MipMap = D3DPTEXTURECAPS_MIPMAP,
			MipVolumeMap = D3DPTEXTURECAPS_MIPVOLUMEMAP,
			MipCubeMap = D3DPTEXTURECAPS_MIPCUBEMAP,
			CubeMapPow2 = D3DPTEXTURECAPS_CUBEMAP_POW2,
			VolumeMapPow2 = D3DPTEXTURECAPS_VOLUMEMAP_POW2,
			NoProjectedBumpEnvironment = D3DPTEXTURECAPS_NOPROJECTEDBUMPENV,
		};
		
		[System::Flags]
		public enum class TextureCoordIndex : System::Int32
		{
			PassThru = D3DTSS_TCI_PASSTHRU,
			CameraSpaceNormal = D3DTSS_TCI_CAMERASPACENORMAL,
			CameraSpacePosition = D3DTSS_TCI_CAMERASPACEPOSITION,
			CameraSpaceReflectionVector = D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR,
			SphereMap = D3DTSS_TCI_SPHEREMAP,
		};
		
		public enum class TextureFilter : System::Int32
		{
			None = D3DTEXF_NONE,
			Point = D3DTEXF_POINT,
			Linear = D3DTEXF_LINEAR,
			Anisotropic = D3DTEXF_ANISOTROPIC,
			PyramidalQuad = D3DTEXF_PYRAMIDALQUAD,
			GaussianQuad = D3DTEXF_GAUSSIANQUAD,
		};

		public enum class TextureOperation : System::Int32
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

			BumpEnvironmentMap = D3DTOP_BUMPENVMAP,
			BumpEnvironmentMapLuminance = D3DTOP_BUMPENVMAPLUMINANCE,

			DotProduct3 = D3DTOP_DOTPRODUCT3,

			MultiplyAdd = D3DTOP_MULTIPLYADD,
			Lerp = D3DTOP_LERP,
		};

		[System::Flags]
		public enum class TextureOperationCaps : System::Int32
		{
			Disable = D3DTEXOPCAPS_DISABLE,
			SelectArg1 = D3DTEXOPCAPS_SELECTARG1,
			SelectArg2 = D3DTEXOPCAPS_SELECTARG2,
			Modulate = D3DTEXOPCAPS_MODULATE,
			Modulate2X = D3DTEXOPCAPS_MODULATE2X,
			Modulate4X = D3DTEXOPCAPS_MODULATE4X,
			Add = D3DTEXOPCAPS_ADD,
			AddSigned = D3DTEXOPCAPS_ADDSIGNED,
			AddSigned2X = D3DTEXOPCAPS_ADDSIGNED2X,
			Subtract = D3DTEXOPCAPS_SUBTRACT,
			AddSmooth = D3DTEXOPCAPS_ADDSMOOTH,
			BlendDiffuseAlpha = D3DTEXOPCAPS_BLENDDIFFUSEALPHA,
			BlendTextureAlpha = D3DTEXOPCAPS_BLENDTEXTUREALPHA,
			BlendFactorAlpha = D3DTEXOPCAPS_BLENDFACTORALPHA,
			BlendTextureAlphaPM = D3DTEXOPCAPS_BLENDTEXTUREALPHAPM,
			BlendCurrentAlpha = D3DTEXOPCAPS_BLENDCURRENTALPHA,
			Premodulate = D3DTEXOPCAPS_PREMODULATE,
			ModulateAlphaAddColor = D3DTEXOPCAPS_MODULATEALPHA_ADDCOLOR,
			ModulateColorAddAlpha = D3DTEXOPCAPS_MODULATECOLOR_ADDALPHA,
			ModulateInvAlphaAddColor = D3DTEXOPCAPS_MODULATEINVALPHA_ADDCOLOR,
			ModulateInvColorAddAlpha = D3DTEXOPCAPS_MODULATEINVCOLOR_ADDALPHA,
			BumpEnvironmentMap = D3DTEXOPCAPS_BUMPENVMAP,
			BumpEnvironmentMapLuminance = D3DTEXOPCAPS_BUMPENVMAPLUMINANCE,
			DotProduct3 = D3DTEXOPCAPS_DOTPRODUCT3,
			MultiplyAdd = D3DTEXOPCAPS_MULTIPLYADD,
			Lerp = D3DTEXOPCAPS_LERP,
		};
		
		public enum class TextureStage : System::Int32
		{
			ColorOperation = D3DTSS_COLOROP,
			ColorArg1 = D3DTSS_COLORARG1,
			ColorArg2 = D3DTSS_COLORARG2,
			AlphaOperation = D3DTSS_ALPHAOP,
			AlphaArg1 = D3DTSS_ALPHAARG1,
			AlphaArg2 = D3DTSS_ALPHAARG2,
			BumpEnvironmentMat00 = D3DTSS_BUMPENVMAT00,
			BumpEnvironmentMat01 = D3DTSS_BUMPENVMAT01,
			BumpEnvironmentMat10 = D3DTSS_BUMPENVMAT10,
			BumpEnvironmentMat11 = D3DTSS_BUMPENVMAT11,
			TexCoordIndex = D3DTSS_TEXCOORDINDEX,
			BumpEnvironmentLScale = D3DTSS_BUMPENVLSCALE,
			BumpEnvironmentLOffset = D3DTSS_BUMPENVLOFFSET,
			TextureTransformFlags = D3DTSS_TEXTURETRANSFORMFLAGS,
			ColorArg0 = D3DTSS_COLORARG0,
			AlphaArg0 = D3DTSS_ALPHAARG0,
			ResultArg = D3DTSS_RESULTARG,
			Constant = D3DTSS_CONSTANT,
		};
		
		public enum class TextureTransform : System::Int32
		{
			Disable = D3DTTFF_DISABLE,
			Count1 = D3DTTFF_COUNT1,
			Count2 = D3DTTFF_COUNT2,
			Count3 = D3DTTFF_COUNT3,
			Count4 = D3DTTFF_COUNT4,
			Projected = D3DTTFF_PROJECTED,
		};

		public enum class TrackPriority : System::Int32
		{
			Low = D3DXPRIORITY_LOW,
			High = D3DXPRIORITY_HIGH
		};
		
		public enum class TransformState : System::Int32
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

		public enum class TransitionType : System::Int32
		{
			Linear = D3DXTRANSITION_LINEAR,
			EaseInEaseOut = D3DXTRANSITION_EASEINEASEOUT
		};
		
		[System::Flags]
		public enum class Usage : System::Int32
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
			SoftwareProcessing = D3DUSAGE_SOFTWAREPROCESSING,

			// Query usage
			QueryLegacyBumpMap = D3DUSAGE_QUERY_LEGACYBUMPMAP,
			QuerySrgbRead = D3DUSAGE_QUERY_SRGBREAD,
			QueryFilter = D3DUSAGE_QUERY_FILTER,
			QuerySrgbWrite = D3DUSAGE_QUERY_SRGBWRITE,
			QueryPostPixelShaderBlending = D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
			QueryVertexTexture = D3DUSAGE_QUERY_VERTEXTEXTURE,
			QueryWrapAndMip = D3DUSAGE_QUERY_WRAPANDMIP,
			QueryDisplacementMap = D3DUSAGE_DMAP,

			// Extensions
			R2VBTarget = RenderTarget | QueryDisplacementMap,
		};
		
		[System::Flags]
		public enum class VertexFormat : System::Int32
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

		[System::Flags]
		public enum class VertexFormatCaps : System::Int32
		{
			TextureCoordCountMask = D3DFVFCAPS_TEXCOORDCOUNTMASK,
			DoNotStripElements = D3DFVFCAPS_DONOTSTRIPELEMENTS,
			PointSize = D3DFVFCAPS_PSIZE,
		};

		[System::Flags]
		public enum class VertexProcessingCaps
		{
			TextureGen = D3DVTXPCAPS_TEXGEN,
			MaterialSource7 = D3DVTXPCAPS_MATERIALSOURCE7,
			DirectionalLights = D3DVTXPCAPS_DIRECTIONALLIGHTS,
			PositionAllLights = D3DVTXPCAPS_POSITIONALLIGHTS,
			LocalViewer = D3DVTXPCAPS_LOCALVIEWER,
			Tweening = D3DVTXPCAPS_TWEENING,
			TexGenSphereMap = D3DVTXPCAPS_TEXGEN_SPHEREMAP,
			NoTexGenNonLocalViewer = D3DVTXPCAPS_NO_TEXGEN_NONLOCALVIEWER,
		};

		[System::Flags]
		public enum class XFileFormat : System::Int32
		{
			Binary = D3DXF_FILEFORMAT_BINARY,
			Text = D3DXF_FILEFORMAT_TEXT,
			Compressed = D3DXF_FILEFORMAT_COMPRESSED
		};
		
		/// <remarks>
		/// Z-buffer usage types.
		/// </remarks>
		public enum class ZBufferType
		{
			/// <summary>
			/// Used to enable the depth buffer.
			/// </summary>
			UseZBuffer = D3DZB_TRUE,

			/// <summary>
			/// Used to disable the depth buffer.
			/// </summary>
			DontUseZBuffer = D3DZB_FALSE,

			/// <summary>
			/// Used to enable a W-buffer.
			/// </summary>
			UseWBuffer = D3DZB_USEW
		};
	}
}
