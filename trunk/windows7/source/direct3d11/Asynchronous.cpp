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

#include <d3d11.h>

#include "Direct3D11Exception.h"

#include "Asynchronous.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{ 
	Asynchronous::Asynchronous()
	{
	}
	
	Asynchronous::Asynchronous( ID3D11Asynchronous* pointer )
	{
		Construct( pointer );
	}

	Asynchronous::Asynchronous( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}	

	Asynchronous^ Asynchronous::FromPointer( ID3D11Asynchronous* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		Asynchronous^ tableEntry = safe_cast<Asynchronous^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew Asynchronous( pointer );
	}

	Asynchronous^ Asynchronous::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		Asynchronous^ tableEntry = safe_cast<Asynchronous^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew Asynchronous( pointer );
	}

	/*
	bool Asynchronous::IsDataAvailable::get()
	{
		return InternalPointer->GetData( 0, 0, 0 ) == S_OK;
	}
	
	void Asynchronous::Begin()
	{
		InternalPointer->Begin();
	}
	
	void Asynchronous::End()
	{
		InternalPointer->End();
	}
	
	DataStream^ Asynchronous::GetData()
	{
		return GetData( AsynchronousFlags::None );
	}
	
	DataStream^ Asynchronous::GetData( AsynchronousFlags flags )
	{
		int size = InternalPointer->GetDataSize();
		DataStream^ result = gcnew DataStream( size, true, true );
		if( RECORD_D3D11( InternalPointer->GetData( result->RawPointer, size, static_cast<UINT>( flags ) ) ).IsFailure )
			return nullptr;
		return result;
	}*/
}
}
