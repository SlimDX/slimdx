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

#include "Gamepad.h"

namespace SlimDX
{
	namespace XInput
	{
		public value class State : System::IEquatable<State>
		{
		private:
			System::UInt32 m_PacketNumber;
			XInput::Gamepad m_Gamepad;
		
		internal:
			State( const XINPUT_STATE& native );
		
		public:
			/// <summary>
			/// Gets the state packet number.
			/// <summar>
			/// <remarks>
			/// The packet number indicates whether there have been any changes in the state of the controller. If the value
			/// does not change in sequentially returned State structures, the controller state has not changed. 
			/// </remarks>
			property System::UInt32 PacketNumber
			{
				System::UInt32 get();
			}
      
			property XInput::Gamepad Gamepad
			{
				XInput::Gamepad get();
			}

			static bool operator == ( State left, State right );
			static bool operator != ( State left, State right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( State other );
			static bool Equals( State% value1, State% value2 );
		};
	}
}