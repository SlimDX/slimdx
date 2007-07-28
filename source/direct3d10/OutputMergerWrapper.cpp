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

#include <d3d10.h>
#include <d3dx10.h>

#include "GraphicsException.h"

#include "OutputMergerWrapper.h"
#include "DepthStencilState.h"
#include "DepthStencilView.h"
#include "RenderTargetView.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	OutputMergerWrapper::OutputMergerWrapper( ID3D10Device* device )
	{
		if( device == NULL )
			throw gcnew ArgumentNullException( "device" );
		m_Device = device;
	}
	
	void OutputMergerWrapper::DepthStencilState::set( SlimDX::Direct3D10::DepthStencilState^ value )
	{
		if( value == nullptr )
			m_Device->OMSetDepthStencilState( NULL, 0 ); //@TODO: Confirm that this is kosher.
		else
			m_Device->OMSetDepthStencilState( value->InternalPointer, 0 );
	}
	
	SlimDX::Direct3D10::DepthStencilState^ OutputMergerWrapper::DepthStencilState::get()
	{
		ID3D10DepthStencilState* state = 0;
		int stencilRef = 0;
		m_Device->OMGetDepthStencilState( &state, (UINT*) &stencilRef );
		return gcnew SlimDX::Direct3D10::DepthStencilState( state );
	}
	
	void OutputMergerWrapper::SetTargets( RenderTargetView^ renderTargetView )
	{
		SetTargets( nullptr, renderTargetView );
	}
	
	void OutputMergerWrapper::SetTargets( DepthStencilView^ depthStencilView, RenderTargetView^ renderTargetView )
	{
		ID3D10DepthStencilView *nativeDSV = depthStencilView == nullptr ? NULL : (ID3D10DepthStencilView*) depthStencilView->InternalPointer;
		ID3D10RenderTargetView *nativeRTV[] = { (ID3D10RenderTargetView*) renderTargetView->InternalPointer };
		
		m_Device->OMSetRenderTargets( 1, nativeRTV, nativeDSV );
	}

	void OutputMergerWrapper::SetTargets( ... array<RenderTargetView^>^ renderTargets )
	{
		SetTargets( nullptr, renderTargets );
	}

	void OutputMergerWrapper::SetTargets( DepthStencilView^ depthStencilView, ... array<RenderTargetView^>^ renderTargets )
	{
		ID3D10DepthStencilView *nativeDSV = depthStencilView == nullptr ? NULL : (ID3D10DepthStencilView*) depthStencilView->InternalPointer;
		ID3D10RenderTargetView* nativeRTVs[D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT];
		
		for( int i = 0; i < renderTargets->Length; ++i )
			nativeRTVs[ i ] = (ID3D10RenderTargetView*) renderTargets[ i ]->InternalPointer;
		m_Device->OMSetRenderTargets( renderTargets->Length, nativeRTVs, nativeDSV );
	}
}
}
