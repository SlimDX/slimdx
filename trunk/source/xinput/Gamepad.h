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

#include "Enums.h"

namespace SlimDX
{
	namespace XInput
	{
		/// <summary>
		/// Describes the current state of the Xbox 360 Controller.
		/// </summary>
		/// <remarks>
		/// Each of the thumbstick axis members is a signed value between -32768 and 32767 describing the position of the thumbstick.
		/// A value of 0 is centered. Negative values signify down or to the left. Positive values signify up or to the right.
		/// The constants GamepadLeftThumbDeadZone or GamepadRightThumbDeadZone can be used as a positive and negative value to filter a
		/// thumbstick input.
		/// </remarks>
		public value class Gamepad
		{
		private:
			GamepadButtonFlags m_Buttons;
			System::Byte leftTrigger;
			System::Byte rightTrigger;
			System::Int16 leftThumbX;
			System::Int16 leftThumbY;
			System::Int16 rightThumbX;
			System::Int16 rightThumbY;

		internal:
			Gamepad( const XINPUT_GAMEPAD &native );

		public:
			property GamepadButtonFlags Buttons
			{
				GamepadButtonFlags get();
			}

			/// <summary>
			/// The current value of the left trigger analog control. The value is between 0 and 255.
			/// </summary>
            property System::Byte LeftTrigger
            {
                System::Byte get() { return leftTrigger; }
            }

			/// <summary>
			/// The current value of the right trigger analog control. The value is between 0 and 255.
			/// </summary>
            property System::Byte RightTrigger
            {
                System::Byte get() { return rightTrigger; }
            }

			/// <summary>
			/// Right thumbstick y-axis value. The value is between -32768 and 32767.
			/// </summary>
            property System::Int16 LeftThumbX
            {
                System::Int16 get() { return leftThumbX; }
            }

			/// <summary>
			/// Left thumbstick y-axis value. The value is between -32768 and 32767.
			/// </summary>
            property System::Int16 LeftThumbY
            {
                System::Int16 get() { return leftThumbY; }
            }

			/// <summary>
			/// Right thumbstick x-axis value. The value is between -32768 and 32767.
			/// </summary>
            property System::Int16 RightThumbX
            {
                System::Int16 get() { return rightThumbX; }
            }

			/// <summary>
			/// Right thumbstick y-axis value. The value is between -32768 and 32767.
			/// </summary>
            property System::Int16 RightThumbY
            {
                System::Int16 get() { return rightThumbY; }
            }

			/// <summary>
			/// Can be used as a positive and negative value to filter the left thumbstick input.
			/// </summary>
			literal System::Int16 GamepadLeftThumbDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

			/// <summary>
			/// Can be used as a positive and negative value to filter the right thumbstick input.
			/// </summary>
			literal System::Int16 GamepadRightThumbDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

			/// <summary>
			/// This constantmay be used as the value which LeftTrigger and RightTrigger must be greater than to register as pressed.
			/// </summary>
			literal System::Byte GamepadTriggerThreshold = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
		};
	}
}