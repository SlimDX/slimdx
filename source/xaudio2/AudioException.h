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
	namespace Direct3D9
	{
		public ref class AudioException : public SlimDX::DirectXException
		{
		public:
			static AudioException()
			{
				LastError = S_OK;
			}

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
			AudioException(SerializationInfo^ info, StreamingContext context) : DirectXException(info, context)
			{ }

			static property int LastError;

			static AudioException^ GetExceptionFromHResult( HRESULT hr );
			static void CheckHResult( HRESULT hr );
			static void CheckHResult( HRESULT hr, String^ dataKey, Object^ dataValue );
		};

		inline AudioException^ AudioException::GetExceptionFromHResult( HRESULT hr )
		{
			AudioException^ ex;

			//TODO: exception selection
			ex = gcnew AudioException();

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