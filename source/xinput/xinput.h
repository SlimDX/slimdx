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
		/// Specifies motor speed levels for the vibration function of a controller.
		/// </summary>
		/// <remarks>
		/// The left motor is the low-frequency rumble motor. The right motor is the high-frequency rumble motor. The two motors are not the same, and they create different vibration effects.
		/// </remarks>
		public value class Vibration {
		public:
			/// <summary>
			/// Speed of the left motor. Valid values are in the range 0 to 65,535. Zero signifies no motor use; 65,535 signifies 100 percent motor use.
			/// </summary>
			UInt16 LeftMotorSpeed;
			/// <summary>
			/// Speed of the right motor. Valid values are in the range 0 to 65,535. Zero signifies no motor use; 65,535 signifies 100 percent motor use.
			/// </summary>
			UInt16 RightMotorSpeed;
		};

		[Flags]
		/// <summary>
		/// Bitmask of the device digital buttons
		/// </summary>
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
		/// <summary>
		/// Describes the current state of the Xbox 360 Controller.
		/// </summary>
		/// <remarks>
		/// Each of the thumbstick axis members is a signed value between -32768 and 32767 describing the position of the thumbstick.
		/// A value of 0 is centered. Negative values signify down or to the left. Positive values signify up or to the right.
		/// The constants GamepadLeftThumbDeadZone or GamepadRightThumbDeadZone can be used as a positive and negative value to filter a
		/// thumbstick input.
		/// </remarks>
		public value class GamePad {
		public:
			/// <summary>
			/// Bitmask of the device digital buttons
			/// </summary>
			GamepadButtonFlags Buttons;
			/// <summary>
			/// The current value of the left trigger analog control. The value is between 0 and 255.
			/// </summary>
			Byte LeftTrigger;
			/// <summary>
			/// The current value of the right trigger analog control. The value is between 0 and 255.
			/// </summary>
			Byte RightTrigger;
			/// <summary>
			/// Right thumbstick y-axis value. The value is between -32768 and 32767.
			/// </summary>
			Int16 LeftThumbX;
			/// <summary>
			/// Left thumbstick y-axis value. The value is between -32768 and 32767.
			/// </summary>
			Int16 LeftThumbY;
			/// <summary>
			/// Right thumbstick x-axis value. The value is between -32768 and 32767.
			/// </summary>
			Int16 RightThumbX;
			/// <summary>
			/// Right thumbstick y-axis value. The value is between -32768 and 32767.
			/// </summary>
			Int16 RightThumbY;

			/// <summary>
			/// Can be used as a positive and negative value to filter the left thumbstick input.
			/// </summary>
			static const Int16 GamepadLeftThumbDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
			/// <summary>
			/// Can be used as a positive and negative value to filter the right thumbstick input.
			/// </summary>
			static const Int16 GamepadRightThumbDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
			/// <summary>
			/// This constantmay be used as the value which LeftTrigger and RightTrigger must be greater than to register as pressed.
			/// </summary>
			static const Byte GamepadTriggerThreshold = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
		};

		[Flags]
		/// <summary>
		/// Flags that indicate the keyboard state at the time of the input event.
		/// </summary>
		public enum class KeyStrokeFlags : UInt16 {
			KeyDown = XINPUT_KEYSTROKE_KEYDOWN,
			KeyUp = XINPUT_KEYSTROKE_KEYUP,
			Repeat = XINPUT_KEYSTROKE_REPEAT
		};

		/// <summary>
		/// Controller input virtual key codes
		/// </summary>
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
		/// <summary>
		/// Specifies keystroke data returned by Controller.GetKeystroke
		/// </summary>
		public value class KeyStroke {
		public:
			/// <summary>
			/// Virtual-key code of the key, button, or stick movement.
			/// </summary>
			GamepadKeyCodes VirtualKey;
			/// <summary>
			/// Unused and should be zero.
			/// </summary>
			Char Unicode;
			/// <summary>
			/// Combination of flags that indicate the keyboard state at the time of the input event.
			/// </summary>
			KeyStrokeFlags Flags;
			/// <summary>
			/// Index of the signed-in gamer associated with the device. Can be a value in the range 0–3.
			/// </summary>
			Byte UserIndex;
			/// <summary>
			/// HID code corresponding to the input. If there is no corresponding HID code, this value is zero.
			/// </summary>
			Byte HidCode;
		};

		[StructLayout(LayoutKind::Sequential)]
		/// <summary>
		/// Represents the state of a controller.
		/// </summary>
		public value class State {
		public:
			/// <summary>
			/// State packet number. The packet number indicates whether there have been any changes in the state of the controller.
			/// If the PacketNumber member is the same in sequentially returned State structures, the controller state has not changed. 
			/// </summary>
			UInt32 PacketNumber;
			/// <summary>
			/// GamePad structure containing the current state of an Xbox 360 Controller. 
			/// </summary>
			GamePad Gamepad;
		};

		/// <summary>
		/// Controller type.
		/// </summary>
		public enum class DeviceType : Byte {
			/// <summary>
			/// The device is a game controller.
			/// </summary>
			Gamepad = XINPUT_DEVTYPE_GAMEPAD
		};

		/// <summary>
		/// Subtype of the game controller.
		/// </summary>
		public enum class DeviceSubType : Byte {
			ArcadeStick = XINPUT_DEVSUBTYPE_ARCADE_STICK,
			Gamepad = XINPUT_DEVSUBTYPE_GAMEPAD,
			Wheel = XINPUT_DEVSUBTYPE_WHEEL,
			DancePad = XINPUT_DEVSUBTYPE_DANCE_PAD,
			FlightStick = XINPUT_DEVSUBTYPE_FLIGHT_SICK
		};

		[Flags]
		/// <summary>
		/// Features of the controller. 
		/// </summary>
		public enum class CapabilitiesFlags : UInt16 {
			/// <summary>
			/// The device has an integrated voice device.
			/// </summary>
			VoiceSupported = XINPUT_CAPS_VOICE_SUPPORTED
		};

		[StructLayout(LayoutKind::Sequential)]
		/// <summary>
		/// Describes the capabilities of a connected controller.
		/// </summary>
		/// <remarks>
		/// Sets the structure members to indicate which inputs the device supports. For binary state controls, such as digital buttons, the corresponding bit reflects
		/// whether or not the control is supported by the device. For proportional controls, such as thumbsticks, the value indicates the resolution for that control.
		/// Some number of the least significant bits may not be set, indicating that the control does not provide resolution to that level.
		/// </remarks>
		public value class Capabilities {
		public:
			/// <summary>
			/// Controller type.
			/// </summary>
			DeviceType Type;
			/// <summary>
			/// Subtype of the game controller. 
			/// </summary>
			DeviceSubType SubType;
			/// <summary>
			/// Features of the controller. 
			/// </summary>
			CapabilitiesFlags Flags;
			/// <summary>
			/// GamePad structure that describes available controller features and control resolutions. 
			/// </summary>
			GamePad Gamepad;
			/// <summary>
			/// Vibration structure that describes available vibration functionality and resolutions. 
			/// </summary>
			Vibration Vibration;
		};

		/// <summary>
		/// Flags that identify the device type.
		/// </summary>
		public enum class DeviceQueryType : Int32 {
			Any = 0,
			GamePad = XINPUT_FLAG_GAMEPAD
		};

		/// <summary>
		/// Index of the signed-in gamer associated with the device.
		/// </summary>
		public enum class UserIndex : UInt32 {
			Any = XUSER_INDEX_ANY,
			One = 0,
			Two = 1,
			Three = 2,
			Four = 3,
			MaxUserCount = XUSER_MAX_COUNT
		};

		/// <summary>
		/// 
		/// </summary>
		public ref class Controller {
		public:
			/// <summary>
			/// Initializes a new instance of Controller
			/// </summary>
			/// <param name="userIndex">Index of the user's controller.</param>
			Controller(UserIndex userIndex);
			/// <summary>
			/// Retrieves the current state of the specified controller.
			/// </summary>
			/// <param name="currentState">Out reference to State structure that receives the current state of the controller.</param>
			void GetState([Out] State% currentState);
			/// <summary>
			/// Sends data to a connected controller. This function is used to activate the vibration function of a controller.
			/// </summary>
			/// <param name="vibration">Reference structure containing the vibration information to send to the controller.</param>
			void SetState(Vibration% vibration);
			/// <summary>
			/// Retrieves the capabilities and features of a connected controller.
			/// </summary>
			/// <param name="flag">Input flags that identify the device type.</param>
			/// <param name="capabilities">Out reference to Capabilities structure that receives the controller capabilities.</param>
			void GetCapabilities(DeviceQueryType flag, [Out] Capabilities% capabilities);
			/// <summary>
			/// Retrieves the sound rendering and sound capture device GUIDs that are associated with the headset connected to the specified controller.
			/// </summary>
			/// <param name="soundRenderGuid">Out reference to Guid structure that receives the GUID of the headset sound rendering device.</param>
			/// <param name="soundCaptureGuid">Out reference to Guid structure that receives the GUID of the headset sound capture device.</param>
			void GetDirectSoundAudioDeviceGuids([Out] Guid% soundRenderGuid, [Out] Guid% soundCaptureGuid);
			/// <summary>
			/// Retrieves a gamepad input event.
			/// </summary>
			/// <param name="flag">Input flags that identify the device type.</param>
			/// <param name="keystroke">Out reference to KeyStroke structure that receives an input event.</param>
			/// <returns>False if no new keys have been pressed.</returns>
			bool GetKeystroke(DeviceQueryType flag, KeyStroke% keystroke);
		private:
			UInt32 userIndex;
		};
	}
}
