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

#include <xinput.h>

namespace SlimDX
{
	namespace XInput
	{
		// NOTE: The enumerations defined in this file are in alphabetical order. When
		//       adding new enumerations or renaming existing ones, please make sure
		//       the ordering is maintained.
		
		public enum class BatteryDeviceType : System::Int32
		{
			Gamepad = BATTERY_DEVTYPE_GAMEPAD,
			Headset = BATTERY_DEVTYPE_HEADSET
		};
		
		/// <summary>
		/// Values indicating the amount of charge remaining in a battery.
		/// </summary>
		/// <remarks>
		/// These are only valid for wireless, connected devices, with known battery types. The amount of use time remaining depends on the type of device.
		/// </remarks>
		public enum class BatteryLevel : System::Int32
		{
			Empty = BATTERY_LEVEL_EMPTY,
			Low = BATTERY_LEVEL_LOW,
			Medium = BATTERY_LEVEL_MEDIUM,
			Full = BATTERY_LEVEL_FULL
		};
		
		public enum class BatteryType : System::Int32
		{
			Disconnected = BATTERY_TYPE_DISCONNECTED,
			Wired = BATTERY_TYPE_WIRED,
			Alkaline = BATTERY_TYPE_ALKALINE,
			NickelMetalHydride = BATTERY_TYPE_NIMH,
			Unknown = BATTERY_TYPE_UNKNOWN
		};
		
		[System::Flags]
		public enum class CapabilityFlags : System::Int32
		{
			None = 0,

			/// <summary>
			/// The device has an integrated voice device.
			/// </summary>
			VoiceSupported = XINPUT_CAPS_VOICE_SUPPORTED
		};
		
		/// <summary>
		/// Vales specifying controller type.
		/// </summary>
		public enum class DeviceType : System::Int32
		{
			/// <summary>
			/// The device is a game controller.
			/// </summary>
			Gamepad = XINPUT_DEVTYPE_GAMEPAD
		};
		
		public enum class DeviceQueryType : System::Int32
		{
			Any = 0,
			Gamepad = XINPUT_FLAG_GAMEPAD
		};
		
		/// <summary>
		/// Values specifying controller subtype.
		/// </summary>
		public enum class DeviceSubtype : System::Int32
		{
			ArcadeStick = XINPUT_DEVSUBTYPE_ARCADE_STICK,
			Gamepad = XINPUT_DEVSUBTYPE_GAMEPAD,
			Wheel = XINPUT_DEVSUBTYPE_WHEEL,
			DancePad = XINPUT_DEVSUBTYPE_DANCE_PAD,
			FlightStick = XINPUT_DEVSUBTYPE_FLIGHT_SICK
		};
		
		[System::Flags]
		public enum class GamepadButtonFlags : System::UInt16
		{
			None = 0,
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
			Y = XINPUT_GAMEPAD_Y
		};
		
		public enum class GamepadKeyCode : System::Int32
		{
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
		
		[System::Flags]
		public enum class KeystrokeFlags : System::Int32
		{
			None = 0,
			KeyDown = XINPUT_KEYSTROKE_KEYDOWN,
			KeyUp = XINPUT_KEYSTROKE_KEYUP,
			Repeat = XINPUT_KEYSTROKE_REPEAT
		};

		public enum class UserIndex : System::Int32
		{
			Any = XUSER_INDEX_ANY,
			One = 0,
			Two = 1,
			Three = 2,
			Four = 3
		};
	}
}