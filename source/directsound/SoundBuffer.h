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
#include "../AudioEnums.h"
#include "../WaveFormat.h"

#include "Enums.h"
#include "DirectSound.h"
#include "SoundBufferDescription.h"
#include "SoundEffectDescription.h"
#include "BufferCapabilities.h"

namespace SlimDX
{
	namespace DirectSound
	{
		/// <summary>
		/// The SoundBuffer object is used to manage sound buffers.
		/// </summary>
		public ref class SoundBuffer : public ComObject
		{
			COMOBJECT(IDirectSoundBuffer, SoundBuffer);

		protected:
			DataStream^ Lock( int offset, int sizeBytes, LockFlags flags, [Out] DataStream^% secondPart );
			void Unlock( DataStream^ firstPart, DataStream^ secondPart );

			bool notVirtualized;

		public:
			/// <summary>
			/// Constructs a new instance of the <see cref="SlimDX::DirectSound::SoundBuffer"/> class using the specified pointer to a
			/// previously constructed unmanaged object.
			/// </summary>
			/// <param name="pointer">The unmanaged IDirectSoundBuffer pointer.</param>
			/// <returns>The newly constructed object.</returns>
			static SoundBuffer^ FromPointer( System::IntPtr pointer );

			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectSound::SoundBuffer"/> class.
			/// </summary>
			/// <param name="dsound"></param>
			/// <param name="description"></param>
			/// <returns></returns>
			SoundBuffer( DirectSound^ dsound, SoundBufferDescription description );
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectSound::SoundBuffer"/> class.
			/// </summary>
			/// <param name="filename"></param>
			/// <param name="dsound"></param>
			/// <returns></returns>
			SoundBuffer( System::String^ filename, DirectSound^ dsound );
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectSound::SoundBuffer"/> class.
			/// </summary>
			/// <param name="filename"></param>
			/// <param name="dsound"></param>
			/// <param name="description"></param>
			/// <returns></returns>
			SoundBuffer( System::String^ filename, DirectSound^ dsound, SoundBufferDescription description );

			/// <summary>
			/// Releases all resources used by the <see cref="SlimDX::DirectSound::SoundBuffer"/> class.
			/// </summary>
			~SoundBuffer();

			/// <summary>
			/// Restores the memory allocation for a lost sound buffer.
			/// </summary>
			void Restore();

			/// <summary>
			/// Causes the sound buffer to play, starting at the play cursor.
			/// </summary>
			void Play( int priority, PlayFlags flags );

			/// <summary>
			/// Causes the sound buffer to stop playing.
			/// </summary>
			void Stop();

			/// <summary>
			/// Reads the current data in the buffer.
			/// </summary>
			/// <returns></returns>
			array<unsigned char>^ Read( int offset, int sizeBytes, LockFlags flags );

			/// <summary>
			/// Writes data to the buffer.
			/// </summary>
			/// <returns></returns>
			void Write( array<unsigned char>^ data, int offset, LockFlags flags );

			/// <summary>
			/// Sets a description of the sound data format in the buffer.
			/// </summary>
			void SetFormat( WaveFormat^ format );

			/// <summary>
			/// Retrieves a description of the sound data format in the buffer.
			/// </summary>
			/// <returns></returns>
			WaveFormat^ GetFormat();

			/// <summary>
			/// Retrieves the position of the write cursor in the sound buffer.
			/// </summary>
			property int CurrentWritePosition
			{
				int get();
			}

			/// <summary>
			/// Retrieves or sets the position of the play cursor.
			/// </summary>
			property int CurrentPlayPosition
			{
				int get();
				void set( int value );
			}

			/// <summary>
			/// Retrieves or sets the frequency, in samples per second, at which the buffer is playing.
			/// </summary>
			property int Frequency
			{
				int get();
				void set( int value );
			}

			/// <summary>
			/// Retrieves or sets the attenuation of the sound.
			/// </summary>
			property int Volume
			{
				int get();
				void set( int value );
			}

			/// <summary>
			/// Retrieves or sets the relative volume of the left and right audio channels.
			/// </summary>
			property int Pan
			{
				int get();
				void set( int value );
			}

			/// <summary>
			/// Retrieves the status of the sound buffer.
			/// </summary>
			property BufferStatus Status
			{
				BufferStatus get();
			}

			/// <summary>
			/// True if a requested 3D algorithm was not available and stereo panning was substituted.
			/// </summary>
			property bool NoVirtualization
			{
				bool get();
			}

			/// <summary>
			/// Retrieves the capabilities of the buffer object.
			/// </summary>
			property BufferCapabilities Capabilities
			{
				BufferCapabilities get();
			}
		};
	}
}