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

namespace SlimDX
{
	namespace RawInput
	{
		// NOTE: The enumerations defined in this file are in alphabetical order. When
		//       adding new enumerations or renaming existing ones, please make sure
		//       the ordering is maintained.

		[System::Flags]
		public enum class DeviceFlags : System::Int32
		{
			None = 0,
			ApplicationKeys = RIDEV_APPKEYS,
			CaptureMouse = RIDEV_CAPTUREMOUSE,
			InputSink = RIDEV_INPUTSINK,
			NoHotkeys = RIDEV_NOHOTKEYS,
			NoLegacy = RIDEV_NOLEGACY,
		};

		public enum class DeviceType : System::Int32
		{
			Keyboard = RIM_TYPEKEYBOARD,
			Mouse = RIM_TYPEMOUSE,
			HumanInputDevice = RIM_TYPEHID
		};

		[System::Flags]
		public enum class ScanCodeFlags : System::Int32
		{
			Make = RI_KEY_MAKE,
			Break = RI_KEY_BREAK,
			E0 = RI_KEY_E0,
			E1 = RI_KEY_E1,
			TerminalServerSetLed = RI_KEY_TERMSRV_SET_LED,
			TerminalServerShadow = RI_KEY_TERMSRV_SHADOW
		};

		public enum class KeyState
		{
			Pressed = WM_KEYDOWN,
			Released = WM_KEYUP,
			SystemKeyReleased = WM_SYSKEYUP,
			SystemKeyPressed = WM_SYSKEYDOWN,
			Hotkey = WM_HOTKEY,
		};

		[System::Flags]
		public enum class MouseButtonFlags : System::Int32
		{
			None = 0,
			LeftDown = RI_MOUSE_LEFT_BUTTON_DOWN,
			LeftUp = RI_MOUSE_LEFT_BUTTON_UP,
			RightDown = RI_MOUSE_RIGHT_BUTTON_DOWN,
			RightUp = RI_MOUSE_RIGHT_BUTTON_UP,
			MiddleDown = RI_MOUSE_MIDDLE_BUTTON_DOWN,
			MiddleUp = RI_MOUSE_MIDDLE_BUTTON_UP,
			Button4Down = RI_MOUSE_BUTTON_4_DOWN,
			Button4Up = RI_MOUSE_BUTTON_4_UP,
			Button5Down = RI_MOUSE_BUTTON_5_DOWN,
			Button5Up = RI_MOUSE_BUTTON_5_UP,
			MouseWheel = RI_MOUSE_WHEEL
		};

		[System::Flags]
		public enum class MouseState : System::Int32
		{
			AbsoluteMovement = MOUSE_MOVE_ABSOLUTE,
			AttributesChanged = MOUSE_ATTRIBUTES_CHANGED,
			RelativeMovement = MOUSE_MOVE_RELATIVE,
			VirtualDesktopMovement = MOUSE_VIRTUAL_DESKTOP
		};

		public enum class UsageId : System::Int32
		{
			/// <summary></summary>
			Pointer = 0x01,
			/// <summary></summary>
			Mouse = 0x02,
			/// <summary></summary>
			Joystick = 0x04,
			/// <summary></summary>
			Gamepad = 0x05,
			/// <summary></summary>
			Keyboard = 0x06,
			/// <summary></summary>
			Keypad = 0x07,
			/// <summary></summary>
			SystemControl = 0x80,
			/// <summary></summary>
			X = 0x30,
			/// <summary></summary>
			Y = 0x31,
			/// <summary></summary>
			Z = 0x32,
			/// <summary></summary>
			RelativeX = 0x33,
			/// <summary></summary>        
			RelativeY = 0x34,
			/// <summary></summary>
			RelativeZ = 0x35,
			/// <summary></summary>
			Slider = 0x36,
			/// <summary></summary>
			Dial = 0x37,
			/// <summary></summary>
			Wheel = 0x38,
			/// <summary></summary>
			HatSwitch = 0x39,
			/// <summary></summary>
			CountedBuffer = 0x3A,
			/// <summary></summary>
			ByteCount = 0x3B,
			/// <summary></summary>
			MotionWakeup = 0x3C,
			/// <summary></summary>
			VX = 0x40,
			/// <summary></summary>
			VY = 0x41,
			/// <summary></summary>
			VZ = 0x42,
			/// <summary></summary>
			VbrX = 0x43,
			/// <summary></summary>
			VbrY = 0x44,
			/// <summary></summary>
			VbrZ = 0x45,
			/// <summary></summary>
			Vno = 0x46,
			/// <summary></summary>
			SystemControlPower = 0x81,
			/// <summary></summary>
			SystemControlSleep = 0x82,
			/// <summary></summary>
			SystemControlWake = 0x83,
			/// <summary></summary>
			SystemControlContextMenu = 0x84,
			/// <summary></summary>
			SystemControlMainMenu = 0x85,
			/// <summary></summary>
			SystemControlApplicationMenu = 0x86,
			/// <summary></summary>
			SystemControlHelpMenu = 0x87,
			/// <summary></summary>
			SystemControlMenuExit = 0x88,
			/// <summary></summary>
			SystemControlMenuSelect = 0x89,
			/// <summary></summary>
			SystemControlMenuRight = 0x8A,
			/// <summary></summary>
			SystemControlMenuLeft = 0x8B,
			/// <summary></summary>
			SystemControlMenuUp = 0x8C,
			/// <summary></summary>
			SystemControlMenuDown = 0x8D,
			/// <summary></summary>
			KeyboardNoEvent = 0x00,
			/// <summary></summary>
			KeyboardRollover = 0x01,
			/// <summary></summary>
			KeyboardPostFail = 0x02,
			/// <summary></summary>
			KeyboardUndefined = 0x03,
			/// <summary></summary>
			KeyboardaA = 0x04,
			/// <summary></summary>
			KeyboardzZ = 0x1D,
			/// <summary></summary>
			Keyboard1 = 0x1E,
			/// <summary></summary>
			Keyboard0 = 0x27,
			/// <summary></summary>
			KeyboardLeftControl = 0xE0,
			/// <summary></summary>
			KeyboardLeftShift = 0xE1,
			/// <summary></summary>
			KeyboardLeftAlt = 0xE2,
			/// <summary></summary>
			KeyboardLeftGui = 0xE3,
			/// <summary></summary>
			KeyboardRightControl = 0xE4,
			/// <summary></summary>
			KeyboardRightShift = 0xE5,
			/// <summary></summary>
			KeyboardRightAlt = 0xE6,
			/// <summary></summary>
			KeyboardRightGui = 0xE7,
			/// <summary></summary>
			KeyboardScrollLock = 0x47,
			/// <summary></summary>
			KeyboardNumLock = 0x53,
			/// <summary></summary>
			KeyboardCapsLock = 0x39,
			/// <summary></summary>
			KeyboardF1 = 0x3A,
			/// <summary></summary>
			KeyboardF12 = 0x45,
			/// <summary></summary>
			KeyboardReturn = 0x28,
			/// <summary></summary>
			KeyboardEscape = 0x29,
			/// <summary></summary>
			KeyboardDelete = 0x2A,
			/// <summary></summary>
			KeyboardPrintScreen = 0x46,
			/// <summary></summary>
			LedNumLock = 0x01,
			/// <summary></summary>
			LedCapsLock = 0x02,
			/// <summary></summary>
			LedScrollLock = 0x03,
			/// <summary></summary>
			LedCompose = 0x04,
			/// <summary></summary>
			LedKana = 0x05,
			/// <summary></summary>
			LedPower = 0x06,
			/// <summary></summary>
			LedShift = 0x07,
			/// <summary></summary>
			LedDoNotDisturb = 0x08,
			/// <summary></summary>
			LedMute = 0x09,
			/// <summary></summary>
			LedToneEnable = 0x0A,
			/// <summary></summary>
			LedHighCutFilter = 0x0B,
			/// <summary></summary>
			LedLowCutFilter = 0x0C,
			/// <summary></summary>
			LedEqualizerEnable = 0x0D,
			/// <summary></summary>
			LedSoundFieldOn = 0x0E,
			/// <summary></summary>
			LedSurroundFieldOn = 0x0F,
			/// <summary></summary>
			LedRepeat = 0x10,
			/// <summary></summary>
			LedStereo = 0x11,
			/// <summary></summary>
			LedSamplingRateDirect = 0x12,
			/// <summary></summary>
			LedSpinning = 0x13,
			/// <summary></summary>
			LedCav = 0x14,
			/// <summary></summary>
			LedClv = 0x15,
			/// <summary></summary>
			LedRecordingFormatDet = 0x16,
			/// <summary></summary>
			LedOffHook = 0x17,
			/// <summary></summary>
			LedRing = 0x18,
			/// <summary></summary>
			LedMessageWaiting = 0x19,
			/// <summary></summary>
			LedDataMode = 0x1A,
			/// <summary></summary>
			LedBatteryOperation = 0x1B,
			/// <summary></summary>
			LedBatteryOk = 0x1C,
			/// <summary></summary>
			LedBatteryLow = 0x1D,
			/// <summary></summary>
			LedSpeaker = 0x1E,
			/// <summary></summary>
			LedHeadset = 0x1F,
			/// <summary></summary>
			LedHold = 0x20,
			/// <summary></summary>
			LedMicrophone = 0x21,
			/// <summary></summary>
			LedCoverage = 0x22,
			/// <summary></summary>
			LedNightMode = 0x23,
			/// <summary></summary>
			LedSendCalls = 0x24,
			/// <summary></summary>
			LedCallPickup = 0x25,
			/// <summary></summary>
			LedConference = 0x26,
			/// <summary></summary>
			LedStandby = 0x27,
			/// <summary></summary>
			LedCameraOn = 0x28,
			/// <summary></summary>
			LedCameraOff = 0x29,
			/// <summary></summary>        
			LedOnline = 0x2A,
			/// <summary></summary>
			LedOffline = 0x2B,
			/// <summary></summary>
			LedBusy = 0x2C,
			/// <summary></summary>
			LedReady = 0x2D,
			/// <summary></summary>
			LedPaperOut = 0x2E,
			/// <summary></summary>
			LedPaperJam = 0x2F,
			/// <summary></summary>
			LedRemote = 0x30,
			/// <summary></summary>
			LedForward = 0x31,
			/// <summary></summary>
			LedReverse = 0x32,
			/// <summary></summary>
			LedStop = 0x33,
			/// <summary></summary>
			LedRewind = 0x34,
			/// <summary></summary>
			LedFastForward = 0x35,
			/// <summary></summary>
			LedPlay = 0x36,
			/// <summary></summary>
			LedPause = 0x37,
			/// <summary></summary>
			LedRecord = 0x38,
			/// <summary></summary>
			LedError = 0x39,
			/// <summary></summary>
			LedSelectedIndicator = 0x3A,
			/// <summary></summary>
			LedInUseIndicator = 0x3B,
			/// <summary></summary>
			LedMultimodeIndicator = 0x3C,
			/// <summary></summary>
			LedIndicatorOn = 0x3D,
			/// <summary></summary>
			LedIndicatorFlash = 0x3E,
			/// <summary></summary>
			LedIndicatorSlowBlink = 0x3F,
			/// <summary></summary>
			LedIndicatorFastBlink = 0x40,
			/// <summary></summary>
			LedIndicatorOff = 0x41,
			/// <summary></summary>
			LedFlashOnTime = 0x42,
			/// <summary></summary>
			LedSlowBlinkOnTime = 0x43,
			/// <summary></summary>
			LedSlowBlinkOffTime = 0x44,
			/// <summary></summary>
			LedFastBlinkOnTime = 0x45,
			/// <summary></summary>
			LedFastBlinkOffTime = 0x46,
			/// <summary></summary>
			LedIndicatorColor = 0x47,
			/// <summary></summary>
			LedRed = 0x48,
			/// <summary></summary>
			LedGreen = 0x49,
			/// <summary></summary>
			LedAmber = 0x4A,
			/// <summary></summary>
			LedGenericIndicator = 0x3B,
			/// <summary></summary>
			TelephonyPhone = 0x01,
			/// <summary></summary>
			TelephonyAnsweringMachine = 0x02,
			/// <summary></summary>
			TelephonyMessageControls = 0x03,
			/// <summary></summary>
			TelephonyHandset = 0x04,
			/// <summary></summary>
			TelephonyHeadset = 0x05,
			/// <summary></summary>
			TelephonyKeypad = 0x06,
			/// <summary></summary>
			TelephonyProgrammableButton = 0x07,
			/// <summary></summary>
			SimulationRudder = 0xBA,
			/// <summary></summary>
			SimulationThrottle = 0xBB
		};

		public enum class UsagePage : System::Int32
		{
			Undefined = 0x00,
			/// <summary>Generic desktop controls.</summary>
			Generic = 0x01,
			/// <summary>Simulation controls.</summary>
			Simulation = 0x02,
			/// <summary>Virtual reality controls.</summary>
			VR = 0x03,
			/// <summary>Sports controls.</summary>
			Sport = 0x04,
			/// <summary>Games controls.</summary>
			Game = 0x05,
			/// <summary>Keyboard controls.</summary>
			Keyboard = 0x07,
			/// <summary>Led controls.</summary>
			Led = 0x08,
			/// <summary>Button.</summary>
			Button = 0x09,
			/// <summary>Ordinal.</summary>
			Ordinal = 0x0A,
			/// <summary>Telephony.</summary>
			Telephony = 0x0B,
			/// <summary>Consumer.</summary>
			Consumer = 0x0C,
			/// <summary>Digitizer.</summary>
			Digitizer = 0x0D,
			/// <summary>Physical interface device.</summary>
			Pid = 0x0F,
			/// <summary>Unicode.</summary>
			Unicode = 0x10,
			/// <summary>Alphanumeric display.</summary>
			Alphanumeric = 0x14,
			/// <summary>Medical instruments.</summary>
			Medical = 0x40,
			/// <summary>Monitor page 0.</summary>
			MonitorPage0 = 0x80,
			/// <summary>Monitor page 1.</summary>
			MonitorPage1 = 0x81,
			/// <summary>Monitor page 2.</summary>
			MonitorPage2 = 0x82,
			/// <summary>Monitor page 3.</summary>
			MonitorPage3 = 0x83,
			/// <summary>Power page 0.</summary>
			PowerPage0 = 0x84,
			/// <summary>Power page 1.</summary>
			PowerPage1 = 0x85,
			/// <summary>Power page 2.</summary>
			PowerPage2 = 0x86,
			/// <summary>Power page 3.</summary>
			PowerPage3 = 0x87,
			/// <summary>Bar code scanner.</summary>
			Barcode = 0x8C,
			/// <summary>Scale page.</summary>
			Scale = 0x8D,
			/// <summary>Magnetic strip reading devices.</summary>
			Msr = 0x8E
		};
	}
}