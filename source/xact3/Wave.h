/*
* Copyright (c) 2007-2010 SlimDX Group
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

#include "Engine.h"
#include "Enums.h"
#include "WaveInstanceProperties.h"

namespace SlimDX
{
	namespace XACT3
	{
		public ref class Wave
		{
		private:
			IXACT3Wave* InternalPointer;

		public:
			/// <summary>
			/// Play the wave.
			/// </summary>
			/// <unmanaged>IXACT3Wave::Play</unmanaged>
			void Play();

			/// <summary>
			/// Stop the wave.
			/// </summary>
			/// <param name="flags"><see cref="StopFlags"/> that specify how the wave is stopped.</param>
			/// <unmanaged>IXACT3Wave::Stop</unmanaged>
			void Stop(StopFlags flags);

			/// <summary>
			/// Pause playback of the wave.
			/// </summary>
			/// <param name="pause">The action to take. If true, playback is paused, if false, playback is resumed.</param>
			/// <unmanaged>IXACT3Wave::Pause</unmanaged>
			void Pause(bool pause);

			/// <summary>
			/// Get a <see cref="WaveState"/> value representing the current state of the wave.
			/// </summary>
			/// <unmanaged>IXACT3Wave::GetState</unmanaged>
			property WaveState State { WaveState get(); }

			/// <summary>
			/// Set the pitch of the wave.
			/// </summary>
			/// <param name="pitch">The value that is used to set the pitch for playback of this wave. This value may be between -1200 and 1200, which is approximately one semitone.</param>
			/// <unmanaged>IXACT3Wave::SetPitch</unmanaged>
			void SetPitch(short pitch);

			/// <summary>
			/// Set the volume of the wave.
			/// </summary>
			/// <param name="volume">The volume level to set.</param>
			/// <unmanaged>IXACT3Wave::SetVolume</unmanaged>
			void SetVolume(float volume);

			/// <summary>
			/// Sets the volume level that each source channel of the wave should play in each of its destination channels.
			/// </summary>
			/// <param name="srcChannelCount">Number of source channels. This must equal the number of emitter channels.</param>
			/// <param name="dstChannelCount">Number of destination channels. This must equal the number of final mix channels.</param>
			/// <param name="matrixCoefficients">Matrix coefficient table. This is an array that represents the volume level of each source channel present in each destination channel. The source channels are the column index and the destination channels are the row index of the table. The table must have at least <paramref name="srcChannelCount"/> * <paramref name="dstChannelCount"/> elements.</param>
			/// <unmanaged>IXACT3Wave::SetMatrixCoefficients</unmanaged>
			void SetMatrixCoefficients(int srcChannelCount, int dstChannelCount, array<float>^ matrixCoefficients);

			/// <summary>
			/// Gets a <see cref="WaveInstanceProperties"/> object that contains the properties of the wave instance.
			/// </summary>
			/// <unmanaged>IXACT3Wave::GetProperties</unmanaged>
			property WaveInstanceProperties^ Properties { WaveInstanceProperties^ get(); }
		};
	}
}
