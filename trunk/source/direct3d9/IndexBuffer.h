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

#include "Enums.h"
#include "Resource.h"
#include "../DataStream.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		public value class IndexBufferDescription : System::IEquatable<IndexBufferDescription>
		{
		public:
			property Format Format;
			property ResourceType Type;
			property Usage Usage;
			property Pool Pool;
			property int SizeInBytes;

			static bool operator == ( IndexBufferDescription left, IndexBufferDescription right );
			static bool operator != ( IndexBufferDescription left, IndexBufferDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( IndexBufferDescription other );
			static bool Equals( IndexBufferDescription% value1, IndexBufferDescription% value2 );
		};

		public ref class IndexBuffer : public Resource
		{
			COMOBJECT(IDirect3DIndexBuffer9, IndexBuffer);

			IndexBufferDescription description;
			void InitDescription();
			
		public:
			IndexBuffer( SlimDX::Direct3D9::Device^ device, int sizeBytes, Usage usage, Pool pool, bool sixteenBit );
			virtual ~IndexBuffer() { }
			static IndexBuffer^ FromPointer( System::IntPtr buffer );

			DataStream^ Lock( int offset, int size, LockFlags flags );
			Result Unlock();
			
			property IndexBufferDescription Description
			{
				IndexBufferDescription get() { return description; }
			}
		};
	}
}
