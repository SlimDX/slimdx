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
#include <windows.h>
#include <dinput.h>

#include "../DirectXObject.h"
#include "../Utils.h"
#include "DirectInput.h"
#include "Device.h"
#include "InputException.h"

namespace SlimDX
{
namespace DirectInput
{
	generic<typename DataFormat>
	Device<DataFormat>::Device( IDirectInputDevice8W* device ) : DirectXObject( device )
	{
		if( device == NULL )
			throw gcnew ArgumentNullException( "device" );
		properties = gcnew DeviceProperties( m_Pointer );
	}

	generic<typename DataFormat>
	Device<DataFormat>::Device( IntPtr device )
	{
		if( device == IntPtr::Zero )
			throw gcnew ArgumentNullException( "device" );

		void* pointer;
		IUnknown* unknown = (IUnknown*) device.ToPointer();
		HRESULT hr = unknown->QueryInterface( IID_IDirectInputDevice8W, &pointer );
		if( FAILED( hr ) )
			throw gcnew InputException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = (IDirectInputDevice8W*) pointer;
	}

	generic<typename DataFormat>
	Device<DataFormat>::Device( Guid subsystem )
	{
		IDirectInputDevice8W* device;
		HRESULT hr = DirectInput::InternalPointer->CreateDevice( *(GUID*) &subsystem, &device, NULL );
		InputException::CheckHResult( hr );

		m_Pointer = device;

		Type^ type = DataFormat::typeid;
		if( type == KeyboardState::typeid )
			hr = m_Pointer->SetDataFormat( &c_dfDIKeyboard );
		else if( type == MouseState::typeid )
			hr = m_Pointer->SetDataFormat( &c_dfDIMouse2 );
		else if( type == JoystickState::typeid )
			hr = m_Pointer->SetDataFormat( &c_dfDIJoystick2 );
		else
		{
			array<DataFormatAttribute^>^ formatAttributes = ( array<DataFormatAttribute^>^ )type->GetCustomAttributes(
				DataFormatAttribute::typeid, false );

			if( formatAttributes->Length != 1 )
				throw gcnew InvalidOperationException( "The data format must be marked with one and only one DataFormat attribute." );
			DataFormatAttribute^ formatAttribute = formatAttributes[0];

			List<DataObjectAttribute^>^ objectAttributes = gcnew List<DataObjectAttribute^>();
			array<FieldInfo^>^ fields = type->GetFields();
			for each( FieldInfo^ field in fields )
			{
				array<DataObjectAttribute^>^ attributes = ( array<DataObjectAttribute^>^ )field->GetCustomAttributes( 
					DataObjectAttribute::typeid, false );
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
			format.dwFlags = ( DWORD )formatAttribute->Flags;
			format.dwDataSize = Marshal::SizeOf( type );
			format.dwNumObjs = objectAttributes->Count;

			DIOBJECTDATAFORMAT *objectFormats = new DIOBJECTDATAFORMAT[objectAttributes->Count];
			for( int i = 0; i < objectAttributes->Count; i++ )
			{
				GUID *guid = new GUID( SystemGuid::ToGUID( objectAttributes[i]->SourceGuid ) );
				objectFormats[i].dwFlags = ( DWORD )objectAttributes[i]->Flags;
				objectFormats[i].dwType = ( DWORD )objectAttributes[i]->Type;
				objectFormats[i].pguid = guid;
				if( objectAttributes[i]->InstanceNumber == -1 )
					objectFormats[i].dwType |= DIDFT_ANYINSTANCE;
				else
					objectFormats[i].dwType |= DIDFT_MAKEINSTANCE( objectAttributes[i]->InstanceNumber );
				objectFormats[i].dwOfs = objectAttributes[i]->Offset;
			}

			format.rgodf = objectFormats;
			hr = m_Pointer->SetDataFormat( &format );

			for( int i = 0; i < objectAttributes->Count; i++ )
				delete objectFormats[i].pguid;
			delete[] objectFormats;
		}

		InputException::CheckHResult( hr );

		properties = gcnew DeviceProperties( m_Pointer );
	}

	generic<typename DataFormat>
	void Device<DataFormat>::SetCooperativeLevel( IntPtr handle, CooperativeLevel flags )
	{
		HRESULT hr = m_Pointer->SetCooperativeLevel( ( HWND )handle.ToPointer(), ( DWORD )flags );
		InputException::CheckHResult( hr );
	}

	generic<typename DataFormat>
	void Device<DataFormat>::SetCooperativeLevel( Control^ control, CooperativeLevel flags )
	{
		SetCooperativeLevel( control->Handle, flags );
	}

	generic<typename DataFormat>
	void Device<DataFormat>::Acquire()
	{
		HRESULT hr = m_Pointer->Acquire();
		InputException::CheckHResult( hr );
	}

	generic<typename DataFormat>
	void Device<DataFormat>::Unacquire()
	{
		HRESULT hr = m_Pointer->Unacquire();
		InputException::CheckHResult( hr );
	}

	generic<typename DataFormat>
	void Device<DataFormat>::Poll()
	{
		HRESULT hr = m_Pointer->Poll();
		if( FAILED( hr ) )
		{
			hr = m_Pointer->Acquire();
			while( hr == DIERR_INPUTLOST )
				hr = m_Pointer->Acquire();
		}
		InputException::CheckHResult( hr );
	}

	generic<typename DataFormat>
	void Device<DataFormat>::RunControlPanel()
	{
		HRESULT hr = m_Pointer->RunControlPanel( NULL, 0 );
		InputException::CheckHResult( hr );
	}

	generic<typename DataFormat>
	void Device<DataFormat>::RunControlPanel( Control^ parent )
	{
		HRESULT hr = m_Pointer->RunControlPanel( ( HWND )parent->Handle.ToPointer(), 0 );
		InputException::CheckHResult( hr );
	}

	generic<typename DataFormat>
	Collection<BufferedData<DataFormat>^>^ Device<DataFormat>::GetBufferedData()
	{
		List<BufferedData<DataFormat>^>^ list = gcnew List<BufferedData<DataFormat>^>();

		int size = INFINITE;
		HRESULT hr = m_Pointer->GetDeviceData( sizeof( DIDEVICEOBJECTDATA ), NULL, ( LPDWORD )&size, DIGDD_PEEK );
		bool deviceLost = false;
		if( FAILED( hr ) )
		{
			if( hr == DIERR_INPUTLOST )
				deviceLost = true;

			hr = m_Pointer->Acquire();
			while( hr == DIERR_INPUTLOST )
				hr = m_Pointer->Acquire();
		}
		InputException::CheckHResult( hr );

		if( hr == DI_BUFFEROVERFLOW && &Device::BufferOverflow != nullptr )
			BufferOverflow( this, EventArgs::Empty );

		if( deviceLost && &Device::DeviceLost != nullptr )
			DeviceLost( this, EventArgs::Empty );

		DIDEVICEOBJECTDATA *data = new DIDEVICEOBJECTDATA[size];
		hr = m_Pointer->GetDeviceData( sizeof( DIDEVICEOBJECTDATA ), data, ( LPDWORD )&size, 0 );
		deviceLost = false;
		if( FAILED( hr ) )
		{
			if( hr == DIERR_INPUTLOST )
				deviceLost = true;

			hr = m_Pointer->Acquire();
			while( hr == DIERR_INPUTLOST )
				hr = m_Pointer->Acquire();
		}

		if( hr == DI_BUFFEROVERFLOW && &Device::BufferOverflow != nullptr )
			BufferOverflow( this, EventArgs::Empty );

		InputException::CheckHResult( hr );

		if( deviceLost && &Device::DeviceLost != nullptr )
			DeviceLost( this, EventArgs::Empty );

		delete[] data;

		for( int i = 0; i < size; i++ )
		{
			BufferedData<DataFormat>^ bufferedData = gcnew BufferedData<DataFormat>( data[i] );
			list->Add( bufferedData );
		}

		return gcnew Collection<BufferedData<DataFormat>^>( list );
	}

	generic<typename DataFormat>
	DataFormat Device<DataFormat>::GetCurrentState()
	{
		Type^ type = DataFormat::typeid;

		if( type == KeyboardState::typeid )
		{
			BYTE keys[256];
			HRESULT hr = m_Pointer->GetDeviceState( sizeof( BYTE ) * 256, keys );
			bool deviceLost = false;
			if( FAILED( hr ) )
			{
				if( hr == DIERR_INPUTLOST )
					deviceLost = true;

				hr = m_Pointer->Acquire();
				while( hr == DIERR_INPUTLOST )
					hr = m_Pointer->Acquire();
			}
			InputException::CheckHResult( hr );

			if( deviceLost && &Device::DeviceLost != nullptr )
				DeviceLost( this, EventArgs::Empty );

			KeyboardState^ state = gcnew KeyboardState();
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
			HRESULT hr = m_Pointer->GetDeviceState( sizeof( DIMOUSESTATE2 ), ( DIMOUSESTATE2* )&state );
			bool deviceLost = false;
			if( FAILED( hr ) )
			{
				if( hr == DIERR_INPUTLOST )
					deviceLost = true;

				hr = m_Pointer->Acquire();
				while( hr == DIERR_INPUTLOST )
					hr = m_Pointer->Acquire();
			}
			InputException::CheckHResult( hr );

			if( deviceLost && &Device::DeviceLost != nullptr )
				DeviceLost( this, EventArgs::Empty );

			MouseState^ result = gcnew MouseState( state.lX, state.lY, state.lZ );
			result = gcnew MouseState( state.lX, state.lY, state.lZ );
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
			HRESULT hr = m_Pointer->GetDeviceState( sizeof( DIJOYSTATE2 ), ( DIJOYSTATE2* )&state );
			bool deviceLost = false;
			if( FAILED( hr ) )
			{
				if( hr == DIERR_INPUTLOST )
					deviceLost = true;

				hr = m_Pointer->Acquire();
				while( hr == DIERR_INPUTLOST )
					hr = m_Pointer->Acquire();
			}
			InputException::CheckHResult( hr );

			if( deviceLost && &Device::DeviceLost != nullptr )
				DeviceLost( this, EventArgs::Empty );

			return ( DataFormat )gcnew JoystickState( state );
		}
		else
		{
			int typeSize = Marshal::SizeOf( type );
			BYTE *bytes = new BYTE[typeSize];
			HRESULT hr = m_Pointer->GetDeviceState( sizeof( BYTE ) * typeSize, bytes );
			bool deviceLost = false;
			if( FAILED( hr ) )
			{
				if( hr == DIERR_INPUTLOST )
					deviceLost = true;

				hr = m_Pointer->Acquire();
				while( hr == DIERR_INPUTLOST )
					hr = m_Pointer->Acquire();
			}
			InputException::CheckHResult( hr );

			if( deviceLost && &Device::DeviceLost != nullptr )
				DeviceLost( this, EventArgs::Empty );

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
		HRESULT hr = m_Pointer->GetCapabilities( &caps );
		InputException::CheckHResult( hr );

		return gcnew Capabilities( caps );
	}

	generic<typename DataFormat>
	DeviceInstance^ Device<DataFormat>::DeviceInformation::get()
	{
		DIDEVICEINSTANCE deviceInstance;
		HRESULT hr = m_Pointer->GetDeviceInfo( &deviceInstance );
		InputException::CheckHResult( hr );

		return gcnew DeviceInstance( deviceInstance );
	}

	generic<typename DataFormat>
	IntPtr Device<DataFormat>::NativePointer::get()
	{
		return IntPtr(m_Pointer);
	}
}
}
