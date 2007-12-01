/*
* Copyright (c) 2007 SlimDX Group
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
#define WINVER 0x0501
#define _WIN32_WINNT 0x501
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "../DirectXObject.h"
#include "../Utils.h"
#include "../math/Math.h"

#include "Device.h"
#include "Sprite.h"
#include "Font.h"

#include <vcclr.h>

namespace SlimDX
{
namespace Direct3D9
{
	/* Unused for now.
	Font::Font( ID3DXFont* font ) : DirectXObject( font )
	{
		if( font == NULL )
			throw gcnew ArgumentNullException( "font" );
	}
	*/

	Font::Font( IntPtr font )
	{
		if( font == IntPtr::Zero )
			throw gcnew ArgumentNullException( "font" );

		void* pointer;
		IUnknown* unknown = static_cast<IUnknown*>( font.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_ID3DXFont, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<ID3DXFont*>( pointer );
	}

	Font::Font( Device^ device, int height, int width, FontWeight weight, int mipLevels, bool italic,
		CharacterSet charSet, Precision outputPrecision, FontQuality quality,
		PitchAndFamily pitchAndFamily, String^ faceName )
	{
		ID3DXFont* font;
		pin_ptr<const wchar_t> pinned_name = PtrToStringChars( faceName );

		HRESULT hr = D3DXCreateFont( device->InternalPointer, height, width, static_cast<UINT>( weight ), mipLevels, italic, static_cast<DWORD>( charSet ),
			static_cast<DWORD>( outputPrecision ), static_cast<DWORD>( quality ), static_cast<DWORD>( pitchAndFamily ), reinterpret_cast<LPCWSTR>( pinned_name ), &font );
		GraphicsException::CheckHResult( hr );

		m_Pointer = font;
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

		return m_Pointer->DrawTextW( spritePtr, reinterpret_cast<LPCWSTR>( pinned_text ), text->Length, &nativeRect, static_cast<DWORD>( format ), color );
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

		m_Pointer->DrawTextW( spritePtr, reinterpret_cast<LPCWSTR>( pinned_text ), text->Length, &nativeRect, 
			static_cast<DWORD>(format | DrawTextFormat::CalcRect), 0 );
	
		return System::Drawing::Rectangle( nativeRect.left, nativeRect.top, 
			nativeRect.right - nativeRect.left, nativeRect.bottom - nativeRect.top );
	}

	void Font::PreloadCharacters( int first, int last )
	{
		HRESULT hr = m_Pointer->PreloadCharacters( first, last );
		GraphicsException::CheckHResult( hr );
	}

	void Font::PreloadGlyphs( int first, int last )
	{
		HRESULT hr = m_Pointer->PreloadGlyphs( first, last );
		GraphicsException::CheckHResult( hr );
	}

	void Font::PreloadText( String^ text )
	{
		pin_ptr<const wchar_t> pinned_text = PtrToStringChars( text );
		HRESULT hr = m_Pointer->PreloadTextW( reinterpret_cast<LPCWSTR>( pinned_text ), text->Length );
		GraphicsException::CheckHResult( hr );
	}

	void Font::OnLostDevice()
	{
		HRESULT hr = m_Pointer->OnLostDevice();
		GraphicsException::CheckHResult( hr );
	}

	void Font::OnResetDevice()
	{
		HRESULT hr = m_Pointer->OnResetDevice();
		GraphicsException::CheckHResult( hr );
	}

	FontDescription Font::Description::get()
	{
		D3DXFONT_DESC desc;
		
		HRESULT hr = m_Pointer->GetDesc( &desc );
		GraphicsException::CheckHResult( hr );

		FontDescription outDesc;
		outDesc.Height = desc.Height;
		outDesc.Width = desc.Width;
		outDesc.Weight = static_cast<FontWeight>( desc.Weight );
		outDesc.MipLevels = desc.MipLevels;
		outDesc.Italic = desc.Italic > 0;
		outDesc.CharSet = static_cast<CharacterSet>( desc.CharSet );
		outDesc.OutputPrecision = static_cast<Precision>( desc.OutputPrecision );
		outDesc.Quality = static_cast<FontQuality>( desc.Quality );
		outDesc.PitchAndFamily = static_cast<PitchAndFamily>( desc.PitchAndFamily );
		outDesc.FaceName = gcnew String( desc.FaceName );

		return outDesc;
	}

	IntPtr Font::DeviceContext::get()
	{
		return static_cast<IntPtr>( m_Pointer->GetDC() );
	}
}
}
