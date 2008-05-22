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

#include "../ComObject.h"

#include "Enums.h"
#include "DataFormatAttribute.h"
#include "DataObjectAttribute.h"
#include "DeviceInstance.h"
#include "Capabilities.h"
#include "BufferedData.h"
#include "BufferedDataCollection.h"
#include "DeviceObjectCollection.h"
#include "Guids.h"
#include "DeviceProperties.h"
#include "ObjectProperties.h"

namespace SlimDX
{
	value class Result;

	namespace DirectInput
	{
		/// <summary>
		/// Used to gain and release access to Microsoft DirectInput devices, manage device
		/// properties and information, set behavior, perform initialization, create and
		/// play force-feedback effects, and open a device's control panel.
		/// </summary>
		/// <typeparam name="DataFormat">The desired data format of the device.</typeparam>
		generic<typename DataFormat>
		public ref class Device : public ComObject
		{
			COMOBJECT(IDirectInputDevice8W, Device);

		private:
			DeviceProperties^ properties;
			Capabilities^ caps;
			DeviceInstance^ information;

		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="Device"/> class.
			/// </summary>
			/// <param name="subsystem">The subsystem identifier.</param>
			[System::Security::Permissions::SecurityPermission( System::Security::Permissions::SecurityAction::LinkDemand, Flags=System::Security::Permissions::SecurityPermissionFlag::UnmanagedCode )]
			Device( System::Guid subsystem );

			/// <summary>
			/// Constructs a new instance of the <see cref="Device"/> class using the specified pointer to a
			/// previously constructed unmanaged object.
			/// </summary>
			/// <param name="pointer">The unmanaged IDirectInputDevice8W pointer.</param>
			/// <returns>The newly constructed object.</returns>
			static Device^ FromPointer( System::IntPtr pointer );

			/// <summary>
			/// Obtains access to the input device.
			/// </summary>
			/// <returns>A <see cref="SlimDX::Result"/> object describing the result of the operation.</returns>
			Result Acquire();

			/// <summary>
			/// Releases access to the device.
			/// </summary>
			/// <returns>A <see cref="SlimDX::Result"/> object describing the result of the operation.</returns>
			Result Unacquire();
			
			/// <summary>
			/// Sets the device's cooperative level.
			/// </summary>
			/// <param name="handle">A handle of a window to associate with the device.</param>
			/// <param name="flags">Flags that describe the cooperative level of the device.</param>
			/// <returns>A <see cref="SlimDX::Result"/> object describing the result of the operation.</returns>
			Result SetCooperativeLevel( System::IntPtr handle, CooperativeLevel flags );

			/// <summary>
			/// Sets the device's cooperative level.
			/// </summary>
			/// <param name="control">A control to associate with the device.</param>
			/// <param name="flags">Flags that describe the cooperative level of the device.</param>
			/// <returns>A <see cref="SlimDX::Result"/> object describing the result of the operation.</returns>
			Result SetCooperativeLevel( System::Windows::Forms::Control^ control, CooperativeLevel flags );

			/// <summary>
			/// Runs the DirectInput control panel associated with this device. If the
			/// device does not have a control panel associated with it, the default
			/// device control panel is launched.
			/// </summary>
			/// <returns>A <see cref="SlimDX::Result"/> object describing the result of the operation.</returns>
			Result RunControlPanel();

			/// <summary>
			/// Runs the DirectInput control panel associated with this device. If the
			/// device does not have a control panel associated with it, the default
			/// device control panel is launched.
			/// </summary>
			/// <param name="parent">The parent control.</param>
			/// <returns>A <see cref="SlimDX::Result"/> object describing the result of the operation.</returns>
			Result RunControlPanel( System::Windows::Forms::Control^ parent );

			/// <summary>
			/// Retrieves the current device state.
			/// </summary>
			/// <returns>The current device state.</returns>
			DataFormat GetCurrentState();

			/// <summary>
			/// Retrieves the current device state.
			/// </summary>
			/// <returns>A <see cref="SlimDX::Result"/> object describing the result of the operation.</returns>
			[System::Security::Permissions::SecurityPermission( System::Security::Permissions::SecurityAction::LinkDemand, Flags=System::Security::Permissions::SecurityPermissionFlag::UnmanagedCode )]
			Result GetCurrentState( DataFormat% data );

			/// <summary>
			/// Retrieves buffered data from the device.
			/// </summary>
			/// <returns>A collection of buffered input events.</returns>
			BufferedDataCollection<DataFormat>^ GetBufferedData();

			/// <summary>
			/// Retrieves data from polled objects on a DirectInput device.
			/// </summary>
			/// <returns>A <see cref="SlimDX::Result"/> object describing the result of the operation.</returns>
			Result Poll();

			/// <summary>
			/// Gets properties about a single object on an input device.
			/// </summary>
			/// <param name="name">The name of the object whose properties are to be retrieved.</param>
			/// <returns>The properties of the desired object.</returns>
			ObjectProperties^ GetObjectPropertiesByName( System::String^ name );

			/// <summary>
			/// Gets properties about a single object on an input device.
			/// </summary>
			/// <param name="usageCode">The usageCode of the object whose properties are to be retrieved.</param>
			/// <returns>The properties of the desired object.</returns>
			ObjectProperties^ GetObjectPropertiesByUsage( int usageCode );

			/// <summary>
			/// Gets properties about a single object on an input device.
			/// </summary>
			/// <param name="objectId">The identifier of the object whose properties are to be retrieved.</param>
			/// <returns>The properties of the desired object.</returns>
			ObjectProperties^ GetObjectPropertiesById( int objectId );

			/// <summary>
			/// Retrieves a collection of objects on the device.
			/// </summary>
			/// <param name="objectType">A filter for the returned device objects collection.</param>
			/// <returns>A collection of device objects matching the specified filter.</returns>
			DeviceObjectCollection^ GetDeviceObjects( ObjectDeviceType objectType );

			/// <summary>
			/// Retrieves a collection of objects on the device.
			/// </summary>
			/// <returns>A collection of all device objects on the device.</returns>
			DeviceObjectCollection^ GetDeviceObjects();

			/// <summary>
			/// Sends a hardware-specific command to the force-feedback driver.
			/// </summary>
			/// <param name="command">The command to be sent.</param>
			/// <param name="data">The data to be sent to the device.</param>
			/// <param name="outputSize">The expected size of the output buffer.</param>
			/// <returns>The output data of the command.</returns>
			array<System::Byte>^ Escape( int command, array<System::Byte>^ data, int outputSize );

			/// <summary>
			/// Gets a set of properties that control the behavior of the device.
			/// </summary>
			property DeviceProperties^ Properties { DeviceProperties^ get(); }

			/// <summary>
			/// Gets the capabilities of the device.
			/// </summary>
			property Capabilities^ Caps { Capabilities^ get(); }

			/// <summary>
			/// Gets information about the device's identity.
			/// </summary>
			property DeviceInstance^ DeviceInformation { DeviceInstance^ get(); }
		};
	}
}
