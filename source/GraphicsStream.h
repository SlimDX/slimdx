#pragma once

using namespace System;
using namespace System::IO;

namespace SlimDX
{
	public ref class GraphicsStream : public Stream
	{
	private:
		initonly char* m_Buffer;
		Int64 m_Position;

		initonly bool m_CanRead;
		initonly bool m_CanWrite;

	internal:
		GraphicsStream( void* buffer, bool canRead, bool canWrite );

	public:
		virtual void Close() override;
		virtual Int64 Seek( Int64 offset, SeekOrigin origin ) override;

		//Write functions
		virtual void Write( array<Byte>^ buffer, int offset, int count ) override;

		generic<typename T> where T : value class
		void Write( T value );

		generic<typename T> where T : value class
		void Write( array<T>^ data, int startIndex, int count );

		generic<typename T> where T : value class
		void Write( array<T>^ data ) { Write( data, 0, 0 ); }

		//TODO: Write all the read functions
		virtual int Read( array<Byte>^ buffer, int offset, int count ) override { return 0; }
		/*T Read();
		void Read( array<T>^ buffer, int count, int writeOffset );
		array<T>^ Read( int count );*/

		virtual void Flush() override
		{
			throw gcnew NotSupportedException();
		}

		virtual void SetLength( Int64 value ) override
		{
			throw gcnew NotSupportedException();
		}

		property bool CanRead
		{
			virtual bool get() override { return m_CanRead; }
		}

		property bool CanSeek
		{
			virtual bool get() override { return true; }
		}

		property bool CanWrite
		{
			virtual bool get() override { return m_CanWrite; }
		}

		property Int64 Length
		{
			virtual Int64 get() override { throw gcnew NotSupportedException(); }
		}

		property Int64 Position
		{
			virtual Int64 get() override
			{
				return m_Position;
			}

			virtual void set( Int64 value ) override
			{
				Seek( value, SeekOrigin::Begin );
			}
		}
	};
}
