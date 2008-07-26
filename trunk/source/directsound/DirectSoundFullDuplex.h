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

#include "Enums.h"
#include "CaptureBuffer.h"
#include "SoundBufferDescription.h"
#include "CaptureBufferDescription.h"

namespace SlimDX
{
	namespace DirectSound
	{
		/// <summary>
		/// The DirectSoundFullDuplex object represents a full-duplex stream.
		/// </summary>
		public ref class DirectSoundFullDuplex : public ComObject
		{
			COMOBJECT(IDirectSoundFullDuplex, DirectSoundFullDuplex);

		public:
			/// <summary>
			/// Constructs a new instance of the <see cref="SlimDX::DirectSound::DirectSoundFullDuplex"/> class using the specified pointer to a
			/// previously constructed unmanaged object.
			/// </summary>
			/// <param name="pointer">The unmanaged IDirectSoundFullDuplex pointer.</param>
			/// <returns>The newly constructed object.</returns>
			static DirectSoundFullDuplex^ FromPointer( System::IntPtr pointer );

			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectSound::DirectSoundFullDuplex"/> class.
			/// </summary>
			/// <param name="captureDevice"></param>
			/// <param name="playbackDevice"></param>
			/// <param name="captureDesc"></param>
			/// <param name="bufferDesc"></param>
			/// <param name="windowHandle"></param>
			/// <param name="level"></param>
			/// <param name="captureBuffer"></param>
			/// <param name="secondaryBuffer"></param>
			DirectSoundFullDuplex( System::Guid captureDevice, System::Guid playbackDevice, CaptureBufferDescription captureDesc, 
								   SoundBufferDescription bufferDesc, System::IntPtr windowHandle, CooperativeLevel level, 
								   [Out] CaptureBuffer^% captureBuffer, [Out] SecondarySoundBuffer^% secondaryBuffer );

			/// <summary>
			/// Releases all resources used by the <see cref="SlimDX::DirectSound::DirectSoundFullDuplex"/> class.
			/// </summary>
			~DirectSoundFullDuplex();
		};
	}
}