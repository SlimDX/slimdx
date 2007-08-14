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

using namespace System;

namespace SlimDX
{
	namespace DirectSound
	{
		public enum class CooperativeLevel : Int32
		{
			Normal = DSSCL_NORMAL,
			Priority = DSSCL_PRIORITY,
			Exclusive = DSSCL_EXCLUSIVE,
			WritePrimary = DSSCL_WRITEPRIMARY,
		};

		public enum class Speaker : Int32
		{
			DirectOut = DSSPEAKER_DIRECTOUT,
			Headphone = DSSPEAKER_HEADPHONE,
			Mono = DSSPEAKER_MONO,
			Quadrophonic = DSSPEAKER_QUAD,
			Stereo = DSSPEAKER_STEREO,
			Surround = DSSPEAKER_SURROUND,
			FivePointOne = DSSPEAKER_5POINT1,
			SevenPointOne = DSSPEAKER_7POINT1,
			SevenPointOneSurround = DSSPEAKER_7POINT1_SURROUND,
			SevenPointOneWide = DSSPEAKER_7POINT1_WIDE
		};

		public enum class SpeakerGeometry : Int32
		{
			None = 0,
			Min = DSSPEAKER_GEOMETRY_MIN,
			Narrow = DSSPEAKER_GEOMETRY_NARROW,
			Wide = DSSPEAKER_GEOMETRY_WIDE,
			Max = DSSPEAKER_GEOMETRY_MAX,
		};

		[Flags]
		public enum class PlayFlags : Int32
		{
			None = 0,
			Looping = DSBPLAY_LOOPING,

			Hardware = DSBPLAY_LOCHARDWARE,
			Software = DSBPLAY_LOCSOFTWARE,

			TerminateByTime = DSBPLAY_TERMINATEBY_TIME,
			TerminateByDistance = DSBPLAY_TERMINATEBY_DISTANCE,
			TerminateByPriority = DSBPLAY_TERMINATEBY_PRIORITY,
		};

		[Flags]
		public enum class BufferFlags : Int32
		{
			None = 0,
			PrimaryBuffer = DSBCAPS_PRIMARYBUFFER,
			Static = DSBCAPS_STATIC,
			Hardware = DSBCAPS_LOCHARDWARE,
			Software = DSBCAPS_LOCSOFTWARE,
			Control3D = DSBCAPS_CTRL3D,
			ControlFrequency = DSBCAPS_CTRLFREQUENCY,
			ControlPan = DSBCAPS_CTRLPAN,
			ControlVolume = DSBCAPS_CTRLVOLUME,
			ControlPositionNotify = DSBCAPS_CTRLPOSITIONNOTIFY,
			ControlFx = DSBCAPS_CTRLFX,
			StickFocus = DSBCAPS_STICKYFOCUS,
			GlobalFocus = DSBCAPS_GLOBALFOCUS,
			GetCurrentPosition2 = DSBCAPS_GETCURRENTPOSITION2,
			Mute3DAtMaxDistance = DSBCAPS_MUTE3DATMAXDISTANCE,
			Defer = DSBCAPS_LOCDEFER,
		};

		[Flags]
		public enum class BufferStatus : Int32
		{
			None = 0,
			Playing = DSBSTATUS_PLAYING,
			BufferLost = DSBSTATUS_BUFFERLOST,
			Looping = DSBSTATUS_LOOPING,
			Hardware = DSBSTATUS_LOCHARDWARE,
			Software = DSBSTATUS_LOCSOFTWARE,
			Terminated = DSBSTATUS_TERMINATED,
		};

		[Flags]
		public enum class LockFlags : Int32
		{
			None = 0,
			FromWriteCursor = DSBLOCK_FROMWRITECURSOR,
			EntireBuffer = DSBLOCK_ENTIREBUFFER,
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
			Extensible = WAVE_FORMAT_EXTENSIBLE,
		};
#pragma warning(default: 4369)
	}
}