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

#include "../Utilities.h"
#include "Enums.h"
#include "SoundBuffer.h"
#include "DirectSound.h"
#include "SoundBufferDescription.h"
#include "SoundEffectDescription.h"

namespace SlimDX
{
	namespace DirectSound
	{
		/// <summary>
		/// The SecondarySoundBuffer object is used to manage sound buffers and effects.
		/// </summary>
		public ref class SecondarySoundBuffer : public SoundBuffer
		{
		internal:
			property IDirectSoundBuffer8* DS8Pointer
			{
				IDirectSoundBuffer8* get() 
				{ 
					return m_DS8Pointer; 
				}
			}

			//While I believe the IDirectSoundBuffer can be safely cast to one of these, it's not
			//guaranteed to be safe to do so, so we'll just do the Right Thing (tm) and use QueryInterface
			//to get it and store it separately.
			IDirectSoundBuffer8* m_DS8Pointer;

			void SetDS8Pointer();

		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectSound::"/> class.
			/// </summary>
			/// <param name="dsound"></param>
			/// <param name="description"></param>
			/// <returns></returns>
			SecondarySoundBuffer( DirectSound^ dsound, SoundBufferDescription description );
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectSound::"/> class.
			/// </summary>
			/// <param name="filename"></param>
			/// <param name="dsound"></param>
			/// <returns></returns>
			SecondarySoundBuffer( System::String^ filename, DirectSound^ dsound );
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectSound::"/> class.
			/// </summary>
			/// <param name="filename"></param>
			/// <param name="dsound"></param>
			/// <param name="description"></param>
			/// <returns></returns>
			SecondarySoundBuffer( System::String^ filename, DirectSound^ dsound, SoundBufferDescription description );

			/// <summary>
			/// Releases all resources used by the <see cref="SlimDX::DirectSound::"/> class.
			/// </summary>
			~SecondarySoundBuffer();

			/// <summary>
			/// 
			/// </summary>
			/// <param name="effects"></param>
			/// <returns></returns>
			array<SoundEffectReturnValue>^ SetEffects( array<SoundEffectDescription>^ effects );
			/// <summary>
			/// 
			/// </summary>
			/// <param name="index"></param>
			/// <returns></returns>
			System::Object^ GetEffect( int index );
		};
	}
}