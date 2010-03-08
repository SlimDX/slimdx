/*
* Copyright (c) 2007-2010 SlimDX Group
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

extern const IID IID_IDWriteFactory;

#include "../ComObject.h"
#include "Enums.h"
#include "GlyphRunDW.h"

namespace SlimDX
{
	namespace Direct2D
	{
		value class Matrix3x2;
	}
	namespace DirectWrite
	{
		using namespace SlimDX::Direct2D;
		using namespace System;
		ref class FontCollection;
		ref class FontFace;
		ref class FontFile;
		ref class GlyphRunAnalysis;
		ref class InlineObject;
		ref class NumberSubstitution;
		ref class TextFormat;
		ref class TextLayout;

		public ref class Factory : public ComObject
		{
			COMOBJECT(IDWriteFactory, Factory);

			void Init( FactoryType factoryType );
			
		public:
			Factory();
			Factory( FactoryType factoryType );

			FontCollection ^GetSystemFontCollection(bool checkForUpdates);

			TextLayout ^CreateGdiCompatibleTextLayout(String ^string, TextFormat ^textFormat,
				float layoutWidth, float layoutHeight, float pixelsPerDip,
				bool useGdiNatural);
			TextLayout ^CreateGdiCompatibleTextLayout(String ^string, TextFormat ^textFormat,
				float layoutWidth, float layoutHeight, float pixelsPerDip,
				Matrix3x2 transform, bool useGdiNatural);
			InlineObject ^CreateEllipsisTrimmingSign(TextFormat ^textFormat);
			FontFace ^CreateFontFace(FontFaceType fontFaceType, array<FontFile^> ^fontFiles, int faceIndex, FontSimulations fontFaceSimulationFlags);
			FontFile ^CreateFontFileReference(String ^filePath);
			FontFile ^CreateFontFileReference(String ^filePath, System::Runtime::InteropServices::ComTypes::FILETIME fileTime);
			GlyphRunAnalysis ^CreateGlyphRunAnalysis(GlyphRun ^glyphRun, float pixelsPerDip,
				RenderingMode renderingMode, MeasuringMode measuringMode,
				float baselineOriginX, float baselineOriginY);
			GlyphRunAnalysis ^CreateGlyphRunAnalysis(GlyphRun ^glyphRun,
				float pixelsPerDip, Matrix3x2 transform,
				RenderingMode renderingMode, MeasuringMode measuringMode,
				float baselineOriginX, float baselineOriginY);
			RenderingParameters ^CreateMonitorRenderingParameters(IntPtr monitor);
			NumberSubstitution ^CreateNumberSubstitution(NumberSubstitutionMethod method, String ^localeName, bool ignoreUserOverride);
			RenderingParameters ^CreateRenderingParameters();
		};
	}
}
