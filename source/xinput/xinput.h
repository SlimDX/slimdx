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
		/// <summary>
		/// 
		/// </summary>
		public value class Vibration {
		public:
			/// <summary>
			/// 
			/// </summary>
			UInt16 LeftMotorSpeed;
			/// <summary>
			/// 
			/// </summary>
			UInt16 RightMotorSpeed;
		};

		[Flags]
		/// <summary>
		/// 
		/// </summary>
		public enum class GamepadButtonFlags : UInt16 {
			/// <summary>
			/// 
			/// </summary>
			DPadUp = XINPUT_GAMEPAD_DPAD_UP,
			/// <summary>
			/// 
			/// </summary>
			DPadDown = XINPUT_GAMEPAD_DPAD_DOWN,
			/// <summary>
			/// 
			/// </summary>
			DPadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
			/// <summary>
			/// 
			/// </summary>
			DPadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
			/// <summary>
			/// 
			/// </summary>
			Start = XINPUT_GAMEPAD_START,
			/// <summary>
			/// 
			/// </summary>
			Back =XINPUT_GAMEPAD_BACK,
			/// <summary>
			/// 
			/// </summary>
			LeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,     
			/// <summary>
			/// 
			/// </summary>
			RightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,     
			/// <summary>
			/// 
			/// </summary>
			LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
			/// <summary>
			/// 
			/// </summary>
			RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
			/// <summary>
			/// 
			/// </summary>
			A = XINPUT_GAMEPAD_A,
			/// <summary>
			/// 
			/// </summary>
			B = XINPUT_GAMEPAD_B,
			/// <summary>
			/// 
			/// </summary>
			X = XINPUT_GAMEPAD_X,
			/// <summary>
			/// 
			/// </summary>
			Y = XINPUT_GAMEPAD_Y,
		};

		[StructLayout(LayoutKind::Sequential)]
		/// <summary>
		/// 
		/// </summary>
		public value class GamePad {
		public:
			/// <summary>
			/// 
			/// </summary>
			GamepadButtonFlags wButtons;
			/// <summary>
			/// 
			/// </summary>
			Byte bLeftTrigger;
			/// <summary>
			/// 
			/// </summary>
			Byte bRightTrigger;
			/// <summary>
			/// 
			/// </summary>
			Int16 sThumbLX;
			/// <summary>
			/// 
			/// </summary>
			Int16 sThumbLY;
			/// <summary>
			/// 
			/// </summary>
			Int16 sThumbRX;
			/// <summary>
			/// 
			/// </summary>
			Int16 sThumbRY;

			/// <summary>
			/// 
			/// </summary>
			static const Int16 GamepadLeftThumbDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
			/// <summary>
			/// 
			/// </summary>
			static const Int16 GamepadRightThumbDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
			/// <summary>
			/// 
			/// </summary>
			static const Byte GamepadTriggerThreshold = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
		};

		[Flags]
		/// <summary>
		/// 
		/// </summary>
		public enum class KeyStrokeFlags : UInt16 {
			/// <summary>
			/// 
			/// </summary>
			KeyDown = XINPUT_KEYSTROKE_KEYDOWN,
			/// <summary>
			/// 
			/// </summary>
			KeyUp = XINPUT_KEYSTROKE_KEYUP,
			/// <summary>
			/// 
			/// </summary>
			Repeat = XINPUT_KEYSTROKE_REPEAT
		};

		/// <summary>
		/// 
		/// </summary>
		public enum class GamepadKeyCodes : UInt16 {
			/// <summary>
			/// 
			/// </summary>
			A = VK_PAD_A,
			/// <summary>
			/// 
			/// </summary>
			B = VK_PAD_B,
			/// <summary>
			/// 
			/// </summary>
			X = VK_PAD_X,
			/// <summary>
			/// 
			/// </summary>
			Y = VK_PAD_Y,
			/// <summary>
			/// 
			/// </summary>
			RightShoulder = VK_PAD_RSHOULDER,
			/// <summary>
			/// 
			/// </summary>
			LeftShoulder = VK_PAD_LSHOULDER,
			/// <summary>
			/// 
			/// </summary>
			LeftTrigger = VK_PAD_LTRIGGER,
			/// <summary>
			/// 
			/// </summary>
			RightTrigger = VK_PAD_RTRIGGER,
			/// <summary>
			/// 
			/// </summary>
			DPadUp = VK_PAD_DPAD_UP,
			/// <summary>
			/// 
			/// </summary>
			DPadDown = VK_PAD_DPAD_DOWN,
			/// <summary>
			/// 
			/// </summary>
			DPadLeft = VK_PAD_DPAD_LEFT,
			/// <summary>
			/// 
			/// </summary>
			DPadRight = VK_PAD_DPAD_RIGHT,
			/// <summary>
			/// 
			/// </summary>
			Start = VK_PAD_START,
			/// <summary>
			/// 
			/// </summary>
			Back = VK_PAD_BACK,
			/// <summary>
			/// 
			/// </summary>
			LeftThumbPress = VK_PAD_LTHUMB_PRESS,
			/// <summary>
			/// 
			/// </summary>
			RightThumbPress=  VK_PAD_RTHUMB_PRESS,
			/// <summary>
			/// 
			/// </summary>
			LeftThumbUp = VK_PAD_LTHUMB_UP,
			/// <summary>
			/// 
			/// </summary>
			LeftThumbDown = VK_PAD_LTHUMB_DOWN,
			/// <summary>
			/// 
			/// </summary>
			LeftThumpLeft=  VK_PAD_LTHUMB_LEFT,
			/// <summary>
			/// 
			/// </summary>
			LeftThumbRight = VK_PAD_LTHUMB_RIGHT,
			/// <summary>
			/// 
			/// </summary>
			LeftThumbUpLeft = VK_PAD_LTHUMB_UPLEFT,
			/// <summary>
			/// 
			/// </summary>
			LeftThumbUpRight = VK_PAD_LTHUMB_UPRIGHT,
			/// <summary>
			/// 
			/// </summary>
			LeftThumbDownLeft = VK_PAD_LTHUMB_DOWNLEFT,
			/// <summary>
			/// 
			/// </summary>
			LeftThumbDownRight = VK_PAD_LTHUMB_DOWNRIGHT,
			/// <summary>
			/// 
			/// </summary>
			RightThumbUp = VK_PAD_RTHUMB_UP,
			/// <summary>
			/// 
			/// </summary>
			RightThumbDown = VK_PAD_RTHUMB_DOWN,
			/// <summary>
			/// 
			/// </summary>
			RightThumpLeft=  VK_PAD_RTHUMB_LEFT,
			/// <summary>
			/// 
			/// </summary>
			RightThumbRight = VK_PAD_RTHUMB_RIGHT,
			/// <summary>
			/// 
			/// </summary>
			RightThumbUpLeft = VK_PAD_RTHUMB_UPLEFT,
			/// <summary>
			/// 
			/// </summary>
			RightThumbUpRight = VK_PAD_RTHUMB_UPRIGHT,
			/// <summary>
			/// 
			/// </summary>
			RightThumbDownLeft = VK_PAD_RTHUMB_DOWNLEFT,
			/// <summary>
			/// 
			/// </summary>
			RightThumbDownRight = VK_PAD_RTHUMB_DOWNRIGHT
		};

		[StructLayout(LayoutKind::Sequential)]
		/// <summary>
		/// 
		/// </summary>
		public value class KeyStroke {
		public:
			/// <summary>
			/// 
			/// </summary>
			GamepadKeyCodes VirtualKey;
			/// <summary>
			/// 
			/// </summary>
			Char Unicode;
			/// <summary>
			/// 
			/// </summary>
			KeyStrokeFlags Flags;
			/// <summary>
			/// 
			/// </summary>
			Byte UserIndex;
			/// <summary>
			/// 
			/// </summary>
			Byte HidCode;
		};

		[StructLayout(LayoutKind::Sequential)]
		/// <summary>
		/// 
		/// </summary>
		public value class State {
		public:
			/// <summary>
			/// 
			/// </summary>
			UInt32 PacketNumber;
			/// <summary>
			/// 
			/// </summary>
			GamePad Gamepad;
		};

		/// <summary>
		/// 
		/// </summary>
		public enum class DeviceType : Byte {
			/// <summary>
			/// 
			/// </summary>
			Gamepad = XINPUT_DEVTYPE_GAMEPAD
		};

		/// <summary>
		/// 
		/// </summary>
		public enum class DeviceSubType : Byte {
			/// <summary>
			/// 
			/// </summary>
			ArcadeStick = XINPUT_DEVSUBTYPE_ARCADE_STICK,
			/// <summary>
			/// 
			/// </summary>
			Gamepad = XINPUT_DEVSUBTYPE_GAMEPAD,
			/// <summary>
			/// 
			/// </summary>
			Wheel = XINPUT_DEVSUBTYPE_WHEEL,
			/// <summary>
			/// 
			/// </summary>
			DancePad = XINPUT_DEVSUBTYPE_DANCE_PAD,
			/// <summary>
			/// 
			/// </summary>
			FlightStick = XINPUT_DEVSUBTYPE_FLIGHT_SICK
		};

		[Flags]
		/// <summary>
		/// 
		/// </summary>
		public enum class CapabilitiesFlags : UInt16 {
			/// <summary>
			/// 
			/// </summary>
			VoiceSupported = XINPUT_CAPS_VOICE_SUPPORTED
		};

		[StructLayout(LayoutKind::Sequential)]
		/// <summary>
		/// 
		/// </summary>
		public value class Capabilities {
		public:
			/// <summary>
			/// 
			/// </summary>
			DeviceType Type;
			/// <summary>
			/// 
			/// </summary>
			DeviceSubType SubType;
			/// <summary>
			/// 
			/// </summary>
			CapabilitiesFlags Flags;
			/// <summary>
			/// 
			/// </summary>
			GamePad Gamepad;
			/// <summary>
			/// 
			/// </summary>
			Vibration Vibration;
		};

		/// <summary>
		/// 
		/// </summary>
		public enum class DeviceQueryType : Int32 {
			/// <summary>
			/// 
			/// </summary>
			Any = 0,
			/// <summary>
			/// 
			/// </summary>
			GamePad = XINPUT_FLAG_GAMEPAD
		};

		/// <summary>
		/// 
		/// </summary>
		public ref class Controller {
		public:
			/// <summary>
			/// Initializes a new instance of Controller
			/// </summary>
			Controller();
			/// <summary>
			/// 
			/// </summary>
			/// <param name="userIndex"></param>
			/// <param name="currentState"></param>
			void GetState(UInt32 userIndex, State% currentState);
			/// <summary>
			/// 
			/// </summary>
			/// <param name="userIndex"></param>
			/// <param name="vibration"></param>
			void SetState(UInt32 userIndex, Vibration% vibration);
			/// <summary>
			/// 
			/// </summary>
			/// <param name="userIndex"></param>
			/// <param name="flag"></param>
			/// <param name="capabilities"></param>
			void GetCapabilities(UInt32 userIndex, DeviceQueryType flag, Capabilities% capabilities);
			/// <summary>
			/// 
			/// </summary>
			/// <param name="userIndex"></param>
			/// <param name="soundRenderGuid"></param>
			/// <param name="soundCaptureGuid"></param>
			void GetDirectSoundAudioDeviceGuids(UInt32 userIndex, Guid% soundRenderGuid, Guid% soundCaptureGuid);
			/// <summary>
			/// 
			/// </summary>
			/// <param name="userIndex"></param>
			/// <param name="flag"></param>
			/// <param name="keystroke"></param>
			/// <returns></returns>
			bool GetKeystroke(UInt32 userIndex, DeviceQueryType flag, KeyStroke% keystroke);
		};
	}
}
