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

#include "RawInputDevice.h"

#include <windows.h>

namespace SlimDX
{
namespace RawInput
{
	HIDUsagePage RawInputDevice::UsagePage::get() {
		return static_cast<HIDUsagePage>(this->Internal->usUsagePage);
	}

	void RawInputDevice::UsagePage::set(HIDUsagePage usagePage) {
		this->Internal->usUsagePage = static_cast<unsigned short>(usagePage);
	}

	HIDUsage RawInputDevice::Usage::get() {
		return static_cast<HIDUsage>(this->Internal->usUsage);
	}

	void RawInputDevice::Usage::set(HIDUsage usage) {
		this->Internal->usUsage = static_cast<unsigned short>(usage);
	}

	DeviceFlags RawInputDevice::Flags::get() {
		return static_cast<DeviceFlags>(this->Internal->dwFlags);
	}

	void RawInputDevice::Flags::set(DeviceFlags flags) {
		this->Internal->dwFlags = static_cast<DWORD>(flags);
	}

	System::IntPtr^ RawInputDevice::Target::get() {
		return gcnew System::IntPtr(this->Internal->hwndTarget);
	}

	void RawInputDevice::Target::set(System::IntPtr^ target) {
		this->Internal->hwndTarget = (HWND)target->ToPointer();
	}
}
}