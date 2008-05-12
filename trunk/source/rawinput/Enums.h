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
			InputSinkExtended = RIDEV_EXINPUTSINK,
			NoHotKeys = RIDEV_NOHOTKEYS,
			NoLegacy = RIDEV_NOLEGACY,
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
	}
}