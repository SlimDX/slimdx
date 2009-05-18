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
#include "../CollectionShim.h"

#include "DirectInput.h"
#include "DirectInputException.h"

#include "Device.h"
#include "CallbacksDI.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

namespace SlimDX
{
namespace DirectInput
{
	Device::Device( DirectInput^ directInput, Guid subsystem )
	{
		IDirectInputDevice8* device;
		HRESULT hr = directInput->InternalPointer->CreateDevice( Utilities::ConvertManagedGuid( subsystem ), &device, NULL );

		if( RECORD_DINPUT( hr ).IsFailure )
			throw gcnew DirectInputException( Result::Last );

		Construct( device );
	}

	Result Device::SetCooperativeLevel( IntPtr handle, CooperativeLevel flags )
	{
		HRESULT hr = InternalPointer->SetCooperativeLevel( static_cast<HWND>( handle.ToPointer() ), static_cast<DWORD>( flags ) );
		return RECORD_DINPUT( hr );
	}

	Result Device::SetCooperativeLevel( Control^ control, CooperativeLevel flags )
	{
		return SetCooperativeLevel( control->Handle, flags );
	}

	Result Device::Acquire()
	{
		HRESULT hr = InternalPointer->Acquire();
		return RecordError( hr );
	}

	Result Device::Unacquire()
	{
		HRESULT hr = InternalPointer->Unacquire();
		return RecordError( hr );
	}

	Result Device::Poll()
	{
		HRESULT hr = InternalPointer->Poll();
		return RecordError( hr );
	}

	Result Device::RunControlPanel()
	{
		HRESULT hr = InternalPointer->RunControlPanel( NULL, 0 );
		return RECORD_DINPUT( hr );
	}

	Result Device::RunControlPanel( Control^ parent )
	{
		HRESULT hr = InternalPointer->RunControlPanel( static_cast<HWND>( parent->Handle.ToPointer() ), 0 );
		return RECORD_DINPUT( hr );
	}

	SlimDX::DirectInput::Capabilities^ Device::Capabilities::get()
	{
		if( caps != nullptr )
			return caps;

		DIDEVCAPS c;
		c.dwSize = sizeof( DIDEVCAPS );
		HRESULT hr = InternalPointer->GetCapabilities( &c );
		
		if( RECORD_DINPUT( hr ).IsFailure )
			caps = nullptr;

		caps = gcnew SlimDX::DirectInput::Capabilities( c );
		return caps;
	}

	DeviceInstance^ Device::Information::get()
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

	IList<DeviceObjectInstance>^ Device::GetObjects()
	{
		return GetObjects( ObjectDeviceType::All );
	}

	IList<DeviceObjectInstance>^ Device::GetObjects( ObjectDeviceType objectType )
	{
		List<DeviceObjectInstance>^ results = gcnew List<DeviceObjectInstance>();
		CollectionShim<DeviceObjectInstance> shim( results );

		HRESULT hr = InternalPointer->EnumObjects( static_cast<LPDIENUMDEVICEOBJECTSCALLBACK>( EnumerateObjects ), &shim, static_cast<DWORD>( objectType ) );
		if( RECORD_DINPUT( hr ).IsFailure )
			return nullptr;

		return results;
	}

	ObjectProperties^ Device::GetObjectPropertiesById( int objectId )
	{
		return gcnew ObjectProperties( InternalPointer, objectId, false );
	}

	ObjectProperties^ Device::GetObjectPropertiesByUsage( int usageCode )
	{
		return gcnew ObjectProperties( InternalPointer, usageCode, true );
	}

	array<Byte>^ Device::Escape( int command, array<Byte>^ data, int outputSize )
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

	DeviceProperties^ Device::Properties::get()
	{
		if( properties == nullptr )
			properties = gcnew DeviceProperties( InternalPointer );

		return properties;
	}
}
}
