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
#include <d3d9.h>
#include <d3dx9.h>

#include "Direct3D.h"
#include "AdapterDetails.h"
#include "AdapterInformation.h"

using namespace System;
using namespace System::Collections::Generic;

namespace SlimDX
{
namespace Direct3D9
{
	AdapterInformation::AdapterInformation( unsigned int adapter )
	{
		m_Adapter = static_cast<int>( adapter );
		Details = gcnew AdapterDetails( adapter );
	}

	IntPtr AdapterInformation::Monitor::get()
	{
		return Direct3D::GetAdapterMonitor( m_Adapter );
	}

	DisplayMode AdapterInformation::CurrentDisplayMode::get()
	{
        return Direct3D::GetAdapterDisplayMode( m_Adapter );
	}

    Capabilities AdapterInformation::GetCaps( DeviceType type )
    {
        return Direct3D::GetDeviceCaps( m_Adapter, type );
    }

	bool AdapterInformation::SupportsR2VB( DeviceType type )
	{
		return Direct3D::SupportsR2VB( m_Adapter, type );
	}

    DisplayModeCollection^ AdapterInformation::GetDisplayModes( Format format )
    {
        return gcnew DisplayModeCollection( m_Adapter, format );
    }

    AdapterCollection::AdapterCollection( unsigned int adapterCount )
    {
		m_Adapters = gcnew List<AdapterInformation^>();

        for( unsigned int i = 0; i < adapterCount; ++i )
            m_Adapters->Add( gcnew AdapterInformation( i ) );
    }
}
}