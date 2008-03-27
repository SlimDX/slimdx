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
#ifdef WRAP_XAUDIO2

#include <xaudio2.h>
#include <vcclr.h>

#include "VoiceCallback.h"

using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace XAudio2
{
	VoiceCallback::VoiceCallback()
	{
		Shim = new VoiceCallbackShim( this );
	}

	VoiceCallback::~VoiceCallback()
	{
		this->!VoiceCallback();
	}

	VoiceCallback::!VoiceCallback()
	{
		delete Shim;
		Shim = NULL;
	}

	VoiceCallbackShim::VoiceCallbackShim( VoiceCallback^ wrappedInterface )
	{
		m_WrappedInterface = wrappedInterface;
	}

	void VoiceCallbackShim::OnVoiceProcessingPassStart()
	{
		m_WrappedInterface->OnVoiceProcessingPassStart();
	}

	void VoiceCallbackShim::OnVoiceProcessingPassEnd()
	{
		m_WrappedInterface->OnVoiceProcessingPassEnd();
	}

	void VoiceCallbackShim::OnStreamEnd()
	{
		m_WrappedInterface->OnStreamEnd();
	}

	void VoiceCallbackShim::OnBufferStart( void* pBufferContext )
	{
		Object^ bufferContext = nullptr;
		GCHandle contextHandle;

		if( pBufferContext != NULL )
		{
			contextHandle = GCHandle::FromIntPtr( safe_cast<IntPtr>( pBufferContext ) );
			bufferContext = contextHandle.Target;
		}

		m_WrappedInterface->OnBufferStart( bufferContext );

		if( pBufferContext != NULL )
			contextHandle.Free();
	}

	void VoiceCallbackShim::OnBufferEnd( void* pBufferContext )
	{
		Object^ bufferContext = nullptr;
		GCHandle contextHandle;

		if( pBufferContext != NULL )
		{
			contextHandle = GCHandle::FromIntPtr( safe_cast<IntPtr>( pBufferContext ) );
			bufferContext = contextHandle.Target;
		}

		m_WrappedInterface->OnBufferEnd( bufferContext );

		if( pBufferContext != NULL )
			contextHandle.Free();
	}

	void VoiceCallbackShim::OnLoopEnd( void* pBufferContext )
	{
		Object^ bufferContext = nullptr;
		GCHandle contextHandle;

		if( pBufferContext != NULL )
		{
			contextHandle = GCHandle::FromIntPtr( safe_cast<IntPtr>( pBufferContext ) );
			bufferContext = contextHandle.Target;
		}

		m_WrappedInterface->OnLoopEnd( bufferContext );

		if( pBufferContext != NULL )
			contextHandle.Free();
	}
}
}

#endif //WRAP_XAUDIO2