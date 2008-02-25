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

#include <d3d10.h>

#include "DepthStencilOperationDescription.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{ 
	DepthStencilOperationDescription::DepthStencilOperationDescription( const D3D10_DEPTH_STENCILOP_DESC& native )
	{
		m_StencilFailOp = static_cast<StencilOperation>( native.StencilFailOp );
		m_StencilDepthFailOp = static_cast<StencilOperation>( native.StencilDepthFailOp );
		m_StencilPassOp = static_cast<StencilOperation>( native.StencilPassOp );
		m_StencilFunc = static_cast<Direct3D10::Comparison>( native.StencilFunc );
	}
	
	D3D10_DEPTH_STENCILOP_DESC DepthStencilOperationDescription::CreateNativeVersion()
	{
		D3D10_DEPTH_STENCILOP_DESC native;
		native.StencilFailOp = static_cast<D3D10_STENCIL_OP>( m_StencilFailOp );
		native.StencilDepthFailOp = static_cast<D3D10_STENCIL_OP>( m_StencilDepthFailOp );
		native.StencilPassOp = static_cast<D3D10_STENCIL_OP>( m_StencilPassOp );
		native.StencilFunc = static_cast<D3D10_COMPARISON_FUNC>( m_StencilFunc );
		
		return native;
	}
	
	StencilOperation DepthStencilOperationDescription::FailOperation::get()
	{
		return m_StencilFailOp;
	}
	
	void DepthStencilOperationDescription::FailOperation::set( StencilOperation value )
	{
		m_StencilFailOp = value;
	}

	StencilOperation DepthStencilOperationDescription::DepthFailOperation::get()
	{
		return m_StencilDepthFailOp;
	}
	
	void DepthStencilOperationDescription::DepthFailOperation::set( StencilOperation value )
	{
		m_StencilDepthFailOp = value;
	}
	
	StencilOperation DepthStencilOperationDescription::PassOperation::get()
	{
		return m_StencilPassOp;
	}
	
	void DepthStencilOperationDescription::PassOperation::set( StencilOperation value )
	{
		m_StencilPassOp = value;
	}
	
	Direct3D10::Comparison DepthStencilOperationDescription::Comparison::get()
	{
		return m_StencilFunc;
	}
	
	void DepthStencilOperationDescription::Comparison::set( Direct3D10::Comparison value )
	{
		m_StencilFunc = value;
	}
}
}
