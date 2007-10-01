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

namespace SlimDX
{
	namespace XInput
	{
		/// <summary>
		/// Specifies motor speed levels for the vibration function of a controller.
		/// </summary>
		/// <remarks>
		/// The left motor is the low-frequency rumble motor. The right motor is the high-frequency rumble motor. 
		/// The two motors are not the same, and they create different vibration effects.
		/// </remarks>
		[StructLayout(LayoutKind::Sequential)]
		public value class Vibration
		{
		private:
			UInt16 leftMotorSpeed;
			UInt16 rightMotorSpeed;

		public:
			/// <summary>
			/// Speed of the left motor. Valid values are in the range 0 to 65,535. Zero signifies no motor use; 
			/// 65,535 signifies 100 percent motor use.
			/// </summary>
			property UInt16 LeftMotorSpeed
            {
                UInt16 get() { return leftMotorSpeed; }
                void set( UInt16 value ) { leftMotorSpeed = value; }
            }

			/// <summary>
			/// Speed of the right motor. Valid values are in the range 0 to 65,535. Zero signifies no motor use; 
			/// 65,535 signifies 100 percent motor use.
			/// </summary>
            property UInt16 RightMotorSpeed
            {
                UInt16 get() { return rightMotorSpeed; }
                void set( UInt16 value ) { rightMotorSpeed = value; }
            }
		};

		/// <summary>
		/// Bitmask of the device digital buttons
		/// </summary>
		[Flags]
		public enum class GamepadButtons : UInt16
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
			Y = XINPUT_GAMEPAD_Y,
		};
		
		/// <summary>
		/// Describes the current state of the Xbox 360 Controller.
		/// </summary>
		/// <remarks>
		/// Each of the thumbstick axis members is a signed value between -32768 and 32767 describing the position of the thumbstick.
		/// A value of 0 is centered. Negative values signify down or to the left. Positive values signify up or to the right.
		/// The constants GamepadLeftThumbDeadZone or GamepadRightThumbDeadZone can be used as a positive and negative value to filter a
		/// thumbstick input.
		/// </remarks>
		[StructLayout(LayoutKind::Sequential)]
		public value class GamePad
		{
		private:
			GamepadButtons buttons;
            Byte leftTrigger;
            Byte rightTrigger;
            Int16 leftThumbX;
            Int16 leftThumbY;
            Int16 rightThumbX;
            Int16 rightThumbY;

		public:
			/// <summary>
			/// Bitmask of the device digital buttons
			/// </summary>
			property GamepadButtons Buttons
            {
                GamepadButtons get() { return buttons; }
                void set( GamepadButtons value ) { buttons = value; }
            }

			/// <summary>
			/// The current value of the left trigger analog control. The value is between 0 and 255.
			/// </summary>
            property Byte LeftTrigger
            {
                Byte get() { return leftTrigger; }
                void set( Byte value ) { leftTrigger = value; }
            }

			/// <summary>
			/// The current value of the right trigger analog control. The value is between 0 and 255.
			/// </summary>
            property Byte RightTrigger
            {
                Byte get() { return rightTrigger; }
                void set( Byte value ) { rightTrigger = value; }
            }

			/// <summary>
			/// Right thumbstick y-axis value. The value is between -32768 and 32767.
			/// </summary>
            property Int16 LeftThumbX
            {
                Int16 get() { return leftThumbX; }
                void set( Int16 value ) { leftThumbX = value; }
            }

			/// <summary>
			/// Left thumbstick y-axis value. The value is between -32768 and 32767.
			/// </summary>
            property Int16 LeftThumbY
            {
                Int16 get() { return leftThumbY; }
                void set( Int16 value ) { leftThumbY = value; }
            }

			/// <summary>
			/// Right thumbstick x-axis value. The value is between -32768 and 32767.
			/// </summary>
            property Int16 RightThumbX
            {
                Int16 get() { return rightThumbX; }
                void set( Int16 value ) { rightThumbX = value; }
            }

			/// <summary>
			/// Right thumbstick y-axis value. The value is between -32768 and 32767.
			/// </summary>
            property Int16 RightThumbY
            {
                Int16 get() { return rightThumbY; }
                void set( Int16 value ) { rightThumbY = value; }
            }

			/// <summary>
			/// Can be used as a positive and negative value to filter the left thumbstick input.
			/// </summary>
			literal Int16 GamepadLeftThumbDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

			/// <summary>
			/// Can be used as a positive and negative value to filter the right thumbstick input.
			/// </summary>
			literal Int16 GamepadRightThumbDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

			/// <summary>
			/// This constantmay be used as the value which LeftTrigger and RightTrigger must be greater than to register as pressed.
			/// </summary>
			literal Byte GamepadTriggerThreshold = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
		};

		/// <summary>
		/// Flags that indicate the keyboard state at the time of the input event.
		/// </summary>
		[Flags]
		public enum class KeyStrokeFlags : UInt16
		{
			None = 0,
			KeyDown = XINPUT_KEYSTROKE_KEYDOWN,
			KeyUp = XINPUT_KEYSTROKE_KEYUP,
			Repeat = XINPUT_KEYSTROKE_REPEAT
		};

		/// <summary>
		/// Controller input virtual key codes
		/// </summary>
		public enum class GamepadKeyCodes : UInt16
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

		
		/// <summary>
		/// Specifies keystroke data returned by Controller.GetKeystroke
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value class KeyStroke
		{
		private:
			GamepadKeyCodes virtualKey;
            Char unicode;
            KeyStrokeFlags flags;
            Byte userIndex;
            Byte hidCode;

		public:
			/// <summary>
			/// Virtual-key code of the key, button, or stick movement.
			/// </summary>
			property GamepadKeyCodes VirtualKey
            {
                GamepadKeyCodes get() { return virtualKey; }
                void set( GamepadKeyCodes value ) { virtualKey = value; }
            }

			/// <summary>
			/// Unused and should be zero.
			/// </summary>
            property Char Unicode
            {
                Char get() { return unicode; }
                void set( Char value ) { unicode = value; }
            }

			/// <summary>
			/// Combination of flags that indicate the keyboard state at the time of the input event.
			/// </summary>
            property KeyStrokeFlags Flags
            {
                KeyStrokeFlags get() { return flags; }
                void set( KeyStrokeFlags value ) { flags = value; }
            }

			/// <summary>
			/// Index of the signed-in gamer associated with the device. Can be a value in the range 0–3.
			/// </summary>
            property Byte UserIndex
            {
                Byte get() { return userIndex; }
                void set( Byte value ) { userIndex = value; }
            }

			/// <summary>
			/// HID code corresponding to the input. If there is no corresponding HID code, this value is zero.
			/// </summary>
            property Byte HidCode
            {
                Byte get() { return hidCode; }
                void set( Byte value ) { hidCode = value; }
            }
		};
		
		/// <summary>
		/// Represents the state of a controller.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value class State
		{
		private:
			UInt32 packetNumber;
            GamePad gamepad;

		public:
			/// <summary>
			/// State packet number. The packet number indicates whether there have been any changes in the state of the controller.
			/// If the PacketNumber member is the same in sequentially returned State structures, the controller state has not changed. 
			/// </summary>
			property UInt32 PacketNumber
            {
                UInt32 get() { return packetNumber; }
                void set( UInt32 value ) { packetNumber = value; }
            }

			/// <summary>
			/// GamePad structure containing the current state of an Xbox 360 Controller. 
			/// </summary>
            property GamePad Gamepad
            {
                GamePad get() { return gamepad; }
                void set( GamePad value ) { gamepad = value; }
            }
		};

		/// <summary>
		/// Controller type.
		/// </summary>
		public enum class DeviceType : Byte
		{
			/// <summary>
			/// The device is a game controller.
			/// </summary>
			Gamepad = XINPUT_DEVTYPE_GAMEPAD
		};

		/// <summary>
		/// Subtype of the game controller.
		/// </summary>
		public enum class DeviceSubType : Byte
		{
			ArcadeStick = XINPUT_DEVSUBTYPE_ARCADE_STICK,
			Gamepad = XINPUT_DEVSUBTYPE_GAMEPAD,
			Wheel = XINPUT_DEVSUBTYPE_WHEEL,
			DancePad = XINPUT_DEVSUBTYPE_DANCE_PAD,
			FlightStick = XINPUT_DEVSUBTYPE_FLIGHT_SICK
		};

		
		/// <summary>
		/// Features of the controller. 
		/// </summary>
		[Flags]
		public enum class CapabilitiesFlags : UInt16
		{
			None = 0,

			/// <summary>
			/// The device has an integrated voice device.
			/// </summary>
			VoiceSupported = XINPUT_CAPS_VOICE_SUPPORTED
		};
		
		/// <summary>
		/// Describes the capabilities of a connected controller.
		/// </summary>
		/// <remarks>
		/// Sets the structure members to indicate which inputs the device supports. For binary state controls, such as digital buttons, the corresponding bit reflects
		/// whether or not the control is supported by the device. For proportional controls, such as thumbsticks, the value indicates the resolution for that control.
		/// Some number of the least significant bits may not be set, indicating that the control does not provide resolution to that level.
		/// </remarks>
		[StructLayout(LayoutKind::Sequential)]
		public value class Capabilities
		{
		private:
            DeviceType type;
            DeviceSubType subType;
            CapabilitiesFlags flags;
            GamePad gamepad;
            Vibration vibration;

		public:
			/// <summary>
			/// Controller type.
			/// </summary>
			property DeviceType Type
            {
                DeviceType get() { return type; }
                void set( DeviceType value ) { type = value; }
            }

			/// <summary>
			/// Subtype of the game controller. 
			/// </summary>
            property DeviceSubType SubType
            {
                DeviceSubType get() { return subType; }
                void set( DeviceSubType value ) { subType = value; }
            }

			/// <summary>
			/// Features of the controller. 
			/// </summary>
            property CapabilitiesFlags Flags
            {
                CapabilitiesFlags get() { return flags; }
                void set( CapabilitiesFlags value ) { flags = value; }
            }

			/// <summary>
			/// GamePad structure that describes available controller features and control resolutions. 
			/// </summary>
            property GamePad Gamepad
            {
                GamePad get() { return gamepad; }
                void set( GamePad value ) { gamepad = value; }
            }

			/// <summary>
			/// Vibration structure that describes available vibration functionality and resolutions. 
			/// </summary>
            property SlimDX::XInput::Vibration Vibration
            {
                SlimDX::XInput::Vibration get() { return vibration; }
                void set( SlimDX::XInput::Vibration value ) { vibration = value; }
            }
		};

		/// <summary>
		/// Flags for battery type
		/// </summary>
		public enum class BatteryType : Byte
		{
			Disconnected = BATTERY_TYPE_DISCONNECTED,
			Wired = BATTERY_TYPE_WIRED,
			Alkaline = BATTERY_TYPE_ALKALINE,
			NickelMetalHydride = BATTERY_TYPE_NIMH,
			Unknown = BATTERY_TYPE_UNKNOWN
		};

		/// <summary>
		/// The amount of charge remaining in the battery.
		/// </summary>
		/// <remarks>
		/// These are only valid for wireless, connected devices, with known battery types. The amount of use time remaining depends on the type of device.
		/// </remarks>
		public enum class BatteryLevel : Byte
		{
			Empty = BATTERY_LEVEL_EMPTY,
			Low = BATTERY_LEVEL_LOW,
			Medium = BATTERY_LEVEL_MEDIUM,
			Full = BATTERY_LEVEL_FULL
		};

		public value class BatteryInformation
		{
			BatteryType Type;
			BatteryLevel Level;
		};

		/// <summary>
		/// Flags that identify the device type.
		/// </summary>
		public enum class DeviceQueryType : Int32
		{
			Any = 0,
			GamePad = XINPUT_FLAG_GAMEPAD
		};

		/// <summary>
		/// Devices that support batteries.
		/// </summary>
		public enum class BatteryDeviceType : Byte
		{
			Gamepad = BATTERY_DEVTYPE_GAMEPAD,
			Headset = BATTERY_DEVTYPE_HEADSET
		};

		/// <summary>
		/// Index of the signed-in gamer associated with the device.
		/// </summary>
		public enum class UserIndex : UInt32
		{
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
		public ref class Controller
		{
		private:
			UInt32 userIndex;

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
			bool GetKeystroke(DeviceQueryType flag, [Out] KeyStroke% keystroke);

			/// <summary>
			/// Gets information on the controllers battery.
			/// </summary>
			/// <param name="flag">Input flags that identify the device type.</param>
			/// <param name="batteryInfo">Out reference to BatteryInformation structure that receives the battery status information.</param>
			void GetBatteryInformation(BatteryDeviceType flag, [Out] BatteryInformation% batteryInfo);

			/// <summary>
			/// Tests if the controller is currently connected. 
			/// </summary>
			/// <remarks>
			/// Wireless controllers are not considered active upon system startup, and calls to any of the XInput functions before a wireless controller
			/// is made active return ERROR_DEVICE_NOT_CONNECTED. Game titles must examine the return code and be prepared to handle this condition.
			/// Wired controllers are automatically activated when they are inserted. Wireless controllers are activated when the user presses the START
			/// or Xbox Guide button to power on the controller.
			/// </remarks>
			property bool IsConnected { bool get(); }
		};
	}
}
