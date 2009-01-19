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
#include <vector>

#include "Direct3D11Exception.h"

#include "Buffer.h"
#include "CommandList.h"
#include "CounterCapabilities.h"
#include "CounterDescription.h"
#include "CounterMetadata.h"
#include "DepthStencilView.h"
#include "DeviceContext.h"
#include "InputAssemblerWrapper.h"
#include "InputLayout.h"
#include "OutputMergerWrapper.h"
#include "PixelShader.h"
#include "RasterizerWrapper.h"
#include "RenderTargetView.h"
#include "Resource.h"
#include "ResourceRegion.h"
#include "ShaderResourceView.h"
#include "StreamOutputWrapper.h"
#include "VertexShader.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{
	DeviceContext::DeviceContext( ID3D11DeviceContext* pointer )
	{
		Construct( pointer );
		
		m_InputAssembler = gcnew InputAssemblerWrapper( InternalPointer );
		m_OutputMerger = gcnew OutputMergerWrapper( InternalPointer );
		m_StreamOutput = gcnew StreamOutputWrapper( InternalPointer );
		m_Rasterizer = gcnew RasterizerWrapper( InternalPointer );
	}
	
	DeviceContext::DeviceContext( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
		
		m_InputAssembler = gcnew InputAssemblerWrapper( InternalPointer );
		m_OutputMerger = gcnew OutputMergerWrapper( InternalPointer );
		m_StreamOutput = gcnew StreamOutputWrapper( InternalPointer );
		m_Rasterizer = gcnew RasterizerWrapper( InternalPointer );
	}
	
	DeviceContext^ DeviceContext::FromPointer( ID3D11DeviceContext* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		DeviceContext^ tableEntry = safe_cast<DeviceContext^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew DeviceContext( pointer );
	}

	DeviceContext^ DeviceContext::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		DeviceContext^ tableEntry = safe_cast<DeviceContext^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew DeviceContext( pointer );
	}

	InputAssemblerWrapper^ DeviceContext::InputAssembler::get()
	{
		return m_InputAssembler;
	}
	
	OutputMergerWrapper^ DeviceContext::OutputMerger::get()
	{
		return m_OutputMerger;
	}
	
	StreamOutputWrapper^ DeviceContext::StreamOutput::get()
	{
		return m_StreamOutput;
	}
	
	RasterizerWrapper^ DeviceContext::Rasterizer::get()
	{
		return m_Rasterizer;
	}
	
	void DeviceContext::ClearDepthStencilView( DepthStencilView^ view, DepthStencilClearFlags flags, float depth, Byte stencil )
	{
		InternalPointer->ClearDepthStencilView( view->InternalPointer, static_cast<UINT>( flags ), depth, stencil );
	}
	
	void DeviceContext::ClearRenderTargetView( RenderTargetView^ view, Color4 color )
	{
		const float nativeColor[] = { color.Red, color.Green, color.Blue, color.Alpha };
		InternalPointer->ClearRenderTargetView( view->InternalPointer, nativeColor );
	}
	
	void DeviceContext::ClearState()
	{
		InternalPointer->ClearState();
	}
	
	Result DeviceContext::ClearAllObjects()
	{
		return RECORD_D3D11( D3DX11UnsetAllDeviceObjects( InternalPointer ) );
	}
	
	void DeviceContext::CopyResource( Resource^ source, Resource^ destination )
	{
		InternalPointer->CopyResource( destination->InternalPointer, source->InternalPointer );
	}
	
	void DeviceContext::CopySubresourceRegion( Resource^ source, int sourceSubresource, ResourceRegion region, Resource^ destination, int destinationSubresource, int x, int y, int z )
	{
		D3D11_BOX nativeRegion = region.CreateNativeVersion();
		InternalPointer->CopySubresourceRegion( destination->InternalPointer, destinationSubresource, x, y, z, source->InternalPointer, sourceSubresource, &nativeRegion );
	}
	
	void DeviceContext::ResolveSubresource( Resource^ source, int sourceSubresource, Resource^ destination, int destinationSubresource, DXGI::Format format )
	{
		InternalPointer->ResolveSubresource( destination->InternalPointer, destinationSubresource, source->InternalPointer, sourceSubresource, static_cast<DXGI_FORMAT>( format ) );
	}
	
	void DeviceContext::UpdateSubresource( DataBox^ source, Resource^ resource, int subresource, ResourceRegion region ) 
	{
		D3D11_BOX nativeRegion = region.CreateNativeVersion();
		InternalPointer->UpdateSubresource( resource->InternalPointer, static_cast<UINT>( subresource), &nativeRegion, source->Data->RawPointer, source->RowPitch,source->SlicePitch);
	}

	void DeviceContext::Draw( int vertexCount, int startVertexLocation )
	{
		InternalPointer->Draw( vertexCount, startVertexLocation );
	}
	
	void DeviceContext::DrawInstanced( int vertexCountPerInstance, int instanceCount, int startVertexLocation, int startInstanceLocation )
	{
		InternalPointer->DrawInstanced( vertexCountPerInstance, instanceCount, startVertexLocation, startInstanceLocation );
	}
	
	void DeviceContext::DrawIndexed( int indexCount, int startIndexLocation, int baseVertexLocation )
	{
		InternalPointer->DrawIndexed( indexCount, startIndexLocation, baseVertexLocation );
	}
	
	void DeviceContext::DrawIndexedInstanced( int indexCountPerInstance, int instanceCount, int startIndexLocation, int baseVertexLocation, int startInstanceLocation )
	{
		InternalPointer->DrawIndexedInstanced( indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation );
	}
	
	void DeviceContext::DrawAuto()
	{
		InternalPointer->DrawAuto();
	}
	
	CommandList^ DeviceContext::FinishCommandList( bool resetState )
	{
		ID3D11CommandList *commandList;
		HRESULT hr = InternalPointer->FinishCommandList( resetState, &commandList );
		RECORD_D3D11(hr);
		if( Result::Last.IsFailure )
		{
			return nullptr;
		}

		return CommandList::FromPointer( commandList );
	}

	void DeviceContext::ExecuteCommandList( CommandList^ commandList, bool restoreState )
	{
		if (commandList == nullptr)
			throw gcnew ArgumentNullException( "commandList" );

		InternalPointer->ExecuteCommandList( commandList->InternalPointer, restoreState );
	}

	void DeviceContext::Flush()
	{
		InternalPointer->Flush();
	}
	
	void DeviceContext::GenerateMips( ShaderResourceView^ view )
	{
		InternalPointer->GenerateMips( view->InternalPointer );
	}
	
	void DeviceContext::SetVertexShader( VertexShader^ vertexShader )
	{
		InternalPointer->VSSetShader( vertexShader->InternalPointer, 0, 0 );
	}
	
	void DeviceContext::SetPixelShader( PixelShader^ pixelShader )
	{
		InternalPointer->PSSetShader( pixelShader->InternalPointer, 0, 0 );
	}
}
}
