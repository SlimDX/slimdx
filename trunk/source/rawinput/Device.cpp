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

#include "../StackAlloc.h"
#include "../Utilities.h"

#include "../SlimDXException.h"

#include "Device.h"
#include "KeyboardInfo.h"
#include "MouseInfo.h"
#include "HidInfo.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Collections::ObjectModel;
using namespace System::Collections::Generic;

namespace SlimDX
{
namespace RawInput
{
	Device::Device( SlimDX::UsagePage usagePage, SlimDX::UsageId usageId, DeviceFlags flags )
	{
		Construct( usagePage, usageId, flags, IntPtr::Zero );
	}

	Device::Device( SlimDX::UsagePage usagePage, SlimDX::UsageId usageId, DeviceFlags flags, IntPtr target )
	{
		Construct( usagePage, usageId, flags, target );
	}

	void Device::Construct( SlimDX::UsagePage usagePage, SlimDX::UsageId usageId, DeviceFlags flags, IntPtr target )
	{
		m_usagePage = usagePage;
		m_usageId = usageId;
		m_flags = flags;
		m_target = target;

		RAWINPUTDEVICE device;
		device.usUsagePage = static_cast<USHORT>( usagePage );
		device.usUsage = static_cast<USHORT>( usageId );
		device.dwFlags = static_cast<DWORD>( flags );
		device.hwndTarget = static_cast<HWND>( target.ToPointer() );

		if( RegisterRawInputDevices( &device, 1, sizeof(RAWINPUTDEVICE) ) <= 0 )
			throw gcnew Win32Exception();

		if( target == IntPtr::Zero )
		{
			if( filter == nullptr )
			{
				filter = gcnew InputMessageFilter();
				Application::AddMessageFilter( filter );
			}

			filter->Add( this );
		}
		else
		{
			subclass = gcnew WindowSubclass( this );
			subclass->AssignHandle( target );
		}
	}

	void Device::OnWmInput( HRAWINPUT handle )
	{
		UINT size = 0;
		GetRawInputData( handle, RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER) );

		if( size == 0 )
			return;

		BYTE *bytes = new BYTE[size];
		GetRawInputData( handle, RID_INPUT, bytes, &size, sizeof(RAWINPUTHEADER) );

		RAWINPUT *rawInput = reinterpret_cast<RAWINPUT*>( bytes );

		if( rawInput->header.dwType == RIM_TYPEKEYBOARD )
		{
			OnKeyboardInput( gcnew KeyboardInputEventArgs( rawInput->data.keyboard.MakeCode,
				static_cast<ScanCodeFlags>( rawInput->data.keyboard.Flags ),
				static_cast<Keys>( rawInput->data.keyboard.VKey ),
				static_cast<KeyState>( rawInput->data.keyboard.Message ),
				rawInput->data.keyboard.ExtraInformation ) );
		}
		else if( rawInput->header.dwType == RIM_TYPEMOUSE )
		{
			OnMouseInput( gcnew MouseInputEventArgs( static_cast<MouseState>( rawInput->data.mouse.usFlags ),
				static_cast<MouseButtonFlags>( rawInput->data.mouse.usButtonFlags ),
				rawInput->data.mouse.usButtonData,
				rawInput->data.mouse.ulRawButtons,
				rawInput->data.mouse.lLastX,
				rawInput->data.mouse.lLastY,
				rawInput->data.mouse.ulExtraInformation ) );
		}
		else
		{
			int length = rawInput->data.hid.dwCount * rawInput->data.hid.dwSizeHid;
			array<Byte>^ bytes = gcnew array<Byte>( length );
			for( int i = 0; i < length; i++ )
				bytes[i] = rawInput->data.hid.bRawData[i];

			OnRawInput( gcnew RawInputEventArgs( rawInput->data.hid.dwSizeHid, rawInput->data.hid.dwCount, bytes ) );
		}

		delete[] bytes;
	}

	void Device::Destruct()
	{
		if( subclass != nullptr )
		{
			subclass->ReleaseHandle();
			subclass = nullptr;
		}

		if( filter != nullptr )
		{
			filter->Remove( this );

			if( filter->Count == 0 )
			{
				Application::RemoveMessageFilter( filter );
				filter = nullptr;
			}
		}

		RAWINPUTDEVICE device;
		device.usUsagePage = static_cast<USHORT>( UsagePage );
		device.usUsage = static_cast<USHORT>( UsageId );
		device.dwFlags = RIDEV_REMOVE;
		device.hwndTarget = NULL;

		RegisterRawInputDevices( &device, 1, sizeof(RAWINPUTDEVICE) );
	}

	void Device::OnKeyboardInput( KeyboardInputEventArgs^ e )
	{
		if( &Device::KeyboardInput != nullptr )
			KeyboardInput( this, e );
	}

	void Device::OnMouseInput( MouseInputEventArgs^ e )
	{
		if( &Device::MouseInput != nullptr )
			MouseInput( this, e );
	}

	void Device::OnRawInput( RawInputEventArgs^ e )
	{
		if( &Device::RawInput != nullptr )
			RawInput( this, e );
	}

	ReadOnlyCollection<DeviceInfo^>^ Device::GetDevices()
	{
		List<DeviceInfo^>^ devices = gcnew List<DeviceInfo^>();
		UINT count = 0;

		if( GetRawInputDeviceList( NULL, &count, sizeof(RAWINPUTDEVICELIST) ) != 0 )
			throw gcnew Win32Exception();

		if( count == 0 )
			return nullptr;

		stack_vector<RAWINPUTDEVICELIST> deviceList( count );
		if( GetRawInputDeviceList( &deviceList[0], &count, sizeof(RAWINPUTDEVICELIST) ) == -1 )
			throw gcnew Win32Exception();

		for( unsigned int i = 0; i < count; i++ )
		{
			UINT size = 0;
			BYTE *bytes;
			String^ name;

			GetRawInputDeviceInfo( deviceList[i].hDevice, RIDI_DEVICENAME, NULL, &size );

			if( size != 0 )
			{
				bytes = new BYTE[size];
				GetRawInputDeviceInfo( deviceList[i].hDevice, RIDI_DEVICENAME, bytes, &size );

				name = gcnew String( reinterpret_cast<const char*>( bytes ) );
				delete[] bytes;
			}

			GetRawInputDeviceInfo( deviceList[i].hDevice, RIDI_DEVICEINFO, NULL, &size );

			if( size == 0 )
				continue;

			bytes = new BYTE[size];
			RID_DEVICE_INFO *nativeInfo = reinterpret_cast<RID_DEVICE_INFO*>( bytes );
			nativeInfo->cbSize = sizeof( RID_DEVICE_INFO );

			GetRawInputDeviceInfo( deviceList[i].hDevice, RIDI_DEVICEINFO, nativeInfo, &size );			

			if( nativeInfo->dwType == RIM_TYPEKEYBOARD )
			{
				KeyboardInfo^ info = gcnew KeyboardInfo();

				info->DeviceType = static_cast<DeviceType>( nativeInfo->dwType );
				info->DeviceName = name;
				info->KeyboardType = nativeInfo->keyboard.dwType;
				info->Subtype = nativeInfo->keyboard.dwSubType;
				info->KeyboardMode = nativeInfo->keyboard.dwKeyboardMode;
				info->FunctionKeyCount = nativeInfo->keyboard.dwNumberOfFunctionKeys;
				info->IndicatorCount = nativeInfo->keyboard.dwNumberOfIndicators;
				info->TotalKeyCount = nativeInfo->keyboard.dwNumberOfKeysTotal;

				devices->Add( info );
			}
			else if( nativeInfo->dwType == RIM_TYPEMOUSE )
			{
				MouseInfo^ info = gcnew MouseInfo();

				info->DeviceType = static_cast<DeviceType>( nativeInfo->dwType );
				info->DeviceName = name;
				info->Id = nativeInfo->mouse.dwId;
				info->ButtonCount = nativeInfo->mouse.dwNumberOfButtons;
				info->SampleRate = nativeInfo->mouse.dwSampleRate;

				devices->Add( info );
			}
			else
			{
				HidInfo^ info = gcnew HidInfo();

				info->DeviceType = static_cast<DeviceType>( nativeInfo->dwType );
				info->DeviceName = name;
				info->VendorId = nativeInfo->hid.dwVendorId;
				info->ProductId = nativeInfo->hid.dwProductId;
				info->VersionNumber = nativeInfo->hid.dwVersionNumber;

				devices->Add( info );
			}

			delete[] bytes;
		}

		return gcnew ReadOnlyCollection<DeviceInfo^>( devices );
	}
}
}