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

#include <dsound.h>

#include "../ComObject.h"
#include "../Utilities.h"
#include "../DataStream.h"
#include "../WaveFormat.h"

#include "Enums.h"
#include "ResultCode.h"
#include "DirectSoundCapture.h"
#include "CaptureBufferDescription.h"

namespace SlimDX
{
	namespace DirectSound
	{
		/// <summary>
		/// The CaptureBuffer object is used to manipulate sound capture buffers.
		/// </summary>
		public ref class CaptureBuffer : public ComObject
		{
			COMOBJECT(IDirectSoundCaptureBuffer8, CaptureBuffer);

		private:
			DataStream^ Lock( int offset, int sizeBytes, bool lockEntireBuffer, [Out] DataStream^% secondPart );
			void Unlock( DataStream^ firstPart, DataStream^ secondPart );

		public:
			/// <summary>
			/// Constructs a new instance of the <see cref="SlimDX::DirectSound::CaptureBuffer"/> class using the specified pointer to a
			/// previously constructed unmanaged object.
			/// </summary>
			/// <param name="pointer">The unmanaged IDirectSoundCaptureBuffer8 pointer.</param>
			/// <returns>The newly constructed object.</returns>
			static CaptureBuffer^ FromPointer( System::IntPtr pointer );

			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectSound::CaptureBuffer"/> class.
			/// </summary>
			/// <param name="capture"></param>
			/// <param name="description"></param>
			CaptureBuffer( DirectSoundCapture^ capture, CaptureBufferDescription description );
			/// <summary>
			/// Releases all resources used by the <see cref="SlimDX::DirectSound::CaptureBuffer"/> class.
			/// </summary>
			~CaptureBuffer();

			/// <summary>
			/// Retrieves an effect object associated with the buffer.
			/// </summary>
			/// <param name="index"></param>
			/// <returns></returns>
			System::Object^ GetEffect( int index );
			/// <summary>
			/// Retrieves the status of capture effects.
			/// </summary>
			/// <param name="effectCount"></param>
			/// <returns></returns>
			array<CaptureEffectReturnValue>^ GetEffectStatus( int effectCount );

			/// <summary>
			/// Reads data from the capture buffer.
			/// </summary>
			/// <param name="offset"></param>
			/// <param name="sizeBytes"></param>
			/// <param name="lockEntireBuffer"></param>
			/// <returns></returns>
			array<unsigned char>^ Read( int offset, int sizeBytes, bool lockEntireBuffer );
			/// <summary>
			/// Write data to the capture buffer.
			/// </summary>
			/// <param name="data"></param>
			/// <param name="offset"></param>
			/// <param name="lockEntireBuffer"></param>
			/// <returns></returns>
			void Write( array<unsigned char>^ data, int offset, bool lockEntireBuffer );

			/// <summary>
			/// Begins capturing data into the buffer. If the buffer is already capturing, the method has no effect.
			/// </summary>
			void Start( bool looping );
			/// <summary>
			/// Stops the buffer so that it is no longer capturing data. If the buffer is not capturing, the method has no effect.
			/// </summary>
			void Stop();

			/// <summary>
			/// True if the buffer is currently capturing.
			/// </summary>
			property bool Capturing
			{
				bool get();
			}

			/// <summary>
			/// True if the capture buffer is looping.
			/// </summary>
			property bool Looping
			{
				bool get();
			}

			/// <summary>
			/// Retrieves the waveform format of the capture buffer.
			/// </summary>
			property WaveFormat^ Format
			{
				WaveFormat^ get();
			}

			/// <summary>
			/// The size, in bytes, of the capture buffer.
			/// </summary>
			property int SizeInBytes
			{
				int get();
			}

			/// <summary>
			/// True if the buffer wave mapped.
			/// </summary>
			property bool WaveMapped
			{
				bool get();
			}

			/// <summary>
			/// Retrieves the position of the capture cursor in the buffer. The capture cursor is ahead of the read cursor. The data after the read position up to and including the capture position is not necessarily valid data.
			/// </summary>
			property int CurrentCapturePosition
			{
				int get();
			}

			/// <summary>
			/// Retrieves the position of the read cursor in the buffer. The capture cursor is ahead of the read cursor. The data after the read position up to and including the capture position is not necessarily valid data.
			/// </summary>
			property int CurrentReadPosition
			{
				int get();
			}
		};
	}
}