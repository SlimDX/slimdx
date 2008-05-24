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
	/// <summary>
	/// Specifies possible speaker combinations for audio devices.
	/// </summary>
	[System::Flags]
	public enum class Speakers : System::Int32
	{
		/// <summary>
		/// A front left speaker will be used.
		/// </summary>
		FrontLeft = SPEAKER_FRONT_LEFT,

		/// <summary>
		/// A front right speaker will be used.
		/// </summary>
		FrontRight = SPEAKER_FRONT_RIGHT,

		/// <summary>
		/// A front center speaker will be used.
		/// </summary>
		FrontCenter = SPEAKER_FRONT_CENTER,

		/// <summary>
		/// A low frequency speaker will be used.
		/// </summary>
		LowFrequency = SPEAKER_LOW_FREQUENCY,

		/// <summary>
		/// A back left speaker will be used.
		/// </summary>
		BackLeft = SPEAKER_BACK_LEFT,

		/// <summary>
		/// A back right speaker will be used.
		/// </summary>
		BackRight = SPEAKER_BACK_RIGHT,

		/// <summary>
		/// A front left-of-center speaker will be used.
		/// </summary>
		FrontLeftOfCenter = SPEAKER_FRONT_LEFT_OF_CENTER,

		/// <summary>
		/// A front right-of-center speaker will be used.
		/// </summary>
		FrontRightOfCenter = SPEAKER_FRONT_RIGHT_OF_CENTER,

		/// <summary>
		/// A back center speaker will be used.
		/// </summary>
		BackCenter = SPEAKER_BACK_CENTER,

		/// <summary>
		/// A left side speaker will be used.
		/// </summary>
		SideLeft = SPEAKER_SIDE_LEFT,

		/// <summary>
		/// A right side speaker will be used.
		/// </summary>
		SideRight = SPEAKER_SIDE_RIGHT,

		/// <summary>
		/// A top center speaker will be used.
		/// </summary>
		TopCenter = SPEAKER_TOP_CENTER,

		/// <summary>
		/// A top front left speaker will be used.
		/// </summary>
		TopFrontLeft = SPEAKER_TOP_FRONT_LEFT,

		/// <summary>
		/// A top front center speaker will be used.
		/// </summary>
		TopFrontCenter = SPEAKER_TOP_FRONT_CENTER,

		/// <summary>
		/// A top front right speaker will be used.
		/// </summary>
		TopFrontRight = SPEAKER_TOP_FRONT_RIGHT,

		/// <summary>
		/// A top back left speaker will be used.
		/// </summary>
		TopBackLeft = SPEAKER_TOP_BACK_LEFT,

		/// <summary>
		/// A top back center speaker will be used.
		/// </summary>
		TopBackCenter = SPEAKER_TOP_BACK_CENTER,

		/// <summary>
		/// A top back right speaker will be used.
		/// </summary>
		TopBackRight = SPEAKER_TOP_BACK_RIGHT,

		/// <summary>
		/// A reserved speaker will be used.
		/// </summary>
		Reserved = SPEAKER_RESERVED,

#pragma warning(disable: 4369)
		/// <summary>
		/// All possible speakers will be used.
		/// </summary>
		All = SPEAKER_ALL,
#pragma warning(default: 4369)

		/// <summary>
		/// A single speaker will be used.
		/// </summary>
		Mono = SPEAKER_MONO,

		/// <summary>
		/// Two or more speakers will be used.
		/// </summary>
		Stereo = SPEAKER_STEREO,

		/// <summary>
		/// A combination of speakers will be used that provides 2.1 sound output.
		/// </summary>
		TwoPointOne = SPEAKER_2POINT1,

		/// <summary>
		/// A combination of speakers will be used that provides surround sound output.
		/// </summary>
		Surround = SPEAKER_SURROUND,

		/// <summary>
		/// A combination of speakers will be used that provides quadrophonic sound output.
		/// </summary>
		Quadrophonic = SPEAKER_QUAD,

		/// <summary>
		/// A combination of speakers will be used that provides 4.1 sound output.
		/// </summary>
		FourPointOne = SPEAKER_4POINT1,

		/// <summary>
		/// A combination of speakers will be used that provides 5.1 sound output.
		/// </summary>
		FivePointOne = SPEAKER_5POINT1,

		/// <summary>
		/// A combination of speakers will be used that provides 7.1 sound output.
		/// </summary>
		SevenPointOne = SPEAKER_7POINT1,

		/// <summary>
		/// A combination of speakers will be used that provides 5.1 surround sound output.
		/// </summary>
		FivePointOneSurround = SPEAKER_5POINT1_SURROUND,

		/// <summary>
		/// A combination of speakers will be used that provides 7.1 surround sound output.
		/// </summary>
		SevenPointOneSurround = SPEAKER_7POINT1_SURROUND,
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