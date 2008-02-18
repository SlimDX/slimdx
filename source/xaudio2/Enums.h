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

#ifdef WRAP_XAUDIO2

//using namespace System;

namespace SlimDX
{
	namespace XAudio2
	{
		public enum class DeviceRole : System::Int32
		{
			NotDefaultDevice = NotDefaultDevice,
			DefaultConsoleDevice = DefaultConsoleDevice,
			DefaultMultimediaDevice = DefaultMultimediaDevice,
			DefaultCommunicationsDevice = DefaultCommunicationsDevice,
			DefaultGameDevice = DefaultGameDevice,
			GlobalDefaultDevice = GlobalDefaultDevice,
			InvalidDeviceRole = InvalidDeviceRole
		};

		public enum class FilterType : System::Int32
		{
			LowPassFilter = LowPassFilter,
			BandPassFilter = BandPassFilter,
			HighPassFilter = HighPassFilter
		};

		public enum class WindowsProcessorSpecifier : System::Int32
		{
			Processor0 = Processor0,
			Processor1 = Processor1,
			Processor2 = Processor2,
			Processor3 = Processor3,
			Processor4 = Processor4,
			Processor5 = Processor5,
			Processor6 = Processor6,
			Processor7 = Processor7,
			Processor8 = Processor8,
			Processor9 = Processor9,
			Processor10 = Processor10,
			Processor11 = Processor11,
			Processor12 = Processor12,
			Processor13 = Processor13,
			Processor14 = Processor14,
			Processor15 = Processor15,

			MaxProcessor = XAUDIO2_MAX_PROCESSOR,
			AnyProcessor = XAUDIO2_ANY_PROCESSOR,
			DefaultProcessor = XAUDIO2_DEFAULT_PROCESSOR
		};

		[System::Flags]
		public enum class XAudio2Flags : System::Int32
		{
			DebugEngine = XAUDIO2_DEBUG_ENGINE,
		};

		[System::Flags]
		public enum class VoiceFlags : System::Int32
		{
			//Used in IXAudio2::CreateSourceVoice()
			NoPitch = XAUDIO2_VOICE_NOPITCH,
			NoSource = XAUDIO2_VOICE_NOSRC,
			UseFilter = XAUDIO2_VOICE_USEFILTER,
			Music = XAUDIO2_VOICE_MUSIC,

			//Used in IXAudio2Voice::Start() and Stop()
			PlayTails = XAUDIO2_PLAY_TAILS,
			FlushBuffers = XAUDIO2_FLUSH_BUFFERS,
		};

		[System::Flags]
		public enum class BufferFlags : System::Int32
		{
			EndOfStream = XAUDIO2_END_OF_STREAM,
		};

		[System::Flags]
		public enum class Speakers : System::Int32
		{
			FrontLeft = SPEAKER_FRONT_LEFT,
			FrontRight = SPEAKER_FRONT_RIGHT,
			FrontCenter = SPEAKER_FRONT_CENTER,
			LowFrequency = SPEAKER_LOW_FREQUENCY,
			BackLeft = SPEAKER_BACK_LEFT,
			BackRight = SPEAKER_BACK_RIGHT,
			FrontLeftOfCenter = SPEAKER_FRONT_LEFT_OF_CENTER,
			FrontRightOfCenter = SPEAKER_FRONT_RIGHT_OF_CENTER,
			BackCenter = SPEAKER_BACK_CENTER,
			SideLeft = SPEAKER_SIDE_LEFT,
			SideRight = SPEAKER_SIDE_RIGHT,
			TopCenter = SPEAKER_TOP_CENTER,
			TopFrontLeft = SPEAKER_TOP_FRONT_LEFT,
			TopFrontCenter = SPEAKER_TOP_FRONT_CENTER,
			TopFrontRight = SPEAKER_TOP_FRONT_RIGHT,
			TopBackLeft = SPEAKER_TOP_BACK_LEFT,
			TopBackCenter = SPEAKER_TOP_BACK_CENTER,
			TopBackRight = SPEAKER_TOP_BACK_RIGHT,

			Reserved = SPEAKER_RESERVED,
			//warning C4369: 'All' : enumerator value '2147483648' cannot be represented as 'int', value is '-2147483648'
#pragma warning(disable: 4369)
			All = SPEAKER_ALL,
#pragma warning(default: 4369)

			Mono = SPEAKER_MONO,
			Stereo = SPEAKER_STEREO,
			TwoPointOne = SPEAKER_2POINT1,
			Surround = SPEAKER_SURROUND,
			Quadrophonic = SPEAKER_QUAD,
			FourPointOne = SPEAKER_4POINT1,
			FivePointOne = SPEAKER_5POINT1,
			SevenPointOne = SPEAKER_7POINT1,
			FivePointOneSurround = SPEAKER_5POINT1_SURROUND,
			SevenPointOneSurround = SPEAKER_7POINT1_SURROUND,
		};

		//warning C4369: 'Extensible' : enumerator value '65534' cannot be represented as 'short', value is '-2'
#pragma warning(disable: 4369)
		public enum class WaveFormat : Int16
		{
			Pcm = WAVE_FORMAT_PCM,
			AdPcm = WAVE_FORMAT_ADPCM,
			IeeeFloat = WAVE_FORMAT_IEEE_FLOAT,
			MpegLayer3 = WAVE_FORMAT_MPEGLAYER3,
			DolbyAC3Spdif = WAVE_FORMAT_DOLBY_AC3_SPDIF,
			WmaSpdif = WAVE_FORMAT_WMASPDIF,
			Extensible = WAVE_FORMAT_EXTENSIBLE,
		};
#pragma warning(default: 4369)
	}
}

#endif //WRAP_XAUDIO2