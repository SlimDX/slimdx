/*
* Copyright (c) 2007 SlimDX Group
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

#include "DXGIErrorHandler.h"

#include "Adapter.h"
#include "Factory.h"

namespace SlimDX
{
namespace DXGI
{ 
	Factory::Factory()
	{
		IDXGIFactory* factory = 0;
		HRESULT hr = CreateDXGIFactory( __uuidof( IDXGIFactory ), reinterpret_cast<void**>( &factory ) );
		DXGIErrorHandler::TestForFailure( hr );

		Construct( factory );
	}
	
	int Factory::GetAdapterCount()
	{
		int count = 0;
		IDXGIAdapter* adapter = 0;
		while( InternalPointer->EnumAdapters( count, &adapter) != DXGI_ERROR_NOT_FOUND )
		{
			adapter->Release();
			++count;
		}

		return count;
	}

	Adapter^ Factory::GetAdapter( int index )
	{
		IDXGIAdapter* adapter = 0;
		HRESULT hr = InternalPointer->EnumAdapters( index, &adapter);
		if( DXGIErrorHandler::TestForFailure( hr ) )
			return nullptr;
		return gcnew Adapter( adapter );
	}
		
	IntPtr Factory::GetWindowAssociation()
	{
		HWND window = 0;
		HRESULT hr = InternalPointer->GetWindowAssociation( &window );
		if( DXGIErrorHandler::TestForFailure( hr ) )
			return IntPtr::Zero;
		return IntPtr( window );
	}
	
	void Factory::SetWindowAssociation( IntPtr handle, WindowAssociationFlags flags )
	{
		HRESULT hr = InternalPointer->MakeWindowAssociation( reinterpret_cast<HWND>( handle.ToInt32() ), static_cast<UINT>( flags ) );
		DXGIErrorHandler::TestForFailure( hr );
	}
}
}
