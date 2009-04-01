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

#include <d3d10.h>
#include <d3dx10.h>

#include "Buffer.h"
#include "InputAssemblerWrapper.h"
#include "InputLayout.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{ 
	InputAssemblerWrapper::InputAssemblerWrapper( ID3D10Device* device )
	{
		if( device == 0 )
			throw gcnew ArgumentNullException( "device" );
		m_Device = device;
	}

	void InputAssemblerWrapper::SetInputLayout( InputLayout^ value)
	{
		if( value == nullptr )
		{
			m_Device->IASetInputLayout( 0 );
		} else
		{
			m_Device->IASetInputLayout( value->InternalPointer );
		}
	}
	
	void InputAssemblerWrapper::SetPrimitiveTopology( PrimitiveTopology value)
	{
		m_Device->IASetPrimitiveTopology( static_cast<D3D10_PRIMITIVE_TOPOLOGY>( value ) );
	}
	
	void InputAssemblerWrapper::SetIndexBuffer( Buffer^ indexBuffer, DXGI::Format format, int offset )
	{
		if( indexBuffer == nullptr )
		{
			m_Device->IASetIndexBuffer( 0, DXGI_FORMAT_UNKNOWN, 0 );
		}
		else
		{
			m_Device->IASetIndexBuffer( static_cast<ID3D10Buffer*>( indexBuffer->InternalPointer ), static_cast<DXGI_FORMAT>( format ), offset );
		}
	}
	
	void InputAssemblerWrapper::SetVertexBuffers( int slot, VertexBufferBinding vertexBufferBinding )
	{
		ID3D10Buffer* buffers[] = { static_cast<ID3D10Buffer*>( vertexBufferBinding.Buffer == nullptr ? 0 : vertexBufferBinding.Buffer->InternalPointer ) };
		UINT strides[] = { vertexBufferBinding.Stride };
		UINT offsets[] = { vertexBufferBinding.Offset };
		
		m_Device->IASetVertexBuffers( slot, 1, buffers, strides, offsets );
	}
	
	void InputAssemblerWrapper::SetVertexBuffers( int firstSlot, ... array<VertexBufferBinding>^ vertexBufferBinding )
	{
		ID3D10Buffer* buffers[D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
		UINT strides[D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
		UINT offsets[D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
		
		for( int i = 0; i < vertexBufferBinding->Length; ++i )
		{
			buffers[i] = vertexBufferBinding[ i ].Buffer == nullptr ? 0 : static_cast<ID3D10Buffer*>( vertexBufferBinding[ i ].Buffer->InternalPointer );
			strides[i] = vertexBufferBinding[ i ].Stride;
			offsets[i] = vertexBufferBinding[ i ].Offset;
		}
		
		m_Device->IASetVertexBuffers( firstSlot, vertexBufferBinding->Length, buffers, strides, offsets );
	}
}
}
