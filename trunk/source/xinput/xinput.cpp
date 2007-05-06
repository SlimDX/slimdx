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