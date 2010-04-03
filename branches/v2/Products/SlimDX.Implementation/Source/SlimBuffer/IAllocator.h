#pragma once

namespace SlimBuffer {
	/// <summary>
	/// The interface required of an object that manages the acquisition and release of
	/// the native memory used by a MemoryBuffer.
	///
	/// The interface is structured in terms of the managed IntPtr class to allow for
	/// managed libraries to implement it, thus allowing for interoperability with
	/// other libraries both native and managed.
	/// </summary>
	public interface struct IAllocator {
		public:
			/// <summary>
			/// Allocates a native memory block of the specified size.
			/// </summary>
			/// <param name="size">The size, in bytes, of the requested allocation. Must be greater than zero.</param>
			/// <returns>The allocated block, or IntPtr::Zero if the allocation failed.</returns>
			System::IntPtr Allocate( System::Int64 size );
			
			/// <summary>
			/// Releases a native memory block.
			/// </summary>
			/// <param name="pointer">A pointer to the memory block.</param>
			void Release( System::IntPtr pointer );
	};
}
