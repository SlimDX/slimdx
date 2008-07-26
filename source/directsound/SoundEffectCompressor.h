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

namespace SlimDX
{
	namespace DirectSound
	{
		/// <summary>
		/// Contains parameters for a compression effect.
		/// </summary>
		public value class CompressorParameters
		{
		internal:
			CompressorParameters( const DSFXCompressor& value );
			DSFXCompressor Marshal();

		public:
			/// <summary>
			/// Time before compression reaches its full value.
			/// </summary>
			property float Attack;
			/// <summary>
			/// Output gain of signal after compression.
			/// </summary>
			property float Gain;
			/// <summary>
			/// Speed at which compression is stopped after input drops below Threshold.
			/// </summary>
			property float Release;
			/// <summary>
			/// Time after Threshold is reached before attack phase is started, in milliseconds.
			/// </summary>
			property float PreDelay;
			/// <summary>
			/// Compression ratio. The default value is 3, which means 3:1 compression.
			/// </summary>
			property float Ratio;
			/// <summary>
			/// Point at which compression begins, in decibels.
			/// </summary>
			property float Threshold;
		};

		/// <summary>
		/// The SoundEffectCompressor object is used to set and retrieve effect parameters on a buffer that supports compression.
		/// </summary>
		public ref class SoundEffectCompressor : public ComObject
		{
			COMOBJECT(IDirectSoundFXCompressor, SoundEffectCompressor);

		public:
			/// <summary>
			/// Constructs a new instance of the <see cref="SlimDX::DirectSound::SoundEffectCompressor"/> class using the specified pointer to a
			/// previously constructed unmanaged object.
			/// </summary>
			/// <param name="pointer">The unmanaged IDirectSoundFXCompressor pointer.</param>
			/// <returns>The newly constructed object.</returns>
			static SoundEffectCompressor^ FromPointer( System::IntPtr pointer );

			/// <summary>
			/// Releases all resources used by the <see cref="SlimDX::DirectSound::SoundEffectCompressor"/>.
			/// </summary>
			~SoundEffectCompressor();

			/// <summary>
			/// Gets or sets
			/// </summary>
			property CompressorParameters AllParameters
			{
				CompressorParameters get();
				void set( CompressorParameters value );
			}

			/// <summary>
			/// Default time before compression reaches its full value, in decibels (dB). The default value is 10 ms.
			/// </summary>
			literal float AttackDefault = 10.0f;
			/// <summary>
			/// Maximum time before compression reaches its full value, in decibels (dB).
			/// </summary>
			literal float AttackMax = DSFXCOMPRESSOR_ATTACK_MAX;
			/// <summary>
			/// Minimum time before compression reaches its full value, in decibels (dB).
			/// </summary>
			literal float AttackMin = DSFXCOMPRESSOR_ATTACK_MIN;
			/// <summary>
			/// Default output gain of signal after compression, in decibels (dB). The default value is 0 dB. 
			/// </summary>
			literal float GainDefault = 0.0f;
			/// <summary>
			/// Maximum output gain of signal after compression, in decibels (dB). 
			/// </summary>
			literal float GainMax = DSFXCOMPRESSOR_GAIN_MAX;
			/// <summary>
			/// Minimum output gain of signal after compression, in decibels (dB). 
			/// </summary>
			literal float GainMin = DSFXCOMPRESSOR_GAIN_MIN;
			/// <summary>
			/// Default time after threshold is reached before attack phase is started, in milliseconds. The default value is 4 ms. 
			/// </summary>
			literal float PreDelayDefault = 4.0f;
			/// <summary>
			/// Maximum time after threshold is reached before attack phase is started, in milliseconds. 
			/// </summary>
			literal float PreDelayMax = DSFXCOMPRESSOR_PREDELAY_MAX;
			/// <summary>
			/// Minimum time after threshold is reached before attack phase is started, in milliseconds. 
			/// </summary>
			literal float PreDelayMin = DSFXCOMPRESSOR_PREDELAY_MIN;
			/// <summary>
			/// Default compression ratio. The default value is 3, which means 3:1 compression. 
			/// </summary>
			literal float RatioDefault = 3.0f;
			/// <summary>
			/// Maximum compression ratio.  
			/// </summary>
			literal float RatioMax = DSFXCOMPRESSOR_RATIO_MAX;
			/// <summary>
			/// Minimum compression ratio. 
			/// </summary>
			literal float RatioMin = DSFXCOMPRESSOR_RATIO_MIN;
			/// <summary>
			/// Default speed at which compression is stopped after input drops below Threshold, in miliseconds. The default value is 200 ms.
			/// </summary>
			literal float ReleaseDefault = 200.0f;
			/// <summary>
			/// Maximum speed at which compression is stopped after input drops below Threshold, in miliseconds. 
			/// </summary>
			literal float ReleaseMax = DSFXCOMPRESSOR_RELEASE_MAX;
			/// <summary>
			/// Minimum speed at which compression is stopped after input drops below Threshold, in miliseconds. 
			/// </summary>
			literal float ReleaseMin = DSFXCOMPRESSOR_RELEASE_MIN;
			/// <summary>
			/// Default point at which compression begins, in decibels, in decibels (dB). The default value is -20 dB.
			/// </summary>
			literal float ThresholdDefault = -20.0f;
			/// <summary>
			/// Maximum point at which compression begins, in decibels, in decibels (dB). 
			/// </summary>
			literal float ThresholdMax = DSFXCOMPRESSOR_THRESHOLD_MAX;
			/// <summary>
			/// Minimum point at which compression begins, in decibels, in decibels (dB).
			/// </summary>
			literal float ThresholdMin = DSFXCOMPRESSOR_THRESHOLD_MIN;
		};
	}
}