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
#include <windows.h>
#include <xinput.h>

#include "xinput.h"
#include "Exception.h"

namespace SlimDX {
	namespace XInput {
		Controller::Controller(UserIndex userIndex) {
			XInputEnable(true);
			this->userIndex = (UInt32)userIndex;
		}

		void Controller::GetState([Out] State% currentState) {
			pin_ptr<State> state = &currentState;
			XInputException::CheckResult(XInputGetState(userIndex, (XINPUT_STATE*)state));
		}
		
		void Controller::SetState(Vibration% vibration) {
			pin_ptr<Vibration> vib = &vibration;
			XInputException::CheckResult(XInputSetState(userIndex, (XINPUT_VIBRATION*)vib));
		}
		
		void Controller::GetCapabilities(DeviceQueryType flags, Capabilities% capabilities) {
			pin_ptr<Capabilities> cap = &capabilities;
			XInputException::CheckResult(XInputGetCapabilities(userIndex, (UInt32)flags, (XINPUT_CAPABILITIES*)cap));
		}
		
		void Controller::GetDirectSoundAudioDeviceGuids(Guid% soundRenderGuid, Guid% soundCaptureGuid) {
			pin_ptr<Guid> renderGuid = &soundRenderGuid;
			pin_ptr<Guid> captureGuid = &soundCaptureGuid;
			XInputException::CheckResult(XInputGetDSoundAudioDeviceGuids(userIndex, (GUID*)renderGuid, (GUID*)captureGuid));
		}
		
		bool Controller::GetKeystroke(DeviceQueryType flags, KeyStroke% keystroke) {
			pin_ptr<KeyStroke> keys = &keystroke;
			UInt32 result = XInputGetKeystroke(userIndex, (UInt32)flags, (XINPUT_KEYSTROKE*)keys);
			XInputException::CheckResult(result);

			if(result == ERROR_EMPTY)
				return false;
			return true;
		}
	}
}
