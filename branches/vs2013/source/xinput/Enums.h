/*
* Copyright (c) 2007-2014 SlimDX Group
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
		
	#pragma warning(disable: 4369)
		/// <summary>
		/// Describes a set of pressed buttons on a gamepad.
		/// </summary>
		[System::Flags]
		public enum class GamepadButtonFlags : System::Int16
		{
			/// <summary>
			/// No buttons are pressed.
			/// </summary>
			None = 0,

			/// <summary>
			/// The Up button on the D-Pad is pressed.
			/// </summary>
			DPadUp = XINPUT_GAMEPAD_DPAD_UP,

			/// <summary>
			/// The Down button on the D-Pad is pressed.
			/// </summary>
			DPadDown = XINPUT_GAMEPAD_DPAD_DOWN,

			/// <summary>
			/// The Left button on the D-Pad is pressed.
			/// </summary>
			DPadLeft = XINPUT_GAMEPAD_DPAD_LEFT,

			/// <summary>
			/// The Right button on the D-Pad is pressed.
			/// </summary>
			DPadRight = XINPUT_GAMEPAD_DPAD_RIGHT,

			/// <summary>
			/// The start button is pressed.
			/// </summary>
			Start = XINPUT_GAMEPAD_START,

			/// <summary>
			/// The back button is pressed.
			/// </summary>
			Back = XINPUT_GAMEPAD_BACK,

			/// <summary>
			/// The left thumb button is pressed.
			/// </summary>
			LeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,  

			/// <summary>
			/// The right thumb button is pressed.
			/// </summary>
			RightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,   

			/// <summary>
			/// The left shoulder button is pressed.
			/// </summary>
			LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,

			/// <summary>
			/// The right shoulder button is pressed.
			/// </summary>
			RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,

			/// <summary>
			/// The A button is pressed.
			/// </summary>
			A = XINPUT_GAMEPAD_A,

			/// <summary>
			/// The B button is pressed.
			/// </summary>
			B = XINPUT_GAMEPAD_B,

			/// <summary>
			/// The X button is pressed.
			/// </summary>
			X = XINPUT_GAMEPAD_X,

			/// <summary>
			/// The Y button is pressed.
			/// </summary>
			Y = XINPUT_GAMEPAD_Y
		};
	#pragma warning(default: 4369)

		/// <summary>
		/// Specifies the index of a user's controller.
		/// </summary>
		public enum class UserIndex : System::Int32
		{
			/// <summary>
			/// The index of the user is unimportant.
			/// </summary>
			Any = XUSER_INDEX_ANY,

			/// <summary>
			/// Player one.
			/// </summary>
			One = 0,

			/// <summary>
			/// Player two.
			/// </summary>
			Two = 1,

			/// <summary>
			/// Player three.
			/// </summary>
			Three = 2,

			/// <summary>
			/// Player four.
			/// </summary>
			Four = 3
		};
	}
}