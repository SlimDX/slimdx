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
#pragma once

using namespace System;

#include "Enums.h"
#include "InputElement.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Buffer;
		ref class InputAssemblerWrapper;
		ref class InputLayout;
		ref class OutputMergerWrapper;
		ref class RasterizerWrapper;
		ref class RenderTargetView;
		ref class Resource;
		ref class StreamOutputWrapper;
		ref class SwapChain;
		value class RenderTargetViewDescription;
		value class SwapChainDescription;

		public ref class Device
		{
			IDXGIFactory* m_Factory;
			ID3D10Device* m_Device;
		
		protected:
			void Destruct();

		internal:
			property IDXGIFactory* FactoryPointer
			{
				IDXGIFactory* get() { return m_Factory; }
			}

			property ID3D10Device* DevicePointer
			{
				ID3D10Device* get() { return m_Device; }
			}
		
		public:
			initonly InputAssemblerWrapper^ InputAssembler;
			initonly RasterizerWrapper^ Rasterizer;
			initonly OutputMergerWrapper^ OutputMerger;
			initonly StreamOutputWrapper^ StreamOutput;
			
			Device( DriverType driverType, DeviceCreationFlags flags );

			~Device();
			!Device();
			
			void ClearState();
			
			void Draw( int vertexCount, int startVertexLocation );
			void DrawAuto();
			void DrawIndexed( int indexCount, int startIndexLocation, int baseVertexLocation );
			void DrawIndexedInstanced( int indexCountPerInstance, int instanceCount, int startIndexLocation, int baseVertexLocation, int startInstanceLocation );
			void DrawInstanced( int vertexCountPerInstance, int instanceCount, int startVertexLocation, int startInstanceLocation );
		
			void Flush();
		};
	}
};