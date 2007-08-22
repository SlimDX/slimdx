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

namespace SlimDX
{
	namespace DirectInput
	{
		/// <summary>
		/// Specifies other attributes of a data format.
		/// </summary>
		public enum class DataFormatFlags : Int32
		{
			/// <summary>
			/// The axes are in absolute mode.
			/// </summary>
			AbsoluteAxis = DIDF_ABSAXIS,

			/// <summary>
			/// The axes are in relative mode.
			/// </summary>
			RelativeAxis = DIDF_RELAXIS
		};

		/// <summary>
		/// Specifies the main type of a DirectInput device.
		/// </summary>
		public enum class DeviceType : Int32
		{
			/// <summary>
			/// A first-person action game device.
			/// </summary>
			FirstPerson = DI8DEVTYPE_1STPERSON,

			/// <summary>
			/// A device that does not fall into any other category.
			/// </summary>
			Other = DI8DEVTYPE_DEVICE,

			/// <summary>
			/// Input device used to control another type of device from within the context of
			/// the application.
			/// </summary>
			ControlDevice = DI8DEVTYPE_DEVICECTRL,

			/// <summary>
			/// A device for steering.
			/// </summary>
			Driving = DI8DEVTYPE_DRIVING,

			/// <summary>
			/// Controller for a flight simulation.
			/// </summary>
			Flight = DI8DEVTYPE_FLIGHT,

			/// <summary>
			/// A console game pad.
			/// </summary>
			GamePad = DI8DEVTYPE_GAMEPAD,

			/// <summary>
			/// A generic joystick.
			/// </summary>
			Joystick = DI8DEVTYPE_JOYSTICK,

			/// <summary>
			/// A keyboard or keyboard-like device.
			/// </summary>
			Keyboard = DI8DEVTYPE_KEYBOARD,

			/// <summary>
			/// A mouse or mouse-like device.
			/// </summary>
			Mouse = DI8DEVTYPE_MOUSE,

			/// <summary>
			/// A remote-control device.
			/// </summary>
			Remote = DI8DEVTYPE_REMOTE,

			/// <summary>
			/// A screen pointer device.
			/// </summary>
			ScreenPointer = DI8DEVTYPE_SCREENPOINTER,

			/// <summary>
			/// A specialized device with functionality unsuitable for main control of an application,
			/// such as pedals with a wheel.
			/// </summary>
			Supplemental = DI8DEVTYPE_SUPPLEMENTAL
		};

		/// <summary>
		/// Specifies the flags that can be associated with a DirectInput device.
		/// </summary>
		[Flags]
		public enum class DeviceFlags : Int32
		{
			/// <summary>
			/// The device is a duplicate of another DirectInput device.
			/// </summary>
			Alias = DIDC_ALIAS,

			/// <summary>
			/// The device is physically attached to the user's computer.
			/// </summary>
			Attached = DIDC_ATTACHED,

			/// <summary>
			/// The device supports deadband for at least one force-feedback condition.
			/// </summary>
			DeadBand = DIDC_DEADBAND,

			/// <summary>
			/// Specifies that the device's data is coming from a user mode device interface.
			/// </summary>
			Emulated = DIDC_EMULATED,

			/// <summary>
			/// The device supports force-feedback.
			/// </summary>
			ForceFeedback = DIDC_FORCEFEEDBACK,

			/// <summary>
			/// The force-feedback system supports the fade parameter for at least one effect.
			/// </summary>
			ForceFeedbackFade = DIDC_FFFADE,

			/// <summary>
			/// The force-feedback system supports the attack parameter for at least one effect.
			/// </summary>
			ForceFeedbackAttack = DIDC_FFATTACK,

			/// <summary>
			/// The device is a fictious device created by a device driver so that is can generate
			/// mouse and keyboard events.
			/// </summary>
			Hidden = DIDC_HIDDEN,

			/// <summary>
			/// The device is a placeholder.
			/// </summary>
			Phantom = DIDC_PHANTOM,

			/// <summary>
			/// At least one object in the current data format is polled, rather than interrupt driven.
			/// </summary>
			PolledDataFormat = DIDC_POLLEDDATAFORMAT,

			/// <summary>
			/// At least one object on the device is polled, rather than interrupt driven.
			/// </summary>
			PolledDevice = DIDC_POLLEDDEVICE,

			/// <summary>
			/// The force-feedback system supports two coefficient values for conditions.
			/// </summary>
			PositiveNegativeCoefficients = DIDC_POSNEGCOEFFICIENTS,

			/// <summary>
			/// The force-feedback system supports a maximum saturation for both positive and negative
			/// force output for at least one condition.
			/// </summary>
			PositiveNegativeSaturation = DIDC_POSNEGSATURATION,

			/// <summary>
			/// The force-feedback system supports the saturation of condition effects for at least
			/// one condition.
			/// </summary>
			Saturation = DIDC_SATURATION,

			/// <summary>
			/// The force-feedback system supports the start delay parameter for at least one effect.
			/// </summary>
			StartDelay = DIDC_STARTDELAY
		};

		/// <summary>
		/// Specifies the cooperative level for a DirectInput device.
		/// </summary>
		[Flags]
		public enum class CooperativeLevel : Int32
		{
			/// <summary>
			/// Exclusive access to the device.
			/// </summary>
			Exclusive = DISCL_EXCLUSIVE,

			/// <summary>
			/// Non exclusive access to the device.
			/// </summary>
			NonExclusive = DISCL_NONEXCLUSIVE,

			/// <summary>
			/// Foreground operation of the device.
			/// </summary>
			Foreground = DISCL_FOREGROUND,

			/// <summary>
			/// Background operation of the device.
			/// </summary>
			Background = DISCL_BACKGROUND,

			/// <summary>
			/// Disables the Windows logo key.
			/// </summary>
			NoWinKey = DISCL_NOWINKEY,
		};

		/// <summary>
		/// The data format for a DirectInput device.
		/// </summary>
		public enum class DeviceDataFormat : Int32
		{
			/// <summary>
			/// Keyboard data.
			/// </summary>
			Keyboard,

			/// <summary>
			/// Mouse data.
			/// </summary>
			Mouse,

			/// <summary>
			/// Joystick data.
			/// </summary>
			Joystick
		};

		/// <summary>
		/// Defines possible keyboard key codes.
		/// </summary>
		public enum class Key : Int32
		{
			/// <summary>
			/// The Escape key.
			/// </summary>
			Escape = 1,

			/// <summary>
			/// The letter Q key.
			/// </summary>
			Q = 16,

			/// <summary>
			/// The Tab key.
			/// </summary>
			Tab = 15,

			/// <summary>
			/// The Back navigation key.
			/// </summary>
			Back = 14,

			/// <summary>
			/// The equals key.
			/// </summary>
			Equals = 13,

			/// <summary>
			/// The minus/subtraction key.
			/// </summary>
			Minus = 12,

			/// <summary>
			/// The number 0 key.
			/// </summary>
			D0 = 11,

			/// <summary>
			/// The number 0 key.
			/// </summary>
			D9 = 10,

			/// <summary>
			/// The number 9 key.
			/// </summary>
			D8 = 9,

			/// <summary>
			/// The number 8 key.
			/// </summary>
			D7 = 8,

			/// <summary>
			/// The number 7 key.
			/// </summary>
			D6 = 7,

			/// <summary>
			/// The number 6 key.
			/// </summary>
			D5 = 6,

			/// <summary>
			/// The number 5 key.
			/// </summary>
			D4 = 5,

			/// <summary>
			/// The number 4 key.
			/// </summary>
			D3 = 4,

			/// <summary>
			/// The number 3 key.
			/// </summary>
			D2 = 3,

			/// <summary>
			/// The number 2 key.
			/// </summary>
			D1 = 2,

			/// <summary>
			/// The Sleep key.
			/// </summary>
			Sleep = 223,

			/// <summary>
			/// The Next key.
			/// </summary>
			Next = 209,

			/// <summary>
			/// The Stop key.
			/// </summary>
			Stop = 149,

			/// <summary>
			/// The Convert key.
			/// </summary>
			Convert = 121,

			/// <summary>
			/// The decimal/period key.
			/// </summary>
			Decimal = 83,

			/// <summary>
			/// The letter X key.
			/// </summary>
			X = 45,

			/// <summary>
			/// The letter Y key.
			/// </summary>
			Y = 21,

			/// <summary>
			/// The Circumflex key.
			/// </summary>
			Circumflex = 144,

			/// <summary>
			/// The PageDown key.
			/// </summary>
			PageDown = 209,

			/// <summary>
			/// The down arrow.
			/// </summary>
			DownArrow = 208,

			/// <summary>
			/// The right arrow.
			/// </summary>
			RightArrow = 205,

			/// <summary>
			/// The left arrow.
			/// </summary>
			LeftArrow = 203,

			/// <summary>
			/// The Page Up key.
			/// </summary>
			PageUp = 201,

			/// <summary>
			/// The up arrow
			/// </summary>
			UpArrow = 200,

			/// <summary>
			/// The right Alt key.
			/// </summary>
			RightAlt = 184,

			/// <summary>
			/// The Slash key on the NumPad.
			/// </summary>
			NumPadSlash = 181,

			/// <summary>
			/// The decimal/period key on the NumPad.
			/// </summary>
			NumPadPeriod = 83,

			/// <summary>
			/// The plus key on the NumPad.
			/// </summary>
			NumPadPlus = 78,

			/// <summary>
			/// The minus key on the NumPad.
			/// </summary>
			NumPadMinus = 74,

			/// <summary>
			/// The CapsLock key.
			/// </summary>
			CapsLock = 58,

			/// <summary>
			/// The left Alt key.
			/// </summary>
			LeftAlt = 56,

			/// <summary>
			/// The asterisk on the NumPad.
			/// </summary>
			NumPadStar = 55,

			/// <summary>
			/// The Backspace key.
			/// </summary>
			BackSpace = 14,

			/// <summary>
			/// The Media Select key.
			/// </summary>
			MediaSelect = 237,

			/// <summary>
			/// The Mail key.
			/// </summary>
			Mail = 236,

			/// <summary>
			/// The My Computer key.
			/// </summary>
			MyComputer = 235,

			/// <summary>
			/// The Backwards navigation key.
			/// </summary>
			WebBack = 234,

			/// <summary>
			/// The Forwards navigation key.
			/// </summary>
			WebForward = 233,

			/// <summary>
			/// The Stop navigation key.
			/// </summary>
			WebStop = 232,

			/// <summary>
			/// The Refresh navigation key.
			/// </summary>
			WebRefresh = 231,

			/// <summary>
			/// The Favorities key.
			/// </summary>
			WebFavorites = 230,

			/// <summary>
			/// The Search key.
			/// </summary>
			WebSearch = 229,

			/// <summary>
			/// The Wake Up key.
			/// </summary>
			Wake = 227,

			/// <summary>
			/// The Power key.
			/// </summary>
			Power = 222,

			/// <summary>
			/// The Apps key.
			/// </summary>
			Apps = 221,

			/// <summary>
			/// The right Windows key.
			/// </summary>
			RightWindows = 220,

			/// <summary>
			/// The left Windows key.
			/// </summary>
			LeftWindows = 219,

			/// <summary>
			/// The Down navigation key.
			/// </summary>
			Down = 208,

			/// <summary>
			/// The End key.
			/// </summary>
			End = 207,

			/// <summary>
			/// The Prior navigation key.
			/// </summary>
			Prior = 201,

			/// <summary>
			/// The Up navigation key.
			/// </summary>
			Up = 200,

			/// <summary>
			/// The Home key.
			/// </summary>
			Home = 199,

			/// <summary>
			/// The right Menu key.
			/// </summary>
			RightMenu = 184,

			/// <summary>
			/// The System key.
			/// </summary>
			SysRq = 183,

			/// <summary>
			/// The divide/slash key.
			/// </summary>
			Divide = 181,

			/// <summary>
			/// The comma key on the NumPad.
			/// </summary>
			NumPadComma = 179,

			/// <summary>
			/// The homepage navigation key.
			/// </summary>
			WebHome = 178,

			/// <summary>
			/// The volume increase key.
			/// </summary>
			VolumeUp = 176,

			/// <summary>
			/// The volume decrease key.
			/// </summary>
			VolumeDown = 174,

			/// <summary>
			/// The Media Stop key.
			/// </summary>
			MediaStop = 164,

			/// <summary>
			/// The Play/Pause key.
			/// </summary>
			PlayPause = 162,

			/// <summary>
			/// The Calculator key.
			/// </summary>
			Calculator = 161,

			/// <summary>
			/// The mute key.
			/// </summary>
			Mute = 160,

			/// <summary>
			/// The right control key.
			/// </summary>
			RightControl = 157,

			/// <summary>
			/// The enter/return key on the NumPad.
			/// </summary>
			NumPadEnter = 156,

			/// <summary>
			/// The Next Track media key.
			/// </summary>
			NextTrack = 153,

			/// <summary>
			/// An unlabeled key.
			/// </summary>
			Unlabeled = 151,

			/// <summary>
			/// The foreign AX key.
			/// </summary>
			AX = 150,

			/// <summary>
			/// The foregin Kanji key.
			/// </summary>
			Kanji = 148,

			/// <summary>
			/// The Underline key.
			/// </summary>
			Underline = 147,

			/// <summary>
			/// The colon key.
			/// </summary>
			Colon = 146,

			/// <summary>
			/// The foreign At key.
			/// </summary>
			At = 145,

			/// <summary>
			/// The Previous Track media key.
			/// </summary>
			PrevTrack = 144,

			/// <summary>
			/// The equals key on the NumPad.
			/// </summary>
			NumPadEquals = 141,

			/// <summary>
			/// The foregin AbntC2 key.
			/// </summary>
			AbntC2 = 126,

			/// <summary>
			/// The foregin Yen key.
			/// </summary>
			Yen = 125,

			/// <summary>
			/// The No Convert key.
			/// </summary>
			NoConvert = 123,

			/// <summary>
			/// The foreign AbntC1 key.
			/// </summary>
			AbntC1 = 115,

			/// <summary>
			/// The foreign Kana key.
			/// </summary>
			Kana = 112,

			/// <summary>
			/// The F15 key.
			/// </summary>
			F15 = 102,

			/// <summary>
			/// The F14 key.
			/// </summary>
			F14 = 101,

			/// <summary>
			/// The F13 key.
			/// </summary>
			F13 = 100,

			/// <summary>
			/// The F12 key.
			/// </summary>
			F12 = 88,

			/// <summary>
			/// The F11 key.
			/// </summary>
			F11 = 87,

			/// <summary>
			/// The OEM 102 key.
			/// </summary>
			OEM102 = 86,

			/// <summary>
			/// The number 0 on the NumPad.
			/// </summary>
			NumPad0 = 82,

			/// <summary>
			/// The number 3 on the NumPad.
			/// </summary>
			NumPad3 = 81,

			/// <summary>
			/// The number 2 on the NumPad.
			/// </summary>
			NumPad2 = 80,

			/// <summary>
			/// The number 1 on the NumPad.
			/// </summary>
			NumPad1 = 79,

			/// <summary>
			/// The number 6 on the NumPad.
			/// </summary>
			NumPad6 = 77,

			/// <summary>
			/// The number 5 on the NumPad.
			/// </summary>
			NumPad5 = 76,

			/// <summary>
			/// The number 4 on the NumPad.
			/// </summary>
			NumPad4 = 75,

			/// <summary>
			/// The subtract/minus key.
			/// </summary>
			Subtract = 74,

			/// <summary>
			/// The number 9 on the NumPad.
			/// </summary>
			NumPad9 = 73,

			/// <summary>
			/// The number 8 on the NumPad.
			/// </summary>
			NumPad8 = 72,

			/// <summary>
			/// The number 7 on the NumPad.
			/// </summary>
			NumPad7 = 71,

			/// <summary>
			/// The scroll key.
			/// </summary>
			Scroll = 70,

			/// <summary>
			/// The number lock key.
			/// </summary>
			Numlock = 69,

			/// <summary>
			/// The F10 key.
			/// </summary>
			F10 = 68,

			/// <summary>
			/// The F9 key.
			/// </summary>
			F9 = 67,

			/// <summary>
			/// The F8 key.
			/// </summary>
			F8 = 66,

			/// <summary>
			/// The F7 key.
			/// </summary>
			F7 = 65,

			/// <summary>
			/// The F6 key.
			/// </summary>
			F6 = 64,

			/// <summary>
			/// The F5 key.
			/// </summary>
			F5 = 63,

			/// <summary>
			/// The F4 key.
			/// </summary>
			F4 = 62,

			/// <summary>
			/// The F3 key.
			/// </summary>
			F3 = 61,

			/// <summary>
			/// The F2 key.
			/// </summary>
			F2 = 60,

			/// <summary>
			/// The F1 key.
			/// </summary>
			F1 = 59,

			/// <summary>
			/// The Capital key.
			/// </summary>
			Capital = 58,

			/// <summary>
			/// The spacebar.
			/// </summary>
			Space = 57,

			/// <summary>
			/// The left Menu key.
			/// </summary>
			LeftMenu = 56,

			/// <summary>
			/// The multiply/asterisk key.
			/// </summary>
			Multiply = 55,

			/// <summary>
			/// The right Shift key.
			/// </summary>
			RightShift = 54,

			/// <summary>
			/// The slash/divide key.
			/// </summary>
			Slash = 53,

			/// <summary>
			/// The period/decimal key.
			/// </summary>
			Period = 52,

			/// <summary>
			/// The comma key.
			/// </summary>
			Comma = 51,

			/// <summary>
			/// The letter M key.
			/// </summary>
			M = 50,

			/// <summary>
			/// The letter N key.
			/// </summary>
			N = 49,

			/// <summary>
			/// The letter B key.
			/// </summary>
			B = 48,

			/// <summary>
			/// The letter V key.
			/// </summary>
			V = 47,

			/// <summary>
			/// The letter C key.
			/// </summary>
			C = 46,

			/// <summary>
			/// The letter Z key.
			/// </summary>
			Z = 44,

			/// <summary>
			/// The backslash key.
			/// </summary>
			BackSlash = 43,

			/// <summary>
			/// The left Shift key.
			/// </summary>
			LeftShift = 42,

			/// <summary>
			/// The grave character key.
			/// </summary>
			Grave = 41,

			/// <summary>
			/// The apostrophe key.
			/// </summary>
			Apostrophe = 40,

			/// <summary>
			/// The semi-colon key.
			/// </summary>
			SemiColon = 39,

			/// <summary>
			/// The letter L key.
			/// </summary>
			L = 38,

			/// <summary>
			/// The letter K key.
			/// </summary>
			K = 37,

			/// <summary>
			/// The letter J key.
			/// </summary>
			J = 36,

			/// <summary>
			/// The letter H key.
			/// </summary>
			H = 35,

			/// <summary>
			/// The letter G key.
			/// </summary>
			G = 34,

			/// <summary>
			/// The letter F key.
			/// </summary>
			F = 33,

			/// <summary>
			/// The letter D key.
			/// </summary>
			D = 32,

			/// <summary>
			/// The letter S key.
			/// </summary>
			S = 31,

			/// <summary>
			/// The letter A key.
			/// </summary>
			A = 30,

			/// <summary>
			/// The left Control key.
			/// </summary>
			LeftControl = 29,

			/// <summary>
			/// The return/enter key.
			/// </summary>
			Return = 28,

			/// <summary>
			/// The right bracket key.
			/// </summary>
			RightBracket = 27,

			/// <summary>
			/// The left bracket key.
			/// </summary>
			LeftBracket = 26,

			/// <summary>
			/// The letter P key.
			/// </summary>
			P = 25,

			/// <summary>
			/// The letter O key.
			/// </summary>
			O = 24,

			/// <summary>
			/// The letter I key.
			/// </summary>
			I = 23,

			/// <summary>
			/// The letter U key.
			/// </summary>
			U = 22,

			/// <summary>
			/// The letter T key.
			/// </summary>
			T = 20,

			/// <summary>
			/// The letter R key.
			/// </summary>
			R = 19,

			/// <summary>
			/// The letter E key.
			/// </summary>
			E = 18,

			/// <summary>
			/// The letter W key.
			/// </summary>
			W = 17,

			/// <summary>
			/// The Insert key.
			/// </summary>
			Insert = 210,

			/// <summary>
			/// The Right navigation key.
			/// </summary>
			Right = 205,

			/// <summary>
			/// The Left navigation key.
			/// </summary>
			Left = 203,

			/// <summary>
			/// The Pause navigation key.
			/// </summary>
			Pause = 197,

			/// <summary>
			/// The add/plus key.
			/// </summary>
			Add = 78,

			/// <summary>
			/// The Delete key.
			/// </summary>
			Delete = 211,
		};
	}
}