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

namespace SlimDX
{
	namespace DirectSound
	{
		

		/// <summary>
		/// Describes the capabilities of the capture device.
		/// </summary>
		[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential, Pack = 4 )]
		public value class CaptureCapabilities
		{
		internal:
			CaptureCapabilities( const DSCCAPS& caps );

		public:
			/// <summary>
			/// The driver for the device is a certified WDM driver.
			/// </summary>
			property bool Certified;
			/// <summary>
			/// Number of channels supported by the device, where 1 is mono, 2 is stereo, and so on.
			/// </summary>
			property int Channels;
			/// <summary>
			/// There is no DirectSoundCapture driver for the device, so the standard waveform audio functions are being used.
			/// </summary>
			property bool EmulatedDriver;
			/// <summary>
			/// The driver supports the 11Khz 16 Bit Mono format.
			/// </summary>
			property bool Format11KhzMono16Bit;
			/// <summary>
			/// The driver supports the 11Khz 8 Bit Mono format.
			/// </summary>
			property bool Format11KhzMono8Bit;
			/// <summary>
			/// The driver supports the 11Khz 16 Bit Stereo format.
			/// </summary>
			property bool Format11KhzStereo16Bit;
			/// <summary>
			/// The driver supports the 11Khz 8 Bit Stereo format.
			/// </summary>
			property bool Format11KhzStereo8Bit;
			/// <summary>
			/// The driver supports the 22Khz 16 Bit Mono format.
			/// </summary>
			property bool Format22KhzMono16Bit;
			/// <summary>
			/// The driver supports the 22Khz 8 Bit Mono format.
			/// </summary>
			property bool Format22KhzMono8Bit;
			/// <summary>
			/// The driver supports the 22Khz 16 Bit Stereo format.
			/// </summary>
			property bool Format22KhzStereo16Bit;
			/// <summary>
			/// The driver supports the 22Khz 8 Bit Stereo format.
			/// </summary>
			property bool Format22KhzStereo8Bit;
			/// <summary>
			/// The driver supports the 44Khz 16 Bit Mono format.
			/// </summary>
			property bool Format44KhzMono16Bit;
			/// <summary>
			/// The driver supports the 44Khz 8 Bit Mono format.
			/// </summary>
			property bool Format44KhzMono8Bit;
			/// <summary>
			/// The driver supports the 44Khz 16 Bit Stereo format.
			/// </summary>
			property bool Format44KhzStereo16Bit;
			/// <summary>
			/// The driver supports the 44Khz 8 Bit Stereo format.
			/// </summary>
			property bool Format44KhzStereo8Bit;
			/// <summary>
			/// The driver supports the 48Khz 16 Bit Mono format.
			/// </summary>
			property bool Format48KhzMono16Bit;
			/// <summary>
			/// The driver supports the 48Khz 8 Bit Mono format.
			/// </summary>
			property bool Format48KhzMono8Bit;
			/// <summary>
			/// The driver supports the 48Khz 16 Bit Stereo format.
			/// </summary>
			property bool Format48KhzStereo16Bit;
			/// <summary>
			/// The driver supports the 48Khz 8 Bit Stereo format.
			/// </summary>
			property bool Format48KhzStereo8Bit;
			/// <summary>
			/// The driver supports the 96Khz 16 Bit Mono format.
			/// </summary>
			property bool Format96KhzMono16Bit;
			/// <summary>
			/// The driver supports the 96Khz 8 Bit Mono format.
			/// </summary>
			property bool Format96KhzMono8Bit;
			/// <summary>
			/// The driver supports the 96Khz 16 Bit Stereo format.
			/// </summary>
			property bool Format96KhzStereo16Bit;
			/// <summary>
			/// The driver supports the 96Khz 8 Bit Stereo format.
			/// </summary>
			property bool Format96KhzStereo8Bit;
			/// <summary>
			/// Multiple capture objects can be used simultaneously on the capture device.
			/// </summary>
			property bool MultipleCapture;
		};
	}
}