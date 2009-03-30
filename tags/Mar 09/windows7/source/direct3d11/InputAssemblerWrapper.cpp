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

#include "Buffer.h"
#include "InputAssemblerWrapper.h"
#include "InputLayout.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{ 
	InputAssemblerWrapper::InputAssemblerWrapper( ID3D11DeviceContext* deviceContext )
	{
		if( deviceContext == 0 )
			throw gcnew ArgumentNullException( "deviceContext" );
		m_DeviceContext = deviceContext;
	}

	void InputAssemblerWrapper::SetInputLayout( InputLayout^ value)
	{
		if( value == nullptr )
		{
			m_DeviceContext->IASetInputLayout( 0 );
		} else
		{
			m_DeviceContext->IASetInputLayout( value->InternalPointer );
		}
	}
	
	void InputAssemblerWrapper::SetPrimitiveTopology( PrimitiveTopology value)
	{
		m_DeviceContext->IASetPrimitiveTopology( static_cast<D3D11_PRIMITIVE_TOPOLOGY>( value ) );
	}
	
	void InputAssemblerWrapper::SetIndexBuffer( Buffer^ indexBuffer, DXGI::Format format, int offset )
	{
		if( indexBuffer == nullptr )
		{
			m_DeviceContext->IASetIndexBuffer( 0, DXGI_FORMAT_UNKNOWN, 0 );
		}
		else
		{
			m_DeviceContext->IASetIndexBuffer( static_cast<ID3D11Buffer*>( indexBuffer->InternalPointer ), static_cast<DXGI_FORMAT>( format ), offset );
		}
	}
	
	void InputAssemblerWrapper::SetVertexBuffers( int slot, VertexBufferBinding vertexBufferBinding )
	{
		ID3D11Buffer* buffers[] = { static_cast<ID3D11Buffer*>( vertexBufferBinding.Buffer == nullptr ? 0 : vertexBufferBinding.Buffer->InternalPointer ) };
		UINT strides[] = { vertexBufferBinding.Stride };
		UINT offsets[] = { vertexBufferBinding.Offset };
		
		m_DeviceContext->IASetVertexBuffers( slot, 1, buffers, strides, offsets );
	}
	
	void InputAssemblerWrapper::SetVertexBuffers( int firstSlot, ... array<VertexBufferBinding>^ vertexBufferBinding )
	{
		ID3D11Buffer* buffers[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
		UINT strides[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
		UINT offsets[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
		
		for( int i = 0; i < vertexBufferBinding->Length; ++i )
		{
			buffers[i] = vertexBufferBinding[ i ].Buffer == nullptr ? 0 : static_cast<ID3D11Buffer*>( vertexBufferBinding[ i ].Buffer->InternalPointer );
			strides[i] = vertexBufferBinding[ i ].Stride;
			offsets[i] = vertexBufferBinding[ i ].Offset;
		}
		
		m_DeviceContext->IASetVertexBuffers( firstSlot, vertexBufferBinding->Length, buffers, strides, offsets );
	}
}
}
