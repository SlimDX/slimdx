/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include <dwrite.h>
#include <vcclr.h>

#include "DirectWriteException.h"

#include "TextLayout.h"

const IID IID_IDWriteTextLayout = __uuidof(IDWriteTextLayout);

using namespace System;

namespace SlimDX
{
namespace DirectWrite
{
	TextLayout::TextLayout( IDWriteTextLayout* pointer )
	{
		Construct( pointer );
	}

	TextLayout::TextLayout( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	TextLayout::TextLayout( Factory^ factory, System::String^ text, TextFormat^ format )
	{
		Init( factory, text, format, 0, 0 );
	}

	TextLayout::TextLayout( Factory^ factory, System::String^ text, TextFormat^ format, float maxWidth, float maxHeight )
	{
		Init( factory, text, format, maxWidth, maxHeight );
	}

	void TextLayout::Init( Factory^ factory, System::String^ text, TextFormat^ format, float maxWidth, float maxHeight )
	{
		IDWriteTextLayout *layout = NULL;
		pin_ptr<const wchar_t> pinnedText = PtrToStringChars( text );

		HRESULT hr = factory->InternalPointer->CreateTextLayout( pinnedText, text->Length, format->InternalPointer, maxWidth, maxHeight, &layout );
		if( RECORD_DW( hr ).IsFailure )
			throw gcnew DirectWriteException( Result::Last );

		Construct( layout );
	}

	Result TextLayout::SetFontSize( float size, TextRange range )
	{
		DWRITE_TEXT_RANGE tr;
		tr.startPosition = range.StartPosition;
		tr.length = range.Length;

		HRESULT hr = InternalPointer->SetFontSize( size, tr );
		return RECORD_DW( hr );
	}

	Result TextLayout::SetUnderline( bool underline, TextRange range )
	{
		DWRITE_TEXT_RANGE tr;
		tr.startPosition = range.StartPosition;
		tr.length = range.Length;

		HRESULT hr = InternalPointer->SetUnderline( underline, tr );
		return RECORD_DW( hr );
	}

	Result TextLayout::SetFontWeight( FontWeight weight, TextRange range )
	{
		DWRITE_TEXT_RANGE tr;
		tr.startPosition = range.StartPosition;
		tr.length = range.Length;

		HRESULT hr = InternalPointer->SetFontWeight( static_cast<DWRITE_FONT_WEIGHT>( weight ), tr );
		return RECORD_DW( hr );
	}

	Result TextLayout::SetTypography( Typography^ typography, TextRange range )
	{
		DWRITE_TEXT_RANGE tr;
		tr.startPosition = range.StartPosition;
		tr.length = range.Length;

		HRESULT hr = InternalPointer->SetTypography( typography->InternalPointer, tr );
		return RECORD_DW( hr );
	}

	float TextLayout::MaxWidth::get()
	{
		return InternalPointer->GetMaxWidth();
	}

	void TextLayout::MaxWidth::set( float value )
	{
		RECORD_DW( InternalPointer->SetMaxWidth( value ) );
	}

	float TextLayout::MaxHeight::get()
	{
		return InternalPointer->GetMaxHeight();
	}

	void TextLayout::MaxHeight::set( float value )
	{
		RECORD_DW( InternalPointer->SetMaxHeight( value ) );
	}
}
}