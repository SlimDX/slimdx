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

#include "DepthStencilState.h"
#include "Device.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	DepthStencilState::DepthStencilState( ID3D10DepthStencilState* state )
	{
		if( state == NULL )
			throw gcnew ArgumentNullException( "state" );
		
		D3D10_DEPTH_STENCIL_DESC desc;
		state->GetDesc( &desc );
			
		m_EnableDepth = desc.DepthEnable ? true : false;
		m_DepthWriteMask = ( SlimDX::Direct3D10::DepthWriteMask ) desc.DepthWriteMask;
		m_DepthComparison = ( Comparison ) desc.DepthFunc;
		m_EnableStencil = desc.StencilEnable ? true : false;
		m_StencilReadMask = desc.StencilReadMask;
		m_StencilWriteMask = desc.StencilWriteMask;
		m_FrontStencilComparison = ( Comparison ) desc.FrontFace.StencilFunc;
		m_FrontStencilFailureOp = ( StencilOperation ) desc.FrontFace.StencilFailOp;
		m_FrontStencilDepthFailureOp = ( StencilOperation ) desc.FrontFace.StencilDepthFailOp;
		m_FrontStencilPassOp = ( StencilOperation ) desc.FrontFace.StencilPassOp;
		m_BackStencilComparison = ( Comparison ) desc.BackFace.StencilFunc;
		m_BackStencilFailureOp = ( StencilOperation ) desc.BackFace.StencilFailOp;
		m_BackStencilDepthFailureOp = ( StencilOperation ) desc.BackFace.StencilDepthFailOp;
		m_BackStencilPassOp = ( StencilOperation ) desc.BackFace.StencilPassOp;
		
		m_Pointer = state;
	}
	
	DepthStencilState::DepthStencilState( Device^ device, bool enableDepth, SlimDX::Direct3D10::DepthWriteMask depthWriteMask, Comparison depthComparison,
		bool enableStencil, Byte stencilReadMask, Byte stencilWriteMask,
		Comparison frontComparison, StencilOperation frontFailOp, StencilOperation frontDepthFailOp, StencilOperation frontPassOp,
		Comparison backComparison, StencilOperation backFailOp, StencilOperation backDepthFailOp, StencilOperation backPassOp)
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
			
		D3D10_DEPTH_STENCIL_DESC desc;
		ZeroMemory( &desc, sizeof( desc ) );
		
		desc.DepthEnable = enableDepth;
		desc.DepthWriteMask = ( D3D10_DEPTH_WRITE_MASK ) depthWriteMask;
		desc.DepthFunc = ( D3D10_COMPARISON_FUNC ) depthComparison;
		desc.StencilEnable = enableStencil;
		desc.StencilReadMask = stencilReadMask;
		desc.StencilWriteMask = stencilWriteMask;
		desc.FrontFace.StencilFunc = ( D3D10_COMPARISON_FUNC ) frontComparison;
		desc.FrontFace.StencilFailOp = ( D3D10_STENCIL_OP ) frontFailOp;
		desc.FrontFace.StencilDepthFailOp = ( D3D10_STENCIL_OP ) frontDepthFailOp;
		desc.FrontFace.StencilPassOp = ( D3D10_STENCIL_OP ) frontPassOp;
		desc.BackFace.StencilFunc = ( D3D10_COMPARISON_FUNC ) backComparison;
		desc.BackFace.StencilFailOp = ( D3D10_STENCIL_OP ) backFailOp;
		desc.BackFace.StencilDepthFailOp = ( D3D10_STENCIL_OP ) backDepthFailOp;
		desc.BackFace.StencilPassOp = ( D3D10_STENCIL_OP ) backPassOp;
		
		m_EnableDepth = desc.DepthEnable ? true : false;
		m_DepthWriteMask = ( SlimDX::Direct3D10::DepthWriteMask ) desc.DepthWriteMask;
		m_DepthComparison = ( Comparison ) desc.DepthFunc;
		m_EnableStencil = desc.StencilEnable ? true : false;
		m_StencilReadMask = desc.StencilReadMask;
		m_StencilWriteMask = desc.StencilWriteMask;
		m_FrontStencilComparison = ( Comparison ) desc.FrontFace.StencilFunc;
		m_FrontStencilFailureOp = ( StencilOperation ) desc.FrontFace.StencilFailOp;
		m_FrontStencilDepthFailureOp = ( StencilOperation ) desc.FrontFace.StencilDepthFailOp;
		m_FrontStencilPassOp = ( StencilOperation ) desc.FrontFace.StencilPassOp;
		m_BackStencilComparison = ( Comparison ) desc.BackFace.StencilFunc;
		m_BackStencilFailureOp = ( StencilOperation ) desc.BackFace.StencilFailOp;
		m_BackStencilDepthFailureOp = ( StencilOperation ) desc.BackFace.StencilDepthFailOp;
		m_BackStencilPassOp = ( StencilOperation ) desc.BackFace.StencilPassOp;
		
		ID3D10DepthStencilState* state = 0;
		HRESULT hr = device->DevicePointer->CreateDepthStencilState( &desc, &state );
		GraphicsException::CheckHResult( hr );
		
		m_Pointer = state;
	}
}
}
