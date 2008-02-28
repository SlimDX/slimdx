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
#include "Texture.h"
#include "RenderToEnvMap.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D9
	{
		bool RenderToEnvironmentMapDescription::operator == ( RenderToEnvironmentMapDescription left, RenderToEnvironmentMapDescription right )
		{
			return RenderToEnvironmentMapDescription::Equals( left, right );
		}

		bool RenderToEnvironmentMapDescription::operator != ( RenderToEnvironmentMapDescription left, RenderToEnvironmentMapDescription right )
		{
			return !RenderToEnvironmentMapDescription::Equals( left, right );
		}

		int RenderToEnvironmentMapDescription::GetHashCode()
		{
			return Size.GetHashCode() + MipLevels.GetHashCode() + Format.GetHashCode()
				 + DepthStencil.GetHashCode() + DepthStencilFormat.GetHashCode();
		}

		bool RenderToEnvironmentMapDescription::Equals( Object^ value )
		{
			if( value == nullptr )
				return false;

			if( value->GetType() != GetType() )
				return false;

			return Equals( static_cast<RenderToEnvironmentMapDescription>( value ) );
		}

		bool RenderToEnvironmentMapDescription::Equals( RenderToEnvironmentMapDescription value )
		{
			return ( Size == value.Size && MipLevels == value.MipLevels && Format == value.Format
				 && DepthStencil == value.DepthStencil && DepthStencilFormat == value.DepthStencilFormat );
		}

		bool RenderToEnvironmentMapDescription::Equals( RenderToEnvironmentMapDescription% value1, RenderToEnvironmentMapDescription% value2 )
		{
			return ( value1.Size == value2.Size && value1.MipLevels == value2.MipLevels && value1.Format == value2.Format
				 && value1.DepthStencil == value2.DepthStencil && value1.DepthStencilFormat == value2.DepthStencilFormat );
		}

		RenderToEnvironmentMap::RenderToEnvironmentMap( ID3DXRenderToEnvMap *pointer )
		{
			Construct(pointer);
		}

		RenderToEnvironmentMap::RenderToEnvironmentMap( IntPtr pointer )
		{
			Construct( pointer, NativeInterface );
		}

		RenderToEnvironmentMap::RenderToEnvironmentMap( Device^ device, int size, int mipLevels, Format format, Format depthStencilFormat )
		{
			ID3DXRenderToEnvMap *result;

			HRESULT hr = D3DXCreateRenderToEnvMap( device->InternalPointer, size, mipLevels, static_cast<D3DFORMAT>( format ),
				true, static_cast<D3DFORMAT>( depthStencilFormat ), &result );
			
			if( RECORD_D3D9( hr ).IsFailure )
				throw gcnew Direct3D9Exception( Result::Last );

			Construct(result);
		}

		RenderToEnvironmentMap::RenderToEnvironmentMap( Device^ device, int size, int mipLevels, Format format )
		{
			ID3DXRenderToEnvMap *result;

			HRESULT hr = D3DXCreateRenderToEnvMap( device->InternalPointer, size, mipLevels, static_cast<D3DFORMAT>( format ),
				false, D3DFMT_UNKNOWN, &result );

			if( RECORD_D3D9( hr ).IsFailure )
				throw gcnew Direct3D9Exception( Result::Last );

			Construct(result);
		}

		RenderToEnvironmentMap^ RenderToEnvironmentMap::FromPointer( ID3DXRenderToEnvMap* pointer )
		{
			RenderToEnvironmentMap^ tableEntry = safe_cast<RenderToEnvironmentMap^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
			if( tableEntry != nullptr )
			{
				pointer->Release();
				return tableEntry;
			}

			return gcnew RenderToEnvironmentMap( pointer );
		}

		RenderToEnvironmentMap^ RenderToEnvironmentMap::FromPointer( IntPtr pointer )
		{
			RenderToEnvironmentMap^ tableEntry = safe_cast<RenderToEnvironmentMap^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
			if( tableEntry != nullptr )
			{
				return tableEntry;
			}

			return gcnew RenderToEnvironmentMap( pointer );
		}

		Result RenderToEnvironmentMap::BeginCube( CubeTexture^ texture )
		{
			HRESULT hr = InternalPointer->BeginCube( texture->InternalPointer );
			return RECORD_D3D9( hr );
		}

		Result RenderToEnvironmentMap::BeginHemisphere( Texture^ positiveZTexture, Texture^ negativeZTexture )
		{
			HRESULT hr = InternalPointer->BeginHemisphere( positiveZTexture->InternalPointer, negativeZTexture->InternalPointer );
			return RECORD_D3D9( hr );
		}

		Result RenderToEnvironmentMap::BeginParabolic( Texture^ positiveZTexture, Texture^ negativeZTexture )
		{
			HRESULT hr = InternalPointer->BeginParabolic( positiveZTexture->InternalPointer, negativeZTexture->InternalPointer );
			return RECORD_D3D9( hr );
		}

		Result RenderToEnvironmentMap::BeginSphere( Texture^ texture )
		{
			HRESULT hr = InternalPointer->BeginSphere( texture->InternalPointer );
			return RECORD_D3D9( hr );
		}

		Result RenderToEnvironmentMap::End( Filter mipFilter )
		{
			HRESULT hr = InternalPointer->End( static_cast<DWORD>( mipFilter ) );
			return RECORD_D3D9( hr );
		}

		Result RenderToEnvironmentMap::Face( CubeMapFace face, Filter mipFilter )
		{
			HRESULT hr = InternalPointer->Face( static_cast<D3DCUBEMAP_FACES>( face ), static_cast<DWORD>( mipFilter ) );
			return RECORD_D3D9( hr );
		}

		Device^ RenderToEnvironmentMap::GetDevice()
		{
			IDirect3DDevice9* device;

			HRESULT hr = InternalPointer->GetDevice( &device );
			
			if( RECORD_D3D9( hr ).IsFailure )
				return nullptr;

			return Device::FromPointer( device );
		}

		Result RenderToEnvironmentMap::OnLostDevice()
		{
			HRESULT hr = InternalPointer->OnLostDevice();
			return RECORD_D3D9( hr );
		}

		Result RenderToEnvironmentMap::OnResetDevice()
		{
			HRESULT hr = InternalPointer->OnResetDevice();
			return RECORD_D3D9( hr );
		}

		RenderToEnvironmentMapDescription RenderToEnvironmentMap::Description::get()
		{
			D3DXRTE_DESC description = {0};

			HRESULT hr = InternalPointer->GetDesc( &description );
			
			if( RECORD_D3D9( hr ).IsFailure )
				return RenderToEnvironmentMapDescription();

			RenderToEnvironmentMapDescription outDesc;
			outDesc.Size = description.Size;
			outDesc.MipLevels = description.MipLevels;
			outDesc.Format = static_cast<Format>( description.Format );
			outDesc.DepthStencil = description.DepthStencil > 0;
			outDesc.DepthStencilFormat = static_cast<Format>( description.DepthStencilFormat );

			return outDesc;
		}
	}
}