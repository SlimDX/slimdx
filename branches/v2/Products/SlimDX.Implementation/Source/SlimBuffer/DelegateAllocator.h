#pragma once

#include "IAllocator.h"

namespace SlimBuffer {
	public delegate System::IntPtr AllocateDelegate(System::Int64 ptr);
	public delegate void ReleaseDelegate(System::IntPtr ptr);
	/// <summary>
	/// Implements the IAllocator interface using user-specified delegates for the allocation
	/// and release operations.
	/// </summary>
	public value struct DelegateAllocator : IAllocator {
		public:
			/// <summary>
			/// Initializes a new instance of the DelegateAllocator class.
			/// </summary>
			/// <param name="allocateDelegate">A delegate that handles the allocation request.</param>
			/// <param name="releaseDelegate">A delegate that handles the release request.</param>
			DelegateAllocator( AllocateDelegate^ allocateDelegate, ReleaseDelegate^ releaseDelegate );
			
			/// <summary>
			/// Allocates a native memory block of the specified size.
			/// </summary>
			/// <param name="size">The size, in bytes, of the requested allocation. Must be greater than zero.</param>
			/// <returns>The allocated block, or IntPtr::Zero if the allocation failed.</returns>
			virtual System::IntPtr Allocate( System::Int64 size );
			
			/// <summary>
			/// Releases a native memory block.
			/// </summary>
			/// <param name="pointer">A pointer to the memory block.</param>
			virtual void Release( System::IntPtr pointer );
		
		private:
			AllocateDelegate^ allocateDelegate;
			ReleaseDelegate^ releaseDelegate;
	};
}
