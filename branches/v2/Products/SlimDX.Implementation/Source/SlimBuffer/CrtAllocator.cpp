#include "stdafx.h"
#include "CrtAllocator.h"

using namespace System;

namespace SlimBuffer {
	IntPtr CrtAllocator::Allocate( Int64 sizeInBytes ) {
		if( sizeInBytes <= 0 ) {
			throw gcnew ArgumentOutOfRangeException( "sizeInBytes", "Buffer size must be greater than zero." );
		}
		
		return IntPtr( new unsigned char[static_cast<size_t>( sizeInBytes )] );
	}
	
	void CrtAllocator::Release( IntPtr pointer ) {
		delete[] pointer.ToPointer();
	}
}
