// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using SlimDX2.Direct3D;

namespace SlimDX2
{
    /// <summary>
    ///   Provides a stream interface to a buffer located in unmanaged memory.
    /// </summary>
    /// <unmanaged>None</unmanaged>
    public class DataStream : Stream
    {
        private unsafe sbyte* _buffer;
        private bool _canRead;
        private bool _canWrite;
        private GCHandle _gCHandle;
        private Blob _blob;
        private bool _ownsBuffer;
        private long _position;
        private long _size;

        /// <summary>
        ///   Release any resource associated to this DataStream
        /// </summary>
        public void Release()
        {
            unsafe
            {
                if (_blob != null)
                    _blob.Release();
                if (_gCHandle.IsAllocated)
                    _gCHandle.Free();
                if (_ownsBuffer && _buffer != (sbyte*) 0)
                {
                    Marshal.FreeHGlobal((IntPtr) _buffer);
                    _buffer = (sbyte*) 0;
                }
            }
        }

        internal unsafe DataStream(Blob buffer)
        {
            Debug.Assert(buffer.GetBufferSize() > 0);

            this._buffer = (sbyte*) buffer.GetBufferPointer();
            this._size = buffer.GetBufferSize();
            this._canRead = true;
            this._canWrite = true;
            this._blob = buffer;
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "SlimDX2.DataStream" /> class, using a managed buffer as a backing store.
        /// </summary>
        /// <param name = "userBuffer">A managed array to be used as a backing store.</param>
        /// <param name = "canRead">
        ///   <c>true</c> if reading from the buffer should be allowed; otherwise, <c>false</c>.</param>
        /// <param name = "canWrite">
        ///   <c>true</c> if writing to the buffer should be allowed; otherwise, <c>false</c>.</param>
        public DataStream(Array userBuffer, bool canRead, bool canWrite)
        {
            unsafe
            {
                int num;
                if (userBuffer == null)
                {
                    throw new ArgumentNullException("userBuffer");
                }
                GCHandle handle = GCHandle.Alloc(userBuffer, GCHandleType.Pinned);

                this._gCHandle = handle;
                IntPtr ptr = this._gCHandle.AddrOfPinnedObject();
                this._buffer = (sbyte*) ptr.ToPointer();
                if (userBuffer.Length == 0)
                {
                    num = 0;
                }
                else
                {
                    num = Marshal.SizeOf(userBuffer.GetValue(0))*userBuffer.Length;
                }
                this._size = num;
                this._canRead = canRead;
                this._canWrite = canWrite;
            }
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "SlimDX2.DataStream" /> class, and allocates a new buffer to use as a backing store.
        /// </summary>
        /// <param name = "sizeInBytes">The size of the buffer to be allocated, in bytes.</param>
        /// <param name = "canRead">
        ///   <c>true</c> if reading from the buffer should be allowed; otherwise, <c>false</c>.</param>
        /// <param name = "canWrite">
        ///   <c>true</c> if writing to the buffer should be allowed; otherwise, <c>false</c>.</param>
        /// <exception cref = "T:System.ArgumentOutOfRangeException">
        ///   <paramref name = "sizeInBytes" /> is less than 1.</exception>
        public DataStream(int sizeInBytes, bool canRead, bool canWrite)
        {
            unsafe
            {
                Debug.Assert(sizeInBytes > 0);

                this._buffer = (sbyte*) Marshal.AllocHGlobal(sizeInBytes);
                this._size = sizeInBytes;
                this._ownsBuffer = true;
                this._canRead = canRead;
                this._canWrite = canWrite;
            }
        }

        internal unsafe DataStream(void* buffer, int sizeInBytes, bool canRead, bool makeCopy)
        {
            Debug.Assert(sizeInBytes > 0);

            if (makeCopy)
            {
                this._buffer = (sbyte*) Marshal.AllocHGlobal(sizeInBytes);
                Utilities.CopyMemory((IntPtr) this._buffer, (IntPtr) buffer, sizeInBytes);
            }
            else
            {
                this._buffer = (sbyte*) buffer;
            }
            this._size = sizeInBytes;
            this._canRead = canRead;
            this._ownsBuffer = makeCopy;
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "SlimDX2.DataStream" /> class, using an unmanaged buffer as a backing store.
        /// </summary>
        /// <param name = "userBuffer">A pointer to the buffer to be used as a backing store.</param>
        /// <param name = "sizeInBytes">The size of the buffer provided, in bytes.</param>
        /// <param name = "canRead">
        ///   <c>true</c> if reading from the buffer should be allowed; otherwise, <c>false</c>.</param>
        /// <param name = "canWrite">
        ///   <c>true</c> if writing to the buffer should be allowed; otherwise, <c>false</c>.</param>
        /// <exception cref = "T:System.ArgumentNullException">
        ///   <paramref name = "userBuffer" /> is a zero pointer.</exception>
        /// <exception cref = "T:System.ArgumentOutOfRangeException">
        ///   <paramref name = "sizeInBytes" /> is less than 1.</exception>
        public DataStream(IntPtr userBuffer, long sizeInBytes, bool canRead, bool canWrite)
        {
            unsafe
            {
                Debug.Assert(userBuffer != IntPtr.Zero);
                Debug.Assert(sizeInBytes > 0);
                this._buffer = (sbyte*) userBuffer.ToPointer();
                this._size = sizeInBytes;
                this._canRead = canRead;
                this._canWrite = canWrite;
            }
        }

        internal unsafe DataStream(void* buffer, int sizeInBytes, bool canRead, bool canWrite, bool makeCopy)
        {
            Debug.Assert(sizeInBytes > 0);
            if (makeCopy)
            {
                this._buffer = (sbyte*) Marshal.AllocHGlobal(sizeInBytes);
                Utilities.CopyMemory((IntPtr) this._buffer, (IntPtr) buffer, sizeInBytes);
            }
            else
            {
                this._buffer = (sbyte*) buffer;
            }
            this._size = sizeInBytes;
            this._canRead = canRead;
            this._canWrite = canWrite;
            this._ownsBuffer = makeCopy;
        }

        /// <summary>
        ///   Not supported.
        /// </summary>
        /// <exception cref = "T:System.NotSupportedException">Always thrown.</exception>
        public override void Flush()
        {
            throw new NotSupportedException("DataStream objects cannot be flushed.");
        }

        /// <summary>
        ///   Reads a single value from the current stream and advances the current
        ///   position within this stream by the number of bytes read.
        /// </summary>
        /// <typeparam name = "T">The type of the value to be read from the stream.</typeparam>
        /// <returns>The value that was read.</returns>
        /// <exception cref = "T:System.NotSupportedException">This stream does not support reading.</exception>
        /// <exception cref = "T:System.IO.EndOfStreamException">There is not enough space in the current
        ///   stream to read a value of this type.</exception>
        public T Read<T>() where T : struct
        {
            unsafe
            {
                Debug.Assert(_canRead);

                sbyte* from = this._buffer + _position;
                T result = default(T);
                _position = (sbyte*) Utilities.Read((IntPtr)from, ref result) - this._buffer;
                return result;
            }
        }

        /// <summary>
        ///   Reads a sequence of bytes from the current stream and advances the position
        ///   within the stream by the number of bytes read.
        /// </summary>
        /// <param name = "buffer">An array of values to be read from the stream.</param>
        /// <param name = "offset">The zero-based byte offset in buffer at which to begin storing
        ///   the data read from the current stream.</param>
        /// <param name = "count">The maximum number of bytes to be read from the current stream.</param>
        /// <returns>The number of bytes read from the stream.</returns>
        /// <exception cref = "T:System.NotSupportedException">This stream does not support reading.</exception>
        /// <exception cref = "T:System.ArgumentNullException">
        ///   <paramref name = "buffer" /> is a null reference.</exception>
        /// <exception cref = "T:System.ArgumentOutOfRangeException">
        ///   <paramref name = "offset" /> or <paramref name = "count" /> is negative.</exception>
        /// <exception cref = "T:System.ArgumentException">The sum of <paramref name = "offset" /> and <paramref name = "count" /> is greater than the buffer length.</exception>
        public override int Read(byte[] buffer, int offset, int count)
        {
            return this.ReadRange<byte>(buffer, offset, count);
        }

        /// <summary>
        ///   Reads an array of values from the current stream, and advances the current position
        ///   within this stream by the number of bytes written.
        /// </summary>
        /// <typeparam name = "T">The type of the values to be read from the stream.</typeparam>
        /// <returns>An array of values that was read from the current stream.</returns>
        /// <exception cref = "T:System.NotSupportedException">This stream does not support reading.</exception>
        /// <exception cref = "T:System.ArgumentOutOfRangeException">
        ///   <paramref name = "count" /> is negative.</exception>
        public T[] ReadRange<T>(int count) where T : struct
        {
            unsafe
            {
                Debug.Assert(_canRead);

                sbyte* from = this._buffer + _position;
                T[] result = new T[count];
                _position = (sbyte*) Utilities.Read((IntPtr)from, result, 0, count) - this._buffer;
                return result;
            }
        }

        /// <summary>
        ///   Reads a sequence of elements from the current stream into a target buffer and
        ///   advances the position within the stream by the number of bytes read.
        /// </summary>
        /// <param name = "buffer">An array of values to be read from the stream.</param>
        /// <param name = "offset">The zero-based byte offset in buffer at which to begin storing
        ///   the data read from the current stream.</param>
        /// <param name = "count">The number of values to be read from the current stream.</param>
        /// <returns>The number of bytes read from the stream.</returns>
        /// <exception cref = "T:System.NotSupportedException">This stream does not support reading.</exception>
        /// <exception cref = "T:System.ArgumentNullException">
        ///   <paramref name = "buffer" /> is a null reference.</exception>
        /// <exception cref = "T:System.ArgumentOutOfRangeException">
        ///   <paramref name = "offset" /> or <paramref name = "count" /> is negative.</exception>
        /// <exception cref = "T:System.ArgumentException">The sum of <paramref name = "offset" /> and <paramref name = "count" /> is greater than the buffer length.</exception>
        public int ReadRange<T>(T[] buffer, int offset, int count) where T : struct
        {
            unsafe
            {
                Debug.Assert(_canRead);

                sbyte* from = this._buffer + _position;
                long old_position = _position;
                _position = (sbyte*) Utilities.Read((IntPtr)from, buffer, offset, count) - this._buffer;
                return (int) (_position - old_position);
            }
        }

        /// <summary>
        ///   Sets the position within the current stream.
        /// </summary>
        /// <exception cref = "T:System.InvalidOperationException">Attempted to seek outside of the bounds of the stream.</exception>
        public override long Seek(long offset, SeekOrigin origin)
        {
            long targetPosition = 0;

            switch (origin)
            {
                case SeekOrigin.Begin:
                    targetPosition = offset;
                    break;

                case SeekOrigin.Current:
                    targetPosition = _position + offset;
                    break;

                case SeekOrigin.End:
                    targetPosition = _size - offset;
                    break;
            }

            if (targetPosition < 0)
                throw new InvalidOperationException("Cannot seek beyond the beginning of the stream.");
            if (targetPosition > _size)
                throw new InvalidOperationException("Cannot seek beyond the end of the stream.");

            _position = targetPosition;
            return _position;
        }

        /// <summary>
        ///   Not supported.
        /// </summary>
        /// <param name = "value">Always ignored.</param>
        /// <exception cref = "T:System.NotSupportedException">Always thrown.</exception>
        public override void SetLength(long value)
        {
            throw new NotSupportedException("DataStream objects cannot be resized.");
        }

        /// <summary>
        ///   Writes a single value to the stream, and advances the current position
        ///   within this stream by the number of bytes written.
        /// </summary>
        /// <typeparam name = "T">The type of the value to be written to the stream.</typeparam>
        /// <param name = "value">The value to write to the stream.</param>
        /// <exception cref = "T:System.NotSupportedException">The stream does not support writing.</exception>
        /// <exception cref = "T:System.IO.EndOfStreamException">There is not enough space
        ///   remaining in the stream to write this type of value.</exception>
        public void Write<T>(T value) where T : struct
        {
            Debug.Assert(_canWrite);
            unsafe
            {
                _position = (sbyte*) SlimDX2.Interop.Write(_buffer + _position, ref value) - _buffer;
            }
        }

        /// <summary>
        ///   Writes a sequence of bytes to the current stream and advances the current
        ///   position within this stream by the number of bytes written.
        /// </summary>
        /// <param name = "buffer">An array of bytes. This method copies count bytes from buffer to the current stream.</param>
        /// <param name = "offset">The zero-based byte offset in buffer at which to begin copying bytes to the current stream.</param>
        /// <param name = "count">The number of bytes to be written to the current stream.</param>
        /// <exception cref = "T:System.NotSupportedException">This stream does not support writing.</exception>
        /// <exception cref = "T:System.ArgumentNullException">
        ///   <paramref name = "buffer" /> is a null reference.</exception>
        /// <exception cref = "T:System.ArgumentOutOfRangeException">
        ///   <paramref name = "offset" /> or <paramref name = "count" /> is negative.</exception>
        /// <exception cref = "T:System.ArgumentException">The sum of <paramref name = "offset" /> and <paramref name = "count" /> is greater than the buffer length.</exception>
        public override void Write(byte[] buffer, int offset, int count)
        {
            this.WriteRange<byte>(buffer, offset, count);
        }

        /// <summary>
        ///   Writes an array of values to the current stream, and advances the current position
        ///   within this stream by the number of bytes written.
        /// </summary>
        /// <param name = "data">An array of values to be written to the current stream.</param>
        /// <exception cref = "T:System.NotSupportedException">This stream does not support writing.</exception>
        /// <exception cref = "T:System.ArgumentNullException">
        ///   <paramref name = "data" /> is a null reference.</exception>
        public void WriteRange<T>(T[] data) where T : struct
        {
            this.WriteRange<T>(data, 0, data.Length);
        }

        /// <summary>
        ///   Writes a range of bytes to the current stream, and advances the current position
        ///   within this stream by the number of bytes written.
        /// </summary>
        /// <param name = "source">A pointer to the location to start copying from.</param>
        /// <param name = "count">The number of bytes to copy from source to the current stream.</param>
        /// <exception cref = "T:System.NotSupportedException">This stream does not support writing.</exception>
        /// <exception cref = "T:System.ArgumentNullException">
        ///   <paramref name = "source" /> is a zero pointer.</exception>
        /// <exception cref = "T:System.ArgumentOutOfRangeException">
        ///   <paramref name = "count" /> is negative.</exception>
        public void WriteRange(IntPtr source, long count)
        {
            unsafe
            {
                Debug.Assert(_canWrite);
                Debug.Assert(source != IntPtr.Zero);
                Debug.Assert(count > 0);
                Debug.Assert((this._position + count) < this._size);

                // TODO: use Interop.memcpy
                Utilities.CopyMemory((IntPtr) (this._buffer + this._position), source, (ulong) count);
                this._position += count;
            }
        }

        /// <summary>
        ///   Writes an array of values to the current stream, and advances the current position
        ///   within this stream by the number of bytes written.
        /// </summary>
        /// <typeparam name = "T">The type of the values to be written to the stream.</typeparam>
        /// <param name = "data">An array of values to be written to the stream.</param>
        /// <param name = "offset">The zero-based offset in data at which to begin copying values to the current stream.</param>
        /// <param name = "count">The number of values to be written to the current stream. If this is zero,
        ///   all of the contents <paramref name = "data" /> will be written.</param>
        /// <exception cref = "T:System.NotSupportedException">This stream does not support writing.</exception>
        /// <exception cref = "T:System.ArgumentNullException">
        ///   <paramref name = "data" /> is a null reference.</exception>
        /// <exception cref = "T:System.ArgumentOutOfRangeException">
        ///   <paramref name = "offset" /> or <paramref name = "count" /> is negative.</exception>
        /// <exception cref = "T:System.ArgumentException">The sum of <paramref name = "offset" /> and <paramref name = "count" /> is greater than the buffer length.</exception>
        public void WriteRange<T>(T[] data, int offset, int count) where T : struct
        {
            unsafe
            {
                Debug.Assert(_canWrite);
                _position = (sbyte*) SlimDX2.Interop.Write(_buffer + _position, data, offset, count) - _buffer;
            }
        }

        /// <summary>
        ///   Gets a value indicating whether the current stream supports reading.
        /// </summary>
        /// <value>
        ///   <c>true</c> if the stream supports reading; otherwise, <c>false</c>.</value>
        public override bool CanRead
        {
            get { return this._canRead; }
        }

        /// <summary>
        ///   Gets a value indicating whether the current stream supports seeking.
        /// </summary>
        /// <value>Always <c>true</c>.</value>
        public override bool CanSeek
        {
            get { return true; }
        }

        /// <summary>
        ///   Gets a value indicating whether the current stream supports writing.
        /// </summary>
        /// <value>
        ///   <c>true</c> if the stream supports writing; otherwise, <c>false</c>.</value>
        public override bool CanWrite
        {
            get { return this._canWrite; }
        }

        /// <summary>
        ///   Gets the internal pointer to the current stream's backing store.
        /// </summary>
        /// <value>An IntPtr to the buffer being used as a backing store.</value>
        public IntPtr DataPointer
        {
            get
            {
                unsafe
                {
                    return new IntPtr(this._buffer);
                }
            }
        }

        /// <summary>
        ///   Gets the length in bytes of the stream.
        /// </summary>
        /// <value>A long value representing the length of the stream in bytes.</value>
        public override long Length
        {
            get { return this._size; }
        }

        /// <summary>
        ///   Gets or sets the position within the current stream.
        /// </summary>
        /// <value>The current position within the stream.</value>
        /// <seealso cref = "T:System.IO.Stream">Stream Class</seealso>
        public override long Position
        {
            get { return this._position; }
            set { this.Seek(value, SeekOrigin.Begin); }
        }


        internal unsafe IntPtr PositionPointer
        {
            get
            {
                return (IntPtr) (this._buffer + this._position);
            }
        }

        internal long RemainingLength
        {
            get { return (this._size - this._position); }
        }
    }
}