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
#include "stdafx.h"
#include <windows.h>
#include <dinput.h>
#include <vector>

#include "../ComObject.h"
#include "../Utilities.h"

#include "DirectInput.h"
#include "DirectInputException.h"

#include "DataFormatAttribute.h"
#include "DataObjectAttribute.h"
#include "CustomDevice.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Reflection;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Forms;

namespace SlimDX
{
namespace DirectInput
{
	generic<typename DataFormat>
	CustomDevice<DataFormat>::CustomDevice( IDirectInputDevice8* device, ComObject^ owner )
	{
		Construct( device, owner );
	}

	generic<typename DataFormat>
	CustomDevice<DataFormat>::CustomDevice( IntPtr device )
	{
		Construct( device, NativeInterface );
	}

	generic<typename DataFormat>
	CustomDevice<DataFormat>::CustomDevice( DirectInput^ directInput, Guid subsystem ) : Device( directInput, subsystem )
	{
		Type^ type = DataFormat::typeid;
		array<DataFormatAttribute^>^ formatAttributes = safe_cast<array<DataFormatAttribute^>^>( type->GetCustomAttributes(
			DataFormatAttribute::typeid, false ) );

		if( formatAttributes->Length != 1 )
			throw gcnew InvalidOperationException( "The data format must be marked with one and only one DataFormat attribute." );
		DataFormatAttribute^ formatAttribute = formatAttributes[0];

		List<DataObjectAttribute^>^ objectAttributes = gcnew List<DataObjectAttribute^>();
		array<FieldInfo^>^ fields = type->GetFields();
		for each( FieldInfo^ field in fields )
		{
			array<DataObjectAttribute^>^ attributes = safe_cast<array<DataObjectAttribute^>^>( field->GetCustomAttributes( 
				DataObjectAttribute::typeid, false ) );
			if( attributes->Length == 1 )
			{
				attributes[0]->Offset = Marshal::OffsetOf( type, field->Name ).ToInt32();
				objectAttributes->Add( attributes[0] );
			}
		}

		if( objectAttributes->Count < 1 )
			throw gcnew InvalidOperationException( "The data format must have at least one field marked with the DataObject attribute." );			

		DIDATAFORMAT format;
		format.dwSize = sizeof( DIDATAFORMAT );
		format.dwObjSize = sizeof( DIOBJECTDATAFORMAT );
		format.dwFlags = static_cast<DWORD>( formatAttribute->Flags );
		format.dwDataSize = static_cast<DWORD>( sizeof( type ) );
		format.dwNumObjs = objectAttributes->Count;

		std::vector<DIOBJECTDATAFORMAT> objectFormats( objectAttributes->Count );
		for( int i = 0; i < objectAttributes->Count; i++ )
		{
			// Manual Allocation: handled properly
			// we clean up just below. No methods in between throw exceptions
			GUID *guid = new GUID( Utilities::ConvertManagedGuid( objectAttributes[i]->SourceGuid ) );
			objectFormats[i].dwFlags = static_cast<DWORD>( objectAttributes[i]->Flags );
			objectFormats[i].dwType = static_cast<DWORD>( objectAttributes[i]->Type );
			objectFormats[i].pguid = guid;
			if( objectAttributes[i]->InstanceNumber == -1 )
				objectFormats[i].dwType |= DIDFT_ANYINSTANCE;
			else
				objectFormats[i].dwType |= DIDFT_MAKEINSTANCE( objectAttributes[i]->InstanceNumber );
			objectFormats[i].dwOfs = objectAttributes[i]->Offset;
		}

		format.rgodf = &objectFormats[0];
		HRESULT hr = InternalPointer->SetDataFormat( &format );

		for( int i = 0; i < objectAttributes->Count; i++ )
			delete objectFormats[i].pguid;

		if( RECORD_DINPUT( hr ).IsFailure )
			throw gcnew DirectInputException( Result::Last );
	}

	generic<typename DataFormat>
	CustomDevice<DataFormat>^ CustomDevice<DataFormat>::FromPointer( IDirectInputDevice8W* pointer, ComObject^ owner, ComObjectFlags flags )
	{
		if( pointer == 0 )
			return nullptr;

		CustomDevice<DataFormat>^ tableEntry = safe_cast<CustomDevice<DataFormat>^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			if( static_cast<int>( flags & ComObjectFlags::IsAncillary ) == 0 ) 
				pointer->Release();
			return tableEntry;
		}

		CustomDevice<DataFormat>^ result = gcnew CustomDevice<DataFormat>( pointer, owner );
		result->SetFlags( flags );
		return result;
	}

	generic<typename DataFormat>
	CustomDevice<DataFormat>^ CustomDevice<DataFormat>::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		CustomDevice<DataFormat>^ tableEntry = safe_cast<CustomDevice<DataFormat>^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew CustomDevice<DataFormat>( pointer );
	}

	generic<typename DataFormat>
	IList<DataFormat>^ CustomDevice<DataFormat>::GetBufferedData()
	{
		DWORD size = INFINITE;
		HRESULT hr = InternalPointer->GetDeviceData( sizeof( DIDEVICEOBJECTDATA ), NULL, &size, DIGDD_PEEK );
		if( RecordError( hr ).IsFailure )
			return nullptr;

		List<DataFormat>^ list = gcnew List<DataFormat>( size );
		if( size == 0 )
			return list;

		std::vector<DIDEVICEOBJECTDATA> data( size );
		hr = InternalPointer->GetDeviceData( sizeof( DIDEVICEOBJECTDATA ), &data[0], &size, 0 );
		if( RecordError( hr ).IsFailure )
			return nullptr;

		if( size == 0 )
			return list;

		Type^ type = DataFormat::typeid;
		array<FieldInfo^>^ fields = type->GetFields();

		for( unsigned int i = 0; i < size; i++ )
		{
			DataFormat dataPacket = safe_cast<DataFormat>( Activator::CreateInstance( type ) );
            for each( FieldInfo^ field in fields )
            {
				if( static_cast<unsigned int>( Marshal::OffsetOf( type, field->Name ).ToInt32() ) == data[i].dwOfs )
				{
					field->SetValue( dataPacket, data[i].dwData );
					break;
				}
            }

			list->Add( dataPacket );
		}

		return list;
	}

	generic<typename DataFormat>
	Result CustomDevice<DataFormat>::GetCurrentState( DataFormat% data )
	{
		Type^ type = DataFormat::typeid;
		size_t typeSize = sizeof( type );
		std::vector<BYTE> bytes( typeSize );

		HRESULT hr = InternalPointer->GetDeviceState( static_cast<DWORD>( typeSize ), &bytes[0] );
		if( RecordError( hr ).IsFailure )
			return Result::Last;

		IntPtr pointerData( &bytes[0] );
		GCHandle handle = GCHandle::Alloc( data, GCHandleType::Pinned );
		memcpy( handle.AddrOfPinnedObject().ToPointer(), pointerData.ToPointer(), typeSize );
		handle.Free();

		return Result::Last;
	}

	generic<typename DataFormat>
	DataFormat CustomDevice<DataFormat>::GetCurrentState()
	{
		DataFormat result = Activator::CreateInstance<DataFormat>();
		GetCurrentState( result );
		return result;
	}

	generic<typename DataFormat>
	ObjectProperties^ CustomDevice<DataFormat>::GetObjectPropertiesByName( String^ name )
	{
		return gcnew ObjectProperties( InternalPointer, name, DataFormat::typeid );
	}
}
}
