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

using namespace System;
using namespace System::Runtime::Serialization;

#include "../Exceptions.h"
#include <dxerr.h>

namespace SlimDX
{
	namespace DirectSound
	{
		public ref class SoundException : public SlimDX::DirectXException
		{
		public:
			static SoundException()
			{
				LastError = S_OK;
			}

			SoundException() : DirectXException(E_FAIL, "A DirectSound exception occurred.")
			{ }
			SoundException(String^ message) : DirectXException(E_FAIL, message)
			{ }
			SoundException(int errorCode ) : DirectXException( errorCode, gcnew String( DXGetErrorDescription( errorCode ) ) )
			{ }
			SoundException(int errorCode, String^ message) : DirectXException( errorCode, message )
			{ }
			SoundException(String^ message, Exception^ innerException) : DirectXException( message, innerException )
			{ }
			SoundException(SerializationInfo^ info, StreamingContext context) : DirectXException(info, context)
			{ }

			static property int LastError;

			static SoundException^ GetExceptionFromHResult( HRESULT hr );
			static void CheckHResult( HRESULT hr );
			static void CheckHResult( HRESULT hr, String^ dataKey, Object^ dataValue );
		};

#define DEFINE_SOUND_EXCEPTION( ExName, ErrorCode ) \
	public ref class ExName ## Exception : public SoundException \
	{ \
		public: \
		ExName ## Exception () : SoundException( ErrorCode ) { } \
		ExName ## Exception ( String^ message ) : SoundException( ErrorCode, message ) { } \
		ExName ## Exception ( String^ message, Exception^ innerException ) : SoundException( message, innerException ) { } \
		ExName ## Exception (SerializationInfo^ info, StreamingContext context) : SoundException(info, context) { }\
	}

#define DEFINE_CUSTOM_SOUND_EXCEPTION( ExName, ErrorCode, Message ) \
	public ref class ExName ## Exception : public SoundException \
	{ \
		public: \
		ExName ## Exception () : SoundException( ErrorCode, Message ) { } \
		ExName ## Exception ( String^ message ) : SoundException( ErrorCode, message ) { } \
		ExName ## Exception ( String^ message, Exception^ innerException ) : SoundException( message, innerException ) { } \
		ExName ## Exception (SerializationInfo^ info, StreamingContext context) : SoundException(info, context) { }\
	}

		DEFINE_SOUND_EXCEPTION( Allocated, DSERR_ALLOCATED );
		DEFINE_SOUND_EXCEPTION( ControlUnavailable, DSERR_CONTROLUNAVAIL );
		DEFINE_SOUND_EXCEPTION( InvalidParameter, DSERR_INVALIDPARAM );
		DEFINE_SOUND_EXCEPTION( InvalidCall, DSERR_INVALIDCALL );
		DEFINE_SOUND_EXCEPTION( GenericSound, DSERR_GENERIC );
		DEFINE_SOUND_EXCEPTION( PriorityLevelNeeded, DSERR_PRIOLEVELNEEDED );
		DEFINE_SOUND_EXCEPTION( OutOfMemory, DSERR_OUTOFMEMORY );
		DEFINE_SOUND_EXCEPTION( BadFormat, DSERR_BADFORMAT );
		DEFINE_SOUND_EXCEPTION( Unsupported, DSERR_UNSUPPORTED );
		DEFINE_SOUND_EXCEPTION( NoDriver, DSERR_NODRIVER );
		DEFINE_SOUND_EXCEPTION( AlreadyInitialized, DSERR_ALREADYINITIALIZED );
		DEFINE_SOUND_EXCEPTION( NoAggregation, DSERR_NOAGGREGATION );
		DEFINE_SOUND_EXCEPTION( BufferLost, DSERR_BUFFERLOST );
		DEFINE_SOUND_EXCEPTION( OtherAppHasPriority, DSERR_OTHERAPPHASPRIO );
		DEFINE_SOUND_EXCEPTION( Uninitialized, DSERR_UNINITIALIZED );
		DEFINE_SOUND_EXCEPTION( NoInterface, DSERR_NOINTERFACE );
		DEFINE_SOUND_EXCEPTION( AccessDenied, DSERR_ACCESSDENIED );
		DEFINE_SOUND_EXCEPTION( BufferTooSmall, DSERR_BUFFERTOOSMALL );
		DEFINE_SOUND_EXCEPTION( DirectSound8Required, DSERR_DS8_REQUIRED );
		DEFINE_SOUND_EXCEPTION( SendLoop, DSERR_SENDLOOP );
		DEFINE_SOUND_EXCEPTION( BadSendBufferGuid, DSERR_BADSENDBUFFERGUID );
		DEFINE_SOUND_EXCEPTION( ObjectNotFound, DSERR_OBJECTNOTFOUND );
		DEFINE_SOUND_EXCEPTION( FxUnavailable, DSERR_FXUNAVAILABLE );

		DEFINE_CUSTOM_SOUND_EXCEPTION( DirectSoundNotFound, E_FAIL, "DirectSound not found." );

		inline SoundException^ SoundException::GetExceptionFromHResult( HRESULT hr )
		{
			SoundException^ ex;

#			define GENERATE_EXCEPTION(type, errCase) \
			case errCase:\
				ex = gcnew type ## Exception ();\
				break;

			switch( hr )
			{
			GENERATE_EXCEPTION( Allocated, DSERR_ALLOCATED );
			GENERATE_EXCEPTION( ControlUnavailable, DSERR_CONTROLUNAVAIL );
			GENERATE_EXCEPTION( InvalidParameter, DSERR_INVALIDPARAM );
			GENERATE_EXCEPTION( InvalidCall, DSERR_INVALIDCALL );
			GENERATE_EXCEPTION( GenericSound, DSERR_GENERIC );
			GENERATE_EXCEPTION( PriorityLevelNeeded, DSERR_PRIOLEVELNEEDED );
			GENERATE_EXCEPTION( OutOfMemory, DSERR_OUTOFMEMORY );
			GENERATE_EXCEPTION( BadFormat, DSERR_BADFORMAT );
			GENERATE_EXCEPTION( Unsupported, DSERR_UNSUPPORTED );
			GENERATE_EXCEPTION( NoDriver, DSERR_NODRIVER );
			GENERATE_EXCEPTION( AlreadyInitialized, DSERR_ALREADYINITIALIZED );
			GENERATE_EXCEPTION( NoAggregation, DSERR_NOAGGREGATION );
			GENERATE_EXCEPTION( BufferLost, DSERR_BUFFERLOST );
			GENERATE_EXCEPTION( OtherAppHasPriority, DSERR_OTHERAPPHASPRIO );
			GENERATE_EXCEPTION( Uninitialized, DSERR_UNINITIALIZED );
			GENERATE_EXCEPTION( NoInterface, DSERR_NOINTERFACE );
			GENERATE_EXCEPTION( AccessDenied, DSERR_ACCESSDENIED );
			GENERATE_EXCEPTION( BufferTooSmall, DSERR_BUFFERTOOSMALL );
			GENERATE_EXCEPTION( DirectSound8Required, DSERR_DS8_REQUIRED );
			GENERATE_EXCEPTION( SendLoop, DSERR_SENDLOOP );
			GENERATE_EXCEPTION( BadSendBufferGuid, DSERR_BADSENDBUFFERGUID );
			GENERATE_EXCEPTION( ObjectNotFound, DSERR_OBJECTNOTFOUND );
			GENERATE_EXCEPTION( FxUnavailable, DSERR_FXUNAVAILABLE );

			default:
				ex = gcnew SoundException();
			}

			ex->HResult = hr;
			return ex;
		}

		inline void SoundException::CheckHResult( HRESULT hr, String^ dataKey, Object^ dataValue )
		{
			if( DirectXException::EnableExceptions && FAILED(hr) )
			{
				SoundException^ ex = SoundException::GetExceptionFromHResult( (hr) );
				//don't throw if an exception wasn't returned for some reason (e.g. it's part of a disabled subset)
				if( ex != nullptr )
				{
					if( dataKey != nullptr )
						ex->Data->Add( dataKey, dataValue );
					throw ex;
				}
			}

			SoundException::LastError = hr;
		}

		inline void SoundException::CheckHResult( HRESULT hr )
		{
			SoundException::CheckHResult( hr, nullptr, nullptr );
		}
	}
}
