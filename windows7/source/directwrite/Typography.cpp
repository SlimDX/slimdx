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

#include <dwrite.h>
#include <vcclr.h>

#include "DirectWriteException.h"

#include "Typography.h"

const IID IID_IDWriteTypography = __uuidof(IDWriteTypography);

using namespace System;

namespace SlimDX
{
namespace DirectWrite
{
	Typography::Typography( IDWriteTypography* pointer )
	{
		Construct( pointer );
	}

	Typography::Typography( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	Typography^ Typography::FromPointer( IDWriteTypography* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		Typography^ tableEntry = safe_cast<Typography^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew Typography( pointer );
	}

	Typography^ Typography::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		Typography^ tableEntry = safe_cast<Typography^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew Typography( pointer );
	}

	Typography::Typography( Factory^ factory )
	{
		IDWriteTypography *typo = NULL;

		HRESULT hr = factory->InternalPointer->CreateTypography( &typo );
		if( RECORD_DW( hr ).IsFailure )
			throw gcnew DirectWriteException( Result::Last );

		Construct( typo );
	}
}
}