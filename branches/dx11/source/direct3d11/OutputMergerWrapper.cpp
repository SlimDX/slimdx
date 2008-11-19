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

#include "BlendState.h"
#include "DepthStencilState.h"
#include "DepthStencilView.h"
#include "OutputMergerWrapper.h"
#include "RenderTargetView.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{ 
	OutputMergerWrapper::OutputMergerWrapper( ID3D11DeviceContext* deviceContext )
	{
		if( deviceContext == 0 )
			throw gcnew ArgumentNullException( "deviceContext" );
		m_DeviceContext = deviceContext;
	}
	
	void OutputMergerWrapper::DepthStencilState::set( SlimDX::Direct3D11::DepthStencilState^ value )
	{
		ID3D11DepthStencilState* oldState;
		int oldReference;
		m_DeviceContext->OMGetDepthStencilState( &oldState, reinterpret_cast<UINT*>( &oldReference ) );
	
		if( value == nullptr )
			m_DeviceContext->OMSetDepthStencilState( 0, oldReference );
		else
			m_DeviceContext->OMSetDepthStencilState( value->InternalPointer, oldReference );
	}
	
	SlimDX::Direct3D11::DepthStencilState^ OutputMergerWrapper::DepthStencilState::get()
	{
		ID3D11DepthStencilState* oldState = 0;
		int oldReference = 0;
		m_DeviceContext->OMGetDepthStencilState( &oldState, reinterpret_cast<UINT*>( &oldReference ) );
		
		return SlimDX::Direct3D11::DepthStencilState::FromPointer( oldState );
	}
	
	void OutputMergerWrapper::DepthStencilReference::set( int value )
	{
		ID3D11DepthStencilState* oldState = 0;
		int oldReference = 0;
		m_DeviceContext->OMGetDepthStencilState( &oldState, reinterpret_cast<UINT*>( &oldReference ) );
	
		m_DeviceContext->OMSetDepthStencilState( oldState, value );
	}
	
	int OutputMergerWrapper::DepthStencilReference::get()
	{
		ID3D11DepthStencilState* oldState = 0;
		int oldReference = 0;
		m_DeviceContext->OMGetDepthStencilState( &oldState, reinterpret_cast<UINT*>( &oldReference ) );
		
		return oldReference;
	}
	
	void OutputMergerWrapper::BlendState::set( SlimDX::Direct3D11::BlendState^ value )
	{
		ID3D11BlendState* oldState = 0;
		float oldFactor[4];
		int oldMask = 0;
		m_DeviceContext->OMGetBlendState( &oldState, oldFactor, reinterpret_cast<UINT*>( &oldMask ) );
		
		if( value == nullptr )
		{
			m_DeviceContext->OMSetBlendState( 0, oldFactor, oldMask );
		}
		else 
		{
			m_DeviceContext->OMSetBlendState( value->InternalPointer, oldFactor, oldMask );
		}
	}
	
	SlimDX::Direct3D11::BlendState^ OutputMergerWrapper::BlendState::get()
	{
		ID3D11BlendState* oldState = 0;
		float oldFactor[4];
		int oldMask = 0;
		m_DeviceContext->OMGetBlendState( &oldState, oldFactor, reinterpret_cast<UINT*>( &oldMask ) );
		
		return SlimDX::Direct3D11::BlendState::FromPointer( oldState );
	}
	
	void OutputMergerWrapper::BlendFactor::set( Color4 value )
	{
		ID3D11BlendState* oldState = 0;
		float oldFactor[4];
		int oldMask = 0;
		m_DeviceContext->OMGetBlendState( &oldState, oldFactor, reinterpret_cast<UINT*>( &oldMask ) );
		
		float newFactor[4] = { value.Red, value.Green, value.Blue, value.Alpha };
		m_DeviceContext->OMSetBlendState( oldState, newFactor, oldMask );
	}
	
	Color4 OutputMergerWrapper::BlendFactor::get()
	{
		ID3D11BlendState* oldState = 0;
		float oldFactor[4];
		int oldMask = 0;
		m_DeviceContext->OMGetBlendState( &oldState, oldFactor, reinterpret_cast<UINT*>( &oldMask ) );
		
		return Color4( oldFactor[3], oldFactor[0], oldFactor[1], oldFactor[2] );
	}
	
	void OutputMergerWrapper::BlendSampleMask::set( int value )
	{
		ID3D11BlendState* oldState = 0;
		float oldFactor[4];
		int oldMask = 0;
		m_DeviceContext->OMGetBlendState( &oldState, oldFactor, reinterpret_cast<UINT*>( &oldMask ) );
	
		m_DeviceContext->OMSetBlendState( oldState, oldFactor, value );
	}
	
	int OutputMergerWrapper::BlendSampleMask::get()
	{
		ID3D11BlendState* oldState = 0;
		float oldFactor[4];
		int oldMask = 0;
		m_DeviceContext->OMGetBlendState( &oldState, oldFactor, reinterpret_cast<UINT*>( &oldMask ) );
		
		return oldMask;
	}
	
	void OutputMergerWrapper::SetTargets( RenderTargetView^ renderTargetView )
	{
		SetTargets( nullptr, renderTargetView );
	}
	
	void OutputMergerWrapper::SetTargets( DepthStencilView^ depthStencilView, RenderTargetView^ renderTargetView )
	{
		ID3D11DepthStencilView *nativeDSV = depthStencilView == nullptr ? 0 : static_cast<ID3D11DepthStencilView*>( depthStencilView->InternalPointer );
		ID3D11RenderTargetView *nativeRTV[] = { renderTargetView == nullptr ? 0 : static_cast<ID3D11RenderTargetView*>( renderTargetView->InternalPointer ) };
		
		m_DeviceContext->OMSetRenderTargets( 1, nativeRTV, nativeDSV );
	}

	void OutputMergerWrapper::SetTargets( ... array<RenderTargetView^>^ renderTargets )
	{
		SetTargets( nullptr, renderTargets );
	}

	void OutputMergerWrapper::SetTargets( DepthStencilView^ depthStencilView, ... array<RenderTargetView^>^ renderTargets )
	{
		ID3D11DepthStencilView *nativeDSV = depthStencilView == nullptr ? 0 : static_cast<ID3D11DepthStencilView*>( depthStencilView->InternalPointer );
		ID3D11RenderTargetView* nativeRTVs[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
		
		if( renderTargets == nullptr )
		{
			m_DeviceContext->OMSetRenderTargets( 0, 0, nativeDSV );
		}
		else 
		{
			for( int i = 0; i < renderTargets->Length; ++i )
				nativeRTVs[ i ] = renderTargets[ i ] == nullptr ? 0 : static_cast<ID3D11RenderTargetView*>( renderTargets[ i ]->InternalPointer );
			m_DeviceContext->OMSetRenderTargets( renderTargets->Length, nativeRTVs, nativeDSV );
		}
	}
}
}
