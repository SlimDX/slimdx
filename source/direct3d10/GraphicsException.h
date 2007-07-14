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

namespace SlimDX
{
	namespace Direct3D10
	{
		public ref class GraphicsException : public DirectXException
		{
		public:
			static GraphicsException()
			{
				LastError = S_OK;
			}

			GraphicsException() : DirectXException(E_FAIL, "A Direct3D exception occurred.")
			{ }
			GraphicsException(String^ message) : DirectXException(E_FAIL, message)
			{ }
			GraphicsException( int errorCode, String^ message ) : DirectXException( errorCode, message )
			{ }
			GraphicsException( String^ message, Exception^ innerException ) : DirectXException( message, innerException )
			{ }
			GraphicsException(SerializationInfo^ info, StreamingContext context) : DirectXException(info, context)
			{ }

			static property int LastError;

			static GraphicsException^ GetExceptionFromHResult( HRESULT hr );
			static void CheckHResult( HRESULT hr );
		};

#define DEFINE_GRAPHICS_EXCEPTION( ExName, ErrorCode, Message ) \
	public ref class ExName ## Exception : public GraphicsException \
	{ \
		public: \
		ExName ## Exception () : GraphicsException( ErrorCode, Message ) { } \
		ExName ## Exception ( String^ message ) : GraphicsException( ErrorCode, message ) { } \
		ExName ## Exception ( String^ message, Exception^ innerException ) : GraphicsException( message, innerException ) { } \
		ExName ## Exception (SerializationInfo^ info, StreamingContext context) : GraphicsException(info, context) { }\
	}
		
		DEFINE_GRAPHICS_EXCEPTION( FileNotFound, D3D10_ERROR_FILE_NOT_FOUND, "File not found." );
		DEFINE_GRAPHICS_EXCEPTION( TooManyStateObjects, D3D10_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS, "Too many state objects." );
		
		DEFINE_GRAPHICS_EXCEPTION( InvalidCall, D3DERR_INVALIDCALL, "Invalid call." );
		DEFINE_GRAPHICS_EXCEPTION( WasStillDrawing, D3DERR_WASSTILLDRAWING, "Was still drawing." );
		
		DEFINE_GRAPHICS_EXCEPTION( OutOfMemory, E_OUTOFMEMORY, "Out of memory." );

		inline GraphicsException^ GraphicsException::GetExceptionFromHResult( HRESULT hr )
		{
			GraphicsException^ ex;

#			define GENERATE_EXCEPTION(errCase, type) \
			case errCase:\
				ex = gcnew type ## Exception ();\
				break;

#			define GENERATE_EXCEPTION_IF(errCase, type, condition) \
			case errCase:\
				if(condition)\
					ex = gcnew type ## Exception ();\
				else\
					return nullptr;\
				break;

			switch( hr )
			{
			GENERATE_EXCEPTION(D3D10_ERROR_FILE_NOT_FOUND, FileNotFound);
			GENERATE_EXCEPTION(D3D10_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS, TooManyStateObjects);
			
			GENERATE_EXCEPTION(D3DERR_INVALIDCALL, InvalidCall);
			GENERATE_EXCEPTION(D3DERR_WASSTILLDRAWING, WasStillDrawing);
			
			GENERATE_EXCEPTION(E_OUTOFMEMORY, OutOfMemory);

			default:
				ex = gcnew GraphicsException( E_FAIL, "A graphics exception occurred." );
			}

			ex->HResult = hr;
			return ex;
		}

		inline void GraphicsException::CheckHResult( HRESULT hr )
		{
			if( DirectXException::EnableExceptions && FAILED(hr) )
			{
				GraphicsException^ ex = GraphicsException::GetExceptionFromHResult( (hr) );
				//don't throw if an exception wasn't returned for some reason (e.g. it's part of a disabled subset)
				if( ex != nullptr )
					throw ex;
			}

			GraphicsException::LastError = hr;
		}
	}
}
