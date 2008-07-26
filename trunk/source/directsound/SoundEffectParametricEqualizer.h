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
		/// Contains parameters for a parametric equalizer effect.
		/// </summary>
		public value class ParamEqParameters
		{
		internal:
			ParamEqParameters( const DSFXParamEq& value );
			DSFXParamEq Marshal();

		public:
			/// <summary>
			/// Center frequency, in hertz. This value cannot exceed one-third of the frequency of the buffer. The default value is 8000.
			/// </summary>
			property float Center;
			/// <summary>
			/// Bandwidth, in semitones. The default value is 12.
			/// </summary>
			property float Bandwidth;
			/// <summary>
			/// Gain, The default value is 0.
			/// </summary>
			property float Gain;
		};

		/// <summary>
		/// The SoundEffectParametricEqualizer object is used to set and retrieve effect parameters on a buffer that supports parametric equalizer effects.
		/// </summary>
		public ref class SoundEffectParametricEqualizer : public ComObject
		{
			COMOBJECT(IDirectSoundFXParamEq, SoundEffectParametricEqualizer);

		public:
			/// <summary>
			/// Constructs a new instance of the <see cref="SlimDX::DirectSound::SoundEffectParametricEqualizer"/> class using the specified pointer to a
			/// previously constructed unmanaged object.
			/// </summary>
			/// <param name="pointer">The unmanaged IDirectSoundFXParamEq pointer.</param>
			/// <returns>The newly constructed object.</returns>
			static SoundEffectParametricEqualizer^ FromPointer( System::IntPtr pointer );

			/// <summary>
			/// Releases all resources used by the <see cref="SlimDX::DirectSound::SoundEffectParametricEqualizer"/> class.
			/// </summary>
			~SoundEffectParametricEqualizer();

			/// <summary>
			/// Gets or sets all the parametric equalizer parameters of a buffer.
			/// </summary>
			property ParamEqParameters AllParameters
			{
				ParamEqParameters get();
				void set( ParamEqParameters value );
			}

			/// <summary>
			/// Default center frequency, in hertz.
			/// </summary>
			literal float CenterDefault = 8000.0f;
			/// <summary>
			/// Maximum center frequency, in hertz.
			/// </summary>
			literal float CenterMax = DSFXPARAMEQ_CENTER_MAX;
			/// <summary>
			/// Minimum center frequency, in hertz.
			/// </summary>
			literal float CenterMin = DSFXPARAMEQ_CENTER_MIN;
			/// <summary>
			/// Default bandwidth, in semitones.
			/// </summary>
			literal float BandwidthDefault = 12.0f;
			/// <summary>
			/// Maximum bandwidth, in semitones.
			/// </summary>
			literal float BandwidthMax = DSFXPARAMEQ_BANDWIDTH_MAX;
			/// <summary>
			/// Minimum bandwidth, in semitones.
			/// </summary>
			literal float BandwidthMin = DSFXPARAMEQ_BANDWIDTH_MIN;
			/// <summary>
			/// Default gain.
			/// </summary>
			literal float GainDefault = 0.0f;
			/// <summary>
			/// Maximum gain.
			/// </summary>
			literal float GainMax = DSFXPARAMEQ_GAIN_MAX;
			/// <summary>
			/// Minimum gain.
			/// </summary>
			literal float GainMin = DSFXPARAMEQ_GAIN_MIN;
		};
	}
}