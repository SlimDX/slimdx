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

#ifdef WRAP_XAUDIO2

#include "Enums.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
	namespace XAudio2
	{
		ref class EngineCallback;

		[StructLayout( LayoutKind::Sequential )]
		public value class PerformanceData
		{
			Int64 AudioCyclesSinceLastQuery;
			Int64 TotalCyclesSinceLastQuery;
			Int32 MinimumCyclesPerQuantum;
			Int32 MaximumCyclesPerQuantum;

			Int32 CurrentLatencyInSamples;
			Int32 CurrentOutputSamplesQueued;
			Int32 GlitchesSinceLastQuery;

			Int32 ActiveSourceVoiceCount;
			Int32 TotalSourceVoiceCount;
			Int32 ActiveSubmixVoiceCount;
			Int32 TotalSubmixVoiceCount;

			Int32 ActiveXmaSourceVoices;
			Int32 ActiveXmaStreams;
		};

		[StructLayout( LayoutKind::Explicit, Pack = 2)]
		public value class WaveFormatExtended
		{
			[FieldOffset( 0 )]
			WaveFormat FormatTag;
			[FieldOffset( 2 )]
			short Channels;
			[FieldOffset( 4 )]
			int SamplesPerSecond;
			[FieldOffset( 8 )]
			int AverageBytesPerSecond;
			[FieldOffset( 12 )]
			short BlockAlign;
			[FieldOffset( 14 )]
			short BitsPerSample;
			[FieldOffset( 16 )]
			short Size;

			[FieldOffset( 18 )]
			short ValidBitsPerSample;
			[FieldOffset( 18 )]
			short SamplesPerBlock;
			[FieldOffset( 18 )]
			short Reserved;

			[FieldOffset( 20 )]
			Speakers ChannelMask;

			[FieldOffset( 24 )]
			Guid SubFormat;
		};

		public value class DeviceDetails
		{
			String^ DeviceId;
			String^ DisplayName;
			DeviceRole Role;
			WaveFormatExtended OutputFormat;
		};

		public ref class XAudio2 : SlimDXObject<IXAudio2>
		{
		public:
			XAudio2( XAudio2Flags flags, EngineCallback^ callback, WindowsProcessorSpecifier processor );
			DXOBJECT_FUNCTIONS;

			static float AmplitudeRatioToDecibels( float volume );
			static float DecibelsToAmplitudeRatio( float decibels );
			static float FrequencyRatioToSemitones( float frequencyRatio );
			static float SemitonesToFrequencyRatio( float semitones );

			void Initialize( EngineCallback^ callback, WindowsProcessorSpecifier processor );

			void StartEngine();
			void StopEngine();

			DeviceDetails GetDeviceDetails( int index );

			property int DeviceCount
			{
				int get();
			}

			property PerformanceData PerformanceData
			{
				SlimDX::XAudio2::PerformanceData get();
			}
		};
	}
}

#endif //WRAP_XAUDIO2