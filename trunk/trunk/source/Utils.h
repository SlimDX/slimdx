#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Diagnostics;

namespace SlimDX
{
	ref class Utils sealed
	{
	public:
		static void ReportNotDisposed( Object^ obj )
		{
			String^ message = String::Format( "Object of type {0} not disposed.", obj->GetType()->ToString() );
			Debug::WriteLine( message );
		}

		static void MarkDisposed( bool %disposed, Object^ obj )
		{
			if( disposed )
				throw gcnew ObjectDisposedException( obj->GetType()->ToString() );

			disposed = true;
			GC::SuppressFinalize( obj );
		}

		static array<Byte>^ ReadStream( Stream^ stream, int readLength )
		{
			if( stream == nullptr )
				throw gcnew ArgumentNullException( "stream" );
			if( !stream->CanRead )
				throw gcnew NotSupportedException();

			if( readLength == 0 )
				readLength = (int) ( stream->Length - stream->Position );
			if( readLength < 0 )
				throw gcnew ArgumentOutOfRangeException( "readLength" );
			if( readLength == 0 )
				return gcnew array<Byte>( 0 );

			array<Byte>^ buffer = gcnew array<Byte>( readLength ); 
			int bytesRead = 0;

			while( bytesRead < readLength )
			{
				bytesRead += stream->Read( buffer, bytesRead, readLength - bytesRead );
			}

			return buffer;
		}
	};
}
