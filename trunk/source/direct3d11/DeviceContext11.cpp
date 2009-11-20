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
#include "stdafx.h"

#include "../DataStream.h"

#include "Direct3D11Exception.h"

#include "Buffer11.h"
#include "CommandList11.h"
#include "Asynchronous11.h"
#include "DeviceContext11.h"
#include "InputAssemblerWrapper11.h"
#include "OutputMergerWrapper11.h"
#include "StreamOutputWrapper11.h"
#include "RasterizerWrapper11.h"
#include "VertexShaderWrapper11.h"
#include "PixelShaderWrapper11.h"
#include "GeometryShaderWrapper11.h"
#include "DomainShaderWrapper11.h"
#include "HullShaderWrapper11.h"
#include "ComputeShaderWrapper11.h"
#include "DepthStencilView11.h"
#include "RenderTargetView11.h"
#include "UnorderedAccessView11.h"
#include "ShaderResourceView11.h"
#include "Resource11.h"
#include "ResourceRegion11.h"
#include "Predicate11.h"
#include "Device11.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{
	void DeviceContext::InitializeSubclasses()
	{
		inputAssembler = gcnew InputAssemblerWrapper( InternalPointer );
		outputMerger = gcnew OutputMergerWrapper( InternalPointer );
		streamOutput = gcnew StreamOutputWrapper( InternalPointer );
		rasterizer = gcnew RasterizerWrapper( InternalPointer );
		vertexShader = gcnew VertexShaderWrapper( InternalPointer );
		pixelShader = gcnew PixelShaderWrapper( InternalPointer );
		geometryShader = gcnew GeometryShaderWrapper( InternalPointer );
		domainShader = gcnew DomainShaderWrapper( InternalPointer );
		hullShader = gcnew HullShaderWrapper( InternalPointer );
		computeShader = gcnew ComputeShaderWrapper( InternalPointer );
	}

	DeviceContext::DeviceContext( ID3D11DeviceContext* pointer, ComObject^ owner )
	{
		Construct( pointer, owner );
		InitializeSubclasses();
	}
	
	DeviceContext::DeviceContext( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
		InitializeSubclasses();
	}
	
	DeviceContext^ DeviceContext::FromPointer( ID3D11DeviceContext* pointer, ComObject^ owner, ComObjectFlags flags )
	{
		return ConstructFromPointer<DeviceContext,ID3D11DeviceContext>( pointer, owner, flags );
	}
	
	DeviceContext^ DeviceContext::FromPointer( IntPtr pointer )
	{
		return ConstructFromUserPointer<DeviceContext>( pointer );
	}

	DeviceContext::DeviceContext( SlimDX::Direct3D11::Device^ device )
	{
		ID3D11DeviceContext* context;

		HRESULT hr = device->InternalPointer->CreateDeferredContext( 0, &context );
		if( RECORD_D3D11( hr ).IsFailure )
			throw gcnew Direct3D11Exception( Result::Last );

		Construct( context );
		InitializeSubclasses();
	}

	void DeviceContext::Begin( Asynchronous^ data )
	{
		InternalPointer->Begin( data->InternalPointer );
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

	void DeviceContext::ClearUnorderedAccessView( UnorderedAccessView^ unorderedAccessView, array<int>^ values )
	{
		if( values->Length != 4 )
			throw gcnew ArgumentException( "Must supply exactly four clear values", "values" );

		const UINT nativeValues[] = { values[0], values[1], values[2], values[3] };
		InternalPointer->ClearUnorderedAccessViewUint( unorderedAccessView->InternalPointer, nativeValues );
	}

	void DeviceContext::ClearUnorderedAccessView( UnorderedAccessView^ unorderedAccessView, array<float>^ values )
	{
		if( values->Length != 4 )
			throw gcnew ArgumentException( "Must supply exactly four clear values", "values" );

		const FLOAT nativeValues[] = { values[0], values[1], values[2], values[3] };
		InternalPointer->ClearUnorderedAccessViewFloat( unorderedAccessView->InternalPointer, nativeValues );
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
	
	void DeviceContext::UpdateSubresource( DataBox^ source, Resource^ resource, int subresource ) 
	{
		InternalPointer->UpdateSubresource( resource->InternalPointer, static_cast<UINT>( subresource), 0, source->Data->PositionPointer, source->RowPitch,source->SlicePitch);
	}

	void DeviceContext::UpdateSubresource( DataBox^ source, Resource^ resource, int subresource, ResourceRegion region ) 
	{
		D3D11_BOX nativeRegion = region.CreateNativeVersion();
		InternalPointer->UpdateSubresource( resource->InternalPointer, static_cast<UINT>( subresource), &nativeRegion, source->Data->PositionPointer, source->RowPitch,source->SlicePitch);
	}

	void DeviceContext::Dispatch( int threadGroupCountX, int threadGroupCountY, int threadGroupCountZ )
	{
		InternalPointer->Dispatch( threadGroupCountX, threadGroupCountY, threadGroupCountZ );
	}
	
	void DeviceContext::DispatchIndirect( Buffer^ arguments, int alignedOffset )
	{
		InternalPointer->DispatchIndirect( arguments->InternalPointer, alignedOffset );
	}

	void DeviceContext::Draw( int vertexCount, int startVertexLocation )
	{
		InternalPointer->Draw( vertexCount, startVertexLocation );
	}
	
	void DeviceContext::DrawInstanced( int vertexCountPerInstance, int instanceCount, int startVertexLocation, int startInstanceLocation )
	{
		InternalPointer->DrawInstanced( vertexCountPerInstance, instanceCount, startVertexLocation, startInstanceLocation );
	}

	void DeviceContext::DrawInstancedIndirect( Buffer^ arguments, int alignedOffset )
	{
		InternalPointer->DrawInstancedIndirect( arguments->InternalPointer, alignedOffset );
	}
	
	void DeviceContext::DrawIndexed( int indexCount, int startIndexLocation, int baseVertexLocation )
	{
		InternalPointer->DrawIndexed( indexCount, startIndexLocation, baseVertexLocation );
	}
	
	void DeviceContext::DrawIndexedInstanced( int indexCountPerInstance, int instanceCount, int startIndexLocation, int baseVertexLocation, int startInstanceLocation )
	{
		InternalPointer->DrawIndexedInstanced( indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation );
	}

	void DeviceContext::DrawIndexedInstancedIndirect( Buffer^ arguments, int alignedOffset )
	{
		InternalPointer->DrawIndexedInstancedIndirect( arguments->InternalPointer, alignedOffset );
	}
	
	void DeviceContext::DrawAuto()
	{
		InternalPointer->DrawAuto();
	}

	void DeviceContext::End( Asynchronous^ data )
	{
		InternalPointer->End( data->InternalPointer );
	}

	void DeviceContext::ExecuteCommandList( CommandList^ commands, bool restoreState )
	{
		InternalPointer->ExecuteCommandList( commands->InternalPointer, restoreState );
	}

	CommandList^ DeviceContext::FinishCommandList( bool restoreState )
	{
		ID3D11CommandList* commands;

		HRESULT hr = InternalPointer->FinishCommandList( restoreState, &commands );
		if( RECORD_D3D11( hr ).IsFailure )
			return nullptr;

		return CommandList::FromPointer( commands );
	}
	
	void DeviceContext::Flush()
	{
		InternalPointer->Flush();
	}
	
	void DeviceContext::GenerateMips( ShaderResourceView^ view )
	{
		InternalPointer->GenerateMips( view->InternalPointer );
	}

	float DeviceContext::GetMinimumLod( Resource^ resource )
	{
		return InternalPointer->GetResourceMinLOD( resource->InternalPointer );
	}

	void DeviceContext::SetMinimumLod( Resource^ resource, float minimumLod )
	{
		InternalPointer->SetResourceMinLOD( resource->InternalPointer, minimumLod );
	}

	DataStream^ DeviceContext::GetData( Asynchronous^ data )
	{
		return GetData( data, AsynchronousFlags::None );
	}
	
	DataStream^ DeviceContext::GetData( Asynchronous^ data, AsynchronousFlags flags )
	{
		int size = data->InternalPointer->GetDataSize();
		DataStream^ result = gcnew DataStream( size, true, true );

		if( RECORD_D3D11( InternalPointer->GetData( data->InternalPointer, result->PositionPointer, size, static_cast<UINT>( flags ) ) ).IsFailure )
			return nullptr;
		return result;
	}

	void DeviceContext::GetPredication( [Out] Predicate^ %predicate, bool %predicateValue )
	{
		ID3D11Predicate* pointer;
		BOOL value;

		InternalPointer->GetPredication( &pointer, &value );

		predicate = Predicate::FromPointer( pointer );
		predicateValue = value > 0;
	}

	void DeviceContext::SetPredication( Predicate^ predicate, bool predicateValue )
	{
		InternalPointer->SetPredication( predicate->InternalPointer, predicateValue );
	}

	DataBox^ DeviceContext::MapSubresource( Resource^ resource, int subresource, int sizeInBytes, MapMode mode, MapFlags flags )
	{
		D3D11_MAPPED_SUBRESOURCE mapped;
		HRESULT hr = InternalPointer->Map( resource->InternalPointer, subresource, static_cast<D3D11_MAP>( mode ), static_cast<UINT>( flags ), &mapped );
		if( RECORD_D3D11( hr ).IsFailure )
			return nullptr;

		DataBox^ box = gcnew DataBox( mapped.RowPitch, mapped.DepthPitch, gcnew DataStream( mapped.pData, sizeInBytes, true, true, false ) );
		return box;
	}

	void DeviceContext::UnmapSubresource( Resource^ resource, int subresource )
	{
		InternalPointer->Unmap( resource->InternalPointer, subresource );
	}

	DeviceContextType DeviceContext::Type::get()
	{
		return static_cast<DeviceContextType>( InternalPointer->GetType() );
	}

	InputAssemblerWrapper^ DeviceContext::InputAssembler::get()
	{
		return inputAssembler;
	}
	
	OutputMergerWrapper^ DeviceContext::OutputMerger::get()
	{
		return outputMerger;
	}
	
	StreamOutputWrapper^ DeviceContext::StreamOutput::get()
	{
		return streamOutput;
	}
	
	RasterizerWrapper^ DeviceContext::Rasterizer::get()
	{
		return rasterizer;
	}

	VertexShaderWrapper^ DeviceContext::VertexShader::get()
	{
		return vertexShader;
	}

	PixelShaderWrapper^ DeviceContext::PixelShader::get()
	{
		return pixelShader;
	}

	GeometryShaderWrapper^ DeviceContext::GeometryShader::get()
	{
		return geometryShader;
	}

	DomainShaderWrapper^ DeviceContext::DomainShader::get()
	{
		return domainShader;
	}

	HullShaderWrapper^ DeviceContext::HullShader::get()
	{
		return hullShader;
	}

	ComputeShaderWrapper^ DeviceContext::ComputeShader::get()
	{
		return computeShader;
	}
}
}