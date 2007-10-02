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
		/// Defines possible joystick object codes.
		/// </summary>
		public ref class JoystickObjects sealed
		{
		private:
			JoystickObjects() { }

		public:
			/// <summary>
			/// The rotational X axis.
			/// </summary>
			literal int XAxisRotation = DIJOFS_RX;

			/// <summary>
			/// The rotational X axis.
			/// </summary>
			literal int YAxisRotation = DIJOFS_RY;

			/// <summary>
			/// The rotational X axis.
			/// </summary>
			literal int ZAxisRotation = DIJOFS_RZ;

			/// <summary>
			/// The rotational X axis.
			/// </summary>
			literal int XAxis = DIJOFS_X;

			/// <summary>
			/// The rotational X axis.
			/// </summary>
			literal int YAxis = DIJOFS_Y;

			/// <summary>
			/// The rotational X axis.
			/// </summary>
			literal int ZAxis = DIJOFS_Z;

			/// <summary>
			/// Provides scan codes for the specified button.
			/// </summary>
			static int Button( int buttonId );

			/// <summary>
			/// Provides scan codes for the specified slider.
			/// </summary>
			static int Slider( int sliderId );

			/// <summary>
			/// Provides scan codes for the specified Point-Of-View controller.
			/// </summary>
			static int PointOfView( int povId );
		};

		/// <summary>
		/// Defines object codes that refer to any control type on a device.
		/// </summary>
		public ref class AnyControl sealed
		{
		private:
			AnyControl() { }

		public:
			/// <summary>
			/// Refers to any axis.
			/// </summary>
			literal int Axis1 = DIAXIS_ANY_1;

			/// <summary>
			/// Refers to any axis.
			/// </summary>
			literal int Axis2 = DIAXIS_ANY_2;

			/// <summary>
			/// Refers to any axis.
			/// </summary>
			literal int Axis3 = DIAXIS_ANY_3;

			/// <summary>
			/// Refers to any accelerator.
			/// </summary>
			literal int Accelerator1 = DIAXIS_ANY_A_1;

			/// <summary>
			/// Refers to any accelerator.
			/// </summary>
			literal int Accelerator2 = DIAXIS_ANY_A_2;

			/// <summary>
			/// Refers to any brake.
			/// </summary>
			literal int Brake1 = DIAXIS_ANY_B_1;

			/// <summary>
			/// Refers to any brake.
			/// </summary>
			literal int Brake2 = DIAXIS_ANY_B_2;

			/// <summary>
			/// Refers to any clutch.
			/// </summary>
			literal int Clutch1 = DIAXIS_ANY_C_1;

			/// <summary>
			/// Refers to any clutch.
			/// </summary>
			literal int Clutch2 = DIAXIS_ANY_C_2;

			/// <summary>
			/// Refers to any r-axis.
			/// </summary>
			literal int RAxis1 = DIAXIS_ANY_R_1;

			/// <summary>
			/// Refers to any r-axis.
			/// </summary>
			literal int RAxis2 = DIAXIS_ANY_R_2;

			/// <summary>
			/// Refers to any s-axis.
			/// </summary>
			literal int SAxis1 = DIAXIS_ANY_S_1;

			/// <summary>
			/// Refers to any s-axis.
			/// </summary>
			literal int SAxis2 = DIAXIS_ANY_S_2;

			/// <summary>
			/// Refers to any u-axis.
			/// </summary>
			literal int UAxis1 = DIAXIS_ANY_U_1;

			/// <summary>
			/// Refers to any u-axis.
			/// </summary>
			literal int UAxis2 = DIAXIS_ANY_U_2;

			/// <summary>
			/// Refers to any v-axis.
			/// </summary>
			literal int VAxis1 = DIAXIS_ANY_V_1;

			/// <summary>
			/// Refers to any v-axis.
			/// </summary>
			literal int VAxis2 = DIAXIS_ANY_V_2;

			/// <summary>
			/// Refers to any x-axis.
			/// </summary>
			literal int XAxis1 = DIAXIS_ANY_X_1;

			/// <summary>
			/// Refers to any x-axis.
			/// </summary>
			literal int XAxis2 = DIAXIS_ANY_X_2;

			/// <summary>
			/// Refers to any y-axis.
			/// </summary>
			literal int YAxis1 = DIAXIS_ANY_Y_1;

			/// <summary>
			/// Refers to any y-axis.
			/// </summary>
			literal int YAxis2 = DIAXIS_ANY_Y_2;

			/// <summary>
			/// Refers to any z-axis.
			/// </summary>
			literal int ZAxis1 = DIAXIS_ANY_Z_1;

			/// <summary>
			/// Refers to any z-axis.
			/// </summary>
			literal int ZAxis2 = DIAXIS_ANY_Z_2;

			/// <summary>
			/// Refers to any point-of-view controller.
			/// </summary>
			literal int PointOfView1 = DIPOV_ANY_1;

			/// <summary>
			/// Refers to any point-of-view controller.
			/// </summary>
			literal int PointOfView2 = DIPOV_ANY_2;

			/// <summary>
			/// Refers to any point-of-view controller.
			/// </summary>
			literal int PointOfView3 = DIPOV_ANY_3;

			/// <summary>
			/// Refers to any point-of-view controller.
			/// </summary>
			literal int PointOfView4 = DIPOV_ANY_4;

			/// <summary>
			/// Refers to any button.
			/// </summary>
			static int Button( int buttonId );
		};

		/// <summary>
		/// Defines possible mouse object codes.
		/// </summary>
		public enum class MouseObject : Int32
		{
			/// <summary>
			/// The first button.
			/// </summary>
			Button1,

			/// <summary>
			/// The second button.
			/// </summary>
			Button2,

			/// <summary>
			/// The third button.
			/// </summary>
			Button3,

			/// <summary>
			/// The fourth button.
			/// </summary>
			Button4,

			/// <summary>
			/// The fifth button.
			/// </summary>
			Button5,

			/// <summary>
			/// The sixth button.
			/// </summary>
			Button6,

			/// <summary>
			/// The seventh button.
			/// </summary>
			Button7,

			/// <summary>
			/// The eighth button.
			/// </summary>
			Button8,

			/// <summary>
			/// The X axis.
			/// </summary>
			XAxis,

			/// <summary>
			/// The Y axis.
			/// </summary>
			YAxis,

			/// <summary>
			/// The Z axis.
			/// </summary>
			ZAxis
		};

		/// <summary>
		/// Defines possible keyboard key codes.
		/// </summary>
		public enum class Key : Int32
		{
			/// <summary>
			/// The number 0.
			/// </summary>
			D0,

			/// <summary>
			/// The number 1.
			/// </summary>
			D1,

			/// <summary>
			/// The number 2.
			/// </summary>
			D2,

			/// <summary>
			/// The number 3.
			/// </summary>
			D3,

			/// <summary>
			/// The number 4.
			/// </summary>
			D4,

			/// <summary>
			/// The number 5.
			/// </summary>
			D5,

			/// <summary>
			/// The number 6.
			/// </summary>
			D6,

			/// <summary>
			/// The number 7.
			/// </summary>
			D7,

			/// <summary>
			/// The number 8.
			/// </summary>
			D8,

			/// <summary>
			/// The number 9.
			/// </summary>
			D9,

			/// <summary>
			/// The letter A.
			/// </summary>
			A,

			/// <summary>
			/// The letter B.
			/// </summary>
			B,

			/// <summary>
			/// The letter C.
			/// </summary>
			C,

			/// <summary>
			/// The letter D.
			/// </summary>
			D,

			/// <summary>
			/// The letter E.
			/// </summary>
			E,

			/// <summary>
			/// The letter F.
			/// </summary>
			F,

			/// <summary>
			/// The letter G.
			/// </summary>
			G,

			/// <summary>
			/// The letter H.
			/// </summary>
			H,

			/// <summary>
			/// The letter I.
			/// </summary>
			I,

			/// <summary>
			/// The letter J.
			/// </summary>
			J,

			/// <summary>
			/// The letter K.
			/// </summary>
			K,

			/// <summary>
			/// The letter L.
			/// </summary>
			L,

			/// <summary>
			/// The letter M.
			/// </summary>
			M,

			/// <summary>
			/// The letter N.
			/// </summary>
			N,

			/// <summary>
			/// The letter O.
			/// </summary>
			O,

			/// <summary>
			/// The letter P.
			/// </summary>
			P,

			/// <summary>
			/// The letter Q.
			/// </summary>
			Q,

			/// <summary>
			/// The letter R.
			/// </summary>
			R,

			/// <summary>
			/// The letter S.
			/// </summary>
			S,

			/// <summary>
			/// The letter T.
			/// </summary>
			T,

			/// <summary>
			/// The letter U.
			/// </summary>
			U,

			/// <summary>
			/// The letter V.
			/// </summary>
			V,

			/// <summary>
			/// The letter W.
			/// </summary>
			W,

			/// <summary>
			/// The letter X.
			/// </summary>
			X,

			/// <summary>
			/// The letter Y.
			/// </summary>
			Y,

			/// <summary>
			/// The letter Z.
			/// </summary>
			Z,

			/// <summary>
			/// The AbntC1 key on Brazillian keyboards.
			/// </summary>
			AbntC1,

			/// <summary>
			/// The AbntC2 key on Brazillian keyboards.
			/// </summary>
			AbntC2,

			/// <summary>
			/// The apostrophe key.
			/// </summary>
			Apostrophe,

			/// <summary>
			/// The Applications key.
			/// </summary>
			Applications,

			/// <summary>
			/// The Japanese At key.
			/// </summary>
			AT,

			/// <summary>
			/// The Japanese Ax key.
			/// </summary>
			AX,

			/// <summary>
			/// The BackSpace.
			/// </summary>
			BackSpace,

			/// <summary>
			/// The back slash key.
			/// </summary>
			BackSlash,

			/// <summary>
			/// The calculator key.
			/// </summary>
			Calculator,

			/// <summary>
			/// The Caps Lock key.
			/// </summary>
			CapsLock,

			/// <summary>
			/// The colon key.
			/// </summary>
			Colon,

			/// <summary>
			/// The comma key.
			/// </summary>
			Comma,

			/// <summary>
			/// The Japanese Convert key.
			/// </summary>
			Convert,

			/// <summary>
			/// The Delete key.
			/// </summary>
			Delete,

			/// <summary>
			/// The Down Arrow key.
			/// </summary>
			DownArrow,

			/// <summary>
			/// The End key.
			/// </summary>
			End,

			/// <summary>
			/// The equals key.
			/// </summary>
			Equals,

			/// <summary>
			/// The Escape key.
			/// </summary>
			Escape,

			/// <summary>
			/// The F1 key.
			/// </summary>
			F1,

			/// <summary>
			/// The F2 key.
			/// </summary>
			F2,

			/// <summary>
			/// The F3 key.
			/// </summary>
			F3,

			/// <summary>
			/// The F4 key.
			/// </summary>
			F4,

			/// <summary>
			/// The F5 key.
			/// </summary>
			F5,

			/// <summary>
			/// The F6 key.
			/// </summary>
			F6,

			/// <summary>
			/// The F7 key.
			/// </summary>
			F7,

			/// <summary>
			/// The F8 key.
			/// </summary>
			F8,

			/// <summary>
			/// The F9 key.
			/// </summary>
			F9,

			/// <summary>
			/// The F10 key.
			/// </summary>
			F10,

			/// <summary>
			/// The F11 key.
			/// </summary>
			F11,

			/// <summary>
			/// The F12 key.
			/// </summary>
			F12,

			/// <summary>
			/// The F13 key.
			/// </summary>
			F13,

			/// <summary>
			/// The F14 key.
			/// </summary>
			F14,

			/// <summary>
			/// The F15 key.
			/// </summary>
			F15,

			/// <summary>
			/// The grav accent (`) key.
			/// </summary>
			Grave,

			/// <summary>
			/// The Home key.
			/// </summary>
			Home,

			/// <summary>
			/// The Insert key.
			/// </summary>
			Insert,

			/// <summary>
			/// The Japanese Kana key.
			/// </summary>
			Kana,

			/// <summary>
			/// The Japanese Kanji key.
			/// </summary>
			Kanji,

			/// <summary>
			/// The left square bracket key.
			/// </summary>
			LeftBracket,

			/// <summary>
			/// The left Ctrl key.
			/// </summary>
			LeftControl,

			/// <summary>
			/// The Left Arrow key.
			/// </summary>
			LeftArrow,

			/// <summary>
			/// The left Alt key.
			/// </summary>
			LeftAlt,

			/// <summary>
			/// The left Shift key.
			/// </summary>
			LeftShift,

			/// <summary>
			/// The left Windows key.
			/// </summary>
			LeftWindowsKey,

			/// <summary>
			/// The Mail key.
			/// </summary>
			Mail,

			/// <summary>
			/// The Media Select key.
			/// </summary>
			MediaSelect,

			/// <summary>
			/// The Media Stop key.
			/// </summary>
			MediaStop,

			/// <summary>
			/// The minus key.
			/// </summary>
			Minus,

			/// <summary>
			/// The Mute key.
			/// </summary>
			Mute,

			/// <summary>
			/// The My Computer key.
			/// </summary>
			MyComputer,

			/// <summary>
			/// The Next Track key.
			/// </summary>
			NextTrack,

			/// <summary>
			/// The Japanese No Convert key.
			/// </summary>
			NoConvert,

			/// <summary>
			/// The NumberLock key.
			/// </summary>
			NumberLock,

			/// <summary>
			/// The number 0 on the NumberPad.
			/// </summary>
			NumberPad0,

			/// <summary>
			/// The number 1 on the NumberPad.
			/// </summary>
			NumberPad1,

			/// <summary>
			/// The number 2 on the NumberPad.
			/// </summary>
			NumberPad2,

			/// <summary>
			/// The number 3 on the NumberPad.
			/// </summary>
			NumberPad3,

			/// <summary>
			/// The number 4 on the NumberPad.
			/// </summary>
			NumberPad4,

			/// <summary>
			/// The number 5 on the NumberPad.
			/// </summary>
			NumberPad5,

			/// <summary>
			/// The number 6 on the NumberPad.
			/// </summary>
			NumberPad6,

			/// <summary>
			/// The number 7 on the NumberPad.
			/// </summary>
			NumberPad7,

			/// <summary>
			/// The number 8 on the NumberPad.
			/// </summary>
			NumberPad8,

			/// <summary>
			/// The number 9 on the NumberPad.
			/// </summary>
			NumberPad9,

			/// <summary>
			/// The comma key on the NumberPad.
			/// </summary>
			NumberPadComma,

			/// <summary>
			/// The Enter key on the NumberPad.
			/// </summary>
			NumberPadEnter,

			/// <summary>
			/// The equals key on the NumberPad.
			/// </summary>
			NumberPadEquals,

			/// <summary>
			/// The minus key on the NumberPad.
			/// </summary>
			NumberPadMinus,

			/// <summary>
			/// The period key on the NumberPad.
			/// </summary>
			NumberPadPeriod,

			/// <summary>
			/// The plus key on the NumberPad.
			/// </summary>
			NumberPadPlus,

			/// <summary>
			/// The slash key on the NumberPad.
			/// </summary>
			NumberPadSlash,

			/// <summary>
			/// The asterisk key on the NumberPad.
			/// </summary>
			NumberPadStar,

			/// <summary>
			/// The British and German OEM102 key.
			/// </summary>
			OEM102,

			/// <summary>
			/// The Page Down key.
			/// </summary>
			PageDown,

			/// <summary>
			/// The Page Up key.
			/// </summary>
			PageUp,

			/// <summary>
			/// The Pause key.
			/// </summary>
			Pause,

			/// <summary>
			/// The period key.
			/// </summary>
			Period,

			/// <summary>
			/// The Play/Pause key.
			/// </summary>
			PlayPause,

			/// <summary>
			/// The Power key.
			/// </summary>
			Power,

			/// <summary>
			/// The Previous Track key.
			/// </summary>
			PreviousTrack,

			/// <summary>
			/// The right square bracket key.
			/// </summary>
			RightBracket,

			/// <summary>
			/// The right Ctrl key.
			/// </summary>
			RightControl,

			/// <summary>
			/// The Return/Enter key.
			/// </summary>
			Return,

			/// <summary>
			/// The Right Arrow key.
			/// </summary>
			RightArrow,

			/// <summary>
			/// The right Alt key.
			/// </summary>
			RightAlt,

			/// <summary>
			/// The right Shift key.
			/// </summary>
			RightShift,

			/// <summary>
			/// The right Windows key.
			/// </summary>
			RightWindowsKey,

			/// <summary>
			/// The Scroll Lock key.
			/// </summary>
			ScrollLock,

			/// <summary>
			/// The semicolon key.
			/// </summary>
			Semicolon,

			/// <summary>
			/// The slash key.
			/// </summary>
			Slash,

			/// <summary>
			/// The Sleep key.
			/// </summary>
			Sleep,

			/// <summary>
			/// The Spacebar.
			/// </summary>
			Space,

			/// <summary>
			/// The Stop key.
			/// </summary>
			Stop,

			/// <summary>
			/// The Print Screen key.
			/// </summary>
			PrintScreen,

			/// <summary>
			/// The Tab key.
			/// </summary>
			Tab,

			/// <summary>
			/// The Japanese Underline key.
			/// </summary>
			Underline,

			/// <summary>
			/// An unlabeled key.
			/// </summary>
			Unlabeled,

			/// <summary>
			/// The Up Arrow key.
			/// </summary>
			UpArrow,

			/// <summary>
			/// The Volume Down key.
			/// </summary>
			VolumeDown,

			/// <summary>
			/// The Volume Up key.
			/// </summary>
			VolumeUp,

			/// <summary>
			/// The Wake key.
			/// </summary>
			Wake,

			/// <summary>
			/// The Web Backwards key.
			/// </summary>
			WebBack,

			/// <summary>
			/// The Web Favorites key.
			/// </summary>
			WebFavorites,

			/// <summary>
			/// The Web Forwards key.
			/// </summary>
			WebForward,

			/// <summary>
			/// The Web Home key.
			/// </summary>
			WebHome,

			/// <summary>
			/// The Web Refresh key.
			/// </summary>
			WebRefresh,

			/// <summary>
			/// The Web Search key.
			/// </summary>
			WebSearch,

			/// <summary>
			/// The Web Stop key.
			/// </summary>
			WebStop,

			/// <summary>
			/// The Japanese Yen key.
			/// </summary>
			Yen
		};

		private ref class DeviceConstantConverter sealed
		{
		private:
			DeviceConstantConverter() { }

		public:
			static int KeyToDIK( Key key );
			static int KeyToDIKEYBOARD( Key key );
			static int MouseToDIMOFS( MouseObject mouse );
			static int MouseToDIMOUSE( MouseObject mouse );
		};
	}
}