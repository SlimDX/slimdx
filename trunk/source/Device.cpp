#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Exceptions.h"
#include "Device.h"
#include "Manager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "RenderStateManager.h"
#include "Utils.h"

namespace SlimDX
{
namespace Direct3D
{
	Device::Device( int adapter, DeviceType deviceType, IntPtr controlHandle, CreateFlags createFlags, PresentParameters^ presentParams )
	{
		IDirect3DDevice9* device;

		//TODO: Interop the present parameters correctly
		D3DPRESENT_PARAMETERS d3dpp = { 0 };
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

		HRESULT hr = Manager::Direct3D->CreateDevice( adapter, (D3DDEVTYPE) deviceType, (HWND) controlHandle.ToPointer(), 
			(DWORD) createFlags, (D3DPRESENT_PARAMETERS*) &d3dpp, &device );
		GraphicsException::CheckHResult( hr );

		m_Device = device;
		m_Disposed = false;

		m_RenderState = gcnew RenderStateManager( this );
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
}
}
