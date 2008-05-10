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

namespace SlimDX
{
	namespace XAudio2
	{
		// NOTE: The enumerations defined in this file are in alphabetical order. When
		//       adding new enumerations or renaming existing ones, please make sure
		//       the ordering is maintained.

		public enum class BufferFlags : System::Int32
		{
			None = 0,
			EndOfStream = XAUDIO2_END_OF_STREAM
		};

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

		[System::Flags]
		public enum class LogType : System::Int32
		{
			None = 0,
			Errors = XAUDIO2_LOG_ERRORS,
			Warnings = XAUDIO2_LOG_WARNINGS,
			Information = XAUDIO2_LOG_INFO,
			Details = XAUDIO2_LOG_DETAIL,
			ApiCalls = XAUDIO2_LOG_API_CALLS,
			FunctionCalls = XAUDIO2_LOG_FUNC_CALLS,
			Timing = XAUDIO2_LOG_TIMING,
			Locks = XAUDIO2_LOG_LOCKS,
			Memory = XAUDIO2_LOG_MEMORY,
			Streaming = XAUDIO2_LOG_STREAMING
		};

		public enum class ProcessorSpecifier : System::Int32
		{
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
			Processor16 = Processor16,
			Processor17 = Processor17,
			Processor18 = Processor18,
			Processor19 = Processor19,
			Processor20 = Processor20,
			Processor21 = Processor21,
			Processor22 = Processor22,
			Processor23 = Processor23,
			Processor24 = Processor24,
			Processor25 = Processor25,
			Processor26 = Processor26,
			Processor27 = Processor27,
			Processor28 = Processor28,
			Processor29 = Processor29,
			Processor30 = Processor30,
			Processor31 = Processor31,
			Processor32 = Processor32,
			AnyProcessor = XAUDIO2_ANY_PROCESSOR,
			DefaultProcessor = XAUDIO2_DEFAULT_PROCESSOR
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

		public enum class PlayFlags : System::Int32
		{
			None = 0,
			PlayTails = XAUDIO2_PLAY_TAILS
		};

		[System::Flags]
		public enum class VoiceFlags : System::Int32
		{
			None = 0,
			NoPitch = XAUDIO2_VOICE_NOPITCH,
			NoSampleRateConversion = XAUDIO2_VOICE_NOSRC,
			UseFilter = XAUDIO2_VOICE_USEFILTER,
			Music = XAUDIO2_VOICE_MUSIC
		};

		public enum class XAudio2Flags : System::Int32
		{
			None = 0,
			DebugEngine = XAUDIO2_DEBUG_ENGINE
		};

#pragma warning(disable: 4369)
		public enum class WaveFormatTag : System::Int32
		{
			Pcm = WAVE_FORMAT_PCM,
			AdPcm = WAVE_FORMAT_ADPCM,
			IeeeFloat = WAVE_FORMAT_IEEE_FLOAT,
			MpegLayer3 = WAVE_FORMAT_MPEGLAYER3,
			DolbyAC3Spdif = WAVE_FORMAT_DOLBY_AC3_SPDIF,
			WmAudio2 = WAVE_FORMAT_WMAUDIO2,
			WmAudio3 = WAVE_FORMAT_WMAUDIO3,
			WmaSpdif = WAVE_FORMAT_WMASPDIF,
			Extensible = WAVE_FORMAT_EXTENSIBLE,
		};
#pragma warning(default: 4369)
	}
}