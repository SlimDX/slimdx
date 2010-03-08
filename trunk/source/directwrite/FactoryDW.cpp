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
#include "stdafx.h"
#include <vector>

#include "DirectWriteException.h"
#include "../direct2d/Matrix3x2.h"
#include "../stack_array.h"

#include "FactoryDW.h"
#include "FontCollection.h"
#include "FontFile.h"
#include "FontFace.h"
#include "GlyphRunDW.h"
#include "GlyphRunAnalysis.h"
#include "InlineObject.h"
#include "NativeUnicodeString.h"
#include "NumberSubstitution.h"
#include "RenderingParameters.h"
#include "TextAnalyzer.h"
#include "TextFormat.h"
#include "TextLayout.h"

const IID IID_IDWriteFactory = __uuidof(IDWriteFactory);

using namespace System;

namespace SlimDX
{
namespace DirectWrite
{
	Factory::Factory()
	{
		Init( FactoryType::Shared );
	}

	Factory::Factory( FactoryType factoryType )
	{
		Init( factoryType );
	}

	void Factory::Init( FactoryType factoryType )
	{
		IDWriteFactory *factory = NULL;

		if( RECORD_DW( DWriteCreateFactory( static_cast<DWRITE_FACTORY_TYPE>( factoryType ), IID_IDWriteFactory, reinterpret_cast<IUnknown**>( &factory ) ) ).IsFailure )
			throw gcnew DirectWriteException( Result::Last );

		Construct( factory );
	}

	FontCollection ^Factory::GetSystemFontCollection(bool checkForUpdates)
	{
		IDWriteFontCollection *collection = 0;
		if (RECORD_DW(InternalPointer->GetSystemFontCollection(&collection, checkForUpdates ? TRUE : FALSE)).IsFailure)
		{
			return nullptr;
		}
		return FontCollection::FromPointer(collection);
	}

	static TextLayout ^CreateGdiCompatibleTextLayoutInternal(IDWriteFactory *factory,
		String ^text, TextFormat ^textFormat,
		float layoutWidth, float layoutHeight, float pixelsPerDip,
		DWRITE_MATRIX *transform, bool useGdiNatural)
	{
		IDWriteTextLayout *layout = 0;
		if (RECORD_DW(factory->CreateGdiCompatibleTextLayout(NativeUnicodeString(text), text->Length,
			textFormat->InternalPointer, layoutWidth, layoutHeight, pixelsPerDip,
			transform, useGdiNatural ? TRUE : FALSE, &layout)).IsFailure)
		{
			return nullptr;
		}
		return TextLayout::FromPointer(layout);			
	}

	TextLayout ^Factory::CreateGdiCompatibleTextLayout(String ^text, TextFormat ^textFormat,
		float layoutWidth, float layoutHeight, float pixelsPerDip, bool useGdiNatural)
	{
		return CreateGdiCompatibleTextLayoutInternal(InternalPointer, text, textFormat,
			layoutWidth, layoutHeight, pixelsPerDip, 0, useGdiNatural);
	}
	TextLayout ^Factory::CreateGdiCompatibleTextLayout(String ^text, TextFormat ^textFormat,
		float layoutWidth, float layoutHeight, float pixelsPerDip,
		SlimDX::Direct2D::Matrix3x2 transform, bool useGdiNatural)
	{
		return CreateGdiCompatibleTextLayoutInternal(InternalPointer, text, textFormat,
			layoutWidth, layoutHeight, pixelsPerDip,
			reinterpret_cast<DWRITE_MATRIX *>(&transform), useGdiNatural);
	}
	InlineObject ^Factory::CreateEllipsisTrimmingSign(TextFormat ^textFormat)
	{
		IDWriteInlineObject *obj = 0;
		if (RECORD_DW(InternalPointer->
			CreateEllipsisTrimmingSign(textFormat->InternalPointer, &obj)).IsFailure)
		{
			return nullptr;
		}
		return InlineObject::FromPointer(obj);
	}
	FontFace ^Factory::CreateFontFace(FontFaceType fontFaceType, array<FontFile^> ^fontFiles, int faceIndex, FontSimulations fontFaceSimulationFlags)
	{
		std::vector<IDWriteFontFile *> nativeFontFiles;
		nativeFontFiles.resize(fontFiles->Length);
		for (int i = 0; i < fontFiles->Length; i++)
		{
			nativeFontFiles[i] = fontFiles[i]->InternalPointer;
		}
		IDWriteFontFace *fontFace;
		if (RECORD_DW(InternalPointer->CreateFontFace(static_cast<DWRITE_FONT_FACE_TYPE>(fontFaceType),
			nativeFontFiles.size(), &nativeFontFiles[0],
			faceIndex, static_cast<DWRITE_FONT_SIMULATIONS>(fontFaceSimulationFlags),
			&fontFace)).IsFailure)
		{
			return nullptr;
		}
		return FontFace::FromPointer(fontFace);
	}

	static FontFile ^CreateFontFileReferenceInternal(IDWriteFactory *factory, String ^filePath, FILETIME const *fileTime)
	{
		IDWriteFontFile *fontFile = 0;
		if (RECORD_DW(factory->CreateFontFileReference(NativeUnicodeString(filePath), fileTime, &fontFile)).IsFailure)
		{
			return nullptr;
		}
		return FontFile::FromPointer(fontFile);
	}

	FontFile ^Factory::CreateFontFileReference(String ^filePath)
	{
		return CreateFontFileReferenceInternal(InternalPointer, filePath, 0);
	}
	FontFile ^Factory::CreateFontFileReference(String ^filePath, System::Runtime::InteropServices::ComTypes::FILETIME fileTime)
	{
		return CreateFontFileReferenceInternal(InternalPointer, filePath, reinterpret_cast<FILETIME *>(&fileTime));
	}

	static GlyphRunAnalysis ^CreateGlyphRunAnalysisInternal(IDWriteFactory *factory,
		GlyphRun ^glyphRun, float pixelsPerDip, DWRITE_MATRIX *transform,
		RenderingMode renderingMode, MeasuringMode measuringMode,
		float baselineOriginX, float baselineOriginY)
	{
		stack_array<UINT16> indices;
		stack_array<FLOAT> advances;
		stack_array<DWRITE_GLYPH_OFFSET> offsets;
		DWRITE_GLYPH_RUN nativeGlyphRun = glyphRun->ToUnmanaged(indices, advances, offsets);
		IDWriteGlyphRunAnalysis *analysis = 0;
		if (RECORD_DW(factory->CreateGlyphRunAnalysis(&nativeGlyphRun,
				pixelsPerDip, transform,
				static_cast<DWRITE_RENDERING_MODE>(renderingMode),
				static_cast<DWRITE_MEASURING_MODE>(measuringMode),
				baselineOriginX, baselineOriginY, &analysis)).IsFailure)
		{
			return nullptr;
		}
		return GlyphRunAnalysis::FromPointer(analysis);
	}

	GlyphRunAnalysis ^Factory::CreateGlyphRunAnalysis(GlyphRun ^glyphRun, float pixelsPerDip,
		RenderingMode renderingMode, MeasuringMode measuringMode,
		float baselineOriginX, float baselineOriginY)
	{
		return CreateGlyphRunAnalysisInternal(InternalPointer,
			glyphRun, pixelsPerDip, 0, renderingMode, measuringMode,
			baselineOriginX, baselineOriginY);
	}
	GlyphRunAnalysis ^Factory::CreateGlyphRunAnalysis(GlyphRun ^glyphRun,
		float pixelsPerDip, Matrix3x2 transform,
		RenderingMode renderingMode, MeasuringMode measuringMode,
		float baselineOriginX, float baselineOriginY)
	{
		return CreateGlyphRunAnalysisInternal(InternalPointer,
			glyphRun, pixelsPerDip, reinterpret_cast<DWRITE_MATRIX *>(&transform),
			renderingMode, measuringMode,
			baselineOriginX, baselineOriginY);
	}

	RenderingParameters ^Factory::CreateMonitorRenderingParameters(IntPtr monitor)
	{
		IDWriteRenderingParams *params = 0;
		if (RECORD_DW(InternalPointer->CreateMonitorRenderingParams(static_cast<HMONITOR>(monitor.ToPointer()), &params)).IsFailure)
		{
			return nullptr;
		}
		return RenderingParameters::FromPointer(params);
	}

	NumberSubstitution ^Factory::CreateNumberSubstitution(NumberSubstitutionMethod method, String ^localeName, bool ignoreUserOverride)
	{
		IDWriteNumberSubstitution *sub = 0;
		if (RECORD_DW(InternalPointer->CreateNumberSubstitution(
			static_cast<DWRITE_NUMBER_SUBSTITUTION_METHOD>(method), NativeUnicodeString(localeName),
			ignoreUserOverride ? TRUE : FALSE, &sub)).IsFailure)
		{
			return nullptr;
		}
		return NumberSubstitution::FromPointer(sub);
	}

	RenderingParameters ^Factory::CreateRenderingParameters()
	{
		IDWriteRenderingParams *params = 0;
		if (RECORD_DW(InternalPointer->CreateRenderingParams(&params)).IsFailure)
		{
			return nullptr;
		}
		return RenderingParameters::FromPointer(params);
	}

	TextAnalyzer ^Factory::CreateTextAnalyzer()
	{
		IDWriteTextAnalyzer *analyzer = 0;
		if (RECORD_DW(InternalPointer->CreateTextAnalyzer(&analyzer)).IsFailure)
		{
			return nullptr;
		}
		return TextAnalyzer::FromPointer(analyzer);
	}
}
}
