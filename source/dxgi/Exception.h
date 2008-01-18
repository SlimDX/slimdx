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

#include <dxgi.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::Serialization;

namespace SlimDX
{
	[Serializable]
	public ref class Exception : public ApplicationException
	{	
		static Dictionary<int,String^>^ messages;

		static Exception()
		{
			Enabled = true;
			messages = gcnew Dictionary<int,String^>();

			messages->Add( DXGI_ERROR_INVALID_CALL, "Invalid parameters provided to call." );
			messages->Add( DXGI_ERROR_NOT_FOUND, "The requested object was not found." );
			messages->Add( DXGI_ERROR_MORE_DATA, "The provided buffer was too small." );
			messages->Add( DXGI_ERROR_UNSUPPORTED, "The requested functionality is not supported." );
			messages->Add( DXGI_ERROR_DEVICE_REMOVED, "The device has been removed." );
			messages->Add( DXGI_ERROR_DEVICE_HUNG, "The device has hung." );
			messages->Add( DXGI_ERROR_DEVICE_RESET, "The device was reset." );
			messages->Add( DXGI_ERROR_WAS_STILL_DRAWING, "The device was busy." );
			messages->Add( DXGI_ERROR_DRIVER_INTERNAL_ERROR, "A driver internal error occured." );
			messages->Add( DXGI_ERROR_NONEXCLUSIVE, "Exclusive ownership of the specified output could not be acquired." );
		}
	
	internal:
		static bool TestForFailure( HRESULT hr );

	protected:
		Exception( SerializationInfo^ info, StreamingContext context );
		
	public:
		static property bool Enabled;
		
		property int ErrorCode;

		Exception();
		Exception( String^ message );
		Exception( String^ message, Exception^ innerException );
		Exception( String^ message, int errorCode );
	};
}
