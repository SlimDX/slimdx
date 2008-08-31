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

#include "WaveFormat.h"
#include "WaveFormatExtensible.h"

namespace SlimDX
{
	namespace Multimedia
	{
		public ref class WaveFile : System::IDisposable
		{
		private:
			int size;
			WaveFormat^ format;
			System::IO::FileAccess access;

			HMMIO fileHandle;
			MMCKINFO *fileInfo;
			MMCKINFO *dataChunk;
			MMIOINFO *outputInfo;

			void Construct( System::String^ fileName, WaveFormat^ format, System::IO::FileAccess access );
			void Destruct();
			void Close();

			void ReadHeader();
			void WriteHeader( WaveFormat^ format );

		public:
			WaveFile( System::String^ fileName, WaveFormat^ format, System::IO::FileAccess access );
			WaveFile( System::String^ fileName );
			~WaveFile() { Destruct(); }
			!WaveFile() { Destruct(); }

			void Reset();

			int Read( array<System::Byte>^ buffer, int length );
			int Write( array<System::Byte>^ buffer, int length );

			property int Size
			{
				int get() { return size; }
			}

			property WaveFormat^ Format
			{
				WaveFormat^ get() { return format; }
			}
		};
	}
}