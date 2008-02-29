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
#pragma once

#include <d3dx9.h>

#include "Resource.h"
#include "../DataStream.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
		public value class VertexBufferDescription
		{
		public:
			Format Format;
			ResourceType Type;
			Usage Usage;
			Pool Pool;
			int SizeInBytes;
			VertexFormat FVF;
		};

		public ref class VertexBuffer : public Resource
		{
			COMOBJECT( IDirect3DVertexBuffer9, VertexBuffer );
		
			VertexBufferDescription m_Description;
			
			void InitDescription();

		public:
			VertexBuffer( SlimDX::Direct3D9::Device^ device, int sizeBytes, SlimDX::Direct3D9::Usage usage, VertexFormat format, SlimDX::Direct3D9::Pool pool );
			virtual ~VertexBuffer() { }
			static VertexBuffer^ FromPointer( System::IntPtr buffer );

			DataStream^ Lock( int offset, int size, LockFlags flags );
			Result Unlock();

			property VertexBufferDescription Description
			{
				VertexBufferDescription get() { return m_Description; }
			private:
				void set( VertexBufferDescription value ) { m_Description = value; }
			}
		};
	}
}
