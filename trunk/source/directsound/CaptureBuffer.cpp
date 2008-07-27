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
#include <dsound.h>
#include <vector>

#include "../ComObject.h"
#include "../Utilities.h"
#include "../DataStream.h"
#include "../WaveFormat.h"
#include "../WaveFormatExtensible.h"

#include "DirectSoundException.h"

#include "CaptureBuffer.h"

using namespace System;
using namespace System::Reflection;

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

	Result CaptureBuffer::Start( bool looping )
	{
		HRESULT hr = InternalPointer->Start( looping ? DSCBSTART_LOOPING : 0 );
		return RECORD_DSOUND( hr );
	}

	Result CaptureBuffer::Stop()
	{
		HRESULT hr = InternalPointer->Stop();
		return RECORD_DSOUND( hr );
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
			secondPart = gcnew DataStream( buffer2, size2, true, true, false );

		return stream1;
	}

	Result CaptureBuffer::Unlock( DataStream^ firstPart, DataStream^ secondPart )
	{
		void* buffer2 = NULL;
		int size2 = 0;

		if( secondPart != nullptr )
		{
			buffer2 = secondPart->RawPointer;
			size2 = static_cast<int>( secondPart->Length );
		}

		HRESULT hr = InternalPointer->Unlock( firstPart->RawPointer, static_cast<int>( firstPart->Length ), buffer2, size2 );
		return RECORD_DSOUND( hr );
	}

	array<Byte>^ CaptureBuffer::Read( int offset, int sizeBytes, bool lockEntireBuffer )
	{
		DataStream^ data2;
		DataStream^ data = Lock( offset, sizeBytes, lockEntireBuffer, data2 );

		if( data == nullptr )
			return nullptr;

		array<Byte>^ readBytes1 = gcnew array<Byte>( static_cast<int>( data->Length ) );
		array<unsigned char>^ readBytes2 = nullptr;

		int read = data->Read( readBytes1, 0, static_cast<int>( data->Length ) );

		if( data2 != nullptr && read < sizeBytes )
		{
			readBytes2 = gcnew array<Byte>( read - sizeBytes );
			data2->Read( readBytes2, 0, read - sizeBytes );
		}

		if( Unlock( data, data2 ).IsFailure )
			return nullptr;

		int length = readBytes1->Length;

		if( readBytes2 != nullptr )
			length += readBytes2->Length;

		array<Byte>^ totalBytes = gcnew array<Byte>( length );

		for( int i = 0; i < readBytes1->Length; i++ )
			totalBytes[i] = readBytes1[i];

		if( readBytes2 != nullptr )
		{
			for( int i = 0; i < readBytes2->Length; i++ )
				totalBytes[readBytes1->Length + i] = readBytes2[i];
		}

		return totalBytes;
	}

	Result CaptureBuffer::Write( array<Byte>^ data, int offset, bool lockEntireBuffer )
	{
		DataStream^ stream2;
		DataStream^ stream1 = Lock( offset, data->Length, lockEntireBuffer, stream2 );

		if( stream1 == nullptr )
			return Result::Last;

		stream1->Write( data, 0, static_cast<int>( stream1->Length ) );

		if( stream2 != nullptr && data->Length > stream1->Length )				
		{
			int offset2 = static_cast<int>( stream1->Length );
			int count = static_cast<int>( data->Length ) - offset2;
			stream2->Write( data, offset2, count );
		}

		return Unlock( stream1, stream2 );
	}

	WaveFormat^ CaptureBuffer::Format::get()
	{
		WaveFormat^ result;
		WAVEFORMATEX* format;
		DWORD size;

		HRESULT hr = InternalPointer->GetFormat( NULL, 0, &size );
		if( RECORD_DSOUND( hr ).IsFailure )
			throw gcnew DirectSoundException( Result::Last );

		format = reinterpret_cast<WAVEFORMATEX*>( new char[size] );
		hr = InternalPointer->GetFormat( format, size, NULL );

		if( FAILED( hr ) )
			delete[] format;

		if( RECORD_DSOUND( hr ).IsFailure )
			return nullptr;

		if( format->wFormatTag == WAVE_FORMAT_EXTENSIBLE )
			result = WaveFormatExtensible::FromBase( format );
		else 
			result = WaveFormat::FromUnmanaged( *format );

		delete[] format;
		return result;
	}

	array<CaptureEffectReturnValue>^ CaptureBuffer::GetEffectStatus( int effectCount )
	{
		std::vector<DWORD> results( effectCount );

		HRESULT hr = InternalPointer->GetFXStatus( effectCount, &results[0] );
		if( RECORD_DSOUND( hr ).IsFailure )
			return nullptr;

		array<CaptureEffectReturnValue>^ output = gcnew array<CaptureEffectReturnValue>( effectCount );

		for( int i = 0; i < effectCount; i++ )
			output[i] = static_cast<CaptureEffectReturnValue>( results[i] );

		return output;
	}

	generic<typename T>
	T CaptureBuffer::GetEffect( int index )
	{
		GUID guid = Utilities::GetNativeGuidForType( T::typeid );
		void *resultPointer;

		HRESULT hr = InternalPointer->GetObjectInPath( GUID_All_Objects, index, guid, &resultPointer );
		if( RECORD_DSOUND( hr ).IsFailure )
			return T();

		MethodInfo^ method = T::typeid->GetMethod( "FromPointer", BindingFlags::Public | BindingFlags::Static );
		return safe_cast<T>( method->Invoke( nullptr, gcnew array<Object^> { IntPtr( resultPointer ) } ) );
	}

	bool CaptureBuffer::WaveMapped::get()
	{
		DSCBCAPS caps;
		caps.dwSize = sizeof( DSCBCAPS );
		HRESULT hr = InternalPointer->GetCaps( &caps );

		if( RECORD_DSOUND( hr ).IsFailure )
			return false;

		return caps.dwFlags == DSCBCAPS_WAVEMAPPED;
	}

	int CaptureBuffer::SizeInBytes::get()
	{
		DSCBCAPS caps;
		caps.dwSize = sizeof( DSCBCAPS );
		HRESULT hr = InternalPointer->GetCaps( &caps );

		if( RECORD_DSOUND( hr ).IsFailure )
			return 0;

		return caps.dwBufferBytes;
	}

	bool CaptureBuffer::Capturing::get()
	{
		DWORD status;
		HRESULT hr = InternalPointer->GetStatus( &status );
		
		if( RECORD_DSOUND( hr ).IsFailure )
			return false;

		return ( status & DSCBSTATUS_CAPTURING ) != 0;
	}

	bool CaptureBuffer::Looping::get()
	{
		DWORD status;
		HRESULT hr = InternalPointer->GetStatus( &status );
		
		if( RECORD_DSOUND( hr ).IsFailure )
			return false;

		return ( status & DSCBSTATUS_LOOPING ) != 0;
	}

	int CaptureBuffer::CurrentCapturePosition::get()
	{
		DWORD capturePosition;
		HRESULT hr = InternalPointer->GetCurrentPosition( &capturePosition, NULL );
		
		if( RECORD_DSOUND( hr ).IsFailure )
			return 0;

		return capturePosition;
	}

	int CaptureBuffer::CurrentReadPosition::get()
	{
		DWORD readPosition;
		HRESULT hr = InternalPointer->GetCurrentPosition( NULL, &readPosition );
		
		if( RECORD_DSOUND( hr ).IsFailure )
			return 0;

		return readPosition;
	}
}
}