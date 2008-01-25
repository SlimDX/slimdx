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
#include <d3d9.h>
#include <d3dx9.h>

#include "../ComObject.h"

#include "Direct3D9Exception.h"

#include "Device.h"
#include "Direct3D.h"
#include "Surface.h"
#include "SwapChain.h"

namespace SlimDX
{
namespace Direct3D9
{
	//grab this function from Device.cpp
	void ConvertPresentParams( PresentParameters^ presentParams, D3DPRESENT_PARAMETERS& d3dpp );

	SwapChain::SwapChain( IDirect3DSwapChain9* swapChain )
	{
		if( swapChain == NULL )
			throw gcnew ArgumentNullException( "swapChain" );

		Construct(swapChain);
	}

	SwapChain::SwapChain( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	SwapChain::SwapChain( Device^ device, PresentParameters^ presentParams )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
		if( presentParams == nullptr )
			throw gcnew ArgumentNullException( "presentParams" );

		D3DPRESENT_PARAMETERS d3dpp;
		ConvertPresentParams( presentParams, d3dpp );

		IDirect3DSwapChain9* swapChain;
		HRESULT hr = device->InternalPointer->CreateAdditionalSwapChain( &d3dpp, &swapChain );
		Direct3D9ErrorHandler::TestForFailure( hr );
		if( FAILED( hr ) )
			throw gcnew Direct3D9Exception( "Failed to create swap chain." );

		Construct(swapChain);
	}

	Surface^ SwapChain::GetBackBuffer( int index )
	{
		IDirect3DSurface9* surface;
		HRESULT hr = InternalPointer->GetBackBuffer( index, D3DBACKBUFFER_TYPE_MONO, &surface );
		Direct3D9ErrorHandler::TestForFailure( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew Surface( surface );
	}

	void SwapChain::GetFrontBufferData( Surface^ destSurface )
	{
		if( destSurface == nullptr )
			throw gcnew ArgumentNullException( "destSurface" );

		HRESULT hr = InternalPointer->GetFrontBufferData( destSurface->SurfacePointer );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	Device^ SwapChain::GetDevice()
	{
		IDirect3DDevice9* device;
		HRESULT hr = InternalPointer->GetDevice( &device );
		Direct3D9ErrorHandler::TestForFailure( hr );

		return gcnew Device( device );
	}

	SlimDX::Direct3D9::DisplayMode SwapChain::DisplayMode::get()
	{
		SlimDX::Direct3D9::DisplayMode mode;
		HRESULT hr = InternalPointer->GetDisplayMode( reinterpret_cast<D3DDISPLAYMODE*>( &mode ) );
		Direct3D9ErrorHandler::TestForFailure( hr );

		return mode;
	}

	SlimDX::Direct3D9::RasterStatus SwapChain::RasterStatus::get()
	{
		D3DRASTER_STATUS status;
		HRESULT hr = InternalPointer->GetRasterStatus( &status );
		Direct3D9ErrorHandler::TestForFailure( hr );

		SlimDX::Direct3D9::RasterStatus result;
		result.InVBlank = status.InVBlank > 0;
		result.ScanLine = status.ScanLine;
		return result;
	}

	void SwapChain::Present( SlimDX::Direct3D9::Present flags )
	{
		HRESULT hr = InternalPointer->Present( 0, 0, 0, 0, static_cast<DWORD>( flags ) );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}
}
}
