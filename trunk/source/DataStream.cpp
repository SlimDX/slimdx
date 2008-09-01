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

#include <d3d9.h>
#include <d3dx9.h>
#include <stdexcept>

#include "DataStream.h"
#include "Utilities.h"
#include "InternalHelpers.h"

using namespace System;
using namespace System::IO;

namespace SlimDX
{
	DataStream::DataStream( ID3DXBuffer* buffer )
	{
		if( buffer->GetBufferSize() < 1 )
			throw gcnew ArgumentException( "Buffer size is less than 1." );

		m_Buffer = static_cast<char*>( buffer->GetBufferPointer() );
		m_Size = buffer->GetBufferSize();
		
		m_CanRead = true;
		m_CanWrite = true;
		
		m_ID3DXBuffer = buffer;
	}
	
	DataStream::DataStream( void* buffer, Int64 sizeInBytes, bool canRead, bool canWrite, bool makeCopy )
	{
		if( sizeInBytes < 1 )
			throw gcnew ArgumentOutOfRangeException( "sizeInBytes" );
	
		if( makeCopy )
		{
			// Manual Allocation: this is fine
			m_Buffer = new char[static_cast<size_t>( sizeInBytes )];
			memcpy( m_Buffer, buffer, static_cast<size_t>( sizeInBytes ) );
			GC::AddMemoryPressure( sizeInBytes );
		}
		else
		{
			m_Buffer = static_cast<char*>( buffer );
		}

		m_Size = sizeInBytes;
		
		m_CanRead = canRead;
		m_CanWrite = canWrite;
		m_OwnsBuffer = makeCopy;
		
		m_ID3DXBuffer = 0;
	}
	
	DataStream::DataStream( Int64 sizeInBytes, bool canRead, bool canWrite )
	{
		if( sizeInBytes < 1 )
			throw gcnew ArgumentOutOfRangeException( "sizeInBytes" );
	
		try
		{
			// Manual Allocation: this is fine
			m_Buffer = new char[ static_cast<int>( sizeInBytes ) ];
			GC::AddMemoryPressure( sizeInBytes );
		}
		catch (std::bad_alloc&)
		{
			throw gcnew OutOfMemoryException();
		}

		m_Size = sizeInBytes;
		
		m_OwnsBuffer = true;
		
		m_CanRead = canRead;
		m_CanWrite = canWrite;
		
		m_ID3DXBuffer = 0;
	}

	DataStream::DataStream( IntPtr userBuffer, Int64 sizeInBytes, bool canRead, bool canWrite )
	{
		if( userBuffer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "userBuffer" );
		if( sizeInBytes < 1 )
			throw gcnew ArgumentOutOfRangeException( "sizeInBytes" );

		m_Buffer = static_cast<char*>( userBuffer.ToPointer() );
		m_Size = sizeInBytes;

		m_CanRead = canRead;
		m_CanWrite = canWrite;
		
		m_ID3DXBuffer = 0;
	}

	DataStream::~DataStream()
	{
		this->!DataStream();
	}
	
	DataStream::!DataStream()
	{
		if(m_OwnsBuffer)
		{
			delete[] m_Buffer;
			GC::RemoveMemoryPressure( m_Size );
			m_OwnsBuffer = false;
		}
		
		if( m_ID3DXBuffer != 0 )
		{
			m_ID3DXBuffer->Release();
			m_ID3DXBuffer = 0;
		}
		
		m_Buffer = 0;
	}

	char* DataStream::RawPointer::get()
	{
		return m_Buffer;
	}

	ID3DXBuffer* DataStream::GetD3DBuffer()
	{
		if( m_ID3DXBuffer != 0 )
			return m_ID3DXBuffer;

		ID3DXBuffer *temp;
		HRESULT hr = D3DXCreateBuffer( static_cast<DWORD>( m_Size ), &temp );
		if( FAILED( hr ) )
			throw gcnew OutOfMemoryException();

		m_ID3DXBuffer = temp;

		memcpy( m_ID3DXBuffer->GetBufferPointer(), m_Buffer, static_cast<size_t>( m_Size ) );
		return m_ID3DXBuffer;
	}

	Int64 DataStream::Seek( Int64 offset, SeekOrigin origin )
	{
		Int64 targetPosition = 0;

		switch( origin )
		{
		case SeekOrigin::Begin:
			targetPosition = offset;
			break;

		case SeekOrigin::Current:
			targetPosition = m_Position + offset;
			break;

		case SeekOrigin::End:
			targetPosition = m_Size - offset;
			break;
		}

		if( targetPosition < 0 )
			throw gcnew InvalidOperationException("Cannot seek beyond the beginning of the stream.");
		if( targetPosition > m_Size )
			throw gcnew InvalidOperationException("Cannot seek beyond the end of the stream.");

		m_Position = targetPosition;
		return m_Position;
	}

	generic<typename T> where T : value class
	void DataStream::Write( T value )
	{
		if( !m_CanWrite )
			throw gcnew NotSupportedException();

		Int64 size = static_cast<Int64>( sizeof(T) );

		if( m_Position + size > m_Size )
			throw gcnew InvalidOperationException();

		memcpy( m_Buffer + m_Position, &value, (size_t) size );
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
		if( m_Position + count > m_Size )
			throw gcnew InvalidOperationException();

		pin_ptr<Byte> pinnedBuffer = &buffer[offset];
		memcpy( m_Buffer + m_Position, pinnedBuffer, count );

		m_Position += count;
	}

	generic<typename T> where T : value class
	void DataStream::WriteRange( array<T>^ data, int offset, int count )
	{
		if( !m_CanWrite )
			throw gcnew NotSupportedException();
		
		Int64 size = static_cast<Int64>( sizeof(T) );

		if( data == nullptr )
			throw gcnew ArgumentNullException( "data" );
		if( offset < 0 || offset > data->Length - 1 )
			throw gcnew ArgumentOutOfRangeException( "offset" );
		if( count < 0 )
			throw gcnew ArgumentOutOfRangeException( "count" );
		if( count == 0 )
			count = data->Length;
		if( offset + count > data->Length )
			throw gcnew ArgumentOutOfRangeException( "data" );
		if( (m_Position + count * size) > m_Size )
			throw gcnew InvalidOperationException();

		pin_ptr<T> pinnedData = &data[offset];
		memcpy( m_Buffer + m_Position, pinnedData, (size_t) size * count );
		m_Position += size * count;
	}
	
	void DataStream::WriteRange( IntPtr source, Int64 count )
	{
		if( !m_CanWrite )
			throw gcnew NotSupportedException();
		
		if( source == IntPtr::Zero )
			throw gcnew ArgumentNullException( "source" );
		if( count < 0 )
			throw gcnew ArgumentOutOfRangeException( "count" );
		if( m_Position + count > m_Size )
			throw gcnew InvalidOperationException();

		memcpy( m_Buffer + m_Position, source.ToPointer(), static_cast<size_t>( count ) );
		m_Position += count;
	}
	
	generic<typename T> where T : value class
	T DataStream::Read()
	{
		if( !m_CanRead )
			throw gcnew NotSupportedException();

		T result;
		Int64 size = static_cast<Int64>( sizeof(T) );

		if( Length - m_Position < size )
			throw gcnew InvalidOperationException();

		memcpy( &result, m_Buffer + m_Position, (size_t) size );
		m_Position += size;
		return result;
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

		int actualCount = min( static_cast<int>(Length - m_Position), count );

		pin_ptr<Byte> pinnedBuffer = &buffer[offset];
		memcpy( pinnedBuffer, m_Buffer + m_Position, actualCount );

		m_Position += actualCount;
		return actualCount;
	}

	generic<typename T> where T : value class
	array<T>^ DataStream::ReadRange( int count )
	{
		if( !m_CanRead )
			throw gcnew NotSupportedException();
		if( count < 0 )
			throw gcnew ArgumentOutOfRangeException( "count" );
			
		size_t elementSize = sizeof(T);
		unsigned int actualCount = min( static_cast<unsigned int>((Length - m_Position) / elementSize), static_cast<unsigned int>( count ) );
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
		SLIMDX_UNREFERENCED_PARAMETER(value);
		throw gcnew NotSupportedException("DataStream objects cannot be resized.");
	}

	Int64 DataStream::Position::get()
	{
		return m_Position;
	}

	void DataStream::Position::set( System::Int64 value )
	{
		Seek( value, System::IO::SeekOrigin::Begin );
	}
	
	Int64 DataStream::Length::get()
	{
		return m_Size;
	}
}
