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

#include "../Exceptions.h"
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

	bool RenderStateManager::AlphaBlendEnable::get()
	{
		DWORD value;
		HRESULT hr = m_Device->InternalPointer->GetRenderState( D3DRS_ALPHABLENDENABLE, &value );
		GraphicsException::CheckHResult( hr );
		return value > 0;
	}

	void RenderStateManager::AlphaBlendEnable::set( bool value )
	{
		HRESULT hr = m_Device->InternalPointer->SetRenderState( D3DRS_ALPHABLENDENABLE, value );
		GraphicsException::CheckHResult( hr );
	}
}
}
