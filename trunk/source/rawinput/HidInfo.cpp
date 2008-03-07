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

#include "HidInfo.h"

#include <windows.h>

namespace SlimDX
{
namespace RawInput
{
	HidInfo::HidInfo( RID_DEVICE_INFO_HID info )
	{
		vendorID = info.dwVendorId;
		productID = info.dwProductId;
		versionNumber = info.dwVersionNumber;
		usage = static_cast<HidUsage>( info.usUsage );
		usagePage = static_cast<HidUsagePage>( info.usUsagePage );
	}

	int HidInfo::VendorID::get()
	{
		return vendorID;
	}

	int HidInfo::ProductID::get()
	{
		return productID;
	}

	int HidInfo::VersionNumber::get()
	{
		return versionNumber;
	}

	HidUsage HidInfo::Usage::get()
	{
		return usage;
	}

	HidUsagePage HidInfo::UsagePage::get()
	{
		return usagePage;
	}
}
}