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

#include <dxgi.h>

#include "AdapterDescription.h"

using namespace System;

namespace SlimDX
{
namespace DXGI
{ 	
	AdapterDescription::AdapterDescription( const DXGI_ADAPTER_DESC& native )
	{
		m_Description = gcnew String( native.Description );
		m_VendorId = native.VendorId;
		m_DeviceId = native.DeviceId;
		m_SubSysId = native.SubSysId;
		m_Revision = native.Revision;
		m_DedicatedVideoMemory = native.DedicatedVideoMemory;
		m_DedicatedSystemMemory = native.DedicatedSystemMemory;
		m_SharedSystemMemory = native.SharedSystemMemory;
		m_Luid = (static_cast<Int64>(native.AdapterLuid.HighPart) << 32) | native.AdapterLuid.LowPart;
	}

	String^ AdapterDescription::Description::get()
	{
		return m_Description;
	}

	int AdapterDescription::VendorId::get()
	{
		return m_VendorId;
	}

	int AdapterDescription::DeviceId::get()
	{
		return m_DeviceId;
	}

	int AdapterDescription::SubsystemId::get()
	{
		return m_SubSysId;
	}

	int AdapterDescription::Revision::get()
	{
		return m_Revision;
	}

	int AdapterDescription::DedicatedVideoMemory::get()
	{
		return m_DedicatedVideoMemory;
	}

	int AdapterDescription::DedicatedSystemMemory::get()
	{
		return m_DedicatedSystemMemory;
	}

	int AdapterDescription::SharedSystemMemory::get()
	{
		return m_SharedSystemMemory;
	}

	Int64 AdapterDescription::Luid::get()
	{
		return m_Luid;
	}
}
}
