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
#include "D3DXEnums.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		// NOTE: The enumerations defined in this file are in alphabetical order. When
		//       adding new enumerations or renaming existing ones, please make sure
		//       the ordering is maintained.
		
		/// <summary>Defines the basis type of a high-order patch surface.</summary>
		/// <unmanaged>D3DBASISTYPE</unmanaged>
		public enum class Basis : System::Int32
		{
			/// <summary>
			/// Input vertices are treated as a series of Bezier patches.
			/// </summary>
			Bezier = D3DBASIS_BEZIER,

			/// <summary>
			/// Input vertices are treated as control points of a B-spline surface.
			/// </summary>
			BSpline = D3DBASIS_BSPLINE,

			/// <summary>
			/// An interpolation basis defines the surface so that the surface goes through all the input vertices specified.
			/// </summary>
			CatmullRom = D3DBASIS_CATMULL_ROM,
		};
		
		/// <summary>Defines the supported blend mode.</summary>
		/// <unmanaged>D3DBLEND</unmanaged>
		public enum class Blend : System::Int32
		{
			/// <summary>
			/// Blend factor is (0, 0, 0, 0).
			/// </summary>
			Zero = D3DBLEND_ZERO,

			/// <summary>
			/// Blend factor is (1, 1, 1, 1).
			/// </summary>
			One = D3DBLEND_ONE,

			/// <summary>
			/// Blend factor is the source color.
			/// </summary>
			SourceColor = D3DBLEND_SRCCOLOR,

			/// <summary>
			/// Blend factor is one minus the source color.
			/// </summary>
			InverseSourceColor = D3DBLEND_INVSRCCOLOR,

			/// <summary>
			/// Blend factor is the source alpha.
			/// </summary>
			SourceAlpha = D3DBLEND_SRCALPHA,

			/// <summary>
			/// Blend factor is one minus the source alpha.
			/// </summary>
			InverseSourceAlpha = D3DBLEND_INVSRCALPHA,

			/// <summary>
			/// Blend factor is the destination alpha.
			/// </summary>
			DestinationAlpha = D3DBLEND_DESTALPHA,

			/// <summary>
			/// Blend factor is one minus the destination alpha.
			/// </summary>
			InverseDestinationAlpha = D3DBLEND_INVDESTALPHA,

			/// <summary>
			/// Blend factor is the destination color.
			/// </summary>
			DestinationColor = D3DBLEND_DESTCOLOR,

			/// <summary>
			/// Blend factor is one minus the destination color.
			/// </summary>
			InverseDestinationColor = D3DBLEND_INVDESTCOLOR,

			/// <summary>
			/// Blend factor is (f, f, f, 1); where f = min(As, 1 - Ad).
			/// </summary>
			SourceAlphaSaturated = D3DBLEND_SRCALPHASAT,

			/// <summary>
			/// Source blend factor is one minus the source alpha, and destination blend factor
			/// is one minus the destination alpha.
			/// </summary>
			BothInverseSourceAlpha = D3DBLEND_BOTHINVSRCALPHA,

			/// <summary>
			/// Constant color blending factor used by the frame-buffer blender.
			/// </summary>
			BlendFactor = D3DBLEND_BLENDFACTOR,

			/// <summary>
			/// Inverted constant color blending factor used by the frame-buffer blender.
			/// </summary>
			InverseBlendFactor = D3DBLEND_INVBLENDFACTOR,

			/// <summary>
			/// Blend factor is the output color of the pixel shader. Only available in Direct3D9Ex.
			/// </summary>
			SourceColor2 = D3DBLEND_SRCCOLOR2,

			/// <summary>
			/// Blend factor is one minus the output color of the pixel shader. Only available in Direct3D9Ex.
			/// </summary>
			InverseSourceColor2 = D3DBLEND_INVSRCCOLOR2
		};

		/// <summary>
		/// Defines possible source blending capabilities.
		/// </summary>
		[System::Flags]
		public enum class BlendCaps : System::Int32
		{
			/// <summary>
			/// The device supports <see cref="Blend.Zero"/>.
			/// </summary>
			Zero = D3DPBLENDCAPS_ZERO,

			/// <summary>
			/// The device supports <see cref="Blend.One"/>.
			/// </summary>
			One = D3DPBLENDCAPS_ONE,

			/// <summary>
			/// The device supports <see cref="Blend.SourceColor"/>.
			/// </summary>
			SourceColor = D3DPBLENDCAPS_SRCCOLOR,

			/// <summary>
			/// The device supports <see cref="Blend.InverseSourceColor"/>.
			/// </summary>
			InverseSourceColor = D3DPBLENDCAPS_INVSRCCOLOR,

			/// <summary>
			/// The device supports <see cref="Blend.SourceAlpha"/>.
			/// </summary>
			SourceAlpha = D3DPBLENDCAPS_SRCALPHA,

			/// <summary>
			/// The device supports <see cref="Blend.InverseSourceAlpha"/>.
			/// </summary>
			InverseSourceAlpha = D3DPBLENDCAPS_INVSRCALPHA,

			/// <summary>
			/// The device supports <see cref="Blend.DestinationAlpha"/>.
			/// </summary>
			DestinationAlpha = D3DPBLENDCAPS_DESTALPHA,

			/// <summary>
			/// The device supports <see cref="Blend.InverseDestinationAlpha"/>.
			/// </summary>
			InverseDestinationAlpha = D3DPBLENDCAPS_INVDESTALPHA,

			/// <summary>
			/// The device supports <see cref="Blend.DestinationColor"/>.
			/// </summary>
			DestinationColor = D3DPBLENDCAPS_DESTCOLOR,

			/// <summary>
			/// The device supports <see cref="Blend.InverseDestinationColor"/>.
			/// </summary>
			InverseDestinationColor = D3DPBLENDCAPS_INVDESTCOLOR,

			/// <summary>
			/// The device supports <see cref="Blend.SourceAlphaSaturated"/>.
			/// </summary>
			SourceAlphaSaturated = D3DPBLENDCAPS_SRCALPHASAT,

			/// <summary>
			/// The device supports <see cref="Blend.BothInverseSourceAlpha"/>.
			/// </summary>
			BothInverseSourceAlpha = D3DPBLENDCAPS_BOTHINVSRCALPHA,

			/// <summary>
			/// The device supports <see cref="Blend.BlendFactor"/> and <see cref="Blend.InverseBlendFactor"/>
			/// </summary>
			BlendFactor = D3DPBLENDCAPS_BLENDFACTOR
		};
		
		/// <summary>Defines the supported blend operations.</summary>
		/// <unmanaged>D3DBLENDOP</unmanaged>
		public enum class BlendOperation : System::Int32
		{
			/// <summary>
			/// The result is the destination added to the source.
			/// </summary>
			Add = D3DBLENDOP_ADD,

			/// <summary>
			/// The result is the destination subtracted from the source.
			/// </summary>
			Subtract = D3DBLENDOP_SUBTRACT,

			/// <summary>
			/// The result is the source subtracted from the destination.
			/// </summary>
			ReverseSubtract = D3DBLENDOP_REVSUBTRACT,

			/// <summary>
			/// The result is the minimum of the source and destination.
			/// </summary>
			Minimum = D3DBLENDOP_MIN,

			/// <summary>
			/// The result is the maximum of the source and destination.
			/// </summary>
			Maximum = D3DBLENDOP_MAX,
		};

		/// <summary>Driver-specific capability flags.</summary>
		[System::Flags]
		public enum class Caps : System::Int32
		{
			/// <summary>
			/// No extra capabilities defined.
			/// </summary>
			None = 0,

			/// <summary>
			/// Display hardware is capable of returning the current scan line.
			/// </summary>
			ReadScanline = D3DCAPS_READ_SCANLINE,
		};

		/// <summary>Driver-specific capability flags.</summary>
		/// <unmanaged>D3DCAPS2</unmanaged>
		[System::Flags]
		public enum class Caps2 : System::Int32
		{
			/// <summary>
			/// No extra capabilities defined.
			/// </summary>
			None = 0,

			/// <summary>
			/// The driver supports dynamic gamma ramp adjustment in fullscreen mode.
			/// </summary>
			FullScreenGamma = D3DCAPS2_FULLSCREENGAMMA,

			/// <summary>
			/// The system has a calibrator installed that can automatically adjust the gamma ramp so that
			/// the result is identical on all systems that have a calibrator.
			/// </summary>
			CanCalibrateGamma = D3DCAPS2_CANCALIBRATEGAMMA,

			/// <summary>
			/// The driver is capable of managing resources.
			/// </summary>
			CanManageResource = D3DCAPS2_CANMANAGERESOURCE,

			/// <summary>
			/// The driver supports dynamic textures.
			/// </summary>
			DynamicTextures = D3DCAPS2_DYNAMICTEXTURES,

			/// <summary>
			/// The driver is capable of automatically generating mipmaps.
			/// </summary>
			CanAutoGenerateMipMap = D3DCAPS2_CANAUTOGENMIPMAP
		};

		/// <summary>Driver-specific capability flags.</summary>
		/// <unmanaged>D3DCAPS3</unmanaged>
		[System::Flags]
		public enum class Caps3 : System::Int32
		{
			/// <summary>
			/// No extra capabilities defined.
			/// </summary>
			None = 0,

			/// <summary>
			/// Indicates that the device can respect the AlphaBlendEnable render state in fullscreen mode
			/// while using the Flip or Discard swap effect.
			/// </summary>
			AlphaFullScreenFlipOrDiscard = D3DCAPS3_ALPHA_FULLSCREEN_FLIP_OR_DISCARD,

			/// <summary>
			/// Indicates that the device can perform gamma correction from a windowed back buffer to
			/// an sRGB desktop.
			/// </summary>
			LinearToSrgbPresentation = D3DCAPS3_LINEAR_TO_SRGB_PRESENTATION,

			/// <summary>
			/// Device can accelerate a memory copy from system memory to local video memory.
			/// </summary>
			CopyToVideoMemory = D3DCAPS3_COPY_TO_VIDMEM,

			/// <summary>
			/// Device can accelerate a memory copy from local video memory to system memory.
			/// </summary>
			CopyToSystemMemory = D3DCAPS3_COPY_TO_SYSTEMMEM,
		};

		/// <summary>
		/// Defines possible character sets for fonts.
		/// </summary>
		public enum class CharacterSet : System::Int32
		{
			/// <summary>
			/// The ANSI character set.
			/// </summary>
			Ansi = ANSI_CHARSET,

			/// <summary>
			/// The default system character set.
			/// </summary>
			Default = DEFAULT_CHARSET,

			/// <summary>
			/// The symbol character set.
			/// </summary>
			Symbol = SYMBOL_CHARSET,

			/// <summary>
			/// The ShiftJIS character set.
			/// </summary>
			ShiftJIS = SHIFTJIS_CHARSET,

			/// <summary>
			/// The Hangul character set.
			/// </summary>
			Hangul = HANGUL_CHARSET,

			/// <summary>
			/// The GB2312 character set.
			/// </summary>
			GB2312 = GB2312_CHARSET,

			/// <summary>
			/// The Chinese character set.
			/// </summary>
			ChineseBig5 = CHINESEBIG5_CHARSET,

			/// <summary>
			/// The OEM character set.
			/// </summary>
			Oem = OEM_CHARSET,

			/// <summary>
			/// The Johab character set.
			/// </summary>
			Johab = JOHAB_CHARSET,

			/// <summary>
			/// The Hebrew character set.
			/// </summary>
			Hebrew = HEBREW_CHARSET,

			/// <summary>
			/// The Arabic character set.
			/// </summary>
			Arabic = ARABIC_CHARSET,

			/// <summary>
			/// The Greek character set.
			/// </summary>
			Greek = GREEK_CHARSET,

			/// <summary>
			/// The Turkish character set.
			/// </summary>
			Turkish = TURKISH_CHARSET,

			/// <summary>
			/// The Vietnamese character set.
			/// </summary>
			Vietnamese = VIETNAMESE_CHARSET,

			/// <summary>
			/// The Thai character set.
			/// </summary>
			Thai = THAI_CHARSET,

			/// <summary>
			/// The East Europe character set.
			/// </summary>
			EastEurope = EASTEUROPE_CHARSET,

			/// <summary>
			/// The Russian character set.
			/// </summary>
			Russian = RUSSIAN_CHARSET,

			/// <summary>
			/// The Baltic character set.
			/// </summary>
			Baltic = BALTIC_CHARSET,

			/// <summary>
			/// The Mac character set.
			/// </summary>
			Mac = MAC_CHARSET
		};

		/// <summary>These flags identify a surface to reset when calling <see cref="Device.Clear"/>.</summary>
		/// <unmanaged>D3DCLEAR</unmanaged>
		[System::Flags]
		public enum class ClearFlags : System::Int32
		{
			/// <summary>
			/// Don't clear any surfaces.
			/// </summary>
			None = 0,

			/// <summary>
			/// Clear the stencil surface.
			/// </summary>
			Stencil = D3DCLEAR_STENCIL,

			/// <summary>
			/// Clear the render target.
			/// </summary>
			Target = D3DCLEAR_TARGET,

			/// <summary>
			/// Clear the depth buffer.
			/// </summary>
			ZBuffer = D3DCLEAR_ZBUFFER
		};

		/// <summary>
		/// Specifies a set of values that describe the current clip status.
		/// </summary>
		[System::Flags]
		public enum class ClipFlags : System::Int32
		{
			/// <summary>
			/// Combination of all clip flags.
			/// </summary>
			All = D3DCS_ALL,

			/// <summary>
			/// All vertices are clipped by the left plane of the viewing frustum.
			/// </summary>
			Left = D3DCS_LEFT,

			/// <summary>
			/// All vertices are clipped by the right plane of the viewing frustum.
			/// </summary>
			Right = D3DCS_RIGHT,

			/// <summary>
			/// All vertices are clipped by the top plane of the viewing frustum.
			/// </summary>
			Top = D3DCS_TOP,

			/// <summary>
			/// All vertices are clipped by the bottom plane of the viewing frustum.
			/// </summary>
			Bottom = D3DCS_BOTTOM,

			/// <summary>
			/// All vertices are clipped by the front plane of the viewing frustum.
			/// </summary>
			Front = D3DCS_FRONT,

			/// <summary>
			/// All vertices are clipped by the back plane of the viewing frustum.
			/// </summary>
			Back = D3DCS_BACK,

			/// <summary>
			/// Application defined clipping plane.
			/// </summary>
			Plane0 = D3DCS_PLANE0,

			/// <summary>
			/// Application defined clipping plane.
			/// </summary>
			Plane1 = D3DCS_PLANE1,

			/// <summary>
			/// Application defined clipping plane.
			/// </summary>
			Plane2 = D3DCS_PLANE2,

			/// <summary>
			/// Application defined clipping plane.
			/// </summary>
			Plane3 = D3DCS_PLANE3,

			/// <summary>
			/// Application defined clipping plane.
			/// </summary>
			Plane4 = D3DCS_PLANE4,

			/// <summary>
			/// Application defined clipping plane.
			/// </summary>
			Plane5 = D3DCS_PLANE5
		};
		
		/// <summary>
		/// Defines the location at which a color or color component must be accessed for lighting calculations.
		/// </summary>
		/// <unmanaged>D3DMATERIALCOLORSOURCE</unmanaged>
		public enum class ColorSource : System::Int32
		{
			/// <summary>
			/// Use the color from the current material.
			/// </summary>
			Material = D3DMCS_MATERIAL,

			/// <summary>
			/// Use the diffuse vertex color.
			/// </summary>
			Color1 = D3DMCS_COLOR1,

			/// <summary>
			/// Use the specular vertex color.
			/// </summary>
			Color2 = D3DMCS_COLOR2,
		};
		
		/// <summary>
		/// Flags that enable a per-channel write for the render target color buffer.
		/// </summary>
		[System::Flags]
		public enum class ColorWriteEnable : System::Int32
		{
			/// <summary>
			/// Allow writes to the alpha channel.
			/// </summary>
			Alpha = D3DCOLORWRITEENABLE_ALPHA,

			/// <summary>
			/// Allow writes to the blue channel.
			/// </summary>
			Blue = D3DCOLORWRITEENABLE_BLUE,

			/// <summary>
			/// Allow writes to the green channel.
			/// </summary>
			Green = D3DCOLORWRITEENABLE_GREEN,

			/// <summary>
			/// Allow writes to the red channel.
			/// </summary>
			Red = D3DCOLORWRITEENABLE_RED,

			/// <summary>
			/// Allow writes to all channels.
			/// </summary>
			All = Alpha | Blue | Green | Red
		};

		/// <summary>Specifies possible compare functions.</summary>
		/// <unmanaged>D3DCMPFUNC</unmanaged>
		public enum class Compare
		{
			/// <summary>
			/// Always fail the test.
			/// </summary>
			Never = D3DCMP_NEVER,

			/// <summary>
			/// Accept the new pixel if its value is less than the value of the current pixel.
			/// </summary>
			Less = D3DCMP_LESS,

			/// <summary>
			/// Accept the new pixel if its value equals the value of the current pixel.
			/// </summary>
			Equal = D3DCMP_EQUAL,

			/// <summary>
			/// Accept the new pixel if its value is less than or equal to the value of the current pixel.
			/// </summary>
			LessEqual = D3DCMP_LESSEQUAL,

			/// <summary>
			/// Accept the new pixel if its value is greater than the value of the current pixel.
			/// </summary>
			Greater = D3DCMP_GREATER,

			/// <summary>
			/// Accept the new pixel if its value does not equal the value of the current pixel.
			/// </summary>
			NotEqual = D3DCMP_NOTEQUAL,

			/// <summary>
			/// Accept the new pixel if its value is greater than or equal to the value of the current pixel.
			/// </summary>
			GreaterEqual = D3DCMP_GREATEREQUAL,

			/// <summary>
			/// Always pass the test.
			/// </summary>
			Always = D3DCMP_ALWAYS
		};

		/// <summary>
		/// Specifies a set of flags that describe the supported compare capabilities of the device.
		/// </summary>
		[System::Flags]
		public enum class CompareCaps : System::Int32
		{
			/// <summary>
			/// The device supports <see cref="Compare.Never"/>.
			/// </summary>
			Never = D3DPCMPCAPS_NEVER,

			/// <summary>
			/// The device supports <see cref="Compare.Less"/>.
			/// </summary>
			Less = D3DPCMPCAPS_LESS,

			/// <summary>
			/// The device supports <see cref="Compare.Equal"/>.
			/// </summary>
			Equal = D3DPCMPCAPS_EQUAL,

			/// <summary>
			/// The device supports <see cref="Compare.lessEqual"/>.
			/// </summary>
			LessEqual = D3DPCMPCAPS_LESSEQUAL,

			/// <summary>
			/// The device supports <see cref="Compare.Greater"/>.
			/// </summary>
			Greater = D3DPCMPCAPS_GREATER,

			/// <summary>
			/// The device supports <see cref="Compare.NotEqual"/>.
			/// </summary>
			NotEqual = D3DPCMPCAPS_NOTEQUAL,

			/// <summary>
			/// The device supports <see cref="Compare.GreaterEqual"/>.
			/// </summary>
			GreaterEqual = D3DPCMPCAPS_GREATEREQUAL,

			/// <summary>
			/// The device supports <see cref="Compare.Always"/>.
			/// </summary>
			Always = D3DPCMPCAPS_ALWAYS
		};

		/// <summary>A combination of one or more flags that control the device creation behavior.</summary>
		/// <unmanaged>D3DCREATE</unmanaged>
		[System::Flags]
		public enum class CreateFlags : System::Int32
		{
			/// <summary>
			/// No extra creation flags specified.
			/// </summary>
			None = 0,

			/// <summary>
			/// Asks the device to drive all heads that the master adapter owns.
			/// </summary>
			AdapterGroupDevice = D3DCREATE_ADAPTERGROUP_DEVICE,

			/// <summary>
			/// Direct3D will managed resources instead of the driver.
			/// </summary>
			DisableDriverManagement = D3DCREATE_DISABLE_DRIVER_MANAGEMENT,

			/// <summary>
			/// Direct3D will managed resources instead of the driver. Errors will still be thrown
			/// for conditions such as insufficient video memory.
			/// </summary>
			DisableExtendedDriverManagement = D3DCREATE_DISABLE_DRIVER_MANAGEMENT_EX,

			/// <summary>
			/// Causes the runtime to not register hotkeys for print screen. Only available in Direct3D9Ex.
			/// </summary>
			DisablePrintScreen = D3DCREATE_DISABLE_PRINTSCREEN,

			/// <summary>
			/// Restrict computation to the main application thread. Only available on Windows Vista.
			/// </summary>
			DisablePsgpThreading = D3DCREATE_DISABLE_PSGP_THREADING,

			/// <summary>
			/// Enables the gathering of presentation statistics. Only available in Direct3D9Ex.
			/// </summary>
			EnablePresentStatistics = D3DCREATE_ENABLE_PRESENTSTATS,

			/// <summary>
			/// Preserve the floating point precision used in the calling thread.
			/// </summary>
			FpuPreserve = D3DCREATE_FPU_PRESERVE,

			/// <summary>
			/// Tells the device to use hardware vertex processing.
			/// </summary>
			HardwareVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING,

			/// <summary>
			/// Tells the device to use mixed vertex processing.
			/// </summary>
			MixedVertexProcessing = D3DCREATE_MIXED_VERTEXPROCESSING,

			/// <summary>
			/// Indicates that the application requests Direct3D to be multithread safe.
			/// </summary>
			Multithreaded = D3DCREATE_MULTITHREADED,

			/// <summary>
			/// Indicates that Direct3D must not alter the focus window in any way.
			/// </summary>
			NoWindowChanges = D3DCREATE_NOWINDOWCHANGES,

			/// <summary>
			/// Specifies that the device does not support Get* calls for anything that can be stored
			/// in state blocks.
			/// </summary>
			PureDevice = D3DCREATE_PUREDEVICE,

			/// <summary>
			/// Allows screensavers during a fullscreen application.
			/// </summary>
			AllowScreensavers = D3DCREATE_SCREENSAVER,

			/// <summary>
			/// Tells the device to use software vertex processing.
			/// </summary>
			SoftwareVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		};

		/// <summary>
		/// Specifies how to combine glyph data from the source and destination surfaces in a ComposeRect operation.
		/// </summary>
		/// <unmanaged>D3DCOMPOSERECTSOP</unmanaged>
		public enum class ComposeRectOperation : System::Int32
		{
			/// <summary>
			/// Copy the source to the destination.
			/// </summary>
			Copy = D3DCOMPOSERECTS_COPY,

			/// <summary>
			/// Bitwise OR the source and the destination.
			/// </summary>
			Or = D3DCOMPOSERECTS_OR,

			/// <summary>
			/// Bitwise AND the source and the destination.
			/// </summary>
			And = D3DCOMPOSERECTS_AND,

			/// <summary>
			/// Copy the negated source to the destination.
			/// </summary>
			Negate = D3DCOMPOSERECTS_NEG
		};
		
		/// <summary>Defines the faces of a cubemap.</summary>
		/// <unmanaged>D3DCUBEMAP_FACES</unmanaged>
		public enum class CubeMapFace : System::Int32
		{
			/// <summary>
			/// Positive x-face of the cubemap.
			/// </summary>
			PositiveX = D3DCUBEMAP_FACE_POSITIVE_X,

			/// <summary>
			/// Negative x-face of the cubemap.
			/// </summary>
			NegativeX = D3DCUBEMAP_FACE_NEGATIVE_X,

			/// <summary>
			/// Positive y-face of the cubemap.
			/// </summary>
			PositiveY = D3DCUBEMAP_FACE_POSITIVE_Y,

			/// <summary>
			/// Negative y-face of the cubemap.
			/// </summary>
			NegativeY = D3DCUBEMAP_FACE_NEGATIVE_Y,

			/// <summary>
			/// Positive z-face of the cubemap.
			/// </summary>
			PositiveZ = D3DCUBEMAP_FACE_POSITIVE_Z,

			/// <summary>
			/// Negative z-face of the cubemap.
			/// </summary>
			NegativeZ = D3DCUBEMAP_FACE_NEGATIVE_Z
		};
		
		/// <summary>Defines the supported culling modes.</summary>
		/// <unmanaged>D3DCULL</unmanaged>
		public enum class Cull : System::Int32
		{
			/// <summary>
			/// Cull back faces with clockwise vertices.
			/// </summary>
			Clockwise = D3DCULL_CW,

			/// <summary>
			/// Cull back faces with counterclockwise vertices.
			/// </summary>
			Counterclockwise = D3DCULL_CCW,

			/// <summary>
			/// Do not cull back faces.
			/// </summary>
			None = D3DCULL_NONE
		};

		/// <summary>Driver cursor capability flags.</summary>
		/// <unmanaged>D3DCURSORCAPS</unmanaged>
		[System::Flags]
		public enum class CursorCaps : System::Int32
		{
			/// <summary>
			/// The driver supports color cursors.
			/// </summary>
			Color = D3DCURSORCAPS_COLOR,

			/// <summary>
			/// The driver supports cursors in low resolution modes.
			/// </summary>
			LowResolution = D3DCURSORCAPS_LOWRES,
		};

		/// <summary>
		/// Defines settings for debug monitor tokens.
		/// </summary>
		/// <unmanaged>D3DDEBUGMONITORTOKENS</unmanaged>
		public enum class DebugMonitorTokens : System::Int32
		{
			/// <summary>
			/// Enable the debug monitor.
			/// </summary>
			Enable = D3DDMT_ENABLE,

			/// <summary>
			/// Disable the debug monitor.
			/// </summary>
			Disable = D3DDMT_DISABLE
		};
		
		/// <summary>
		/// Defines the vertex declaration method which is a predefined operation performed by the
		/// tessellator (or any procedural geometry routine on the vertex data during tessellation).
		/// </summary>
		/// <unmanaged>D3DDECLMETHOD</unmanaged>
		public enum class DeclarationMethod : System::Byte
		{
			/// <summary>
			/// Default value. The tessellator copies the vertex data as is, with no additional calculations.
			/// </summary>
			Default = D3DDECLMETHOD_DEFAULT,

			/// <summary>
			/// Computes the tangent at a point on the rectangle or triangle patch in the U direction.
			/// </summary>
			PartialU = D3DDECLMETHOD_PARTIALU,

			/// <summary>
			/// Computes the tangent at a point on the rectangle or triangle patch in the V direction.
			/// </summary>
			PartialV = D3DDECLMETHOD_PARTIALV,

			/// <summary>
			/// Computes the normal at a point on the rectangle or triangle patch by taking the cross product of the two tangents.
			/// </summary>
			CrossUV = D3DDECLMETHOD_CROSSUV,

			/// <summary>
			/// Copies out the U and V values at a point on the rectangle or triangle patch.
			/// </summary>
			UV = D3DDECLMETHOD_UV,

			/// <summary>
			/// Look up a displacement map.
			/// </summary>
			Lookup = D3DDECLMETHOD_LOOKUP,

			/// <summary>
			/// Lookup a presampled displacement map.
			/// </summary>
			LookupPresampled = D3DDECLMETHOD_LOOKUPPRESAMPLED
		};

		/// <summary>Defines a vertex declaration data type.</summary>
		/// <unmanaged>D3DDECLTYPE</unmanaged>
		public enum class DeclarationType : System::Byte
		{
			/// <summary>
			/// One component float.
			/// </summary>
			Float1 = D3DDECLTYPE_FLOAT1,

			/// <summary>
			/// Two component float.
			/// </summary>
			Float2 = D3DDECLTYPE_FLOAT2,

			/// <summary>
			/// Three component float.
			/// </summary>
			Float3 = D3DDECLTYPE_FLOAT3,

			/// <summary>
			/// Four component float.
			/// </summary>
			Float4 = D3DDECLTYPE_FLOAT4,

			/// <summary>
			/// Four component, packed, unsigned bytes mapped to the 0 to 1 range. Input is a color
			/// and is expanded to RGBA order.
			/// </summary>
			Color = D3DDECLTYPE_D3DCOLOR,

			/// <summary>
			/// Four component, unsigned byte.
			/// </summary>
			Ubyte4 = D3DDECLTYPE_UBYTE4,

			/// <summary>
			/// Two component, signed short.
			/// </summary>
			Short2 = D3DDECLTYPE_SHORT2,

			/// <summary>
			/// Four component, signed short.
			/// </summary>
			Short4 = D3DDECLTYPE_SHORT4,

			/// <summary>
			/// Four component byte with each byte normalized by dividing by 255.0f.
			/// </summary>
			UByte4N = D3DDECLTYPE_UBYTE4N,

			/// <summary>
			/// Normalized, two component, signed short normalized by dividing by 32767.0f.
			/// </summary>
			Short2N = D3DDECLTYPE_SHORT2N,

			/// <summary>
			/// Normalized, four component, signed short normalized by dividing by 32767.0f.
			/// </summary>
			Short4N = D3DDECLTYPE_SHORT4N,

			/// <summary>
			/// Normalized, two component, unsigned short normalized by dividing by 65535.0f.
			/// </summary>
			UShort2N = D3DDECLTYPE_USHORT2N,

			/// <summary>
			/// Normalized, four component, unsigned short normalized by dividing by 65535.0f.
			/// </summary>
			UShort4N = D3DDECLTYPE_USHORT4N,

			/// <summary>
			/// Three component, unsigned, 10 10 10 format.
			/// </summary>
			UDec3 = D3DDECLTYPE_UDEC3,

			/// <summary>
			/// Three component, signed, 10 10 10 format normalized by dividing by 511.0f.
			/// </summary>
			Dec3N = D3DDECLTYPE_DEC3N,

			/// <summary>
			/// Two component, 16 bit, floating point.
			/// </summary>
			HalfTwo = D3DDECLTYPE_FLOAT16_2,

			/// <summary>
			/// Four component, 16 bit, floating point.
			/// </summary>
			HalfFour = D3DDECLTYPE_FLOAT16_4,

			/// <summary>
			/// Type field in the declaration is unused.
			/// </summary>
			Unused = D3DDECLTYPE_UNUSED
		};

		/// <summary>
		/// Specifies the declaration types supported by the device.
		/// </summary>
		[System::Flags]
		public enum class DeclarationTypeCaps
		{
			/// <summary>
			/// The device supports <see cref="DeclarationType.UByte4"/>.
			/// </summary>
			UByte4 = D3DDTCAPS_UBYTE4,

			/// <summary>
			/// The device supports <see cref="DeclarationType.UByte4N"/>.
			/// </summary>
			UByte4N = D3DDTCAPS_UBYTE4N,

			/// <summary>
			/// The device supports <see cref="DeclarationType.Short2N"/>.
			/// </summary>
			Short2N = D3DDTCAPS_SHORT2N,

			/// <summary>
			/// The device supports <see cref="DeclarationType.Short4N"/>.
			/// </summary>
			Short4N = D3DDTCAPS_SHORT4N,

			/// <summary>
			/// The device supports <see cref="DeclarationType.UShort2N"/>.
			/// </summary>
			UShort2N = D3DDTCAPS_USHORT2N,

			/// <summary>
			/// The device supports <see cref="DeclarationType.UShort4N"/>.
			/// </summary>
			UShort4N = D3DDTCAPS_USHORT4N,

			/// <summary>
			/// The device supports <see cref="DeclarationType.UDec3"/>.
			/// </summary>
			UDec3 = D3DDTCAPS_UDEC3,

			/// <summary>
			/// The device supports <see cref="DeclarationType.Dec3N"/>.
			/// </summary>
			Dec3N = D3DDTCAPS_DEC3N,

			/// <summary>
			/// The device supports <see cref="DeclarationType.HalfTwo"/>.
			/// </summary>
			HalfTwo = D3DDTCAPS_FLOAT16_2,

			/// <summary>
			/// The device supports <see cref="DeclarationType.HalfFour"/>.
			/// </summary>
			HalfFour = D3DDTCAPS_FLOAT16_4,
		};

		/// <summary>Identifies the intended use of vertex data.</summary>
		/// <unmanaged>D3DDECLUSAGE</unmanaged>
		public enum class DeclarationUsage : System::Byte
		{
			/// <summary>
			/// Position data ranging from (-1, -1) to (1, 1).
			/// </summary>
			Position = D3DDECLUSAGE_POSITION,

			/// <summary>
			/// Blending weight data.
			/// </summary>
			BlendWeight = D3DDECLUSAGE_BLENDWEIGHT,

			/// <summary>
			/// Blending indices data.
			/// </summary>
			BlendIndices = D3DDECLUSAGE_BLENDINDICES,

			/// <summary>
			/// Vertex normal data.
			/// </summary>
			Normal = D3DDECLUSAGE_NORMAL,

			/// <summary>
			/// Point size data.
			/// </summary>
			PointSize = D3DDECLUSAGE_PSIZE,

			/// <summary>
			/// Texture coordinate data.
			/// </summary>
			TextureCoordinate = D3DDECLUSAGE_TEXCOORD,

			/// <summary>
			/// Vertex tangent data.
			/// </summary>
			Tangent = D3DDECLUSAGE_TANGENT,

			/// <summary>
			/// Vertex binormal data.
			/// </summary>
			Binormal = D3DDECLUSAGE_BINORMAL,

			/// <summary>
			/// Single positive floating point value.
			/// </summary>
			TessellateFactor = D3DDECLUSAGE_TESSFACTOR,

			/// <summary>
			/// Vertex data contains transformed position data ranging from (0, 0) to (viewport width, viewport height).
			/// </summary>
			PositionTransformed = D3DDECLUSAGE_POSITIONT,

			/// <summary>
			/// Vertex data contains diffuse or specular color.
			/// </summary>
			Color = D3DDECLUSAGE_COLOR,

			/// <summary>
			/// Vertex data contains fog data.
			/// </summary>
			Fog = D3DDECLUSAGE_FOG,

			/// <summary>
			/// Vertex data contains depth data.
			/// </summary>
			Depth = D3DDECLUSAGE_DEPTH,

			/// <summary>
			/// Vertex data contains sampler data.
			/// </summary>
			Sample = D3DDECLUSAGE_SAMPLE
		};
		
		/// <summary>Defines the degree of the variables in the equation that describes a curve.</summary>
		/// <unmanaged>D3DDEGREETYPE</unmanaged>
		public enum class Degree : System::Int32
		{
			/// <summary>
			/// Curve is described by variables of first order.
			/// </summary>
			Linear = D3DDEGREE_LINEAR,

			/// <summary>
			/// Curve is described by variables of second order.
			/// </summary>
			Quadratic = D3DDEGREE_QUADRATIC,

			/// <summary>
			/// Curve is described by variables of third order.
			/// </summary>
			Cubic = D3DDEGREE_CUBIC,

			/// <summary>
			/// Curve is described by variables of fourth order.
			/// </summary>
			Quintic = D3DDEGREE_QUINTIC,
		};

		/// <summary>Driver capability flags.</summary>
		/// <unmanaged>D3DDEVCAPS2</unmanaged>
		[System::Flags]
		public enum class DevCaps2
		{
			/// <summary>
			/// Device supports stream offsets.
			/// </summary>
			StreamOffset = D3DDEVCAPS2_STREAMOFFSET,

			/// <summary>
			/// Device supports displacement maps for N-patches.
			/// </summary>
			DMapNPatch = D3DDEVCAPS2_DMAPNPATCH,

			/// <summary>
			/// Device supports adaptive tessellation of RT-patches.
			/// </summary>
			AdaptiveTessRTPatch = D3DDEVCAPS2_ADAPTIVETESSRTPATCH,

			/// <summary>
			/// Device supports adaptive tessellation of N-patches.
			/// </summary>
			AdaptiveTessNPatch = D3DDEVCAPS2_ADAPTIVETESSNPATCH,

			/// <summary>
			/// Device supports texture stretching using a texture as the source.
			/// </summary>
			CanStretchRectFromTextures = D3DDEVCAPS2_CAN_STRETCHRECT_FROM_TEXTURES,

			/// <summary>
			/// Devices supports presampled displacement maps for N-patches.
			/// </summary>
			PresampledMapNPatch = D3DDEVCAPS2_PRESAMPLEDDMAPNPATCH,

			/// <summary>
			/// Multiple vertex elements can share the same stream offset in a stream.
			/// </summary>
			VertexElementsCanShareStreamOffset = D3DDEVCAPS2_VERTEXELEMENTSCANSHARESTREAMOFFSET,
		};

		/// <summary>
		/// Flags identifying the capabilities of the device.
		/// </summary>
		[System::Flags]
		public enum class DeviceCaps : System::Int32
		{
			/// <summary>
			/// Device can use execute buffers from system memory.
			/// </summary>
			ExecuteSystemMemory = D3DDEVCAPS_EXECUTESYSTEMMEMORY,

			/// <summary>
			/// Device can use execute buffers from video memory.
			/// </summary>
			ExecuteVideoMemory = D3DDEVCAPS_EXECUTEVIDEOMEMORY,

			/// <summary>
			/// Device can use buffers from system memory for transformed and lit vertices.
			/// </summary>
			TLVertexSystemMemory = D3DDEVCAPS_TLVERTEXSYSTEMMEMORY,

			/// <summary>
			/// Device can use buffers from video memory for transformed and lit vertices.
			/// </summary>
			TLVertexVideoMemory = D3DDEVCAPS_TLVERTEXVIDEOMEMORY,

			/// <summary>
			/// Device can retrieve textures from system memory.
			/// </summary>
			TextureSystemMemory = D3DDEVCAPS_TEXTURESYSTEMMEMORY,

			/// <summary>
			/// Device can retrieve textures from video memory.
			/// </summary>
			TextureVideoMemory = D3DDEVCAPS_TEXTUREVIDEOMEMORY,

			/// <summary>
			/// Device exports a DrawPrimitive aware HAL.
			/// </summary>
			DrawPrimTLVertex = D3DDEVCAPS_DRAWPRIMTLVERTEX,

			/// <summary>
			/// Device can queue rendering commands after a page flip.
			/// </summary>
			CanRenderAfterFlip = D3DDEVCAPS_CANRENDERAFTERFLIP,

			/// <summary>
			/// Device can retrieve textures from non-local video memory.
			/// </summary>
			TextureNonLocalVideoMemory = D3DDEVCAPS_TEXTURENONLOCALVIDMEM,

			/// <summary>
			/// Device can support at least a DirectX 5-compliant driver.
			/// </summary>
			DrawPrimitives2 = D3DDEVCAPS_DRAWPRIMITIVES2,

			/// <summary>
			/// Device is texturing from separate memory pools.
			/// </summary>
			SeparateTextureMemory = D3DDEVCAPS_SEPARATETEXTUREMEMORIES,

			/// <summary>
			/// Device can support at least a DirectX 7-compliant driver.
			/// </summary>
			DrawPrimitives2Extended = D3DDEVCAPS_DRAWPRIMITIVES2EX,

			/// <summary>
			/// Device can support hardware transformation and lighting.
			/// </summary>
			HWTransformAndLight = D3DDEVCAPS_HWTRANSFORMANDLIGHT,

			/// <summary>
			/// Device supports blits from system-memory textures to nonlocal video-memory textures.
			/// </summary>
			CanBlitSysToNonLocal = D3DDEVCAPS_CANBLTSYSTONONLOCAL,

			/// <summary>
			/// Device has hardware acceleration for scene rasterization.
			/// </summary>
			HWRasterization = D3DDEVCAPS_HWRASTERIZATION,

			/// <summary>
			/// Device can support rasterization, transform, lighting, and shading in hardware.
			/// </summary>
			PureDevice = D3DDEVCAPS_PUREDEVICE,

			/// <summary>
			/// Device supports quintic bezier curves and b-splines.
			/// </summary>
			QuinticRTPatches = D3DDEVCAPS_QUINTICRTPATCHES,

			/// <summary>
			/// Device supports rectangular and triangular patches.
			/// </summary>
			RTPatches = D3DDEVCAPS_RTPATCHES,

			/// <summary>
			/// The device does not require caching of any patch information.
			/// </summary>
			RTPatchHandleZero = D3DDEVCAPS_RTPATCHHANDLEZERO,

			/// <summary>
			/// Device supports N-patches.
			/// </summary>
			NPatches = D3DDEVCAPS_NPATCHES,
		};
		
		/// <summary>Defines device types.</summary>
		/// <unmanaged>D3DDEVTYPE</unmanaged>
		public enum class DeviceType : System::Int32
		{
			/// <summary>
			/// Hardware rasterization.
			/// </summary>
			Hardware = D3DDEVTYPE_HAL,

			/// <summary>
			/// Initialize Direct3D on a computer that has neither hardware nor reference rasterization available.
			/// </summary>
			NullReference = D3DDEVTYPE_NULLREF,

			/// <summary>
			/// Direct3D features are implemented in software.
			/// </summary>
			Reference = D3DDEVTYPE_REF,

			/// <summary>
			/// A pluggable software renderer has been registered. Not supported by SlimDX.
			/// </summary>
			Software = D3DDEVTYPE_SW
		};
		
		/// <summary>
		/// Specifies formatting options for text rendering.
		/// </summary>
		[System::Flags]
		public enum class DrawTextFormat : System::Int32
		{
			/// <summary>
			/// Align the text to the top.
			/// </summary>
			Top = DT_TOP,

			/// <summary>
			/// Align the text to the left.
			/// </summary>
			Left = DT_LEFT,

			/// <summary>
			/// Align the text to the center.
			/// </summary>
			Center = DT_CENTER,

			/// <summary>
			/// Align the text to the right.
			/// </summary>
			Right = DT_RIGHT,

			/// <summary>
			/// Vertically align the text to the center.
			/// </summary>
			VerticalCenter = DT_VCENTER,

			/// <summary>
			/// Align the text to the bottom.
			/// </summary>
			Bottom = DT_BOTTOM,

			/// <summary>
			/// Allow word breaks.
			/// </summary>
			WordBreak = DT_WORDBREAK,

			/// <summary>
			/// Force all text to a single line.
			/// </summary>
			SingleLine = DT_SINGLELINE,

			/// <summary>
			/// Expand tab characters.
			/// </summary>
			ExpandTabs = DT_EXPANDTABS,

			/// <summary>
			/// Don't clip the text.
			/// </summary>
			NoClip = DT_NOCLIP,

			/// <summary>
			/// Calculate the dimensions of the text.
			/// </summary>
			CalcRect = DT_CALCRECT,

			/// <summary>
			/// Rendering the text in right-to-left reading order.
			/// </summary>
			RtlReading = DT_RTLREADING,
		};
		
		/// <summary>
		/// Specifies possible driver levels.
		/// </summary>
		public enum class DriverLevel : System::Int32
		{
			/// <summary>
			/// The driver supports at least Direct3D7.
			/// </summary>
			Direct3D7 = 700,

			/// <summary>
			/// The driver supports at least Direct3D8.
			/// </summary>
			Direct3D8 = 800,

			/// <summary>
			/// The driver supports at least Direct3D9.
			/// </summary>
			Direct3D9 = 900,
		};

		/// <summary>
		/// Specifies how the monitor being used to display a fullscreen application is rotated.
		/// </summary>
		/// <unmanaged>D3DDISPLAYROTATION</unmanaged>
		public enum class DisplayRotation : System::Int32
		{
			/// <summary>
			/// Display is not rotated.
			/// </summary>
			Identity = D3DDISPLAYROTATION_IDENTITY,

			/// <summary>
			/// Display is rotated 90 degrees.
			/// </summary>
			Rotation90 = D3DDISPLAYROTATION_90,

			/// <summary>
			/// Display is rotated 180 degrees.
			/// </summary>
			Rotation180 = D3DDISPLAYROTATION_180,

			/// <summary>
			/// Display is rotated 270 degrees.
			/// </summary>
			Rotation270 = D3DDISPLAYROTATION_270
		};
		
		/// <summary>
		/// Defines constants describing the fill mode.
		/// </summary>
		/// <unmanaged>D3DFILLMODE</unmanaged>
		public enum class FillMode : System::Int32
		{
			/// <summary>
			/// Fill points.
			/// </summary>
			Point = D3DFILL_POINT,

			/// <summary>
			/// Fill wireframe.
			/// </summary>
			Wireframe = D3DFILL_WIREFRAME,

			/// <summary>
			/// Fill solid.
			/// </summary>
			Solid = D3DFILL_SOLID
		};

		/// <summary>
		/// Defines the filter capabilities of the device.
		/// </summary>
		/// <unmanaged>D3DPTFILTERCAPS</unmanaged>
		[System::Flags]
		public enum class FilterCaps : System::Int32
		{
			/// <summary>
			/// Device supports per-stage point-sample filtering for minifying textures.
			/// </summary>
			MinPoint = D3DPTFILTERCAPS_MINFPOINT,

			/// <summary>
			/// Device supports per-stage linear filtering for minifying textures.
			/// </summary>
			MinLinear = D3DPTFILTERCAPS_MINFLINEAR,

			/// <summary>
			/// Device supports per-stage anisotropic filtering for minifying textures.
			/// </summary>
			MinAnisotropic = D3DPTFILTERCAPS_MINFANISOTROPIC,

			/// <summary>
			/// Device supports per-stage pyramidal sample filtering for minifying textures.
			/// </summary>
			MinPyramidalQuad = D3DPTFILTERCAPS_MINFPYRAMIDALQUAD,

			/// <summary>
			/// Device supports per-stage Gaussian quad filtering for minifying textures.
			/// </summary>
			MinGaussianQuad = D3DPTFILTERCAPS_MINFGAUSSIANQUAD,

			/// <summary>
			/// Device supports per-stage point-sample filtering for mipmaps.
			/// </summary>
			MipPoint = D3DPTFILTERCAPS_MIPFPOINT,

			/// <summary>
			/// Device supports per-stage linear filtering for mipmaps.
			/// </summary>
			MipLinear = D3DPTFILTERCAPS_MIPFLINEAR,

			/// <summary>
			/// Device supports per-stage point-sample filtering for magnifying textures.
			/// </summary>
			MagPoint = D3DPTFILTERCAPS_MAGFPOINT,

			/// <summary>
			/// Device supports per-stage linaer filtering for magnifying textures.
			/// </summary>
			MagLinear = D3DPTFILTERCAPS_MAGFLINEAR,

			/// <summary>
			/// Device supports per-stage anisotropic filtering for magnifying textures.
			/// </summary>
			MagAnisotropic = D3DPTFILTERCAPS_MAGFANISOTROPIC,

			/// <summary>
			/// Device supports per-stage pyramidal sample filtering for magnifying textures.
			/// </summary>
			MagPyramidalQuad = D3DPTFILTERCAPS_MAGFPYRAMIDALQUAD,

			/// <summary>
			/// Device supports per-stage Gaussian quad filtering for magnifying textures.
			/// </summary>
			MagGaussianQuad = D3DPTFILTERCAPS_MAGFGAUSSIANQUAD,
		};

		/// <summary>
		/// Device constants that describe the fog mode.
		/// </summary>
		public enum class FogMode : System::Int32
		{
			/// <summary>
			/// No fog effect.
			/// </summary>
			None = D3DFOG_NONE,

			/// <summary>
			/// Fog effect intensifies exponentially.
			/// </summary>
			Exponential = D3DFOG_EXP,

			/// <summary>
			/// Fog effect intesifies exponentially with the square of the distance.
			/// </summary>
			ExponentialSquared = D3DFOG_EXP2,

			/// <summary>
			/// Fog effect intesifies linearly between the start and end points.
			/// </summary>
			Linear = D3DFOG_LINEAR
		};
		
		/// <summary>
		/// Specifies quality options for font rendering.
		/// </summary>
		public enum class FontQuality : System::Int32
		{
			/// <summary>
			/// Default quality levels.
			/// </summary>
			Default = DEFAULT_QUALITY,

			/// <summary>
			/// Draft quality.
			/// </summary>
			Draft = DRAFT_QUALITY,

			/// <summary>
			/// Proof quality.
			/// </summary>
			Proof = PROOF_QUALITY,

			/// <summary>
			/// Non-antialiased quality.
			/// </summary>
			NonAntialiased = NONANTIALIASED_QUALITY,

			/// <summary>
			/// Antialiased quality.
			/// </summary>
			Antialiased = ANTIALIASED_QUALITY,

			/// <summary>
			/// Clear type quality.
			/// </summary>
			ClearType = CLEARTYPE_QUALITY,

			/// <summary>
			/// Clear type natural quality.
			/// </summary>
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
		
		/// <summary>
		/// Z-buffer usage types.
		/// </summary>
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
