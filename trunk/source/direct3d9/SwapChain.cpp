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

#include "../ComObject.h"

#include "Direct3D9Exception.h"

#include "Device.h"
#include "Direct3D.h"
#include "Surface.h"
#include "SwapChain.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D9
{
	//grab this function from Device.cpp
	void ConvertPresentParams( PresentParameters^ presentParameters, D3DPRESENT_PARAMETERS& d3dpp );

	SwapChain::SwapChain( IDirect3DSwapChain9* swapChain )
	{
		Construct(swapChain);
	}

	SwapChain::SwapChain( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	SwapChain::SwapChain( Device^ device, PresentParameters^ presentParameters )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );

		if( presentParameters == nullptr )
			throw gcnew ArgumentNullException( "presentParameters" );

		D3DPRESENT_PARAMETERS d3dpp;
		ConvertPresentParams( presentParameters, d3dpp );

		IDirect3DSwapChain9* swapChain;
		HRESULT hr = device->InternalPointer->CreateAdditionalSwapChain( &d3dpp, &swapChain );
		
		if( RECORD_D3D9( hr ).IsFailure )
			throw gcnew Direct3D9Exception( "Failed to create swap chain." );

		Construct(swapChain);
	}

	Surface^ SwapChain::GetBackBuffer( int index )
	{
		IDirect3DSurface9* surface;
		HRESULT hr = InternalPointer->GetBackBuffer( index, D3DBACKBUFFER_TYPE_MONO, &surface );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return gcnew Surface( surface );
	}

	Result SwapChain::GetFrontBufferData( Surface^ destinationSurface )
	{
		if( destinationSurface == nullptr )
			throw gcnew ArgumentNullException( "destinationSurface" );

		HRESULT hr = InternalPointer->GetFrontBufferData( destinationSurface->SurfacePointer );
		return RECORD_D3D9( hr );
	}

	Device^ SwapChain::GetDevice()
	{
		IDirect3DDevice9* device;
		HRESULT hr = InternalPointer->GetDevice( &device );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return gcnew Device( device );
	}

	SlimDX::Direct3D9::DisplayMode SwapChain::DisplayMode::get()
	{
		SlimDX::Direct3D9::DisplayMode mode;
		HRESULT hr = InternalPointer->GetDisplayMode( reinterpret_cast<D3DDISPLAYMODE*>( &mode ) );
		RECORD_D3D9( hr );

		return mode;
	}

	SlimDX::Direct3D9::RasterStatus SwapChain::RasterStatus::get()
	{
		D3DRASTER_STATUS status;
		HRESULT hr = InternalPointer->GetRasterStatus( &status );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return SlimDX::Direct3D9::RasterStatus();

		SlimDX::Direct3D9::RasterStatus result;
		result.InVBlank = status.InVBlank > 0;
		result.Scanline = status.ScanLine;
		return result;
	}

	Result SwapChain::Present( SlimDX::Direct3D9::Present flags )
	{
		HRESULT hr = InternalPointer->Present( 0, 0, 0, 0, static_cast<DWORD>( flags ) );
		return RECORD_D3D9( hr );
	}
}
}
