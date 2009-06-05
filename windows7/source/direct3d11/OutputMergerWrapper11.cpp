#include "stdafx.h"
/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include "BlendState11.h"
#include "DepthStencilState11.h"
#include "DepthStencilView11.h"
#include "OutputMergerWrapper11.h"
#include "RenderTargetView11.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{ 
	OutputMergerWrapper::OutputMergerWrapper( ID3D11DeviceContext* device )
	{
		if( device == 0 )
			throw gcnew ArgumentNullException( "device" );
		deviceContext = device;
	}
	
	void OutputMergerWrapper::DepthStencilState::set( SlimDX::Direct3D11::DepthStencilState^ value )
	{
		ID3D11DepthStencilState* oldState;
		int oldReference;
		deviceContext->OMGetDepthStencilState( &oldState, reinterpret_cast<UINT*>( &oldReference ) );
	
		if( value == nullptr )
			deviceContext->OMSetDepthStencilState( 0, oldReference );
		else
			deviceContext->OMSetDepthStencilState( value->InternalPointer, oldReference );
	}
	
	SlimDX::Direct3D11::DepthStencilState^ OutputMergerWrapper::DepthStencilState::get()
	{
		ID3D11DepthStencilState* oldState = 0;
		int oldReference = 0;
		deviceContext->OMGetDepthStencilState( &oldState, reinterpret_cast<UINT*>( &oldReference ) );
		
		return SlimDX::Direct3D11::DepthStencilState::FromPointer( oldState );
	}
	
	void OutputMergerWrapper::DepthStencilReference::set( int value )
	{
		ID3D11DepthStencilState* oldState = 0;
		int oldReference = 0;
		deviceContext->OMGetDepthStencilState( &oldState, reinterpret_cast<UINT*>( &oldReference ) );
	
		deviceContext->OMSetDepthStencilState( oldState, value );
	}
	
	int OutputMergerWrapper::DepthStencilReference::get()
	{
		ID3D11DepthStencilState* oldState = 0;
		int oldReference = 0;
		deviceContext->OMGetDepthStencilState( &oldState, reinterpret_cast<UINT*>( &oldReference ) );
		
		return oldReference;
	}
	
	void OutputMergerWrapper::BlendState::set( SlimDX::Direct3D11::BlendState^ value )
	{
		ID3D11BlendState* oldState = 0;
		float oldFactor[4];
		int oldMask = 0;
		deviceContext->OMGetBlendState( &oldState, oldFactor, reinterpret_cast<UINT*>( &oldMask ) );
		
		if( value == nullptr )
		{
			deviceContext->OMSetBlendState( 0, oldFactor, oldMask );
		}
		else 
		{
			deviceContext->OMSetBlendState( value->InternalPointer, oldFactor, oldMask );
		}
	}
	
	SlimDX::Direct3D11::BlendState^ OutputMergerWrapper::BlendState::get()
	{
		ID3D11BlendState* oldState = 0;
		float oldFactor[4];
		int oldMask = 0;
		deviceContext->OMGetBlendState( &oldState, oldFactor, reinterpret_cast<UINT*>( &oldMask ) );
		
		return SlimDX::Direct3D11::BlendState::FromPointer( oldState );
	}
	
	void OutputMergerWrapper::BlendFactor::set( Color4 value )
	{
		ID3D11BlendState* oldState = 0;
		float oldFactor[4];
		int oldMask = 0;
		deviceContext->OMGetBlendState( &oldState, oldFactor, reinterpret_cast<UINT*>( &oldMask ) );
		
		float newFactor[4] = { value.Red, value.Green, value.Blue, value.Alpha };
		deviceContext->OMSetBlendState( oldState, newFactor, oldMask );
	}
	
	Color4 OutputMergerWrapper::BlendFactor::get()
	{
		ID3D11BlendState* oldState = 0;
		float oldFactor[4];
		int oldMask = 0;
		deviceContext->OMGetBlendState( &oldState, oldFactor, reinterpret_cast<UINT*>( &oldMask ) );
		
		return Color4( oldFactor[3], oldFactor[0], oldFactor[1], oldFactor[2] );
	}
	
	void OutputMergerWrapper::BlendSampleMask::set( int value )
	{
		ID3D11BlendState* oldState = 0;
		float oldFactor[4];
		int oldMask = 0;
		deviceContext->OMGetBlendState( &oldState, oldFactor, reinterpret_cast<UINT*>( &oldMask ) );
	
		deviceContext->OMSetBlendState( oldState, oldFactor, value );
	}
	
	int OutputMergerWrapper::BlendSampleMask::get()
	{
		ID3D11BlendState* oldState = 0;
		float oldFactor[4];
		int oldMask = 0;
		deviceContext->OMGetBlendState( &oldState, oldFactor, reinterpret_cast<UINT*>( &oldMask ) );
		
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
		
		deviceContext->OMSetRenderTargets( 1, nativeRTV, nativeDSV );
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
			deviceContext->OMSetRenderTargets( 0, 0, nativeDSV );
		}
		else 
		{
			for( int i = 0; i < renderTargets->Length; ++i )
				nativeRTVs[ i ] = renderTargets[ i ] == nullptr ? 0 : static_cast<ID3D11RenderTargetView*>( renderTargets[ i ]->InternalPointer );
			deviceContext->OMSetRenderTargets( renderTargets->Length, nativeRTVs, nativeDSV );
		}
	}
}
}
