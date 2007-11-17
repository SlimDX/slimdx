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
#ifdef WRAP_XAUDIO2

#include <xaudio2.h>
#include <vcclr.h>

#include "EngineCallback.h"

namespace SlimDX
{
namespace XAudio2
{
	EngineCallback::EngineCallback()
	{
		Shim = new EngineCallbackShim( this );
	}

	EngineCallback::~EngineCallback()
	{
		this->!EngineCallback();
	}

	EngineCallback::!EngineCallback()
	{
		delete Shim;
		Shim = NULL;
	}

	EngineCallbackShim::EngineCallbackShim( EngineCallback^ wrappedInterface )
	{
		m_WrappedInterface = wrappedInterface;
	}

	void EngineCallbackShim::OnCriticalError( HRESULT hr )
	{
		m_WrappedInterface->OnCriticalError( static_cast<int>( hr ) );
	}

	void EngineCallbackShim::OnProcessingPassStart()
	{
		m_WrappedInterface->OnProcessingPassStart();
	}

	void EngineCallbackShim::OnProcessingPassEnd()
	{
		m_WrappedInterface->OnProcessingPassEnd();
	}
}
}

#endif //WRAP_XAUDIO2