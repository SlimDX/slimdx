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
#include "Gamepad.h"
#include "Vibration.h"

namespace SlimDX
{
	namespace XInput
	{
		/// <summary>
		/// Describes the capabilities of a controller.
		/// </summary>
		public value class Capabilities : System::IEquatable<Capabilities>
		{
		private:
			DeviceType m_Type;
			DeviceSubtype m_SubType;
			CapabilityFlags m_Flags;
			XInput::Gamepad m_Gamepad;
			XInput::Vibration m_Vibration;
		
		internal:
			Capabilities( const XINPUT_CAPABILITIES& native );
			
		public:
			/// <summary>
			/// Gets the controller type.
			/// </summary>
			property DeviceType Type
			{
				DeviceType get();
			}

			/// <summary>
			/// Gets the controller subtype.
			/// </summary>
			property DeviceSubtype Subtype
			{
				DeviceSubtype get();
			}

			/// <summary>
			/// Features of the controller. 
			/// </summary>
			property CapabilityFlags Flags
			{
				CapabilityFlags get();
			}

			property XInput::Gamepad Gamepad
			{
				XInput::Gamepad get();
			}

			property XInput::Vibration Vibration
			{
				XInput::Vibration get();
			}

			static bool operator == ( Capabilities left, Capabilities right );
			static bool operator != ( Capabilities left, Capabilities right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( Capabilities other );
			static bool Equals( Capabilities% value1, Capabilities% value2 );
		};
	}
}