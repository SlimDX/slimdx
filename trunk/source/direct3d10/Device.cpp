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
#include <d3dx10.h>

#include "Direct3D10Exception.h"

#include "Buffer.h"
#include "Device.h"
#include "InputAssemblerWrapper.h"
#include "InputLayout.h"
#include "OutputMergerWrapper.h"
#include "RasterizerWrapper.h"
#include "RenderTargetView.h"
#include "Resource.h"
#include "StreamOutputWrapper.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{
	Device::Device( ID3D10Device* pointer )
	{
		Construct( pointer );
		
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
	
	Device::Device( DeviceCreationFlags flags )
	{
		ID3D10Device* device = 0;
		Result::Record( D3D10CreateDevice( 0, D3D10_DRIVER_TYPE_HARDWARE, 0, static_cast<UINT>( flags ), D3D10_SDK_VERSION, &device ) );
		if( Result::Last.IsFailure )
			throw gcnew Direct3D10Exception( Result::Last.Code );
		
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
	
	void Device::ClearState()
	{
		InternalPointer->ClearState();
	}
	
	void Device::Draw( int vertexCount, int startVertexLocation )
	{
		InternalPointer->Draw( vertexCount, startVertexLocation );
	}
	
	void Device::DrawAuto()
	{
		InternalPointer->DrawAuto();
	}
	
	void Device::DrawIndexed( int indexCount, int startIndexLocation, int baseVertexLocation )
	{
		InternalPointer->DrawIndexed( indexCount, startIndexLocation, baseVertexLocation );
	}
	
	void Device::DrawIndexedInstanced( int indexCountPerInstance, int instanceCount, int startIndexLocation, int baseVertexLocation, int startInstanceLocation )
	{
		InternalPointer->DrawIndexedInstanced( indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation );
	}
	
	void Device::DrawInstanced( int vertexCountPerInstance, int instanceCount, int startVertexLocation, int startInstanceLocation )
	{
		InternalPointer->DrawInstanced( vertexCountPerInstance, instanceCount, startVertexLocation, startInstanceLocation );
	}
	
	void Device::Flush()
	{
		InternalPointer->Flush();
	}
}
}
