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
#include "IDWriteTextLayoutMockGetters.h"
#include "TextLayoutTest.h"

using namespace testing;
using namespace SlimDX::DirectWrite;
using namespace System;

ref class MockedTextLayoutGetters
{
public:
	MockedTextLayoutGetters()
		: mockLayout(new IDWriteTextLayoutMockGetters),
		layout(TextLayout::FromPointer(System::IntPtr(mockLayout))),
		throwOnError(SlimDX::Configuration::ThrowOnError)
	{
	}
	~MockedTextLayoutGetters()
	{
		SlimDX::Configuration::ThrowOnError = throwOnError;
		delete layout;
		layout = nullptr;
		delete mockLayout;
		mockLayout = 0;
	}
	property IDWriteTextLayoutMockGetters &Mock
	{
		IDWriteTextLayoutMockGetters &get() { return *mockLayout; }
	}
	property TextLayout ^Layout
	{
		TextLayout ^get() { return layout; }
	}

private:
	bool const throwOnError;
	IDWriteTextLayoutMockGetters *mockLayout;
	TextLayout ^layout;
};

static DWRITE_CLUSTER_METRICS ExpectedClusterMetrics()
{
	DWRITE_CLUSTER_METRICS expectedMetrics;
	expectedMetrics.width = 15.0f;
	expectedMetrics.length = 1;
	expectedMetrics.canWrapLineAfter = 0;
	expectedMetrics.isWhitespace = 0;
	expectedMetrics.isNewline = 0;
	expectedMetrics.isSoftHyphen = 0;
	expectedMetrics.isRightToLeft = 0;
	return expectedMetrics;
}

static void AssertClusterMetricsMatchExpected(ClusterMetrics metrics)
{
	DWRITE_CLUSTER_METRICS expected = ExpectedClusterMetrics();
	ASSERT_EQ(expected.width, metrics.Width);
	ASSERT_EQ(expected.length, metrics.Length);
	ASSERT_EQ(expected.canWrapLineAfter != 0, metrics.CanWrapLineAfter);
	ASSERT_EQ(expected.isWhitespace != 0, metrics.IsWhitespace);
	ASSERT_EQ(expected.isNewline != 0, metrics.IsNewline);
	ASSERT_EQ(expected.isSoftHyphen != 0, metrics.IsSoftHyphen);
	ASSERT_EQ(expected.isRightToLeft != 0, metrics.IsRightToLeft);
}

TEST_F(TextLayoutTest, GetClusterMetrics)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetClusterMetrics(_, _, _))
		.WillRepeatedly(Return(E_UNEXPECTED));
	EXPECT_CALL(layout.Mock, GetClusterMetrics(0, 0, NotNull()))
		.WillOnce(DoAll(SetArgumentPointee<2>(1), Return(E_NOT_SUFFICIENT_BUFFER)));
	EXPECT_CALL(layout.Mock, GetClusterMetrics(NotNull(), Gt(0U), NotNull()))
		.WillOnce(DoAll(SetArgumentPointee<0>(ExpectedClusterMetrics()),
		SetArgumentPointee<2>(1),
		Return(S_OK)));
	array<SlimDX::DirectWrite::ClusterMetrics>^ metrics = layout.Layout->GetClusterMetrics();
	AssertLastResultSucceeded();
	ASSERT_TRUE(metrics != nullptr);
	ASSERT_EQ(1, metrics->Length);
	AssertClusterMetricsMatchExpected(metrics[0]);
}

TEST_F(TextLayoutTest, GetFontCollectionNoTextRange)
{
	MockedTextLayoutGetters layout;
	IDWriteFontCollectionMock mockCollection;
	EXPECT_CALL(layout.Mock, GetFontCollection(0, NotNull(), 0))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<1>(&mockCollection), Return(S_OK)));
	FontCollection ^collection = layout.Layout->GetFontCollection(0);
	AssertLastResultSucceeded();
	ASSERT_TRUE(collection != nullptr);
	ASSERT_EQ(collection->InternalPointer, &mockCollection);
	delete collection;
}

TEST_F(TextLayoutTest, GetFontCollectionWithTextRange)
{
	MockedTextLayoutGetters layout;
	IDWriteFontCollectionMock mockCollection;
	EXPECT_CALL(layout.Mock, GetFontCollection(0, NotNull(), NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<1>(&mockCollection),
		SetArgumentPointee<2>(ExpectedTextRange()),
		Return(S_OK)));
	TextRange textRange;
	FontCollection ^collection = layout.Layout->GetFontCollection(0, textRange);
	AssertLastResultSucceeded();
	ASSERT_TRUE(collection != nullptr);
	ASSERT_EQ(collection->InternalPointer, &mockCollection);
	AssertTextRangeMatchesExpected(textRange);
	delete collection;
}

#define NUM_OF(ary_) (sizeof(ary_)/sizeof(ary_[0]))

TEST_F(TextLayoutTest, GetFontFamilyNameNoTextRange)
{
	MockedTextLayoutGetters layout;
	WCHAR fakeName[] = L"Slartibartfast";
	int const numFakeName = NUM_OF(fakeName);
	EXPECT_CALL(layout.Mock, GetFontFamilyNameLength(0, NotNull(), 0))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<1>(numFakeName), Return(S_OK)));
	EXPECT_CALL(layout.Mock, GetFontFamilyName(0, NotNull(), numFakeName, 0))
		.Times(1)
		.WillOnce(DoAll(SetArrayArgument<1>(&fakeName[0], &fakeName[numFakeName]),
		Return(S_OK)));
	String^ name = layout.Layout->GetFontFamilyName(0);
	AssertLastResultSucceeded();
	ASSERT_TRUE(name != nullptr);
	ASSERT_TRUE(gcnew String(fakeName) == name);
}

TEST_F(TextLayoutTest, GetFontFamilyNameWithTextRange)
{
	MockedTextLayoutGetters layout;
	WCHAR fakeName[] = L"Slartibartfast";
	int const numFakeName = NUM_OF(fakeName);
	EXPECT_CALL(layout.Mock, GetFontFamilyNameLength(0, NotNull(), NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<1>(numFakeName), Return(S_OK)));
	EXPECT_CALL(layout.Mock, GetFontFamilyName(0, NotNull(), numFakeName, NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArrayArgument<1>(&fakeName[0], &fakeName[numFakeName]),
		SetArgumentPointee<3>(ExpectedTextRange()),
		Return(S_OK)));
	TextRange range;
	String^ name = layout.Layout->GetFontFamilyName(0, range);
	AssertLastResultSucceeded();
	ASSERT_TRUE(name != nullptr);
	ASSERT_TRUE(gcnew String("Slartibartfast") == name);
	AssertTextRangeMatchesExpected(range);
}

TEST_F(TextLayoutTest, GetFontSizeNoTextRange)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetFontSize(0U, NotNull(), 0))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<1>(14.5f), Return(S_OK)));
	ASSERT_EQ(14.5f, layout.Layout->GetFontSize(0));
	AssertLastResultSucceeded();
}

TEST_F(TextLayoutTest, GetFontSizeWithTextRange)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetFontSize(0U, NotNull(), NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<1>(14.5f),
		SetArgumentPointee<2>(ExpectedTextRange()),
		Return(S_OK)));
	TextRange textRange;
	ASSERT_EQ(14.5f, layout.Layout->GetFontSize(0, textRange));
	AssertLastResultSucceeded();
	AssertTextRangeMatchesExpected(textRange);
}

TEST_F(TextLayoutTest, GetFontStretchNoTextRange)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetFontStretch(0U, NotNull(), 0))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<1>(DWRITE_FONT_STRETCH_ULTRA_EXPANDED), Return(S_OK)));
	ASSERT_EQ(FontStretch::UltraExpanded, layout.Layout->GetFontStretch(0));
	AssertLastResultSucceeded();
}

TEST_F(TextLayoutTest, GetFontStretchFailureReturnsUndefined)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetFontStretch(0U, NotNull(), 0))
		.Times(1)
		.WillOnce(Return(E_FAIL));
	SlimDX::Configuration::ThrowOnError = false;
	ASSERT_EQ(FontStretch::Undefined, layout.Layout->GetFontStretch(0));
	AssertLastResultFailed();
}

TEST_F(TextLayoutTest, GetFontStretchWithTextRange)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetFontStretch(0U, NotNull(), NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<1>(DWRITE_FONT_STRETCH_ULTRA_EXPANDED),
		SetArgumentPointee<2>(ExpectedTextRange()),
		Return(S_OK)));
	TextRange textRange;
	ASSERT_EQ(FontStretch::UltraExpanded, layout.Layout->GetFontStretch(0, textRange));
	AssertLastResultSucceeded();
	AssertTextRangeMatchesExpected(textRange);
}

TEST_F(TextLayoutTest, GetFontStretchWithTextRangeFailureReturnsUndefined)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetFontStretch(0U, NotNull(), NotNull()))
		.Times(1)
		.WillOnce(Return(E_FAIL));
	SlimDX::Configuration::ThrowOnError = false;
	TextRange textRange;
	ASSERT_EQ(FontStretch::Undefined, layout.Layout->GetFontStretch(0, textRange));
	AssertLastResultFailed();
}

TEST_F(TextLayoutTest, GetFontStyleFailureReturnsMinusOne)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetFontStyle(0U, NotNull(), 0))
		.Times(1)
		.WillOnce(Return(E_FAIL));
	SlimDX::Configuration::ThrowOnError = false;
	ASSERT_EQ(-1, static_cast<int>(layout.Layout->GetFontStyle(0)));
	AssertLastResultFailed();
}

TEST_F(TextLayoutTest, GetFontStyleNoTextRange)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetFontStyle(0U, NotNull(), 0))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<1>(DWRITE_FONT_STYLE_NORMAL), Return(S_OK)));
	ASSERT_EQ(FontStyle::Normal, layout.Layout->GetFontStyle(0));
	AssertLastResultSucceeded();
}

TEST_F(TextLayoutTest, GetFontStyleWithTextRange)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetFontStyle(0U, NotNull(), NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<1>(DWRITE_FONT_STYLE_NORMAL),
		SetArgumentPointee<2>(ExpectedTextRange()),
		Return(S_OK)));
	TextRange textRange;
	ASSERT_EQ(FontStyle::Normal, layout.Layout->GetFontStyle(0, textRange));
	AssertLastResultSucceeded();
	AssertTextRangeMatchesExpected(textRange);
}

TEST_F(TextLayoutTest, GetFontWeightNoTextRange)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetFontWeight(0U, NotNull(), 0))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<1>(DWRITE_FONT_WEIGHT_ULTRA_BOLD),
		Return(S_OK)));
	ASSERT_EQ(FontWeight::UltraBold, layout.Layout->GetFontWeight(0));
	AssertLastResultSucceeded();
}

TEST_F(TextLayoutTest, GetFontWeightNoTextRangeFailureReturnsMinusOne)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetFontWeight(0U, NotNull(), 0))
		.Times(1)
		.WillOnce(Return(E_FAIL));
	SlimDX::Configuration::ThrowOnError = false;
	ASSERT_EQ(FontWeight(-1), layout.Layout->GetFontWeight(0));
	AssertLastResultFailed();
}

TEST_F(TextLayoutTest, GetFontWeightWithTextRange)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetFontWeight(0U, NotNull(), NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<1>(DWRITE_FONT_WEIGHT_ULTRA_BOLD),
		SetArgumentPointee<2>(ExpectedTextRange()),
		Return(S_OK)));
	TextRange range;
	ASSERT_EQ(FontWeight::UltraBold, layout.Layout->GetFontWeight(0, range));
	AssertLastResultSucceeded();
	AssertTextRangeMatchesExpected(range);
}

static DWRITE_LINE_METRICS ExpectedLineMetrics()
{
	DWRITE_LINE_METRICS const expected =
	{
		11, 13, 17, 333.0f, 123.f, TRUE
	};
	return expected;
}

static void AssertLineMetricsMatchExpected(LineMetrics metrics)
{
	DWRITE_LINE_METRICS expected = ExpectedLineMetrics();
	ASSERT_EQ(metrics.Baseline, expected.baseline);
	ASSERT_EQ(metrics.Height, expected.height);
	ASSERT_EQ(metrics.Length, expected.length);
	ASSERT_EQ(metrics.NewlineLength, expected.newlineLength);
	ASSERT_EQ(metrics.TrailingWhitespaceLength, expected.trailingWhitespaceLength);
}

TEST_F(TextLayoutTest, GetLineMetrics)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetLineMetrics(0, 0, NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<2>(1), Return(E_NOT_SUFFICIENT_BUFFER)));
	EXPECT_CALL(layout.Mock, GetLineMetrics(NotNull(), 1, NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<0>(ExpectedLineMetrics()),
		SetArgumentPointee<2>(1),
		Return(S_OK)));
	array<LineMetrics> ^metrics = layout.Layout->GetLineMetrics();
	AssertLastResultSucceeded();
	ASSERT_TRUE(metrics != nullptr);
	ASSERT_EQ(1, metrics->Length);
	AssertLineMetricsMatchExpected(metrics[0]);
}

static DWRITE_TEXT_METRICS ExpectedTextMetrics()
{
	DWRITE_TEXT_METRICS expected =
	{
	};
	return expected;
}

static void AssertTextMetricsMatchExpected(TextMetrics %metrics)
{
	DWRITE_TEXT_METRICS expected = ExpectedTextMetrics();
	ASSERT_EQ(expected.height, metrics.Height);
	ASSERT_EQ(expected.layoutHeight, metrics.LayoutHeight);
	ASSERT_EQ(expected.layoutWidth, metrics.LayoutWidth);
	ASSERT_EQ(expected.left, metrics.Left);
	ASSERT_EQ(expected.lineCount, metrics.LineCount);
	ASSERT_EQ(expected.maxBidiReorderingDepth, metrics.MaximumBidiReorderingDepth);
	ASSERT_EQ(expected.top, metrics.Top);
	ASSERT_EQ(expected.width, metrics.Width);
	ASSERT_EQ(expected.widthIncludingTrailingWhitespace, metrics.WidthIncludingTrailingWhitespace);
}

TEST_F(TextLayoutTest, Metrics)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetMetrics(NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<0>(ExpectedTextMetrics()), Return(S_OK)));
	AssertTextMetricsMatchExpected(layout.Layout->Metrics);
	AssertLastResultSucceeded();
}

static DWRITE_OVERHANG_METRICS ExpectedOverhangMetrics()
{
	DWRITE_OVERHANG_METRICS expected;
	expected.left = 23;
	expected.top = 456;
	expected.right = 1256;
	expected.bottom = 20;
	return expected;
}

static void AssertOverhangMetricsMatchExpected(OverhangMetrics %metrics)
{
	DWRITE_OVERHANG_METRICS expected = ExpectedOverhangMetrics();
	ASSERT_EQ(expected.left, metrics.Left);
	ASSERT_EQ(expected.top, metrics.Top);
	ASSERT_EQ(expected.right, metrics.Right);
	ASSERT_EQ(expected.bottom, metrics.Bottom);
}

TEST_F(TextLayoutTest, OverhangMetrics)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetOverhangMetrics(NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<0>(ExpectedOverhangMetrics()), Return(S_OK)));
	AssertOverhangMetricsMatchExpected(layout.Layout->OverhangMetrics);
	AssertLastResultSucceeded();
}

TEST_F(TextLayoutTest, OverhangMetricsReturnsZeroOnFailure)
{
	MockedTextLayoutGetters layout;
	EXPECT_CALL(layout.Mock, GetOverhangMetrics(NotNull()))
		.Times(1)
		.WillOnce(Return(E_FAIL));
	SlimDX::Configuration::ThrowOnError = false;
	OverhangMetrics metrics = layout.Layout->OverhangMetrics;
	AssertLastResultFailed();
	ASSERT_EQ(0, metrics.Left);
	ASSERT_EQ(0, metrics.Right);
	ASSERT_EQ(0, metrics.Top);
	ASSERT_EQ(0, metrics.Bottom);
}

TEST_F(TextLayoutTest, GetLocaleNameNoTextRange)
{
	MockedTextLayoutGetters layout;
	WCHAR fakeName[] = L"Slartibartfast";
	int const numFakeName = NUM_OF(fakeName);
	EXPECT_CALL(layout.Mock, GetLocaleNameLength(0, NotNull(), 0))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<1>(numFakeName), Return(S_OK)));
	EXPECT_CALL(layout.Mock, GetLocaleName(0, NotNull(), numFakeName, 0))
		.Times(1)
		.WillOnce(DoAll(SetArrayArgument<1>(&fakeName[0], &fakeName[numFakeName]),
		Return(S_OK)));
	String^ name = layout.Layout->GetLocaleName(0);
	AssertLastResultSucceeded();
	ASSERT_TRUE(name != nullptr);
	ASSERT_EQ(gcnew String(fakeName), name);
}

TEST_F(TextLayoutTest, GetLocaleNameWithTextRange)
{
	MockedTextLayoutGetters layout;
	WCHAR fakeName[] = L"Slartibartfast";
	int const numFakeName = NUM_OF(fakeName);
	EXPECT_CALL(layout.Mock, GetLocaleNameLength(0, NotNull(), 0))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<1>(numFakeName), Return(S_OK)));
	EXPECT_CALL(layout.Mock, GetLocaleName(0, NotNull(), numFakeName, NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArrayArgument<1>(&fakeName[0], &fakeName[numFakeName]),
						SetArgumentPointee<3>(ExpectedTextRange()),
						Return(S_OK)));
	TextRange range;
	String^ name = layout.Layout->GetLocaleName(0, range);
	AssertLastResultSucceeded();
	ASSERT_TRUE(name != nullptr);
	ASSERT_EQ(gcnew String(fakeName), name);
	AssertTextRangeMatchesExpected(range);
}
