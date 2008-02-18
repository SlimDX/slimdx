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
#include <dinput.h>

#include "../DirectInput/Guids.h"

#include "XInput.h"
#include "XInputException.h"

using namespace System;

namespace SlimDX
{
	namespace XInput
	{
		Controller::Controller(UserIndex userIndex)
		{
			XInputEnable(true);
			this->userIndex = static_cast<System::UInt32>( userIndex );
		}

		void Controller::GetState([Out] State% currentState)
		{
			pin_ptr<State> state = &currentState;
			Result::Record(XInputGetState(userIndex, reinterpret_cast<XINPUT_STATE*>(state)));
		}
		
		void Controller::SetVibration(Vibration% vibration)
		{
			pin_ptr<Vibration> vib = &vibration;
			Result::Record(XInputSetState(userIndex, reinterpret_cast<XINPUT_VIBRATION*>(vib)));
		}

		void Controller::SetVibration(Vibration vibration)
		{
			Result::Record(XInputSetState(userIndex, reinterpret_cast<XINPUT_VIBRATION*>(&vibration)));
		}
		
		void Controller::GetCapabilities(DeviceQueryType flags, SlimDX::XInput::Capabilities% capabilities)
		{
			XINPUT_CAPABILITIES caps;
			Result::Record(XInputGetCapabilities(userIndex, static_cast<DWORD>(flags), &caps));

			capabilities.Type = static_cast<DeviceType>(caps.Type);
			capabilities.Subtype = static_cast<DeviceSubtype>(caps.SubType);
			capabilities.Gamepad = Gamepad( caps.Gamepad );
			capabilities.Flags = static_cast<CapabilitiesFlags>(caps.Flags);
			capabilities.Vibration.LeftMotorSpeed = caps.Vibration.wLeftMotorSpeed;
			capabilities.Vibration.RightMotorSpeed = caps.Vibration.wRightMotorSpeed;
		}
		
		void Controller::GetDirectSoundAudioDeviceGuids(Guid% soundRenderGuid, Guid% soundCaptureGuid)
		{
			pin_ptr<Guid> renderGuid = &soundRenderGuid;
			pin_ptr<Guid> captureGuid = &soundCaptureGuid;
			Result::Record(XInputGetDSoundAudioDeviceGuids(userIndex,
				reinterpret_cast<GUID*>(renderGuid), reinterpret_cast<GUID*>(captureGuid)));
		}
		
		bool Controller::GetKeystroke(DeviceQueryType flags, Keystroke% keystroke)
		{
			XINPUT_KEYSTROKE keys;
			UInt32 result = XInputGetKeystroke(userIndex, static_cast<DWORD>(flags), &keys);
			Result::Record(result);

			keystroke.VirtualKey = static_cast<GamepadKeyCode>(keys.VirtualKey);
			keystroke.Flags = static_cast<KeystrokeFlags>(keys.Flags);
			keystroke.UserIndex = static_cast<UserIndex>(keys.UserIndex);
			keystroke.HidCode = keys.HidCode;

			if(result == ERROR_EMPTY)
				return false;

			return true;
		}

		void Controller::GetBatteryInformation(BatteryDeviceType flag, [Out] BatteryInformation% batteryInfo)
		{
			XINPUT_BATTERY_INFORMATION info;
			Result::Record( XInputGetBatteryInformation( userIndex, static_cast<BYTE>(flag), &info ) );

			batteryInfo.Level = static_cast<BatteryLevel>(info.BatteryLevel);
			batteryInfo.Type = static_cast<BatteryType>(info.BatteryType);
		}

		BatteryInformation Controller::GetBatteryInformation(BatteryDeviceType flag)
		{
			XINPUT_BATTERY_INFORMATION info;
			Result::Record( XInputGetBatteryInformation( userIndex, static_cast<BYTE>(flag), &info ) );

			BatteryInformation batteryInfo;
			batteryInfo.Level = static_cast<BatteryLevel>(info.BatteryLevel);
			batteryInfo.Type = static_cast<BatteryType>(info.BatteryType);
			return batteryInfo;
		}

		bool Controller::IsConnected::get()
		{
			XINPUT_STATE state;
			UInt32 result = XInputGetState(userIndex, &state);

			if(result == ERROR_DEVICE_NOT_CONNECTED)
				return false;
			else if(result != ERROR_SUCCESS)
				Result::Record(result);

			return true;
		}

		State Controller::CurrentState::get()
		{
			State state;
			Result::Record(XInputGetState(userIndex, reinterpret_cast<XINPUT_STATE*>(&state)));
			return state;
		}

		Capabilities Controller::Capabilities::get()
		{
			SlimDX::XInput::Capabilities capabilities;
			XINPUT_CAPABILITIES caps;
			Result::Record(XInputGetCapabilities(userIndex, XINPUT_FLAG_GAMEPAD, &caps));

			capabilities.Type = static_cast<DeviceType>(caps.Type);
			capabilities.Subtype = static_cast<DeviceSubtype>(caps.SubType);
			capabilities.Gamepad = Gamepad( caps.Gamepad );
			capabilities.Flags = static_cast<CapabilitiesFlags>(caps.Flags);
			capabilities.Vibration.LeftMotorSpeed = caps.Vibration.wLeftMotorSpeed;
			capabilities.Vibration.RightMotorSpeed = caps.Vibration.wRightMotorSpeed;

			return capabilities;
		}

		Guid Controller::SoundRenderGuid::get()
		{
			GUID renderGuid;
			GUID captureGuid;
			Result::Record(XInputGetDSoundAudioDeviceGuids(userIndex, &renderGuid, &captureGuid));

			return Utilities::ConvertNativeGuid( renderGuid );
		}

		Guid Controller::SoundCaptureGuid::get()
		{
			GUID renderGuid;
			GUID captureGuid;
			Result::Record(XInputGetDSoundAudioDeviceGuids(userIndex, &renderGuid, &captureGuid));

			return Utilities::ConvertNativeGuid( captureGuid );
		}
	}
}
