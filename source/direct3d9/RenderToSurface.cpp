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

#include "Direct3D9Exception.h"

#include "Device.h"
#include "Surface.h"
#include "RenderToSurface.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D9
	{
		bool RenderToSurfaceDescription::operator == ( RenderToSurfaceDescription left, RenderToSurfaceDescription right )
		{
			return RenderToSurfaceDescription::Equals( left, right );
		}

		bool RenderToSurfaceDescription::operator != ( RenderToSurfaceDescription left, RenderToSurfaceDescription right )
		{
			return !RenderToSurfaceDescription::Equals( left, right );
		}

		int RenderToSurfaceDescription::GetHashCode()
		{
			return Width.GetHashCode() + Height.GetHashCode() + Format.GetHashCode()
				 + DepthStencil.GetHashCode() + DepthStencilFormat.GetHashCode();
		}

		bool RenderToSurfaceDescription::Equals( Object^ value )
		{
			if( value == nullptr )
				return false;

			if( value->GetType() != GetType() )
				return false;

			return Equals( static_cast<RenderToSurfaceDescription>( value ) );
		}

		bool RenderToSurfaceDescription::Equals( RenderToSurfaceDescription value )
		{
			return ( Width == value.Width && Height == value.Height && Format == value.Format
				 && DepthStencil == value.DepthStencil && DepthStencilFormat == value.DepthStencilFormat );
		}

		bool RenderToSurfaceDescription::Equals( RenderToSurfaceDescription% value1, RenderToSurfaceDescription% value2 )
		{
			return ( value1.Width == value2.Width && value1.Height == value2.Height && value1.Format == value2.Format
				 && value1.DepthStencil == value2.DepthStencil && value1.DepthStencilFormat == value2.DepthStencilFormat );
		}

		RenderToSurface::RenderToSurface( ID3DXRenderToSurface* pointer )
		{
			Construct( pointer );
		}

		RenderToSurface::RenderToSurface( IntPtr pointer )
		{
			Construct( pointer, NativeInterface );
		}

		RenderToSurface::RenderToSurface( Device^ device, int width, int height, Format format )
		{
			ID3DXRenderToSurface* rtsPointer;
			HRESULT hr = D3DXCreateRenderToSurface( device->InternalPointer, width, height, static_cast<D3DFORMAT>( format ), FALSE, D3DFMT_UNKNOWN, &rtsPointer );
			
			if( RECORD_D3D9( hr ).IsFailure )
				throw gcnew Direct3D9Exception( Result::Last );

			Construct(rtsPointer);
		}

		RenderToSurface::RenderToSurface( Device^ device, int width, int height, Format format, Format depthStencilFormat )
		{
			ID3DXRenderToSurface* rtsPointer;
			HRESULT hr = D3DXCreateRenderToSurface( device->InternalPointer, width, height,
				static_cast<D3DFORMAT>( format ), TRUE, static_cast<D3DFORMAT>( depthStencilFormat ), &rtsPointer );
			
			if( RECORD_D3D9( hr ).IsFailure )
				throw gcnew Direct3D9Exception( Result::Last );

			Construct(rtsPointer);
		}

		RenderToSurface^ RenderToSurface::FromPointer( ID3DXRenderToSurface* pointer )
		{
			RenderToSurface^ tableEntry = safe_cast<RenderToSurface^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
			if( tableEntry != nullptr )
			{
				pointer->Release();
				return tableEntry;
			}

			return gcnew RenderToSurface( pointer );
		}

		RenderToSurface^ RenderToSurface::FromPointer( IntPtr pointer )
		{
			RenderToSurface^ tableEntry = safe_cast<RenderToSurface^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
			if( tableEntry != nullptr )
			{
				return tableEntry;
			}

			return gcnew RenderToSurface( pointer );
		}

		Result RenderToSurface::BeginScene( Surface^ renderSurface, SlimDX::Viewport viewport )
		{
			IDirect3DSurface9* surface = renderSurface->InternalPointer;
			HRESULT hr = InternalPointer->BeginScene( surface, reinterpret_cast<D3DVIEWPORT9*>( &viewport ) );
			return RECORD_D3D9( hr );
		}

		Result RenderToSurface::EndScene( Filter mipFilter )
		{
			HRESULT hr = InternalPointer->EndScene( static_cast<DWORD>( mipFilter ) );
			return RECORD_D3D9( hr );
		}

		Device^ RenderToSurface::GetDevice()
		{
			IDirect3DDevice9* device;
			HRESULT hr = InternalPointer->GetDevice( &device );
			
			if( RECORD_D3D9( hr ).IsFailure )
				return nullptr;

			return Device::FromPointer( device );
		}

		Result RenderToSurface::OnLostDevice()
		{
			HRESULT hr = InternalPointer->OnLostDevice();
			return RECORD_D3D9( hr );
		}

		Result RenderToSurface::OnResetDevice()
		{
			HRESULT hr = InternalPointer->OnResetDevice();
			return RECORD_D3D9( hr );
		}

		RenderToSurfaceDescription RenderToSurface::Description::get()
		{
			D3DXRTS_DESC description = {0};
			HRESULT hr = InternalPointer->GetDesc( &description );
			
			if( RECORD_D3D9( hr ).IsFailure )
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