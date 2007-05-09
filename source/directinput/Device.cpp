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

namespace SlimDX
{
namespace DirectInput
{
	GUID ToGUID( Guid guid )
	{
		//TODO: This is fucking crazy
		GUID result;
		array<Byte>^ bytes = guid.ToByteArray();
		pin_ptr<unsigned char> pinned_bytes = &bytes[0];
		memcpy( &result, pinned_bytes, sizeof(GUID) );

		return result;
	}

	Device::Device( IDirectInputDevice8W* device )
	{
		m_Device = device;
	}

	Device::Device( Guid subsystem )
	{
		IDirectInputDevice8W* device;
		HRESULT hr = DirectInput::InternalPointer->CreateDevice( *(GUID*) &subsystem, &device, NULL );

		m_Device = device;

		if( subsystem == SystemGuid::Keyboard )
			SetDataFormat( DeviceDataFormat::Keyboard );
		else if( subsystem == SystemGuid::Mouse )
			SetDataFormat( DeviceDataFormat::Mouse );
		else if( subsystem == SystemGuid::Joystick )
			SetDataFormat( DeviceDataFormat::Joystick );
	}

	void Device::SetDataFormat( DeviceDataFormat format )
	{
		HRESULT hr;

		switch( format )
		{
		case DeviceDataFormat::Keyboard:
			hr = m_Device->SetDataFormat( &c_dfDIKeyboard );
			break;

		case DeviceDataFormat::Mouse:
			hr = m_Device->SetDataFormat( &c_dfDIMouse2 );
			break;

		case DeviceDataFormat::Joystick:
			hr = m_Device->SetDataFormat( &c_dfDIJoystick2 );
			break;

		default:
			hr = S_OK;
		}
	}

	void Device::SetCooperativeLevel( IntPtr handle, CooperativeLevel flags )
	{
		HRESULT hr = m_Device->SetCooperativeLevel( (HWND) handle.ToPointer(), (DWORD) flags );
	}

	void Device::Acquire()
	{
		HRESULT hr = m_Device->Acquire();
	}

	void Device::Unacquire()
	{
		HRESULT hr = m_Device->Unacquire();
	}

	void Device::Poll()
	{
		HRESULT hr = m_Device->Poll();
	}

	MouseState Device::CurrentMouseState::get()
	{
		DIMOUSESTATE2 state;

		HRESULT hr = m_Device->GetDeviceState( sizeof( MouseState ), (DIMOUSESTATE2*) &state );

		//convert to a managed structure
		MouseState result;
		result.X = state.lX;
		result.Y = state.lY;
		result.Z = state.lZ;
		result.buttons = gcnew array<Byte>( 8 );
		for( int i = 0; i < 8; ++i )
			result.buttons[i] = state.rgbButtons[i];

		return result;
	}
}
}
