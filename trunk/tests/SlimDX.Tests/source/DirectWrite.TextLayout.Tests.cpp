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

#include "IDWriteTextLayoutMock.h"

using namespace testing;
using namespace System;
using namespace SlimDX;
using namespace SlimDX::DirectWrite;

TEST(TextLayoutTests, GetClusterMetrics)
{
	IDWriteTextLayoutMock mockLayout;
	TextLayout ^layout = TextLayout::FromPointer(System::IntPtr(&mockLayout));
	EXPECT_CALL(mockLayout, GetClusterMetrics(_, _, _))
		.WillRepeatedly(Return(E_UNEXPECTED));
	EXPECT_CALL(mockLayout, GetClusterMetrics(0, 0, NotNull()))
		.WillOnce(DoAll(
			SetArgumentPointee<2>(1),
			Return(HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER))
		));
	DWRITE_CLUSTER_METRICS expectedMetrics;
	expectedMetrics.width = 15.0f;
	expectedMetrics.length = 1;
	expectedMetrics.canWrapLineAfter = 0;
	expectedMetrics.isWhitespace = 0;
	expectedMetrics.isNewline = 0;
	expectedMetrics.isSoftHyphen = 0;
	expectedMetrics.isRightToLeft = 0;
	EXPECT_CALL(mockLayout, GetClusterMetrics(NotNull(), Gt(0U), NotNull()))
		.WillOnce(DoAll(
			SetArgumentPointee<0>(expectedMetrics),
			SetArgumentPointee<2>(1),
			Return(S_OK)
		));
	array<SlimDX::DirectWrite::ClusterMetrics>^ metrics = layout->GetClusterMetrics();
	ASSERT_TRUE( Result::Last.IsSuccess );
	ASSERT_TRUE( metrics != nullptr );
	ASSERT_EQ( 1, metrics->Length );
	ASSERT_EQ( 15.0f, metrics[0].Width );
	ASSERT_EQ( 1, metrics[0].Length );
	ASSERT_FALSE( metrics[0].CanWrapLineAfter );
	ASSERT_FALSE( metrics[0].IsWhitespace );
	ASSERT_FALSE( metrics[0].IsNewline );
	ASSERT_FALSE( metrics[0].IsSoftHyphen );
	ASSERT_FALSE( metrics[0].IsRightToLeft );
}

TEST(TextLayoutTests, DetermineMinWidth)
{
	IDWriteTextLayoutMock mockLayout;
	TextLayout ^layout = TextLayout::FromPointer(System::IntPtr(&mockLayout));
	EXPECT_CALL(mockLayout, DetermineMinWidth(NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<0>(14.5f), Return(S_OK)));
	float minWidth = -1.0f;
	ASSERT_EQ( 14.5f, layout->DetermineMinWidth() );
}

static DWRITE_HIT_TEST_METRICS ExpectedHitTestMetrics()
{
	DWRITE_HIT_TEST_METRICS expectedMetrics;
	expectedMetrics.textPosition = 0;
	expectedMetrics.length = 1;
	expectedMetrics.left = 0.15f;
	expectedMetrics.top = 0.245f;
	expectedMetrics.width = 45.8f;
	expectedMetrics.height = 998.5f;
	expectedMetrics.bidiLevel = 23;
	expectedMetrics.isText = TRUE;
	expectedMetrics.isTrimmed = TRUE;
	return expectedMetrics;
}

static void AssertHitTestMetricsMatchExpected(HitTestMetrics% actual)
{
	DWRITE_HIT_TEST_METRICS expected = ExpectedHitTestMetrics();
	ASSERT_EQ( expected.textPosition, actual.TextPosition );
	ASSERT_EQ( expected.length, actual.Length );
	ASSERT_EQ( expected.left, actual.Left );
	ASSERT_EQ( expected.top, actual.Top );
	ASSERT_EQ( expected.width, actual.Width );
	ASSERT_EQ( expected.height, actual.Height );
	ASSERT_EQ( expected.bidiLevel, actual.BidiLevel );
	ASSERT_EQ( expected.isText == TRUE, actual.IsText );
	ASSERT_EQ( expected.isTrimmed == TRUE, actual.IsTrimmed );
}

TEST(TextLayoutTests, HitTestPoint)
{
	IDWriteTextLayoutMock mockLayout;
	TextLayout ^layout = TextLayout::FromPointer(System::IntPtr(&mockLayout));
	EXPECT_CALL(mockLayout, HitTestPoint(10.0f, 12.0f, NotNull(), NotNull(), NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<2>(false),
						SetArgumentPointee<3>(false),
						SetArgumentPointee<4>(ExpectedHitTestMetrics()),
						Return(S_OK)));
	bool isTrailingHit = true;
	bool isInside = true;
	HitTestMetrics metrics = layout->HitTestPoint(10.0f, 12.0f, isTrailingHit, isInside);
	ASSERT_TRUE( Result::Last.IsSuccess );
	ASSERT_FALSE( isTrailingHit );
	ASSERT_FALSE( isInside );
	AssertHitTestMetricsMatchExpected(metrics);
}

TEST(TextLayoutTests, HitTestTextPosition)
{
	IDWriteTextLayoutMock mockLayout;
	TextLayout ^layout = TextLayout::FromPointer(System::IntPtr(&mockLayout));
	EXPECT_CALL(mockLayout, HitTestTextPosition(12U, FALSE, NotNull(), NotNull(), NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<2>(12.5f),
		SetArgumentPointee<3>(13.5f),
		SetArgumentPointee<4>(ExpectedHitTestMetrics()),
		Return(S_OK)));
	float x, y;
	HitTestMetrics metrics = layout->HitTestTextPosition(12U, false, x, y);
	ASSERT_TRUE( Result::Last.IsSuccess );
	ASSERT_EQ( 12.5f, x );
	ASSERT_EQ( 13.5f, y );
	AssertHitTestMetricsMatchExpected(metrics);
}
