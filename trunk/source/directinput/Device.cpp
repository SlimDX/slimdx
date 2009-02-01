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
#include <windows.h>
#include <dinput.h>
#include <vector>

#include "../ComObject.h"
#include "../Utilities.h"

#include "DirectInput.h"
#include "DirectInputException.h"

#include "Device.h"
#include "KeyboardState.h"
#include "JoystickState.h"
#include "MouseState.h"
#include "Callbacks.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Reflection;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Forms;

namespace SlimDX
{
namespace DirectInput
{
	Result RecordError( HRESULT hr )
	{
		if( hr == DIERR_OTHERAPPHASPRIO || hr == DIERR_INPUTLOST )
			return Result::Record<DirectInputException^>( hr, false, nullptr, nullptr );
		else
			return RECORD_DINPUT( hr );
	}

	generic<typename DataFormat>
	Device<DataFormat>::Device( IDirectInputDevice8W* device, ComObject^ owner )
	{
		Construct(device, owner);

		properties = gcnew DeviceProperties( InternalPointer );
	}

	generic<typename DataFormat>
	Device<DataFormat>::Device( IntPtr device )
	{
		Construct( device, NativeInterface );
		properties = gcnew DeviceProperties( InternalPointer );
	}

	generic<typename DataFormat>
	Device<DataFormat>::Device( Guid subsystem )
	{
		IDirectInputDevice8W* device;
		HRESULT hr = DirectInput::InternalPointer->CreateDevice( Utilities::ConvertManagedGuid( subsystem ), &device, NULL );

		if( RECORD_DINPUT( hr ).IsFailure )
			throw gcnew DirectInputException( Result::Last );

		Construct(device);

		Type^ type = DataFormat::typeid;
		if( type == KeyboardState::typeid )
			hr = InternalPointer->SetDataFormat( &c_dfDIKeyboard );
		else if( type == MouseState::typeid )
			hr = InternalPointer->SetDataFormat( &c_dfDIMouse2 );
		else if( type == JoystickState::typeid )
			hr = InternalPointer->SetDataFormat( &c_dfDIJoystick2 );
		else
		{
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
			format.dwDataSize = (DWORD) sizeof( type );
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
			hr = InternalPointer->SetDataFormat( &format );

			for( int i = 0; i < objectAttributes->Count; i++ )
				delete objectFormats[i].pguid;
		}

		if( RECORD_DINPUT( hr ).IsFailure )
			throw gcnew DirectInputException( Result::Last );

		properties = gcnew DeviceProperties( InternalPointer );
	}

	generic<typename DataFormat>
	Device<DataFormat>^ Device<DataFormat>::FromPointer( IDirectInputDevice8W* pointer, ComObject^ owner, ComObjectFlags flags )
	{
		if( pointer == 0 )
			return nullptr;

		Device^ tableEntry = safe_cast<Device^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			if( static_cast<int>( flags & ComObjectFlags::ExternalReferenceCount ) == 0 ) 
					pointer->Release();
			return tableEntry;
		}

		Device^ result = gcnew Device( pointer, owner );
		result->SetFlags( flags );
		return result;
	}

	generic<typename DataFormat>
	Device<DataFormat>^ Device<DataFormat>::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		Device^ tableEntry = safe_cast<Device^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew Device( pointer );
	}

	generic<typename DataFormat>
	Result Device<DataFormat>::SetCooperativeLevel( IntPtr handle, CooperativeLevel flags )
	{
		HRESULT hr = InternalPointer->SetCooperativeLevel( static_cast<HWND>( handle.ToPointer() ), static_cast<DWORD>( flags ) );
		return RECORD_DINPUT( hr );
	}

	generic<typename DataFormat>
	Result Device<DataFormat>::SetCooperativeLevel( Control^ control, CooperativeLevel flags )
	{
		return SetCooperativeLevel( control->Handle, flags );
	}

	generic<typename DataFormat>
	Result Device<DataFormat>::Acquire()
	{
		HRESULT hr = InternalPointer->Acquire();
		return RecordError( hr );
	}

	generic<typename DataFormat>
	Result Device<DataFormat>::Unacquire()
	{
		HRESULT hr = InternalPointer->Unacquire();
		return RecordError( hr );
	}

	generic<typename DataFormat>
	Result Device<DataFormat>::Poll()
	{
		HRESULT hr = InternalPointer->Poll();
		return RecordError( hr );
	}

	generic<typename DataFormat>
	Result Device<DataFormat>::RunControlPanel()
	{
		HRESULT hr = InternalPointer->RunControlPanel( NULL, 0 );
		return RECORD_DINPUT( hr );
	}

	generic<typename DataFormat>
	Result Device<DataFormat>::RunControlPanel( Control^ parent )
	{
		HRESULT hr = InternalPointer->RunControlPanel( static_cast<HWND>( parent->Handle.ToPointer() ), 0 );
		return RECORD_DINPUT( hr );
	}

	generic<typename DataFormat>
	BufferedDataCollection<DataFormat>^ Device<DataFormat>::GetBufferedData()
	{
		DWORD size = INFINITE;
		HRESULT hr = InternalPointer->GetDeviceData( sizeof( DIDEVICEOBJECTDATA ), NULL, &size, DIGDD_PEEK );
		if( RecordError( hr ).IsFailure )
			return nullptr;

		BufferedDataCollection<DataFormat>^ list = gcnew BufferedDataCollection<DataFormat>( size );

		if( size == 0 )
			return list;

		std::vector<DIDEVICEOBJECTDATA> data( size );
		hr = InternalPointer->GetDeviceData( sizeof( DIDEVICEOBJECTDATA ), &data[0], &size, 0 );
		if( RecordError( hr ).IsFailure )
			return nullptr;

		if( size == 0 )
			return list;

		for( unsigned int i = 0; i < size; i++ )
		{
			BufferedData<DataFormat>^ bufferedData = gcnew BufferedData<DataFormat>( data[i] );
			list->Add( bufferedData );
		}

		return list;
	}

	generic<typename DataFormat>
	Result Device<DataFormat>::GetCurrentState( DataFormat% data )
	{
		Type^ type = DataFormat::typeid;

		if( type == KeyboardState::typeid )
		{
			BYTE keys[256];
			HRESULT hr = InternalPointer->GetDeviceState( sizeof( BYTE ) * 256, keys );
			if( RecordError( hr ).IsFailure )
				return Result::Last;

			KeyboardState^ state = safe_cast<KeyboardState^>( data );
			state->UpdateKeys( keys, 256 );
		}
		else if( type == MouseState::typeid )
		{
			DIMOUSESTATE2 state;
			HRESULT hr = InternalPointer->GetDeviceState( sizeof( DIMOUSESTATE2 ), &state );
			if( RecordError( hr ).IsFailure )
				return Result::Last;

			MouseState^ result = safe_cast<MouseState^>( data );
			result->AssignState(state);
		}
		else if( type == JoystickState::typeid )
		{
			DIJOYSTATE2 joystate;
			HRESULT hr = InternalPointer->GetDeviceState( sizeof( DIJOYSTATE2 ), &joystate );
			if( RecordError( hr ).IsFailure )
				return Result::Last;

			JoystickState^ state = safe_cast<JoystickState^>( data );
			state->AssignState(joystate);
		}
		else
		{
			size_t typeSize = sizeof(type);
			std::vector<BYTE> bytes(typeSize);
			HRESULT hr = InternalPointer->GetDeviceState( static_cast<DWORD>(sizeof(BYTE) * typeSize), &bytes[0] );
			if( RecordError( hr ).IsFailure )
				return Result::Last;

			IntPtr pointerData( &bytes[0] );
			GCHandle handle = GCHandle::Alloc( data, GCHandleType::Pinned );
			memcpy( handle.AddrOfPinnedObject().ToPointer(), pointerData.ToPointer(), typeSize );
			handle.Free();
		}

		return Result::Last;
	}

	generic<typename DataFormat>
	DataFormat Device<DataFormat>::GetCurrentState()
	{
		DataFormat result = Activator::CreateInstance<DataFormat>();
		GetCurrentState( result );
		return result;
	}

	generic<typename DataFormat>
	ObjectProperties^ Device<DataFormat>::GetObjectPropertiesById( int objectId )
	{
		return gcnew ObjectProperties( InternalPointer, objectId, false );
	}

	generic<typename DataFormat>
	ObjectProperties^ Device<DataFormat>::GetObjectPropertiesByUsage( int usageCode )
	{
		return gcnew ObjectProperties( InternalPointer, usageCode, true );
	}

	generic<typename DataFormat>
	ObjectProperties^ Device<DataFormat>::GetObjectPropertiesByName( String^ name )
	{
		return gcnew ObjectProperties( InternalPointer, name, DataFormat::typeid );
	}

	generic<typename DataFormat>
	DeviceProperties^ Device<DataFormat>::Properties::get()
	{
		return properties;
	}

	generic<typename DataFormat>
	Capabilities^ Device<DataFormat>::Caps::get()
	{
		if( caps != nullptr )
			return caps;

		DIDEVCAPS c;
		c.dwSize = sizeof(DIDEVCAPS);
		HRESULT hr = InternalPointer->GetCapabilities( &c );
		
		if( RECORD_DINPUT( hr ).IsFailure )
			caps = nullptr;

		caps = gcnew Capabilities( c );

		return caps;
	}

	generic<typename DataFormat>
	DeviceInstance^ Device<DataFormat>::DeviceInformation::get()
	{
		if( information != nullptr )
			return information;

		DIDEVICEINSTANCE deviceInstance;
		deviceInstance.dwSize = sizeof(DIDEVICEINSTANCE);
		HRESULT hr = InternalPointer->GetDeviceInfo( &deviceInstance );
		
		if( RECORD_DINPUT( hr ).IsFailure )
			information = nullptr;

		information = gcnew DeviceInstance( deviceInstance );

		return information;
	}

	generic<typename DataFormat>
	DeviceObjectCollection^ Device<DataFormat>::GetDeviceObjects()
	{
		return GetDeviceObjects( ObjectDeviceType::All );
	}

	generic<typename DataFormat>
	DeviceObjectCollection^ Device<DataFormat>::GetDeviceObjects( ObjectDeviceType objectType )
	{
		DeviceObjectCollection^ results = gcnew DeviceObjectCollection();
		DeviceObjectCollectionShim shim( results );

		HRESULT hr = InternalPointer->EnumObjects( static_cast<LPDIENUMDEVICEOBJECTSCALLBACK>( EnumerateObjects ), &shim, static_cast<DWORD>( objectType ) );
		if( RECORD_DINPUT( hr ).IsFailure )
			return nullptr;

		return results;
	}

	generic<typename DataFormat>
	array<Byte>^ Device<DataFormat>::Escape( int command, array<Byte>^ data, int outputSize )
	{
		array<Byte>^ output = gcnew array<Byte>( outputSize );

		pin_ptr<Byte> pinnedData = &data[0];
		pin_ptr<Byte> pinnedOutput = &output[0];

		DIEFFESCAPE input;
		input.dwSize = sizeof(DIEFFESCAPE);
		input.dwCommand = command;
		input.cbInBuffer = data->Length;
		input.cbOutBuffer = output->Length;
		input.lpvInBuffer = pinnedData;
		input.lpvOutBuffer = pinnedOutput;

		HRESULT hr = InternalPointer->Escape( &input );
		if( RECORD_DINPUT( hr ).IsFailure )
			return nullptr;

		return output;
	}
}
}
