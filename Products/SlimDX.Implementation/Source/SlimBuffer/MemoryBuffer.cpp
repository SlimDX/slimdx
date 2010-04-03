#include "stdafx.h"
#include "MemoryBuffer.h"

#include <windows.h>
#include <vcclr.h>
#include <memory.h>

#include "CrtAllocator.h"

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace SlimBuffer {
	MemoryBuffer::MemoryBuffer( Int64 sizeInBytes, IAllocator^ allocator )
	: writeOffset( 0 )
	, readOffset( 0 ) {
		if( sizeInBytes <= 0 ) {
			throw gcnew ArgumentOutOfRangeException( "sizeInBytes", "Buffer size must be greater than zero." );
		}
		
		if( allocator == nullptr ) {
			this->allocator = gcnew CrtAllocator();
		} else {
			this->allocator = allocator;
		}
		
		base = reinterpret_cast<unsigned char*>( this->allocator->Allocate( sizeInBytes ).ToPointer() );
	}
	
	MemoryBuffer::MemoryBuffer( IntPtr buffer )
	: writeOffset( 0 )
	, readOffset( 0 ) {
		if( buffer == IntPtr::Zero ) {
			throw gcnew ArgumentNullException( "buffer" );
		}
		
		base = static_cast<unsigned char*>( buffer.ToPointer() );
	}
	
	MemoryBuffer::MemoryBuffer( unsigned char* buffer )
	: writeOffset( 0 )
	, readOffset( 0 ) {
		if( buffer == 0 ) {
			throw gcnew ArgumentNullException( "buffer" );
		}
	
		base = buffer;
	}
	
	MemoryBuffer::~MemoryBuffer() {
		this->!MemoryBuffer();
	}
	
	MemoryBuffer::!MemoryBuffer() {
		if( allocator != nullptr ) {
			allocator->Release( IntPtr( base ) );
		}
	}

	IAllocator^ MemoryBuffer::Allocator::get() {
		return allocator;
	}
	
	Int64 MemoryBuffer::WriteOffset::get() {
		return writeOffset;
	}
	
	void MemoryBuffer::WriteOffset::set( Int64 value ) {
		writeOffset = value;
	}
	
	Int64 MemoryBuffer::ReadOffset::get() {
		return readOffset;
	}
	
	void MemoryBuffer::ReadOffset::set( Int64 value ) {
		readOffset = value;
	}
	
	generic<typename T> where T : value class
	void MemoryBuffer::Write( T value ) {
		memcpy( base + writeOffset, &value, sizeof( T ) );
		writeOffset += sizeof( T );
	}
	
	generic<typename T> where T : value class
	T MemoryBuffer::Read() {
		T value;
		unsigned char* readPointer = base + readOffset;
		
		memcpy( &value, base + readOffset, sizeof( T ) );
		readOffset += sizeof( T );
		return value;
	}
}
