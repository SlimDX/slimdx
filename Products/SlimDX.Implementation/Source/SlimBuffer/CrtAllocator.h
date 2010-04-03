#pragma once

#include "IAllocator.h"

namespace SlimBuffer {
	/// <summary>
	/// Implements the IAllocator interface using the CRT.
	/// </summary>
	public value struct CrtAllocator : IAllocator {
		public:
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
	};
}
