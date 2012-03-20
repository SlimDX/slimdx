using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace SlimDX.Toolkit
{
    /// <summary>
    /// Provides a 16-byte aligned array.
    /// </summary>
    /// <typeparam name="T">The type of the objects within the array. These must be value types that only contain other value types; otherwise, the behavior is undefined.</typeparam>
    public unsafe class AlignedArray<T> : IDisposable where T : struct
    {
        SafeHGlobal memory;
        byte* ptr;
        int elementSize;

        /// <summary>
        /// Gets a pointer to the aligned block of memory.
        /// </summary>
        public byte* Pointer
        {
            get { return ptr; }
        }

        /// <summary>
        /// Gets the number of elements in the array.
        /// </summary>
        public int Length
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets a pointer to the element at the specified index.
        /// </summary>
        public byte* this[int index]
        {
            get { return Pointer + elementSize * index; }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="AlignedArray&lt;T&gt;"/> class.
        /// </summary>
        /// <param name="count">The number of elements in the array.</param>
        /// <exception cref="ArgumentOutOfRangeException">Thrown if <paramref name="count"/> is not a valid array length.</exception>
        /// <exception cref="InvalidOperationException">Thrown if an attempt is made to create an aligned array of reference types.</exception>
        public AlignedArray(int count)
        {
            if (!typeof(T).IsValueType)
                throw new InvalidOperationException("Cannot create aligned arrays for reference types.");
            if (count <= 0)
                throw new ArgumentOutOfRangeException("count", count, "Invalid size passed for length of the array.");

            Length = count;
            elementSize = Marshal.SizeOf(typeof(T));
            memory = new SafeHGlobal(elementSize * count + 15);
            void *mem = memory.DangerousGetHandle().ToPointer();

            // make sure we get a 16-byte aligned pointer
            ptr = (byte*)(((long)mem + 15) & ~0x0F);
        }

        /// <summary>
        /// Reallocates the array with the new size and copies over the existing elements.
        /// </summary>
        /// <param name="newCount">The number of elements in the new array.</param>
        /// <exception cref="ArgumentOutOfRangeException">Thrown if <paramref name="newCount"/> is not a valid array length.</exception>
        public void Realloc(int newCount)
        {
            if (newCount <= Length)
                throw new ArgumentOutOfRangeException("newCount", newCount, "Invalid size passed for length of the array.");

            var newMemory = new SafeHGlobal(elementSize * newCount + 15);
            void* mem = newMemory.DangerousGetHandle().ToPointer();

            // make sure we get a 16-byte aligned pointer
            var newPtr = (byte*)(((long)mem + 15) & ~0x0F);

            for (int i = 0; i < Length * elementSize; i++)
                newPtr[i] = ptr[i];

            memory.Close();
            memory = newMemory;
            ptr = newPtr;
            Length = newCount;
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            if (memory != null)
            {
                memory.Close();
                memory = null;
            }
        }
    }
}
