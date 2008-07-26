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

#include "../ComObject.h"
#include "../Utilities.h"
#include "../Result.h"
#include "../DataStream.h"
#include "../WaveFile.h"
#include "../WaveFormat.h"
#include "../WaveFormatExtensible.h"
#include "Enums.h"
#include "ResultCode.h"

#include "SoundBufferDescription.h"
#include "BufferCapabilities.h"
#include "DirectSoundException.h"
#include "DirectSound.h"
#include "SoundBuffer.h"


using namespace System;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
	namespace DirectSound
	{
		SoundBuffer::SoundBuffer( IDirectSoundBuffer* buffer )
		{
			if( buffer == NULL )
				throw gcnew ArgumentNullException( "pointer" );

			Construct(buffer);
		}

		SoundBuffer::SoundBuffer( IntPtr buffer )
		{
			Construct( buffer, NativeInterface );
		}

		SoundBuffer::SoundBuffer( DirectSound^ dsound, SoundBufferDescription description )
		{
			DSBUFFERDESC nativeDesc = description.ToUnmanaged();

			IDirectSoundBuffer* buffer;
			HRESULT hr = dsound->InternalPointer->CreateSoundBuffer( &nativeDesc, &buffer, NULL );
			RECORD_DSOUND( hr );
			if( FAILED( hr ) )
				throw gcnew DirectSoundException( Result::Last );

			Construct(buffer);
		}

		SoundBuffer::SoundBuffer( System::String ^filename, SlimDX::DirectSound::DirectSound ^dsound )
		{
			WaveFile^ waveFile = gcnew WaveFile(filename, nullptr, System::IO::FileAccess::Read);

			DSBUFFERDESC desc;
			desc.dwSize = sizeof(DSBUFFERDESC);
			desc.dwFlags = static_cast<DWORD>( BufferFlags::None );
			desc.dwBufferBytes = static_cast<DWORD>( waveFile->Size );
			desc.guid3DAlgorithm = GUID_NULL;
			desc.lpwfxFormat = new WAVEFORMATEX( *WaveFormat::ToUnmanaged( waveFile->Format ).get() );
			desc.dwReserved = 0;

			IDirectSoundBuffer* buffer;
			HRESULT hr = dsound->InternalPointer->CreateSoundBuffer( &desc, &buffer, NULL );
			RECORD_DSOUND( hr );
			if( FAILED( hr ) )
			{
				if( waveFile != nullptr )
					waveFile->~WaveFile();

				throw gcnew DirectSoundException( Result::Last );
			}

			if( hr == DS_NO_VIRTUALIZATION )
				notVirtualized = true;
			else
				notVirtualized = false;

			Construct(buffer);

			//Fill the buffer.
			array<unsigned char>^ databuffer = gcnew array<unsigned char>( waveFile->Size );
			waveFile->Read( databuffer, waveFile->Size );
			waveFile->~WaveFile();
			Write( databuffer, 0, LockFlags::None );
		}

		SoundBuffer::SoundBuffer( System::String ^filename, SlimDX::DirectSound::DirectSound ^dsound, SlimDX::DirectSound::SoundBufferDescription description )
		{
			WaveFile^ waveFile = gcnew WaveFile(filename, description.Format, System::IO::FileAccess::Read);

			DSBUFFERDESC desc = description.ToUnmanaged();
						
			if( description.SizeInBytes == 0 )
				desc.dwBufferBytes = static_cast<DWORD>( waveFile->Size );

			if( description.Format == nullptr )
				desc.lpwfxFormat = new WAVEFORMATEX( *WaveFormat::ToUnmanaged( waveFile->Format ).get() );

			IDirectSoundBuffer* buffer;
			HRESULT hr = dsound->InternalPointer->CreateSoundBuffer( &desc, &buffer, NULL );
			RECORD_DSOUND( hr );
			if( FAILED( hr ) )
			{
				if( waveFile != nullptr )
					waveFile->~WaveFile();

				throw gcnew DirectSoundException( Result::Last );
			}

			if( hr == DS_NO_VIRTUALIZATION )
				notVirtualized = true;
			else
				notVirtualized = false;

			Construct(buffer);

			//Fill the buffer.
			array<unsigned char>^ databuffer = gcnew array<unsigned char>( waveFile->Size );
			waveFile->Read( databuffer, waveFile->Size );
			waveFile->~WaveFile();
			Write( databuffer, 0, LockFlags::None );
		}

		SoundBuffer::~SoundBuffer()
		{
		}

		SoundBuffer^ SoundBuffer::FromPointer( IDirectSoundBuffer* pointer )
		{
			SoundBuffer^ tableEntry = safe_cast<SoundBuffer^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
			if( tableEntry != nullptr )
			{
				pointer->Release();
				return tableEntry;
			}

			return gcnew SoundBuffer( pointer );
		}

		SoundBuffer^ SoundBuffer::FromPointer( IntPtr pointer )
		{
			SoundBuffer^ tableEntry = safe_cast<SoundBuffer^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
			if( tableEntry != nullptr )
			{
				return tableEntry;
			}

			return gcnew SoundBuffer( pointer );
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

		array<unsigned char>^ SoundBuffer::Read( int offset, int sizeBytes, SlimDX::DirectSound::LockFlags flags )
		{
			DataStream^ data2;
			DataStream^ data = Lock( offset, sizeBytes, flags, data2 );
			array<unsigned char>^ readBytes1 = data->ReadRange<unsigned char>( static_cast<int>( data->Length ) );
			array<unsigned char>^ readBytes2 = nullptr;

			if( data2 != nullptr )
			{
				readBytes2 = data2->ReadRange<unsigned char>( static_cast<int>( data2->Length ) );
			}

			Unlock( data, data2 );

			int length = readBytes1->Length;

			if( readBytes2 != nullptr )
			{
				length += readBytes2->Length;
			}

			array<unsigned char>^ totalBytes = gcnew array<unsigned char>( length );

			for( int i = 0; i < readBytes1->Length; i++ )
				totalBytes[i] = readBytes1[i];

			if( readBytes2 != nullptr )
			{
				int bytesLeft = length - readBytes1->Length;

				for( int i = 0; i < readBytes2->Length; i++ )
					totalBytes[bytesLeft + i] = readBytes2[i];
			}

			return totalBytes;
		}

		void SoundBuffer::Write( array<unsigned char>^ data, int offset, SlimDX::DirectSound::LockFlags flags )
		{
			int sizeBytes = sizeof( unsigned char ) * static_cast<int>( data->Length );

			DataStream^ stream2;
			DataStream^ stream1 = Lock( offset, sizeBytes, flags, stream2 );

			stream1->WriteRange<unsigned char>( data );

			if( stream2 != nullptr )				
			{
				int offset2 = static_cast<int>( stream1->Length ) / sizeof( unsigned char );
				int count = static_cast<int>( data->Length ) - offset2;
				stream2->WriteRange<unsigned char>( data, offset2, count );
			}

			Unlock( stream1, stream2 );
		}

		void SoundBuffer::SetFormat( WaveFormat^ format )
		{
			WAVEFORMATEX result = WAVEFORMATEX( *WaveFormat::ToUnmanaged( format ).get() );

			HRESULT hr = InternalPointer->SetFormat( &result );
			RECORD_DSOUND( hr );
		}

		WaveFormat^ SoundBuffer::GetFormat()
		{
			WAVEFORMATEX* format;
			DWORD size;

			HRESULT hr = InternalPointer->GetFormat( NULL, 0, &size );
			RECORD_DSOUND( hr );
			if( FAILED( hr ) )
				throw gcnew DirectSoundException( Result::Last );

			format = reinterpret_cast<WAVEFORMATEX*>( new char[size] );
			hr = InternalPointer->GetFormat( format, size, NULL );
			RECORD_DSOUND( hr );
			if( FAILED( hr ) )
				throw gcnew DirectSoundException( Result::Last );

			if( format->wFormatTag == WAVE_FORMAT_EXTENSIBLE )
				return WaveFormatExtensible::FromBase( format );
			else 
				return WaveFormat::FromUnmanaged( *format );
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

		bool SoundBuffer::NoVirtualization::get()
		{
			return notVirtualized;
		}

		BufferCapabilities SoundBuffer::Capabilities::get()
		{
			DSBCAPS caps;
			caps.dwSize = sizeof(DSBCAPS);
			HRESULT hr = InternalPointer->GetCaps( &caps );
			RECORD_DSOUND( hr );

			return BufferCapabilities( caps );
		}
	}
}