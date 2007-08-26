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
	Device::Device( IDirectInputDevice8W* device ) : DirectXObject( device )
	{
		if( device == NULL )
			throw gcnew ArgumentNullException( "device" );
	}

	Device::Device( Guid subsystem )
	{
		IDirectInputDevice8W* device;
		HRESULT hr = DirectInput::InternalPointer->CreateDevice( *(GUID*) &subsystem, &device, NULL );
		InputException::CheckHResult( hr );

		m_Pointer = device;

		if( subsystem == SystemGuid::Keyboard )
			SetDataFormat( DeviceDataFormat::Keyboard );
		else if( subsystem == SystemGuid::Mouse )
			SetDataFormat( DeviceDataFormat::Mouse );
	}

	void Device::SetDataFormat( DeviceDataFormat format )
	{
		HRESULT hr;

		switch( format )
		{
		case DeviceDataFormat::Keyboard:
			hr = m_Pointer->SetDataFormat( &c_dfDIKeyboard );
			break;

		case DeviceDataFormat::Mouse:
			hr = m_Pointer->SetDataFormat( &c_dfDIMouse2 );
			break;

		case DeviceDataFormat::Joystick:
			hr = m_Pointer->SetDataFormat( &c_dfDIJoystick2 );
			break;

		default:
			hr = S_OK;
		}

		InputException::CheckHResult( hr );
	}

	void Device::SetDataFormat( DataFormat^ format )
	{
		DIDATAFORMAT dataFormat = format->ToUnmanaged();
		HRESULT hr = m_Pointer->SetDataFormat( &dataFormat );
		
		for( unsigned int i = 0; i < dataFormat.dwNumObjs; i++ )
			delete dataFormat.rgodf[i].pguid;
		delete[] dataFormat.rgodf;

		InputException::CheckHResult( hr );
	}

	void Device::SetCooperativeLevel( IntPtr handle, CooperativeLevel flags )
	{
		HRESULT hr = m_Pointer->SetCooperativeLevel( ( HWND )handle.ToPointer(), ( DWORD )flags );
		InputException::CheckHResult( hr );
	}

	void Device::SetCooperativeLevel( Control^ control, CooperativeLevel flags )
	{
		SetCooperativeLevel( control->Handle, flags );
	}

	void Device::Acquire()
	{
		HRESULT hr = m_Pointer->Acquire();
		InputException::CheckHResult( hr );
	}

	void Device::Unacquire()
	{
		HRESULT hr = m_Pointer->Unacquire();
		InputException::CheckHResult( hr );
	}

	void Device::Poll()
	{
		HRESULT hr = m_Pointer->Poll();
		InputException::CheckHResult( hr );
	}

	void Device::RunControlPanel()
	{
		HRESULT hr = m_Pointer->RunControlPanel( NULL, 0 );
		InputException::CheckHResult( hr );
	}

	void Device::RunControlPanel( Control^ parent )
	{
		HRESULT hr = m_Pointer->RunControlPanel( ( HWND )parent->Handle.ToPointer(), 0 );
		InputException::CheckHResult( hr );
	}

	Collection<BufferedData^>^ Device::GetBufferedData( int size )
	{
		List<BufferedData^>^ list = gcnew List<BufferedData^>();

		DIDEVICEOBJECTDATA *data = new DIDEVICEOBJECTDATA[size];
		HRESULT hr = m_Pointer->GetDeviceData( sizeof( DIDEVICEOBJECTDATA ), data, ( LPDWORD )&size, 0 );
		InputException::CheckHResult( hr );

		for( int i = 0; i < size; i++ )
			list->Add( gcnew BufferedData( data[i] ) );

		delete[] data;

		return gcnew Collection<BufferedData^>( list );
	}

	array<Byte>^ Device::GetCurrentState( int size )
	{
		BYTE *bytes = new BYTE[size];
		HRESULT hr = m_Pointer->GetDeviceState( size, bytes );
		InputException::CheckHResult( hr );

		array<Byte>^ ret = gcnew array<Byte>( size );
		for( int i = 0; i < size; i++ )
			ret[i] = bytes[i];

		return ret;
	}

	JoystickState^ Device::CurrentJoystickState::get()
	{
		DIJOYSTATE2 state;
		HRESULT hr = m_Pointer->GetDeviceState( sizeof( DIJOYSTATE2 ), ( DIJOYSTATE2* )&state );
		InputException::CheckHResult( hr );

		return gcnew JoystickState( state );
	}

	MouseState^ Device::CurrentMouseState::get()
	{
		DIMOUSESTATE2 state;
		HRESULT hr = m_Pointer->GetDeviceState( sizeof( DIMOUSESTATE2 ), (DIMOUSESTATE2*) &state );
		InputException::CheckHResult( hr );

		MouseState^ result = gcnew MouseState( state.lX, state.lY, state.lZ );
		
		for( int i = 0; i < 8; i++ )
			result->Buttons[i] = state.rgbButtons[i] & 0x80;

		return result;
	}

	KeyboardState^ Device::CurrentKeyboardState::get()
	{
		BYTE keys[256];
		HRESULT hr = m_Pointer->GetDeviceState( sizeof( BYTE ) * 256, keys );
		InputException::CheckHResult( hr );

		KeyboardState^ result = gcnew KeyboardState();
		
		for( int i = 0; i < 256; i++ )
		{
			if( keys[i] )
				result->keys[i] = true;
			else
				result->keys[i] = false;
		}

		return result;
	}

	Capabilities^ Device::Caps::get()
	{
		DIDEVCAPS caps;
		HRESULT hr = m_Pointer->GetCapabilities( &caps );
		InputException::CheckHResult( hr );

		return gcnew Capabilities( caps );
	}

	DeviceInstance^ Device::DeviceInformation::get()
	{
		DIDEVICEINSTANCE deviceInstance;
		HRESULT hr = m_Pointer->GetDeviceInfo( &deviceInstance );
		InputException::CheckHResult( hr );

		return gcnew DeviceInstance( deviceInstance );
	}
}
}
