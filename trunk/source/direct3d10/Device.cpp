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

#include "Device.h"
#include "Buffer.h"
#include "InputAssemblerWrapper.h"
#include "InputLayout.h"
#include "OutputMergerWrapper.h"
#include "RasterizerWrapper.h"
#include "RenderTargetView.h"
#include "Resource.h"
#include "StreamOutputWrapper.h"
#include "SwapChain.h"
#include "SwapChainDescription.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	Device::Device( DriverType driverType, DeviceCreationFlags flags )
	{
		HRESULT hr;
		IDXGIFactory* factory;
		ID3D10Device* device;

		hr = CreateDXGIFactory( __uuidof( IDXGIFactory ), reinterpret_cast<void**>( &factory ) );
		GraphicsException::CheckHResult( hr );	
		m_Factory = factory;
		
		hr = D3D10CreateDevice( NULL, static_cast<D3D10_DRIVER_TYPE>( driverType ), NULL, static_cast<UINT>( flags ), D3D10_SDK_VERSION, &device );
		GraphicsException::CheckHResult( hr );
		m_Device = device;
		
		InputAssembler = gcnew InputAssemblerWrapper( m_Device );
		Rasterizer = gcnew RasterizerWrapper( m_Device );
		OutputMerger = gcnew OutputMergerWrapper( m_Device );
		StreamOutput = gcnew StreamOutputWrapper( m_Device );
	}

	Device::~Device()
	{
		Destruct();
	}

	Device::!Device()
	{
		Destruct();
	}

	void Device::Destruct()
	{
		m_Device->Release();
		m_Factory->Release();
	}
	
	void Device::ClearState()
	{
		m_Device->ClearState();
	}
	
	void Device::Draw( int vertexCount, int startVertexLocation )
	{
		m_Device->Draw( vertexCount, startVertexLocation );
	}
	
	void Device::DrawAuto()
	{
		m_Device->DrawAuto();
	}
	
	void Device::DrawIndexed( int indexCount, int startIndexLocation, int baseVertexLocation )
	{
		m_Device->DrawIndexed( indexCount, startIndexLocation, baseVertexLocation );
	}
	
	void Device::DrawIndexedInstanced( int indexCountPerInstance, int instanceCount, int startIndexLocation, int baseVertexLocation, int startInstanceLocation )
	{
		m_Device->DrawIndexedInstanced( indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation );
	}
	
	void Device::DrawInstanced( int vertexCountPerInstance, int instanceCount, int startVertexLocation, int startInstanceLocation )
	{
		m_Device->DrawInstanced( vertexCountPerInstance, instanceCount, startVertexLocation, startInstanceLocation );
	}
	
	void Device::Flush()
	{
		m_Device->Flush();
	}
}
}
