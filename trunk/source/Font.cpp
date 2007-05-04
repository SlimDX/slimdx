#define WINVER 0x0501
#define _WIN32_WINNT 0x501
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Device.h"
#include "Sprite.h"
#include "Font.h"
#include "Utils.h"

#include <vcclr.h>

namespace SlimDX
{
namespace Direct3D
{
	Font::Font( ID3DXFont* font )
	{
		if( font == NULL )
			throw gcnew ArgumentNullException( "font" );

		m_Font = font;
		m_Disposed = false;
	}

	Font::~Font()
	{
		Utils::MarkDisposed( m_Disposed, this );

		m_Font->Release();
		m_Font = NULL;
	}

	Font::!Font()
	{
		Utils::ReportNotDisposed( this );
	}

	Font::Font( Device^ device, int height, int width, FontWeight weight, int mipLevels, bool italic,
		CharacterSet charSet, Precision outputPrecision, FontQuality quality,
		PitchAndFamily pitchAndFamily, String^ faceName )
	{
		ID3DXFont* font;
		pin_ptr<const wchar_t> pinned_name = PtrToStringChars( faceName );

		HRESULT hr = D3DXCreateFont( device->InternalPointer, height, width, (UINT) weight, mipLevels, italic, (DWORD) charSet,
			(DWORD) outputPrecision, (DWORD) quality, (DWORD) pitchAndFamily, (LPCWSTR) pinned_name, &font );
		FAILED_THROW( hr );

		m_Font = font;
		m_Disposed = false;
	}

	int Font::DrawText( Sprite^ sprite, String^ text, System::Drawing::Rectangle rect, DrawTextFormat format, int color )
	{
		ID3DXSprite* spritePtr = sprite != nullptr ? sprite->InternalPointer : NULL;
		pin_ptr<const wchar_t> pinned_text = PtrToStringChars( text );
		RECT nativeRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };

		return m_Font->DrawTextW( spritePtr, (LPCWSTR) pinned_text, text->Length, &nativeRect, (DWORD) format, color );
	}

	int Font::DrawText( Sprite^ sprite, String^ text, System::Drawing::Rectangle rect, DrawTextFormat format, Color color )
	{
		return DrawText( sprite, text, rect, format, color.ToArgb() );
	}

	int Font::DrawText( Sprite^ sprite, String^ text, int x, int y, int color )
	{
		System::Drawing::Rectangle rect( x, y, 0, 0 );
		return DrawText( sprite, text, rect, DrawTextFormat::NoClip, color );
	}

	int Font::DrawText( Sprite^ sprite, String^ text, int x, int y, Color color )
	{
		return DrawText( sprite, text, x, y, color.ToArgb() );
	}
}
}