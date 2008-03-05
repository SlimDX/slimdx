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
#include <d3d9.h>
#include <d3dx9.h>

#include "../ComObject.h"
#include "../DataStream.h"
#include "../StackAlloc.h"
#include "XFile.h"

#include "Direct3D9Exception.h"

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace Direct3D9
{
	XFileSaveObject::XFileSaveObject( ID3DXFileSaveObject* pointer )
	{
		Construct( pointer );
	}

	XFileSaveObject::XFileSaveObject( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	XFileSaveObject^ XFileSaveObject::FromPointer( ID3DXFileSaveObject* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		XFileSaveObject^ tableEntry = safe_cast<XFileSaveObject^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew XFileSaveObject( pointer );
	}

	XFileSaveObject^ XFileSaveObject::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		XFileSaveObject^ tableEntry = safe_cast<XFileSaveObject^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew XFileSaveObject( pointer );
	}

	XFileSaveData^ XFileSaveObject::AddDataObject( Guid dataTemplate, String^ name, Guid id, array<Byte>^ data )
	{
		ID3DXFileSaveData *result;
		GUID nativeId = Utilities::ConvertManagedGuid( id );
		GUID *pointer = &nativeId;
		if( id == Guid::Empty )
			pointer = NULL;

		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		pin_ptr<unsigned char> pinnedMemory = &data[0];

		HRESULT hr = InternalPointer->AddDataObject( Utilities::ConvertManagedGuid( dataTemplate ), reinterpret_cast<LPCSTR>( pinnedName ), pointer, 
			data->Length, reinterpret_cast<LPCVOID>( pinnedMemory ), &result );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		return XFileSaveData::FromPointer( result );
	}

	XFileSaveData^ XFileSaveObject::AddDataObject( Guid dataTemplate, String^ name, Guid id, Stream^ data )
	{
		array<Byte>^ memory = Utilities::ReadStream( data, 0 );
		return AddDataObject( dataTemplate, name, id, memory );
	}

	XFile^ XFileSaveObject::GetFile()
	{
		ID3DXFile* result;

		HRESULT hr = InternalPointer->GetFile( &result );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		return XFile::FromPointer( result );
	}

	Result XFileSaveObject::Save()
	{
		HRESULT hr = InternalPointer->Save();
		return RECORD_D3D9( hr );
	}
}
}