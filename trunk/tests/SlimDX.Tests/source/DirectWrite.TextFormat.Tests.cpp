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
#include <ostream>

#include <dwrite.h>

#include "SlimDXTest.h"
#include "CommonMocks.h"

using namespace testing;
using namespace SlimDX::DirectWrite;
using namespace System;

class IDWriteTextFormatMock : public IDWriteTextFormat
{
public:
	MOCK_IUNKNOWN;

	// IDWriteTextFormat
	STDMETHOD(SetTextAlignment)(DWRITE_TEXT_ALIGNMENT textAlignment) { return E_NOTIMPL; }
	STDMETHOD(SetParagraphAlignment)(DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment) { return E_NOTIMPL; }
	STDMETHOD(SetWordWrapping)(DWRITE_WORD_WRAPPING wordWrapping) { return E_NOTIMPL; }
	STDMETHOD(SetReadingDirection)(DWRITE_READING_DIRECTION readingDirection) { return E_NOTIMPL; }
	MOCK_METHOD1_WITH_CALLTYPE( STDMETHODCALLTYPE, SetFlowDirection, HRESULT(DWRITE_FLOW_DIRECTION) );
	STDMETHOD(SetIncrementalTabStop)(FLOAT incrementalTabStop) { return E_NOTIMPL; }
	STDMETHOD(SetTrimming)(DWRITE_TRIMMING const* trimmingOptions, IDWriteInlineObject* trimmingSign) { return E_NOTIMPL; }
	STDMETHOD(SetLineSpacing)(DWRITE_LINE_SPACING_METHOD lineSpacingMethod, FLOAT lineSpacing, FLOAT baseline) { return E_NOTIMPL; }
	STDMETHOD_(DWRITE_TEXT_ALIGNMENT, GetTextAlignment)() { return DWRITE_TEXT_ALIGNMENT(-1); }
	STDMETHOD_(DWRITE_PARAGRAPH_ALIGNMENT, GetParagraphAlignment)() { return DWRITE_PARAGRAPH_ALIGNMENT(-1); }
	STDMETHOD_(DWRITE_WORD_WRAPPING, GetWordWrapping)() { return DWRITE_WORD_WRAPPING(-1); }
	STDMETHOD_(DWRITE_READING_DIRECTION, GetReadingDirection)() { return DWRITE_READING_DIRECTION(-1); }
	MOCK_METHOD0_WITH_CALLTYPE( STDMETHODCALLTYPE, GetFlowDirection, DWRITE_FLOW_DIRECTION() );
	STDMETHOD_(FLOAT, GetIncrementalTabStop)() { return -1.0f; }
	STDMETHOD(GetTrimming)(DWRITE_TRIMMING* trimmingOptions, IDWriteInlineObject** trimmingSign) { return E_NOTIMPL; }
	STDMETHOD(GetLineSpacing)(DWRITE_LINE_SPACING_METHOD* lineSpacingMethod, FLOAT* lineSpacing, FLOAT* baseline) { return E_NOTIMPL; }
	STDMETHOD(GetFontCollection)(IDWriteFontCollection** fontCollection) { return E_NOTIMPL; }
	STDMETHOD_(UINT32, GetFontFamilyNameLength)() { return ~0U; }
	STDMETHOD(GetFontFamilyName)(WCHAR* fontFamilyName, UINT32 nameSize) { return E_NOTIMPL; }
	STDMETHOD_(DWRITE_FONT_WEIGHT, GetFontWeight)() { return DWRITE_FONT_WEIGHT(-1); }
	STDMETHOD_(DWRITE_FONT_STYLE, GetFontStyle)() { return DWRITE_FONT_STYLE(-1); }
	STDMETHOD_(DWRITE_FONT_STRETCH, GetFontStretch)() { return DWRITE_FONT_STRETCH(-1); }
	STDMETHOD_(FLOAT, GetFontSize)() { return -1.0f; }
	STDMETHOD_(UINT32, GetLocaleNameLength)() { return ~0U; }
	STDMETHOD(GetLocaleName)(WCHAR* localeName, UINT32 nameSize) { return E_NOTIMPL; }
};

ref class MockedTextFormat
{
public:
	MockedTextFormat()
		: mockFormat(new IDWriteTextFormatMock),
		format(TextFormat::FromPointer(System::IntPtr(mockFormat))),
		throwOnError(SlimDX::Configuration::ThrowOnError)
	{
	}
	~MockedTextFormat()
	{
		SlimDX::Configuration::ThrowOnError = throwOnError;
		delete format;
		format = nullptr;
		delete mockFormat;
		mockFormat = 0;
	}
	property IDWriteTextFormatMock &Mock
	{
		IDWriteTextFormatMock &get() { return *mockFormat; }
	}
	property TextFormat ^Format
	{
		TextFormat ^get() { return format; }
	}

private:
	bool const throwOnError;
	IDWriteTextFormatMock *mockFormat;
	TextFormat ^format;
};

class TextFormatTest : public SlimDXTest
{
};

static std::ostream &operator<<(std::ostream &stream, FlowDirection dir)
{
	return stream << dir.ToString();
}

TEST_F(TextFormatTest, GetFlowDirection)
{
	MockedTextFormat format;
	EXPECT_CALL(format.Mock, GetFlowDirection())
		.Times(1)
		.WillOnce(Return(DWRITE_FLOW_DIRECTION_TOP_TO_BOTTOM));
	ASSERT_EQ(FlowDirection::TopToBottom, format.Format->FlowDirection);
	AssertLastResultSucceeded();
}

TEST_F(TextFormatTest, SetFlowDirection)
{
	MockedTextFormat format;
	EXPECT_CALL(format.Mock, SetFlowDirection(DWRITE_FLOW_DIRECTION_TOP_TO_BOTTOM))
		.Times(1)
		.WillOnce(Return(S_OK));
	format.Format->FlowDirection = FlowDirection::TopToBottom;
	AssertLastResultSucceeded();
}
