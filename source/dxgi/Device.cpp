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

#include <vector>

#include "DXGIException.h"

#include "Adapter.h"
#include "Device.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;

namespace SlimDX
{
namespace DXGI
{ 	
	Device::Device( IDXGIDevice* pointer )
	{
		Construct( pointer );
	}
	
	Device::Device( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	Device^ Device::FromPointer( IDXGIDevice* pointer )
	{
		Device^ tableEntry = safe_cast<Device^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew Device( pointer );
	}

	Device^ Device::FromPointer( IntPtr pointer )
	{
		Device^ tableEntry = safe_cast<Device^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew Device( pointer );
	}

	int Device::GpuThreadPriority::get()
	{
		int result = 0;
		RECORD_DXGI( InternalPointer->GetGPUThreadPriority( &result ) );
		if( Result::Last.IsSuccess )
			return result;
		
		throw gcnew DXGIException( Result::Last );
	}
	
	void Device::GpuThreadPriority::set( int value )
	{
		if( RECORD_DXGI( InternalPointer->SetGPUThreadPriority( value ) ).IsFailure )
			throw gcnew DXGIException( Result::Last );
	}

	Adapter^ Device::GetAdapter()
	{
		IDXGIAdapter* adapter = 0;
		RECORD_DXGI( InternalPointer->GetAdapter( &adapter ) );
		if( Result::Last.IsFailure )
			return nullptr;
		return Adapter::FromPointer( adapter );
	}

	ReadOnlyCollection<Residency>^ Device::QueryResourceResidency( IList<ComObject^>^ resources )
	{
		std::vector<DXGI_RESIDENCY> nativeResidency( resources->Count );
		std::vector<IUnknown*> nativeResources( resources->Count );
		for( int resourceIndex = 0; resourceIndex < resources->Count; ++resourceIndex )
			nativeResources[ resourceIndex ] = resources[ resourceIndex ]->UnknownPointer;
		
		RECORD_DXGI( InternalPointer->QueryResourceResidency( &nativeResources[0], &nativeResidency[0], resources->Count ) );
		if( Result::Last.IsFailure )
			return nullptr;
		
		List< Residency >^ result = gcnew List<Residency>( nativeResidency.size() );
		for( unsigned int resourceIndex = 0; resourceIndex < nativeResidency.size(); ++resourceIndex )
			result->Add( static_cast<Residency>( nativeResidency[ resourceIndex ] ) );
		return gcnew ReadOnlyCollection<Residency>( result );
	}
}
}
