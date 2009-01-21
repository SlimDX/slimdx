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

#include "Factory.h"
#include "TextFormat.h"
#include "TextRange.h"

extern const IID IID_IDWriteTextLayout;

namespace SlimDX
{
	namespace DirectWrite
	{
		public ref class TextLayout : public ComObject
		{
			COMOBJECT(IDWriteTextLayout, TextLayout);

			void Init( Factory^ factory, System::String^ text, TextFormat^ format, float maxWidth, float maxHeight );

		public:
			TextLayout( Factory^ factory, System::String^ text, TextFormat^ format );
			TextLayout( Factory^ factory, System::String^ text, TextFormat^ format, float maxWidth, float maxHeight );

			static TextLayout^ FromPointer( System::IntPtr pointer );

			Result SetFontSize( float size, TextRange range );
			Result SetUnderline( bool underline, TextRange range );
			Result SetFontWeight( FontWeight weight, TextRange range );
		};
	}
}