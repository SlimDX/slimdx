/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include <d3dx10.h>
#include <vcclr.h>

#include "../DataStream.h"

#include "Direct3D10Exception.h"

#include "MeshBuffer.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{
	MeshBuffer::MeshBuffer( ID3DX10MeshBuffer* pointer )
	{
		Construct( pointer );
	}
	
	MeshBuffer::MeshBuffer( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	MeshBuffer^ MeshBuffer::FromPointer( ID3DX10MeshBuffer* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		MeshBuffer^ tableEntry = safe_cast<MeshBuffer^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew MeshBuffer( pointer );
	}

	MeshBuffer^ MeshBuffer::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		MeshBuffer^ tableEntry = safe_cast<MeshBuffer^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew MeshBuffer( pointer );
	}
	
	int MeshBuffer::SizeInBytes::get() 
	{
		return static_cast<int>( InternalPointer->GetSize() );
	}

	DataStream^ MeshBuffer::Map()
	{
		void* mappedPtr = 0;
		SIZE_T mappedSize = 0;
		if( RECORD_D3D10( InternalPointer->Map( &mappedPtr, &mappedSize ) ).IsFailure )
			return nullptr;
		
		return gcnew DataStream( mappedPtr, mappedSize, true, true, false );
	}

	Result MeshBuffer::Unmap()
	{
		return RECORD_D3D10( InternalPointer->Unmap() );
	}
}
}
