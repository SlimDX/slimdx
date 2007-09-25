/*
* Copyright (c) 2007 SlimDX Group
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

using namespace System;

#include "Enums.h"

namespace SlimDX
{
	namespace DirectInput
	{
		/// <summary>
		/// Contains information about a device's identity.
		/// </summary>
		public ref class DeviceInstance
		{
		private:
			Guid instanceGuid;
			Guid productGuid;
			Guid ffDriverGuid;
			DeviceType type;
			int subType;
			String^ instanceName;
			String^ productName;
			int usage;
			int usagePage;
			bool hid;

		internal:
			DeviceInstance( const DIDEVICEINSTANCE &deviceInstance );

		public:
			/// <summary>
			/// Gets the unique identifier for the instance of the device. Instance Guids are
			/// specific to a particular computer.
			/// </summary>
			property Guid InstanceGuid
			{
				Guid get() { return instanceGuid; }
			}

			/// <summary>
			/// Gets the unique identifier for the product. This identifier is established
			/// by the manufacturer of the device.
			/// </summary>
			property Guid ProductGuid
			{
				Guid get() { return productGuid; }
			}

			/// <summary>
			/// Gets the unique identifier for the driver being used for force-feedback. The
			/// driver's manufacturer establishes this identifier.
			/// </summary>
			property Guid ForceFeedbackDriverGuid
			{
				Guid get() { return ffDriverGuid; }
			}

			/// <summary>
			/// Gets the main device type specifier.
			/// </summary>
			property DeviceType Type
			{
				DeviceType get() { return type; }
			}

			/// <summary>
			/// Gets the secondary device type specifier.
			/// </summary>
			property int SubType
			{
				int get() { return subType; }
			}

			/// <summary>
			/// Gets the friendly name for the instance.
			/// </summary>
			property String^ InstanceName
			{
				String^ get() { return instanceName; }
			}

			/// <summary>
			/// Gets the friendly name for the product.
			/// </summary>
			property String^ ProductName
			{
				String^ get() { return productName; }
			}

			/// <summary>
			/// If the device is a Human Interface Device, this member contains
			/// the HID usage code.
			/// </summary>
			property int Usage
			{
				int get() { return usage; }
			}

			/// <summary>
			/// If the device is a Human Interface Device, this member contains
			/// the HID usage page code.
			/// </summary>
			property int UsagePage
			{
				int get() { return usagePage; }
			}

			/// <summary>
			/// Gets a value indicating whether the device is a Human Interface Device.
			/// </summary>
			property bool HumanInterfaceDevice
			{
				bool get() { return hid; }
			}
		};

		/// <summary>
		/// Describes a DirectInput device's capabilities.
		/// </summary>
		public ref class Capabilities
		{
		private:
			DeviceFlags flags;
			DeviceType type;
			int subType;
			int axesCount;
			int buttonCount;
			int povCount;
			int ffSamplePeriod;
			int ffMinTimeResolution;
			int ffDriverVersion;
			int firmwareRevision;
			int hardwareRevision;
			bool hid;

		internal:
			Capabilities( const DIDEVCAPS &caps );

		public:
			/// <summary>
			/// Gets the flags associated with the device.
			/// </summary>
			property DeviceFlags Flags
			{
				DeviceFlags get() { return flags; }
			}

			/// <summary>
			/// Gets the device type specifier.
			/// </summary>
			property DeviceType Type
			{
				DeviceType get() { return type; }
			}

			/// <summary>
			/// Gets the device sub-type specifier.
			/// </summary>
			property int SubType
			{
				int get() { return subType; }
			}

			/// <summary>
			/// Gets the number of axes available on the device.
			/// </summary>
			property int AxesCount
			{
				int get() { return axesCount; }
			}

			/// <summary>
			/// Gets the number of buttons available on the device.
			/// </summary>
			property int ButtonCount
			{
				int get() { return buttonCount; }
			}

			/// <summary>
			/// Gets the number of Point-Of-View controllers available on the device.
			/// </summary>
			property int POVCount
			{
				int get() { return povCount; }
			}

			/// <summary>
			/// Gets the minimum time between playback of consecutive raw force commands, in microseconds.
			/// </summary>
			property int ForceFeedbackSamplePeriod
			{
				int get() { return ffSamplePeriod; }
			}

			/// <summary>
			/// Gets the minimum time, in microseconds, that the device can resolve. The device
			/// rounds any times to the nearest supported increment.
			/// </summary>
			property int ForceFeedbackMinimumTimeResolution
			{
				int get() { return ffMinTimeResolution; }
			}

			/// <summary>
			/// Gets the driver version number.
			/// </summary>
			property int DriverVersion
			{
				int get() { return ffDriverVersion; }
			}

			/// <summary>
			/// Gets the firmware revision number.
			/// </summary>
			property int FirmwareRevision
			{
				int get() { return firmwareRevision; }
			}

			/// <summary>
			/// Gets the hardware revision number.
			/// </summary>
			property int HardwareRevision
			{
				int get() { return hardwareRevision; }
			}

			/// <summary>
			/// Gets a value indicating whether the device is a Human Interface Device.
			/// </summary>
			property bool HumanInterfaceDevice
			{
				bool get() { return hid; }
			}
		};

		/// <summary>
		/// Specifies the sub type of a DirectInput device.
		/// </summary>
		public ref class DeviceSubType sealed
		{
		private:
			DeviceSubType() { }

		public:
			/// <summary>
			/// A device that does not provide the minimum number of device objects for
			/// action mapping.
			/// </summary>
			literal int Limited = DI8DEVTYPE_LIMITEDGAMESUBTYPE;

			/// <summary>
			/// Unknown subtype for a first-person device.
			/// </summary>
			literal int FirstPersonUnknown = DI8DEVTYPE1STPERSON_UNKNOWN;

			/// <summary>
			/// Device designed for first-person person shooter games.
			/// </summary>
			literal int FirstPersonShooter = DI8DEVTYPE1STPERSON_SHOOTER;

			/// <summary>
			/// Device with six degrees of freedom; that is, three lateral axes and three rotation axes.
			/// </summary>
			literal int SixDegreesOfFreedom = DI8DEVTYPE1STPERSON_SIXDOF;

			/// <summary>
			/// Control used to make communications selections.
			/// </summary>
			literal int CommunicationSelections = DI8DEVTYPEDEVICECTRL_COMMSSELECTION;

			/// <summary>
			/// Device that must use its default configuration and cannot be remapped.
			/// </summary>
			literal int Hardwired = DI8DEVTYPEDEVICECTRL_COMMSSELECTION_HARDWIRED;

			/// <summary>
			/// Unknown subtype for a control device.
			/// </summary>
			literal int ControlDeviceUnknown = DI8DEVTYPEDEVICECTRL_UNKNOWN;

			/// <summary>
			/// Steering device that reports accelerations and break pedal values from a single axis.
			/// </summary>
			literal int CombinedPedals = DI8DEVTYPEDRIVING_COMBINEDPEDALS;

			/// <summary>
			/// Steering device that reports accelerations and break pedal values from separate axes.
			/// </summary>
			literal int DualPedals = DI8DEVTYPEDRIVING_DUALPEDALS;

			/// <summary>
			/// Hand-held steering device.
			/// </summary>
			literal int DrivingHandheld = DI8DEVTYPEDRIVING_HANDHELD;

			/// <summary>
			/// Steering device that reports acceleration, break, and clutch pedal values from
			/// separate axes.
			/// </summary>
			literal int ThreePedals = DI8DEVTYPEDRIVING_THREEPEDALS;

			/// <summary>
			/// Flight device based upon a remote control for model aircraft.
			/// </summary>
			literal int RemoteControlledFlight = DI8DEVTYPEFLIGHT_RC;

			/// <summary>
			/// A joystick for flight simulators.
			/// </summary>
			literal int FlightStick = DI8DEVTYPEFLIGHT_STICK;

			/// <summary>
			/// A yoke for flight simulators.
			/// </summary>
			literal int FlightYoke = DI8DEVTYPEFLIGHT_YOKE;

			/// <summary>
			/// Standard game pad that provides the minimum number of objects for
			/// action mapping.
			/// </summary>
			literal int StandardGamePad = DI8DEVTYPEGAMEPAD_STANDARD;

			/// <summary>
			/// IBM PC/XT 83-key keyboard.
			/// </summary>
			literal int PCXTKeyboard = DI8DEVTYPEKEYBOARD_PCXT;

			/// <summary>
			/// Olivetti 102-key keyboard.
			/// </summary>
			literal int OlivettiKeyboard = DI8DEVTYPEKEYBOARD_OLIVETTI;

			/// <summary>
			/// IBM PC/AT 84-key keyboard.
			/// </summary>
			literal int PCATKeyboard = DI8DEVTYPEKEYBOARD_PCAT;

			/// <summary>
			/// IBM PC Enhanced 101/102-key keyboard or Microsoft Natural keyboard.
			/// </summary>
			literal int StandardKeyboard = DI8DEVTYPEKEYBOARD_PCENH;

			/// <summary>
			/// Nokia 1050 keyboard.
			/// </summary>
			literal int Nokia1050Keyboard = DI8DEVTYPEKEYBOARD_NOKIA1050;

			/// <summary>
			/// Nokia 9140 keyboard.
			/// </summary>
			literal int Nokia9140Keyboard = DI8DEVTYPEKEYBOARD_NOKIA9140;

			/// <summary>
			/// Japanse NEC PC98 keyboard.
			/// </summary>
			literal int JapaneseNECKeyboard = DI8DEVTYPEKEYBOARD_NEC98;

			/// <summary>
			/// Japanese NEC PC98 laptop keyboard.
			/// </summary>
			literal int JapaneseNECLaptopKeyboard = DI8DEVTYPEKEYBOARD_NEC98LAPTOP;

			/// <summary>
			/// Japanese NEC PC98 106-key keyboard.
			/// </summary>
			literal int JapaneseNEC106Keyboard = DI8DEVTYPEKEYBOARD_NEC98106;

			/// <summary>
			/// Japanese 106-key keyboard.
			/// </summary>
			literal int Japanese106Keyboard = DI8DEVTYPEKEYBOARD_JAPAN106;

			/// <summary>
			/// Japanese AX keyboard.
			/// </summary>
			literal int JapaneseAXKeyboard = DI8DEVTYPEKEYBOARD_JAPANAX;

			/// <summary>
			/// Japanese J3100 keyboard.
			/// </summary>
			literal int JapaneseJ3100Keyboard = DI8DEVTYPEKEYBOARD_J3100;
		};
	}
}