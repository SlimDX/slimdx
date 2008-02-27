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

#include <d3dx10.h>

#include "FontDescription.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{ 	
	FontDescription::FontDescription( const D3DX10_FONT_DESC& native )
	{
		m_Height = native.Height;
		m_Width = native.Width;
		m_Weight = static_cast<FontWeight>( native.Weight );
		m_MipLevels = native.MipLevels;
		m_Italic = native.Italic ? true : false;
		m_CharSet = static_cast<FontCharacterSet>( native.CharSet );
		m_OutputPrecision = static_cast<FontPrecision>( native.OutputPrecision );
		m_Quality = static_cast<FontQuality>( native.Quality );
		m_PitchAndFamily = static_cast<FontPitchAndFamily>( native.PitchAndFamily );
		m_FaceName = gcnew String( native.FaceName );
	}
	
	/*D3DX10_FONT_DESC FontDescription::CreateNativeVersion()
	{
		D3DX10_FONT_DESC native;
		native.Height = m_Height;
		native.Width = m_Width;
		native.Weight = static_cast<UINT>( m_Weight );
		native.MipLevels = m_MipLevels;
		native.Italic = m_Italic;
		native.CharSet = static_cast<BYTE>( m_CharSet );
		native.OutputPrecision = static_cast<BYTE>( m_OutputPrecision );
		native.Quality = static_cast<BYTE>( m_Quality );
		native.PitchAndFamily = static_cast<BYTE>( m_PitchAndFamily );
		
		for(int index = 0; index < LF_FACESIZE; ++index )
		{
			if( index < m_FaceName->Length )
				native.FaceName[ index ] = m_FaceName[ index ];
			else
				native.FaceName[ index ] = 0;
		}
		
		return native;
	}*/

	int FontDescription::Width::get()
	{
		return m_Width;
	}

	void FontDescription::Width::set( int value )
	{
		m_Width = value;
	}
	
	int FontDescription::Height::get()
	{
		return m_Height;
	}

	void FontDescription::Height::set( int value )
	{
		m_Height = value;
	}
	
	FontWeight FontDescription::Weight::get()
	{
		return m_Weight;
	}

	void FontDescription::Weight::set( FontWeight value )
	{
		m_Weight = value;
	}
	
	int FontDescription::MipLevels::get()
	{
		return m_MipLevels;
	}

	void FontDescription::MipLevels::set( int value )
	{
		m_MipLevels = value;
	}
	
	bool FontDescription::IsItalic::get()
	{
		return m_Italic;
	}

	void FontDescription::IsItalic::set( bool value )
	{
		m_Italic = value;
	}
	
	FontCharacterSet FontDescription::CharacterSet::get()
	{
		return m_CharSet;
	}

	void FontDescription::CharacterSet::set( FontCharacterSet value )
	{
		m_CharSet = value;
	}
	
	FontPrecision FontDescription::Precision::get()
	{
		return m_OutputPrecision;
	}

	void FontDescription::Precision::set( FontPrecision value )
	{
		m_OutputPrecision = value;
	}
	
	FontQuality FontDescription::Quality::get()
	{
		return m_Quality;
	}

	void FontDescription::Quality::set( FontQuality value )
	{
		m_Quality = value;
	}
	
	FontPitchAndFamily FontDescription::PitchAndFamily::get()
	{
		return m_PitchAndFamily;
	}

	void FontDescription::PitchAndFamily::set( FontPitchAndFamily value )
	{
		m_PitchAndFamily = value;
	}
	
	String^ FontDescription::FaceName::get()
	{
		return m_FaceName;
	}

	void FontDescription::FaceName::set( String^ value )
	{
		m_FaceName = value;
	}
}
}
