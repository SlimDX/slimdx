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
#pragma once

#include "Enums11.h"
#include "VertexBufferBinding11.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace Direct3D11
	{
		ref class Buffer;
		ref class InputLayout;
		
		public ref class InputAssemblerWrapper
		{
		private:
			ID3D11DeviceContext* deviceContext;
			
		internal:
			InputAssemblerWrapper( ID3D11DeviceContext* device );
			
		public:
			property InputLayout^ InputLayout
			{
				Direct3D11::InputLayout^ get();
				void set( Direct3D11::InputLayout^ value );
			}

			property PrimitiveTopology PrimitiveTopology
			{
				Direct3D11::PrimitiveTopology get();
				void set( Direct3D11::PrimitiveTopology value );
			}
			
			void SetIndexBuffer( Buffer^ indexBuffer, DXGI::Format format, int offset );
			void GetIndexBuffer( [Out] Buffer^ %indexBuffer, [Out] DXGI::Format %format, [Out] int %offset );
			
			void SetVertexBuffers( int slot, VertexBufferBinding vertexBufferBinding );
			void SetVertexBuffers( int firstSlot, ... array<VertexBufferBinding>^ vertexBufferBindings );

			array<VertexBufferBinding>^ GetVertexBuffers( int firstSlot, int count );
		};
	}
};