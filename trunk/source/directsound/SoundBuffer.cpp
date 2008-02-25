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

#include <windows.h>
#include <mmreg.h>
#include <dsound.h>
#include <d3dx9.h>

#include "../DataStream.h"

#include "DirectSound.h"

#include "DirectSoundException.h"

#include "WaveFormat.h"
#include "SoundBuffer.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace DirectSound
{
	void BufferDescription::Marshal( DSBUFFERDESC& description )
	{
		description.dwSize = sizeof(DSBUFFERDESC);
		description.dwFlags = static_cast<DWORD>( this->Flags );
		description.dwBufferBytes = static_cast<DWORD>( this->SizeInBytes );
		description.dwReserved = 0;

		if( this->Format == nullptr )
			description.lpwfxFormat = NULL;
		else
			description.lpwfxFormat = this->Format->InternalPointer;
	}

	SoundBuffer::SoundBuffer( IDirectSoundBuffer* buffer )
	{
		if( buffer == NULL )
			throw gcnew ArgumentNullException( "buffer" );

		Construct(buffer);

		SetDS8Pointer();
	}

	SoundBuffer::SoundBuffer( DirectSound^ dsound, BufferDescription description )
	{
		DSBUFFERDESC nativeDesc;
		description.Marshal( nativeDesc );

		IDirectSoundBuffer* buffer;
		HRESULT hr = dsound->InternalPointer->CreateSoundBuffer( &nativeDesc, &buffer, NULL );
		RECORD_DSOUND( hr );
		if( FAILED( hr ) )
			throw gcnew DirectSoundException( Result::Last );

		Construct(buffer);
		SetDS8Pointer();
	}

	SoundBuffer::~SoundBuffer()
	{
		if( m_DS8Pointer != NULL )
		{
			m_DS8Pointer->Release();
			m_DS8Pointer = NULL;
		}

		Destruct();
	}

	void SoundBuffer::SetDS8Pointer()
	{
		IDirectSoundBuffer8* buffer;
		HRESULT hr = InternalPointer->QueryInterface( IID_IDirectSoundBuffer8, reinterpret_cast<void**>( &buffer ) );
		
		if( SUCCEEDED( hr ) )
		{
			m_DS8Pointer = buffer;
		}
		else
		{
			m_DS8Pointer = NULL;
		}
	}

	void SoundBuffer::Initialize( DirectSound^ dsound, BufferDescription description )
	{
		DSBUFFERDESC nativeDesc;
		description.Marshal( nativeDesc );

		IDirectSoundBuffer* buffer;
		HRESULT hr = dsound->InternalPointer->CreateSoundBuffer( &nativeDesc, &buffer, NULL );
		RECORD_DSOUND( hr );
		if( FAILED( hr ) )
			throw gcnew DirectSoundException();

		Construct( buffer );;
		SetDS8Pointer();
	}

	void SoundBuffer::Restore()
	{
		HRESULT hr = InternalPointer->Restore();
		RECORD_DSOUND( hr );
	}

	void SoundBuffer::Play( int priority, PlayFlags flags )
	{
		HRESULT hr = InternalPointer->Play( 0, priority, static_cast<DWORD>( flags ) );
		RECORD_DSOUND( hr );
	}

	void SoundBuffer::Stop()
	{
		HRESULT hr = InternalPointer->Stop();
		RECORD_DSOUND( hr );
	}

	DataStream^ SoundBuffer::Lock( int offset, int sizeBytes, LockFlags flags, [Out] DataStream^% secondPart )
	{
		void* buffer1;
		void* buffer2;
		DWORD size1, size2;

		secondPart = nullptr;

		HRESULT hr = InternalPointer->Lock( offset, sizeBytes, &buffer1, &size1, &buffer2, &size2, static_cast<DWORD>( flags ) );
		RECORD_DSOUND( hr );
		if( FAILED( hr ) )
			return nullptr;

		DataStream^ stream1 = gcnew DataStream( buffer1, size1, true, true, false );
		if( buffer2 != NULL )
		{
			secondPart = gcnew DataStream( buffer2, size2, true, true, false );
		}

		return stream1;
	}

	void SoundBuffer::Unlock( DataStream^ firstPart, DataStream^ secondPart )
	{
		void* buffer2 = NULL;
		int size2 = 0;

		if( secondPart != nullptr )
		{
			buffer2 = secondPart->RawPointer;
			size2 = static_cast<int>( secondPart->Length );
		}

		HRESULT hr = InternalPointer->Unlock( firstPart->RawPointer, static_cast<int>( firstPart->Length ), buffer2, size2 );
		RECORD_DSOUND( hr );
	}

	void SoundBuffer::SetFormat( WaveFormatExtended^ format )
	{
		HRESULT hr = InternalPointer->SetFormat( format->InternalPointer );
		RECORD_DSOUND( hr );
	}

	WaveFormatExtended^ SoundBuffer::GetFormat()
	{
		WAVEFORMATEX* format;
		DWORD size;

		HRESULT hr = InternalPointer->GetFormat( NULL, 0, &size );
		RECORD_DSOUND( hr );
		if( FAILED( hr ) )
			return nullptr;

		format = reinterpret_cast<WAVEFORMATEX*>( new char[size] );
		hr = InternalPointer->GetFormat( format, size, NULL );
		RECORD_DSOUND( hr );
		if( FAILED( hr ) )
			return nullptr;

		if( format->wFormatTag == WAVE_FORMAT_EXTENSIBLE )
			return gcnew WaveFormatExtensible( reinterpret_cast<WAVEFORMATEXTENSIBLE*>( format ) );
		else
			return gcnew WaveFormatExtended( format );
	}

	int SoundBuffer::CurrentPlayPosition::get()
	{
		DWORD position = 0;
		HRESULT hr = InternalPointer->GetCurrentPosition( &position, NULL );
		RECORD_DSOUND( hr );

		return position;
	}
	
	void SoundBuffer::CurrentPlayPosition::set( int value )
	{
		HRESULT hr = InternalPointer->SetCurrentPosition( value );
		RECORD_DSOUND( hr );
	}

	int SoundBuffer::CurrentWritePosition::get()
	{
		DWORD position = 0;
		HRESULT hr = InternalPointer->GetCurrentPosition( NULL, &position );
		RECORD_DSOUND( hr );

		return position;
	}
	
	int SoundBuffer::Frequency::get()
	{
		DWORD freq = 0;
		HRESULT hr = InternalPointer->GetFrequency( &freq );
		RECORD_DSOUND( hr );

		return freq;
	}

	void SoundBuffer::Frequency::set( int value )
	{
		HRESULT hr = InternalPointer->SetFrequency( value );
		RECORD_DSOUND( hr );
	}

	int SoundBuffer::Volume::get()
	{
		LONG volume = 0;
		HRESULT hr = InternalPointer->GetVolume( &volume );
		RECORD_DSOUND( hr );

		return volume;
	}

	void SoundBuffer::Volume::set( int value )
	{
		HRESULT hr = InternalPointer->SetVolume( value );
		RECORD_DSOUND( hr );
	}

	int SoundBuffer::Pan::get()
	{
		LONG pan = 0;
		HRESULT hr = InternalPointer->GetPan( &pan );
		RECORD_DSOUND( hr );

		return pan;
	}

	void SoundBuffer::Pan::set( int value )
	{
		HRESULT hr = InternalPointer->SetPan( value );
		RECORD_DSOUND( hr );
	}

	BufferStatus SoundBuffer::Status::get()
	{
		DWORD status = 0;
		HRESULT hr = InternalPointer->GetStatus( &status );
		RECORD_DSOUND( hr );

		return static_cast<BufferStatus>( status );
	}
}
}