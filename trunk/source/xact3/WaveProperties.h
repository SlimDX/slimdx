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

using namespace System;

#include "WaveBankMiniWaveFormat.h"
#include "WaveBankSampleRegion.h"

namespace SlimDX
{
	namespace XACT3
	{
		/// <summary>
		/// The properties that are common to all waves.
		/// </summary>
		/// <unmanaged>XACT_WAVE_PROPERTIES</unmanaged>
		public value class WaveProperties
		{
		private:
			String^ name;
			WaveBankMiniWaveFormat^ format;
			long durationInSamples;
			WaveBankSampleRegion^ loopRegion;
			bool isStreaming;

		internal:
			WaveProperties(const XACT_WAVE_PROPERTIES& waveProperties);

		public:
			/// <summary>
			/// Gets the friendly name of the wave.
			/// </summary>
			/// <unmanaged>XACT_WAVE_PROPERTIES::friendlyName</unmanaged>
			property String^ FriendlyName
			{
				String^ get() { return name; }
			}

			/// <summary>
			/// Gets the format of the wave.
			/// </summary>
			/// <unmanaged>XACT_WAVE_PROPERTIES::format</unmanaged>
			property WaveBankMiniWaveFormat^ Format
			{
				WaveBankMiniWaveFormat^ get() { return format; }
			}

			/// <summary>
			/// Gets the duration of the wave in samples.
			/// </summary>
			/// <unmanaged>XACT_WAVE_PROPERTIES::durationInSamples</unmanaged>
			property long DurationInSamples
			{
				long get() { return durationInSamples; }
			}

			/// <summary>
			/// Gets the loop region of the wave.
			/// </summary>
			/// <unmanaged>XACT_WAVE_PROPERTIES::loopRegion</unmanaged>
			property WaveBankSampleRegion^ LoopRegion
			{
				WaveBankSampleRegion^ get() { return loopRegion; }
			}

			/// <summary>
			/// Gets a value that is true if the wave is streaming, otherwise false.
			/// </summary>
			/// <unmanaged>XACT_WAVE_PROPERTIES::streaming</unmanaged>
			property bool IsStreaming
			{
				bool get() { return isStreaming; }
			}
		};
	}
}
