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

namespace SlimDX {
	namespace XInput {
		Controller::Controller() {
			XInputEnable(true);
		}

		void Controller::GetState(UInt32 userIndex, State% currentState) {
			pin_ptr<State> state = &currentState;
			XInputGetState(userIndex, (XINPUT_STATE*)state);
		}
		
		void Controller::SetState(UInt32 userIndex, Vibration% vibration) {
			pin_ptr<Vibration> vib = &vibration;
			XInputSetState(userIndex, (XINPUT_VIBRATION*)vib);
		}
		
		void Controller::GetCapabilities(UInt32 userIndex, Flags flags, Capabilities% capabilities) {
			pin_ptr<Capabilities> cap = &capabilities;
			XInputGetCapabilities(userIndex, (UInt32)flags, (XINPUT_CAPABILITIES*)cap);
		}
		
		void Controller::GetDirectSoundAudioDeviceGuids(UInt32 userIndex, Guid% soundRenderGuid, Guid% soundCaptureGuid) {
			pin_ptr<Guid> renderGuid = &soundRenderGuid;
			pin_ptr<Guid> captureGuid = &soundCaptureGuid;
			XInputGetDSoundAudioDeviceGuids(userIndex, (GUID*)renderGuid, (GUID*)captureGuid);
		}
		
		void Controller::GetKeystroke(UInt32 userIndex, Flags flags, KeyStroke% keystroke) {
			pin_ptr<KeyStroke> keys = &keystroke;
			XInputGetKeystroke(userIndex, (UInt32)flags, (XINPUT_KEYSTROKE*)keys);
		}
	}
}