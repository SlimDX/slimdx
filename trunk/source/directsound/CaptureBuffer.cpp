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

#include "../ComObject.h"
#include "../Utilities.h"
#include "../DataStream.h"
#include "../WaveFormat.h"
#include "../WaveFormatExtensible.h"

#include "Enums.h"
#include "ResultCode.h"
#include "CaptureBuffer.h"
#include "DirectSoundCapture.h"
#include "CaptureEffectNoiseSuppress.h"
#include "CaptureEffectAcousticEchoCancel.h"
#include "CaptureEffectDescription.h"
#include "CaptureBufferDescription.h"
#include "DirectSoundException.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
	namespace DirectSound
	{
		CaptureBuffer::CaptureBuffer( IDirectSoundCaptureBuffer8* buffer )
		{
			Construct( buffer );
		}

		CaptureBuffer::CaptureBuffer( System::IntPtr pointer )
		{
			Construct( pointer, NativeInterface );
		}

		CaptureBuffer::CaptureBuffer( DirectSoundCapture^ capture, CaptureBufferDescription description )
		{
			DSCBUFFERDESC value = description.ToUnmanaged();
			IDirectSoundCaptureBuffer* buffer;
			HRESULT hr = capture->InternalPointer->CreateCaptureBuffer( &value, &buffer, NULL );
			if( RECORD_DSOUND( hr ).IsFailure )
				throw gcnew DirectSoundException( Result::Last );

			IDirectSoundCaptureBuffer8* dsCapture;
			hr = buffer->QueryInterface( IID_IDirectSoundCaptureBuffer8, reinterpret_cast<void**>( &dsCapture ) );
			if( RECORD_DSOUND( hr ).IsFailure )
				throw gcnew DirectSoundException( Result::Last );

			Construct( dsCapture );
		}

		CaptureBuffer^ CaptureBuffer::FromPointer( IDirectSoundCaptureBuffer8* pointer )
		{
			CaptureBuffer^ tableEntry = safe_cast<CaptureBuffer^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
			if( tableEntry != nullptr )
			{
				pointer->Release();
				return tableEntry;
			}

			return gcnew CaptureBuffer( pointer );
		}

		CaptureBuffer^ CaptureBuffer::FromPointer( System::IntPtr pointer )
		{
			CaptureBuffer^ tableEntry = safe_cast<CaptureBuffer^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
			if( tableEntry != nullptr )
			{
				return tableEntry;
			}

			return gcnew CaptureBuffer( pointer );
		}

		CaptureBuffer::~CaptureBuffer()
		{
			Destruct();
		}

		void CaptureBuffer::Start( bool looping )
		{
			HRESULT hr = InternalPointer->Start( looping ? DSCBSTART_LOOPING : 0 );
			RECORD_DSOUND( hr );
		}

		void CaptureBuffer::Stop()
		{
			HRESULT hr = InternalPointer->Stop();
			RECORD_DSOUND( hr );
		}

		DataStream^ CaptureBuffer::Lock( int offset, int sizeBytes, bool lockEntireBuffer, [Out] DataStream^% secondPart )
		{
			void* buffer1;
			void* buffer2;
			DWORD size1, size2;

			secondPart = nullptr;

			HRESULT hr = InternalPointer->Lock( offset, sizeBytes, &buffer1, &size1, &buffer2, &size2, lockEntireBuffer ? DSCBLOCK_ENTIREBUFFER : 0 );
			if( RECORD_DSOUND( hr ).IsFailure )
				return nullptr;

			DataStream^ stream1 = gcnew DataStream( buffer1, size1, true, true, false );
			if( buffer2 != NULL )
			{
				secondPart = gcnew DataStream( buffer2, size2, true, true, false );
			}

			return stream1;
		}

		void CaptureBuffer::Unlock( DataStream^ firstPart, DataStream^ secondPart )
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

		array<unsigned char>^ CaptureBuffer::Read( int offset, int sizeBytes, bool lockEntireBuffer )
		{
			DataStream^ data2;
			DataStream^ data = Lock( offset, sizeBytes, lockEntireBuffer, data2 );
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

		void CaptureBuffer::Write( array<unsigned char> ^data, int offset, bool lockEntireBuffer )
		{
			int sizeBytes = sizeof( unsigned char ) * static_cast<int>( data->Length );

			DataStream^ stream2;
			DataStream^ stream1 = Lock( offset, sizeBytes, lockEntireBuffer, stream2 );

			stream1->WriteRange<unsigned char>( data );

			if( stream2 != nullptr )				
			{
				int offset2 = static_cast<int>( stream1->Length ) / sizeof( unsigned char );
				int count = static_cast<int>( data->Length ) - offset2;
				stream2->WriteRange<unsigned char>( data, offset2, count );
			}
		}

		WaveFormat^ CaptureBuffer::Format::get()
		{
			WAVEFORMATEX* format;
			DWORD size;

			HRESULT hr = InternalPointer->GetFormat( NULL, 0, &size );
			if( RECORD_DSOUND( hr ).IsFailure )
				throw gcnew DirectSoundException( Result::Last );

			format = reinterpret_cast<WAVEFORMATEX*>( new char[size] );
			hr = InternalPointer->GetFormat( format, size, NULL );
			if( RECORD_DSOUND( hr ).IsFailure )
				throw gcnew DirectSoundException( Result::Last );

			if( format->wFormatTag == WAVE_FORMAT_EXTENSIBLE )
				return WaveFormatExtensible::FromBase( format );
			else 
				return WaveFormat::FromUnmanaged( *format );
		}

		array<CaptureEffectReturnValue>^ CaptureBuffer::GetEffectStatus( int effectCount )
		{
			LPDWORD dwResults = new DWORD[effectCount];
			HRESULT hr = InternalPointer->GetFXStatus( effectCount, dwResults );
			if( RECORD_DSOUND( hr ).IsFailure )
				return nullptr;

			array<CaptureEffectReturnValue>^ results = gcnew array<CaptureEffectReturnValue>( effectCount );

			for( int i = 0; i < effectCount; i++ )
				results[i] = static_cast<CaptureEffectReturnValue>( dwResults[i] );

			return results;
		}

		Object^ CaptureBuffer::GetEffect( int index )
		{
			IUnknown* pointer;

			if( SUCCEEDED( InternalPointer->GetObjectInPath( GUID_All_Objects, index, IID_IDirectSoundCaptureFXAec8, reinterpret_cast<void**>( &pointer ) ) ) )
				return CaptureEffectAcousticEchoCancel::FromPointer( System::IntPtr( pointer ) );
			else if( SUCCEEDED( InternalPointer->GetObjectInPath( GUID_All_Objects, index, IID_IDirectSoundCaptureFXNoiseSuppress8, reinterpret_cast<void**>( &pointer ) ) ) )
				return CaptureEffectNoiseSuppress::FromPointer( System::IntPtr( pointer ) );

			throw gcnew DirectSoundException( ResultCode::ObjectNotFound );
		}

		bool CaptureBuffer::WaveMapped::get()
		{
			DSCBCAPS caps;
			caps.dwSize = sizeof( DSCBCAPS );
			HRESULT hr = InternalPointer->GetCaps( &caps );
			RECORD_DSOUND( hr );

			if( caps.dwFlags == DSCBCAPS_WAVEMAPPED )
				return true;

			return false;
		}

		int CaptureBuffer::SizeInBytes::get()
		{
			DSCBCAPS caps;
			caps.dwSize = sizeof( DSCBCAPS );
			HRESULT hr = InternalPointer->GetCaps( &caps );
			RECORD_DSOUND( hr );

			return caps.dwBufferBytes;
		}

		bool CaptureBuffer::Capturing::get()
		{
			DWORD status;
			HRESULT hr = InternalPointer->GetStatus( &status );
			RECORD_DSOUND( hr );

			if( ( status & DSCBSTATUS_CAPTURING ) != 0 )
				return true;

			return false;
		}

		bool CaptureBuffer::Looping::get()
		{
			DWORD status;
			HRESULT hr = InternalPointer->GetStatus( &status );
			RECORD_DSOUND ( hr );

			if( ( status & DSCBSTATUS_LOOPING ) != 0 )
				return true;

			return false;
		}

		int CaptureBuffer::CurrentCapturePosition::get()
		{
			DWORD capturePosition;
			HRESULT hr = InternalPointer->GetCurrentPosition( &capturePosition, NULL );
			RECORD_DSOUND( hr );

			return capturePosition;
		}

		int CaptureBuffer::CurrentReadPosition::get()
		{
			DWORD readPosition;
			HRESULT hr = InternalPointer->GetCurrentPosition( NULL, &readPosition );
			RECORD_DSOUND( hr );

			return readPosition;
		}
	}
}