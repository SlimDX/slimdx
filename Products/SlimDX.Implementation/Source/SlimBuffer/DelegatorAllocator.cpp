#include "stdafx.h"
#include "DelegateAllocator.h"

using namespace System;

namespace SlimBuffer {
	DelegateAllocator::DelegateAllocator( AllocateDelegate^ allocateDelegate, ReleaseDelegate^ releaseDelegate )
	: allocateDelegate( allocateDelegate )
	, releaseDelegate( releaseDelegate ) {
		if( allocateDelegate == nullptr ) {
			throw gcnew ArgumentNullException( "allocateDelegate" );
		}
		
		if( releaseDelegate == nullptr ) {
			throw gcnew ArgumentNullException( "releaseDelegate" );
		}
	}

	IntPtr DelegateAllocator::Allocate( Int64 sizeInBytes ) {
		if( sizeInBytes <= 0 ) {
			throw gcnew ArgumentOutOfRangeException( "sizeInBytes", "Buffer size must be greater than zero." );
		}
		
		return allocateDelegate( sizeInBytes );
	}
	
	void DelegateAllocator::Release( IntPtr pointer ) {
		releaseDelegate( pointer );
	}
}
