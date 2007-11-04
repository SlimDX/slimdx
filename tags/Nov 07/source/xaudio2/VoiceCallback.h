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

#ifdef WRAP_XAUDIO2

#include <vcclr.h>

using namespace System;

namespace SlimDX
{
	namespace XAudio2
	{
		class VoiceCallbackShim;

		public ref class VoiceCallback abstract
		{
		internal:
			VoiceCallbackShim* Shim;

		protected:
			VoiceCallback();

		public:
			~VoiceCallback();
			!VoiceCallback();

			virtual void OnVoiceProcessingPassStart() = 0;
			virtual void OnVoiceProcessingPassEnd() = 0;

			virtual void OnStreamEnd() = 0;

			virtual void OnBufferStart( Object^ bufferContext ) = 0;
			virtual void OnBufferEnd( Object^ bufferContext ) = 0;
			virtual void OnLoopEnd( Object^ bufferContext ) = 0;
		};

		class VoiceCallbackShim : public IXAudio2VoiceCallback
		{
		private:
			gcroot<VoiceCallback^> m_WrappedInterface;

		public:
			VoiceCallbackShim( VoiceCallback^ wrappedInterface );

			virtual void WINAPI OnVoiceProcessingPassStart();
			virtual void WINAPI OnVoiceProcessingPassEnd();

			virtual void WINAPI OnStreamEnd();

			virtual void WINAPI OnBufferStart( void* pBufferContext );
			virtual void WINAPI OnBufferEnd( void* pBufferContext );
			virtual void WINAPI OnLoopEnd( void* pBufferContext );
		};
	}
}

#endif //WRAP_XAUDIO2