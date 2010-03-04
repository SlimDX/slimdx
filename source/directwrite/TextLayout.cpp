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
#include <cassert>
#include <vector>

#include "DirectWriteException.h"
#include "OverhangMetrics.h"
#include "TextLayout.h"
#include "TextMetrics.h"

const IID IID_IDWriteTextLayout = __uuidof(IDWriteTextLayout);

using namespace System;

namespace SlimDX
{
namespace DirectWrite
{
	LPWSTR AllocateNativeUnicodeString(String ^text)
	{
		return ( text == nullptr || String::IsNullOrEmpty( text ) ) ?
			NULL
			: reinterpret_cast<LPWSTR>( System::Runtime::InteropServices::Marshal::StringToHGlobalUni( text ).ToPointer() );
	}
	void FreeNativeUnicodeString(LPWSTR text)
	{
		if (text)
		{
			System::Runtime::InteropServices::Marshal::FreeHGlobal( IntPtr( reinterpret_cast<void*>( text ) ) );
		}
	}
	class NativeUnicodeString
	{
	public:
		explicit NativeUnicodeString(String ^text)
			: m_nativeString(AllocateNativeUnicodeString(text))
		{
		}
		~NativeUnicodeString()
		{
			FreeNativeUnicodeString(m_nativeString);
		}
		operator LPCWSTR() const
		{
			return m_nativeString;
		}

	private:
		LPWSTR m_nativeString;
	};

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

	float TextLayout::DetermineMinWidth()
	{
		float minWidth = -1.0f;
		RECORD_DW( InternalPointer->DetermineMinWidth(&minWidth) );
		return minWidth;
	}

	HitTestMetrics TextLayout::HitTestPoint( float pointX, float pointY, [Out] bool% isTrailingHit, [Out] bool% isInside )
	{
		DWRITE_HIT_TEST_METRICS htm;
		BOOL trailingHit;
		BOOL inside;

		HRESULT hr = InternalPointer->HitTestPoint( pointX, pointY, &trailingHit, &inside, &htm );
		if( RECORD_DW( hr ).IsFailure )
		{
			return HitTestMetrics();
		}

		isTrailingHit = trailingHit == TRUE;
		isInside = inside == TRUE;
		return HitTestMetrics( htm.textPosition, htm.length, htm.left, htm.top, htm.width, htm.height,
			htm.bidiLevel, htm.isText == TRUE, htm.isTrimmed == TRUE );
	}

	HitTestMetrics TextLayout::HitTestTextPosition( int textPosition, bool isTrailingHit, [Out] float% pointX, [Out] float% pointY )
	{
		DWRITE_HIT_TEST_METRICS htm;
		FLOAT x;
		FLOAT y;

		HRESULT hr = InternalPointer->HitTestTextPosition( textPosition, isTrailingHit, &x, &y, &htm );
		if( RECORD_DW( hr ).IsFailure )
		{
			return HitTestMetrics();
		}

		pointX = x;
		pointY = y;
		return HitTestMetrics( htm.textPosition, htm.length, htm.left, htm.top, htm.width, htm.height,
			htm.bidiLevel, htm.isText == TRUE, htm.isTrimmed == TRUE );
	}

	array<HitTestMetrics>^ TextLayout::HitTestTextRange( int textPosition, int textLength, float originX, float originY )
	{
		// Find out how many hit-test metrics to buffer for
		UINT32 count = 0;
		{
			HRESULT const hr = InternalPointer->HitTestTextRange(textPosition, textLength,
				originX, originY, 0, 0, &count);
			assert(FAILED(hr) && (HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER) == hr));
		}

		std::vector<DWRITE_HIT_TEST_METRICS> metrics(count);
		if (RECORD_DW(InternalPointer->HitTestTextRange(
				textPosition, textLength, originX, originY, 
				&metrics[0], count, &count)).IsFailure)
		{
			return nullptr;
		}

		array<HitTestMetrics>^ result = gcnew array<HitTestMetrics>(count);
		for (UINT32 i = 0; i < count; ++i )
		{
			result[i] = HitTestMetrics( metrics[i].textPosition, metrics[i].length,
				metrics[i].left, metrics[i].top, metrics[i].width, metrics[i].height,
				metrics[i].bidiLevel, metrics[i].isText == TRUE, metrics[i].isTrimmed == TRUE);
		}
		return result;
	}

	array<ClusterMetrics>^ TextLayout::GetClusterMetrics()
	{
		UINT32 count = 0;
		{
			HRESULT const hr = InternalPointer->GetClusterMetrics(0, 0, &count);
			assert(FAILED(hr) && (HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER) == hr));
		}

		std::vector<DWRITE_CLUSTER_METRICS> metrics;
		metrics.resize(count);
		if (RECORD_DW(InternalPointer->GetClusterMetrics(&metrics[0], count, &count)).IsFailure)
		{
			return nullptr;
		}
		array<SlimDX::DirectWrite::ClusterMetrics>^ result = gcnew array<SlimDX::DirectWrite::ClusterMetrics>(count);
		for (UINT32 i = 0; i < count; i++)
		{
			result[i] = ClusterMetrics( metrics[i].width, metrics[i].length,
				metrics[i].canWrapLineAfter != 0,
				metrics[i].isWhitespace != 0,
				metrics[i].isNewline != 0,
				metrics[i].isSoftHyphen != 0,
				metrics[i].isRightToLeft != 0 );
		}
		return result;
	}

	FontCollection^ TextLayout::GetFontCollection ( int currentPosition )
	{
		return GetFontCollectionInternal(currentPosition, 0);
	}

	static TextRange TextRangeFromNative(DWRITE_TEXT_RANGE const &range)
	{
		TextRange result;
		result.StartPosition = range.startPosition;
		result.Length = range.length;
		return result;
	}

	FontCollection^ TextLayout::GetFontCollection ( int currentPosition, [Out] TextRange% textRange )
	{
		DWRITE_TEXT_RANGE tr;
		FontCollection ^collection = GetFontCollectionInternal(currentPosition, &tr);
		if (collection != nullptr)
		{
			textRange = TextRangeFromNative(tr);
		}

		return collection;
	}

	FontCollection ^TextLayout::GetFontCollectionInternal(int currentPosition, DWRITE_TEXT_RANGE *textRange)
	{
		IDWriteFontCollection* fc;
		if( RECORD_DW(InternalPointer->GetFontCollection(currentPosition, &fc, textRange)).IsFailure)
		{
			return nullptr;
		}

		return SlimDX::DirectWrite::FontCollection::FromPointer(fc);
	}

	String^ TextLayout::GetFontFamilyNameInternal(int currentPosition, DWRITE_TEXT_RANGE *textRange)
	{
		UINT32 length = 0U;
		if (RECORD_DW(InternalPointer->GetFontFamilyNameLength(currentPosition, &length, textRange)).IsFailure)
		{
			return String::Empty;
		}

		std::vector<WCHAR> name(length);
		if (RECORD_DW(InternalPointer->GetFontFamilyName(currentPosition, &name[0], length, textRange)).IsFailure)
		{
			return String::Empty;
		}

		return gcnew String(&name[0]);
	}

	String^ TextLayout::GetFontFamilyName( int currentPosition )
	{
		return GetFontFamilyNameInternal(currentPosition, 0);
	}

	String^ TextLayout::GetFontFamilyName( int currentPosition, [Out] TextRange% textRange )
	{
		DWRITE_TEXT_RANGE range;
		String ^familyName = GetFontFamilyNameInternal(currentPosition, &range);
		if (familyName != nullptr)
		{
			textRange = TextRangeFromNative(range);
		}

		return familyName;
	}

	float TextLayout::GetFontSize( int currentPosition )
	{
		float result = -1.0f;
		RECORD_DW(InternalPointer->GetFontSize(currentPosition, &result, 0));
		return result;
	}

	float TextLayout::GetFontSize(int currentPosition, [Out] TextRange% textRange)
	{
		float result = -1.0f;
		DWRITE_TEXT_RANGE range;
		if (RECORD_DW(InternalPointer->GetFontSize(currentPosition, &result, &range)).IsSuccess)
		{
			textRange = TextRangeFromNative(range);
		}
		return result;
	}

	FontStretch TextLayout::GetFontStretch(int currentPosition)
	{
		DWRITE_FONT_STRETCH stretch;
		if (RECORD_DW(InternalPointer->GetFontStretch(currentPosition, &stretch, 0)).IsFailure)
		{
			stretch = DWRITE_FONT_STRETCH_UNDEFINED;
		}
		return static_cast<FontStretch>(stretch);
	}

	FontStretch TextLayout::GetFontStretch(int currentPosition, [Out] TextRange %textRange)
	{
		DWRITE_FONT_STRETCH stretch;
		DWRITE_TEXT_RANGE range;
		if (RECORD_DW(InternalPointer->GetFontStretch(currentPosition, &stretch, &range)).IsSuccess)
		{
			textRange = TextRangeFromNative(range);
		}
		else
		{
			stretch = DWRITE_FONT_STRETCH_UNDEFINED;
		}
		return static_cast<FontStretch>(stretch);
	}

	FontStyle TextLayout::GetFontStyle(int currentPosition)
	{
		DWRITE_FONT_STYLE style;
		if (RECORD_DW(InternalPointer->GetFontStyle(currentPosition, &style, 0)).IsFailure)
		{
			style = DWRITE_FONT_STYLE(-1);
		}
		return static_cast<FontStyle>(style);
	}

	FontStyle TextLayout::GetFontStyle(int currentPosition, [Out] TextRange %textRange)
	{
		DWRITE_FONT_STYLE style;
		DWRITE_TEXT_RANGE range;
		if (RECORD_DW(InternalPointer->GetFontStyle(currentPosition, &style, &range)).IsFailure)
		{
			style = DWRITE_FONT_STYLE(-1);
		}
		else
		{
			textRange = TextRangeFromNative(range);
		}
		return static_cast<FontStyle>(style);
	}

	FontWeight TextLayout::GetFontWeight(int currentPosition)
	{
		DWRITE_FONT_WEIGHT weight;
		if (RECORD_DW(InternalPointer->GetFontWeight(currentPosition, &weight, 0)).IsFailure)
		{
			weight = DWRITE_FONT_WEIGHT(-1);
		}
		return static_cast<FontWeight>(weight);
	}

	FontWeight TextLayout::GetFontWeight(int currentPosition, [Out] TextRange %textRange)
	{
		DWRITE_FONT_WEIGHT weight;
		DWRITE_TEXT_RANGE range;
		if (RECORD_DW(InternalPointer->GetFontWeight(currentPosition, &weight, &range)).IsFailure)
		{
			weight = DWRITE_FONT_WEIGHT(-1);
		}
		else
		{
			textRange = TextRangeFromNative(range);
		}
		return static_cast<FontWeight>(weight);
	}

	array<LineMetrics> ^TextLayout::GetLineMetrics()
	{
		UINT32 count = 0;
		{
			HRESULT const hr = InternalPointer->GetLineMetrics(0, 0, &count);
			assert(FAILED(hr) && (HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER) == hr));
		}

		std::vector<DWRITE_LINE_METRICS> metrics;
		metrics.resize(count);
		if (RECORD_DW(InternalPointer->GetLineMetrics(&metrics[0], count, &count)).IsFailure)
		{
			return nullptr;
		}
		array<SlimDX::DirectWrite::LineMetrics>^ result = gcnew array<SlimDX::DirectWrite::LineMetrics>(count);
		for (UINT32 i = 0; i < count; i++)
		{
			result[i] = LineMetrics(metrics[i].length, metrics[i].trailingWhitespaceLength, metrics[i].newlineLength,
				metrics[i].height, metrics[i].baseline, metrics[i].isTrimmed != 0);
		}
		return result;
	}

	String ^TextLayout::GetLocaleName(int currentPosition)
	{
		UINT32 length = 0U;
		if (RECORD_DW(InternalPointer->GetLocaleNameLength(currentPosition, &length, 0)).IsFailure)
		{
			return String::Empty;
		}

		std::vector<WCHAR> name(length);
		if (RECORD_DW(InternalPointer->GetLocaleName(currentPosition, &name[0], length, 0)).IsFailure)
		{
			return String::Empty;
		}

		return gcnew String(&name[0]);
	}

	String ^TextLayout::GetLocaleName(int currentPosition, [Out] TextRange %range)
	{
		UINT32 length = 0U;
		if (RECORD_DW(InternalPointer->GetLocaleNameLength(currentPosition, &length, 0)).IsFailure)
		{
			return String::Empty;
		}

		std::vector<WCHAR> name(length);
		DWRITE_TEXT_RANGE textRange;
		if (RECORD_DW(InternalPointer->GetLocaleName(currentPosition, &name[0], length, &textRange)).IsFailure)
		{
			return String::Empty;
		}

		range = TextRangeFromNative(textRange);
		return gcnew String(&name[0]);
	}

	static DWRITE_TEXT_RANGE TextRangeFromManaged(TextRange range)
	{
		DWRITE_TEXT_RANGE tr;
		tr.startPosition = range.StartPosition;
		tr.length = range.Length;
		return tr;
	}

	Result TextLayout::SetFontCollection( FontCollection^ collection, TextRange range )
	{
		return RECORD_DW(InternalPointer->SetFontCollection( collection->InternalPointer, TextRangeFromManaged(range)));
	}

	Result TextLayout::SetFontFamilyName(String ^name, TextRange range)
	{
		return RECORD_DW(InternalPointer->SetFontFamilyName( NativeUnicodeString(name), TextRangeFromManaged(range)));
	}

	Result TextLayout::SetFontSize( float size, TextRange range )
	{
		return RECORD_DW(InternalPointer->SetFontSize( size, TextRangeFromManaged(range)));
	}

	Result TextLayout::SetFontStretch(FontStretch stretch, TextRange range)
	{
		return RECORD_DW(InternalPointer->SetFontStretch(static_cast<DWRITE_FONT_STRETCH>(stretch), TextRangeFromManaged(range)));
	}

	Result TextLayout::SetFontStyle(FontStyle style, TextRange range)
	{
		return RECORD_DW(InternalPointer->SetFontStyle(static_cast<DWRITE_FONT_STYLE>(style), TextRangeFromManaged(range)));
	}

	Result TextLayout::SetUnderline( bool underline, TextRange range )
	{
		return RECORD_DW(InternalPointer->SetUnderline( underline, TextRangeFromManaged(range)));
	}

	Result TextLayout::SetFontWeight( FontWeight weight, TextRange range )
	{
		return RECORD_DW(InternalPointer->SetFontWeight(static_cast<DWRITE_FONT_WEIGHT>(weight), TextRangeFromManaged(range)));
	}

	Result TextLayout::SetTypography( Typography^ typography, TextRange range )
	{
		return RECORD_DW(InternalPointer->SetTypography(typography->InternalPointer, TextRangeFromManaged(range)));
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

	TextMetrics TextLayout::Metrics::get()
	{
		DWRITE_TEXT_METRICS metrics;
		if (RECORD_DW(InternalPointer->GetMetrics(&metrics)).IsFailure)
		{
			DWRITE_TEXT_METRICS const zero = { 0 };
			metrics = zero;
		}
		return TextMetrics(metrics.left, metrics.top,
			metrics.width, metrics.widthIncludingTrailingWhitespace, metrics.height,
			metrics.layoutWidth, metrics.layoutHeight,
			metrics.maxBidiReorderingDepth, metrics.lineCount);
	}

	OverhangMetrics TextLayout::OverhangMetrics::get()
	{
		DWRITE_OVERHANG_METRICS metrics;
		if (RECORD_DW(InternalPointer->GetOverhangMetrics(&metrics)).IsFailure)
		{
			DWRITE_OVERHANG_METRICS zero = { 0 };
			metrics = zero;
		}
		return SlimDX::DirectWrite::OverhangMetrics(metrics.left, metrics.top, metrics.right, metrics.bottom);
	}
}
}