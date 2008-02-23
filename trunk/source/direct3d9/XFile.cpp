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
	XFileSaveData::XFileSaveData( ID3DXFileSaveData *object )
	{
		Construct(object);
	}

	XFileSaveData::XFileSaveData( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	XFileSaveData^ XFileSaveData::AddDataObject( Guid dataTemplate, String^ name, Guid id, array<Byte>^ data )
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
		
		if( Result::Record(hr).IsFailure )
			return nullptr;

		return gcnew XFileSaveData( result );
	}

	XFileSaveData^ XFileSaveData::AddDataObject( Guid dataTemplate, String^ name, Guid id, Stream^ data )
	{
		array<Byte>^ memory = Utilities::ReadStream( data, 0 );
		return AddDataObject( dataTemplate, name, id, memory );
	}

	Result XFileSaveData::AddDataReference( String^ name, Guid id )
	{
		GUID nativeId = Utilities::ConvertManagedGuid( id );
		GUID *pointer = &nativeId;
		if( id == Guid::Empty )
			pointer = NULL;

		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		HRESULT hr = InternalPointer->AddDataReference( reinterpret_cast<LPCSTR>( pinnedName ), pointer );
		return Result::Record( hr );
	}

	Guid XFileSaveData::Id::get()
	{
		GUID guid;

		HRESULT hr = InternalPointer->GetId( &guid );

		if( Result::Record(hr).IsFailure || guid == GUID_NULL )
			return Guid::Empty;

		return Utilities::ConvertNativeGuid( guid );
	}

	String^ XFileSaveData::Name::get()
	{
		stack_vector<char> name;
		SIZE_T size = 0;

		HRESULT hr = InternalPointer->GetName( NULL, &size );
		
		if( Result::Record(hr).IsFailure )
			return nullptr;

		name.resize( size );

		hr = InternalPointer->GetName( &name[0], &size );

		if( Result::Record(hr).IsFailure )
			return nullptr;

		return gcnew String( &name[0] );
	}

	XFileSaveObject^ XFileSaveData::SaveObject::get()
	{
		ID3DXFileSaveObject *result;

		HRESULT hr = InternalPointer->GetSave( &result );
		
		if( Result::Record(hr).IsFailure )
			return nullptr;

		return gcnew XFileSaveObject( result );
	}

	Guid XFileSaveData::Type::get()
	{
		GUID result;

		HRESULT hr = InternalPointer->GetType( &result );
		
		if( Result::Record(hr).IsFailure )
			return Guid::Empty;

		return Utilities::ConvertNativeGuid( result );
	}

	XFileSaveObject::XFileSaveObject( ID3DXFileSaveObject *object )
	{
		Construct(object);
	}

	XFileSaveObject::XFileSaveObject( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
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
		
		if( Result::Record(hr).IsFailure )
			return nullptr;

		return gcnew XFileSaveData( result );
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
		
		if( Result::Record(hr).IsFailure )
			return nullptr;

		return gcnew XFile( result );
	}

	Result XFileSaveObject::Save()
	{
		HRESULT hr = InternalPointer->Save();
		return Result::Record( hr );
	}

	XFile::XFile( ID3DXFile *object )
	{
		Construct(object);
	}

	XFile::XFile( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	XFile::XFile()
	{
		ID3DXFile *result;

		HRESULT hr = D3DXFileCreate( &result );
		
		if( Result::Record(hr).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(result);
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
		
		if( Result::Record(hr).IsFailure )
			return nullptr;

		return gcnew XFileEnumerationObject( result );
	}

	XFileEnumerationObject^ XFile::CreateEnumerationObject( array<Byte>^ memory )
	{
		ID3DXFileEnumObject *result;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		D3DXF_FILELOADMEMORY mem;
		mem.lpMemory = reinterpret_cast<LPCVOID>( pinnedMemory );
		mem.dSize = memory->Length;

		HRESULT hr = InternalPointer->CreateEnumObject( reinterpret_cast<LPCVOID>( &mem ), D3DXF_FILELOAD_FROMMEMORY, &result );
		
		if( Result::Record(hr).IsFailure )
			return nullptr;

		return gcnew XFileEnumerationObject( result );
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
		
		if( Result::Record(hr).IsFailure )
			return nullptr;

		return gcnew XFileSaveObject( result );
	}

	Result XFile::RegisterEnumerationTemplates( XFileEnumerationObject^ enumerationObject )
	{
		HRESULT hr = InternalPointer->RegisterEnumTemplates( enumerationObject->InternalPointer );
		return Result::Record( hr );
	}

	Result XFile::RegisterTemplates( array<Byte>^ memory )
	{
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = InternalPointer->RegisterTemplates( reinterpret_cast<LPCVOID>( pinnedMemory ), memory->Length );
		return Result::Record( hr );
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

	XFileEnumerationObject::XFileEnumerationObject( ID3DXFileEnumObject *object )
	{
		Construct(object);
	}

	XFileEnumerationObject::XFileEnumerationObject( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	XFileData^ XFileEnumerationObject::GetChild( int id )
	{
		ID3DXFileData *result;

		HRESULT hr = InternalPointer->GetChild( id, &result );

		if( Result::Record( hr ).IsFailure )
			return nullptr;

		return gcnew XFileData( result );
	}

	XFileData^ XFileEnumerationObject::GetDataObject( Guid id )
	{
		ID3DXFileData *result;

		HRESULT hr = InternalPointer->GetDataObjectById( Utilities::ConvertManagedGuid( id ), &result );
		
		if( Result::Record( hr ).IsFailure )
			return nullptr;

		return gcnew XFileData( result );
	}

	XFileData^ XFileEnumerationObject::GetDataObject( String^ name )
	{
		ID3DXFileData *result;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		HRESULT hr = InternalPointer->GetDataObjectByName( reinterpret_cast<LPCSTR>( pinnedName ), &result );
		
		if( Result::Record( hr ).IsFailure )
			return nullptr;

		return gcnew XFileData( result );
	}

	XFile^ XFileEnumerationObject::GetFile()
	{
		ID3DXFile *result;

		HRESULT hr = InternalPointer->GetFile( &result );
		
		if( Result::Record( hr ).IsFailure )
			return nullptr;

		return gcnew XFile( result );
	}

	int XFileEnumerationObject::ChildCount::get()
	{
		SIZE_T result;

		HRESULT hr = InternalPointer->GetChildren( &result );
		
		if( Result::Record( hr ).IsFailure )
			return 0;

		return result;
	}

	XFileData::XFileData( ID3DXFileData *object )
	{
		Construct(object);
	}

	XFileData::XFileData( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	XFileData^ XFileData::GetChild( int id )
	{
		ID3DXFileData *result;

		HRESULT hr = InternalPointer->GetChild( id, &result );
		
		if( Result::Record( hr ).IsFailure )
			return nullptr;

		return gcnew XFileData( result );
	}

	XFileEnumerationObject^ XFileData::GetEnumerationObject()
	{
		ID3DXFileEnumObject *result;

		HRESULT hr = InternalPointer->GetEnum( &result );
		
		if( Result::Record( hr ).IsFailure )
			return nullptr;

		return gcnew XFileEnumerationObject( result );
	}

	DataStream^ XFileData::Lock()
	{
		SIZE_T size;
		const void *data;

		HRESULT hr = InternalPointer->Lock( &size, &data );
		
		if( Result::Record( hr ).IsFailure )
			return nullptr;

		return gcnew DataStream( const_cast<void*>( data ), size, true, true, true );
	}

	Result XFileData::Unlock()
	{
		HRESULT hr = InternalPointer->Unlock();
		return Result::Record( hr );
	}

	int XFileData::ChildCount::get()
	{
		SIZE_T result;

		HRESULT hr = InternalPointer->GetChildren( &result );
		Result::Record( hr );

		if( FAILED( hr ) )
			return 0;

		return result;
	}

	Guid XFileData::Id::get()
	{
		GUID guid;

		HRESULT hr = InternalPointer->GetId( &guid );

		if( Result::Record( hr ).IsFailure || guid == GUID_NULL )
			return Guid::Empty;

		return Utilities::ConvertNativeGuid( guid );
	}

	String^ XFileData::Name::get()
	{
		stack_vector<char> name;
		SIZE_T size = 0;

		HRESULT hr = InternalPointer->GetName( NULL, &size );
		
		if( Result::Record( hr ).IsFailure )
			return nullptr;

		name.resize( size );

		hr = InternalPointer->GetName( &name[0], &size );

		if( Result::Record( hr ).IsFailure )
			return nullptr;

		return gcnew String( &name[0] );
	}

	Guid XFileData::Type::get()
	{
		GUID result;

		HRESULT hr = InternalPointer->GetType( &result );
		
		if( Result::Record( hr ).IsFailure )
			return Guid::Empty;

		return Utilities::ConvertNativeGuid( result );
	}

	bool XFileData::IsReference::get()
	{
		if( InternalPointer->IsReference() )
			return true;
		else
			return false;
	}
}
}