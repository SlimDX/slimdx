#include "stdafx.h"
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
#include <windows.h>
#include <dinput.h>

#include "../ComObject.h"
#include "../CollectionShim.h"

#include "Device.h"
#include "DeviceInstance.h"
#include "Callbacks.h"

namespace SlimDX
{
namespace DirectInput
{
	BOOL CALLBACK EnumerateDevices( LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef )
	{
		CollectionShim<DeviceInstance^>* shim = static_cast<CollectionShim<DeviceInstance^>*>( pvRef );
		shim->GetItems()->Add( gcnew DeviceInstance( *lpddi ) );

		return DIENUM_CONTINUE;
	}

	BOOL CALLBACK EnumerateObjects( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef )
	{
		CollectionShim<DeviceObjectInstance^>* shim = static_cast<CollectionShim<DeviceObjectInstance^>*>( pvRef );
		shim->GetItems()->Add( gcnew DeviceObjectInstance( *lpddoi ) );

		return DIENUM_CONTINUE;
	}
}
}
