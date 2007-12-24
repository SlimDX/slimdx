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
#include "Texture.h"
#include "RenderToEnvMap.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		RenderToEnvironmentMap::RenderToEnvironmentMap( ID3DXRenderToEnvMap *pointer )
		{
			m_Pointer = pointer;
		}

		RenderToEnvironmentMap::RenderToEnvironmentMap( IntPtr pointer )
		{
			if( pointer == IntPtr::Zero )
				throw gcnew ArgumentNullException( "pointer" );

			void* result;
			IUnknown* unknown = static_cast<IUnknown*>( pointer.ToPointer() );
			HRESULT hr = unknown->QueryInterface( IID_ID3DXRenderToEnvMap, &result );
			if( FAILED( hr ) )
				throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

			m_Pointer = static_cast<ID3DXRenderToEnvMap*>( result );
		}

		RenderToEnvironmentMap::RenderToEnvironmentMap( Device^ device, int size, int mipLevels, Format format, Format depthStencilFormat )
		{
			ID3DXRenderToEnvMap *result;

			HRESULT hr = D3DXCreateRenderToEnvMap( device->InternalPointer, size, mipLevels, static_cast<D3DFORMAT>( format ),
				true, static_cast<D3DFORMAT>( depthStencilFormat ), &result );
			GraphicsException::CheckHResult( hr );

			if( FAILED( hr ) )
				throw gcnew GraphicsException();

			m_Pointer = result;
		}

		RenderToEnvironmentMap::RenderToEnvironmentMap( Device^ device, int size, int mipLevels, Format format )
		{
			ID3DXRenderToEnvMap *result;

			HRESULT hr = D3DXCreateRenderToEnvMap( device->InternalPointer, size, mipLevels, static_cast<D3DFORMAT>( format ),
				false, D3DFMT_UNKNOWN, &result );
			GraphicsException::CheckHResult( hr );

			if( FAILED( hr ) )
				throw gcnew GraphicsException();

			m_Pointer = result;
		}

		void RenderToEnvironmentMap::BeginCube( CubeTexture^ texture )
		{
			HRESULT hr = m_Pointer->BeginCube( texture->TexturePointer );
			GraphicsException::CheckHResult( hr );
		}

		void RenderToEnvironmentMap::BeginHemisphere( Texture^ positiveZTexture, Texture^ negativeZTexture )
		{
			HRESULT hr = m_Pointer->BeginHemisphere( positiveZTexture->TexturePointer, negativeZTexture->TexturePointer );
			GraphicsException::CheckHResult( hr );
		}

		void RenderToEnvironmentMap::BeginParabolic( Texture^ positiveZTexture, Texture^ negativeZTexture )
		{
			HRESULT hr = m_Pointer->BeginParabolic( positiveZTexture->TexturePointer, negativeZTexture->TexturePointer );
			GraphicsException::CheckHResult( hr );
		}

		void RenderToEnvironmentMap::BeginSphere( Texture^ texture )
		{
			HRESULT hr = m_Pointer->BeginSphere( texture->TexturePointer );
			GraphicsException::CheckHResult( hr );
		}

		void RenderToEnvironmentMap::End( Filter mipFilter )
		{
			HRESULT hr = m_Pointer->End( static_cast<DWORD>( mipFilter ) );
			GraphicsException::CheckHResult( hr );
		}

		void RenderToEnvironmentMap::Face( CubeMapFace face, Filter mipFilter )
		{
			HRESULT hr = m_Pointer->Face( static_cast<D3DCUBEMAP_FACES>( face ), static_cast<DWORD>( mipFilter ) );
			GraphicsException::CheckHResult( hr );
		}

		Device^ RenderToEnvironmentMap::GetDevice()
		{
			IDirect3DDevice9* device;

			HRESULT hr = m_Pointer->GetDevice( &device );
			GraphicsException::CheckHResult( hr );

			if( FAILED( hr ) )
				return nullptr;

			return gcnew Device( device );
		}

		void RenderToEnvironmentMap::OnLostDevice()
		{
			HRESULT hr = m_Pointer->OnLostDevice();
			GraphicsException::CheckHResult( hr );
		}

		void RenderToEnvironmentMap::OnResetDevice()
		{
			HRESULT hr = m_Pointer->OnResetDevice();
			GraphicsException::CheckHResult( hr );
		}

		RenderToEnvironmentMapDescription RenderToEnvironmentMap::Description::get()
		{
			D3DXRTE_DESC desc = {0};

			HRESULT hr = m_Pointer->GetDesc( &desc );
			GraphicsException::CheckHResult( hr );

			RenderToEnvironmentMapDescription outDesc;
			outDesc.Size = desc.Size;
			outDesc.MipLevels = desc.MipLevels;
			outDesc.Format = static_cast<Format>( desc.Format );
			outDesc.DepthStencil = desc.DepthStencil > 0;
			outDesc.DepthStencilFormat = static_cast<Format>( desc.DepthStencilFormat );

			return outDesc;
		}
	}
}