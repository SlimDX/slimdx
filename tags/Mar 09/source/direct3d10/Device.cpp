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
#include <vector>

#include "../DataBox.h"

#include "../dxgi/Adapter.h"

#include "Direct3D10Exception.h"

#include "Buffer.h"
#include "CounterCapabilities.h"
#include "CounterDescription.h"
#include "CounterMetadata.h"
#include "DepthStencilView.h"
#include "Device.h"
#include "InputAssemblerWrapper.h"
#include "InputLayout.h"
#include "OutputMergerWrapper.h"
#include "RasterizerWrapper.h"
#include "RenderTargetView.h"
#include "Resource.h"
#include "ResourceRegion.h"
#include "ShaderResourceView.h"
#include "StreamOutputWrapper.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{
	Device::Device( ID3D10Device* pointer, ComObject^ owner )
	{
		Construct( pointer, owner );
		
		m_InputAssembler = gcnew InputAssemblerWrapper( InternalPointer );
		m_OutputMerger = gcnew OutputMergerWrapper( InternalPointer );
		m_StreamOutput = gcnew StreamOutputWrapper( InternalPointer );
		m_Rasterizer = gcnew RasterizerWrapper( InternalPointer );
	}
	
	Device::Device( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
		
		m_InputAssembler = gcnew InputAssemblerWrapper( InternalPointer );
		m_OutputMerger = gcnew OutputMergerWrapper( InternalPointer );
		m_StreamOutput = gcnew StreamOutputWrapper( InternalPointer );
		m_Rasterizer = gcnew RasterizerWrapper( InternalPointer );
	}
	
	Device^ Device::FromPointer( ID3D10Device* pointer, ComObject^ owner, ComObjectFlags flags )
	{
		return ComObject::ConstructFromPointer<Device,ID3D10Device>( pointer, owner, flags );
	}
	
	Device^ Device::FromPointer( IntPtr pointer )
	{
		return ComObject::ConstructFromUserPointer<Device>( pointer );
	}
	
	Device::Device( DeviceCreationFlags flags )
	{
		ID3D10Device* device = 0;
		RECORD_D3D10( D3D10CreateDevice( 0, D3D10_DRIVER_TYPE_HARDWARE, 0, static_cast<UINT>( flags ), D3D10_SDK_VERSION, &device ) );
		if( Result::Last.IsFailure )
			throw gcnew Direct3D10Exception( Result::Last );
		
		Construct( device );
		
		m_InputAssembler = gcnew InputAssemblerWrapper( InternalPointer );
		m_OutputMerger = gcnew OutputMergerWrapper( InternalPointer );
		m_StreamOutput = gcnew StreamOutputWrapper( InternalPointer );
		m_Rasterizer = gcnew RasterizerWrapper( InternalPointer );
	}
	
	Device::Device( DriverType driverType, DeviceCreationFlags flags )
	{
		ID3D10Device* device = 0;
		RECORD_D3D10( D3D10CreateDevice( 0, static_cast<D3D10_DRIVER_TYPE>( driverType ), 0, static_cast<UINT>( flags ), D3D10_SDK_VERSION, &device ) );
		if( Result::Last.IsFailure )
			throw gcnew Direct3D10Exception( Result::Last );
		
		Construct( device );
		
		m_InputAssembler = gcnew InputAssemblerWrapper( InternalPointer );
		m_OutputMerger = gcnew OutputMergerWrapper( InternalPointer );
		m_StreamOutput = gcnew StreamOutputWrapper( InternalPointer );
		m_Rasterizer = gcnew RasterizerWrapper( InternalPointer );
	}
	
	Device::Device( DXGI::Adapter^ adapter, DriverType driverType, DeviceCreationFlags flags )
	{
		IDXGIAdapter* nativeAdapter = adapter == nullptr ? 0 : adapter->InternalPointer;
		ID3D10Device* device = 0;
		RECORD_D3D10( D3D10CreateDevice( nativeAdapter, static_cast<D3D10_DRIVER_TYPE>( driverType ), 0, static_cast<UINT>( flags ), D3D10_SDK_VERSION, &device ) );
		if( Result::Last.IsFailure )
			throw gcnew Direct3D10Exception( Result::Last );
		
		Construct( device );
		
		m_InputAssembler = gcnew InputAssemblerWrapper( InternalPointer );
		m_OutputMerger = gcnew OutputMergerWrapper( InternalPointer );
		m_StreamOutput = gcnew StreamOutputWrapper( InternalPointer );
		m_Rasterizer = gcnew RasterizerWrapper( InternalPointer );
	}

	InputAssemblerWrapper^ Device::InputAssembler::get()
	{
		return m_InputAssembler;
	}
	
	OutputMergerWrapper^ Device::OutputMerger::get()
	{
		return m_OutputMerger;
	}
	
	StreamOutputWrapper^ Device::StreamOutput::get()
	{
		return m_StreamOutput;
	}
	
	RasterizerWrapper^ Device::Rasterizer::get()
	{
		return m_Rasterizer;
	}
	
	DeviceCreationFlags Device::CreationFlags::get()
	{
		return static_cast<DeviceCreationFlags>( InternalPointer->GetCreationFlags() );
	}
	
	CounterCapabilities Device::GetCounterCapabilities()
	{
		D3D10_COUNTER_INFO info;
		InternalPointer->CheckCounterInfo( &info );
		return CounterCapabilities( info );
	}
	
	CounterMetadata Device::GetCounterMetadata( CounterDescription description )
	{
		D3D10_COUNTER_DESC nativeDescription = description.CreateNativeVersion();
		D3D10_COUNTER_TYPE type;
		UINT count = 0;
		UINT nameLength = 0;
		UINT unitsLength = 0;
		UINT descriptionLength = 0;
		if( RECORD_D3D10( InternalPointer->CheckCounter( &nativeDescription, &type, &count, 0, &nameLength, 0, &unitsLength, 0, &descriptionLength ) ).IsFailure )
			return CounterMetadata();
		
		std::vector<char> nameChars( nameLength );
		std::vector<char> unitsChars( unitsLength );
		std::vector<char> descriptionChars( descriptionLength );
		if( RECORD_D3D10( InternalPointer->CheckCounter( &nativeDescription, &type, &count, &nameChars[ 0 ], &nameLength, &unitsChars[ 0 ], &unitsLength, &descriptionChars[ 0 ], &descriptionLength ) ).IsFailure )
			return CounterMetadata();
			
		return CounterMetadata( static_cast<CounterType>( type ), count, gcnew String( &nameChars[ 0 ] ), gcnew String( &unitsChars[ 0 ] ), gcnew String( &descriptionChars[ 0 ] ) );	
	}
	
	FormatSupport Device::CheckFormatSupport( DXGI::Format format )
	{
		UINT support = 0;
		InternalPointer->CheckFormatSupport( static_cast<DXGI_FORMAT>( format ), &support );
		return static_cast<FormatSupport>( support );
	}
	
	int Device::CheckMultisampleQualityLevels( DXGI::Format format, int sampleCount )
	{
		UINT result = 0;
		InternalPointer->CheckMultisampleQualityLevels( static_cast<DXGI_FORMAT>( format ), sampleCount, &result );
		return result;
	}
	
	void Device::ClearDepthStencilView( DepthStencilView^ view, DepthStencilClearFlags flags, float depth, Byte stencil )
	{
		InternalPointer->ClearDepthStencilView( view->InternalPointer, static_cast<UINT>( flags ), depth, stencil );
	}
	
	void Device::ClearRenderTargetView( RenderTargetView^ view, Color4 color )
	{
		const float nativeColor[] = { color.Red, color.Green, color.Blue, color.Alpha };
		InternalPointer->ClearRenderTargetView( view->InternalPointer, nativeColor );
	}
	
	void Device::ClearState()
	{
		InternalPointer->ClearState();
	}
	
	Result Device::ClearAllObjects()
	{
		return RECORD_D3D10( D3DX10UnsetAllDeviceObjects( InternalPointer ) );
	}
	
	void Device::CopyResource( Resource^ source, Resource^ destination )
	{
		InternalPointer->CopyResource( destination->InternalPointer, source->InternalPointer );
	}
	
	void Device::CopySubresourceRegion( Resource^ source, int sourceSubresource, ResourceRegion region, Resource^ destination, int destinationSubresource, int x, int y, int z )
	{
		D3D10_BOX nativeRegion = region.CreateNativeVersion();
		InternalPointer->CopySubresourceRegion( destination->InternalPointer, destinationSubresource, x, y, z, source->InternalPointer, sourceSubresource, &nativeRegion );
	}
	
	void Device::ResolveSubresource( Resource^ source, int sourceSubresource, Resource^ destination, int destinationSubresource, DXGI::Format format )
	{
		InternalPointer->ResolveSubresource( destination->InternalPointer, destinationSubresource, source->InternalPointer, sourceSubresource, static_cast<DXGI_FORMAT>( format ) );
	}
	
	void Device::UpdateSubresource( DataBox^ source, Resource^ resource, int subresource, ResourceRegion region ) 
	{
		D3D10_BOX nativeRegion = region.CreateNativeVersion();
		InternalPointer->UpdateSubresource( resource->InternalPointer, static_cast<UINT>( subresource), &nativeRegion, source->Data->RawPointer, source->RowPitch,source->SlicePitch);
	}

	void Device::Draw( int vertexCount, int startVertexLocation )
	{
		InternalPointer->Draw( vertexCount, startVertexLocation );
	}
	
	void Device::DrawInstanced( int vertexCountPerInstance, int instanceCount, int startVertexLocation, int startInstanceLocation )
	{
		InternalPointer->DrawInstanced( vertexCountPerInstance, instanceCount, startVertexLocation, startInstanceLocation );
	}
	
	void Device::DrawIndexed( int indexCount, int startIndexLocation, int baseVertexLocation )
	{
		InternalPointer->DrawIndexed( indexCount, startIndexLocation, baseVertexLocation );
	}
	
	void Device::DrawIndexedInstanced( int indexCountPerInstance, int instanceCount, int startIndexLocation, int baseVertexLocation, int startInstanceLocation )
	{
		InternalPointer->DrawIndexedInstanced( indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation );
	}
	
	void Device::DrawAuto()
	{
		InternalPointer->DrawAuto();
	}
	
	void Device::Flush()
	{
		InternalPointer->Flush();
	}
	
	void Device::GenerateMips( ShaderResourceView^ view )
	{
		InternalPointer->GenerateMips( view->InternalPointer );
	}
	
	Result Device::CreateWithSwapChain( DXGI::Adapter^ adapter, DriverType driverType, DeviceCreationFlags flags, DXGI::SwapChainDescription swapChainDescription, [Out] Device^ %device, [Out] DXGI::SwapChain^ %swapChain )
	{
		IDXGIAdapter* nativeAdapter = adapter == nullptr ? 0 : adapter->InternalPointer;
		ID3D10Device* resultDevice = 0;
		IDXGISwapChain* resultSwapChain = 0;
		DXGI_SWAP_CHAIN_DESC nativeDescription = swapChainDescription.CreateNativeVersion();
		
		if( RECORD_D3D10( D3D10CreateDeviceAndSwapChain( nativeAdapter, static_cast<D3D10_DRIVER_TYPE>( driverType ), 0, static_cast<UINT>( flags ), D3D10_SDK_VERSION, &nativeDescription, &resultSwapChain, &resultDevice ) ).IsSuccess )
		{
			device = FromPointer( resultDevice );
			swapChain = DXGI::SwapChain::FromPointer( resultSwapChain );
		}
		else {
			device = nullptr;
			swapChain = nullptr;
		}
		
		return Result::Last;
	}
}
}
