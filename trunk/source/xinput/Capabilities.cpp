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

#include <windows.h>
#include <xinput.h>

#include "Capabilities.h"

namespace SlimDX
{
	namespace XInput
	{
		Capabilities::Capabilities( const XINPUT_CAPABILITIES& native )
		{
			m_Type = static_cast<DeviceType>( native.Type );
			m_SubType = static_cast<DeviceSubtype>( native.SubType );
			m_Flags = static_cast<CapabilityFlags>( native.Flags );
			m_Gamepad = XInput::Gamepad( native.Gamepad );
			m_Vibration = XInput::Vibration( native.Vibration );
		}
		
		DeviceType Capabilities::Type::get()
		{
			return m_Type;
		}

		DeviceSubtype Capabilities::Subtype::get()
		{
			return m_SubType;
		}
		
		CapabilityFlags Capabilities::Flags::get()
		{
			return m_Flags;
		}

		XInput::Gamepad Capabilities::Gamepad::get()
		{
			return m_Gamepad;
		}

		XInput::Vibration Capabilities::Vibration::get()
		{
			return m_Vibration;
		}
	}
}