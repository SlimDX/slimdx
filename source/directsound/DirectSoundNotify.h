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

#include "CaptureBuffer.h"
#include "SoundBuffer.h"
#include "SecondarySoundBuffer.h"
#include "BufferPositionNotify.h"

namespace SlimDX
{
	namespace DirectSound
	{
		/// <summary>
		/// The DirectSoundNotify object sets up notification events for a playback or capture buffer.
		/// </summary>
		public ref class DirectSoundNotify : public ComObject
		{
			COMOBJECT(IDirectSoundNotify, DirectSoundNotify);
		
		public:
			/// <summary>
			/// Constructs a new instance of the <see cref="SlimDX::DirectSound::DirectSoundNotify"/> class using the specified pointer to a
			/// previously constructed unmanaged object.
			/// </summary>
			/// <param name="pointer">The unmanaged IDirectSoundNotify pointer.</param>
			/// <returns>The newly constructed object.</returns>
			static DirectSoundNotify^ FromPointer( System::IntPtr pointer );

			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectSound::DirectSoundNotify"/> class.
			/// with a previously created sound buffer.
			/// </summary>
			/// <param name="pointer">The SoundBuffer object.</param>
			DirectSoundNotify( SoundBuffer^ soundBuffer );
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectSound::DirectSoundNotify"/> class.
			/// with a previously created secondary sound buffer.
			/// </summary>
			/// <param name="pointer">The SecondarySoundBuffer object.</param>
			DirectSoundNotify( SecondarySoundBuffer^ secondaryBuffer );
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectSound::DirectSoundNotify"/> class.
			/// with a previously created capture buffer.
			/// </summary>
			/// <param name="pointer">The CaptureBuffer object.</param>
			DirectSoundNotify( CaptureBuffer^ captureBuffer );
			/// <summary>
			/// Releases all resources used by the <see cref="SlimDX::DirectSound::DirectSoundNotify"/> class.
			/// </summary>
			~DirectSoundNotify();

			/// <summary>
			/// Sets the notification positions. 
			/// During capture or playback, whenever the read or play cursor reaches one of the specified offsets, the associated event is signaled.
			/// </summary>
			/// <param name="notifications"></param>
			/// <param name="notifyCount"></param>
			void SetNotificationPositions( array<BufferPositionNotify>^ notifications, int notifyCount );
		};
	}
}