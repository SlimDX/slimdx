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

#include <windows.h>

namespace SlimDX
{
	namespace RawInput
	{
		[System::Flags]
		public enum class DeviceFlags : System::Int32
		{
			NoLegacy = RIDEV_NOLEGACY,
			None = 0
		};

		public enum class InputType : System::Int32
		{
			Keyboard = RIM_TYPEKEYBOARD,
			Mouse = RIM_TYPEMOUSE,
			Other = RIM_TYPEHID
		};

		public enum class Command : System::Int32
		{
			Header = RID_HEADER,
			Input = RID_INPUT
		};

		[System::Flags]
		public enum class ScanCodeFlags : unsigned short
		{
			Break = RI_KEY_BREAK,
			E0 = RI_KEY_E0,
			E1 = RI_KEY_E1,
			Make = RI_KEY_MAKE,
			TerminalServerSetLED = RI_KEY_TERMSRV_SET_LED,
			TerminalServerShadow = RI_KEY_TERMSRV_SHADOW
		};

		[System::Flags]
		public enum class MouseFlags : unsigned short
		{
			AbsoluteMovement = MOUSE_MOVE_ABSOLUTE,
			AttributesChanged = MOUSE_ATTRIBUTES_CHANGED,
			RelativeMovement = MOUSE_MOVE_RELATIVE,
			VirtualDesktopMovement = MOUSE_VIRTUAL_DESKTOP
		};

		[System::Flags]
		public enum class MouseButtonFlags : unsigned short
		{
			None = 0,
			LeftDown = 0x0001,
			LeftUp = 0x0002,
			RightDown = 0x0004,
			RightUp = 0x0008,
			MiddleDown = 0x0010,
			MiddleUp = 0x0020,
			Button4Down = 0x0040,
			Button4Up = 0x0080,
			Button5Down = 0x0100,
			Button5Up = 0x0200,
			MouseWheel = 0x0400
		};

		public enum class KeyState
		{
			Pressed = WM_KEYDOWN,
			Released = WM_KEYUP,
			SystemKeyReleased = WM_SYSKEYUP,
			SystemKeyPressed = WM_SYSKEYDOWN,
			HotKey = WM_HOTKEY,
		};

		public enum class HIDUsagePage : unsigned short
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
			/// <summary>LED controls.</summary>
			LED = 0x08,
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
			PID = 0x0F,
			/// <summary>Unicode.</summary>
			Unicode = 0x10,
			/// <summary>Alphanumeric display.</summary>
			AlphaNumeric = 0x14,
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
			BarCode = 0x8C,
			/// <summary>Scale page.</summary>
			Scale = 0x8D,
			/// <summary>Magnetic strip reading devices.</summary>
			MSR = 0x8E
		};

		public enum class HIDUsage : unsigned short
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
			VBRX = 0x43,
			/// <summary></summary>
			VBRY = 0x44,
			/// <summary></summary>
			VBRZ = 0x45,
			/// <summary></summary>
			VNO = 0x46,
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
			KeyboardLeftALT = 0xE2,
			/// <summary></summary>
			KeyboardLeftGUI = 0xE3,
			/// <summary></summary>
			KeyboardRightControl = 0xE4,
			/// <summary></summary>
			KeyboardRightShift = 0xE5,
			/// <summary></summary>
			KeyboardRightALT = 0xE6,
			/// <summary></summary>
			KeyboardRightGUI = 0xE7,
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
			LEDNumLock = 0x01,
			/// <summary></summary>
			LEDCapsLock = 0x02,
			/// <summary></summary>
			LEDScrollLock = 0x03,
			/// <summary></summary>
			LEDCompose = 0x04,
			/// <summary></summary>
			LEDKana = 0x05,
			/// <summary></summary>
			LEDPower = 0x06,
			/// <summary></summary>
			LEDShift = 0x07,
			/// <summary></summary>
			LEDDoNotDisturb = 0x08,
			/// <summary></summary>
			LEDMute = 0x09,
			/// <summary></summary>
			LEDToneEnable = 0x0A,
			/// <summary></summary>
			LEDHighCutFilter = 0x0B,
			/// <summary></summary>
			LEDLowCutFilter = 0x0C,
			/// <summary></summary>
			LEDEqualizerEnable = 0x0D,
			/// <summary></summary>
			LEDSoundFieldOn = 0x0E,
			/// <summary></summary>
			LEDSurroundFieldOn = 0x0F,
			/// <summary></summary>
			LEDRepeat = 0x10,
			/// <summary></summary>
			LEDStereo = 0x11,
			/// <summary></summary>
			LEDSamplingRateDirect = 0x12,
			/// <summary></summary>
			LEDSpinning = 0x13,
			/// <summary></summary>
			LEDCAV = 0x14,
			/// <summary></summary>
			LEDCLV = 0x15,
			/// <summary></summary>
			LEDRecordingFormatDet = 0x16,
			/// <summary></summary>
			LEDOffHook = 0x17,
			/// <summary></summary>
			LEDRing = 0x18,
			/// <summary></summary>
			LEDMessageWaiting = 0x19,
			/// <summary></summary>
			LEDDataMode = 0x1A,
			/// <summary></summary>
			LEDBatteryOperation = 0x1B,
			/// <summary></summary>
			LEDBatteryOK = 0x1C,
			/// <summary></summary>
			LEDBatteryLow = 0x1D,
			/// <summary></summary>
			LEDSpeaker = 0x1E,
			/// <summary></summary>
			LEDHeadset = 0x1F,
			/// <summary></summary>
			LEDHold = 0x20,
			/// <summary></summary>
			LEDMicrophone = 0x21,
			/// <summary></summary>
			LEDCoverage = 0x22,
			/// <summary></summary>
			LEDNightMode = 0x23,
			/// <summary></summary>
			LEDSendCalls = 0x24,
			/// <summary></summary>
			LEDCallPickup = 0x25,
			/// <summary></summary>
			LEDConference = 0x26,
			/// <summary></summary>
			LEDStandBy = 0x27,
			/// <summary></summary>
			LEDCameraOn = 0x28,
			/// <summary></summary>
			LEDCameraOff = 0x29,
			/// <summary></summary>        
			LEDOnLine = 0x2A,
			/// <summary></summary>
			LEDOffLine = 0x2B,
			/// <summary></summary>
			LEDBusy = 0x2C,
			/// <summary></summary>
			LEDReady = 0x2D,
			/// <summary></summary>
			LEDPaperOut = 0x2E,
			/// <summary></summary>
			LEDPaperJam = 0x2F,
			/// <summary></summary>
			LEDRemote = 0x30,
			/// <summary></summary>
			LEDForward = 0x31,
			/// <summary></summary>
			LEDReverse = 0x32,
			/// <summary></summary>
			LEDStop = 0x33,
			/// <summary></summary>
			LEDRewind = 0x34,
			/// <summary></summary>
			LEDFastForward = 0x35,
			/// <summary></summary>
			LEDPlay = 0x36,
			/// <summary></summary>
			LEDPause = 0x37,
			/// <summary></summary>
			LEDRecord = 0x38,
			/// <summary></summary>
			LEDError = 0x39,
			/// <summary></summary>
			LEDSelectedIndicator = 0x3A,
			/// <summary></summary>
			LEDInUseIndicator = 0x3B,
			/// <summary></summary>
			LEDMultiModeIndicator = 0x3C,
			/// <summary></summary>
			LEDIndicatorOn = 0x3D,
			/// <summary></summary>
			LEDIndicatorFlash = 0x3E,
			/// <summary></summary>
			LEDIndicatorSlowBlink = 0x3F,
			/// <summary></summary>
			LEDIndicatorFastBlink = 0x40,
			/// <summary></summary>
			LEDIndicatorOff = 0x41,
			/// <summary></summary>
			LEDFlashOnTime = 0x42,
			/// <summary></summary>
			LEDSlowBlinkOnTime = 0x43,
			/// <summary></summary>
			LEDSlowBlinkOffTime = 0x44,
			/// <summary></summary>
			LEDFastBlinkOnTime = 0x45,
			/// <summary></summary>
			LEDFastBlinkOffTime = 0x46,
			/// <summary></summary>
			LEDIndicatorColor = 0x47,
			/// <summary></summary>
			LEDRed = 0x48,
			/// <summary></summary>
			LEDGreen = 0x49,
			/// <summary></summary>
			LEDAmber = 0x4A,
			/// <summary></summary>
			LEDGenericIndicator = 0x3B,
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

		public enum class Keys : unsigned short
		{
			/// <summary></summary>
			LeftButton = 0x01,
			/// <summary></summary>
			RightButton = 0x02,
			/// <summary></summary>
			Cancel = 0x03,
			/// <summary></summary>
			MiddleButton = 0x04,
			/// <summary></summary>
			ExtraButton1 = 0x05,
			/// <summary></summary>
			ExtraButton2 = 0x06,
			/// <summary></summary>
			Back = 0x08,
			/// <summary></summary>
			Tab = 0x09,
			/// <summary></summary>
			Clear = 0x0C,
			/// <summary></summary>
			Return = 0x0D,
			/// <summary></summary>
			Shift = 0x10,
			/// <summary></summary>
			Control = 0x11,
			/// <summary></summary>
			Menu = 0x12,
			/// <summary></summary>
			Pause = 0x13,
			/// <summary></summary>
			Kana = 0x15,
			/// <summary></summary>
			Hangeul = 0x15,
			/// <summary></summary>
			Hangul = 0x15,
			/// <summary></summary>
			Junja = 0x17,
			/// <summary></summary>
			Final = 0x18,
			/// <summary></summary>
			Hanja = 0x19,
			/// <summary></summary>
			Kanji = 0x19,
			/// <summary></summary>
			Escape = 0x1B,
			/// <summary></summary>
			Convert = 0x1C,
			/// <summary></summary>
			NonConvert = 0x1D,
			/// <summary></summary>
			Accept = 0x1E,
			/// <summary></summary>
			ModeChange = 0x1F,
			/// <summary></summary>
			Space = 0x20,
			/// <summary></summary>
			Prior = 0x21,
			/// <summary></summary>
			Next = 0x22,
			/// <summary></summary>
			End = 0x23,
			/// <summary></summary>
			Home = 0x24,
			/// <summary></summary>
			Left = 0x25,
			/// <summary></summary>
			Up = 0x26,
			/// <summary></summary>
			Right = 0x27,
			/// <summary></summary>
			Down = 0x28,
			/// <summary></summary>
			Select = 0x29,
			/// <summary></summary>
			Print = 0x2A,
			/// <summary></summary>
			Execute = 0x2B,
			/// <summary></summary>
			Snapshot = 0x2C,
			/// <summary></summary>
			Insert = 0x2D,
			/// <summary></summary>
			Delete = 0x2E,
			/// <summary></summary>
			Help = 0x2F,
			/// <summary></summary>
			N0 = 0x30,
			/// <summary></summary>
			N1 = 0x31,
			/// <summary></summary>
			N2 = 0x32,
			/// <summary></summary>
			N3 = 0x33,
			/// <summary></summary>
			N4 = 0x34,
			/// <summary></summary>
			N5 = 0x35,
			/// <summary></summary>
			N6 = 0x36,
			/// <summary></summary>
			N7 = 0x37,
			/// <summary></summary>
			N8 = 0x38,
			/// <summary></summary>
			N9 = 0x39,
			/// <summary></summary>
			A = 0x41,
			/// <summary></summary>
			B = 0x42,
			/// <summary></summary>
			C = 0x43,
			/// <summary></summary>
			D = 0x44,
			/// <summary></summary>
			E = 0x45,
			/// <summary></summary>
			F = 0x46,
			/// <summary></summary>
			G = 0x47,
			/// <summary></summary>
			H = 0x48,
			/// <summary></summary>
			I = 0x49,
			/// <summary></summary>
			J = 0x4A,
			/// <summary></summary>
			K = 0x4B,
			/// <summary></summary>
			L = 0x4C,
			/// <summary></summary>
			M = 0x4D,
			/// <summary></summary>
			N = 0x4E,
			/// <summary></summary>
			O = 0x4F,
			/// <summary></summary>
			P = 0x50,
			/// <summary></summary>
			Q = 0x51,
			/// <summary></summary>
			R = 0x52,
			/// <summary></summary>
			S = 0x53,
			/// <summary></summary>
			T = 0x54,
			/// <summary></summary>
			U = 0x55,
			/// <summary></summary>
			V = 0x56,
			/// <summary></summary>
			W = 0x57,
			/// <summary></summary>
			X = 0x58,
			/// <summary></summary>
			Y = 0x59,
			/// <summary></summary>
			Z = 0x5A,
			/// <summary></summary>
			LeftWindows = 0x5B,
			/// <summary></summary>
			RightWindows = 0x5C,
			/// <summary></summary>
			Application = 0x5D,
			/// <summary></summary>
			Sleep = 0x5F,
			/// <summary></summary>
			Numpad0 = 0x60,
			/// <summary></summary>
			Numpad1 = 0x61,
			/// <summary></summary>
			Numpad2 = 0x62,
			/// <summary></summary>
			Numpad3 = 0x63,
			/// <summary></summary>
			Numpad4 = 0x64,
			/// <summary></summary>
			Numpad5 = 0x65,
			/// <summary></summary>
			Numpad6 = 0x66,
			/// <summary></summary>
			Numpad7 = 0x67,
			/// <summary></summary>
			Numpad8 = 0x68,
			/// <summary></summary>
			Numpad9 = 0x69,
			/// <summary></summary>
			Multiply = 0x6A,
			/// <summary></summary>
			Add = 0x6B,
			/// <summary></summary>
			Separator = 0x6C,
			/// <summary></summary>
			Subtract = 0x6D,
			/// <summary></summary>
			Decimal = 0x6E,
			/// <summary></summary>
			Divide = 0x6F,
			/// <summary></summary>
			F1 = 0x70,
			/// <summary></summary>
			F2 = 0x71,
			/// <summary></summary>
			F3 = 0x72,
			/// <summary></summary>
			F4 = 0x73,
			/// <summary></summary>
			F5 = 0x74,
			/// <summary></summary>
			F6 = 0x75,
			/// <summary></summary>
			F7 = 0x76,
			/// <summary></summary>
			F8 = 0x77,
			/// <summary></summary>
			F9 = 0x78,
			/// <summary></summary>
			F10 = 0x79,
			/// <summary></summary>
			F11 = 0x7A,
			/// <summary></summary>
			F12 = 0x7B,
			/// <summary></summary>
			F13 = 0x7C,
			/// <summary></summary>
			F14 = 0x7D,
			/// <summary></summary>
			F15 = 0x7E,
			/// <summary></summary>
			F16 = 0x7F,
			/// <summary></summary>
			F17 = 0x80,
			/// <summary></summary>
			F18 = 0x81,
			/// <summary></summary>
			F19 = 0x82,
			/// <summary></summary>
			F20 = 0x83,
			/// <summary></summary>
			F21 = 0x84,
			/// <summary></summary>
			F22 = 0x85,
			/// <summary></summary>
			F23 = 0x86,
			/// <summary></summary>
			F24 = 0x87,
			/// <summary></summary>
			NumLock = 0x90,
			/// <summary></summary>
			ScrollLock = 0x91,
			/// <summary></summary>
			NEC_Equal = 0x92,
			/// <summary></summary>
			Fujitsu_Jisho = 0x92,
			/// <summary></summary>
			Fujitsu_Masshou = 0x93,
			/// <summary></summary>
			Fujitsu_Touroku = 0x94,
			/// <summary></summary>
			Fujitsu_Loya = 0x95,
			/// <summary></summary>
			Fujitsu_Roya = 0x96,
			/// <summary></summary>
			LeftShift = 0xA0,
			/// <summary></summary>
			RightShift = 0xA1,
			/// <summary></summary>
			LeftControl = 0xA2,
			/// <summary></summary>
			RightControl = 0xA3,
			/// <summary></summary>
			LeftMenu = 0xA4,
			/// <summary></summary>
			RightMenu = 0xA5,
			/// <summary></summary>
			BrowserBack = 0xA6,
			/// <summary></summary>
			BrowserForward = 0xA7,
			/// <summary></summary>
			BrowserRefresh = 0xA8,
			/// <summary></summary>
			BrowserStop = 0xA9,
			/// <summary></summary>
			BrowserSearch = 0xAA,
			/// <summary></summary>
			BrowserFavorites = 0xAB,
			/// <summary></summary>
			BrowserHome = 0xAC,
			/// <summary></summary>
			VolumeMute = 0xAD,
			/// <summary></summary>
			VolumeDown = 0xAE,
			/// <summary></summary>
			VolumeUp = 0xAF,
			/// <summary></summary>
			MediaNextTrack = 0xB0,
			/// <summary></summary>
			MediaPrevTrack = 0xB1,
			/// <summary></summary>
			MediaStop = 0xB2,
			/// <summary></summary>
			MediaPlayPause = 0xB3,
			/// <summary></summary>
			LaunchMail = 0xB4,
			/// <summary></summary>
			LaunchMediaSelect = 0xB5,
			/// <summary></summary>
			LaunchApplication1 = 0xB6,
			/// <summary></summary>
			LaunchApplication2 = 0xB7,
			/// <summary></summary>
			OEM1 = 0xBA,
			/// <summary></summary>
			OEMPlus = 0xBB,
			/// <summary></summary>
			OEMComma = 0xBC,
			/// <summary></summary>
			OEMMinus = 0xBD,
			/// <summary></summary>
			OEMPeriod = 0xBE,
			/// <summary></summary>
			OEM2 = 0xBF,
			/// <summary></summary>
			OEM3 = 0xC0,
			/// <summary></summary>
			OEM4 = 0xDB,
			/// <summary></summary>
			OEM5 = 0xDC,
			/// <summary></summary>
			OEM6 = 0xDD,
			/// <summary></summary>
			OEM7 = 0xDE,
			/// <summary></summary>
			OEM8 = 0xDF,
			/// <summary></summary>
			OEMAX = 0xE1,
			/// <summary></summary>
			OEM102 = 0xE2,
			/// <summary></summary>
			ICOHelp = 0xE3,
			/// <summary></summary>
			ICO00 = 0xE4,
			/// <summary></summary>
			ProcessKey = 0xE5,
			/// <summary></summary>
			ICOClear = 0xE6,
			/// <summary></summary>
			Packet = 0xE7,
			/// <summary></summary>
			OEMReset = 0xE9,
			/// <summary></summary>
			OEMJump = 0xEA,
			/// <summary></summary>
			OEMPA1 = 0xEB,
			/// <summary></summary>
			OEMPA2 = 0xEC,
			/// <summary></summary>
			OEMPA3 = 0xED,
			/// <summary></summary>
			OEMWSCtrl = 0xEE,
			/// <summary></summary>
			OEMCUSel = 0xEF,
			/// <summary></summary>
			OEMATTN = 0xF0,
			/// <summary></summary>
			OEMFinish = 0xF1,
			/// <summary></summary>
			OEMCopy = 0xF2,
			/// <summary></summary>
			OEMAuto = 0xF3,
			/// <summary></summary>
			OEMENLW = 0xF4,
			/// <summary></summary>
			OEMBackTab = 0xF5,
			/// <summary></summary>
			ATTN = 0xF6,
			/// <summary></summary>
			CRSel = 0xF7,
			/// <summary></summary>
			EXSel = 0xF8,
			/// <summary></summary>
			EREOF = 0xF9,
			/// <summary></summary>
			Play = 0xFA,
			/// <summary></summary>
			Zoom = 0xFB,
			/// <summary></summary>
			Noname = 0xFC,
			/// <summary></summary>
			PA1 = 0xFD,
			/// <summary></summary>
			OEMClear = 0xFE
		};
	}
}
