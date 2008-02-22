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
	namespace XInput
	{
		public value class Keystroke
		{
		private:
			GamepadKeyCode m_VirtualKey;
			KeystrokeFlags m_Flags;
			XInput::UserIndex m_UserIndex;
			int m_HidCode;
		
		internal:
			Keystroke( const XINPUT_KEYSTROKE& native );
			
		public:
			/// <summary>
			/// Virtual-key code of the key, button, or stick movement.
			/// </summary>
			property GamepadKeyCode VirtualKey
			{
				GamepadKeyCode get();
			}

			/// <summary>
			/// Combination of flags that indicate the keyboard state at the time of the input event.
			/// </summary>
			property KeystrokeFlags Flags
			{
				KeystrokeFlags get();
			}

			/// <summary>
			/// Index of the signed-in gamer associated with the device. Can be a value in the range 0–3.
			/// </summary>
			property XInput::UserIndex UserIndex
			{
				XInput::UserIndex get();
			}

			/// <summary>
			/// HID code corresponding to the input. If there is no corresponding HID code, this value is zero.
			/// </summary>
			property int HidCode
			{
				int get();
			}
		};
	}
}