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

#include "Resource.h"
#include "../Direct3D/..\DataStream.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		public ref class VertexBuffer : public Resource
		{
		private:
			Format format;
			Usage usage;
			Pool pool;
			int sizeInBytes;
			VertexFormat fVF;

		internal:
			property IDirect3DVertexBuffer9* VbPointer
			{
				IDirect3DVertexBuffer9* get() { return static_cast<IDirect3DVertexBuffer9*>( m_Pointer ); }
			}

			VertexBuffer( IDirect3DVertexBuffer9* buffer );

		public:
			VertexBuffer( IntPtr buffer );
			VertexBuffer( Device^ device, int sizeBytes, SlimDX::Direct3D9::Usage usage, VertexFormat format, SlimDX::Direct3D9::Pool pool );
			
			DataStream^ Lock( int offset, int size, LockFlags flags );
			void Unlock();

			property SlimDX::Direct3D9::Format Format
            {
                SlimDX::Direct3D9::Format get() { return format; }
			private:
                void set( SlimDX::Direct3D9::Format value ) { format = value; }
            }

            property SlimDX::Direct3D9::Usage Usage
            {
                SlimDX::Direct3D9::Usage get() { return usage; }
			private:
                void set( SlimDX::Direct3D9::Usage value ) { usage = value; }
            }

            property SlimDX::Direct3D9::Pool Pool
            {
                SlimDX::Direct3D9::Pool get() { return pool; }
			private:
                void set( SlimDX::Direct3D9::Pool value ) { pool = value; }
            }

            property int SizeInBytes
            {
                int get() { return sizeInBytes; }
			private:
                void set( int value ) { sizeInBytes = value; }
            }

            property VertexFormat FVF
            {
                VertexFormat get() { return fVF; }
			private:
                void set( VertexFormat value ) { fVF = value; }
            }
		};
	}
}
