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
#pragma once

#include <windows.h>
#include <mmreg.h>
#include <dsound.h>
#include <d3dx9.h>
#include <cstring>

#include "../DataStream.h"

#include "DirectSound.h"
#include "DirectSoundErrorHandler.h"
#include "DirectSoundException.h"

#include "WaveFormat.h"

namespace SlimDX
{
namespace DirectSound
{
	WaveFormatExtended::WaveFormatExtended()
	{
		InitializeMe( false, 0 );
	}

	WaveFormatExtended::WaveFormatExtended( int extraDataBytes )
	{
		InitializeMe( false, extraDataBytes );
	}

	WaveFormatExtended::WaveFormatExtended( bool extensible, int extraDataBytes )
	{
		InitializeMe( extensible, extraDataBytes );
	}

	WaveFormatExtended::WaveFormatExtended( WAVEFORMATEX* format )
	{
		if( format == NULL )
			throw gcnew ArgumentNullException( "format" );

		m_Format = format;
		if( m_Format->cbSize > 0 )
		{
			m_ExtraData = gcnew DataStream( reinterpret_cast<char*>( m_Format ) + sizeof(WAVEFORMATEX), m_Format->cbSize, true, true, false );
		}
	}

	WaveFormatExtended::~WaveFormatExtended()
	{
		delete m_ExtraData;
		this->!WaveFormatExtended();
	}

	WaveFormatExtended::!WaveFormatExtended()
	{
		m_ExtraData = nullptr;
		delete m_Format;
	}

	void WaveFormatExtended::InitializeMe( bool extensible, int extraDataBytes )
	{
		//22 is the size difference between WAVEFORMATEX and WAVEFORMATEXTENSIBLE
		int extraSize = extensible ? 22 : 0;

		char* data = new char[sizeof(WAVEFORMATEX) + extraSize + extraDataBytes];
		m_Format = reinterpret_cast<WAVEFORMATEX*>( data );

		if( extraDataBytes > 0 )
		{
			//set up the data stream to the extra data
			int offset = sizeof(WAVEFORMATEX) + extraSize;
			m_ExtraData = gcnew DataStream( data + offset, extraDataBytes, true, true, false );
		}

		m_Format->cbSize = extraSize + extraDataBytes;
		this->FormatTag = WaveFormat::Pcm;
		this->Channels = 0;
		this->SamplesPerSecond = 0;
		this->AverageBytesPerSecond = 0;
		this->BlockAlign = 0;
		this->BitsPerSample = 0;
	}

	WaveFormatExtensible::WaveFormatExtensible() : WaveFormatExtended( true, 0 )
	{
		//initialize extra members
		this->ValidBitsPerSample = 0;
		this->ChannelMask = static_cast<Speaker>( 0 );
		memset( &ExtensiblePointer->SubFormat, 0, sizeof(GUID) );
	}

	WaveFormatExtensible::WaveFormatExtensible( int extraDataBytes ) : WaveFormatExtended( true, extraDataBytes )
	{
		//initialize extra members
		this->ValidBitsPerSample = 0;
		this->ChannelMask = static_cast<Speaker>( 0 );
		memset( &ExtensiblePointer->SubFormat, 0, sizeof(GUID) );
	}

	WaveFormatExtensible::WaveFormatExtensible( WAVEFORMATEXTENSIBLE* format )
	{
		if( format == NULL )
			throw gcnew ArgumentNullException( "format" );
		if( format->Format.wFormatTag != WAVE_FORMAT_EXTENSIBLE )
			throw gcnew ArgumentException( "format" );

		Format = reinterpret_cast<WAVEFORMATEX*>( format );

		if( Format->cbSize > 22 )
		{
			ExtraData = gcnew DataStream( reinterpret_cast<char*>( Format ) + sizeof(WAVEFORMATEXTENSIBLE), Format->cbSize - 22, true, true, false );
		}
	};

	Guid WaveFormatExtensible::SubFormat::get()
	{
		Guid result;
		memcpy( &result, &ExtensiblePointer->SubFormat, sizeof(GUID) );
		return result;
	}

	void WaveFormatExtensible::SubFormat::set( Guid value )
	{
		memcpy( &ExtensiblePointer->SubFormat, &value, sizeof(GUID) );
	}
}
}