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

#include <dwrite.h>

namespace SlimDX
{
	namespace DirectWrite
	{
		// NOTE: The enumerations defined in this file are in alphabetical order. When
		//       adding new enumerations or renaming existing ones, please make sure
		//       the ordering is maintained.

		public enum class FactoryType : System::Int32
		{
			Shared = DWRITE_FACTORY_TYPE_SHARED,
			Isolated = DWRITE_FACTORY_TYPE_ISOLATED
		};

		public enum class FontStretch : System::Int32
		{
			Undefined =  DWRITE_FONT_STRETCH_UNDEFINED,
			UltraCondensed =  DWRITE_FONT_STRETCH_ULTRA_CONDENSED,
			ExtraCondensed =  DWRITE_FONT_STRETCH_EXTRA_CONDENSED,
			Condensed =  DWRITE_FONT_STRETCH_CONDENSED,
			SemiCondensed =  DWRITE_FONT_STRETCH_SEMI_CONDENSED,
			Normal =  DWRITE_FONT_STRETCH_NORMAL,
			SemiExpanded =  DWRITE_FONT_STRETCH_SEMI_EXPANDED,
			Expanded =  DWRITE_FONT_STRETCH_EXPANDED,
			ExtraExpanded =  DWRITE_FONT_STRETCH_EXTRA_EXPANDED,
			UltraExpanded =  DWRITE_FONT_STRETCH_ULTRA_EXPANDED
		};

		public enum class FontStyle : System::Int32
		{
			Normal = DWRITE_FONT_STYLE_NORMAL,
			Oblique = DWRITE_FONT_STYLE_OBLIQUE,
			Italic = DWRITE_FONT_STYLE_ITALIC
		};

		public enum class FontWeight : System::Int32
		{
			Thin = DWRITE_FONT_WEIGHT_THIN,
			ExtraLight = DWRITE_FONT_WEIGHT_EXTRA_LIGHT,
			Light = DWRITE_FONT_WEIGHT_LIGHT,
			Normal = DWRITE_FONT_WEIGHT_NORMAL,
			Medium = DWRITE_FONT_WEIGHT_MEDIUM,
			SemiBold = DWRITE_FONT_WEIGHT_SEMI_BOLD,
			Bold = DWRITE_FONT_WEIGHT_BOLD,
			ExtraBold = DWRITE_FONT_WEIGHT_EXTRA_BOLD,
			Black = DWRITE_FONT_WEIGHT_BLACK,
			ExtraBlack = DWRITE_FONT_WEIGHT_EXTRA_BLACK
		};

		public enum class ParagraphAlignment : System::Int32
		{
			Near = DWRITE_PARAGRAPH_ALIGNMENT_NEAR,
			Far = DWRITE_PARAGRAPH_ALIGNMENT_FAR,
			Center = DWRITE_PARAGRAPH_ALIGNMENT_CENTER
		};

		public enum class TextAlignment : System::Int32
		{
			Leading = DWRITE_TEXT_ALIGNMENT_LEADING,
			Trailing = DWRITE_TEXT_ALIGNMENT_TRAILING,
			Center = DWRITE_TEXT_ALIGNMENT_CENTER
		};
	}
}