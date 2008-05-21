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
	XFile::XFile()
	{
		ID3DXFile *result;

		HRESULT hr = D3DXFileCreate( &result );
		
		if( RECORD_D3D9(hr).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(result);
	}

	XFile::XFile( ID3DXFile* pointer )
	{
		Construct( pointer );
	}

	XFile::XFile( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	XFile^ XFile::FromPointer( ID3DXFile* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		XFile^ tableEntry = safe_cast<XFile^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return XFile::FromPointer( pointer );
	}

	XFile^ XFile::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		XFile^ tableEntry = safe_cast<XFile^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew XFile( pointer );
	}

	XFileEnumerationObject^ XFile::CreateEnumerationObject( String^ fileName, CharSet charSet )
	{
		ID3DXFileEnumObject *result;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( fileName );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		DWORD flag;
		if( charSet == CharSet::Unicode )
			flag = D3DXF_FILELOAD_FROMWFILE;
		else
			flag = D3DXF_FILELOAD_FROMFILE;

		HRESULT hr = InternalPointer->CreateEnumObject( reinterpret_cast<LPCVOID>( pinnedName ), flag, &result );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		return XFileEnumerationObject::FromPointer( result );
	}

	XFileEnumerationObject^ XFile::CreateEnumerationObject( array<Byte>^ memory )
	{
		ID3DXFileEnumObject *result;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		D3DXF_FILELOADMEMORY mem;
		mem.lpMemory = reinterpret_cast<LPCVOID>( pinnedMemory );
		mem.dSize = memory->Length;

		HRESULT hr = InternalPointer->CreateEnumObject( reinterpret_cast<LPCVOID>( &mem ), D3DXF_FILELOAD_FROMMEMORY, &result );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		return XFileEnumerationObject::FromPointer( result );
	}

	XFileEnumerationObject^ XFile::CreateEnumerationObject( Stream^ memory )
	{
		array<Byte>^ data = Utilities::ReadStream( memory, 0 );
		return CreateEnumerationObject( data );
	}

	XFileSaveObject^ XFile::CreateSaveObject( String^ fileName, CharSet charSet, XFileFormat format )
	{
		ID3DXFileSaveObject *result;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( fileName );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		DWORD flag;
		if( charSet == CharSet::Unicode )
			flag = D3DXF_FILESAVE_TOWFILE;
		else
			flag = D3DXF_FILESAVE_TOFILE;

		HRESULT hr = InternalPointer->CreateSaveObject( reinterpret_cast<LPCVOID>( pinnedName ), flag, static_cast<D3DXF_FILEFORMAT>( format ), &result );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		return XFileSaveObject::FromPointer( result );
	}

	Result XFile::RegisterEnumerationTemplates( XFileEnumerationObject^ enumerationObject )
	{
		HRESULT hr = InternalPointer->RegisterEnumTemplates( enumerationObject->InternalPointer );
		return RECORD_D3D9( hr );
	}

	Result XFile::RegisterTemplates( array<Byte>^ memory )
	{
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = InternalPointer->RegisterTemplates( reinterpret_cast<LPCVOID>( pinnedMemory ), memory->Length );
		return RECORD_D3D9( hr );
	}

	Result XFile::RegisterTemplates( Stream^ stream )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, 0 );
		return RegisterTemplates( data );
	}

	Result XFile::RegisterTemplates( String^ name )
	{
		array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		return RegisterTemplates( nameBytes );
	}
}
}