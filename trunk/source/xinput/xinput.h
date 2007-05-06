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

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SlimDX {
	namespace XInput {
		[StructLayout(LayoutKind::Sequential)]
		public value class Vibration {
		public:
			UInt16 LeftMotorSpeed;
			UInt16 RightMotorSpeed;
		};

		[Flags]
		public enum class GamepadButtonFlags : UInt16 {
			DPadUp = XINPUT_GAMEPAD_DPAD_UP,
			DPadDown = XINPUT_GAMEPAD_DPAD_DOWN,
			DPadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
			DPadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
			Start = XINPUT_GAMEPAD_START,
			Back =XINPUT_GAMEPAD_BACK,
			LeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,     
			RightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,     
			LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
			RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
			A = XINPUT_GAMEPAD_A,
			B = XINPUT_GAMEPAD_B,
			X = XINPUT_GAMEPAD_X,
			Y = XINPUT_GAMEPAD_Y,
		};

		[StructLayout(LayoutKind::Sequential)]
		public value class GamePad {
		public:
			GamepadButtonFlags wButtons;
			Byte bLeftTrigger;
			Byte bRightTrigger;
			Int16 sThumbLX;
			Int16 sThumbLY;
			Int16 sThumbRX;
			Int16 sThumbRY;

			static const Int16 GamepadLeftThumbDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
			static const Int16 GamepadRightThumbDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
			static const Byte GamepadTriggerThreshold = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
		};

		[Flags]
		public enum class KeyStrokeFlags : UInt16 {
			KeyDown = XINPUT_KEYSTROKE_KEYDOWN,
			KeyUp = XINPUT_KEYSTROKE_KEYUP,
			Repeat = XINPUT_KEYSTROKE_REPEAT
		};

		public enum class GamepadKeyCodes : UInt16 {
			A = VK_PAD_A,
			B = VK_PAD_B,
			X = VK_PAD_X,
			Y = VK_PAD_Y,
			RightShoulder = VK_PAD_RSHOULDER,
			LeftShoulder = VK_PAD_LSHOULDER,
			LeftTrigger = VK_PAD_LTRIGGER,
			RightTrigger = VK_PAD_RTRIGGER,
			DPadUp = VK_PAD_DPAD_UP,
			DPadDown = VK_PAD_DPAD_DOWN,
			DPadLeft = VK_PAD_DPAD_LEFT,
			DPadRight = VK_PAD_DPAD_RIGHT,
			Start = VK_PAD_START,
			Back = VK_PAD_BACK,
			LeftThumbPress = VK_PAD_LTHUMB_PRESS,
			RightThumbPress=  VK_PAD_RTHUMB_PRESS,
			LeftThumbUp = VK_PAD_LTHUMB_UP,
			LeftThumbDown = VK_PAD_LTHUMB_DOWN,
			LeftThumpLeft=  VK_PAD_LTHUMB_LEFT,
			LeftThumbRight = VK_PAD_LTHUMB_RIGHT,
			LeftThumbUpLeft = VK_PAD_LTHUMB_UPLEFT,
			LeftThumbUpRight = VK_PAD_LTHUMB_UPRIGHT,
			LeftThumbDownLeft = VK_PAD_LTHUMB_DOWNLEFT,
			LeftThumbDownRight = VK_PAD_LTHUMB_DOWNRIGHT,
			RightThumbUp = VK_PAD_RTHUMB_UP,
			RightThumbDown = VK_PAD_RTHUMB_DOWN,
			RightThumpLeft=  VK_PAD_RTHUMB_LEFT,
			RightThumbRight = VK_PAD_RTHUMB_RIGHT,
			RightThumbUpLeft = VK_PAD_RTHUMB_UPLEFT,
			RightThumbUpRight = VK_PAD_RTHUMB_UPRIGHT,
			RightThumbDownLeft = VK_PAD_RTHUMB_DOWNLEFT,
			RightThumbDownRight = VK_PAD_RTHUMB_DOWNRIGHT
		};

		[StructLayout(LayoutKind::Sequential)]
		public value class KeyStroke {
		public:
			GamepadKeyCodes VirtualKey;
			Char Unicode;
			KeyStrokeFlags Flags;
			Byte UserIndex;
			Byte HidCode;
		};

		[StructLayout(LayoutKind::Sequential)]
		public value class State {
		public:
			UInt32 PacketNumber;
			GamePad Gamepad;
		};

		public enum class DeviceType : Byte {
			Gamepad = XINPUT_DEVTYPE_GAMEPAD
		};

		public enum class DeviceSubType : Byte {
			ArcadeStick = XINPUT_DEVSUBTYPE_ARCADE_STICK,
			Gamepad = XINPUT_DEVSUBTYPE_GAMEPAD,
			Wheel = XINPUT_DEVSUBTYPE_WHEEL,
			DancePad = XINPUT_DEVSUBTYPE_DANCE_PAD,
			FlightStick = XINPUT_DEVSUBTYPE_FLIGHT_SICK
		};

		[Flags]
		public enum class CapabilitiesFlags : UInt16 {
			VoiceSupported = XINPUT_CAPS_VOICE_SUPPORTED
		};

		[StructLayout(LayoutKind::Sequential)]
		public value class Capabilities {
		public:
			DeviceType Type;
			DeviceSubType SubType;
			CapabilitiesFlags Flags;
			GamePad Gamepad;
			Vibration Vibration;
		};

		public enum class DeviceQueryType : Int32 {
			Any = 0,
			GamePad = XINPUT_FLAG_GAMEPAD
		};

		public ref class Controller {
		public:
			Controller();
			void GetState(UInt32 userIndex, State% currentState);
			void SetState(UInt32 userIndex, Vibration% vibration);
			void GetCapabilities(UInt32 userIndex, DeviceQueryType flag, Capabilities% capabilities);
			void GetDirectSoundAudioDeviceGuids(UInt32 userIndex, Guid% soundRenderGuid, Guid% soundCaptureGuid);
			bool GetKeystroke(UInt32 userIndex, DeviceQueryType flag, KeyStroke% keystroke);
		};
	}
}
