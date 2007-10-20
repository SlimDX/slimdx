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

using namespace System::Runtime::InteropServices;

#include "../DirectXObject.h"
#include "ErrorCode.h"
#include "Enums.h"

namespace SlimDX
{
	namespace DirectSound
	{
		[StructLayout( LayoutKind::Sequential, Pack = 4 )]
		public value class Capabilities
		{
			int Size;
			int Flags;
			int MinSecondarySampleRate;
			int MaxSecondarySampleRate;
			int PrimaryBuffers;
			int MaxHwMixingAllBuffers;
			int MaxHwMixingStaticBuffers;
			int MaxHwMixingStreamingBuffers;
			int FreeHwMixingAllBuffers;
			int FreeHwMixingStaticBuffers;
			int FreeHwMixingStreamingBuffers;
			int MaxHw3DAllBuffers;
			int MaxHw3DStaticBuffers;
			int MaxHw3DStreamingBuffers;
			int FreeHw3DAllBuffers;
			int FreeHw3DStaticBuffers;
			int FreeHw3DStreamingBuffers;
			int TotalHwMemBytes;
			int FreeHwMemBytes;
			int MaxContigFreeHwMemBytes;
			int UnlockTransferRateHwBuffers;
			int PlayCpuOverheadSwBuffers;
			int Reserved1;
			int Reserved2;
		};

		public ref class DirectSound : DirectXObject<IDirectSound8>
		{
		private:
			Capabilities caps;
			Capabilities GetCapabilities();

		public:
			DirectSound( IDirectSound8* dsound );
			DirectSound();
			DirectSound( Guid device );
			~DirectSound() { Destruct(); }

			void Initialize();
			void Initialize( Guid device );

			void SetCooperativeLevel( IntPtr windowHandle, CooperativeLevel coopLevel );
			void SetSpeakerConfig( Speaker speakerSet, SpeakerGeometry geometry );
			void GetSpeakerConfig( [Out] Speaker% speakerSet, [Out] SpeakerGeometry% geometry );
			bool VerifyCertification();

			property Capabilities Capabilities
			{
				SlimDX::DirectSound::Capabilities get() { return caps; }
			}
		};
	}
}