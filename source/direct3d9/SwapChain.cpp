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
	bool RasterStatus::operator == ( RasterStatus left, RasterStatus right )
	{
		return RasterStatus::Equals( left, right );
	}

	bool RasterStatus::operator != ( RasterStatus left, RasterStatus right )
	{
		return !RasterStatus::Equals( left, right );
	}

	int RasterStatus::GetHashCode()
	{
		return InVBlank.GetHashCode() + Scanline.GetHashCode();
	}

	bool RasterStatus::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<RasterStatus>( value ) );
	}

	bool RasterStatus::Equals( RasterStatus value )
	{
		return ( InVBlank == value.InVBlank && Scanline == value.Scanline );
	}

	bool RasterStatus::Equals( RasterStatus% value1, RasterStatus% value2 )
	{
		return ( value1.InVBlank == value2.InVBlank && value1.Scanline == value2.Scanline );
	}

	SwapChain::SwapChain( IDirect3DSwapChain9* pointer )
	{
		Construct( pointer );
	}

	SwapChain::SwapChain( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	SwapChain::SwapChain( SlimDX::Direct3D9::Device^ device, PresentParameters^ presentParameters )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );

		if( presentParameters == nullptr )
			throw gcnew ArgumentNullException( "presentParameters" );

		D3DPRESENT_PARAMETERS d3dpp;
		d3dpp = presentParameters->ToUnmanaged();

		IDirect3DSwapChain9* swapChain;
		HRESULT hr = device->InternalPointer->CreateAdditionalSwapChain( &d3dpp, &swapChain );
		
		if( RECORD_D3D9( hr ).IsFailure )
			throw gcnew Direct3D9Exception( "Failed to create swap chain." );

		Construct(swapChain);
	}

	SwapChain^ SwapChain::FromPointer( IDirect3DSwapChain9* pointer )
	{
		SwapChain^ tableEntry = safe_cast<SwapChain^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew SwapChain( pointer );
	}

	SwapChain^ SwapChain::FromPointer( IntPtr pointer )
	{
		SwapChain^ tableEntry = safe_cast<SwapChain^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew SwapChain( pointer );
	}


	Surface^ SwapChain::GetBackBuffer( int index )
	{
		IDirect3DSurface9* surface;
		HRESULT hr = InternalPointer->GetBackBuffer( index, D3DBACKBUFFER_TYPE_MONO, &surface );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return Surface::FromPointer( surface );
	}

	Result SwapChain::GetFrontBufferData( Surface^ destinationSurface )
	{
		if( destinationSurface == nullptr )
			throw gcnew ArgumentNullException( "destinationSurface" );

		HRESULT hr = InternalPointer->GetFrontBufferData( destinationSurface->InternalPointer );
		return RECORD_D3D9( hr );
	}

	SlimDX::Direct3D9::Device^ SwapChain::Device::get()
	{
		IDirect3DDevice9* device;
		HRESULT hr = InternalPointer->GetDevice( &device );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return SlimDX::Direct3D9::Device::FromPointer( device );
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
