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

//using namespace System;
//using namespace System::IO;

#include <d3dx9.h>

namespace SlimDX
{
	public ref class DataStream : public System::IO::Stream
	{
		private:
		char* m_Buffer;
		bool m_OwnsBuffer;
		ID3DXBuffer *m_ID3DXBuffer;
		
		System::Int64 m_Size;
		System::Int64 m_Position;
		
		initonly bool m_CanRead;
		initonly bool m_CanWrite;

	internal:
		DataStream( ID3DXBuffer *buffer );
		DataStream( void* buffer, System::Int64 sizeInBytes, bool canRead, bool canWrite, bool makeCopy );

		property char* RawPointer
		{
			char* get();
		}
	
		void TakeOwnership() { m_OwnsBuffer = true; }

		ID3DXBuffer* GetD3DBuffer();

	public:
		DataStream( System::Int64 sizeInBytes, bool canRead, bool canWrite );
		DataStream( System::IntPtr userBuffer, System::Int64 sizeInBytes, bool canRead, bool canWrite );
		
		~DataStream();
		!DataStream();
		
		virtual System::Int64 Seek( System::Int64 offset, System::IO::SeekOrigin origin ) override;

		generic<typename T> where T : value class
		void Write( T value );

		virtual void Write( array<System::Byte>^ buffer, int offset, int count ) override;

		generic<typename T> where T : value class
		void WriteRange( array<T>^ data, int startIndex, int count );

		generic<typename T> where T : value class
		void WriteRange( array<T>^ data ) { WriteRange( data, 0, 0 ); }
		
		void WriteRange( System::IntPtr source, System::Int64 count );

		generic<typename T> where T : value class
		T Read();

		virtual int Read( array<System::Byte>^ buffer, int offset, int count ) override;

		generic<typename T> where T : value class
		array<T>^ ReadRange( int count );

		virtual void Flush() override;

		virtual void SetLength( System::Int64 value ) override;

		property bool CanRead
		{
			virtual bool get() override { return m_CanRead; }
		}

		property bool CanSeek
		{
			virtual bool get() override { return true; }
		}

		property bool CanWrite
		{
			virtual bool get() override { return m_CanWrite; }
		}

		property System::Int64 Length
		{
			virtual System::Int64 get() override;
		}

		property System::Int64 Position
		{
			virtual System::Int64 get() override
			{
				return m_Position;
			}

			virtual void set( System::Int64 value ) override
			{
				Seek( value, System::IO::SeekOrigin::Begin );
			}
		}

		property System::IntPtr DataPointer
		{
			System::IntPtr get() { return System::IntPtr( m_Buffer ); }
		}
	};
}
