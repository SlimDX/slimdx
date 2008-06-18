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

#include <windows.h>
#include <vcclr.h>
#include <xaudio2.h>

#include "WaveFile.h"

using namespace System;
using namespace System::IO;

namespace SlimDX
{
	WaveFile::WaveFile( String^ fileName, WaveFormat^ format, FileAccess access )
	{
		Construct( fileName, format, access );
	}

	WaveFile::WaveFile( String^ fileName )
	{
		Construct( fileName, nullptr, FileAccess::Read );
	}

	void WaveFile::Construct( String^ fileName, WaveFormat^ format, FileAccess access )
	{
		fileHandle = NULL;
		fileInfo = NULL;
		this->access = access;

		if( String::IsNullOrEmpty( fileName ) )
			throw gcnew ArgumentNullException( "fileName" );

		if( format == nullptr && access != FileAccess::Read )
			throw gcnew ArgumentNullException( "format" );

		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		DWORD flags = MMIO_ALLOCBUF;
		if( access == FileAccess::Read )
			flags |= MMIO_READ;
		else
			flags |= MMIO_READWRITE | MMIO_CREATE;

		fileHandle = mmioOpen( const_cast<LPWSTR>( reinterpret_cast<LPCWSTR>( pinnedName ) ), NULL, flags );
		if( fileHandle == NULL )
			throw gcnew System::IO::FileLoadException( "Could not open the file", fileName );

		if( access == FileAccess::Read )
			ReadHeader();
		else
			WriteHeader( format );

		Reset();

		size = dataChunk->cksize;
	}

	void WaveFile::Destruct()
	{
		if( fileHandle != NULL )
			Close();

		if( fileInfo != NULL )
			delete fileInfo;

		if( dataChunk != NULL )
			delete dataChunk;

		if( outputInfo != NULL )
			delete outputInfo;

		outputInfo = NULL;
		dataChunk = NULL;
		fileHandle = NULL;
		fileInfo = NULL;
		size = 0;
		format = nullptr;
	}

	void WaveFile::ReadHeader()
	{
		MMCKINFO temp;
		PCMWAVEFORMAT pcmFormat;
		fileInfo = new MMCKINFO();

		if( mmioDescend( fileHandle, fileInfo, NULL, 0 ) != 0 )
			throw gcnew InvalidDataException( "Invalid wave file." );

		if( fileInfo->ckid != FOURCC_RIFF ||
			fileInfo->fccType != mmioFOURCC( 'W', 'A', 'V', 'E' ) )
			throw gcnew InvalidDataException( "Invalid wave file." );

		temp.ckid = mmioFOURCC( 'f', 'm', 't', ' ' );
		if( mmioDescend( fileHandle, &temp, fileInfo, MMIO_FINDCHUNK ) != 0 )
			throw gcnew InvalidDataException( "Invalid wave file." );

		if( temp.cksize < static_cast<LONG>( sizeof( PCMWAVEFORMAT ) ) )
			throw gcnew InvalidDataException( "Invalid wave file." );

		if( mmioRead( fileHandle, reinterpret_cast<HPSTR>( &pcmFormat ), sizeof( pcmFormat ) ) != sizeof( pcmFormat ) )
			throw gcnew InvalidDataException( "Invalid wave file." );

		if( pcmFormat.wf.wFormatTag == WAVE_FORMAT_PCM || pcmFormat.wf.wFormatTag == WAVE_FORMAT_IEEE_FLOAT )
		{
			WAVEFORMATEX *tempFormat = reinterpret_cast<WAVEFORMATEX*>( new BYTE[sizeof( WAVEFORMATEX )] );
			memcpy( tempFormat, &pcmFormat, sizeof( pcmFormat ) );
			tempFormat->cbSize = 0;

			format = WaveFormat::FromUnmanaged( *tempFormat );
			delete[] tempFormat;
		}
		else
		{
			WORD extraBytes = 0;
			if( mmioRead( fileHandle, reinterpret_cast<CHAR*>( &extraBytes ), sizeof( WORD ) ) != sizeof( WORD ) )
				throw gcnew InvalidDataException( "Invalid wave file." );

			WAVEFORMATEX *tempFormat = reinterpret_cast<WAVEFORMATEX*>( new BYTE[sizeof( WAVEFORMATEX ) + extraBytes] );
			memcpy( tempFormat, &pcmFormat, sizeof( pcmFormat ) );
			tempFormat->cbSize = extraBytes;

			if( mmioRead( fileHandle, reinterpret_cast<CHAR*>( reinterpret_cast<BYTE*>( &tempFormat->cbSize ) + sizeof( WORD ) ), extraBytes ) != extraBytes )
			{
				delete[] tempFormat;
				throw gcnew InvalidDataException( "Invalid wave file." );
			}

			// TODO: Add support for ADPCM and XMA2 formats
			if( pcmFormat.wf.wFormatTag == WAVE_FORMAT_ADPCM )
				throw gcnew NotSupportedException( "The ADPCM format is not supported at this time." );
			else if( pcmFormat.wf.wFormatTag == WAVE_FORMAT_XMA2 )
				throw gcnew NotSupportedException( "The XMA2 format is not supported at this time." );
			else
				format = WaveFormatExtensible::FromBase( tempFormat );

			delete[] tempFormat;
		}

		if( mmioAscend( fileHandle, &temp, 0 ) != 0 )
			throw gcnew InvalidDataException( "Invalid wave file." );
	}

	void WaveFile::Reset()
	{
		if( fileHandle == NULL || fileInfo == NULL )
			throw gcnew InvalidOperationException( "No wave file open." );

		if( dataChunk != NULL )
			delete dataChunk;
		dataChunk = new MMCKINFO();
		dataChunk->ckid = mmioFOURCC( 'd', 'a', 't', 'a' );

		if( outputInfo != NULL )
			delete outputInfo;
		outputInfo = new MMIOINFO();

		if( access == FileAccess::Read )
		{
			if( mmioSeek( fileHandle, fileInfo->dwDataOffset + sizeof( FOURCC ), SEEK_SET ) == -1 )
				throw gcnew InvalidDataException( "Invalid wave file." );

			if( mmioDescend( fileHandle, dataChunk, fileInfo, MMIO_FINDCHUNK ) != 0 )
				throw gcnew InvalidDataException( "Invalid wave file." );
		}
		else
		{
			dataChunk->cksize = 0;

			if( mmioCreateChunk( fileHandle, dataChunk, 0 ) != 0 )
				throw gcnew InvalidDataException( "Invalid wave file." );

			if( mmioGetInfo( fileHandle, outputInfo, 0 ) != 0 )
				throw gcnew InvalidDataException( "Invalid wave file." );
		}
	}

	int WaveFile::Read( array<Byte>^ buffer, int length )
	{
		if( fileHandle == NULL || dataChunk == NULL )
			throw gcnew InvalidOperationException( "No wave file open." );

		if( buffer == nullptr )
			throw gcnew ArgumentNullException( "buffer" );
		if( length <= 0 )
			throw gcnew ArgumentOutOfRangeException( "length", length, "Length to read must be greater than zero." );

		MMIOINFO info;
		pin_ptr<Byte> pinnedBuffer = &buffer[0];

		if( mmioGetInfo( fileHandle, &info, 0 ) != 0 )
			throw gcnew InvalidDataException( "Invalid wave file." );

		DWORD dataIn = length;
		if( dataIn > dataChunk->cksize )
			dataIn = dataChunk->cksize;

		dataChunk->cksize -= dataIn;

		for( DWORD i = 0; i < dataIn; i++ )
		{
			if( info.pchNext == info.pchEndRead )
			{
				if( mmioAdvance( fileHandle, &info, MMIO_READ ) != 0 )
					throw gcnew InvalidDataException( "Invalid wave file." );

				if( info.pchNext == info.pchEndRead )
					throw gcnew InvalidDataException( "Invalid wave file." );
			}

			*( reinterpret_cast<BYTE*>( pinnedBuffer ) + i ) = *( reinterpret_cast<BYTE*>( info.pchNext ) );
			info.pchNext++;
		}

		if( mmioSetInfo( fileHandle, &info, 0 ) != 0 )
			throw gcnew InvalidDataException( "Invalid wave file." );

		return dataIn;
	}

	void WaveFile::Close()
	{
		if( access == FileAccess::Read )
			mmioClose( fileHandle, 0 );
		else
		{
			if( outputInfo == NULL || dataChunk == NULL || fileInfo == NULL )
				throw gcnew InvalidDataException( "Invalid wave file." );

			outputInfo->dwFlags |= MMIO_DIRTY;

			if( mmioSetInfo( fileHandle, outputInfo, 0 ) != 0 )
				throw gcnew InvalidDataException( "Invalid wave file." );

			if( mmioAscend( fileHandle, dataChunk, 0 ) != 0 )
				throw gcnew InvalidDataException( "Invalid wave file." );

			if( mmioAscend( fileHandle, fileInfo, 0 ) != 0 )
				throw gcnew InvalidDataException( "Invalid wave file." );

			mmioSeek( fileHandle, 0, SEEK_SET );

			if( mmioDescend( fileHandle, fileInfo, NULL, 0 ) != 0 )
				throw gcnew InvalidDataException( "Invalid wave file." );

			dataChunk->ckid = mmioFOURCC( 'f', 'a', 'c', 't' );

			if( mmioDescend( fileHandle, dataChunk, fileInfo, MMIO_FINDCHUNK ) == 0 )
			{
				DWORD samples = 0;
				mmioWrite( fileHandle, reinterpret_cast<HPSTR>( &samples ), sizeof( DWORD ) );
				mmioAscend( fileHandle, dataChunk, 0 );
			}

			if( mmioAscend( fileHandle, fileInfo, 0 ) != 0 )
				throw gcnew InvalidDataException( "Invalid wave file." );

			mmioClose( fileHandle, 0 );
		}
	}

	void WaveFile::WriteHeader( WaveFormat^ format )
	{
		this->format = format;

		fileInfo = new MMCKINFO();
		fileInfo->fccType = mmioFOURCC( 'W', 'A', 'V', 'E' );
		fileInfo->cksize = 0;

		if( mmioCreateChunk( fileHandle, fileInfo, MMIO_CREATERIFF ) != 0 )
			throw gcnew InvalidDataException( "Invalid wave file." );

		dataChunk = new MMCKINFO();
		dataChunk->ckid = mmioFOURCC( 'f', 'm', 't', ' ' );
		dataChunk->cksize = sizeof( PCMWAVEFORMAT );

		if( mmioCreateChunk( fileHandle, dataChunk, 0 ) != 0 )
			throw gcnew InvalidDataException( "Invalid wave file." );

		std::auto_ptr<WAVEFORMATEX> fmtPtr = WaveFormat::ToUnmanaged( format );

		if( format->FormatTag == WaveFormatTag::Pcm )
		{
			if( mmioWrite( fileHandle, reinterpret_cast<HPSTR>( fmtPtr.get() ), sizeof( PCMWAVEFORMAT ) ) != sizeof( PCMWAVEFORMAT ) )
				throw gcnew InvalidDataException( "Invalid wave file." );
		}
		else
		{
			int size = sizeof( *fmtPtr ) + fmtPtr->cbSize;
			if( mmioWrite( fileHandle, reinterpret_cast<HPSTR>( fmtPtr.get() ), size ) != size )
				throw gcnew InvalidDataException( "Invalid wave file." );
		}

		if( mmioAscend( fileHandle, dataChunk, 0 ) != 0 )
			throw gcnew InvalidDataException( "Invalid wave file." );

		MMCKINFO fact;
		DWORD factData = static_cast<DWORD>( -1 );
		fact.ckid = mmioFOURCC( 'f', 'a', 'c', 't' );
		fact.cksize = 0;

		if( mmioCreateChunk( fileHandle, &fact, 0 ) != 0 )
			throw gcnew InvalidDataException( "Invalid wave file." );

		if( mmioWrite( fileHandle, reinterpret_cast<HPSTR>( &factData ), sizeof( factData ) ) != sizeof( factData ) )
			throw gcnew InvalidDataException( "Invalid wave file." );

		if( mmioAscend( fileHandle, &fact, 0 ) != 0 )
			throw gcnew InvalidDataException( "Invalid wave file." );
	}

	int WaveFile::Write( array<Byte>^ buffer, int length )
	{
		if( fileHandle == NULL || outputInfo == NULL )
			throw gcnew InvalidOperationException( "No wave file open." );

		if( buffer == nullptr )
			throw gcnew ArgumentNullException( "buffer" );
		if( length <= 0 )
			throw gcnew ArgumentOutOfRangeException( "length", length, "Length to read must be greater than zero." );
	
		int written = 0;
		pin_ptr<Byte> pinnedBuffer = &buffer[0];

		for( int i = 0; i < length; i++ )
		{
			if( outputInfo->pchNext == outputInfo->pchEndWrite )
			{
				outputInfo->dwFlags |= MMIO_DIRTY;
				if( mmioAdvance( fileHandle, outputInfo, MMIO_WRITE ) != 0 )
					throw gcnew InvalidDataException( "Invalid wave file." );
			}

			*( reinterpret_cast<BYTE*>( outputInfo->pchNext ) ) = *( reinterpret_cast<BYTE*>( pinnedBuffer ) + i );
			outputInfo->pchNext++;

			written++;
		}

		return written;
	}
}