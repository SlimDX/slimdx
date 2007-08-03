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
* all copies or substantial portions of the Software.`
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

#include <vcclr.h>

using namespace System;

namespace SlimDX
{
	namespace XAudio2
	{
		class EngineCallbackShim;

		public ref class EngineCallback abstract
		{
		internal:
			EngineCallbackShim* Shim;

		protected:
			EngineCallback();

		public:
			~EngineCallback();
			!EngineCallback();

			virtual void OnCriticalError( int hr ) = 0;
			virtual void OnProcessingPassStart() = 0;
			virtual void OnProcessingPassEnd() = 0;
		};

		class EngineCallbackShim : public IXAudio2EngineCallback
		{
		private:
			gcroot<EngineCallback^> m_WrappedInterface;

		public:
			EngineCallbackShim( EngineCallback^ wrappedInterface );

			virtual void WINAPI OnCriticalError( HRESULT hr );
			virtual void WINAPI OnProcessingPassStart();
			virtual void WINAPI OnProcessingPassEnd();
		};
	}
}
