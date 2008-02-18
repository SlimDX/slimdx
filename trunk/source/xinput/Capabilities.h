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

//using namespace System;

namespace SlimDX
{
	namespace XInput
	{
		/// <summary>
		/// Describes the capabilities of a connected controller.
		/// </summary>
		/// <remarks>
		/// Sets the structure members to indicate which inputs the device supports. For binary state controls, such as digital buttons, the corresponding bit reflects
		/// whether or not the control is supported by the device. For proportional controls, such as thumbsticks, the value indicates the resolution for that control.
		/// Some number of the least significant bits may not be set, indicating that the control does not provide resolution to that level.
		/// </remarks>
		public value class Capabilities
		{
		private:
            DeviceType type;
            DeviceSubtype subType;
            CapabilitiesFlags flags;
            Gamepad gamepad;
            Vibration vibration;

		public:
			/// <summary>
			/// Controller type.
			/// </summary>
			property DeviceType Type
            {
                DeviceType get() { return type; }
			internal:
                void set( DeviceType value ) { type = value; }
            }

			/// <summary>
			/// Subtype of the game controller. 
			/// </summary>
            property DeviceSubtype Subtype
            {
                DeviceSubtype get() { return subType; }
			internal:
                void set( DeviceSubtype value ) { subType = value; }
            }

			/// <summary>
			/// Features of the controller. 
			/// </summary>
            property CapabilitiesFlags Flags
            {
                CapabilitiesFlags get() { return flags; }
			internal:
                void set( CapabilitiesFlags value ) { flags = value; }
            }

			/// <summary>
			/// Gamepad structure that describes available controller features and control resolutions. 
			/// </summary>
            property Gamepad Gamepad
            {
				SlimDX::XInput::Gamepad get() { return gamepad; }
			internal:
                void set( SlimDX::XInput::Gamepad value ) { gamepad = value; }
            }

			/// <summary>
			/// Vibration structure that describes available vibration functionality and resolutions. 
			/// </summary>
            property SlimDX::XInput::Vibration Vibration
            {
                SlimDX::XInput::Vibration get() { return vibration; }
            }
		};
	}
}