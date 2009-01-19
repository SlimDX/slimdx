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

#include <d3d11.h>
#include <d3dx11.h>

#include "../ComObject.h"

#include "RasterizerWrapper.h"
#include "RasterizerState.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{ 
	RasterizerWrapper::RasterizerWrapper( ID3D11DeviceContext* deviceContext )
	{
		if( deviceContext == 0 )
			throw gcnew ArgumentNullException( "deviceContext" );
		m_DeviceContext = deviceContext;
	}
	
	void RasterizerWrapper::State::set( RasterizerState^ value )
	{
		if( value == nullptr )
			m_DeviceContext->RSSetState( 0 );
		else
			m_DeviceContext->RSSetState( value->InternalPointer );
	}
	
	RasterizerState^ RasterizerWrapper::State::get()
	{
		ID3D11RasterizerState* state = 0;
		m_DeviceContext->RSGetState( &state );
		return RasterizerState::FromPointer( state );
	}
	
	void RasterizerWrapper::SetViewports( SlimDX::Viewport viewport )
	{
		D3D11_VIEWPORT nativeVP = { static_cast<FLOAT>( viewport.X ), static_cast<FLOAT>( viewport.Y ), 
			static_cast<FLOAT>( viewport.Width ), static_cast<FLOAT>( viewport.Height ), 
			static_cast<FLOAT>( viewport.MinZ ), static_cast<FLOAT>( viewport.MaxZ ) };
		m_DeviceContext->RSSetViewports( 1, &nativeVP );
	}

	void RasterizerWrapper::SetViewports( ... array<SlimDX::Viewport>^ viewports )
	{
		if( viewports == nullptr ) 
		{
			m_DeviceContext->RSSetViewports( 0, 0 );
		}
		else
		{
			D3D11_VIEWPORT nativeVPs[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
			for( int i = 0; i < viewports->Length; ++i )
			{
				nativeVPs[ i ].TopLeftX = static_cast<FLOAT>( viewports[ i ].X );
				nativeVPs[ i ].TopLeftY = static_cast<FLOAT>( viewports[ i ].Y );
				nativeVPs[ i ].Width = static_cast<FLOAT>( viewports[ i ].Width );
				nativeVPs[ i ].Height = static_cast<FLOAT>( viewports[ i ].Height );
				nativeVPs[ i ].MinDepth = static_cast<FLOAT>( viewports[ i ].MinZ );
				nativeVPs[ i ].MaxDepth = static_cast<FLOAT>( viewports[ i ].MaxZ );
			}
			
			m_DeviceContext->RSSetViewports( viewports->Length, nativeVPs );
		}
	}
}
}
