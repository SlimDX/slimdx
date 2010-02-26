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
			SetArrayArgument<0>(&expectedMetrics, &expectedMetrics + 1),
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

TEST(TextLayoutTests, GetMinWidth)
{
	IDWriteTextLayoutMock mockLayout;
	TextLayout ^layout = TextLayout::FromPointer(System::IntPtr(&mockLayout));
	EXPECT_CALL(mockLayout, DetermineMinWidth(NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<0>(14.5f), Return(S_OK)));
	float minWidth = -1.0f;
	ASSERT_EQ( 14.5f, layout->MinWidth );
}
