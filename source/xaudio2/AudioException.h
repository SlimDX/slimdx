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

#ifdef WRAP_XAUDIO2

using namespace System;
using namespace System::Runtime::Serialization;

#include "../Exceptions.h"
#include <dxerr.h>

namespace SlimDX
{
	namespace XAudio2
	{
		public ref class AudioException : public SlimDX::DirectXException
		{
		private:
			static AudioException()
			{
				LastError = S_OK;
			}

		protected:
			AudioException(SerializationInfo^ info, StreamingContext context) : DirectXException(info, context)
			{ }

		public:
			AudioException() : DirectXException(E_FAIL, "An XAudio2 exception occurred.")
			{ }
			AudioException(String^ message) : DirectXException(E_FAIL, message)
			{ }
			AudioException(int errorCode ) : DirectXException( errorCode, gcnew String( DXGetErrorDescription( errorCode ) ) )
			{ }
			AudioException(int errorCode, String^ message) : DirectXException( errorCode, message )
			{ }
			AudioException(String^ message, Exception^ innerException) : DirectXException( message, innerException )
			{ }

			static property int LastError;

			static AudioException^ GetExceptionFromHResult( HRESULT hr );
			static void CheckHResult( HRESULT hr );
			static void CheckHResult( HRESULT hr, String^ dataKey, Object^ dataValue );
		};

#define DEFINE_AUDIO_EXCEPTION( ExName, ErrorCode ) \
	public ref class ExName ## Exception : public AudioException \
	{ \
	protected: \
		ExName ## Exception (SerializationInfo^ info, StreamingContext context) : AudioException(info, context) { }\
	public: \
		ExName ## Exception () : AudioException( ErrorCode ) { } \
		ExName ## Exception ( String^ message ) : AudioException( ErrorCode, message ) { } \
		ExName ## Exception ( String^ message, Exception^ innerException ) : AudioException( message, innerException ) { } \
	}

#define DEFINE_CUSTOM_AUDIO_EXCEPTION( ExName, ErrorCode, Message ) \
	public ref class ExName ## Exception : public AudioException \
	{ \
	protected: \
		ExName ## Exception (SerializationInfo^ info, StreamingContext context) : AudioException(info, context) { }\
	public: \
		ExName ## Exception () : AudioException( ErrorCode, Message ) { } \
		ExName ## Exception ( String^ message ) : AudioException( ErrorCode, message ) { } \
		ExName ## Exception ( String^ message, Exception^ innerException ) : AudioException( message, innerException ) { } \
	}

		DEFINE_AUDIO_EXCEPTION( NotInitialized, XAUDIO2_E_NOT_INITIALIZED );
		DEFINE_AUDIO_EXCEPTION( AlreadyInitialized, XAUDIO2_E_ALREADY_INITIALIZED );
		DEFINE_AUDIO_EXCEPTION( InvalidArgument, XAUDIO2_E_INVALID_ARGUMENT );
		DEFINE_AUDIO_EXCEPTION( InvalidFlags, XAUDIO2_E_INVALID_FLAGS );
		DEFINE_AUDIO_EXCEPTION( InvalidPointer, XAUDIO2_E_INVALID_POINTER );
		DEFINE_AUDIO_EXCEPTION( InvalidIndex, XAUDIO2_E_INVALID_INDEX );
		DEFINE_AUDIO_EXCEPTION( InvalidCall, XAUDIO2_E_INVALID_CALL );
		DEFINE_AUDIO_EXCEPTION( StillinUse, XAUDIO2_E_STILL_IN_USE );
		DEFINE_AUDIO_EXCEPTION( Unsupported, XAUDIO2_E_UNSUPPORTED );
		DEFINE_AUDIO_EXCEPTION( XmaDecoderError, XAUDIO2_E_XMA_DECODER_ERROR );
		DEFINE_AUDIO_EXCEPTION( EffectCreationFailed, XAUDIO2_E_EFFECT_CREATION_FAILED );
		DEFINE_AUDIO_EXCEPTION( DeviceInvalidated, XAUDIO2_E_DEVICE_INVALIDATED );

		DEFINE_CUSTOM_AUDIO_EXCEPTION( XAudio2NotFound, E_FAIL, "XAudio 2 not found." );

		inline AudioException^ AudioException::GetExceptionFromHResult( HRESULT hr )
		{
			AudioException^ ex;

#			define GENERATE_EXCEPTION(type, errCase) \
			case errCase:\
				ex = gcnew type ## Exception ();\
				break;

			switch( hr )
			{
			GENERATE_EXCEPTION( NotInitialized, XAUDIO2_E_NOT_INITIALIZED );
			GENERATE_EXCEPTION( AlreadyInitialized, XAUDIO2_E_ALREADY_INITIALIZED );
			GENERATE_EXCEPTION( InvalidArgument, XAUDIO2_E_INVALID_ARGUMENT );
			GENERATE_EXCEPTION( InvalidFlags, XAUDIO2_E_INVALID_FLAGS );
			GENERATE_EXCEPTION( InvalidPointer, XAUDIO2_E_INVALID_POINTER );
			GENERATE_EXCEPTION( InvalidIndex, XAUDIO2_E_INVALID_INDEX );
			GENERATE_EXCEPTION( InvalidCall, XAUDIO2_E_INVALID_CALL );
			GENERATE_EXCEPTION( StillinUse, XAUDIO2_E_STILL_IN_USE );
			GENERATE_EXCEPTION( Unsupported, XAUDIO2_E_UNSUPPORTED );
			GENERATE_EXCEPTION( XmaDecoderError, XAUDIO2_E_XMA_DECODER_ERROR );
			GENERATE_EXCEPTION( EffectCreationFailed, XAUDIO2_E_EFFECT_CREATION_FAILED );
			GENERATE_EXCEPTION( DeviceInvalidated, XAUDIO2_E_DEVICE_INVALIDATED );

			default:
				ex = gcnew AudioException();
			}

			ex->HResult = hr;
			return ex;
		}

		inline void AudioException::CheckHResult( HRESULT hr, String^ dataKey, Object^ dataValue )
		{
			if( DirectXException::EnableExceptions && FAILED(hr) )
			{
				AudioException^ ex = AudioException::GetExceptionFromHResult( (hr) );
				//don't throw if an exception wasn't returned for some reason (e.g. it's part of a disabled subset)
				if( ex != nullptr )
				{
					if( dataKey != nullptr )
						ex->Data->Add( dataKey, dataValue );
					throw ex;
				}
			}

			AudioException::LastError = hr;
		}

		inline void AudioException::CheckHResult( HRESULT hr )
		{
			AudioException::CheckHResult( hr, nullptr, nullptr );
		}
	}
}

#endif //WRAP_XAUDIO2
