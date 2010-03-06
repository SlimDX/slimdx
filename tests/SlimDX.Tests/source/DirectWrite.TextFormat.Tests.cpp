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

#include "CommonMocks.h"
#include "IDWriteFontCollectionMock.h"
#include "SlimDXTest.h"

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
	MOCK_METHOD1_WITH_CALLTYPE( STDMETHODCALLTYPE, SetIncrementalTabStop, HRESULT(FLOAT) );
	STDMETHOD(SetTrimming)(DWRITE_TRIMMING const* trimmingOptions, IDWriteInlineObject* trimmingSign) { return E_NOTIMPL; }
	MOCK_METHOD3_WITH_CALLTYPE( STDMETHODCALLTYPE, SetLineSpacing, HRESULT(DWRITE_LINE_SPACING_METHOD, FLOAT, FLOAT) );
	STDMETHOD_(DWRITE_TEXT_ALIGNMENT, GetTextAlignment)() { return DWRITE_TEXT_ALIGNMENT(-1); }
	STDMETHOD_(DWRITE_PARAGRAPH_ALIGNMENT, GetParagraphAlignment)() { return DWRITE_PARAGRAPH_ALIGNMENT(-1); }
	STDMETHOD_(DWRITE_WORD_WRAPPING, GetWordWrapping)() { return DWRITE_WORD_WRAPPING(-1); }
	STDMETHOD_(DWRITE_READING_DIRECTION, GetReadingDirection)() { return DWRITE_READING_DIRECTION(-1); }
	MOCK_METHOD0_WITH_CALLTYPE( STDMETHODCALLTYPE, GetFlowDirection, DWRITE_FLOW_DIRECTION() );
	MOCK_METHOD0_WITH_CALLTYPE( STDMETHODCALLTYPE, GetIncrementalTabStop, FLOAT() );
	STDMETHOD(GetTrimming)(DWRITE_TRIMMING* trimmingOptions, IDWriteInlineObject** trimmingSign) { return E_NOTIMPL; }
	MOCK_METHOD3_WITH_CALLTYPE( STDMETHODCALLTYPE, GetLineSpacing, HRESULT(DWRITE_LINE_SPACING_METHOD*, FLOAT*, FLOAT*) );
	MOCK_METHOD1_WITH_CALLTYPE( STDMETHODCALLTYPE, GetFontCollection, HRESULT(IDWriteFontCollection**) );
	MOCK_METHOD0_WITH_CALLTYPE( STDMETHODCALLTYPE, GetFontFamilyNameLength, UINT32() );
	MOCK_METHOD2_WITH_CALLTYPE( STDMETHODCALLTYPE, GetFontFamilyName, HRESULT(WCHAR*, UINT32) );
	MOCK_METHOD0_WITH_CALLTYPE( STDMETHODCALLTYPE, GetFontWeight, DWRITE_FONT_WEIGHT() );
	MOCK_METHOD0_WITH_CALLTYPE( STDMETHODCALLTYPE, GetFontStyle, DWRITE_FONT_STYLE() );
	MOCK_METHOD0_WITH_CALLTYPE( STDMETHODCALLTYPE, GetFontStretch, DWRITE_FONT_STRETCH() );
	MOCK_METHOD0_WITH_CALLTYPE( STDMETHODCALLTYPE, GetFontSize, FLOAT() );
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

TEST_F(TextFormatTest, GetFontCollection)
{
	MockedTextFormat format;
	IDWriteFontCollectionMock mockCollection;
	EXPECT_CALL(format.Mock, GetFontCollection(NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<0>(&mockCollection), Return(S_OK)));
	FontCollection ^collection = format.Format->FontCollection;
	AssertLastResultSucceeded();
	ASSERT_TRUE(collection != nullptr);
	ASSERT_EQ(&mockCollection, collection->InternalPointer);
	delete collection;
}

TEST_F(TextFormatTest, GetFontCollectionFailureReturnsNullPtr)
{
	MockedTextFormat format;
	EXPECT_CALL(format.Mock, GetFontCollection(NotNull()))
		.Times(1)
		.WillOnce(Return(E_FAIL));
	SlimDX::Configuration::ThrowOnError = false;
	FontCollection ^collection = format.Format->FontCollection;
	AssertLastResultFailed();
	ASSERT_TRUE(collection == nullptr);
}

TEST_F(TextFormatTest, GetFontFamilyName)
{
	MockedTextFormat format;
	WCHAR const fakeName[] = L"Slartibartfast";
	UINT32 const fakeNameLength = NUM_OF(fakeName);
	EXPECT_CALL(format.Mock, GetFontFamilyNameLength())
		.Times(1)
		.WillOnce(Return(fakeNameLength - 1));
	EXPECT_CALL(format.Mock, GetFontFamilyName(NotNull(), Gt(0U)))
		.Times(1)
		.WillOnce(DoAll(SetArrayArgument<0>(&fakeName[0], &fakeName[fakeNameLength]),
						Return(S_OK)));
	String ^name = format.Format->FontFamilyName;
	AssertLastResultSucceeded();
	ASSERT_TRUE(!String::IsNullOrEmpty(name));
}

TEST_F(TextFormatTest, GetFontFamilyNameFailureReturnsEmptyString)
{
	MockedTextFormat format;
	WCHAR const fakeName[] = L"Slartibartfast";
	UINT32 const fakeNameLength = NUM_OF(fakeName);
	EXPECT_CALL(format.Mock, GetFontFamilyNameLength())
		.Times(1)
		.WillOnce(Return(fakeNameLength - 1));
	EXPECT_CALL(format.Mock, GetFontFamilyName(NotNull(), Gt(0U)))
		.Times(1)
		.WillOnce(Return(E_FAIL));
	SlimDX::Configuration::ThrowOnError = false;
	String ^name = format.Format->FontFamilyName;
	AssertLastResultFailed();
	ASSERT_TRUE(String::Empty == name);
}

TEST_F(TextFormatTest, GetFontSize)
{
	MockedTextFormat format;
	EXPECT_CALL(format.Mock, GetFontSize())
		.Times(1)
		.WillOnce(Return(45.4f));
	ASSERT_EQ(45.4f, format.Format->FontSize);
}

TEST_F(TextFormatTest, GetFontStretch)
{
	MockedTextFormat format;
	EXPECT_CALL(format.Mock, GetFontStretch())
		.Times(1)
		.WillOnce(Return(DWRITE_FONT_STRETCH_ULTRA_EXPANDED));
	ASSERT_EQ(FontStretch::UltraExpanded, format.Format->FontStretch);
}

TEST_F(TextFormatTest, GetFontStyle)
{
	MockedTextFormat format;
	EXPECT_CALL(format.Mock, GetFontStyle())
		.Times(1)
		.WillOnce(Return(DWRITE_FONT_STYLE_ITALIC));
	ASSERT_EQ(FontStyle::Italic, format.Format->FontStyle);
}

TEST_F(TextFormatTest, GetFontWeight)
{
	MockedTextFormat format;
	EXPECT_CALL(format.Mock, GetFontWeight())
		.Times(1)
		.WillOnce(Return(DWRITE_FONT_WEIGHT_ULTRA_BOLD));
	ASSERT_EQ(FontWeight::UltraBold, format.Format->FontWeight);
}

TEST_F(TextFormatTest, GetIncrementalTabStop)
{
	MockedTextFormat format;
	EXPECT_CALL(format.Mock, GetIncrementalTabStop())
		.Times(1)
		.WillOnce(Return(45.5f));
	ASSERT_EQ(45.5f, format.Format->IncrementalTabStop);
}

TEST_F(TextFormatTest, SetIncrementalTabStop)
{
	MockedTextFormat format;
	EXPECT_CALL(format.Mock, SetIncrementalTabStop(45.5f))
		.Times(1)
		.WillOnce(Return(S_OK));
	format.Format->IncrementalTabStop = 45.5f;
	AssertLastResultSucceeded();
}

static std::ostream &operator<<(std::ostream &stream, LineSpacingMethod method)
{
	return stream << method.ToString();
}

TEST_F(TextFormatTest, GetLineSpacing)
{
	MockedTextFormat format;
	EXPECT_CALL(format.Mock, GetLineSpacing(NotNull(), NotNull(), NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<0>(DWRITE_LINE_SPACING_METHOD_UNIFORM),
						SetArgumentPointee<1>(12.5f),
						SetArgumentPointee<2>(14.8f),
						Return(S_OK)));
	LineSpacingMethod method;
	float lineSpacing, baseline;
	ASSERT_TRUE(format.Format->GetLineSpacing(method, lineSpacing, baseline).IsSuccess);
	ASSERT_EQ(LineSpacingMethod::Uniform, method);
	ASSERT_EQ(12.5f, lineSpacing);
	ASSERT_EQ(14.8f, baseline);
}

TEST_F(TextFormatTest, SetLineSpacing)
{
	MockedTextFormat format;
	EXPECT_CALL(format.Mock, SetLineSpacing(DWRITE_LINE_SPACING_METHOD_UNIFORM, 12.5f, 14.8f))
		.Times(1)
		.WillOnce(Return(S_OK));
	ASSERT_TRUE(format.Format->SetLineSpacing(LineSpacingMethod::Uniform, 12.5f, 14.8f).IsSuccess);
}
