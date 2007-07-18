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

#include "RasterizerState.h"
#include "Device.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	RasterizerState::RasterizerState( ID3D10RasterizerState* state )
	{
		if( state == NULL )
			throw gcnew ArgumentNullException( "state" );
		
		D3D10_RASTERIZER_DESC desc;
		state->GetDesc( &desc );
		
		m_FillMode = ( SlimDX::Direct3D10::FillMode ) desc.FillMode;
		m_CullMode = ( SlimDX::Direct3D10::CullMode ) desc.CullMode;
		m_FrontCounterClockwise = desc.FrontCounterClockwise ? true : false;
		m_DepthBias = desc.DepthBias;
		m_DepthBiasClamp = desc.DepthBiasClamp;
		m_SlopeScaledDepthBias = desc.SlopeScaledDepthBias;
		m_EnableDepthClip = desc.DepthClipEnable ? true : false;
		m_EnableScissor = desc.ScissorEnable ? true : false;
		m_EnableMultisample = desc.MultisampleEnable ? true : false;
		m_EnableAntialiasedLine = desc.AntialiasedLineEnable ? true : false;
		
		m_Pointer = state;
	}
	
	RasterizerState::RasterizerState( Device^ device,SlimDX::Direct3D10::FillMode fillMode, SlimDX::Direct3D10::CullMode cullMode,
		bool frontIsCounterClockwise, int depthBias, float depthBiasClamp, float slopeScaledDepthBias,
		bool enableDepthClip, bool enableScissor, bool enableMultisample, bool enableAntialiasedLine )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
		
		D3D10_RASTERIZER_DESC desc;
		ZeroMemory( &desc, sizeof( desc ) );
		desc.FillMode = ( D3D10_FILL_MODE ) fillMode;
		desc.CullMode = ( D3D10_CULL_MODE ) cullMode;
		desc.FrontCounterClockwise = frontIsCounterClockwise;
		desc.DepthBias = depthBias;
		desc.DepthBiasClamp = depthBiasClamp;
		desc.SlopeScaledDepthBias = slopeScaledDepthBias;
		desc.DepthClipEnable = enableDepthClip;
		desc.ScissorEnable = enableScissor;
		desc.MultisampleEnable = enableMultisample;
		desc.AntialiasedLineEnable = enableAntialiasedLine;
		
		m_FillMode = ( SlimDX::Direct3D10::FillMode ) desc.FillMode;
		m_CullMode = ( SlimDX::Direct3D10::CullMode ) desc.CullMode;
		m_FrontCounterClockwise = desc.FrontCounterClockwise ? true : false;
		m_DepthBias = desc.DepthBias;
		m_DepthBiasClamp = desc.DepthBiasClamp;
		m_SlopeScaledDepthBias = desc.SlopeScaledDepthBias;
		m_EnableDepthClip = desc.DepthClipEnable ? true : false;
		m_EnableScissor = desc.ScissorEnable ? true : false;
		m_EnableMultisample = desc.MultisampleEnable ? true : false;
		m_EnableAntialiasedLine = desc.AntialiasedLineEnable ? true : false;
		
		ID3D10RasterizerState* state = 0;
		HRESULT hr = device->DevicePointer->CreateRasterizerState( &desc, &state );
		GraphicsException::CheckHResult( hr );
		
		m_Pointer = state;
	}
}
}
