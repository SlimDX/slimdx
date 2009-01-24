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

#include <d2d1.h>

namespace SlimDX
{
	namespace Direct2D
	{
		// NOTE: The enumerations defined in this file are in alphabetical order. When
		//       adding new enumerations or renaming existing ones, please make sure
		//       the ordering is maintained.

		public enum class AlphaMode : System::Int32
		{
			Unknown = D2D1_ALPHA_MODE_UNKNOWN,
			Premultiplied = D2D1_ALPHA_MODE_PREMULTIPLIED,
			Straight = D2D1_ALPHA_MODE_STRAIGHT,
			Ignore = D2D1_ALPHA_MODE_IGNORE
		};

		public enum class AntialiasMode : System::Int32
		{
			PerPrimitive = D2D1_ANTIALIAS_MODE_PER_PRIMITIVE,
			Aliased = D2D1_ANTIALIAS_MODE_ALIASED
		};

		public enum class CapStyle : System::Int32
		{
			Flat = D2D1_CAP_STYLE_FLAT,
			Square = D2D1_CAP_STYLE_SQUARE,
			Round = D2D1_CAP_STYLE_ROUND,
			Triangle = D2D1_CAP_STYLE_TRIANGLE
		};

		public enum class CompatibleRenderTargetOptions : System::Int32
		{
			None = D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE,
			GdiCompatible = D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_GDI_COMPATIBLE
		};

		public enum class DashStyle : System::Int32
		{
			Solid = D2D1_DASH_STYLE_SOLID,
			Dash = D2D1_DASH_STYLE_DASH,
			Dot = D2D1_DASH_STYLE_DOT,
			DashDot = D2D1_DASH_STYLE_DASH_DOT,
			DashDotDot = D2D1_DASH_STYLE_DASH_DOT_DOT,
			Custom = D2D1_DASH_STYLE_CUSTOM
		};

		public enum class DebugLevel : System::Int32
		{
			None = D2D1_DEBUG_LEVEL_NONE,
			Error = D2D1_DEBUG_LEVEL_ERROR,
			Warning = D2D1_DEBUG_LEVEL_WARNING,
			Information = D2D1_DEBUG_LEVEL_INFORMATION
		};

		[System::Flags]
		public enum class DrawTextOptions : System::Int32
		{
			None = D2D1_DRAW_TEXT_OPTIONS_NONE,
			NoSnap = D2D1_DRAW_TEXT_OPTIONS_NO_SNAP,
			NoClip = D2D1_DRAW_TEXT_OPTIONS_NO_CLIP
		};

		public enum class ExtendMode : System::Int32
		{
			Clamp = D2D1_EXTEND_MODE_CLAMP,
			Wrap = D2D1_EXTEND_MODE_WRAP,
			Mirror = D2D1_EXTEND_MODE_MIRROR
		};

		public enum class FactoryType : System::Int32
		{
			SingleThreaded = D2D1_FACTORY_TYPE_SINGLE_THREADED,
			MultiThreaded = D2D1_FACTORY_TYPE_MULTI_THREADED
		};

		public enum class Gamma : System::Int32
		{
			StandardRgb = D2D1_GAMMA_2_2,
			Linear = D2D1_GAMMA_1_0
		};

		public enum class InterpolationMode : System::Int32
		{
			NearestNeighbor = D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
			Linear = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
		};

		[System::Flags]
		public enum class LayerOptions : System::Int32
		{
			None = D2D1_LAYER_OPTIONS_NONE,
			InitializeForClearType = D2D1_LAYER_OPTIONS_INITIALIZE_FOR_CLEARTYPE
		};

		public enum class LineJoin : System::Int32
		{
			Miter = D2D1_LINE_JOIN_MITER,
			Bevel = D2D1_LINE_JOIN_BEVEL,
			Round = D2D1_LINE_JOIN_ROUND,
			MiterOrBevel = D2D1_LINE_JOIN_MITER_OR_BEVEL
		};

		public enum class PresentOptions : System::Int32
		{
			None = D2D1_PRESENT_OPTIONS_NONE,
			RetainContents = D2D1_PRESENT_OPTIONS_RETAIN_CONTENTS,
			Immediately = D2D1_PRESENT_OPTIONS_IMMEDIATELY
		};

		[System::Flags]
		public enum class RenderTargetUsage : System::Int32
		{
			None = D2D1_RENDER_TARGET_USAGE_NONE,
			ForceBitmapRemoting = D2D1_RENDER_TARGET_USAGE_FORCE_BITMAP_REMOTING,
			ForceHardwareRendering = D2D1_RENDER_TARGET_USAGE_FORCE_HARDWARE_RENDERING,
			ForceSoftwareRendering = D2D1_RENDER_TARGET_USAGE_FORCE_SOFTWARE_RENDERING,
			GdiCompatible = D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE
		};

		public enum class TextAntialiasMode : System::Int32
		{
			Default = D2D1_TEXT_ANTIALIAS_MODE_DEFAULT,
			ClearType = D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE,
			GrayScale = D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE,
			Aliased = D2D1_TEXT_ANTIALIAS_MODE_ALIASED
		};
	}
}