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

#include "../ComObject.h"

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

		public ref class Device : ComObject
		{
			COMOBJECT(ID3D10Device);
			
			InputAssemblerWrapper^ m_InputAssembler;
            OutputMergerWrapper^ m_OutputMerger;
            StreamOutputWrapper^ m_StreamOutput;
			RasterizerWrapper^ m_Rasterizer;

		internal:
			Device( ID3D10Device* pointer );
		
		public:
			property InputAssemblerWrapper^ InputAssembler
            {
                InputAssemblerWrapper^ get();
            }

            property OutputMergerWrapper^ OutputMerger
            {
                OutputMergerWrapper^ get();
            }

            property StreamOutputWrapper^ StreamOutput
            {
                StreamOutputWrapper^ get();
            }
            
            property RasterizerWrapper^ Rasterizer
            {
                RasterizerWrapper^ get();
            }
			
			Device( IntPtr pointer );
			Device( DeviceCreationFlags flags );

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