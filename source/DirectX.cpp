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

#include <windows.h>
#include <dxerr.h>
#include <vcclr.h>

#include "DirectX.h"

using namespace System::Diagnostics;

namespace SlimDX
{
	String^ DirectX::GetErrorString( int errorCode )
	{
		return gcnew String( DXGetErrorString( errorCode ) );
	}

	String^ DirectX::GetErrorDescription( int errorCode )
	{
		return gcnew String( DXGetErrorDescription( errorCode ) );
	}

	int DirectX::Trace( int errorCode, String^ message, bool messageBox )
	{
		//get the stack frame info of the calling frame
		StackFrame^ frame = gcnew StackFrame( 1, true );
		String^ fileName = frame->GetFileName();
		array<unsigned char>^ fileNameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( fileName );
		pin_ptr<const unsigned char> pinnedFileName = &fileNameBytes[0];

		pin_ptr<const wchar_t> pinnedMessage = PtrToStringChars( message );

		return DXTrace( reinterpret_cast<const char*>( pinnedFileName ), frame->GetFileLineNumber(), errorCode, pinnedMessage, messageBox );
	}
}