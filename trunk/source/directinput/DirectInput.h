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

#include "../SlimDXException.h"
#include "../InternalHelpers.h"

#include "InputDeviceCollection.h"

namespace SlimDX
{
	namespace DirectInput
	{
		/// <summary>
		/// Provides an interface to DirectInput.
		/// </summary>
		public ref class DirectInput sealed
		{
		private:
			DirectInput() { }
			static IDirectInput8W* m_DirectInput;

			static void OnExit( System::Object^ sender, System::EventArgs^ e )
			{
				SLIMDX_UNREFERENCED_PARAMETER(sender);
				SLIMDX_UNREFERENCED_PARAMETER(e);

				Terminate();
			}

		internal:
			static property IDirectInput8W* InternalPointer
			{
				IDirectInput8W* get() { return m_DirectInput; }
			}

		public:
			/// <summary>
			/// Called by the application to initialize DirectInput. This method must be called before
			/// any other DirectInput methods.
			/// </summary>
			static void Initialize();

			/// <summary>
			/// Called by the application to release DirectInput and free resources.
			/// </summary>
			static void Terminate();

			/// <summary>
			/// Runs Control Panel to enable the user to install a new
			/// input device or modify configurations.
			/// </summary>
			static Result RunControlPanel();

			/// <summary>
			/// Runs Control Panel to enable the user to install a new
			/// input device or modify configurations.
			/// </summary>
			/// <param name="parent">The parent control.</param>
			static Result RunControlPanel( System::Windows::Forms::Control^ parent );

			/// <summary>
			/// Gets a value indicating whether the specified device is
			/// attached to the user's system.
			/// </summary>
			static bool IsDeviceAttached( System::Guid device );

			/// <summary>
			/// Retrieves the instance identifier of a device that
			/// has been newly attached to the system.
			/// </summary>
			static System::Guid FindDevice( System::Guid deviceClass, System::String^ name );

			static InputDeviceCollection^ GetDevices();
			static InputDeviceCollection^ GetDevices( DeviceClass deviceClass, DeviceEnumerationFlags enumerationFlags );
			static InputDeviceCollection^ GetDevices( DeviceType deviceType, DeviceEnumerationFlags enumerationFlags );
		};
	}
}
