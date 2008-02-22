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
#include <windows.h>
#include <dinput.h>

#include "../ComObject.h"
#include "../Utilities.h"

#include "DirectInput.h"
#include "DirectInputException.h"

#include "Device.h"

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
	Device<DataFormat>::Device( IDirectInputDevice8W* device )
	{
		Construct(device);

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

		if( Result::Record( hr ).IsFailure )
			throw gcnew DirectInputException();

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
			format.dwDataSize = Marshal::SizeOf( type );
			format.dwNumObjs = objectAttributes->Count;

			DIOBJECTDATAFORMAT *objectFormats = new DIOBJECTDATAFORMAT[objectAttributes->Count];
			for( int i = 0; i < objectAttributes->Count; i++ )
			{
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

			format.rgodf = objectFormats;
			hr = InternalPointer->SetDataFormat( &format );

			for( int i = 0; i < objectAttributes->Count; i++ )
				delete objectFormats[i].pguid;
			delete[] objectFormats;
		}

		if( Result::Record( hr ).IsFailure )
			throw gcnew DirectInputException();

		properties = gcnew DeviceProperties( InternalPointer );
	}

	generic<typename DataFormat>
	Result Device<DataFormat>::SetCooperativeLevel( IntPtr handle, CooperativeLevel flags )
	{
		HRESULT hr = InternalPointer->SetCooperativeLevel( static_cast<HWND>( handle.ToPointer() ), static_cast<DWORD>( flags ) );
		return Result::Record( hr );
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
		return Result::Record( hr );
	}

	generic<typename DataFormat>
	Result Device<DataFormat>::Unacquire()
	{
		HRESULT hr = InternalPointer->Unacquire();
		return Result::Record( hr );
	}

	generic<typename DataFormat>
	Result Device<DataFormat>::Poll()
	{
		HRESULT hr = InternalPointer->Poll();
		return Result::Record( hr );
	}

	generic<typename DataFormat>
	Result Device<DataFormat>::RunControlPanel()
	{
		HRESULT hr = InternalPointer->RunControlPanel( NULL, 0 );
		return Result::Record( hr );
	}

	generic<typename DataFormat>
	Result Device<DataFormat>::RunControlPanel( Control^ parent )
	{
		HRESULT hr = InternalPointer->RunControlPanel( static_cast<HWND>( parent->Handle.ToPointer() ), 0 );
		return Result::Record( hr );
	}

	generic<typename DataFormat>
	BufferedDataCollection<DataFormat>^ Device<DataFormat>::GetBufferedData()
	{
		BufferedDataCollection<DataFormat>^ list = gcnew BufferedDataCollection<DataFormat>();

		int size = INFINITE;
		HRESULT hr = InternalPointer->GetDeviceData( sizeof( DIDEVICEOBJECTDATA ), NULL, reinterpret_cast<LPDWORD>( &size ), DIGDD_PEEK );
		Result::Record( hr );

		if( hr == DI_BUFFEROVERFLOW && &Device::BufferOverflow != nullptr )
			BufferOverflow( this, EventArgs::Empty );

		if( hr == DIERR_INPUTLOST && &Device::DeviceLost != nullptr )
			DeviceLost( this, EventArgs::Empty );

		if( FAILED( hr ) )
			return nullptr;

		DIDEVICEOBJECTDATA *data = new DIDEVICEOBJECTDATA[size];
		hr = InternalPointer->GetDeviceData( sizeof( DIDEVICEOBJECTDATA ), data, reinterpret_cast<LPDWORD>( &size ), 0 );
		Result::Record( hr );

		if( hr == DI_BUFFEROVERFLOW && &Device::BufferOverflow != nullptr )
			BufferOverflow( this, EventArgs::Empty );

		if( hr == DIERR_INPUTLOST && &Device::DeviceLost != nullptr )
			DeviceLost( this, EventArgs::Empty );

		if( FAILED( hr ) )
		{
			delete[] data;
			return nullptr;
		}

		for( int i = 0; i < size; i++ )
		{
			BufferedData<DataFormat>^ bufferedData = gcnew BufferedData<DataFormat>( data[i] );
			list->Add( bufferedData );
		}

		delete[] data;

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
			Result::Record( hr );

			if( hr == DIERR_INPUTLOST )
			{
				if( &Device::DeviceLost != nullptr )
					DeviceLost( this, EventArgs::Empty );
				return Result::Last;
			}

			KeyboardState^ state = reinterpret_cast<KeyboardState^>( data );
			for( int i = 0; i < 256; i++ )
			{
				if( keys[i] )
					state->keys[i] = true;
				else
					state->keys[i] = false;
			}
		}
		else if( type == MouseState::typeid )
		{
			DIMOUSESTATE2 state;
			HRESULT hr = InternalPointer->GetDeviceState( sizeof( DIMOUSESTATE2 ), &state );
			Result::Record( hr );

			if( hr == DIERR_INPUTLOST )
			{
				if( &Device::DeviceLost != nullptr )
					DeviceLost( this, EventArgs::Empty );
				return Result::Last;
			}

			MouseState^ result = reinterpret_cast<MouseState^>( data );
			for( int i = 0; i < 8; i++ )
			{
				if( state.rgbButtons[i] & 0x80 )
					result->buttons[i] = true;
				else
					result->buttons[i] = false;
			}
		}
		else if( type == JoystickState::typeid )
		{
			DIJOYSTATE2 joystate;
			HRESULT hr = InternalPointer->GetDeviceState( sizeof( DIJOYSTATE2 ), &joystate );
			Result::Record( hr );

			if( hr == DIERR_INPUTLOST )
			{
				if( &Device::DeviceLost != nullptr )
					DeviceLost( this, EventArgs::Empty );
				return Result::Last;
			}

			JoystickState^ state = reinterpret_cast<JoystickState^>( data );
			state->x = joystate.lX;
			state->y = joystate.lY;
			state->z = joystate.lZ;
			state->rx = joystate.lRx;
			state->ry = joystate.lRy;
			state->rz = joystate.lRz;
			state->vx = joystate.lVX;
			state->vy = joystate.lVY;
			state->vz = joystate.lVZ;
			state->vrx = joystate.lVRx;
			state->vry = joystate.lVRy;
			state->vrz = joystate.lVRz;
			state->ax = joystate.lAX;
			state->ay = joystate.lAY;
			state->az = joystate.lAZ;
			state->arx = joystate.lARx;
			state->ary = joystate.lARy;
			state->arz = joystate.lARz;
			state->fx = joystate.lFX;
			state->fy = joystate.lFY;
			state->fz = joystate.lFZ;
			state->frx = joystate.lFRx;
			state->fry = joystate.lFRy;
			state->frz = joystate.lFRz;

			for( int i = 0; i < 2; i++ )
			{
				state->sliders[i] = joystate.rglSlider[i];
				state->asliders[i] = joystate.rglASlider[i];
				state->vsliders[i] = joystate.rglVSlider[i];
				state->fsliders[i] = joystate.rglVSlider[i];
			}

			for( int i = 0; i < 4; i++ )
				state->povs[i] = joystate.rgdwPOV[i];

			for( int i = 0; i < 128; i++ )
			{
				if( joystate.rgbButtons[i] )
					state->buttons[i] = true;
				else
					state->buttons[i] = false;
			}
		}
		else
		{
			int typeSize = Marshal::SizeOf( type );
			BYTE *bytes = new BYTE[typeSize];
			HRESULT hr = InternalPointer->GetDeviceState( sizeof( BYTE ) * typeSize, bytes );
			Result::Record( hr );

			if( hr == DIERR_INPUTLOST )
			{
				if( &Device::DeviceLost != nullptr )
					DeviceLost( this, EventArgs::Empty );
				return Result::Last;
			}

			IntPtr pointerData( bytes );
			GCHandle handle = GCHandle::Alloc( data, GCHandleType::Pinned );
			memcpy( handle.AddrOfPinnedObject().ToPointer(), pointerData.ToPointer(), typeSize );
			handle.Free();

			delete[] bytes;
		}

		return Result::Last;
	}

	generic<typename DataFormat>
	DataFormat Device<DataFormat>::GetCurrentState()
	{
		Type^ type = DataFormat::typeid;

		if( type == KeyboardState::typeid )
		{
			BYTE keys[256];
			HRESULT hr = InternalPointer->GetDeviceState( sizeof( BYTE ) * 256, keys );
			Result::Record( hr );

			KeyboardState^ state = gcnew KeyboardState();

			if( hr == DIERR_INPUTLOST )
			{
				if( &Device::DeviceLost != nullptr )
					DeviceLost( this, EventArgs::Empty );
				return reinterpret_cast<DataFormat>( state );
			}

			for( int i = 0; i < 256; i++ )
			{
				if( keys[i] )
					state->keys[i] = true;
				else
					state->keys[i] = false;
			}

			return ( DataFormat )state;
		}
		else if( type == MouseState::typeid )
		{
			DIMOUSESTATE2 state;
			HRESULT hr = InternalPointer->GetDeviceState( sizeof( DIMOUSESTATE2 ), &state );
			Result::Record( hr );

			if( hr == DIERR_INPUTLOST )
			{
				if( &Device::DeviceLost != nullptr )
					DeviceLost( this, EventArgs::Empty );
				return reinterpret_cast<DataFormat>( gcnew MouseState( 0, 0, 0 ) );
			}

			MouseState^ result = gcnew MouseState( state.lX, state.lY, state.lZ );
			for( int i = 0; i < 8; i++ )
			{
				if( state.rgbButtons[i] & 0x80 )
					result->buttons[i] = true;
				else
					result->buttons[i] = false;
			}

			return ( DataFormat )result;
		}
		else if( type == JoystickState::typeid )
		{
			DIJOYSTATE2 state;
			HRESULT hr = InternalPointer->GetDeviceState( sizeof( DIJOYSTATE2 ), &state );
			Result::Record( hr );

			if( hr == DIERR_INPUTLOST )
			{
				if( &Device::DeviceLost != nullptr )
					DeviceLost( this, EventArgs::Empty );
				return reinterpret_cast<DataFormat>( gcnew JoystickState() );
			}

			return reinterpret_cast<DataFormat>( gcnew JoystickState( state ) );
		}
		else
		{
			int typeSize = Marshal::SizeOf( type );
			BYTE *bytes = new BYTE[typeSize];
			HRESULT hr = InternalPointer->GetDeviceState( sizeof( BYTE ) * typeSize, bytes );
			Result::Record( hr );

			if( hr == DIERR_INPUTLOST )
			{
				if( &Device::DeviceLost != nullptr )
					DeviceLost( this, EventArgs::Empty );
				return Activator::CreateInstance<DataFormat>();
			}

			DataFormat result = Activator::CreateInstance<DataFormat>();

			IntPtr pointerData( bytes );
			GCHandle handle = GCHandle::Alloc( result, GCHandleType::Pinned );
			memcpy( handle.AddrOfPinnedObject().ToPointer(), pointerData.ToPointer(), typeSize );
			handle.Free();

			delete[] bytes;

			return result;
		}
	}

	generic<typename DataFormat>
	DeviceProperties^ Device<DataFormat>::Properties::get()
	{
		return properties;
	}

	generic<typename DataFormat>
	Capabilities^ Device<DataFormat>::Caps::get()
	{
		DIDEVCAPS caps;
		HRESULT hr = InternalPointer->GetCapabilities( &caps );
		
		if( Result::Record( hr ).IsFailure )
			return nullptr;

		return gcnew Capabilities( caps );
	}

	generic<typename DataFormat>
	DeviceInstance^ Device<DataFormat>::DeviceInformation::get()
	{
		DIDEVICEINSTANCE deviceInstance;
		HRESULT hr = InternalPointer->GetDeviceInfo( &deviceInstance );
		
		if( Result::Record( hr ).IsFailure )
			return nullptr;

		return gcnew DeviceInstance( deviceInstance );
	}
}
}
