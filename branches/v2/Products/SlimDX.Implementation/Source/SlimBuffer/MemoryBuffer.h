#pragma once

namespace SlimBuffer {
	interface struct IAllocator;
	/// <summary>
	/// Represents a buffer of native memory.
	/// </summary>
	public ref class MemoryBuffer : System::IDisposable, SlimDX::IMemoryBuffer {
		public:
			/// <summary>
			/// Initializes a new instance of the MemoryBuffer class.
			/// </summary>
			/// <param name="sizeInBytes">The size, in bytes, of the buffer to allocate.</param>
			/// <param name="allocator">The allocator used to manage the underlying memory for the buffer.
			/// May be null. If null, a default allocator is used.</param>
			MemoryBuffer( System::Int64 sizeInBytes, IAllocator^ allocator );
			
			/// <summary>
			/// Initializes a new instance of the MemoryBuffer class.
			/// </summary>
			/// <param name="buffer">The native memory buffer to use for the MemoryBuffer. The MemoryBuffer
			/// does not acquire ownership of this memory.</param>
			MemoryBuffer( System::IntPtr buffer );
			
			/// <summary>
			/// Initializes a new instance of the MemoryBuffer class.
			/// </summary>
			/// <param name="buffer">The native memory buffer to use for the MemoryBuffer. The MemoryBuffer
			/// does not acquire ownership of this memory.</param>
			MemoryBuffer( unsigned char* buffer );

			/// <summary>
			/// Disposes of object resources.
			/// </summary>
			~MemoryBuffer();
			
			/// <summary>
			/// Releases unmanaged resources and performs other cleanup operations before the
			/// <see cref="MemoryBuffer"/> is reclaimed by garbage collection.
			/// </summary>
			!MemoryBuffer();
			
			/// <summary>
			/// Gets the allocator used to manage the underlying memory for the buffer.
			/// If null, the buffer does not own its underlying memory.
			/// </summary>
			property IAllocator^ Allocator {
				IAllocator^ get();
			}
			
			/// <summary>
			/// Gets or sets the offset (in bytes) at which the next write will occur within the buffer.
			/// </summary>
			property System::Int64 WriteOffset {
				virtual System::Int64 get();
				virtual void set( System::Int64 value );
			}
			
			/// <summary>
			/// Gets or sets the offset (in bytes) at which the next read will occur within the buffer.
			/// </summary>
			property System::Int64 ReadOffset {
				virtual System::Int64 get();
				virtual void set( System::Int64 value );
			}
			
			/// <summary>
			/// Writes a value to the buffer at the current write offset.
			/// </summary>
			/// <param name="value">The value to write.</param>
			generic<typename T> where T : value class
			virtual void Write( T value );
			
			/// <summary>
			/// Reads a value from the buffer at the current read offset.
			/// </summary>
			/// <returns>The value read.</param>
			generic<typename T> where T : value class
			virtual T Read();
			
		private:
			unsigned char* base;
			System::Int64 writeOffset;
			System::Int64 readOffset;
			
			IAllocator^ allocator;
	};
}
