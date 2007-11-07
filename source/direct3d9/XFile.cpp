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
#include <d3d9.h>
#include <d3dx9.h>

#include "../DirectXObject.h"
#include "../DataStream.h"
#include "GraphicsException.h"
#include "XFile.h"

namespace SlimDX
{
namespace Direct3D9
{
	XFileSaveData::XFileSaveData( ID3DXFileSaveData *object ) : DirectXObject( object )
	{
	}

	XFileSaveData^ XFileSaveData::AddDataObject( Guid dataTemplate, String^ name, Guid id, array<Byte>^ data )
	{
		ID3DXFileSaveData *result;
		GUID nativeId = Utils::ToGUID( id );
		GUID *pointer = &nativeId;
		if( id == Guid::Empty )
			pointer = NULL;

		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		pin_ptr<unsigned char> pinnedMemory = &data[0];

		HRESULT hr = m_Pointer->AddDataObject( Utils::ToGUID( dataTemplate ), (LPCSTR) pinnedName, pointer, 
			data->Length, (LPCVOID) pinnedMemory, &result );
		GraphicsException::CheckHResult( hr );

		return gcnew XFileSaveData( result );
	}

	XFileSaveData^ XFileSaveData::AddDataObject( Guid dataTemplate, String^ name, Guid id, Stream^ data )
	{
		array<Byte>^ memory = Utils::ReadStream( data, 0 );
		return AddDataObject( dataTemplate, name, id, memory );
	}

	void XFileSaveData::AddDataReference( String^ name, Guid id )
	{
		GUID nativeId = Utils::ToGUID( id );
		GUID *pointer = &nativeId;
		if( id == Guid::Empty )
			pointer = NULL;

		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		HRESULT hr = m_Pointer->AddDataReference( (LPCSTR) pinnedName, pointer );
		GraphicsException::CheckHResult( hr );
	}

	Guid XFileSaveData::Id::get()
	{
		GUID guid;

		HRESULT hr = m_Pointer->GetId( &guid );
		GraphicsException::CheckHResult( hr );

		if( guid == GUID_NULL )
			return Guid::Empty;

		return Utils::FromGUID( guid );
	}

	String^ XFileSaveData::Name::get()
	{
		char *name;
		SIZE_T size = 0;

		HRESULT hr = m_Pointer->GetName( NULL, &size );
		GraphicsException::CheckHResult( hr );

		name = new char[size];

		hr = m_Pointer->GetName( name, &size );
		GraphicsException::CheckHResult( hr );

		delete name;

		return gcnew String( name );
	}

	XFileSaveObject^ XFileSaveData::SaveObject::get()
	{
		ID3DXFileSaveObject *result;

		HRESULT hr = m_Pointer->GetSave( &result );
		GraphicsException::CheckHResult( hr );

		return gcnew XFileSaveObject( result );
	}

	Guid XFileSaveData::Type::get()
	{
		GUID result;

		HRESULT hr = m_Pointer->GetType( &result );
		GraphicsException::CheckHResult( hr );

		return Utils::FromGUID( result );
	}

	XFileSaveObject::XFileSaveObject( ID3DXFileSaveObject *object ) : DirectXObject( object )
	{
	}

	XFileSaveData^ XFileSaveObject::AddDataObject( Guid dataTemplate, String^ name, Guid id, array<Byte>^ data )
	{
		ID3DXFileSaveData *result;
		GUID nativeId = Utils::ToGUID( id );
		GUID *pointer = &nativeId;
		if( id == Guid::Empty )
			pointer = NULL;

		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		pin_ptr<unsigned char> pinnedMemory = &data[0];

		HRESULT hr = m_Pointer->AddDataObject( Utils::ToGUID( dataTemplate ), (LPCSTR) pinnedName, pointer, 
			data->Length, (LPCVOID) pinnedMemory, &result );
		GraphicsException::CheckHResult( hr );

		return gcnew XFileSaveData( result );
	}

	XFileSaveData^ XFileSaveObject::AddDataObject( Guid dataTemplate, String^ name, Guid id, Stream^ data )
	{
		array<Byte>^ memory = Utils::ReadStream( data, 0 );
		return AddDataObject( dataTemplate, name, id, memory );
	}

	XFile^ XFileSaveObject::GetFile()
	{
		ID3DXFile* result;

		HRESULT hr = m_Pointer->GetFile( &result );
		GraphicsException::CheckHResult( hr );

		return gcnew XFile( result );
	}

	void XFileSaveObject::Save()
	{
		HRESULT hr = m_Pointer->Save();
		GraphicsException::CheckHResult( hr );
	}

	XFile::XFile( ID3DXFile *object ) : DirectXObject( object )
	{
	}

	XFile::XFile()
	{
		ID3DXFile *result;

		HRESULT hr = D3DXFileCreate( &result );
		GraphicsException::CheckHResult( hr );

		m_Pointer = result;
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

		HRESULT hr = m_Pointer->CreateEnumObject( (LPCVOID) pinnedName, flag, &result );
		GraphicsException::CheckHResult( hr );

		return gcnew XFileEnumerationObject( result );
	}

	XFileEnumerationObject^ XFile::CreateEnumerationObject( array<Byte>^ memory )
	{
		ID3DXFileEnumObject *result;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		D3DXF_FILELOADMEMORY mem;
		mem.lpMemory = (LPCVOID) pinnedMemory;
		mem.dSize = memory->Length;

		HRESULT hr = m_Pointer->CreateEnumObject( (LPCVOID) &mem, D3DXF_FILELOAD_FROMMEMORY, &result );
		GraphicsException::CheckHResult( hr );

		return gcnew XFileEnumerationObject( result );
	}

	XFileEnumerationObject^ XFile::CreateEnumerationObject( Stream^ memory )
	{
		array<Byte>^ data = Utils::ReadStream( memory, 0 );
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

		HRESULT hr = m_Pointer->CreateSaveObject( (LPCVOID) pinnedName, flag, (D3DXF_FILEFORMAT) format, &result );
		GraphicsException::CheckHResult( hr );

		return gcnew XFileSaveObject( result );
	}

	void XFile::RegisterEnumerationTemplates( XFileEnumerationObject^ enumerationObject )
	{
		HRESULT hr = m_Pointer->RegisterEnumTemplates( enumerationObject->InternalPointer );
		GraphicsException::CheckHResult( hr );
	}

	void XFile::RegisterTemplates( array<Byte>^ memory )
	{
		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = m_Pointer->RegisterTemplates( (LPCVOID) pinnedMemory, memory->Length );
		GraphicsException::CheckHResult( hr );
	}

	void XFile::RegisterTemplates( Stream^ stream )
	{
		array<Byte>^ data = Utils::ReadStream( stream, 0 );
		RegisterTemplates( data );
	}

	void XFile::RegisterTemplates( String^ name )
	{
		array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		RegisterTemplates( nameBytes );
	}

	XFileEnumerationObject::XFileEnumerationObject( ID3DXFileEnumObject *object ) : DirectXObject( object )
	{
	}

	XFileData^ XFileEnumerationObject::GetChild( int id )
	{
		ID3DXFileData *result;

		HRESULT hr = m_Pointer->GetChild( id, &result );
		GraphicsException::CheckHResult( hr );

		return gcnew XFileData( result );
	}

	XFileData^ XFileEnumerationObject::GetDataObject( Guid id )
	{
		ID3DXFileData *result;

		HRESULT hr = m_Pointer->GetDataObjectById( Utils::ToGUID( id ), &result );
		GraphicsException::CheckHResult( hr );

		return gcnew XFileData( result );
	}

	XFileData^ XFileEnumerationObject::GetDataObject( String^ name )
	{
		ID3DXFileData *result;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		HRESULT hr = m_Pointer->GetDataObjectByName( (LPCSTR) pinnedName, &result );
		GraphicsException::CheckHResult( hr );

		return gcnew XFileData( result );
	}

	XFile^ XFileEnumerationObject::GetFile()
	{
		ID3DXFile *result;

		HRESULT hr = m_Pointer->GetFile( &result );
		GraphicsException::CheckHResult( hr );

		return gcnew XFile( result );
	}

	int XFileEnumerationObject::ChildCount::get()
	{
		SIZE_T result;

		HRESULT hr = m_Pointer->GetChildren( &result );
		GraphicsException::CheckHResult( hr );

		return result;
	}

	XFileData::XFileData( ID3DXFileData *object ) : DirectXObject( object )
	{
	}

	XFileData^ XFileData::GetChild( int id )
	{
		ID3DXFileData *result;

		HRESULT hr = m_Pointer->GetChild( id, &result );
		GraphicsException::CheckHResult( hr );

		return gcnew XFileData( result );
	}

	XFileEnumerationObject^ XFileData::GetEnumerationObject()
	{
		ID3DXFileEnumObject *result;

		HRESULT hr = m_Pointer->GetEnum( &result );
		GraphicsException::CheckHResult( hr );

		return gcnew XFileEnumerationObject( result );
	}

	DataStream^ XFileData::Lock()
	{
		SIZE_T size;
		const void *data;

		HRESULT hr = m_Pointer->Lock( &size, &data );
		GraphicsException::CheckHResult( hr );

		return gcnew DataStream( const_cast<void*>( data ), size, true, true, true );
	}

	void XFileData::Unlock()
	{
		HRESULT hr = m_Pointer->Unlock();
		GraphicsException::CheckHResult( hr );
	}

	int XFileData::ChildCount::get()
	{
		SIZE_T result;

		HRESULT hr = m_Pointer->GetChildren( &result );
		GraphicsException::CheckHResult( hr );

		return result;
	}

	Guid XFileData::Id::get()
	{
		GUID guid;

		HRESULT hr = m_Pointer->GetId( &guid );
		GraphicsException::CheckHResult( hr );

		if( guid == GUID_NULL )
			return Guid::Empty;

		return Utils::FromGUID( guid );
	}

	String^ XFileData::Name::get()
	{
		char *name;
		SIZE_T size = 0;

		HRESULT hr = m_Pointer->GetName( NULL, &size );
		GraphicsException::CheckHResult( hr );

		name = new char[size];

		hr = m_Pointer->GetName( name, &size );
		GraphicsException::CheckHResult( hr );

		delete name;

		return gcnew String( name );
	}

	Guid XFileData::Type::get()
	{
		GUID result;

		HRESULT hr = m_Pointer->GetType( &result );
		GraphicsException::CheckHResult( hr );

		return Utils::FromGUID( result );
	}

	bool XFileData::IsReference::get()
	{
		if( m_Pointer->IsReference() )
			return true;
		else
			return false;
	}
}
}