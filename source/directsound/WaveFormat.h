/*
* Copyright (c) 2007 SlimDX Group
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

using namespace System;

#include "Enums.h"
#include <mmreg.h>

namespace SlimDX
{
	ref class DataStream;

	namespace DirectSound
	{
		public ref class WaveFormatEx
		{
		protected:
			WAVEFORMATEX* m_Format;
			DataStream^ m_ExtraData;

			void InitializeMe( bool extensible, int extraDataBytes );
			WaveFormatEx( bool extensible, int extraDataBytes );

		internal:
			property WAVEFORMATEX* InternalPointer
			{
				WAVEFORMATEX* get() { return m_Format; }
			}

		public:
			WaveFormatEx();
			WaveFormatEx( int extraDataBytes );
			WaveFormatEx( WAVEFORMATEX* format );
			~WaveFormatEx();
			!WaveFormatEx();

			property WaveFormat FormatTag
			{
				WaveFormat get() { return (WaveFormat) m_Format->wFormatTag; }
				void set( WaveFormat value ) { m_Format->wFormatTag = (WORD) value; }
			}

			property short Channels
			{
				short get() { return m_Format->nChannels; }
				void set( short value ) { m_Format->nChannels = value; }
			}

			property int SamplesPerSecond
			{
				int get() { return m_Format->nSamplesPerSec; }
				void set( int value ) { m_Format->nSamplesPerSec = value; }
			}

			property int AverageBytesPerSecond
			{
				int get() { return m_Format->nAvgBytesPerSec; }
				void set( int value ) { m_Format->nAvgBytesPerSec = value; }
			}

			property short BlockAlign
			{
				short get() { return m_Format->nBlockAlign; }
				void set( short value ) { m_Format->nBlockAlign = value; }
			}

			property short BitsPerSample
			{
				short get() { return m_Format->wBitsPerSample; }
				void set( short value ) { m_Format->wBitsPerSample = value; }
			}

			property DataStream^ ExtraData
			{
				DataStream^ get() { return m_ExtraData; }
			}
		};

		public ref class WaveFormatExtensible sealed : public WaveFormatEx
		{
		internal:
			property WAVEFORMATEXTENSIBLE* ExtensiblePointer
			{
				WAVEFORMATEXTENSIBLE* get() { return (WAVEFORMATEXTENSIBLE*) m_Format; }
			}

		public:
			WaveFormatExtensible();
			WaveFormatExtensible( int extraDataBytes );
			WaveFormatExtensible( WAVEFORMATEXTENSIBLE* format );

			//these properties are all the same field
			property short ValidBitsPerSample
			{
				short get() { return ExtensiblePointer->Samples.wValidBitsPerSample; }
				void set( short value ) { ExtensiblePointer->Samples.wValidBitsPerSample = value; }
			}

			property short SamplesPerBlock
			{
				short get() { return ExtensiblePointer->Samples.wSamplesPerBlock; }
				void set( short value ) { ExtensiblePointer->Samples.wSamplesPerBlock = value; }
			}

			property Speaker ChannelMask
			{
				Speaker get() { return (Speaker) ExtensiblePointer->dwChannelMask; }
				void set( Speaker value ) { ExtensiblePointer->dwChannelMask = (DWORD) value; }
			}

			property Guid SubFormat
			{
				Guid get();
				void set( Guid value );
			}
		};
	}
}