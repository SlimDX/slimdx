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

#include "Enums.h"
#include "WindowSubclass.h"
#include "InputMessageFilter.h"
#include "KeyboardInputEventArgs.h"
#include "MouseInputEventArgs.h"
#include "RawInputEventArgs.h"

namespace SlimDX
{
	namespace RawInput
	{
		public ref class Device
		{
		private:
			UsagePage m_usagePage;
			UsageId m_usageId;
			DeviceFlags m_flags;
			System::IntPtr m_target;
			WindowSubclass^ subclass;
			InputMessageFilter^ filter;

			void Construct( UsagePage usagePage, UsageId usageId, DeviceFlags flags, System::IntPtr target );
			void Destruct();

		internal:
			void OnWmInput( HRAWINPUT handle );

		protected:
			void OnKeyboardInput( KeyboardInputEventArgs^ e );
			void OnMouseInput( MouseInputEventArgs^ e );
			void OnRawInput( RawInputEventArgs^ e );

		public:
			Device( UsagePage usagePage, UsageId usageId, DeviceFlags flags );
			Device( UsagePage usagePage, UsageId usageId, DeviceFlags flags, System::IntPtr target );
			virtual ~Device() { Destruct(); }

			property UsagePage UsagePage
			{
				SlimDX::RawInput::UsagePage get() { return m_usagePage; }
			}

			property UsageId UsageId
			{
				SlimDX::RawInput::UsageId get() { return m_usageId; }
			}

			property DeviceFlags Flags
			{
				DeviceFlags get() { return m_flags; }
			}

			property System::IntPtr Target
			{
				System::IntPtr get() { return m_target; }
			}

			event System::EventHandler<KeyboardInputEventArgs^>^ KeyboardInput;
			event System::EventHandler<MouseInputEventArgs^>^ MouseInput;
			event System::EventHandler<RawInputEventArgs^>^ RawInput;
		};
	}
}