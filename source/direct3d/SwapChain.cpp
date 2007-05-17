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

#include "../DirectXObject.h"

#include "Device.h"
#include "Direct3D.h"
#include "Surface.h"
#include "SwapChain.h"

namespace SlimDX
{
namespace Direct3D
{
	SwapChain::SwapChain( IDirect3DSwapChain9* swapChain )
	{
		if( swapChain == NULL )
			throw gcnew ArgumentNullException( "swapChain" );

		m_Pointer = swapChain;
	}

	Surface^ SwapChain::GetBackBuffer( int index )
	{
		IDirect3DSurface9* surface;
		HRESULT hr = m_Pointer->GetBackBuffer( index, D3DBACKBUFFER_TYPE_MONO, &surface );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew Surface( surface );
	}

	void SwapChain::GetFrontBufferData( Surface^ destSurface )
	{
		if( destSurface == nullptr )
			throw gcnew ArgumentNullException( "destSurface" );

		HRESULT hr = m_Pointer->GetFrontBufferData( destSurface->SurfacePointer );
		GraphicsException::CheckHResult( hr );
	}

	Device^ SwapChain::GetDevice()
	{
		IDirect3DDevice9* device;
		HRESULT hr = m_Pointer->GetDevice( &device );
		GraphicsException::CheckHResult( hr );

		return gcnew Device( device );
	}

	SlimDX::Direct3D::DisplayMode SwapChain::DisplayMode::get()
	{
		SlimDX::Direct3D::DisplayMode mode;
		HRESULT hr = m_Pointer->GetDisplayMode( (D3DDISPLAYMODE*) &mode );
		GraphicsException::CheckHResult( hr );

		return mode;
	}

	SlimDX::Direct3D::RasterStatus SwapChain::RasterStatus::get()
	{
		D3DRASTER_STATUS status;
		HRESULT hr = m_Pointer->GetRasterStatus( &status );
		GraphicsException::CheckHResult( hr );

		SlimDX::Direct3D::RasterStatus result;
		result.InVBlank = status.InVBlank > 0;
		result.ScanLine = status.ScanLine;
		return result;
	}

	void SwapChain::Present( SlimDX::Direct3D::Present flags )
	{
		HRESULT hr = m_Pointer->Present( 0, 0, 0, 0, (DWORD) flags );
		GraphicsException::CheckHResult( hr );
	}
}
}
