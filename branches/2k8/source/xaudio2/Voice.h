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

#include "../Result.h"

#include "FilterParameters.h"
#include "VoiceDetails.h"

namespace SlimDX
{
	namespace XAudio2
	{
		public ref class Voice abstract
		{
		private:
			IXAudio2Voice *m_Pointer;

		internal:
			property IXAudio2Voice *InternalPointer
			{ 
				IXAudio2Voice *get() { return m_Pointer; }
				void set( IXAudio2Voice *value ) { m_Pointer = value; }
			}

		protected:
			Voice() { }

		public:
			void Destroy();

			Result EnableEffect( int effectIndex );
			Result EnableEffect( int effectIndex, int operationSet );

			Result DisableEffect( int effectIndex );
			Result DisableEffect( int effectIndex, int operationSet );

			array<float>^ GetChannelVolumes( int channels );

			Result SetChannelVolumes( int channels, array<float>^ volumes );
			Result SetChannelVolumes( int channels, array<float>^ volumes, int operationSet );

			Result GetEffectParameters( int effectIndex, array<System::Byte>^ parameters );

			Result SetEffectParameters( int effectIndex, array<System::Byte>^ parameters );
			Result SetEffectParameters( int effectIndex, array<System::Byte>^ parameters, int operationSet );

			bool IsEffectEnabled( int effectIndex );

			array<float>^ GetOutputMatrix( Voice^ destinationVoice, int sourceChannels, int destinationChannels );

			Result SetOutputMatrix( Voice^ destinationVoice, int sourceChannels, int destinationChannels, array<float>^ matrix );
			Result SetOutputMatrix( Voice^ destinationVoice, int sourceChannels, int destinationChannels, array<float>^ matrix, int operationSet );

			// TODO: Implement the following method. Unfortunately, this will involve implementing
			// almost all of XAPO, which will be a complete pain in the neck. Let's wait until
			// someone complains :)
			//Result SetEffectChain( EffectChain^ effectChain );

			Result SetOutputVoices( array<Voice^>^ outputVoices );

			property FilterParameters FilterParameters
			{
				SlimDX::XAudio2::FilterParameters get();
				void set( SlimDX::XAudio2::FilterParameters value );
			}

			property VoiceDetails VoiceDetails
			{
				SlimDX::XAudio2::VoiceDetails get();
			}

			property float Volume
			{
				float get();
				void set( float value );
			}
		};
	}
}