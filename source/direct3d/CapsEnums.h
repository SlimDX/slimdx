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
	namespace Direct3D
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
			BlendOp = D3DPMISCCAPS_BLENDOP,
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
			MultisampleToggle = D3DPRASTERCAPS_MULTISAMPLE_TOGGLE,
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
	}
}
