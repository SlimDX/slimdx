#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Exceptions.h"
#include "Device.h"
#include "RenderStateManager.h"

namespace SlimDX
{
namespace Direct3D
{
	Cull RenderStateManager::CullMode::get()
	{
		DWORD value;
		HRESULT hr = m_Device->InternalPointer->GetRenderState( D3DRS_CULLMODE, &value );
		GraphicsException::CheckHResult( hr );
		return (Cull) value;
	}

	void RenderStateManager::CullMode::set( Cull cull )
	{
		HRESULT hr = m_Device->InternalPointer->SetRenderState( D3DRS_CULLMODE, (DWORD) cull );
		GraphicsException::CheckHResult( hr );
	}

	bool RenderStateManager::ZBufferEnable::get()
	{
		DWORD value;
		HRESULT hr = m_Device->InternalPointer->GetRenderState( D3DRS_ZENABLE, &value );
		GraphicsException::CheckHResult( hr );
		return value > 0;
	}

	void RenderStateManager::ZBufferEnable::set( bool value )
	{
		HRESULT hr = m_Device->InternalPointer->SetRenderState( D3DRS_ZENABLE, value );
		GraphicsException::CheckHResult( hr );
	}
}
}
