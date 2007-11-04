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

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Buffer;
		
		public value class VertexBufferBinding
		{
		private:
			Buffer^ buffer;
            int stride;
            int offset;

		public:
			property SlimDX::Direct3D10::Buffer^ Buffer
            {
                SlimDX::Direct3D10::Buffer^ get() { return buffer; }
                void set( SlimDX::Direct3D10::Buffer^ value ) { buffer = value; }
            }

            property int Stride
            {
                int get() { return stride; }
                void set( int value ) { stride = value; }
            }

            property int Offset
            {
                int get() { return offset; }
                void set( int value ) { offset = value; }
            }
			
			VertexBufferBinding( SlimDX::Direct3D10::Buffer^ buffer, int stride, int offset )
				: buffer( buffer ), stride (stride ), offset( offset )
			{
			}
		};
	}
};