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

#include "Asserts.h"
#include "IDWriteFontMock.h"
#include "IDWriteFontFaceMock.h"

using namespace testing;
using namespace System;
using namespace SlimDX;
using namespace SlimDX::DirectWrite;

TEST(FontTests, CreateFontFaceErrorThrowsSlimDXException)
{
	IDWriteFontMock mockFont;
	Font ^font = Font::FromPointer(System::IntPtr(&mockFont));
	EXPECT_CALL(mockFont, CreateFontFace(NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<0>(static_cast<IDWriteFontFace *>(0)),
						Return(E_UNEXPECTED)));
	FontFace ^face;
	ASSERT_MANAGED_THROW( face = font->CreateFontFace(), SlimDXException );
}

TEST(FontTests, CreateFontFaceOK)
{
	IDWriteFontMock mockFont;
	Font ^font = Font::FromPointer(System::IntPtr(&mockFont));
	IDWriteFontFaceMock mockFace;
	EXPECT_CALL(mockFont, CreateFontFace(NotNull()))
		.Times(1)
		.WillOnce(DoAll(SetArgumentPointee<0>(&mockFace),
						Return(S_OK)));
	FontFace ^face = font->CreateFontFace();
	ASSERT_TRUE( nullptr != face );
	ASSERT_EQ( &mockFace, face->InternalPointer );
}
