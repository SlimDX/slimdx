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

// Note: Several DirectInput exceptions are not implemented here because
//       they refer to the same value. They are:
//       - DIERR_HANDLEEXISTS
//		 - DIERR_OBJECTNOTFOUND
//       - DIERR_OTHERAPPHASPRIO
//       - DIERR_READONLY

using namespace System;

#include "../Exceptions.h"
#include <dxerr.h>

namespace SlimDX
{
	namespace DirectInput
	{
		/// <summary>
		/// Provides standard access to all DirectInput exceptions, errors, and result codes.
		/// </summary>
		public ref class InputException : public SlimDX::DirectXException
		{
		public:
			/// <summary>
			/// Initializes the <see cref="SlimDX::DirectInput::InputException"/> class.
			/// </summary>
			static InputException()
			{
				LastError = S_OK;
			}

			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectInput::InputException"/> class.
			/// </summary>
			InputException() : DirectXException(E_FAIL, "A Direct3D exception occurred.")
			{ }

			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectInput::InputException"/> class.
			/// </summary>
			/// <param name="message">The error message.</param>
			InputException(String^ message) : DirectXException(E_FAIL, message)
			{ }

			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectInput::InputException"/> class.
			/// </summary>
			/// <param name="errorCode">The DirectInput error code.</param>
			InputException(int errorCode ) : DirectXException( errorCode, gcnew String( DXGetErrorDescription( errorCode ) ) )
			{ }

			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectInput::InputException"/> class.
			/// </summary>
			/// <param name="errorCode">The DirectInput error code.</param>
			/// <param name="message">The error message.</param>
			InputException(int errorCode, String^ message) : DirectXException( errorCode, message )
			{ }

			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectInput::InputException"/> class.
			/// </summary>
			/// <param name="message">The error message.</param>
			/// <param name="innerException">The wrapped exception.</param>
			InputException(String^ message, Exception^ innerException) : DirectXException( message, innerException )
			{ }

			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectInput::InputException"/> class.
			/// </summary>
			/// <param name="info">Serialization information.</param>
			/// <param name="context">Streaming context information.</param>
			InputException(SerializationInfo^ info, StreamingContext context) : DirectXException(info, context)
			{ }

			/// <summary>
			/// Gets or sets the last error code.
			/// </summary>
			static property int LastError;

			/// <summary>
			/// Retrieves the exception that corresponds to the specified result code.
			/// </summary>
			/// <param name="hr">The result code.</param>
			static InputException^ GetExceptionFromHResult( HRESULT hr );

			/// <summary>
			/// Checks the specified result code. If it specifies an error, an exception matching that
			/// error will be thrown.
			/// </summary>
			/// <param name="hr">The result code.</param>
			static void CheckHResult( HRESULT hr );

			/// <summary>
			/// Checks the specified result code. If it specifies an error, an exception matching that
			/// error will be thrown.
			/// </summary>
			/// <param name="hr">The result code.</param>
			/// <param name="dataKey">The data key.</param>
			/// <param name="dataValue">The data value.</param>
			static void CheckHResult( HRESULT hr, String^ dataKey, Object^ dataValue );
		};

#define DEFINE_INPUT_EXCEPTION( ExName, ErrorCode ) \
	public ref class ExName ## Exception : public InputException \
	{ \
		public: \
		ExName ## Exception () : InputException( ErrorCode ) { } \
		ExName ## Exception ( String^ message ) : InputException( ErrorCode, message ) { } \
		ExName ## Exception ( String^ message, Exception^ innerException ) : InputException( message, innerException ) { } \
		ExName ## Exception (SerializationInfo^ info, StreamingContext context) : InputException(info, context) { }\
	}

#define DEFINE_CUSTOM_INPUT_EXCEPTION( ExName, ErrorCode, Message ) \
	public ref class ExName ## Exception : public InputException \
	{ \
		public: \
		ExName ## Exception () : InputException( ErrorCode, Message ) { } \
		ExName ## Exception ( String^ message ) : InputException( ErrorCode, message ) { } \
		ExName ## Exception ( String^ message, Exception^ innerException ) : InputException( message, innerException ) { } \
		ExName ## Exception (SerializationInfo^ info, StreamingContext context) : InputException(info, context) { }\
	}

		DEFINE_INPUT_EXCEPTION( DeviceAcquired, DIERR_ACQUIRED );
		DEFINE_INPUT_EXCEPTION( AlreadyInitialized, DIERR_ALREADYINITIALIZED );
		DEFINE_INPUT_EXCEPTION( BadDriverVersion, DIERR_BADDRIVERVER );
		DEFINE_INPUT_EXCEPTION( BetaDirectInputVersion, DIERR_BETADIRECTINPUTVERSION );
		DEFINE_INPUT_EXCEPTION( DeviceFull, DIERR_DEVICEFULL );
		DEFINE_INPUT_EXCEPTION( DeviceNotRegistered, DIERR_DEVICENOTREG );
		DEFINE_INPUT_EXCEPTION( EffectPlaying, DIERR_EFFECTPLAYING );
		DEFINE_INPUT_EXCEPTION( GenericInput, DIERR_GENERIC );
		DEFINE_INPUT_EXCEPTION( HasEffects, DIERR_HASEFFECTS );
		DEFINE_INPUT_EXCEPTION( IncompleteEffect, DIERR_INCOMPLETEEFFECT );
		DEFINE_INPUT_EXCEPTION( InputLost, DIERR_INPUTLOST );
		DEFINE_INPUT_EXCEPTION( InvalidParameter, DIERR_INVALIDPARAM );
		DEFINE_INPUT_EXCEPTION( MapFileFail, DIERR_MAPFILEFAIL );
		DEFINE_INPUT_EXCEPTION( MoreData, DIERR_MOREDATA );
		DEFINE_INPUT_EXCEPTION( NoAggregation, DIERR_NOAGGREGATION );
		DEFINE_INPUT_EXCEPTION( NoInterface, DIERR_NOINTERFACE );
		DEFINE_INPUT_EXCEPTION( DeviceNotAcquired, DIERR_NOTACQUIRED );
		DEFINE_INPUT_EXCEPTION( NotBuffered, DIERR_NOTBUFFERED );
		DEFINE_INPUT_EXCEPTION( NotDownloaded, DIERR_NOTDOWNLOADED );
		DEFINE_INPUT_EXCEPTION( NotExclusiveAcquired, DIERR_NOTEXCLUSIVEACQUIRED );
		DEFINE_INPUT_EXCEPTION( NotFound, DIERR_NOTFOUND );
		DEFINE_INPUT_EXCEPTION( NotInitialized, DIERR_NOTINITIALIZED );
		DEFINE_INPUT_EXCEPTION( OldDirectInputVersion, DIERR_OLDDIRECTINPUTVERSION );
		DEFINE_INPUT_EXCEPTION( OutOfMemory, DIERR_OUTOFMEMORY );
		DEFINE_INPUT_EXCEPTION( ReportFull, DIERR_REPORTFULL );
		DEFINE_INPUT_EXCEPTION( Unplugged, DIERR_UNPLUGGED );
		DEFINE_INPUT_EXCEPTION( Unsupported, DIERR_UNSUPPORTED );
		DEFINE_INPUT_EXCEPTION( AccessDenied, E_ACCESSDENIED );

		DEFINE_CUSTOM_INPUT_EXCEPTION( Handle, E_HANDLE, "The handle is not a valid top-level window." );
		DEFINE_CUSTOM_INPUT_EXCEPTION( Pending, E_PENDING, "Data is not yet available." );
		DEFINE_CUSTOM_INPUT_EXCEPTION( Pointer, E_POINTER, "Invalid pointer." );
		DEFINE_CUSTOM_INPUT_EXCEPTION( DirectInput8NotFound, E_FAIL, "DirectInput 8 was not found. Reinstalling DirectX may fix the problem." );

		inline InputException^ InputException::GetExceptionFromHResult( HRESULT hr )
		{
			InputException^ ex;

#			define GENERATE_EXCEPTION(errCase, type) \
			case errCase:\
				ex = gcnew type ## Exception ();\
				break;

			switch( hr )
			{
			GENERATE_EXCEPTION(DIERR_ACQUIRED, DeviceAcquired);
			GENERATE_EXCEPTION(DIERR_ALREADYINITIALIZED, AlreadyInitialized);
			GENERATE_EXCEPTION(DIERR_BADDRIVERVER, BadDriverVersion);
			GENERATE_EXCEPTION(DIERR_BETADIRECTINPUTVERSION, BetaDirectInputVersion);
			GENERATE_EXCEPTION(DIERR_DEVICEFULL, DeviceFull);
			GENERATE_EXCEPTION(DIERR_DEVICENOTREG, DeviceNotRegistered);
			GENERATE_EXCEPTION(DIERR_EFFECTPLAYING, EffectPlaying);
			GENERATE_EXCEPTION(DIERR_GENERIC, GenericInput);
			GENERATE_EXCEPTION(DIERR_HASEFFECTS, HasEffects);
			GENERATE_EXCEPTION(DIERR_INCOMPLETEEFFECT, IncompleteEffect);
			GENERATE_EXCEPTION(DIERR_INPUTLOST, InputLost);
			GENERATE_EXCEPTION(DIERR_INVALIDPARAM, InvalidParameter);
			GENERATE_EXCEPTION(DIERR_MAPFILEFAIL, MapFileFail);
			GENERATE_EXCEPTION(DIERR_MOREDATA, MoreData);
			GENERATE_EXCEPTION(DIERR_NOAGGREGATION, NoAggregation);
			GENERATE_EXCEPTION(DIERR_NOINTERFACE, NoInterface);
			GENERATE_EXCEPTION(DIERR_NOTACQUIRED, DeviceNotAcquired);
			GENERATE_EXCEPTION(DIERR_NOTBUFFERED, NotBuffered);
			GENERATE_EXCEPTION(DIERR_NOTDOWNLOADED, NotDownloaded);
			GENERATE_EXCEPTION(DIERR_NOTEXCLUSIVEACQUIRED, NotExclusiveAcquired);
			GENERATE_EXCEPTION(DIERR_NOTFOUND, NotFound);
			GENERATE_EXCEPTION(DIERR_NOTINITIALIZED, NotInitialized);
			GENERATE_EXCEPTION(DIERR_OLDDIRECTINPUTVERSION, OldDirectInputVersion);
			GENERATE_EXCEPTION(DIERR_OUTOFMEMORY, OutOfMemory);
			GENERATE_EXCEPTION(DIERR_REPORTFULL, ReportFull);
			GENERATE_EXCEPTION(DIERR_UNPLUGGED, Unplugged);
			GENERATE_EXCEPTION(DIERR_UNSUPPORTED, Unsupported);
			GENERATE_EXCEPTION(E_HANDLE, Handle);
			GENERATE_EXCEPTION(E_PENDING, Pending);
			GENERATE_EXCEPTION(E_POINTER, Pointer);

			default:
				ex = gcnew InputException( "An input exception occurred." );
			}

			ex->HResult = hr;
			return ex;
		}

		inline void InputException::CheckHResult( HRESULT hr, String^ dataKey, Object^ dataValue )
		{
			if( DirectXException::EnableExceptions && FAILED( hr ) )
			{
				InputException^ ex = InputException::GetExceptionFromHResult( (hr) );
				//don't throw if an exception wasn't returned for some reason (e.g. it's part of a disabled subset)
				if( ex != nullptr )
				{
					if( dataKey != nullptr )
						ex->Data->Add( dataKey, dataValue );
					throw ex;
				}
			}

			InputException::LastError = hr;
		}

		inline void InputException::CheckHResult( HRESULT hr )
		{
			InputException::CheckHResult( hr, nullptr, nullptr );
		}
	}
}