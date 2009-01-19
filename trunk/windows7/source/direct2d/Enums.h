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

		public enum class DebugLevel : System::Int32
		{
			None = D2D1_DEBUG_LEVEL_NONE,
			Error = D2D1_DEBUG_LEVEL_ERROR,
			Warning = D2D1_DEBUG_LEVEL_WARNING,
			Information = D2D1_DEBUG_LEVEL_INFORMATION
		};

		public enum class FactoryType : System::Int32
		{
			SingleThreaded = D2D1_FACTORY_TYPE_SINGLE_THREADED,
			MultiThreaded = D2D1_FACTORY_TYPE_MULTI_THREADED
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
	}
}