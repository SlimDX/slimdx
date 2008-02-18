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

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace XInput
	{
		/// <remarks>
		/// I don't know what this class does, but I'm using it as a test. 
		/// </remarks>
		public ref class Controller
		{
		private:
			System::UInt32 userIndex;

		public:
			/// <summary>
			/// Initializes a new instance of Controller
			/// </summary>
			/// <param name="userIndex">Index of the user's controller.</param>
			Controller(UserIndex userIndex);

			/// <summary>
			/// Retrieves the current state of the specified controller. See also, unrelated: see cref="SlimDX.Direct3D10.Buffer".
			/// You may also want to go back to the <wiki page="Main Page"/>.
			/// </summary>
			/// <param name="currentState">Out reference to State structure that receives the current state of the controller.</param>
			void GetState([Out] State% currentState);

			/// <summary>
			/// Sends data to a connected controller. This function is used to activate the vibration function of a controller.
			/// </summary>
			/// <param name="vibration">Reference structure containing the vibration information to send to the controller.</param>
			void SetVibration(Vibration% vibration);

			void SetVibration(Vibration vibration);

			/// <summary>
			/// Retrieves the capabilities and features of a connected controller.
			/// </summary>
			/// <param name="flag">Input flags that identify the device type.</param>
			/// <param name="capabilities">Out reference to Capabilities structure that receives the controller capabilities.</param>
			void GetCapabilities(DeviceQueryType flag, [Out] Capabilities% capabilities);

			/// <summary>
			/// Retrieves the sound rendering and sound capture device GUIDs that are associated with the headset connected to the specified controller.
			/// </summary>
			/// <param name="soundRenderGuid">Out reference to Guid structure that receives the GUID of the headset sound rendering device.</param>
			/// <param name="soundCaptureGuid">Out reference to Guid structure that receives the GUID of the headset sound capture device.</param>
			void GetDirectSoundAudioDeviceGuids([Out] System::Guid% soundRenderGuid, [Out] System::Guid% soundCaptureGuid);

			/// <summary>
			/// Retrieves a gamepad input event.
			/// </summary>
			/// <param name="flag">Input flags that identify the device type.</param>
			/// <param name="keystroke">Out reference to Keystroke structure that receives an input event.</param>
			/// <returns>False if no new keys have been pressed.</returns>
			bool GetKeystroke(DeviceQueryType flag, [Out] Keystroke% keystroke);

			/// <summary>
			/// Gets information on the controllers battery.
			/// </summary>
			/// <param name="flag">Input flags that identify the device type.</param>
			/// <param name="batteryInfo">Out reference to BatteryInformation structure that receives the battery status information.</param>
			void GetBatteryInformation(BatteryDeviceType flag, [Out] BatteryInformation% batteryInfo);

			BatteryInformation GetBatteryInformation( BatteryDeviceType flag );

			/// <summary>
			/// Tests if the controller is currently connected. 
			/// </summary>
			/// <remarks>
			/// Wireless controllers are not considered active upon system startup, and calls to any of the XInput functions before a wireless controller
			/// is made active return ERROR_DEVICE_NOT_CONNECTED. Game titles must examine the return code and be prepared to handle this condition.
			/// Wired controllers are automatically activated when they are inserted. Wireless controllers are activated when the user presses the START
			/// or Xbox Guide button to power on the controller.
			/// </remarks>
			property bool IsConnected { bool get(); }

			property State CurrentState
			{
				State get();
			}

			property Capabilities Capabilities
			{
				SlimDX::XInput::Capabilities get();
			}

			property System::Guid SoundRenderGuid
			{
				System::Guid get();
			}

			property System::Guid SoundCaptureGuid
			{
				System::Guid get();
			}
		};
	}
}