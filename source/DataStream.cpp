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
#include <d3d9.h>
#include <d3dx9.h>

#include "Utils.h"
#include "DataStream.h"

using namespace System::Runtime::InteropServices;

namespace SlimDX
{
	DataStream::DataStream( void* buffer, Int64 sizeInBytes, bool canRead, bool canWrite )
	{
		m_Buffer = (char*) buffer;
		m_Size = sizeInBytes;
		
		m_CanRead = canRead;
		m_CanWrite = canWrite;
	}
	
	DataStream::DataStream( Int64 sizeInBytes, bool canRead, bool canWrite )
	{
		m_Buffer = new char[ (int) sizeInBytes ];
		m_Size = sizeInBytes;
		
		m_OwnsBuffer = true;
		
		m_CanRead = canRead;
		m_CanWrite = canWrite;
	}

	DataStream::DataStream( IntPtr userBuffer, Int64 sizeInBytes, bool canRead, bool canWrite )
	{
		if( userBuffer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "userBuffer" );
		if( sizeInBytes < 1 )
			throw gcnew ArgumentOutOfRangeException( "sizeInBytes" );

		m_Buffer = (char*) userBuffer.ToPointer();
		m_Size = sizeInBytes;

		m_CanRead = canRead;
		m_CanWrite = canWrite;
	}

	DataStream::~DataStream()
	{
		DataStream::!DataStream();
	}
	
	DataStream::!DataStream()
	{
		if(m_OwnsBuffer)
		{
			delete[] m_Buffer;
			m_OwnsBuffer = false;
		}
	}

	char* DataStream::RawPointer::get()
	{
		return (m_Buffer);
	}

	Int64 DataStream::Seek( Int64 offset, SeekOrigin origin )
	{
		Int64 targetPosition;

		switch( origin )
		{
		case SeekOrigin::Begin:
			targetPosition = offset;
			break;

		case SeekOrigin::Current:
			targetPosition = m_Position + offset;
			break;

		case SeekOrigin::End:
			if(m_Size == 0)
				throw gcnew NotSupportedException( "Stream size unknown; SeekOrigin::End is not supported." );
			targetPosition = m_Size - offset;
			break;
		}

		if( targetPosition < 0 )
			throw gcnew InvalidOperationException("Cannot seek beyond the beginning of the stream.");
		if( targetPosition > m_Size && m_Size > 0)
			throw gcnew InvalidOperationException("Cannot seek beyond the end of the stream.");

		m_Position = targetPosition;
		return m_Position;
	}

	generic<typename T> where T : value class
	void DataStream::Write( T value )
	{
		if( !m_CanWrite )
			throw gcnew NotSupportedException();

		int size = Marshal::SizeOf( T::typeid );
		memcpy( m_Buffer + m_Position, &value, size );
		m_Position += size;
	}
	
	void DataStream::Write( array<Byte>^ buffer, int offset, int count )
	{
		if( !m_CanWrite )
			throw gcnew NotSupportedException();
		if( buffer == nullptr )
			throw gcnew ArgumentNullException( "buffer" );
		if( offset < 0 || offset >= buffer->Length )
			throw gcnew ArgumentOutOfRangeException( "offset" );
		if( count < 0 || offset + count > buffer->Length )
			throw gcnew ArgumentOutOfRangeException( "count" );

		pin_ptr<Byte> pinnedBuffer = &buffer[offset];
		memcpy( m_Buffer + m_Position, pinnedBuffer, count );

		m_Position += count;
	}

	generic<typename T> where T : value class
	void DataStream::WriteRange( array<T>^ data, int startIndex, int count )
	{
		if( !m_CanWrite )
			throw gcnew NotSupportedException();
			
		if( startIndex < 0 || startIndex > data->Length - 1 )
			throw gcnew ArgumentOutOfRangeException( "startIndex" );
		if( count < 0 )
			throw gcnew ArgumentOutOfRangeException( "count" );
		if( count == 0 )
			count = data->Length;
		if( startIndex + count > data->Length )
			throw gcnew InvalidOperationException();

		int size = count * Marshal::SizeOf( T::typeid );
		pin_ptr<T> pinnedData = &data[startIndex];
		memcpy( m_Buffer + m_Position, pinnedData, size );
		m_Position += size;
	}
	
	void DataStream::WriteRange( IntPtr source, Int64 byteCount )
	{
		if( !m_CanWrite )
			throw gcnew NotSupportedException();
			
		memcpy( m_Buffer + m_Position, source.ToPointer(), (size_t) byteCount );
		m_Position += byteCount;
	}
	
  generic<typename T> where T : value class
	T DataStream::Read()
	{
		if( !m_CanRead )
			throw gcnew NotSupportedException();

		T result;
		int size = Marshal::SizeOf( T::typeid );

		//TODO: This may be the wrong exception to throw.
		if( Length > 0 && Length - m_Position < size )
			throw gcnew ArgumentNullException();

		memcpy( &result, m_Buffer + m_Position, size );
		m_Position += size;
		return (result);
	}
	
	int DataStream::Read( array<Byte>^ buffer, int offset, int count )
	{
		if( !m_CanRead )
			throw gcnew NotSupportedException();
		if( buffer == nullptr )
			throw gcnew ArgumentNullException( "buffer" );
		if( offset < 0 || offset >= buffer->Length )
			throw gcnew ArgumentOutOfRangeException( "offset" );
		if( count < 0 || offset + count > buffer->Length )
			throw gcnew ArgumentOutOfRangeException( "count" );

		pin_ptr<Byte> pinnedBuffer = &buffer[offset];
		memcpy( pinnedBuffer, m_Buffer + m_Position, count );

		m_Position += count;
		return count;
	}
		
	generic<typename T> where T : value class
	array<T>^ DataStream::ReadRange( int count )
	{
		if( !m_CanRead )
			throw gcnew NotSupportedException();
			
		int elementSize = Marshal::SizeOf( T::typeid );
		int actualCount = count;
		if( Length > 0 )
			min( (Length - m_Position) / elementSize, count );
		array<T>^ result = gcnew array<T>( actualCount );

		pin_ptr<T> pinnedBuffer = &result[0];
		memcpy( pinnedBuffer, m_Buffer + m_Position, actualCount * elementSize );
		m_Position += actualCount * elementSize;
		return result;
	}
	
	void DataStream::Flush()
	{
		throw gcnew NotSupportedException("DataStream objects cannot be flushed.");
	}

	void DataStream::SetLength( Int64 value )
	{
		throw gcnew NotSupportedException("DataStream objects cannot be resized.");
	}
	
	Int64 DataStream::Length::get()
	{
		if( m_Size == 0)
			throw gcnew NotSupportedException("Stream size unknown; cannot query length.");
		return m_Size;
	}
}
