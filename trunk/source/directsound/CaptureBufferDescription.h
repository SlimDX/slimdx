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

#include "../WaveFormat.h"
#include "CaptureEffectDescription.h"

namespace SlimDX
{
	namespace DirectSound
	{
		/// <summary>
		/// Describes a capture buffer.
		/// </summary>
		public value class CaptureBufferDescription
		{
		internal:
			CaptureBufferDescription( const DSCBUFFERDESC &description );
			DSCBUFFERDESC ToUnmanaged();

		public:
			/// <summary>
			/// Size of capture buffer to create, in bytes.
			/// </summary>
			property int BufferBytes;

			/// <summary>
			/// The buffer supports effects.
			/// </summary>
			property bool ControlEffects;

			/// <summary>
			/// The Win32 wave mapper will be used for formats not supported by the device.
			/// </summary>
			property bool WaveMapped;

			/// <summary>
			/// The format in which to capture the data.
			/// </summary>
			property WaveFormat^ Format;

			/// <summary>
			/// Describes effects supported by hardware for the buffer.
			/// </summary>
			property array<CaptureEffectDescription>^ EffectDescriptions;
		};
	}
}