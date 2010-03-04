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
#pragma once

#include "ClusterMetrics.h"
#include "FactoryDW.h"
#include "HitTestMetrics.h"
#include "LineMetrics.h"
#include "TextFormat.h"
#include "TextRange.h"
#include "Typography.h"

extern const IID IID_IDWriteTextLayout;
struct DWRITE_TEXT_RANGE;

namespace SlimDX
{
	namespace DirectWrite
	{
		using namespace System;
		value class OverhangMetrics;
		value class TextMetrics;

		public ref class TextLayout : public ComObject
		{
			COMOBJECT(IDWriteTextLayout, TextLayout);

			void Init( Factory^ factory, String^ text, TextFormat^ format, float maxWidth, float maxHeight );
			FontCollection ^GetFontCollectionInternal(int currentPosition, DWRITE_TEXT_RANGE *textRange);
			String ^GetFontFamilyNameInternal(int currentPosition, DWRITE_TEXT_RANGE *textRange);

		public:
			TextLayout( Factory^ factory, String^ text, TextFormat^ format );
			TextLayout( Factory^ factory, String^ text, TextFormat^ format, float maxWidth, float maxHeight );

			float DetermineMinWidth();
			HitTestMetrics HitTestPoint( float pointX, float pointY, [Out] bool% isTrailingHit, [Out] bool% isInside );
			HitTestMetrics HitTestTextPosition( int textPosition, bool isTrailingHit, [Out] float% pointX, [Out] float% pointY );
			array< HitTestMetrics >^ HitTestTextRange( int textPosition, int textLength, float originX, float originY );

			array<ClusterMetrics>^ GetClusterMetrics();
			FontCollection^ GetFontCollection( int currentPosition );
			FontCollection^ GetFontCollection( int currentPosition, [Out] TextRange% textRange );
			String^ GetFontFamilyName( int currentPosition );
			String^ GetFontFamilyName( int currentPosition, [Out] TextRange% textRange );
			float GetFontSize( int currentPosition );
			float GetFontSize( int currentPosition, [Out] TextRange% textRange );
			FontStretch GetFontStretch( int currentPosition );
			FontStretch GetFontStretch(int currentPosition, [Out] TextRange %textRange);
			FontStyle GetFontStyle(int currentPosition);
			FontStyle GetFontStyle(int currentPosition, [Out] TextRange %textRange);
			FontWeight GetFontWeight(int currentPosition);
			FontWeight GetFontWeight(int currentPosition, [Out] TextRange %textRange);
			array<LineMetrics> ^GetLineMetrics();
			String ^GetLocaleName(int currentPosition);
			String ^GetLocaleName(int currentPosition, [Out] TextRange %textRange);
			bool GetStrikethrough(int currentPosition);

			Result SetFontCollection( FontCollection^ collection, TextRange range );
			Result SetFontFamilyName( String^ name, TextRange range );
			Result SetFontSize( float size, TextRange range );
			Result SetFontStretch(FontStretch stretch, TextRange range);
			Result SetFontStyle(FontStyle style, TextRange range);
			Result SetFontWeight( FontWeight weight, TextRange range );
			Result SetTypography( Typography^ typography, TextRange range );
			Result SetUnderline( bool underline, TextRange range );

			property float MaxWidth
			{
				float get();
				void set( float value );
			}

			property float MaxHeight
			{
				float get();
				void set( float value );
			}

			property TextMetrics Metrics
			{
				TextMetrics get();
			}

			property SlimDX::DirectWrite::OverhangMetrics OverhangMetrics
			{
				SlimDX::DirectWrite::OverhangMetrics get();
			}
		};
	}
}