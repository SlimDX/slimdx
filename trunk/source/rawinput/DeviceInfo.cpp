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

#include "DeviceInfo.h"

namespace SlimDX
{
namespace RawInput
{
	DeviceInfo::DeviceInfo(RAWINPUTDEVICELIST deviceInfo) {
		handle = System::IntPtr(deviceInfo.hDevice);
		type = static_cast<InputType>(deviceInfo.dwType);

		UINT size;
		if(::GetRawInputDeviceInfo(deviceInfo.hDevice, RIDI_DEVICENAME, NULL, &size) != 0)
			throw gcnew System::InvalidOperationException("Unable to get length of device name");

		WCHAR* str = (WCHAR*)malloc(sizeof(WCHAR) * size);
		
		UINT result = ::GetRawInputDeviceInfo(deviceInfo.hDevice, RIDI_DEVICENAME, str, &size);
		if(result == -1)
			throw gcnew System::InvalidOperationException("Not enough memory");
		else if (result != size)
			throw gcnew System::InvalidOperationException("Sizes do not match");
		
		name = System::Runtime::InteropServices::Marshal::PtrToStringAuto(System::IntPtr(str));
		free(str);
	}

	System::IntPtr DeviceInfo::Handle::get() {
		return handle;
	}
	
	InputType DeviceInfo::Type::get() {
		return type;
	}

	System::String^ DeviceInfo::Name::get() {
		return name;
	}
}
}