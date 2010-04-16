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
#include "CueProperties.h"
#include "Enums.h"
#include "Cue.h"

using namespace System;
using namespace System::IO;

namespace SlimDX
{
	namespace XACT3
	{
		/// <summary>
		/// Instantiate and manipulate XACT sound bank objects.
		/// </summary>
		/// <unmanaged>IXACT3SoundBank</unmanaged>
		public ref class SoundBank
		{
		private:
			IXACT3SoundBank* InternalPointer;

		public:
			/// <summary>
			/// Get a sound cue index based on a <see cref="String"/> that represents the friendly name of the cue.
			/// </summary>
			/// <param name="friendlyName">A <see cref="String"/> that contains the friendly name of the cue.</param>
			/// <returns>The index for the cue if it exists, otherwise -1.</returns>
			/// <unmanaged>IXACT3SoundBank::GetCueIndex</unmanaged>
			int GetCueIndex(String^ friendlyName);

			/// <summary>
			/// Get the number of sound cues in the sound bank.
			/// </summary>
			/// <unmanaged>IXACT3SoundBank::GetNumCues</unmanaged>
			property int CueCount { int get(); }

			/// <summary>
			/// Get the properties of a cue.
			/// </summary>
			/// <param name="cueIndex">The index of the cue to get the properties of.</param>
			/// <returns>A <see cref="CueProperties"/> object containing the properties of the cue.</returns>
			/// <unmanaged>IXACT3SoundBank::GetCueProperties</unmanaged>
			CueProperties^ GetCueProperties(int cueIndex);

			/// <summary>
			/// Prepare a cue for playback.
			/// </summary>
			/// <param name="cueIndex">The index of the cue to prepare.</param>
			/// <param name="timeOffset">The time offset into the cue to start from, in milliseconds.</param>
			/// <returns>A <see cref="Cue"/> object containing the newly prepared cue.</returns>
			/// <unmanaged>IXACT3SoundBank::Prepare</unmanaged>
			Cue^ Prepare(int cueIndex, int timeOffset);

			/// <summary>
			/// Play a cue.
			/// </summary>
			/// <param name="cueIndex">The index of the cue to play.</param>
			/// <param name="timeOffset">The time offset into the cue to start from, in milliseconds.</param>
			/// <returns>A <see cref="Cue"/> object containing the newly playing cue.</returns>
			/// <unmanaged>IXACT3SoundBank::Play</unmanaged>
			Cue^ Play(int cueIndex, int timeOffset);

			/// <summary>
			/// Stop playback of a cue.
			/// </summary>
			/// <param name="cueIndex">The index of the cue to stop.</param>
			/// <param name="flags"><see cref="StopFlags"/> that specify how the cue is stopped.</param>
			/// <unmanaged>IXACT3SoundBank::Stop</unmanaged>
			void Stop(int cueIndex, StopFlags flags);

			/// <summary>
			/// Get a <see cref="SoundBankState"/> value representing the current state of the sound bank.
			/// </summary>
			/// <unmanaged>IXACT3SoundBank::GetState</unmanaged>
			property SoundBankState State { SoundBankState get(); }
		};
	}
}
