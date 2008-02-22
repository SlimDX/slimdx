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
		/// <summary>
		/// Specifies motor speed levels for the vibration function of a controller.
		/// </summary>
		/// <remarks>
		/// The left motor is the low-frequency rumble motor. The right motor is the high-frequency rumble motor. 
		/// The two motors are not the same, and they create different vibration effects.
		/// </remarks>
		public value class Vibration
		{
		private:
			System::UInt16 m_LeftMotorSpeed;
			System::UInt16 m_RightMotorSpeed;
		
		internal:
			Vibration( const XINPUT_VIBRATION& native );
			
			XINPUT_VIBRATION CreateNativeVersion();
			
		public:
			/// <summary>
			/// Gets or sets the left motor speed. 
			/// </summary>
			/// <remarks>
			/// Valid values are in the range 0 to 65,535. Zero signifies no motor use; 65,535 signifies 100% motor use.
			/// </remarks>
			property System::UInt16 LeftMotorSpeed
			{
				System::UInt16 get();
				void set( System::UInt16 value );
			}

			/// <summary>
			/// Gets or sets the right motor speed. 
			/// </summary>
			/// <remarks>
			/// Valid values are in the range 0 to 65,535. Zero signifies no motor use; 65,535 signifies 100% motor use.
			/// </remarks>
			property System::UInt16 RightMotorSpeed
			{
				System::UInt16 get();
				void set( System::UInt16 value );
			}
		};
	}
}