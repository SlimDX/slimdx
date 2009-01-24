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

#include <d3d11.h>

#include "../ComObject.h"

#include "Direct3D11Exception.h"

#include "Device.h"
#include "DeviceChild.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{ 
	DeviceChild::DeviceChild()
	{
	}
	
	DeviceChild::DeviceChild( ID3D11DeviceChild* pointer )
	{
		Construct( pointer );
	}

	DeviceChild::DeviceChild( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	DeviceChild^ DeviceChild::FromPointer( ID3D11DeviceChild* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		DeviceChild^ tableEntry = safe_cast<DeviceChild^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew DeviceChild( pointer );
	}

	DeviceChild^ DeviceChild::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		DeviceChild^ tableEntry = safe_cast<DeviceChild^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew DeviceChild( pointer );
	}

	SlimDX::Direct3D11::Device^ DeviceChild::Device::get()
	{
		ID3D11Device* device = 0;
		InternalPointer->GetDevice( &device );
		return SlimDX::Direct3D11::Device::FromPointer( device );
	}
}
}
