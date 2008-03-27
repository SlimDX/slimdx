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

#include "RawInput.h"
#include "RawInputDevice.h"
#include "Data.h"
#include "DeviceInfo.h"
#include "Enums.h"
#include "../StackAlloc.h"

using namespace System;

namespace SlimDX
{
namespace RawInput
{
	void RawInput::RegisterRawInputDevices( array<RawInputDevice^>^ devices )
	{
		stack_vector<RAWINPUTDEVICE> Rid( devices->Length );

		for( int i = 0; i < devices->Length; i++ )
			Rid[i] = *devices[i]->Internal;

		if( !::RegisterRawInputDevices( &Rid[0], devices->Length, sizeof( Rid[0] ) ) )
			throw gcnew InvalidOperationException( "Unable to register raw input device. Error code " + GetLastError() );
	}

	SlimDX::RawInput::Data^ RawInput::GetRawInputData( IntPtr lParam, Command command )
	{
		UINT size;
		if( ::GetRawInputData( reinterpret_cast<HRAWINPUT>( lParam.ToPointer() ), RID_INPUT, NULL, &size, sizeof( RAWINPUTHEADER ) ) != 0 )
			throw gcnew InvalidOperationException( "Unable to get size of raw input data. Error code " + GetLastError() );

		stack_vector<LPBYTE> lpb( size );
		if(::GetRawInputData( reinterpret_cast<HRAWINPUT>( lParam.ToPointer() ), static_cast<UINT>( command ), &lpb[0], &size, sizeof( RAWINPUTHEADER ) ) != size )
			throw gcnew InvalidOperationException( "Raw input data does not make expected size. Error code " + GetLastError() );

		Data^ data = gcnew Data( reinterpret_cast<RAWINPUT*>( &lpb[0] ) );

		return data;
	}

	array<SlimDX::RawInput::Data^>^ RawInput::GetRawInputBuffer()
	{
		throw gcnew NotImplementedException();
	}

	array<SlimDX::RawInput::DeviceInfo^>^ RawInput::GetRawInputDevices()
	{
		UINT numberDevices;
		if ( GetRawInputDeviceList( NULL, &numberDevices, sizeof( RAWINPUTDEVICELIST ) ) != 0 )
			throw gcnew System::InvalidOperationException( "Could not count device count" );

		stack_vector<RAWINPUTDEVICELIST> rawInputDeviceList( numberDevices );
		if ( GetRawInputDeviceList( &rawInputDeviceList[0], &numberDevices, sizeof( RAWINPUTDEVICELIST ) ) == (UINT)-1 )
			throw gcnew InvalidOperationException( "Could not get a list of devices" );

		array<SlimDX::RawInput::DeviceInfo^>^ devices = gcnew array<SlimDX::RawInput::DeviceInfo^>( numberDevices );
		for( UINT i = 0; i < numberDevices; i++ )
			devices[i] = gcnew SlimDX::RawInput::DeviceInfo( rawInputDeviceList[i] );

		return devices;
	}

	array<SlimDX::RawInput::RawInputDevice^>^ RawInput::GetRegisteredRawInputDevices()
	{
		UINT numberDevices;
		if ( ::GetRegisteredRawInputDevices( NULL, &numberDevices, sizeof( RAWINPUTDEVICE ) ) != 0 )
			throw gcnew System::InvalidOperationException( "Could not count device count" );

		stack_vector<RAWINPUTDEVICE> rawInputDeviceList( numberDevices );
		if ( ::GetRegisteredRawInputDevices( &rawInputDeviceList[0], &numberDevices, sizeof( RAWINPUTDEVICE ) ) == -1 )
			throw gcnew InvalidOperationException( "Could not get a list of devices" );

		array<SlimDX::RawInput::RawInputDevice^>^ devices = gcnew array<SlimDX::RawInput::RawInputDevice^>( numberDevices );
		for( UINT i = 0; i < numberDevices; i++ )
			devices[i] = gcnew SlimDX::RawInput::RawInputDevice( rawInputDeviceList[i] );

		return devices;
	}
}
}