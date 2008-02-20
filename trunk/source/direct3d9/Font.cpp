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

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "../ComObject.h"
#include "../Utilities.h"
#include "../math/Math.h"

#include "Device.h"
#include "Sprite.h"
#include "Font.h"
#include "Direct3D9Exception.h"

#include <vcclr.h>

using namespace System;
using namespace System::Drawing;

namespace SlimDX
{
namespace Direct3D9
{
	/* Unused for now.
	Font::Font( ID3DXFont* font ) : ComObject( font )
	{
		if( font == NULL )
			throw gcnew ArgumentNullException( "font" );
	}
	*/

	Font::Font( IntPtr font )
	{
		Construct( font, NativeInterface );

	}

	Font::Font( Device^ device, int height, int width, FontWeight weight, int mipLevels, bool italic,
		CharacterSet charSet, Precision outputPrecision, FontQuality quality,
		PitchAndFamily pitchAndFamily, String^ faceName )
	{
		ID3DXFont* font;
		pin_ptr<const wchar_t> pinned_name = PtrToStringChars( faceName );

		HRESULT hr = D3DXCreateFont( device->InternalPointer, height, width, static_cast<UINT>( weight ), mipLevels, italic, static_cast<DWORD>( charSet ),
			static_cast<DWORD>( outputPrecision ), static_cast<DWORD>( quality ), static_cast<DWORD>( pitchAndFamily ), reinterpret_cast<LPCWSTR>( pinned_name ), &font );

		if( Result::Record( hr ).IsFailure )
			throw gcnew Direct3D9Exception();

		Construct(font);
	}

	Font::Font( Device^ device, System::Drawing::Font^ font )
	{
		Font( device, font->Height, 0, (font->Bold) ? FontWeight::Bold : FontWeight::Normal, 0, font->Italic, 
			CharacterSet::Default, Precision::Default, FontQuality::Default, PitchAndFamily::Default, font->Name );
	}

	int Font::DrawString( Sprite^ sprite, String^ text, System::Drawing::Rectangle rect, DrawTextFormat format, int color )
	{
		ID3DXSprite* spritePtr = sprite != nullptr ? sprite->InternalPointer : NULL;
		pin_ptr<const wchar_t> pinned_text = PtrToStringChars( text );
		RECT nativeRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };

		return InternalPointer->DrawTextW( spritePtr, reinterpret_cast<LPCWSTR>( pinned_text ), text->Length, &nativeRect, static_cast<DWORD>( format ), color );
	}

	int Font::DrawString( Sprite^ sprite, String^ text, System::Drawing::Rectangle rect, DrawTextFormat format, Color color )
	{
		return DrawString( sprite, text, rect, format, color.ToArgb() );
	}

	int Font::DrawString( Sprite^ sprite, String^ text, int x, int y, int color )
	{
		System::Drawing::Rectangle rect( x, y, 0, 0 );
		return DrawString( sprite, text, rect, DrawTextFormat::NoClip, color );
	}

	int Font::DrawString( Sprite^ sprite, String^ text, int x, int y, Color color )
	{
		return DrawString( sprite, text, x, y, color.ToArgb() );
	}

	System::Drawing::Rectangle Font::MeasureString( Sprite^ sprite, String^ text, DrawTextFormat format )
	{
		ID3DXSprite* spritePtr = sprite != nullptr ? sprite->InternalPointer : NULL;
		pin_ptr<const wchar_t> pinned_text = PtrToStringChars( text );
		RECT nativeRect;

		InternalPointer->DrawTextW( spritePtr, reinterpret_cast<LPCWSTR>( pinned_text ), text->Length, &nativeRect, 
			static_cast<DWORD>(format | DrawTextFormat::CalcRect), 0 );
	
		return System::Drawing::Rectangle( nativeRect.left, nativeRect.top, 
			nativeRect.right - nativeRect.left, nativeRect.bottom - nativeRect.top );
	}

	Result Font::PreloadCharacters( int first, int last )
	{
		HRESULT hr = InternalPointer->PreloadCharacters( first, last );
		return Result::Record( hr );
	}

	Result Font::PreloadGlyphs( int first, int last )
	{
		HRESULT hr = InternalPointer->PreloadGlyphs( first, last );
		return Result::Record( hr );
	}

	Result Font::PreloadText( String^ text )
	{
		pin_ptr<const wchar_t> pinned_text = PtrToStringChars( text );
		HRESULT hr = InternalPointer->PreloadTextW( reinterpret_cast<LPCWSTR>( pinned_text ), text->Length );
		return Result::Record( hr );
	}

	Result Font::OnLostDevice()
	{
		HRESULT hr = InternalPointer->OnLostDevice();
		return Result::Record( hr );
	}

	Result Font::OnResetDevice()
	{
		HRESULT hr = InternalPointer->OnResetDevice();
		return Result::Record( hr );
	}

	FontDescription Font::Description::get()
	{
		D3DXFONT_DESC description;
		
		HRESULT hr = InternalPointer->GetDesc( &description );
		if( Result::Record( hr ).IsFailure )
			return FontDescription();

		FontDescription outDesc;
		outDesc.Height = description.Height;
		outDesc.Width = description.Width;
		outDesc.Weight = static_cast<FontWeight>( description.Weight );
		outDesc.MipLevels = description.MipLevels;
		outDesc.Italic = description.Italic > 0;
		outDesc.CharSet = static_cast<CharacterSet>( description.CharSet );
		outDesc.OutputPrecision = static_cast<Precision>( description.OutputPrecision );
		outDesc.Quality = static_cast<FontQuality>( description.Quality );
		outDesc.PitchAndFamily = static_cast<PitchAndFamily>( description.PitchAndFamily );
		outDesc.FaceName = gcnew String( description.FaceName );

		return outDesc;
	}

	IntPtr Font::DeviceContext::get()
	{
		return static_cast<IntPtr>( InternalPointer->GetDC() );
	}
}
}
