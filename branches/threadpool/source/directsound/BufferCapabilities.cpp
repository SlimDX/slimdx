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
#include <dsound.h>

#include "BufferCapabilities.h"

namespace SlimDX
{
namespace DirectSound
{
	BufferCapabilities::BufferCapabilities( const DSBCAPS &caps )
	{
		BufferSize = caps.dwBufferBytes;
		PlayCpuOverhead = caps.dwPlayCpuOverhead;
		UnlockTransferRate = caps.dwUnlockTransferRate;
		CanGetCurrentPosition = ( caps.dwFlags & DSBCAPS_GETCURRENTPOSITION2 ) != 0;
		Control3D = ( caps.dwFlags & DSBCAPS_CTRL3D ) != 0;
		ControlEffects = ( caps.dwFlags & DSBCAPS_CTRLFX ) != 0;
		ControlFrequency = ( caps.dwFlags & DSBCAPS_CTRLFREQUENCY ) != 0;
		ControlPan = ( caps.dwFlags & DSBCAPS_CTRLPAN ) != 0;
		ControlPositionNotify = ( caps.dwFlags & DSBCAPS_CTRLPOSITIONNOTIFY ) != 0;
		ControlVolume = ( caps.dwFlags & DSBCAPS_CTRLVOLUME ) != 0;
		GlobalFocus = ( caps.dwFlags & DSBCAPS_GLOBALFOCUS ) != 0;
		LocateInHardware = ( caps.dwFlags & DSBCAPS_LOCHARDWARE ) != 0;
		LocateInSoftware = ( caps.dwFlags & DSBCAPS_LOCSOFTWARE ) != 0;
		LocationDefer = ( caps.dwFlags & DSBCAPS_LOCDEFER ) != 0;
		Mute3DAtMaximumDistance = ( caps.dwFlags & DSBCAPS_MUTE3DATMAXDISTANCE ) != 0;
		PrimaryBuffer = ( caps.dwFlags & DSBCAPS_PRIMARYBUFFER ) != 0;
		StaticBuffer = ( caps.dwFlags & DSBCAPS_STATIC ) != 0;
		StickyFocus = ( caps.dwFlags & DSBCAPS_STICKYFOCUS ) != 0;
	}
}
}
