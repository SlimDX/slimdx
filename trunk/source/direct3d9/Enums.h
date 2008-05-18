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

		/// <summary>
		/// Specifies weights for font rendering.
		/// </summary>
		public enum class FontWeight : System::Int32
		{
			/// <summary>
			/// The font weight doesn't matter.
			/// </summary>
			DoNotCare = FW_DONTCARE,

			/// <summary>
			/// Make the font thin.
			/// </summary>
			Thin = FW_THIN,

			/// <summary>
			/// Make the font extra light.
			/// </summary>
			ExtraLight = FW_EXTRALIGHT,

			/// <summary>
			/// Make the font ultra light.
			/// </summary>
			UltraLight = FW_ULTRALIGHT,

			/// <summary>
			/// Make the font light.
			/// </summary>
			Light = FW_LIGHT,

			/// <summary>
			/// Use a normal weight.
			/// </summary>
			Normal = FW_NORMAL,

			/// <summary>
			/// Use a regular weight.
			/// </summary>
			Regular = FW_REGULAR,

			/// <summary>
			/// Use a medium weight.
			/// </summary>
			Medium = FW_MEDIUM,

			/// <summary>
			/// Use a semi-bold weight.
			/// </summary>
			SemiBold = FW_SEMIBOLD,

			/// <summary>
			/// Use a demi-bold weight.
			/// </summary>
			DemiBold = FW_DEMIBOLD,

			/// <summary>
			/// Use a bold weight.
			/// </summary>
			Bold = FW_BOLD,

			/// <summary>
			/// Use an extra bold weight.
			/// </summary>
			ExtraBold = FW_EXTRABOLD,

			/// <summary>
			/// Use an ultra bold weight.
			/// </summary>
			UltraBold = FW_ULTRABOLD,

			/// <summary>
			/// Use a heavy weight.
			/// </summary>
			Heavy = FW_HEAVY,

			/// <summary>
			/// Use a black weight.
			/// </summary>
			Black = FW_BLACK,
		};

		/// <summary>
		/// Defines the various types of surface formats.
		/// </summary>
		/// <unmanaged>D3DFORMAT</unmanaged>
		public enum class Format : System::Int32
		{
			/// <summary>
			/// 32-bit surface format using 2 bits for alpha and 10 bits for color components (red, green, blue).
			/// </summary>
			A2R10G10B10 = D3DFMT_A2R10G10B10,

			/// <summary>
			/// 32-bit surface format using 8 bits for each channel (alpha, red, green, blue). 
			/// </summary>
			A8R8G8B8 = D3DFMT_A8R8G8B8,

			/// <summary>
			/// 32-bit surface format using 8 bits for each color component (red, green, blue).
			/// </summary>
			X8R8G8B8 = D3DFMT_X8R8G8B8,

			/// <summary>
			/// 16-bit surface format using 1 bit for alpha and 5 bits for each channel (red, green, blue).
			/// </summary>
			A1R5G5B5 = D3DFMT_A1R5G5B5,

			/// <summary>
			/// 16-bit surface format using 5 bits for each color component (red, green, blue).
			/// </summary>
			X1R5G5B5 = D3DFMT_X1R5G5B5,

			/// <summary>
			/// 16-bit surface format using 5 bits for red and blue and 6 bits for green.
			/// </summary>
			R5G6B5 = D3DFMT_R5G6B5,

			/***/

			/// <summary>
			/// 16-bit z-buffer lockable format with 16 bits for depth.
			/// </summary>
			D16Lockable = D3DFMT_D16_LOCKABLE,

			/// <summary>
			/// 32-bit z-buffer format with 32 bits for depth.
			/// </summary>
			D32 = D3DFMT_D32,

			/// <summary>
			/// 16-bit z-buffer format with 15 bits for depth and 1 bit for stencil.
			/// </summary>
			D15S1 = D3DFMT_D15S1,

			/// <summary>
			/// 32-bit z-buffer format with 24 bits for depth and 8 bits for stencil.
			/// </summary>
			D24S8 = D3DFMT_D24S8,

			/// <summary>
			/// 32-bit z-buffer format with 24 bits for depth.
			/// </summary>
			D24X8 = D3DFMT_D24X8,

			/// <summary>
			/// 32-bit z-buffer format with 24 bits for depth and 4 bits for stencil.
			/// </summary>
			D24X4S4 = D3DFMT_D24X4S4,

			/// <summary>
			/// 32-bit z-buffer lockable format with 32 bits for depth (in standard IEEE floating point format).
			/// </summary>
			D32SingleLockable = D3DFMT_D32F_LOCKABLE,

			/// <summary>
			/// 32-bit z-buffer format with 24 bits for depth (in 24-bit floating point format) and 8 bits for stencil.
			/// </summary>
			D24SingleS8 = D3DFMT_D24FS8,

			/// <summary>
			/// Lockable 32-bit depth buffer. Available for Direct3D9Ex only.
			/// </summary>
			D32Lockable = D3DFMT_D32_LOCKABLE,

			/// <summary>
			/// Lockable 8-bit stencil buffer. Available for Direct3D9Ex only.
			/// </summary>
			S8Lockable = D3DFMT_S8_LOCKABLE,

			/// <summary>
			/// 16-bit z-buffer format with 16 bits for depth.
			/// </summary>
			D16 = D3DFMT_D16,

			/***/

			/// <summary>
			/// Describes a vertex buffer surface.
			/// </summary>
			VertexData = D3DFMT_VERTEXDATA,

			/// <summary>
			/// 16-bit index buffer bit depth.
			/// </summary>
			Index16 = D3DFMT_INDEX16,

			/// <summary>
			/// 32-bit index buffer bit depth.
			/// </summary>
			Index32 = D3DFMT_INDEX32,

			/***/		

			/// <summary>
			/// DXT1 compression texture format.
			/// </summary>
			Dxt1 = D3DFMT_DXT1,

			/// <summary>
			/// DXT2 compression texture format.
			/// </summary>
			Dxt2 = D3DFMT_DXT2,

			/// <summary>
			/// DXT3 compression texture format.
			/// </summary>
			Dxt3 = D3DFMT_DXT3,

			/// <summary>
			/// DXT4 compression texture format.
			/// </summary>
			Dxt4 = D3DFMT_DXT4,

			/// <summary>
			/// DXT5 compression texture format.
			/// </summary>
			Dxt5 = D3DFMT_DXT5,

			/***/

			/// <summary>
			/// 16-bit floating point format using 16 bits for the red channel.
			/// </summary>
			R16F = D3DFMT_R16F,

			/// <summary>
			/// 32-bit floating point format using 16 bits for the red channel and 16 bits for the green channel.
			/// </summary>
			G16R16F = D3DFMT_G16R16F,

			/// <summary>
			/// 64-bit floating point format using 16 bits for each channel (alpha, blue, green, red).
			/// </summary>
			A16B16G16R16F = D3DFMT_A16B16G16R16F,

			/***/

			/// <summary>
			/// Multielement texture.
			/// </summary>
			Multi2Argb8 = D3DFMT_MULTI2_ARGB8,

			/// <summary>
			/// 16-bit packed RGB format consisting of pixel pairs to express color.
			/// </summary>
			G8R8_G8B8 = D3DFMT_G8R8_G8B8,

			/// <summary>
			/// 16-bit packed RGB format consisting of pixel pairs to express color.
			/// </summary>
			R8G8_B8G8 = D3DFMT_R8G8_B8G8,

			/// <summary>
			/// UYUV format (PC98 compliance).
			/// </summary>
			Uyvy = D3DFMT_UYVY,

			/// <summary>
			/// YUY2 format (PC98 compliance).
			/// </summary>
			Yuy2 = D3DFMT_YUY2,

			/***/

			/// <summary>
			/// 32-bit floating point format using 32 bits for the red channel.
			/// </summary>
			R32F = D3DFMT_R32F,

			/// <summary>
			/// 64-bit floating point format using 32 bits for the red channel and 32 bits for the green channel.
			/// </summary>
			G32R32F = D3DFMT_G32R32F,

			/// <summary>
			/// 128-bit floating point format using 32 bits for each channel (alpha, blue, green, red).
			/// </summary>
			A32B32G32R32F = D3DFMT_A32B32G32R32F,

			/***/

			/// <summary>
			/// 16-bit bump map format using 6 bits for luminance and 5 bits each for V and U.
			/// </summary>
			L6V5U5 = D3DFMT_L6V5U5,

			/// <summary>
			/// 32-bit bump map format using 8 bits for each channel (luminance, V, U).
			/// </summary>
			X8L8V8U8 = D3DFMT_X8L8V8U8,

			/// <summary>
			/// 32-bit bump map format using 2 bits for alpha and 10 bits each for W, V, and U.
			/// </summary>
			A2W10V10U10 = D3DFMT_A2W10V10U10,

			/***/

			/// <summary>
			/// 16-bit bump map format using 8 bits each for U and V.
			/// </summary>
			V8U8 = D3DFMT_V8U8,

			/// <summary>
			/// 32-bit bump map format using 8 bits for each channel (Q, W, V, U).
			/// </summary>
			Q8W8V8U8 = D3DFMT_Q8W8V8U8,

			/// <summary>
			/// 32-bit bump map format using 16 bits each for V and U.
			/// </summary>
			V16U16 = D3DFMT_V16U16,

			/// <summary>
			/// 64-bit bump map format using 16 bits for each channel (Q, W, V, U).
			/// </summary>
			Q16W16V16U16 = D3DFMT_Q16W16V16U16,

			/// <summary>
			/// 16-bit normal compression format.
			/// </summary>
			CxV8U8 = D3DFMT_CxV8U8,

			/***/

			/// <summary>
			/// 24-bit RGB format using 8 bits per channel.
			/// </summary>
			R8G8B8 = D3DFMT_R8G8B8,

			/// <summary>
			/// 16-bit ARGB format using 4 bits for each channel.
			/// </summary>
			A4R4G4B4 = D3DFMT_A4R4G4B4,

			/// <summary>
			/// 8-bit RGB format using 3 bits for red and green and 2 bits for blue.
			/// </summary>
			R3G3B2 = D3DFMT_R3G3B2,

			/// <summary>
			/// 8-bit alpha format.
			/// </summary>
			A8 = D3DFMT_A8,

			/// <summary>
			/// 16-bit ARGB format using 8 bits for alpha, 3 bits for red and green, and 2 bits for blue.
			/// </summary>
			A8R3G3B2 = D3DFMT_A8R3G3B2,

			/// <summary>
			/// 16-bit RGB format using 4 bits for each color channel.
			/// </summary>
			X4R4G4B4 = D3DFMT_X4R4G4B4,

			/// <summary>
			/// 32-bit ABGR format using 2 bits for alpha and 10 bits for each color component.
			/// </summary>
			A2B10G10R10 = D3DFMT_A2B10G10R10,

			/// <summary>
			/// 32-bit ABGR format using 8 bits for each channel.
			/// </summary>
			A8B8G8R8 = D3DFMT_A8B8G8R8,

			/// <summary>
			/// 32-bit BGR format using 8 bits for each color channel.
			/// </summary>
			X8B8G8R8 = D3DFMT_X8B8G8R8,

			/// <summary>
			/// 32-bit pixel format using 16 bits each for green and red.
			/// </summary>
			G16R16 = D3DFMT_G16R16,

			/// <summary>
			/// 64-bit pixel ABGR format using 16 bits for each channel.
			/// </summary>
			A16B16G16R16 = D3DFMT_A16B16G16R16,

			/// <summary>
			/// 8-bit color indexed with 8 bits of alpha.
			/// </summary>
			A8P8 = D3DFMT_A8P8,

			/// <summary>
			/// 8-bit color indexed.
			/// </summary>
			P8 = D3DFMT_P8,

			/// <summary>
			/// 16-bit luminance.
			/// </summary>
			L16 = D3DFMT_L16,

			/// <summary>
			/// 8-bit luminance.
			/// </summary>
			L8 = D3DFMT_L8,

			/// <summary>
			/// 16-bit format using 8 bits each for alpha and luminance.
			/// </summary>
			A8L8 = D3DFMT_A8L8,

			/// <summary>
			/// 8-bit format using 4 bits each for alpha and luminance.
			/// </summary>
			A4L4 = D3DFMT_A4L4,

			/// <summary>
			/// 1-bit monochrome format. Available for Direct3D9Ex only.
			/// </summary>
			A1 = D3DFMT_A1,

			/// <summary>
			/// Binary buffer format indicating that the data has no inherent type. Available for Direct3D9Ex only.
			/// </summary>
			BinaryBuffer = D3DFMT_BINARYBUFFER,

			/***/

			/// <summary>
			/// Surface format for Render-To-Vertex-Buffer (R2VB).
			/// </summary>
			ATI_R2VB = R2VB_FOURCC_R2VB,

			/***/

			/// <summary>
			/// Unknown surface format.
			/// </summary>
			Unknown = D3DFMT_UNKNOWN,
		};

		/// <summary>
		/// Defines constants for query issues.
		/// </summary>
		[System::Flags]
		public enum class Issue
		{
			/// <summary>
			/// Start a query issue.
			/// </summary>
			Begin = D3DISSUE_BEGIN,

			/// <summary>
			/// End a query issue.
			/// </summary>
			End = D3DISSUE_END
		};
		
		/// <summary>
		/// Defines possible light types.
		/// </summary>
		/// <unmanaged>D3DLIGHTTYPE</unmanaged>
		public enum class LightType : System::Int32
		{
			/// <summary>
			/// Light is a point source. The light has a position in space and radiates in all directions.
			/// </summary>
			Point = D3DLIGHT_POINT,

			/// <summary>
			/// Light is a spotlight source. Illumination is limited to a cone.
			/// </summary>
			Spot = D3DLIGHT_SPOT,

			/// <summary>
			/// Light is a directional light source. This is equivalent to using a point light source at an infinite distance.
			/// </summary>
			Directional = D3DLIGHT_DIRECTIONAL,
		};

		/// <summary>
		/// Specifies the line drawing capabilities of a device.
		/// </summary>
		[System::Flags]
		public enum class LineCaps : System::Int32
		{
			/// <summary>
			/// Supports texture-mapping.
			/// </summary>
			Texture = D3DLINECAPS_TEXTURE,

			/// <summary>
			/// Supports depth test.
			/// </summary>
			DepthTest = D3DLINECAPS_ZTEST,

			/// <summary>
			/// Supports source-blending.
			/// </summary>
			Blend = D3DLINECAPS_BLEND,

			/// <summary>
			/// Supports alpha test comparisons.
			/// </summary>
			AlphaCompare = D3DLINECAPS_ALPHACMP,

			/// <summary>
			/// Supports fog.
			/// </summary>
			Fog = D3DLINECAPS_FOG,

			/// <summary>
			/// Supports antialiasing.
			/// </summary>
			Antialias = D3DLINECAPS_ANTIALIAS,
		};
		
		/// <summary>
		/// Defines flags for buffer locking.
		/// </summary>
		/// <unmanaged>D3DLOCK</unmanaged>
		[System::Flags]
		public enum class LockFlags : System::Int32
		{
			/// <summary>
			/// The application discards all memory within the locked region.
			/// </summary>
			Discard = D3DLOCK_DISCARD,

			/// <summary>
			/// Allows the application to gain back CPU cycles if the driver cannot lock the surface immediately.
			/// </summary>
			DoNotWait = D3DLOCK_DONOTWAIT,

			/// <summary>
			/// Prevents any changes to the dirty state of the resource.
			/// </summary>
			NoDirtyUpdate = D3DLOCK_NO_DIRTY_UPDATE,

			/// <summary>
			/// No locking flags specified.
			/// </summary>
			None = 0,

			/// <summary>
			/// Indicates that the last set of data written will not be modified during this lock call.
			/// </summary>
			NoOverwrite = D3DLOCK_NOOVERWRITE,

			/// <summary>
			/// Prevents the allocation of a system wide resource lock.
			/// </summary>
			NoSystemLock = D3DLOCK_NOSYSLOCK,

			/// <summary>
			/// The application will not write to the buffer.
			/// </summary>
			ReadOnly = D3DLOCK_READONLY,

			// this just exists for ProcessVertices
			DoNotCopyData = D3DPV_DONOTCOPYDATA,
		};
		
		/// <summary>
		/// Defines the levels of full-scene multisampling that the device can apply.
		/// </summary>
		/// <unmanaged>D3DMULTISAMPLE_TYPE</unmanaged>
		public enum class MultisampleType : System::Int32
		{
			/// <summary>
			/// No level of multisampling is available.
			/// </summary>
			None = D3DMULTISAMPLE_NONE,

			/// <summary>
			/// Enables the multisampling quality value.
			/// </summary>
			NonMaskable = D3DMULTISAMPLE_NONMASKABLE,

			/// <summary>
			/// Level of full-scene multisampling using 2 samples.
			/// </summary>
			TwoSamples = D3DMULTISAMPLE_2_SAMPLES,

			/// <summary>
			/// Level of full-scene multisampling using 3 samples.
			/// </summary>
			ThreeSamples = D3DMULTISAMPLE_3_SAMPLES,

			/// <summary>
			/// Level of full-scene multisampling using 4 samples.
			/// </summary>
			FourSamples = D3DMULTISAMPLE_4_SAMPLES,

			/// <summary>
			/// Level of full-scene multisampling using 5 samples.
			/// </summary>
			FiveSamples = D3DMULTISAMPLE_5_SAMPLES,

			/// <summary>
			/// Level of full-scene multisampling using 6 samples.
			/// </summary>
			SixSamples = D3DMULTISAMPLE_6_SAMPLES,

			/// <summary>
			/// Level of full-scene multisampling using 7 samples.
			/// </summary>
			SevenSamples = D3DMULTISAMPLE_7_SAMPLES,

			/// <summary>
			/// Level of full-scene multisampling using 8 samples.
			/// </summary>
			EightSamples = D3DMULTISAMPLE_8_SAMPLES,

			/// <summary>
			/// Level of full-scene multisampling using 9 samples.
			/// </summary>
			NineSamples = D3DMULTISAMPLE_9_SAMPLES,

			/// <summary>
			/// Level of full-scene multisampling using 10 samples.
			/// </summary>
			TenSamples = D3DMULTISAMPLE_10_SAMPLES,

			/// <summary>
			/// Level of full-scene multisampling using 11 samples.
			/// </summary>
			ElevenSamples = D3DMULTISAMPLE_11_SAMPLES,

			/// <summary>
			/// Level of full-scene multisampling using 12 samples.
			/// </summary>
			TwelveSamples = D3DMULTISAMPLE_12_SAMPLES,

			/// <summary>
			/// Level of full-scene multisampling using 13 samples.
			/// </summary>
			ThirteenSamples = D3DMULTISAMPLE_13_SAMPLES,

			/// <summary>
			/// Level of full-scene multisampling using 14 samples.
			/// </summary>
			FourteenSamples = D3DMULTISAMPLE_14_SAMPLES,

			/// <summary>
			/// Level of full-scene multisampling using 15 samples.
			/// </summary>
			FifteenSamples = D3DMULTISAMPLE_15_SAMPLES,

			/// <summary>
			/// Level of full-scene multisampling using 16 samples.
			/// </summary>
			SixteenSamples = D3DMULTISAMPLE_16_SAMPLES
		};

		/// <summary>
		/// Defines whether the current tessellation mode is discrete or continuous.
		/// </summary>
		/// <unmanaged>D3DPATCHEDGESTYLE</unmanaged>
		public enum class PatchEdgeStyle : System::Int32
		{
			/// <summary>
			/// Discrete edge style.
			/// </summary>
			Discrete = D3DPATCHEDGE_DISCRETE,

			/// <summary>
			/// Continuous edge style.
			/// </summary>
			Continuous = D3DPATCHEDGE_CONTINUOUS
		};
		
		/// <summary>
		/// Defines pitch and family settings for fonts.
		/// </summary>
		[System::Flags]
		public enum class PitchAndFamily : System::Int32
		{
			/// <summary>
			/// Default pitch.
			/// </summary>
			Default = DEFAULT_PITCH,

			/// <summary>
			/// Fixed pitch.
			/// </summary>
			Fixed = FIXED_PITCH,

			/// <summary>
			/// Variable pitch.
			/// </summary>
			Variable = VARIABLE_PITCH,

			/// <summary>
			/// Mono pitch.
			/// </summary>
			Mono = MONO_FONT,

			/// <summary>
			/// The font family doesn't matter.
			/// </summary>
			DontCare = FF_DONTCARE,

			/// <summary>
			/// Use the Roman family.
			/// </summary>
			Roman = FF_ROMAN,

			/// <summary>
			/// Use the Swiss family.
			/// </summary>
			Swiss = FF_SWISS,

			/// <summary>
			/// Use the Modern family.
			/// </summary>
			Modern = FF_MODERN,

			/// <summary>
			/// Use the Script family.
			/// </summary>
			Script = FF_SCRIPT,

			/// <summary>
			/// Use the Decorative family.
			/// </summary>
			Decorative = FF_DECORATIVE,
		};
		
		/// <summary>
		/// Defines the memory class that holds the buffers for a resource.
		/// </summary>
		/// <unmanaged>D3DPOOL</unmanaged>
		public enum class Pool : System::Int32
		{
			/// <summary>
			/// Resources are placed in the memory pool most appropriate for the set of usages requested for the resource.
			/// </summary>
			Default = D3DPOOL_DEFAULT,

			/// <summary>
			/// Resources are copied automatically to device-accessable memory as needed. Managed resources are
			/// backed by system memory and do not need to be recreated when the device is lost.
			/// </summary>
			Managed = D3DPOOL_MANAGED,

			/// <summary>
			/// Resources are placed in system memory that is not accessable by the device. These resources
			/// do not need to be recreated when the device is lost.
			/// </summary>
			SystemMemory = D3DPOOL_SYSTEMMEM,

			/// <summary>
			/// Resources are placed in scratch memory. These resources cannot be used as textures or render
			/// targets.
			/// </summary>
			Scratch = D3DPOOL_SCRATCH,
		};

		/// <summary>
		/// Defines precision levels for font rendering.
		/// </summary>
		public enum class Precision : System::Int32
		{
			/// <summary>
			/// Default precision.
			/// </summary>
			Default = OUT_DEFAULT_PRECIS,

			/// <summary>
			/// String-level precision.
			/// </summary>
			String = OUT_STRING_PRECIS,

			/// <summary>
			/// Character-level precision.
			/// </summary>
			Character = OUT_CHARACTER_PRECIS,

			/// <summary>
			/// Stroke-level precision.
			/// </summary>
			Stroke = OUT_STROKE_PRECIS,

			/// <summary>
			/// TrueType precision.
			/// </summary>
			TrueType = OUT_TT_PRECIS,

			/// <summary>
			/// Device precision.
			/// </summary>
			Device = OUT_DEVICE_PRECIS,

			/// <summary>
			/// Raster precision.
			/// </summary>
			Raster = OUT_RASTER_PRECIS,

			/// <summary>
			/// TrueType only precision.
			/// </summary>
			TrueTypeOnly = OUT_TT_ONLY_PRECIS,

			/// <summary>
			/// Outline precision.
			/// </summary>
			Outline = OUT_OUTLINE_PRECIS,

			/// <summary>
			/// Screen outline precision.
			/// </summary>
			ScreenOutline = OUT_SCREEN_OUTLINE_PRECIS,

			/// <summary>
			/// PostScript only precision.
			/// </summary>
			PostScriptOnly = OUT_PS_ONLY_PRECIS,
		};
		
		/// <summary>
		/// Defines flags for presentation calls.
		/// </summary>
		/// <unmanaged>D3DPRESENT</unmanaged>
		[System::Flags]
		public enum class Present : System::Int32
		{
			/// <summary>
			/// No extra presentation flags.
			/// </summary>
			None = 0,

			/// <summary>
			/// Use the front buffer as both the source and the target surface during rendering.
			/// Available for Direct3D9Ex only.
			/// </summary>
			DoNotFlip = D3DPRESENT_DONOTFLIP,

			/// <summary>
			/// Specifies that the application should not wait for rendering to finish.
			/// </summary>
			DoNotWait = D3DPRESENT_DONOTWAIT,

			/// <summary>
			/// The application will discard all previously queued frames and present the current frame next.
			/// Available in Direct3D9Ex only.
			/// </summary>
			FlipRestart = D3DPRESENT_FLIPRESTART,

			/// <summary>
			/// Clips the rendered content to the monitor/device that the adapter is targetting. Available in
			/// Direct3D9Ex only.
			/// </summary>
			VideoRestrictToMonitor = D3DPRESENT_VIDEO_RESTRICT_TO_MONITOR,

			/// <summary>
			/// The content of the backbuffer to be presented is in linear color space.
			/// </summary>
			LinearContent = D3DPRESENT_LINEAR_CONTENT
		};
		
		/// <summary>
		/// Specifies possible presentation flags.
		/// </summary>
		/// <unmanaged>D3DPRESENTFLAG</unmanaged>
		[System::Flags]
		public enum class PresentFlags : System::Int32
		{
			/// <summary>
			/// Clips the presentation to the device.
			/// </summary>
			DeviceClip = D3DPRESENTFLAG_DEVICECLIP,

			/// <summary>
			/// Discards the contents of the depth/stencil surface after each presentation.
			/// </summary>
			DiscardDepthStencil = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL,

			/// <summary>
			/// Set when the application requires the ability to lock the back buffer.
			/// </summary>
			LockableBackBuffer = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER,

			/// <summary>
			/// No extra presentation flags specified.
			/// </summary>
			None = 0,

			/// <summary>
			/// Specifies that the application will perform its own display rotation. Available in Direct3D9Ex only.
			/// </summary>
			NoAutoRotate = D3DPRESENTFLAG_NOAUTOROTATE,

			/// <summary>
			/// Allows the device to use invalid display modes as if they were valid. Available in Direct3D9Ex only.
			/// </summary>
			UnprunedMode = D3DPRESENTFLAG_UNPRUNEDMODE,

			/// <summary>
			/// This is a hint to the driver that the back buffers will contain video data.
			/// </summary>
			Video = D3DPRESENTFLAG_VIDEO
		};

		/// <summary>
		/// Specifies presentation intervals.
		/// </summary>
		/// <unmanaged>D3DPRESENT</unmanaged>
		[System::Flags]
		public enum class PresentInterval : System::Int32
		{
			/// <summary>
			/// The device will wait for the vertical retrace period.
			/// </summary>
			Default = D3DPRESENT_INTERVAL_DEFAULT,

			/// <summary>
			/// The device will present immediately without waiting for the refresh.
			/// </summary>
			Immediate = (int) D3DPRESENT_INTERVAL_IMMEDIATE,

			/// <summary>
			/// The device will wait for the vertical retrace period.
			/// </summary>
			One = D3DPRESENT_INTERVAL_ONE,

			/// <summary>
			/// Present operations will not be affected more than twice every screen refresh.
			/// </summary>
			Two = D3DPRESENT_INTERVAL_TWO,

			/// <summary>
			/// Present operations will not be affected more than three times every screen refresh.
			/// </summary>
			Three = D3DPRESENT_INTERVAL_THREE,

			/// <summary>
			/// Present operations will not be affected more than four times every screen refresh.
			/// </summary>
			Four = D3DPRESENT_INTERVAL_FOUR,
		};

		/// <summary>
		/// Specifies miscellaneous capabilities for primitive rendering supported by the device.
		/// </summary>
		/// <unmanaged>D3DPMISCCAPS</unmanaged>
		[System::Flags]
		public enum class PrimitiveMiscCaps : System::Int32
		{
			/// <summary>
			/// Device can enabled and disable modification of the depth buffer on pixel operations.
			/// </summary>
			MaskZ = D3DPMISCCAPS_MASKZ,

			/// <summary>
			/// The driver does not perform triangle culling.
			/// </summary>
			CullNone = D3DPMISCCAPS_CULLNONE,

			/// <summary>
			/// The driver supports clockwise culling.
			/// </summary>
			CullCW = D3DPMISCCAPS_CULLCW,

			/// <summary>
			/// The driver supports counterclockwise culling.
			/// </summary>
			CullCCW = D3DPMISCCAPS_CULLCCW,

			/// <summary>
			/// Device supports per-channel writes of the color buffer.
			/// </summary>
			ColorWriteEnable = D3DPMISCCAPS_COLORWRITEENABLE,

			/// <summary>
			/// Device correctly clips scaled points of size greater than 1.0.
			/// </summary>
			ClipPlanesScaledPoints = D3DPMISCCAPS_CLIPPLANESCALEDPOINTS,

			/// <summary>
			/// Device clips post-transformed vertex primitives.
			/// </summary>
			ClipTLVertices = D3DPMISCCAPS_CLIPTLVERTS,

			/// <summary>
			/// Device supports temporary texture arguments.
			/// </summary>
			TssArgTemp = D3DPMISCCAPS_TSSARGTEMP,

			/// <summary>
			/// Device supports alpha blending operations.
			/// </summary>
			BlendOperation = D3DPMISCCAPS_BLENDOP,

			/// <summary>
			/// A reference device that does not render.
			/// </summary>
			NullReference = D3DPMISCCAPS_NULLREFERENCE,

			/// <summary>
			/// Device supports independent write masks for multiple render targets.
			/// </summary>
			IndependentWriteMasks = D3DPMISCCAPS_INDEPENDENTWRITEMASKS,

			/// <summary>
			/// Device supports per-stage constants.
			/// </summary>
			PerStageConstant = D3DPMISCCAPS_PERSTAGECONSTANT,

			/// <summary>
			/// Device supports conversion to sRGB after blending. Available for Direct3D9Ex only.
			/// </summary>
			PostBlendSrgbConvert = D3DPMISCCAPS_POSTBLENDSRGBCONVERT,

			/// <summary>
			/// Device supports fog and specular alpha.
			/// </summary>
			FogAndSpecularAlpha = D3DPMISCCAPS_FOGANDSPECULARALPHA,

			/// <summary>
			/// Device supports separate blend settings for the alpha channel.
			/// </summary>
			SeparateAlphaBlend = D3DPMISCCAPS_SEPARATEALPHABLEND,

			/// <summary>
			/// Device supports different bit depths for multiple render targets.
			/// </summary>
			MrtIndependentBitDepths = D3DPMISCCAPS_MRTINDEPENDENTBITDEPTHS,

			/// <summary>
			/// Device supports post pixel shader operations for multiple render targets.
			/// </summary>
			MrtPostPixelShaderBlending = D3DPMISCCAPS_MRTPOSTPIXELSHADERBLENDING,

			/// <summary>
			/// Device clamps fog blend factor per vertex.
			/// </summary>
			FogVertexClamped = D3DPMISCCAPS_FOGVERTEXCLAMPED
		};
		
		/// <summary>
		/// Defines the primitives supported by Direct3D.
		/// </summary>
		/// <unmanaged>D3DPRIMITIVETYPE</unmanaged>
		public enum class PrimitiveType : System::Int32
		{
			/// <summary>
			/// Renders the vertices as a collection of isolated points.
			/// </summary>
			PointList = D3DPT_POINTLIST,

			/// <summary>
			/// Renders the vertices as a list of isolated line segments.
			/// </summary>
			LineList = D3DPT_LINELIST,

			/// <summary>
			/// Renders the vertices as a single polyline.
			/// </summary>
			LineStrip = D3DPT_LINESTRIP,

			/// <summary>
			/// Renders the vertices as a sequence of isolated triangles.
			/// </summary>
			TriangleList = D3DPT_TRIANGLELIST,

			/// <summary>
			/// Renders the vertices as a triangle strip.
			/// </summary>
			TriangleStrip = D3DPT_TRIANGLESTRIP,

			/// <summary>
			/// Renders the vertices as a triangle fan.
			/// </summary>
			TriangleFan = D3DPT_TRIANGLEFAN
		};

		/// <summary>
		/// Identifies possible query types.
		/// </summary>
		/// <unmanaged>D3DQUERYTYPE</unmanaged>
		public enum class QueryType : System::Int32
		{
			/// <summary>
			/// Query for driver hints about data layout for vertex caching.
			/// </summary>
			VCache = D3DQUERYTYPE_VCACHE,

			/// <summary>
			/// Query the resource manager.
			/// </summary>
			ResourceManager = D3DQUERYTYPE_RESOURCEMANAGER,

			/// <summary>
			/// Query vertex statistics.
			/// </summary>
			VertexStats = D3DQUERYTYPE_VERTEXSTATS,

			/// <summary>
			/// Query for any and all asynchronous events that have been issued from API calls.
			/// </summary>
			Event = D3DQUERYTYPE_EVENT,

			/// <summary>
			/// Query for occluded pixels.
			/// </summary>
			Occlusion = D3DQUERYTYPE_OCCLUSION,

			/// <summary>
			/// Queryies the 64-bit timestamp.
			/// </summary>
			Timestamp = D3DQUERYTYPE_TIMESTAMP,

			/// <summary>
			/// Notifies the application that the timestamp frequency has changed.
			/// </summary>
			TimestampDisjoint = D3DQUERYTYPE_TIMESTAMPDISJOINT,

			/// <summary>
			/// Queries the device to see if timestamp frequencies can change mid-call.
			/// </summary>
			TimestampFreq = D3DQUERYTYPE_TIMESTAMPFREQ,

			/// <summary>
			/// Query for pipeline timings.
			/// </summary>
			PipelineTimings = D3DQUERYTYPE_PIPELINETIMINGS,

			/// <summary>
			/// Query for interface timings.
			/// </summary>
			InterfaceTimings = D3DQUERYTYPE_INTERFACETIMINGS,

			/// <summary>
			/// Query for vertex shader timings.
			/// </summary>
			VertexTimings = D3DQUERYTYPE_VERTEXTIMINGS,

			/// <summary>
			/// Query for pixel shader timings.
			/// </summary>
			PixelTimings = D3DQUERYTYPE_PIXELTIMINGS,

			/// <summary>
			/// Query for bandwidth timings.
			/// </summary>
			BandwidthTimings = D3DQUERYTYPE_BANDWIDTHTIMINGS,

			/// <summary>
			/// Measure the cache hit-rate performance for textures and indexed vertices.
			/// </summary>
			CacheUtilization = D3DQUERYTYPE_CACHEUTILIZATION,
		};

		/// <summary>
		/// Specifies sampler values for Render-To-Vertex-Buffer (R2VB).
		/// </summary>
		public enum class R2VBSampler : System::Int32
		{
			/// <summary>
			/// Override the stream with displacement map sampler.
			/// </summary>
			OverrideDMap = R2VB_VSMP_OVR_DMAP,

			/// <summary>
			/// Override the stream with vertex texture 0 sampler.
			/// </summary>
			OverrideVtx0 = R2VB_VSMP_OVR_VTX0,

			/// <summary>
			/// Override the stream with vertex texture 1 sampler.
			/// </summary>
			OverrideVtx1 = R2VB_VSMP_OVR_VTX1,

			/// <summary>
			/// Override the stream with vertex texture 2 sampler.
			/// </summary>
			OverrideVtx2 = R2VB_VSMP_OVR_VTX2,

			/// <summary>
			/// Override the stream with vertex texture 3 sampler.
			/// </summary>
			OverrideVtx3 = R2VB_VSMP_OVR_VTX3,

			/// <summary>
			/// Number of available texture samplers.
			/// </summary>
			Count = R2VB_VSMP_NUM,
		};

		/// <summary>
		/// Specifies information about raster capabilities of the device.
		/// </summary>
		[System::Flags]
		public enum class RasterCaps : System::Int32
		{
			/// <summary>
			/// Device can dither to improve color resolution.
			/// </summary>
			Dither = D3DPRASTERCAPS_DITHER,

			/// <summary>
			/// Device can perform Z-test operations.
			/// </summary>
			DepthTest = D3DPRASTERCAPS_ZTEST,

			/// <summary>
			/// Device calculates the fog value during the lighting operation and interpolates the value during rasterization.
			/// </summary>
			FogVertex = D3DPRASTERCAPS_FOGVERTEX,

			/// <summary>
			/// Device calculates the fog value by referring to a lookup table.
			/// </summary>
			FogTable = D3DPRASTERCAPS_FOGTABLE,

			/// <summary>
			/// Device supports level-of-detail bias adjustments.
			/// </summary>
			MipMapLodBias = D3DPRASTERCAPS_MIPMAPLODBIAS,

			/// <summary>
			/// Device can perform hidden surface removal (HSR) without requiring the application to
			/// sort polygons and without requiring the allocation of a depth buffer.
			/// </summary>
			ZBufferLessHsr = D3DPRASTERCAPS_ZBUFFERLESSHSR,

			/// <summary>
			/// Device supports range-based fog.
			/// </summary>
			FogRange = D3DPRASTERCAPS_FOGRANGE,

			/// <summary>
			/// Device supports anisotropic filtering.
			/// </summary>
			Anisotropy = D3DPRASTERCAPS_ANISOTROPY,

			/// <summary>
			/// Device supports depth buffering using w.
			/// </summary>
			WBuffer = D3DPRASTERCAPS_WBUFFER,

			/// <summary>
			/// Device supports w-based fog.
			/// </summary>
			WFog = D3DPRASTERCAPS_WFOG,

			/// <summary>
			/// Device supports z-based fog.
			/// </summary>
			ZFog = D3DPRASTERCAPS_ZFOG,

			/// <summary>
			/// Device iterates colors perspective correctly.
			/// </summary>
			ColorPerspective = D3DPRASTERCAPS_COLORPERSPECTIVE,

			/// <summary>
			/// Device supports scissor testing.
			/// </summary>
			ScissorTest = D3DPRASTERCAPS_SCISSORTEST,

			/// <summary>
			/// Device performs true slope-scale depth bias.
			/// </summary>
			SlopeScaleDepthBias = D3DPRASTERCAPS_SLOPESCALEDEPTHBIAS,

			/// <summary>
			/// Device supports legacy depth bias.
			/// </summary>
			DepthBias = D3DPRASTERCAPS_DEPTHBIAS,

			/// <summary>
			/// Device supports toggling multisampling on and off.
			/// </summary>
			MultisampleToggle = D3DPRASTERCAPS_MULTISAMPLE_TOGGLE,
		};
		
		/// <summary>
		/// Render states define set-up states for all kinds of vertex and pixel processing. 
		/// Some render states set up vertex processing, and some set up pixel processing.
		/// Render states can be saved and restored using stateblocks.
		/// </summary>
		/// <unmanaged>D3DRENDERSTATETYPE</unmanaged>
		public enum class RenderState : System::Int32
		{
			/// <summary>
			/// Depth-buffering state. Use values from <see cref="ZBufferType"/> to set this state. The
			/// default value for this state is <see cref="ZBufferType.UseZBuffer"/> if a depth stencil was created
			/// along with the device, or <see cref="ZBufferType.DontUseZBuffer"/> otherwise.
			/// </summary>
			ZEnable = D3DRS_ZENABLE,

			/// <summary>
			/// Defines the current fill mode of the device. Use values from <see cref="FillMode"/> to set this state.
			/// The default value is <see cref="FillMode.Solid"/>.
			/// </summary>
			FillMode = D3DRS_FILLMODE,

			/// <summary>
			/// Defines the current shade mode of the device. Use values from <see cref="ShadeMode"/> to set this state.
			/// The default value is <see cref="ShadeMode.Gouraud"/>.
			/// </summary>
			ShadeMode = D3DRS_SHADEMODE,

			/// <summary>
			/// Set this state to <c>true</c> to enable writes to the depth buffer, and <c>false</c> to disable
			/// them. The default value is <c>true</c>.
			/// </summary>
			ZWriteEnable = D3DRS_ZWRITEENABLE,

			/// <summary>
			/// Set this state to <c>true</c> to enable alpha testing, and <c>false</c> to disable it. The
			/// default value is <c>false</c>.
			/// </summary>
			AlphaTestEnable = D3DRS_ALPHATESTENABLE,

			/// <summary>
			/// Set this state to <c>true</c> to enable drawing of the last pixel in a line, and <c>false</c>
			/// to disable it. The default value is <c>true</c>.
			/// </summary>
			LastPixel = D3DRS_LASTPIXEL,

			/// <summary>
			/// Defines the current source blending mode of the device. Use values from <see cref="Blend"/> to
			/// set this state. The default value is <see cref="Blend.One"/>.
			/// </summary>
			SourceBlend = D3DRS_SRCBLEND,

			/// <summary>
			/// Defines the current destination blending mode of the device. Use values from <see cref="Blend"/> to
			/// set this state. The default value is <see cref="Blend.Zero"/>.
			/// </summary>
			DestinationBlend = D3DRS_DESTBLEND,

			/// <summary>
			/// Specifies how back-facing triangles are culled. Use values from <see cref="CullMode"/> to
			/// set this state. The default value is <see cref="CullMode.Counterclockwise"/>.
			/// </summary>
			CullMode = D3DRS_CULLMODE,

			/// <summary>
			/// Specifies the current depth testing function. Use values from <see cref="Compare"/> to
			/// set this state. The default value is <see cref="Compare.LessEqual"/>.
			/// </summary>
			ZFunc = D3DRS_ZFUNC,

			/// <summary>
			/// An integer value that specifies the reference alpha against which pixels are tested when
			/// alpha blending is enabled. The default value is 0.
			/// </summary>
			AlphaRef = D3DRS_ALPHAREF,

			/// <summary>
			/// Specifies the current alpha testing function. Use values from <see cref="Compare"/> to
			/// set this state. The default value is <see cref="Compare.Always"/>.
			/// </summary>
			AlphaFunc = D3DRS_ALPHAFUNC,

			/// <summary>
			/// Set this state to <c>true</c> to enable dithering, and <c>false</c> to disable it. The default
			/// value is <c>false</c>.
			/// </summary>
			DitherEnable = D3DRS_DITHERENABLE,

			/// <summary>
			/// Set this state to <c>true</c> to enable alpha blending, and <c>false</c> to disable it. The default
			/// value is <c>false</c>.
			/// </summary>
			AlphaBlendEnable = D3DRS_ALPHABLENDENABLE,

			/// <summary>
			/// Set this state to <c>true</c> to enable fog blending, and <c>false</c> to disable it. The default
			/// value is <c>false</c>.
			/// </summary>
			FogEnable = D3DRS_FOGENABLE,

			/// <summary>
			/// Set this state to <c>true</c> to enable specular highlights, and <c>false</c> to disable them. 
			/// The default value is <c>false</c>.
			/// </summary>
			SpecularEnable = D3DRS_SPECULARENABLE,

			/// <summary>
			/// Specifies current fog color. Use integer color values to set this state. The default value is
			/// 0 (black).
			/// </summary>
			FogColor = D3DRS_FOGCOLOR,

			/// <summary>
			/// Specifies the current fog formula to be used for pixel fog. Use values from <see cref="FogMode"/>
			/// to set this state. The default value is <see cref="FogMode.None"/>.
			/// </summary>
			FogTableMode = D3DRS_FOGTABLEMODE,

			/// <summary>
			/// A floating point value that defines the depth at which pixel or vertex fog effects begin.
			/// The default value is 0.0f.
			/// </summary>
			FogStart = D3DRS_FOGSTART,

			/// <summary>
			/// A floating point value that defines the depth at which pixel or vertex fog effects end.
			/// The default value is 1.0f.
			/// </summary>
			FogEnd = D3DRS_FOGEND,

			/// <summary>
			/// A floating point value that defines the density of fog used in exponential fog modes.
			/// The default value is 1.0f.
			/// </summary>
			FogDensity = D3DRS_FOGDENSITY,

			/// <summary>
			/// Set this state to <c>true</c> to enable range based fog, and <c>false</c> to use depth based fog. 
			/// The default value is <c>false</c>.
			/// </summary>
			RangeFogEnable = D3DRS_RANGEFOGENABLE,

			/// <summary>
			/// Set this state to <c>true</c> to enable stenciling, and <c>false</c> to disable it. 
			/// The default value is <c>false</c>.
			/// </summary>
			StencilEnable = D3DRS_STENCILENABLE,

			/// <summary>
			/// Specifies the stencil operation to perform if the stencil test fails. Use values from 
			/// <see cref="StencilOperation"/> to set this state. The default value is <see cref="StencilOperation.Keep"/>.
			/// </summary>
			StencilFail = D3DRS_STENCILFAIL,

			/// <summary>
			/// Specifies the stencil operation to perform if the stencil test passes and the depth test fails. 
			/// Use values from <see cref="StencilOperation"/> to set this state. The default value is 
			/// <see cref="StencilOperation.Keep"/>.
			/// </summary>
			StencilZFail = D3DRS_STENCILZFAIL,

			/// <summary>
			/// Specifies the stencil operation to perform if both the stencil and depth tests pass. Use values from 
			/// <see cref="StencilOperation"/> to set this state. The default value is <see cref="StencilOperation.Keep"/>.
			/// </summary>
			StencilPass = D3DRS_STENCILPASS,

			/// <summary>
			/// Specifies the comparison function for stencil tests. Use values from <see cref="Compare"/> 
			/// to set this state. The default value is <see cref="Compare.Always"/>.
			/// </summary>
			StencilFunc = D3DRS_STENCILFUNC,

			/// <summary>
			/// An integer value that specifies the reference value against which pixels are tested when
			/// stencil testing is enabled. The default value is 0.
			/// </summary>
			StencilRef = D3DRS_STENCILREF,

			/// <summary>
			/// An integer value that specifies the mask for stencil values. The default value is 0xFFFFFFFF.
			/// </summary>
			StencilMask = D3DRS_STENCILMASK,

			/// <summary>
			/// An integer value that specifies the write mask used for values written into the stencil buffer.
			/// The default value is 0xFFFFFFFF.
			/// </summary>
			StencilWriteMask = D3DRS_STENCILWRITEMASK,

			/// <summary>
			/// Specifies the color used for multiple texture blending. Use integer color values to set this 
			/// state. The default value is 0xFFFFFFFF (white).
			/// </summary>
			TextureFactor = D3DRS_TEXTUREFACTOR,

			/// <summary>
			/// Texture wrapping behavior for multiple sets of texture coordinates. Use values from
			/// <see cref="TextureWrapping"/> to set this state. The default value for this state is <see cref="None"/>.
			/// </summary>
			Wrap0 = D3DRS_WRAP0,

			/// <summary>
			/// Texture wrapping behavior for multiple sets of texture coordinates. Use values from
			/// <see cref="TextureWrapping"/> to set this state. The default value for this state is <see cref="None"/>.
			/// </summary>
			Wrap1 = D3DRS_WRAP1,

			/// <summary>
			/// Texture wrapping behavior for multiple sets of texture coordinates. Use values from
			/// <see cref="TextureWrapping"/> to set this state. The default value for this state is <see cref="None"/>.
			/// </summary>
			Wrap2 = D3DRS_WRAP2,

			/// <summary>
			/// Texture wrapping behavior for multiple sets of texture coordinates. Use values from
			/// <see cref="TextureWrapping"/> to set this state. The default value for this state is <see cref="None"/>.
			/// </summary>
			Wrap3 = D3DRS_WRAP3,

			/// <summary>
			/// Texture wrapping behavior for multiple sets of texture coordinates. Use values from
			/// <see cref="TextureWrapping"/> to set this state. The default value for this state is <see cref="None"/>.
			/// </summary>
			Wrap4 = D3DRS_WRAP4,

			/// <summary>
			/// Texture wrapping behavior for multiple sets of texture coordinates. Use values from
			/// <see cref="TextureWrapping"/> to set this state. The default value for this state is <see cref="None"/>.
			/// </summary>
			Wrap5 = D3DRS_WRAP5,

			/// <summary>
			/// Texture wrapping behavior for multiple sets of texture coordinates. Use values from
			/// <see cref="TextureWrapping"/> to set this state. The default value for this state is <see cref="None"/>.
			/// </summary>
			Wrap6 = D3DRS_WRAP6,

			/// <summary>
			/// Texture wrapping behavior for multiple sets of texture coordinates. Use values from
			/// <see cref="TextureWrapping"/> to set this state. The default value for this state is <see cref="None"/>.
			/// </summary>
			Wrap7 = D3DRS_WRAP7,

			/// <summary>
			/// Texture wrapping behavior for multiple sets of texture coordinates. Use values from
			/// <see cref="TextureWrapping"/> to set this state. The default value for this state is <see cref="None"/>.
			/// </summary>
			Wrap8 = D3DRS_WRAP8,

			/// <summary>
			/// Texture wrapping behavior for multiple sets of texture coordinates. Use values from
			/// <see cref="TextureWrapping"/> to set this state. The default value for this state is <see cref="None"/>.
			/// </summary>
			Wrap9 = D3DRS_WRAP9,

			/// <summary>
			/// Texture wrapping behavior for multiple sets of texture coordinates. Use values from
			/// <see cref="TextureWrapping"/> to set this state. The default value for this state is <see cref="None"/>.
			/// </summary>
			Wrap10 = D3DRS_WRAP10,

			/// <summary>
			/// Texture wrapping behavior for multiple sets of texture coordinates. Use values from
			/// <see cref="TextureWrapping"/> to set this state. The default value for this state is <see cref="None"/>.
			/// </summary>
			Wrap11 = D3DRS_WRAP11,

			/// <summary>
			/// Texture wrapping behavior for multiple sets of texture coordinates. Use values from
			/// <see cref="TextureWrapping"/> to set this state. The default value for this state is <see cref="None"/>.
			/// </summary>
			Wrap12 = D3DRS_WRAP12,

			/// <summary>
			/// Texture wrapping behavior for multiple sets of texture coordinates. Use values from
			/// <see cref="TextureWrapping"/> to set this state. The default value for this state is <see cref="None"/>.
			/// </summary>
			Wrap13 = D3DRS_WRAP13,

			/// <summary>
			/// Texture wrapping behavior for multiple sets of texture coordinates. Use values from
			/// <see cref="TextureWrapping"/> to set this state. The default value for this state is <see cref="None"/>.
			/// </summary>
			Wrap14 = D3DRS_WRAP14,

			/// <summary>
			/// Texture wrapping behavior for multiple sets of texture coordinates. Use values from
			/// <see cref="TextureWrapping"/> to set this state. The default value for this state is <see cref="None"/>.
			/// </summary>
			Wrap15 = D3DRS_WRAP15,

			/// <summary>
			/// Set this state to <c>true</c> to enable primitive clipping, and <c>false</c>
			/// to disable it. The default value is <c>true</c>.
			/// </summary>
			Clipping = D3DRS_CLIPPING,

			/// <summary>
			/// Set this state to <c>true</c> to enable lighting, and <c>false</c>
			/// to disable it. The default value is <c>true</c>.
			/// </summary>
			Lighting = D3DRS_LIGHTING,

			/// <summary>
			/// Specifies the ambient light color. Use integer color values to set this state. The default value 
			/// is 0 (black).
			/// </summary>
			Ambient = D3DRS_AMBIENT,

			/// <summary>
			/// Specifies the current fog formula to be used for vertex fog. Use values from <see cref="FogMode"/>
			/// to set this state. The default value is <see cref="FogMode.None"/>.
			/// </summary>
			FogVertexMode = D3DRS_FOGVERTEXMODE,

			/// <summary>
			/// Set this state to <c>true</c> to enable colored vertices, and <c>false</c>
			/// to disable them. The default value is <c>true</c>.
			/// </summary>
			ColorVertex = D3DRS_COLORVERTEX,

			/// <summary>
			/// Set this state to <c>true</c> to enable camera-relative specular highlights, and <c>false</c>
			/// to use orthogonal specular highlights. The default value is <c>true</c>.
			/// </summary>
			LocalViewer = D3DRS_LOCALVIEWER,

			/// <summary>
			/// Set this state to <c>true</c> to enable automatic normalization of vertex normals, and <c>false</c>
			/// to disable it. The default value is <c>false</c>.
			/// </summary>
			NormalizeNormals = D3DRS_NORMALIZENORMALS,

			/// <summary>
			/// Specifies the source for diffuse colors. Use values from <see cref="ColorSource"/> to set
			/// this state. The default value is <see cref="ColorSource.Color1"/>.
			/// </summary>
			DiffuseMaterialSource = D3DRS_DIFFUSEMATERIALSOURCE,

			/// <summary>
			/// Specifies the source for specular colors. Use values from <see cref="ColorSource"/> to set
			/// this state. The default value is <see cref="ColorSource.Color2"/>.
			/// </summary>
			SpecularMaterialSource = D3DRS_SPECULARMATERIALSOURCE,

			/// <summary>
			/// Specifies the source for ambient colors. Use values from <see cref="ColorSource"/> to set
			/// this state. The default value is <see cref="ColorSource.Material"/>.
			/// </summary>
			AmbientMaterialSource = D3DRS_AMBIENTMATERIALSOURCE,

			/// <summary>
			/// Specifies the source for emissive colors. Use values from <see cref="ColorSource"/> to set
			/// this state. The default value is <see cref="ColorSource.Material"/>.
			/// </summary>
			EmissiveMaterialSource = D3DRS_EMISSIVEMATERIALSOURCE,

			/// <summary>
			/// An integer value that specifies the number of matrices to use to perform geometry blending.
			/// Use values from <see cref="VertexBlend"/> to set this state. The default value is
			/// <see cref="VertexBlend.Disable"/>.
			/// </summary>
			VertexBlend = D3DRS_VERTEXBLEND,

			/// <summary>
			/// An integer value that specifies which user-defined clip planes are active. Use
			/// </summary>
			ClipPlaneEnable = D3DRS_CLIPPLANEENABLE,

			/// <summary>
			/// A floating point value that specifies the size of points.
			/// </summary>
			PointSize = D3DRS_POINTSIZE,

			/// <summary>
			/// A floating point value that specifies the minimum size of point primitives.
			/// </summary>
			PointSizeMin = D3DRS_POINTSIZE_MIN,

			/// <summary>
			/// Set this state to <c>true</c> to enable point sprites, and <c>false</c>
			/// to disable them. The default value is <c>false</c>.
			/// </summary>
			PointSpriteEnable = D3DRS_POINTSPRITEENABLE,

			/// <summary>
			/// Set this state to <c>true</c> to enable point scaling, and <c>false</c>
			/// to disable it. The default value is <c>false</c>.
			/// </summary>
			PointScaleEnable = D3DRS_POINTSCALEENABLE,

			/// <summary>
			/// A floating point value that specifies attenuation when point scaling is applied. The default
			/// value is 1.0f.
			/// </summary>
			PointScaleA = D3DRS_POINTSCALE_A,

			/// <summary>
			/// A floating point value that specifies attenuation when point scaling is applied. The default
			/// value is 0.0f.
			/// </summary>
			PointScaleB = D3DRS_POINTSCALE_B,

			/// <summary>
			/// A floating point value that specifies attenuation when point scaling is applied. The default
			/// value is 0.0f.
			/// </summary>
			PointScaleC = D3DRS_POINTSCALE_C,

			/// <summary>
			/// Set this state to <c>true</c> to enable point multisampling, and <c>false</c>
			/// to disable it. The default value is <c>false</c>.
			/// </summary>
			MultisampleAntialias = D3DRS_MULTISAMPLEANTIALIAS,

			/// <summary>
			/// An integer mask that controls the samples in a multisampling render target.
			/// </summary>
			MultisampleMask = D3DRS_MULTISAMPLEMASK,

			/// <summary>
			/// Specifies the current patch edge style. Use values from <see cref="PatchEdgeStyle"/> to
			/// set this state. The default value is <see cref="PatchEdgeStyle.Discrete"/>.
			/// </summary>
			PatchEdgeStyle = D3DRS_PATCHEDGESTYLE,

			/// <summary>
			/// Specifies the current debug monitor token. Use values from <see cref="DebugMonitorToken"/> to
			/// set this state. The default value is <see cref="DebugMonitorToken.Enable"/>.
			/// </summary>
			DebugMonitorToken = D3DRS_DEBUGMONITORTOKEN,

			/// <summary>
			/// A floating point value that specifies the maximum size of point primitives.
			/// </summary>
			PointSizeMax = D3DRS_POINTSIZE_MAX,

			/// <summary>
			/// Set this state to <c>true</c> to enable indexed vertex blending, and <c>false</c>
			/// to disable it. The default value is <c>false</c>.
			/// </summary>
			IndexedVertexBlendEnable = D3DRS_INDEXEDVERTEXBLENDENABLE,

			/// <summary>
			/// Specifies the current color write state of the device. Use values from <see cref="ColorWriteEnable"/>
			/// to set this state. The default value is <see cref="ColorWriteEnable.All"/>.
			/// </summary>
			ColorWriteEnable = D3DRS_COLORWRITEENABLE,

			/// <summary>
			/// A floating point value that specifies the tweening factor. The default value is 0.0f.
			/// </summary>
			TweenFactor = D3DRS_TWEENFACTOR,

			/// <summary>
			/// Specifies the blending operation to use when alpha blending is enabled. Use values from
			/// <see cref="BlendOperation"/> to set this state. The default value is <see cref="BlendOperation.Add"/>.
			/// </summary>
			BlendOperation = D3DRS_BLENDOP,

			/// <summary>
			/// Specifies the N-patch position interpolation degree. Use values from <see cref="Degree"/> to
			/// set this state. The default value is <see cref="Degree.Cubic"/>.
			/// </summary>
			PositionDegree = D3DRS_POSITIONDEGREE,

			/// <summary>
			/// Specifies the N-patch normal interpolation degree. Use values from <see cref="Degree"/> to
			/// set this state. The default value is <see cref="Degree.Linear"/>.
			/// </summary>
			NormalDegree = D3DRS_NORMALDEGREE,

			/// <summary>
			/// Set this state to <c>true</c> to enable scissor testing, and <c>false</c>
			/// to disable it. The default value is <c>false</c>.
			/// </summary>
			ScissorTestEnable = D3DRS_SCISSORTESTENABLE,

			/// <summary>
			/// An integer value that specifies how much bias can be applied to co-planar primitives to reduce
			/// Z-fighting. The default value is 0.
			/// </summary>
			SlopeScaleDepthBias = D3DRS_SLOPESCALEDEPTHBIAS,

			/// <summary>
			/// Set this state to <c>true</c> to enable antialiased lines, and <c>false</c>
			/// to disable them. The default value is <c>false</c>.
			/// </summary>
			AntialiasedLineEnable = D3DRS_ANTIALIASEDLINEENABLE,

			/// <summary>
			/// A floating point value that specifies the minium tessellation level. The default value is 1.0f.
			/// </summary>
			MinTessellationLevel = D3DRS_MINTESSELLATIONLEVEL,

			/// <summary>
			/// A floating point value that specifies the maximum tessellation level. The default value is 1.0f.
			/// </summary>
			MaxTessellationLevel = D3DRS_MAXTESSELLATIONLEVEL,

			/// <summary>
			/// A floating point value that specifies the amount to adaptively tessellate, in the X direction.
			/// The default value is 0.0f.
			/// </summary>
			AdaptiveTessX = D3DRS_ADAPTIVETESS_X,

			/// <summary>
			/// A floating point value that specifies the amount to adaptively tessellate, in the Y direction.
			/// The default value is 0.0f.
			/// </summary>
			AdaptiveTessY = D3DRS_ADAPTIVETESS_Y,

			/// <summary>
			/// A floating point value that specifies the amount to adaptively tessellate, in the Z direction.
			/// The default value is 0.0f.
			/// </summary>
			AdaptiveTessZ = D3DRS_ADAPTIVETESS_Z,

			/// <summary>
			/// A floating point value that specifies the amount to adaptively tessellate, in the W direction.
			/// The default value is 1.0f.
			/// </summary>
			AdaptiveTessW = D3DRS_ADAPTIVETESS_W,

			/// <summary>
			/// Set this state to <c>true</c> to enable adaptive tessellation, and <c>false</c>
			/// to disable it. The default value is <c>false</c>.
			/// </summary>
			EnableAdaptiveTessellation = D3DRS_ENABLEADAPTIVETESSELLATION,

			/// <summary>
			/// Set this state to <c>true</c> to enable two sided stenciling, and <c>false</c>
			/// to disable it. The default value is <c>false</c>.
			/// </summary>
			TwoSidedStencilMode = D3DRS_TWOSIDEDSTENCILMODE,

			/// <summary>
			/// Specifies the operation to perform if the stencil test fails. Use values from
			/// <see cref="StencilOperation"/> to set the state. The default value is <see cref="StencilOperation.Keep"/>.
			/// </summary>
			CcwStencilFail = D3DRS_CCW_STENCILFAIL,

			/// <summary>
			/// Specifies the operation to perform if the stencil test passes and depth test fails. Use values from
			/// <see cref="StencilOperation"/> to set the state. The default value is <see cref="StencilOperation.Keep"/>.
			/// </summary>
			CcwStencilZFail = D3DRS_CCW_STENCILZFAIL,

			/// <summary>
			/// Specifies the operation to perform if both the stencil and depth tests pass. Use values from
			/// <see cref="StencilOperation"/> to set the state. The default value is <see cref="StencilOperation.Keep"/>.
			/// </summary>
			CcwStencilPass = D3DRS_CCW_STENCILPASS,

			/// <summary>
			/// Specifies the comparison function for stencil tests.. Use values from
			/// <see cref="Compare"/> to set the state. The default value is <see cref="Compare.Always"/>.
			/// </summary>
			CcwStencilFunc = D3DRS_CCW_STENCILFUNC,

			/// <summary>
			/// Specifies additional color write enable settings for the device. Use values from <see cref="ColorWriteEnable"/>
			/// to set this state. The default value is <see cref="ColorWriteEnable.All"/>.
			/// </summary>
			ColorWriteEnable1 = D3DRS_COLORWRITEENABLE1,

			/// <summary>
			/// Specifies additional color write enable settings for the device. Use values from <see cref="ColorWriteEnable"/>
			/// to set this state. The default value is <see cref="ColorWriteEnable.All"/>.
			/// </summary>
			ColorWriteEnable2 = D3DRS_COLORWRITEENABLE2,

			/// <summary>
			/// Specifies additional color write enable settings for the device. Use values from <see cref="ColorWriteEnable"/>
			/// to set this state. The default value is <see cref="ColorWriteEnable.All"/>.
			/// </summary>
			ColorWriteEnable3 = D3DRS_COLORWRITEENABLE3,

			/// <summary>
			/// Specifies a color to use as a constant blend factor for alpha blending. Use integer color values 
			/// to set this state. The default value is 0xFFFFFFFF (white).
			/// </summary>
			BlendFactor = D3DRS_BLENDFACTOR,

			/// <summary>
			/// Set this state to <c>true</c> to enable sRGB gamma correction, and <c>false</c>
			/// to disable it. The default value is <c>false</c>.
			/// </summary>
			SrgbWriteEnable = D3DRS_SRGBWRITEENABLE,

			/// <summary>
			/// A floating point value that is used for comparison of depth values.
			/// </summary>
			DepthBias = D3DRS_DEPTHBIAS,

			/// <summary>
			/// Set this state to <c>true</c> to enable separate blending modes for the alpha channel, and <c>false</c>
			/// to disable them. The default value is <c>false</c>.
			/// </summary>
			SeparateAlphaBlendEnable = D3DRS_SEPARATEALPHABLENDENABLE,

			/// <summary>
			/// Specifies the source alpha blending function. Use values from <see cref="Blend"/> to set this state.
			/// The default value is <see cref="Blend.One"/>.
			/// </summary>
			SourceBlendAlpha = D3DRS_SRCBLENDALPHA,

			/// <summary>
			/// Specifies the destination alpha blending function. Use values from <see cref="Blend"/> to set this state.
			/// The default value is <see cref="Blend.Zero"/>.
			/// </summary>
			DestinationBlendAlpha = D3DRS_DESTBLENDALPHA,

			/// <summary>
			/// Specifies the operation to perform for separate alpha blending. Use values from <see cref="BlendOperation"/>
			/// to set this state. The default value is <see cref="BlendOperation.Add"/>.
			/// </summary>
			BlendOperationAlpha = D3DRS_BLENDOPALPHA
		};
		
		/// <summary>
		/// Defines resource types.
		/// </summary>
		/// <unmanaged>D3DRESOURCETYPE</unmanaged>
		public enum class ResourceType : System::Int32
		{
			/// <summary>
			/// Surface resource.
			/// </summary>
			Surface = D3DRTYPE_SURFACE,

			/// <summary>
			/// Volume resource.
			/// </summary>
			Volume = D3DRTYPE_VOLUME,

			/// <summary>
			/// Texture resource.
			/// </summary>
			Texture = D3DRTYPE_TEXTURE,

			/// <summary>
			/// Volume texture resource.
			/// </summary>
			VolumeTexture = D3DRTYPE_VOLUMETEXTURE,

			/// <summary>
			/// Cube texture resource.
			/// </summary>
			CubeTexture = D3DRTYPE_CUBETEXTURE,

			/// <summary>
			/// Vertex buffer resource.
			/// </summary>
			VertexBuffer = D3DRTYPE_VERTEXBUFFER,

			/// <summary>
			/// Index buffer resource.
			/// </summary>
			IndexBuffer = D3DRTYPE_INDEXBUFFER,
		};
		
		/// <summary>
		/// Sampler states define texture sampling operations such as texture addressing and texture filtering. 
		/// Some sampler states set-up vertex processing, and some set-up pixel processing. Sampler states can 
		/// be saved and restored using stateblocks 
		/// </summary>
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
		public enum class TextureWrapping : System::Int32
		{
			None = 0,
			WrapCoordinate0 = D3DWRAPCOORD_0,
			WrapCoordinate1 = D3DWRAPCOORD_1,
			WrapCoordinate2 = D3DWRAPCOORD_2,
			WrapCoordinate3 = D3DWRAPCOORD_3,
			All = WrapCoordinate0 | WrapCoordinate1 | WrapCoordinate2 | WrapCoordinate3
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
