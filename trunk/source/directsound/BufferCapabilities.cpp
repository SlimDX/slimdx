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
#include "BufferCapabilities.h"

namespace SlimDX
{
	namespace DirectSound
	{
		BufferCapabilities::BufferCapabilities( const DSBCAPS &caps )
		{
			BufferBytes = caps.dwBufferBytes;
			PlayCpuOverhead = caps.dwPlayCpuOverhead;
			UnlockTransferRate = caps.dwUnlockTransferRate;
			CanGetCurrentPosition = false;
			Control3D = false;
			ControlFrequency = false;
			ControlVolume = false;
			ControlPan = false;
			ControlPositionNotify = false;
			ControlEffects = false;
			GlobalFocus = false;
			LocateInHardware = false;
			LocateInSoftware = false;
			LocationDefer = false;
			Mute3DAtMaximumDistance = false;
			PrimaryBuffer = false;
			StaticBuffer = false;
			StickyFocus = false;

			if( ( caps.dwFlags & DSBCAPS_GETCURRENTPOSITION2 ) != 0 )
				CanGetCurrentPosition = true;

			if( ( caps.dwFlags & DSBCAPS_CTRL3D ) != 0 )
				Control3D = true;

			if( ( caps.dwFlags & DSBCAPS_CTRLFX ) != 0 )
				ControlEffects = true;

			if( ( caps.dwFlags & DSBCAPS_CTRLFREQUENCY ) != 0 )
				ControlFrequency = true;

			if( ( caps.dwFlags & DSBCAPS_CTRLPAN ) != 0 )
				ControlPan = true;

			if( ( caps.dwFlags & DSBCAPS_CTRLPOSITIONNOTIFY ) != 0 )
				ControlPositionNotify = true;

			if( ( caps.dwFlags & DSBCAPS_CTRLVOLUME ) != 0 )
				ControlVolume = true;

			if( ( caps.dwFlags & DSBCAPS_GLOBALFOCUS ) != 0 )
				GlobalFocus = true;

			if( ( caps.dwFlags & DSBCAPS_LOCHARDWARE ) != 0 )
				LocateInHardware = true;

			if( ( caps.dwFlags & DSBCAPS_LOCSOFTWARE ) != 0 )
				LocateInSoftware = true;

			if( ( caps.dwFlags & DSBCAPS_LOCDEFER ) != 0 )
				LocationDefer = true;

			if( ( caps.dwFlags & DSBCAPS_MUTE3DATMAXDISTANCE ) != 0 )
				Mute3DAtMaximumDistance = true;

			if( ( caps.dwFlags & DSBCAPS_PRIMARYBUFFER ) != 0 )
				PrimaryBuffer = true;

			if( ( caps.dwFlags & DSBCAPS_STATIC ) != 0 )
				StaticBuffer = true;

			if( ( caps.dwFlags & DSBCAPS_STICKYFOCUS ) != 0 )
				StickyFocus = true;
		}
	}
}
