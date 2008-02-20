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

//#include "Direct3D9ErrorHandler.h"
#include "Direct3D9Exception.h"

#include "Device.h"
#include "Surface.h"
#include "RenderToSurface.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D9
	{
		/* Unused for now.
		RenderToSurface::RenderToSurface( ID3DXRenderToSurface* pointer ) : ComObject( pointer )
		{
			if( pointer == NULL )
				throw gcnew ArgumentNullException( "pointer" );
		}
		*/

		RenderToSurface::RenderToSurface( IntPtr rts )
		{
			Construct( rts, NativeInterface );
		}

		RenderToSurface::RenderToSurface( Device^ device, int width, int height, Format format )
		{
			ID3DXRenderToSurface* rtsPointer;
			HRESULT hr = D3DXCreateRenderToSurface( device->InternalPointer, width, height, static_cast<D3DFORMAT>( format ), FALSE, D3DFMT_UNKNOWN, &rtsPointer );
			
			if( Result::Record( hr ).IsFailure )
				throw gcnew Direct3D9Exception();

			Construct(rtsPointer);
		}

		RenderToSurface::RenderToSurface( Device^ device, int width, int height, Format format, Format depthStencilFormat )
		{
			ID3DXRenderToSurface* rtsPointer;
			HRESULT hr = D3DXCreateRenderToSurface( device->InternalPointer, width, height,
				static_cast<D3DFORMAT>( format ), TRUE, static_cast<D3DFORMAT>( depthStencilFormat ), &rtsPointer );
			
			if( Result::Record( hr ).IsFailure )
				throw gcnew Direct3D9Exception();

			Construct(rtsPointer);
		}

		Result RenderToSurface::BeginScene( Surface^ renderSurface, SlimDX::Direct3D::Viewport viewport )
		{
			IDirect3DSurface9* surface = renderSurface->SurfacePointer;
			HRESULT hr = InternalPointer->BeginScene( surface, reinterpret_cast<D3DVIEWPORT9*>( &viewport ) );
			return Result::Record( hr );
		}

		Result RenderToSurface::EndScene( Filter mipFilter )
		{
			HRESULT hr = InternalPointer->EndScene( static_cast<DWORD>( mipFilter ) );
			return Result::Record( hr );
		}

		Device^ RenderToSurface::GetDevice()
		{
			IDirect3DDevice9* device;
			HRESULT hr = InternalPointer->GetDevice( &device );
			
			if( Result::Record( hr ).IsFailure )
				return nullptr;

			return gcnew Device( device );
		}

		Result RenderToSurface::OnLostDevice()
		{
			HRESULT hr = InternalPointer->OnLostDevice();
			return Result::Record( hr );
		}

		Result RenderToSurface::OnResetDevice()
		{
			HRESULT hr = InternalPointer->OnResetDevice();
			return Result::Record( hr );
		}

		RenderToSurfaceDescription RenderToSurface::Description::get()
		{
			D3DXRTS_DESC description = {0};
			HRESULT hr = InternalPointer->GetDesc( &description );
			
			if( Result::Record( hr ).IsFailure )
				return RenderToSurfaceDescription();

			RenderToSurfaceDescription outDesc;
			outDesc.Width = description.Width;
			outDesc.Height = description.Height;
			outDesc.Format = static_cast<Format>( description.Format );
			outDesc.DepthStencil = description.DepthStencil > 0;
			outDesc.DepthStencilFormat = static_cast<Format>( description.DepthStencilFormat );
			return outDesc;
		}
	}
}