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

#include "GraphicsException.h"
#include "Device.h"
#include "Surface.h"
#include "RenderToSurface.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		RenderToSurface::RenderToSurface( ID3DXRenderToSurface* pointer ) : DirectXObject( pointer )
		{
			if( pointer == NULL )
				throw gcnew ArgumentNullException( "pointer" );
		}

		RenderToSurface::RenderToSurface( Device^ device, int width, int height, Format format )
		{
			ID3DXRenderToSurface* rtsPointer;
			HRESULT hr = D3DXCreateRenderToSurface( device->InternalPointer, width, height, (D3DFORMAT) format, FALSE, D3DFMT_UNKNOWN, &rtsPointer );
			GraphicsException::CheckHResult( hr );
			if( FAILED( hr ) )
				throw gcnew GraphicsException();

			m_Pointer = rtsPointer;
		}

		RenderToSurface::RenderToSurface( Device^ device, int width, int height, Format format, Format depthStencilFormat )
		{
			ID3DXRenderToSurface* rtsPointer;
			HRESULT hr = D3DXCreateRenderToSurface( device->InternalPointer, width, height,
				(D3DFORMAT) format, TRUE, (D3DFORMAT) depthStencilFormat, &rtsPointer );
			GraphicsException::CheckHResult( hr );
			if( FAILED( hr ) )
				throw gcnew GraphicsException();

			m_Pointer = rtsPointer;
		}

		void RenderToSurface::BeginScene( Surface^ renderSurface, Viewport viewport )
		{
			IDirect3DSurface9* surface = renderSurface->SurfacePointer;
			HRESULT hr = m_Pointer->BeginScene( surface, (D3DVIEWPORT9*) &viewport );
			GraphicsException::CheckHResult( hr );
		}

		void RenderToSurface::EndScene( Filter mipFilter )
		{
			HRESULT hr = m_Pointer->EndScene( (DWORD) mipFilter );
			GraphicsException::CheckHResult( hr );
		}

		Device^ RenderToSurface::GetDevice()
		{
			IDirect3DDevice9* device;
			HRESULT hr = m_Pointer->GetDevice( &device );
			GraphicsException::CheckHResult( hr );
			if( FAILED( hr ) )
				return nullptr;

			return gcnew Device( device );
		}

		void RenderToSurface::OnLostDevice()
		{
			HRESULT hr = m_Pointer->OnLostDevice();
			GraphicsException::CheckHResult( hr );
		}

		void RenderToSurface::OnResetDevice()
		{
			HRESULT hr = m_Pointer->OnResetDevice();
			GraphicsException::CheckHResult( hr );
		}

		RenderToSurfaceDescription RenderToSurface::Description::get()
		{
			D3DXRTS_DESC desc = {0};
			HRESULT hr = m_Pointer->GetDesc( &desc );
			GraphicsException::CheckHResult( hr );

			RenderToSurfaceDescription outDesc;
			outDesc.Width = desc.Width;
			outDesc.Height = desc.Height;
			outDesc.Format = (Format) desc.Format;
			outDesc.DepthStencil = desc.DepthStencil > 0;
			outDesc.DepthStencilFormat = (Format) desc.DepthStencilFormat;
			return outDesc;
		}
	}
}