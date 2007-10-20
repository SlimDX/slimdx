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

namespace SlimDX
{
	public ref class ErrorCode
	{
	internal:
		ErrorCode() { };

	public:
		static bool Failed( int errorCode ) { return FAILED( errorCode ); }

		static bool Succeeded( int errorCode ) { return SUCCEEDED( errorCode ); }

		literal int Ok = S_OK;
		literal int False = S_FALSE;

		literal int UnexpectedError = E_UNEXPECTED;
		literal int NotImplemented = E_NOTIMPL;
		literal int OutOfMemory = E_OUTOFMEMORY;
		literal int InvalidArgument = E_INVALIDARG;
		literal int NoInterface = E_NOINTERFACE;
		literal int InvalidPointer = E_POINTER;
		literal int InvalidHandle = E_HANDLE;
		literal int Aborted = E_ABORT;
		literal int CallFailed = E_FAIL;
		literal int AccessDenied = E_ACCESSDENIED;

		literal int Pending = E_PENDING;
	};
}