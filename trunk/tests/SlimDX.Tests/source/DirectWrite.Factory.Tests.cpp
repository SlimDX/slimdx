#include "stdafx.h"
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

#include "IDWriteFontCollectionMock.h"
#include "IDWriteTextLayoutMock.h"
#include "SlimDXTest.h"

using namespace testing;
using namespace SlimDX;
using namespace SlimDX::Direct2D;
using namespace SlimDX::DirectWrite;
using namespace System;

class IDWriteFactoryMock : public IDWriteFactory
{
public:
	MOCK_IUNKNOWN;

	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, GetSystemFontCollection, HRESULT(IDWriteFontCollection**, BOOL) );
	STDMETHOD(CreateCustomFontCollection)(IDWriteFontCollectionLoader* collectionLoader, void const* collectionKey, UINT32 collectionKeySize, IDWriteFontCollection** fontCollection) { return E_NOTIMPL; } 
	STDMETHOD(RegisterFontCollectionLoader)(IDWriteFontCollectionLoader* fontCollectionLoader) { return E_NOTIMPL; } 
	STDMETHOD(UnregisterFontCollectionLoader)(IDWriteFontCollectionLoader* fontCollectionLoader) { return E_NOTIMPL; } 
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateFontFileReference, HRESULT(WCHAR const*, FILETIME const*, IDWriteFontFile**));
	STDMETHOD(CreateCustomFontFileReference)(void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileLoader* fontFileLoader, IDWriteFontFile** fontFile) { return E_NOTIMPL; } 
	MOCK_METHOD6_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateFontFace, HRESULT(DWRITE_FONT_FACE_TYPE, UINT32, IDWriteFontFile* const*, UINT32, DWRITE_FONT_SIMULATIONS, IDWriteFontFace**));
	STDMETHOD(CreateRenderingParams)(IDWriteRenderingParams** renderingParams) { return E_NOTIMPL; }
	STDMETHOD(CreateMonitorRenderingParams)(HMONITOR monitor, IDWriteRenderingParams** renderingParams) { return E_NOTIMPL; } 
	STDMETHOD(CreateCustomRenderingParams)(FLOAT gamma, FLOAT enhancedContrast, FLOAT clearTypeLevel, DWRITE_PIXEL_GEOMETRY pixelGeometry, DWRITE_RENDERING_MODE renderingMode, IDWriteRenderingParams** renderingParams) { return E_NOTIMPL; }
	STDMETHOD(RegisterFontFileLoader)(IDWriteFontFileLoader* fontFileLoader) { return E_NOTIMPL; } 
	STDMETHOD(UnregisterFontFileLoader)(IDWriteFontFileLoader* fontFileLoader) { return E_NOTIMPL; } 
	STDMETHOD(CreateTextFormat)(WCHAR const* fontFamilyName, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName, IDWriteTextFormat** textFormat) { return E_NOTIMPL; } 
	STDMETHOD(CreateTypography)(IDWriteTypography** typography) { return E_NOTIMPL; } 
	STDMETHOD(GetGdiInterop)(IDWriteGdiInterop** gdiInterop) { return E_NOTIMPL; } 
	STDMETHOD(CreateTextLayout)(WCHAR const* string, UINT32 stringLength, IDWriteTextFormat* textFormat, FLOAT maxWidth, FLOAT maxHeight, IDWriteTextLayout** textLayout) { return E_NOTIMPL; } 
	MOCK_METHOD9_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateGdiCompatibleTextLayout, HRESULT(WCHAR const*, UINT32, IDWriteTextFormat*, FLOAT, FLOAT, FLOAT, DWRITE_MATRIX const*, BOOL, IDWriteTextLayout**) );
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateEllipsisTrimmingSign, HRESULT(IDWriteTextFormat*, IDWriteInlineObject**));
	STDMETHOD(CreateTextAnalyzer)(IDWriteTextAnalyzer** textAnalyzer) { return E_NOTIMPL; }
	STDMETHOD(CreateNumberSubstitution)(DWRITE_NUMBER_SUBSTITUTION_METHOD substitutionMethod, WCHAR const* localeName, BOOL ignoreUserOverride, IDWriteNumberSubstitution** numberSubstitution) { return E_NOTIMPL; }
	MOCK_METHOD8_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateGlyphRunAnalysis, HRESULT(DWRITE_GLYPH_RUN const*, FLOAT, DWRITE_MATRIX const*, DWRITE_RENDERING_MODE, DWRITE_MEASURING_MODE, FLOAT, FLOAT, IDWriteGlyphRunAnalysis**));
};

class IDWriteFontFileFake : public IDWriteFontFile
{
public:
	MOCK_IUNKNOWN;

	STDMETHOD(GetReferenceKey)(void const** fontFileReferenceKey,UINT32* fontFileReferenceKeySize) { return E_NOTIMPL; }
	STDMETHOD(GetLoader)(IDWriteFontFileLoader** fontFileLoader) { return E_NOTIMPL; }
	STDMETHOD(Analyze)(BOOL* isSupportedFontType, DWRITE_FONT_FILE_TYPE* fontFileType, DWRITE_FONT_FACE_TYPE* fontFaceType, UINT32* numberOfFaces) { return E_NOTIMPL; }
};

class IDWriteFontFaceFake : public IDWriteFontFace
{
public:
	MOCK_IUNKNOWN;

	STDMETHOD_(DWRITE_FONT_FACE_TYPE, GetType)() { return DWRITE_FONT_FACE_TYPE(-1); }
	STDMETHOD(GetFiles)(UINT32* numberOfFiles, IDWriteFontFile** fontFiles) { return E_NOTIMPL; }
	STDMETHOD_(UINT32, GetIndex)() { return UINT32(~0U); }
	STDMETHOD_(DWRITE_FONT_SIMULATIONS, GetSimulations)() { return DWRITE_FONT_SIMULATIONS(-1); }
	STDMETHOD_(BOOL, IsSymbolFont)() { return BOOL(-1); }
	STDMETHOD_(void, GetMetrics)(DWRITE_FONT_METRICS* fontFaceMetrics) { }
	STDMETHOD_(UINT16, GetGlyphCount)() { return UINT16(~0U); }
	STDMETHOD(GetDesignGlyphMetrics)(UINT16 const* glyphIndices, UINT32 glyphCount, DWRITE_GLYPH_METRICS* glyphMetrics, BOOL isSideways = FALSE) { return E_NOTIMPL; }
	STDMETHOD(GetGlyphIndices)(UINT32 const* codePoints, UINT32 codePointCount, UINT16* glyphIndices) { return E_NOTIMPL; }
	STDMETHOD(TryGetFontTable)(UINT32 openTypeTableTag, const void** tableData, UINT32* tableSize, void** tableContext, BOOL* exists) { return E_NOTIMPL; }
	STDMETHOD_(void, ReleaseFontTable)(void* tableContext) { }
	STDMETHOD(GetGlyphRunOutline)(FLOAT emSize, UINT16 const* glyphIndices, FLOAT const* glyphAdvances, DWRITE_GLYPH_OFFSET const* glyphOffsets, UINT32 glyphCount, BOOL isSideways, BOOL isRightToLeft, IDWriteGeometrySink* geometrySink) { return E_NOTIMPL; }
	STDMETHOD(GetRecommendedRenderingMode)(FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MEASURING_MODE measuringMode, IDWriteRenderingParams* renderingParams, DWRITE_RENDERING_MODE* renderingMode) { return E_NOTIMPL; }
	STDMETHOD(GetGdiCompatibleMetrics)(FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, DWRITE_FONT_METRICS* fontFaceMetrics) { return E_NOTIMPL; }
	STDMETHOD(GetGdiCompatibleGlyphMetrics)(FLOAT emSize, FLOAT pixelsPerDip, DWRITE_MATRIX const* transform, BOOL useGdiNatural, UINT16 const* glyphIndices, UINT32 glyphCount, DWRITE_GLYPH_METRICS* glyphMetrics, BOOL isSideways = FALSE) { return E_NOTIMPL; }
};

class IDWriteGlyphRunAnalysisFake : public IDWriteGlyphRunAnalysis
{
public:
	MOCK_IUNKNOWN;

	STDMETHOD(GetAlphaTextureBounds)(DWRITE_TEXTURE_TYPE textureType, RECT* textureBounds) { return E_NOTIMPL; }
	STDMETHOD(CreateAlphaTexture)(DWRITE_TEXTURE_TYPE textureType, RECT const* textureBounds, BYTE* alphaValues, UINT32 bufferSize) { return E_NOTIMPL; }
	STDMETHOD(GetAlphaBlendParams)(IDWriteRenderingParams* renderingParams, FLOAT* blendGamma, FLOAT* blendEnhancedContrast, FLOAT* blendClearTypeLevel) { return E_NOTIMPL; }
};

class IDWriteInlineObjectFake : public IDWriteInlineObject
{
public:
	MOCK_IUNKNOWN;

	STDMETHOD(Draw)(void* clientDrawingContext, IDWriteTextRenderer* renderer, FLOAT originX, FLOAT originY, BOOL isSideways, BOOL isRightToLeft, IUnknown* clientDrawingEffect) { return E_NOTIMPL; }
	STDMETHOD(GetMetrics)(DWRITE_INLINE_OBJECT_METRICS* metrics) { return E_NOTIMPL; }
	STDMETHOD(GetOverhangMetrics)(DWRITE_OVERHANG_METRICS* overhangs) { return E_NOTIMPL; }
	STDMETHOD(GetBreakConditions)(DWRITE_BREAK_CONDITION* breakConditionBefore,DWRITE_BREAK_CONDITION* breakConditionAfter) { return E_NOTIMPL; }
};

class IDWriteTextFormatFake : public IDWriteTextFormat
{
public:
	MOCK_IUNKNOWN;

	STDMETHOD(SetTextAlignment)(DWRITE_TEXT_ALIGNMENT textAlignment) { return E_NOTIMPL; }
	STDMETHOD(SetParagraphAlignment)(DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment) { return E_NOTIMPL; }
	STDMETHOD(SetWordWrapping)(DWRITE_WORD_WRAPPING wordWrapping) { return E_NOTIMPL; }
	STDMETHOD(SetReadingDirection)(DWRITE_READING_DIRECTION readingDirection) { return E_NOTIMPL; }
	STDMETHOD(SetFlowDirection)(DWRITE_FLOW_DIRECTION flowDirection) { return E_NOTIMPL; }
	STDMETHOD(SetIncrementalTabStop)(FLOAT incrementalTabStop) { return E_NOTIMPL; }
	STDMETHOD(SetTrimming)(__in DWRITE_TRIMMING const* trimmingOptions,IDWriteInlineObject* trimmingSign) { return E_NOTIMPL; }
	STDMETHOD(SetLineSpacing)(DWRITE_LINE_SPACING_METHOD lineSpacingMethod,FLOAT lineSpacing,FLOAT baseline) { return E_NOTIMPL; }
	STDMETHOD_(DWRITE_TEXT_ALIGNMENT, GetTextAlignment)() { return DWRITE_TEXT_ALIGNMENT(-1); }
	STDMETHOD_(DWRITE_PARAGRAPH_ALIGNMENT, GetParagraphAlignment)() { return DWRITE_PARAGRAPH_ALIGNMENT(-1); }
	STDMETHOD_(DWRITE_WORD_WRAPPING, GetWordWrapping)() { return DWRITE_WORD_WRAPPING(-1); }
	STDMETHOD_(DWRITE_READING_DIRECTION, GetReadingDirection)() { return DWRITE_READING_DIRECTION(-1); }
	STDMETHOD_(DWRITE_FLOW_DIRECTION, GetFlowDirection)() { return DWRITE_FLOW_DIRECTION(-1); }
	STDMETHOD_(FLOAT, GetIncrementalTabStop)() { return -1.0f; }
	STDMETHOD(GetTrimming)(__out DWRITE_TRIMMING* trimmingOptions,__out IDWriteInlineObject** trimmingSign) { return E_NOTIMPL; }
	STDMETHOD(GetLineSpacing)(__out DWRITE_LINE_SPACING_METHOD* lineSpacingMethod,__out FLOAT* lineSpacing,__out FLOAT* baseline) { return E_NOTIMPL; }
	STDMETHOD(GetFontCollection)(__out IDWriteFontCollection** fontCollection) { return E_NOTIMPL; }
	STDMETHOD_(UINT32, GetFontFamilyNameLength)() { return UINT32(~0U); }
	STDMETHOD(GetFontFamilyName)(__out_ecount_z(nameSize) WCHAR* fontFamilyName,UINT32 nameSize) { return E_NOTIMPL; }
	STDMETHOD_(DWRITE_FONT_WEIGHT, GetFontWeight)() { return DWRITE_FONT_WEIGHT(-1); }
	STDMETHOD_(DWRITE_FONT_STYLE, GetFontStyle)() { return DWRITE_FONT_STYLE(-1); }
	STDMETHOD_(DWRITE_FONT_STRETCH, GetFontStretch)() { return DWRITE_FONT_STRETCH(-1); }
	STDMETHOD_(FLOAT, GetFontSize)() { return -1.0f; }
	STDMETHOD_(UINT32, GetLocaleNameLength)() { return UINT32(~0U); }
	STDMETHOD(GetLocaleName)(__out_ecount_z(nameSize) WCHAR* localeName,UINT32 nameSize) { return E_NOTIMPL; }
};

ref class MockedFactory
{
public:
	MockedFactory()
		: mockFactory(new IDWriteFactoryMock),
		font(SlimDX::DirectWrite::Factory::FromPointer(System::IntPtr(mockFactory)))
	{
	}
	~MockedFactory()
	{
		delete font;
		font = nullptr;
		delete mockFactory;
		mockFactory = 0;
	}
	property IDWriteFactoryMock &Mock
	{
		IDWriteFactoryMock &get() { return *mockFactory; }
	}
	property SlimDX::DirectWrite::Factory ^Factory
	{
		SlimDX::DirectWrite::Factory ^get() { return font; }
	}

private:
	IDWriteFactoryMock *mockFactory;
	SlimDX::DirectWrite::Factory ^font;
};

class FactoryTest : public SlimDXTest
{
};

#define FACTORY_TEST(name_) TEST_F(FactoryTest, name_)

FACTORY_TEST(GetSystemFontCollection)
{
	MockedFactory factory;
	IDWriteFontCollectionMock mockCollection;
	EXPECT_CALL(factory.Mock, GetSystemFontCollection(NotNull(), FALSE))
		.Times(1).WillOnce(DoAll(SetArgumentPointee<0>(&mockCollection), Return(S_OK)));
	FontCollection ^collection = factory.Factory->GetSystemFontCollection(false);
	AssertLastResultSucceeded();
	ASSERT_TRUE(collection != nullptr);
	ASSERT_EQ(&mockCollection, collection->InternalPointer);
	delete collection;
}

FACTORY_TEST(GetSystemFontCollectionFailureReturnsNullPtr)
{
	MockedFactory factory;
	EXPECT_CALL(factory.Mock, GetSystemFontCollection(NotNull(), FALSE))
		.Times(1).WillOnce(Return(E_FAIL));
	SlimDX::Configuration::ThrowOnError = false;
	FontCollection ^collection = factory.Factory->GetSystemFontCollection(false);
	AssertLastResultFailed();
	ASSERT_TRUE(collection == nullptr);
}

FACTORY_TEST(CreateGdiCompatibleTextLayout)
{
	MockedFactory factory;
	IDWriteTextLayoutMock mockLayout;
	IDWriteTextFormatFake fakeFormat;
	EXPECT_CALL(factory.Mock, CreateGdiCompatibleTextLayout(NotNull(), Gt(0U), &fakeFormat,
			12.5f, 44.4f, 340.0f, 0, TRUE, NotNull()))
		.Times(1).WillOnce(DoAll(SetArgumentPointee<8>(&mockLayout), Return(S_OK)));
	TextFormat ^textFormat = TextFormat::FromPointer(&fakeFormat);
	TextLayout ^layout = factory.Factory->CreateGdiCompatibleTextLayout(
		gcnew String("Slartibartfast"), textFormat, 12.5, 44.4f, 340.0f, true);
	AssertLastResultSucceeded();
	ASSERT_TRUE(layout != nullptr);
	ASSERT_EQ(&mockLayout, layout->InternalPointer);
	delete textFormat;
	delete layout;
}

FACTORY_TEST(CreateGdiCompatibleTextLayoutFailureReturnsNullPtr)
{
	MockedFactory factory;
	IDWriteTextFormatFake fakeFormat;
	EXPECT_CALL(factory.Mock, CreateGdiCompatibleTextLayout(NotNull(), Gt(0U), &fakeFormat,
		12.5f, 44.4f, 340.0f, 0, TRUE, NotNull()))
		.Times(1).WillOnce(Return(E_FAIL));
	SlimDX::Configuration::ThrowOnError = false;
	TextFormat ^textFormat = TextFormat::FromPointer(&fakeFormat);
	TextLayout ^layout = factory.Factory->CreateGdiCompatibleTextLayout(
		gcnew String("Slartibartfast"), textFormat, 12.5, 44.4f, 340.0f, true);
	AssertLastResultFailed();
	ASSERT_TRUE(layout == nullptr);
	delete textFormat;
}

FACTORY_TEST(CreateEllipsisTrimmingSign)
{
	MockedFactory factory;
	IDWriteTextFormatFake fakeFormat;
	IDWriteInlineObjectFake fakeInlineObject;
	EXPECT_CALL(factory.Mock, CreateEllipsisTrimmingSign(&fakeFormat, NotNull()))
		.Times(1).WillOnce(DoAll(SetArgumentPointee<1>(&fakeInlineObject), Return(S_OK)));
	TextFormat ^format = TextFormat::FromPointer(&fakeFormat);
	InlineObject ^sign = factory.Factory->CreateEllipsisTrimmingSign(format);
	AssertLastResultSucceeded();
	ASSERT_TRUE(nullptr != sign);
	ASSERT_EQ(&fakeInlineObject, sign->InternalPointer);
	delete sign;
	delete format;
}

FACTORY_TEST(CreateEllipsisTrimmingSignFailureReturnsNullPtr)
{
	MockedFactory factory;
	IDWriteTextFormatFake fakeFormat;
	EXPECT_CALL(factory.Mock, CreateEllipsisTrimmingSign(&fakeFormat, NotNull()))
		.Times(1).WillOnce(Return(E_FAIL));
	SlimDX::Configuration::ThrowOnError = false;
	TextFormat ^format = TextFormat::FromPointer(&fakeFormat);
	InlineObject ^sign = factory.Factory->CreateEllipsisTrimmingSign(format);
	AssertLastResultFailed();
	ASSERT_TRUE(nullptr == sign);
	delete format;
}

FACTORY_TEST(CreateFontFace)
{
	MockedFactory factory;
	IDWriteFontFileFake fakeFile;
	IDWriteFontFaceFake fakeFace;
	EXPECT_CALL(factory.Mock, CreateFontFace(DWRITE_FONT_FACE_TYPE_TYPE1,
			1, NotNull(), 0, DWRITE_FONT_SIMULATIONS_OBLIQUE, NotNull()))
		.Times(1).WillOnce(DoAll(SetArgumentPointee<5>(&fakeFace), Return(S_OK)));
	FontFile ^fontFile = FontFile::FromPointer(&fakeFile);
	array<FontFile ^> ^fontFiles = gcnew array<FontFile ^>(1);
	fontFiles[0] = fontFile;
	FontFace ^fontFace = factory.Factory->CreateFontFace(FontFaceType::Type1, fontFiles, 0, FontSimulations::Oblique);
	AssertLastResultSucceeded();
	ASSERT_TRUE(nullptr != fontFace);
	ASSERT_EQ(&fakeFace, fontFace->InternalPointer);
	delete fontFace;
	delete fontFiles;
	delete fontFile;
}

FACTORY_TEST(CreateFontFaceFailureReturnsNullPtr)
{
	MockedFactory factory;
	IDWriteFontFileFake fakeFile;
	EXPECT_CALL(factory.Mock, CreateFontFace(DWRITE_FONT_FACE_TYPE_TYPE1,
		1, NotNull(), 0, DWRITE_FONT_SIMULATIONS_OBLIQUE, NotNull()))
		.Times(1).WillOnce(Return(E_FAIL));
	SlimDX::Configuration::ThrowOnError = false;
	FontFile ^fontFile = FontFile::FromPointer(&fakeFile);
	array<FontFile ^> ^fontFiles = gcnew array<FontFile ^>(1);
	fontFiles[0] = fontFile;
	FontFace ^fontFace = factory.Factory->CreateFontFace(FontFaceType::Type1, fontFiles, 0, FontSimulations::Oblique);
	AssertLastResultFailed();
	ASSERT_TRUE(nullptr == fontFace);
	delete fontFiles;
	delete fontFile;
}

FACTORY_TEST(CreateFontFileReference)
{
	MockedFactory factory;
	IDWriteFontFileFake fakeFile;
	EXPECT_CALL(factory.Mock, CreateFontFileReference(NotNull(), 0, NotNull()))
		.Times(1).WillOnce(DoAll(SetArgumentPointee<2>(&fakeFile), Return(S_OK)));
	FontFile ^file = factory.Factory->CreateFontFileReference(gcnew String("Slartibartfast.fnt"));
	AssertLastResultSucceeded();
	ASSERT_TRUE(file != nullptr);
	ASSERT_EQ(&fakeFile, file->InternalPointer);
	delete file;
}

FACTORY_TEST(CreateFontFileReferenceFailureReturnsNullPtr)
{
	MockedFactory factory;
	EXPECT_CALL(factory.Mock, CreateFontFileReference(NotNull(), 0, NotNull()))
		.Times(1).WillOnce(Return(E_FAIL));
	SlimDX::Configuration::ThrowOnError = false;
	FontFile ^file = factory.Factory->CreateFontFileReference(gcnew String("Slartibartfast.fnt"));
	AssertLastResultFailed();
	ASSERT_TRUE(file == nullptr);
}

static GlyphRun ^CreateGlyphRun(IDWriteFontFaceFake &fakeFace)
{
	GlyphRun ^glyphRun = gcnew GlyphRun;
	glyphRun->FontFace = FontFace::FromPointer(&fakeFace);
	return glyphRun;
}

static void ReleaseGlyphRun(GlyphRun ^glyphRun)
{
	delete glyphRun->FontFace;
	delete glyphRun;
}

FACTORY_TEST(CreateGlyphRunAnalysisFailureReturnsNullPtr)
{
	MockedFactory factory;
	EXPECT_CALL(factory.Mock, CreateGlyphRunAnalysis(NotNull(), 640.0f, 0,
			DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL, DWRITE_MEASURING_MODE_GDI_NATURAL,
			12.5f, 33.3f, NotNull()))
		.Times(1).WillOnce(Return(E_FAIL));
	SlimDX::Configuration::ThrowOnError = false;
	IDWriteFontFaceFake fakeFace;
	GlyphRun ^glyphRun = CreateGlyphRun(fakeFace);
	GlyphRunAnalysis ^analysis = factory.Factory->CreateGlyphRunAnalysis(glyphRun, 640.0f,
		RenderingMode::ClearTypeNatural, MeasuringMode::GdiNatural,
		12.5f, 33.3f);
	AssertLastResultFailed();
	ASSERT_TRUE(analysis == nullptr);
	ReleaseGlyphRun(glyphRun);
}

static Matrix3x2 ExpectedMatrix()
{
	Matrix3x2 matrix;
	matrix.M11 = 1.0f;
	matrix.M12 = 0.0f;
	matrix.M21 = 0.0f;
	matrix.M22 = 1.0f;
	matrix.M31 = 12.5f;
	matrix.M32 = 55.5f;
	return matrix;
}

FACTORY_TEST(CreateGlyphRunAnalysisWithTransform)
{
	MockedFactory factory;
	IDWriteGlyphRunAnalysisFake fakeAnalysis;
	EXPECT_CALL(factory.Mock, CreateGlyphRunAnalysis(NotNull(), 640.0f, NotNull(),
			DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL, DWRITE_MEASURING_MODE_GDI_NATURAL,
			12.5f, 33.3f, NotNull()))
		.Times(1).WillOnce(DoAll(SetArgumentPointee<7>(&fakeAnalysis), Return(S_OK)));
	IDWriteFontFaceFake fakeFace;
	GlyphRun ^glyphRun = CreateGlyphRun(fakeFace);
	GlyphRunAnalysis ^analysis = factory.Factory->CreateGlyphRunAnalysis(glyphRun, 640.0f,
		ExpectedMatrix(), RenderingMode::ClearTypeNatural, MeasuringMode::GdiNatural,
		12.5f, 33.3f);
	AssertLastResultSucceeded();
	ASSERT_TRUE(analysis != nullptr);
	ASSERT_EQ(&fakeAnalysis, analysis->InternalPointer);
	delete analysis;
	ReleaseGlyphRun(glyphRun);
}
