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

#include <dsound.h>

#include "../AudioEnums.h"
#include "CaptureCapabilities.h"

namespace SlimDX
{
	namespace DirectSound
	{
		CaptureCapabilities::CaptureCapabilities( const DSCCAPS &caps )
		{
			Channels = caps.dwChannels;
			EmulatedDriver = false;
			MultipleCapture = false;
			Format11KhzMono16Bit = false;
			Format11KhzMono8Bit = false;
			Format11KhzStereo16Bit = false;
			Format11KhzStereo8Bit = false;
			Format22KhzMono16Bit = false;
			Format22KhzMono8Bit = false;
			Format22KhzStereo16Bit = false;
			Format22KhzStereo8Bit = false;
			Format44KhzMono16Bit = false;
			Format44KhzMono8Bit = false;
			Format44KhzStereo16Bit = false;
			Format44KhzStereo8Bit = false;
			Format48KhzMono16Bit = false;
			Format48KhzMono8Bit = false;
			Format48KhzStereo16Bit = false;
			Format48KhzStereo8Bit = false;
			Format96KhzMono16Bit = false;
			Format96KhzMono8Bit = false;
			Format96KhzStereo16Bit = false;
			Format96KhzStereo8Bit = false;

			if( ( caps.dwFlags & DSCCAPS_CERTIFIED ) != 0 )
				Certified = true;

			if( ( caps.dwFlags & DSCCAPS_EMULDRIVER ) != 0 )
				EmulatedDriver = true;

			if( ( caps.dwFlags & DSCCAPS_MULTIPLECAPTURE ) != 0 )
				MultipleCapture = true;

			if( ( caps.dwFormats & WAVE_FORMAT_1M16 ) != 0 )
				Format11KhzMono16Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_1M08 ) != 0 )
				Format11KhzMono8Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_1S16 ) != 0 )
				Format11KhzStereo16Bit = true; 

			if( ( caps.dwFormats & WAVE_FORMAT_1S08 ) != 0 )
				Format11KhzStereo8Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_2M16 ) != 0 )
				Format22KhzMono16Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_2M08 ) != 0 )
				Format22KhzMono8Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_2S16 ) != 0 )
				Format22KhzStereo16Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_2S08 ) != 0 )
				Format22KhzStereo8Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_4M16 ) != 0 )
				Format44KhzMono16Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_4M08 ) != 0 )
				Format44KhzMono8Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_4S16 ) != 0 )
				Format44KhzStereo16Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_4S08 ) != 0 )
				Format44KhzStereo8Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_48M16 ) != 0 )
				Format48KhzMono16Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_48M08 ) != 0 )
				Format48KhzMono8Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_48S16 ) != 0 )
				Format48KhzStereo16Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_48S08 ) != 0 )
				Format48KhzStereo8Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_96M16 ) != 0 )
				Format96KhzMono16Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_96M08 ) != 0 )
				Format96KhzMono8Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_96S16 ) != 0 )
				Format96KhzStereo16Bit = true;

			if( ( caps.dwFormats & WAVE_FORMAT_96S08 ) != 0 )
				Format96KhzStereo8Bit = true;
		}
	}
}