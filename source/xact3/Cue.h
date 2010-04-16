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
#include "CueInstanceProperties.h"

using namespace System;

namespace SlimDX
{
	namespace XACT3
	{
		ref class Engine;

		public ref class Cue
		{
		private:
			IXACT3Cue* InternalPointer;

		public:
			/// <summary>
			/// Play the cue.
			/// </summary>
			/// <unmanaged>IXACT3Cue::Play</unmanaged>
			void Play();

			/// <summary>
			/// Stop the cue.
			/// </summary>
			/// <param name="flags"><see cref="StopFlags"/> that specify how the cue is stopped.</param>
			/// <unmanaged>IXACT3Cue::Stop</unmanaged>
			void Stop(StopFlags flags);

			/// <summary>
			/// Get a <see cref="CueState"/> value representing the current state of the cue.
			/// </summary>
			/// <unmanaged>IXACT3Cue::GetState</unmanaged>
			property CueState State { CueState get(); }

			/// <summary>
			/// Sets the volume level that each source channel of the cue should play in each of its destination channels.
			/// </summary>
			/// <param name="srcChannelCount">Number of source channels. This must equal the number of emitter channels.</param>
			/// <param name="dstChannelCount">Number of destination channels. This must equal the number of final mix channels.</param>
			/// <param name="pMatrixCoefficients">Matrix coefficient table. This is an array that represents the volume level of each source channel present in each destination channel. The source channels are the column index and the destination channels are the row index of the table. The table must have at least <paramref name="srcChannelCount"/> * <paramref name="dstChannelCount"/> elements.</param>
			/// <unmanaged>IXACT3Cue::SetMatrixCoefficients</unmanaged>
			void SetMatrixCoefficients(int srcChannelCount, int dstChannelCount, array<float>^ pMatrixCoefficients);

			/// <summary>
			/// Get the corresponding index for a variable name string.
			/// </summary>
			/// <param name="friendlyName">A <see cref="String"/> that contains the friendly name of the variable.</param>
			/// <returns>The index for the variable if it exists, otherwise -1.</returns>
			/// <unmanaged>IXACT3Cue::GetVariableIndex</unmanaged>
			int GetVariableIndex(String^ friendlyName);

			/// <summary>
			/// Set the value of a variable.
			/// </summary>
			/// <param name="index">The index of the variable.</param>
			/// <param name="value">The new value of the variable.</param>
			/// <unmanaged>IXACT3Cue::SetVariable</unmanaged>
			void SetVariable(int index, float value);

			/// <summary>
			/// Get the value for a variable.
			/// </summary>
			/// <param name="index">The index of the variable.</param>
			/// <returns>The value that is currently held by the variable.</returns>
			/// <unmanaged>IXACT3Cue::GetVariable</unmanaged>
			float GetVariable(int index);

			/// <summary>
			/// Pause playback of the cue.
			/// </summary>
			/// <param name="pause">The action to take. If true, playback is paused, if false, playback is resumed.</param>
			/// <unmanaged>IXACT3Cue::Pause</unmanaged>
			void Pause(bool pause);

			/// <summary>
			/// Gets a <see cref="CueInstanceProperties"/> object that contains the properties of the cue instance.
			/// </summary>
			/// <unmanaged>IXACT3Cue::GetProperties</unmanaged>
			property CueInstanceProperties^ Properties { CueInstanceProperties^ get(); }

			// TODO: Link with XAudio2 via:
			//SetOutputVoices(THIS_ __in_opt const XAUDIO2_VOICE_SENDS* pSendList);
			//SetOutputVoiceMatrix(THIS_ __in_opt IXAudio2Voice* pDestinationVoice, UINT32 SourceChannels, UINT32 DestinationChannels, __in_ecount(SourceChannels * DestinationChannels) const float* pLevelMatrix);
		};
	}
}
