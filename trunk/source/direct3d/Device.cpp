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
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "../DirectXObject.h"
#include "../Utils.h"
#include "../math/Math.h"
#include "GraphicsException.h"

#include "Device.h"
#include "Direct3D.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "RenderStateManager.h"
#include "TransformManager.h"
#include "D3DX.h"

namespace SlimDX
{
namespace Direct3D
{
	//quick utility function
	void ConvertPresentParams( PresentParameters^ presentParams, D3DPRESENT_PARAMETERS& d3dpp )
	{
		d3dpp.AutoDepthStencilFormat = (D3DFORMAT) presentParams->AutoDepthStencilFormat;
		d3dpp.BackBufferCount = presentParams->BackBufferCount;
		d3dpp.BackBufferFormat = (D3DFORMAT) presentParams->BackBufferFormat;
		d3dpp.BackBufferHeight = presentParams->BackBufferHeight;
		d3dpp.BackBufferWidth = presentParams->BackBufferWidth;
		d3dpp.EnableAutoDepthStencil = presentParams->EnableAutoDepthStencil;
		d3dpp.Flags = (DWORD) presentParams->PresentFlag;
		d3dpp.FullScreen_RefreshRateInHz = presentParams->FullScreenRefreshRateInHz;
		d3dpp.hDeviceWindow = (HWND) presentParams->DeviceWindowHandle.ToPointer();
		d3dpp.MultiSampleQuality = presentParams->MultiSampleQuality;
		d3dpp.MultiSampleType = (D3DMULTISAMPLE_TYPE) presentParams->MultiSample;
		d3dpp.PresentationInterval = (UINT) presentParams->PresentationInterval;
		d3dpp.SwapEffect = (D3DSWAPEFFECT) presentParams->SwapEffect;
		d3dpp.Windowed = presentParams->Windowed;
	}

	Device::Device( int adapter, DeviceType deviceType, IntPtr controlHandle, CreateFlags createFlags, PresentParameters^ presentParams )
	{
		IDirect3DDevice9* device;
		D3DPRESENT_PARAMETERS d3dpp;

		ConvertPresentParams( presentParams, d3dpp );
		HRESULT hr = Direct3D::InternalPointer->CreateDevice( adapter, (D3DDEVTYPE) deviceType, (HWND) controlHandle.ToPointer(), 
			(DWORD) createFlags, (D3DPRESENT_PARAMETERS*) &d3dpp, &device );
		GraphicsException::CheckHResult( hr );

		m_Device = device;
		m_RenderState = gcnew RenderStateManager( this );
		m_Transforms = gcnew TransformManager( this );
	}

	Device::~Device()
	{
		delete m_RenderState;
		delete m_Transforms;
	}

	void Device::Indices::set( IndexBuffer^ value )
	{
		m_Indices = value;

		HRESULT hr;
		if( value != nullptr )
			 hr = m_Device->SetIndices( value->InternalPointer );
		else
			hr = m_Device->SetIndices( NULL );

		GraphicsException::CheckHResult( hr );
	}

	void Device::VertexFormat::set( VertexFormats value )
	{
		m_VertexFormat = value;
		HRESULT hr = m_Device->SetFVF( (DWORD) value );
		GraphicsException::CheckHResult( hr );
	}

	void Device::VertexDeclaration::set( SlimDX::Direct3D::VertexDeclaration^ value )
	{
		m_VertexDecl = value;

		HRESULT hr;
		if( value != nullptr )
			hr = m_Device->SetVertexDeclaration( value->InternalPointer );
		else
			hr = m_Device->SetVertexDeclaration( NULL );

		GraphicsException::CheckHResult( hr );
	}

	void Device::DrawPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount )
	{
		HRESULT hr = m_Device->DrawPrimitive( (D3DPRIMITIVETYPE) primitiveType, startIndex, primitiveCount );
		GraphicsException::CheckHResult( hr );
	}

	generic<typename T>
	void Device::DrawUserPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount, array<T>^ data )
	{
		pin_ptr<T> pinned_data = &data[startIndex];

		HRESULT hr = m_Device->DrawPrimitiveUP( (D3DPRIMITIVETYPE) primitiveType, primitiveCount,
			pinned_data, Marshal::SizeOf( T::typeid ) );
		GraphicsException::CheckHResult( hr );
	}

	void Device::DrawIndexedPrimitives( PrimitiveType primitiveType, int baseVertexIndex, int minVertexIndex, 
					int numVertices, int startIndex, int primCount )
	{
		HRESULT hr = m_Device->DrawIndexedPrimitive( (D3DPRIMITIVETYPE) primitiveType, baseVertexIndex,
			minVertexIndex, numVertices, startIndex, primCount );
		GraphicsException::CheckHResult( hr );
	}

	void Device::Clear( ClearFlags clearFlags, int color, float zdepth, int stencil )
	{
		HRESULT hr = m_Device->Clear( 0, 0, (DWORD) clearFlags, (D3DCOLOR) color, zdepth, stencil );
		GraphicsException::CheckHResult( hr );
	}

	void Device::Clear( ClearFlags clearFlags, Color color, float zdepth, int stencil )
	{
		Clear( clearFlags, color.ToArgb(), zdepth, stencil );
	}

	void Device::BeginScene()
	{
		HRESULT hr = m_Device->BeginScene();
		GraphicsException::CheckHResult( hr );
	}

	void Device::EndScene()
	{
		HRESULT hr = m_Device->EndScene();
		GraphicsException::CheckHResult( hr );
	}

	void Device::Present()
	{
		HRESULT hr = m_Device->Present( 0, 0, 0, 0 );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetStreamSource( int stream, VertexBuffer^ streamData, int offsetInBytes, int stride )
	{
		HRESULT hr = m_Device->SetStreamSource( stream, streamData->InternalPointer, offsetInBytes, stride );
		GraphicsException::CheckHResult( hr );
	}

	void Device::TestCooperativeLevel()
	{
		HRESULT hr = m_Device->TestCooperativeLevel();
		GraphicsException::CheckHResult( hr );
	}

	CooperativeLevel Device::CheckCooperativeLevel()
	{
		HRESULT hr = m_Device->TestCooperativeLevel();
		return (CooperativeLevel) hr;
	}

	void Device::Reset( PresentParameters^ presentParams )
	{
		D3DPRESENT_PARAMETERS d3dpp;

		ConvertPresentParams( presentParams, d3dpp );
		HRESULT hr = m_Device->Reset( &d3dpp );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetTexture( int sampler, BaseTexture^ texture )
	{
		HRESULT hr = m_Device->SetTexture( sampler, texture->BasePointer );
		GraphicsException::CheckHResult( hr );
	}

	void Device::SetRenderTarget( int rtIndex, Surface^ target )
	{
		HRESULT hr = m_Device->SetRenderTarget( rtIndex, target->InternalPointer );
		GraphicsException::CheckHResult( hr );
	}
	
	void Device::SetPixelShader( PixelShader^ shader )
	{
		HRESULT hr = m_Device->SetPixelShader( shader->InternalPointer );
		GraphicsException::CheckHResult( hr );
	}
	
	void Device::SetVertexShader( VertexShader^ shader )
	{
		HRESULT hr = m_Device->SetVertexShader( shader->InternalPointer );
		GraphicsException::CheckHResult( hr );
	}

	Surface^ Device::GetBackBuffer( int swapChain, int backBuffer )
	{
		IDirect3DSurface9* buffer;

		HRESULT hr = m_Device->GetBackBuffer( swapChain, backBuffer, D3DBACKBUFFER_TYPE_MONO, &buffer );
		GraphicsException::CheckHResult( hr );

		return gcnew Surface( buffer );
	}
}
}
