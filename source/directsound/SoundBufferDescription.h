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
#include "Enums.h"

namespace SlimDX
{
	namespace DirectSound
	{
		/// <summary>
		/// Describes the characteristics of a new buffer object.
		/// </summary>
		public value class SoundBufferDescription
		{
		internal:
			DSBUFFERDESC ToUnmanaged();

		public:
			/// <summary>
			/// Size of the new buffer, in bytes. This value must be 0 when creating a buffer.
			/// </summary>
			property int SizeInBytes;

			/// <summary>
			/// Flags specifying the capabilities of the buffer.
			/// </summary>
			property BufferFlags Flags;

			/// <summary>
			/// Structure specifying the waveform format for the buffer.
			/// </summary>
			property WaveFormat^ Format;

			/// <summary>
			/// Unique identifier of the two-speaker virtualization algorithm to be used by DirectSound3D hardware emulation.
			/// </summary>
			property System::Guid AlgorithmFor3D;
		};
	}
}