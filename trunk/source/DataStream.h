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
#pragma once

#include <d3dx9.h>

#ifdef XMLDOCS
using System::InvalidOperationException;
using System::ArgumentNullException;
using System::ArgumentOutOfRangeException;
using System::NotSupportedException;
#endif

namespace SlimDX
{

	/// <summary>
	/// Provides a stream interface to a buffer located in unmanaged memory.
	/// </summary>
	public ref class DataStream : public System::IO::Stream
	{
		private:
		char* m_Buffer;
		bool m_OwnsBuffer;
		ID3DXBuffer *m_ID3DXBuffer;
		
		System::Int64 m_Size;
		System::Int64 m_Position;
		
		initonly bool m_CanRead;
		initonly bool m_CanWrite;

	internal:
		DataStream( ID3DXBuffer *buffer );
		DataStream( void* buffer, System::Int64 sizeInBytes, bool canRead, bool canWrite, bool makeCopy );

		property char* RawPointer
		{
			char* get();
		}
	
		void TakeOwnership() { m_OwnsBuffer = true; }

		ID3DXBuffer* GetD3DBuffer();

	public:
		/// <summary>
		/// Initializes a new instance of the DataStream class, and allocates a new buffer to use as a backing store.
		/// </summary>
		/// <param name="sizeInBytes">The size of the buffer to be allocated, in bytes.</param>
		/// <param name="canRead"><c>true</c> if reading from the buffer should be allowed, <c>false</c> otherwise.</param>
		/// <param name="canWrite"><c>true</c> if writing to the buffer should be allowed, <c>false</c> otherwise.</param>
		/// <exception cref="ArgumentOutOfRangeException"><i>sizeInBytes</i> is less than 1.</exception>
		DataStream( System::Int64 sizeInBytes, bool canRead, bool canWrite );

		/// <summary>
		/// Initializes a new instance of the DataStream class, using a user provided buffer as a backing store.
		/// </summary>
		/// <param name="userBuffer">A pointer to the buffer to be used as a backing store.</param>
		/// <param name="sizeInBytes">The size of the buffer provided, in bytes.</param>
		/// <param name="canRead"><c>true</c> if reading from the buffer should be allowed, <c>false</c> otherwise.</param>
		/// <param name="canWrite"><c>true</c> if writing to the buffer should be allowed, <c>false</c> otherwise.</param>
		/// <exception cref="ArgumentNullException"><i>userBuffer</i> is a zero pointer.</exception>
		/// <exception cref="ArgumentOutOfRangeException"><i>sizeInBytes</i> is less than 1.</exception>
		DataStream( System::IntPtr userBuffer, System::Int64 sizeInBytes, bool canRead, bool canWrite );
		
		~DataStream();
		!DataStream();
		
		/// <summary>Sets the position within the current stream.</summary>
		/// <exception cref="InvalidOperationException">Attempted to seek outside of the bounds of the stream.</exception>
		virtual System::Int64 Seek( System::Int64 offset, System::IO::SeekOrigin origin ) override;

		/// <summary>
		/// Writes a single value to the stream, and advances the current position
		/// within this stream by the number of bytes written.
		/// </summary>
		/// <param name="value">The value to write to the stream.</param>
		/// <exception cref="NotSupportedException">This stream does not support writing.</exception>
		/// <exception cref="InvalidOperationException">There is not enough space
		/// remaining in the stream to write this type of value.</exception>
		generic<typename T> where T : value class
		void Write( T value );

		/// <summary>
		/// Writes a sequence of bytes to the current stream and advances the current
		/// position within this stream by the number of bytes written.
		/// </summary>
		/// <param name="buffer">An array of bytes. This method copies count bytes from buffer to the current stream.</param>
		/// <param name="offset">The zero-based byte offset in buffer at which to begin copying bytes to the current stream.</param>
		/// <param name="count">The number of bytes to be written to the current stream.</param>
		/// <exception cref="NotSupportedException">This stream does not support writing.</exception>
		/// <exception cref="ArgumentNullException"><i>buffer</i> is a null reference.</exception>
		/// <exception cref="ArgumentOutOfRangeException"><i>offset</i> or <i>count</i> leads outside the bounds of <i>buffer</i>.</exception>
		virtual void Write( array<System::Byte>^ buffer, int offset, int count ) override;

		/// <summary>
		/// Writes an array of values to the current stream, and advances the current position
		/// within this stream by the number of bytes written.
		/// </summary>
		/// <param name="data">An array of values to be written to the stream.</param>
		/// <param name="offset">The zero-based offset in data at which to begin copying values to the current stream.</param>
		/// <param name="count">The number of values to be written to the current stream. If this is zero, all of <i>data</i> will be written.</param>
		/// <exception cref="NotSupportedException">This stream does not support writing.</exception>
		/// <exception cref="ArgumentNullException"><i>data</i> is a null reference.</exception>
		/// <exception cref="ArgumentOutOfRangeException"><i>offset</i> or <i>count</i> leads outside the bounds of <i>data</i>.</exception>
		generic<typename T> where T : value class
		void WriteRange( array<T>^ data, int offset, int count );

		/// <summary>
		/// Writes an array of values to the current stream, and advances the current position
		/// within this stream by the number of bytes written.
		/// </summary>
		/// <param name="data">An array of values to be written to the current stream.</param>
		/// <exception cref="NotSupportedException">This stream does not support writing.</exception>
		/// <exception cref="ArgumentNullException"><i>data</i> is a null reference.</exception>
		generic<typename T> where T : value class
		void WriteRange( array<T>^ data ) { WriteRange( data, 0, 0 ); }
		
		/// <summary>
		/// Writes a range of bytes to the current stream, and advances the current position
		/// within this stream by the number of bytes written.
		/// </summary>
		/// <param name="source">A pointer to the location to start copying from.</param>
		/// <param name="count">The number of bytes to copy from source to the current stream.</param>
		/// <exception cref="NotSupportedException">This stream does not support writing.</exception>
		/// <exception cref="ArgumentNullException"><i>source</i> is a zero pointer.</exception>
		/// <exception cref="ArgumentOutOfRangeException"><i>count</i> is less than zero.</exception>
		void WriteRange( System::IntPtr source, System::Int64 count );

		/// <summary>
		/// Reads a single value from the current stream and advances the current
		/// position within this stream by the number of bytes read.
		/// </summary>
		/// <returns>The value that was read.</returns>
		/// <exception cref="NotSupportedException">This stream does not support reading.</exception>
		/// <exception cref="InvalidOperationException">There is not enough space in the current
		/// stream to read a value of this type.</exception>
		generic<typename T> where T : value class
		T Read();

		/// <summary>
		/// Reads a sequence of bytes from the current stream and advances the position
		/// within the stream by the number of bytes read.
		/// </summary>
		/// <param name="buffer">An array of values to be read from the stream.</param>
		/// <param name="offset">The zero-based byte offset in buffer at which to begin storing
		/// the data read from the current stream.</param>
		/// <param name="count">The maximum number of bytes to be read from the current stream.</param>
		/// <exception cref="NotSupportedException">This stream does not support reading.</exception>
		/// <exception cref="ArgumentNullException"><i>buffer</i> is a null reference.</exception>
		/// <exception cref="ArgumentOutOfRangeException"><i>offset</i> or <i>count</i> leads outside the bounds of <i>buffer</i>.</exception>
		virtual int Read( array<System::Byte>^ buffer, int offset, int count ) override;

		/// <summary>
		/// Reads an array of values from the current stream, and advances the current position
		/// within this stream by the number of bytes written.
		/// </summary>
		/// <returns>An array of values that was read from the current stream.</returns> 
		/// <exception cref="NotSupportedException">This stream does not support reading.</exception>
		/// <exception cref="ArgumentOutOfRangeException"><i>count</i> is less than zero.</exception>
		generic<typename T> where T : value class
		array<T>^ ReadRange( int count );

		/// <summary>
		/// Not supported.
		/// </summary>
		/// <exception cref="NotSupportedException">Always thrown.</exception>
		virtual void Flush() override;

		/// <summary>
		/// Not supported.
		/// </summary>
		/// <param name="value">Always ignored.</param>
		/// <exception cref="NotSupportedException">Always thrown.</exception>
		virtual void SetLength( System::Int64 value ) override;

		/// <summary>Gets a value indicating whether the current stream supports reading.</summary>
		/// <value><c>true</c> if the stream supports reading; <c>false</c> otherwise.</value>
		property bool CanRead
		{
			virtual bool get() override { return m_CanRead; }
		}

		/// <summary>Gets a value indicating whether the current stream supports seeking.</summary>
		/// <value>Always <c>true</c>.</value>
		property bool CanSeek
		{
			virtual bool get() override { return true; }
		}

		/// <summary>Gets a value indicating whether the current stream supports writing.</summary>
		/// <value><c>true</c> if the stream supports writing; <c>false</c> otherwise.</value>
		property bool CanWrite
		{
			virtual bool get() override { return m_CanWrite; }
		}

		/// <summary>Gets the length in bytes of the stream.</summary>
		/// <value>A long value representing the length of the stream in bytes.</value>
		property System::Int64 Length
		{
			virtual System::Int64 get() override;
		}

		/// <summary>Gets or sets the position within the current stream.</summary>
		/// <value>The current position within the stream.</value>
		/// <seealso cref="Stream">Stream Class</seealso>
		property System::Int64 Position
		{
			virtual System::Int64 get() override;
			virtual void set( System::Int64 ) override;
		}

		/// <summary>Gets the internal pointer to the current stream's backing store.</summary>
		/// <value>An IntPtr to the buffer being used as a backing store.</value>
		property System::IntPtr DataPointer
		{
			System::IntPtr get() { return System::IntPtr( m_Buffer ); }
		}
	};
}
