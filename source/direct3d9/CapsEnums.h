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
		[Flags]
		public enum class Caps : Int32
		{
			ReadScanline = D3DCAPS_READ_SCANLINE,
		};

		[Flags]
		public enum class Caps2 : Int32
		{
			FullScreenGamma = D3DCAPS2_FULLSCREENGAMMA,
			CanCalibrateGamma = D3DCAPS2_CANCALIBRATEGAMMA,
			CanManageResource = D3DCAPS2_CANMANAGERESOURCE,
			DynamicTextures = D3DCAPS2_DYNAMICTEXTURES,
			CanAutoGenMipMap = D3DCAPS2_CANAUTOGENMIPMAP
		};

		[Flags]
		public enum class Caps3 : Int32
		{
			AlphaFullscreenFlipOrDiscard = D3DCAPS3_ALPHA_FULLSCREEN_FLIP_OR_DISCARD,
			LinearToSrgbPresentation = D3DCAPS3_LINEAR_TO_SRGB_PRESENTATION,
			CopyToVideoMemory = D3DCAPS3_COPY_TO_VIDMEM,
			CopyToSystemMemory = D3DCAPS3_COPY_TO_SYSTEMMEM,
		};

		[Flags]
		public enum class CursorCaps : Int32
		{
			Color = D3DCURSORCAPS_COLOR,
			LowRes = D3DCURSORCAPS_LOWRES,
		};

		[Flags]
		public enum class DeviceCaps : Int32
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
			SeparateTextureMemories = D3DDEVCAPS_SEPARATETEXTUREMEMORIES,
			DrawPrimitives2Ex = D3DDEVCAPS_DRAWPRIMITIVES2EX,
			HWTransformAndLight = D3DDEVCAPS_HWTRANSFORMANDLIGHT,
			CanBlitSysToNonLocal = D3DDEVCAPS_CANBLTSYSTONONLOCAL,
			HWRasterization = D3DDEVCAPS_HWRASTERIZATION,
			PureDevice = D3DDEVCAPS_PUREDEVICE,
			QuinticRTPatches = D3DDEVCAPS_QUINTICRTPATCHES,
			RTPatches = D3DDEVCAPS_RTPATCHES,
			RTPatchHandleZero = D3DDEVCAPS_RTPATCHHANDLEZERO,
			NPatches = D3DDEVCAPS_NPATCHES,
		};

		[Flags]
		public enum class PrimitiveMiscCaps : Int32
		{
			MaskZ = D3DPMISCCAPS_MASKZ,
			CullNone = D3DPMISCCAPS_CULLNONE,
			CullCW = D3DPMISCCAPS_CULLCW,
			CullCCW = D3DPMISCCAPS_CULLCCW,
			ColorWriteEnable = D3DPMISCCAPS_COLORWRITEENABLE,
			ClipPlanesScaledPoints = D3DPMISCCAPS_CLIPPLANESCALEDPOINTS,
			ClipTLVerts = D3DPMISCCAPS_CLIPTLVERTS,
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

		[Flags]
		public enum class LineCaps : Int32
		{
			Texture = D3DLINECAPS_TEXTURE,
			DepthTest = D3DLINECAPS_ZTEST,
			Blend = D3DLINECAPS_BLEND,
			AlphaCompare = D3DLINECAPS_ALPHACMP,
			Fog = D3DLINECAPS_FOG,
			Antialias = D3DLINECAPS_ANTIALIAS,
		};

		[Flags]
		public enum class RasterCaps : Int32
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
			MultiSampleToggle = D3DPRASTERCAPS_MULTISAMPLE_TOGGLE,
		};

		[Flags]
		public enum class CompareCaps : Int32
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

		[Flags]
		public enum class BlendCaps : Int32
		{
			Zero = D3DPBLENDCAPS_ZERO,
			One = D3DPBLENDCAPS_ONE,
			SourceColor = D3DPBLENDCAPS_SRCCOLOR,
			InvSourceColor = D3DPBLENDCAPS_INVSRCCOLOR,
			SourceAlpha = D3DPBLENDCAPS_SRCALPHA,
			InvSourceAlpha = D3DPBLENDCAPS_INVSRCALPHA,
			DestAlpha = D3DPBLENDCAPS_DESTALPHA,
			InvDestAlpha = D3DPBLENDCAPS_INVDESTALPHA,
			DestColor = D3DPBLENDCAPS_DESTCOLOR,
			InvDestColor = D3DPBLENDCAPS_INVDESTCOLOR,
			SrcAlphaSat = D3DPBLENDCAPS_SRCALPHASAT,
			BothSourceAlpha = D3DPBLENDCAPS_BOTHSRCALPHA,
			BothInvSourceAlpha = D3DPBLENDCAPS_BOTHINVSRCALPHA,
			BlendFactor = D3DPBLENDCAPS_BLENDFACTOR,
		};

		[Flags]
		public enum class ShadeCaps : Int32
		{
			ColorGouraudRgb = D3DPSHADECAPS_COLORGOURAUDRGB,
			SpecularGouraudRgb = D3DPSHADECAPS_SPECULARGOURAUDRGB,
			AlphaGouraudBlend = D3DPSHADECAPS_ALPHAGOURAUDBLEND,
			FogGouraud = D3DPSHADECAPS_FOGGOURAUD,
		};

		[Flags]
		public enum class TextureCaps : Int32
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
			NoProjectedBumpEnv = D3DPTEXTURECAPS_NOPROJECTEDBUMPENV,
		};

		[Flags]
		public enum class FilterCaps : Int32
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

		[Flags]
		public enum class TextureAddressCaps : Int32
		{
			Wrap = D3DPTADDRESSCAPS_WRAP,
			Mirror = D3DPTADDRESSCAPS_MIRROR,
			Clamp = D3DPTADDRESSCAPS_CLAMP,
			Border = D3DPTADDRESSCAPS_BORDER,
			IndependentUV = D3DPTADDRESSCAPS_INDEPENDENTUV,
			MirrorOnce = D3DPTADDRESSCAPS_MIRRORONCE,
		};

		[Flags]
		public enum class StencilCaps : Int32
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

		[Flags]
		public enum class TextureOperationCaps : Int32
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
			BumpEnvMap = D3DTEXOPCAPS_BUMPENVMAP,
			BumpEnvMapLuminance = D3DTEXOPCAPS_BUMPENVMAPLUMINANCE,
			DotProduct3 = D3DTEXOPCAPS_DOTPRODUCT3,
			MultiplyAdd = D3DTEXOPCAPS_MULTIPLYADD,
			Lerp = D3DTEXOPCAPS_LERP,
		};

		[Flags]
		public enum class VertexFormatCaps : Int32
		{
			TexCoordCountMask = D3DFVFCAPS_TEXCOORDCOUNTMASK,
			DoNotStripElements = D3DFVFCAPS_DONOTSTRIPELEMENTS,
			PointSize = D3DFVFCAPS_PSIZE,
		};

		[Flags]
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

		[Flags]
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

		[Flags]
		public enum class DeclTypeCaps
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
	}
}
