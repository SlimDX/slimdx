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

namespace SlimDX
{
	namespace DirectInput
	{
		/// <summary>
		/// Specifies the axis mode for the device.
		/// </summary>
		public enum class DeviceAxisMode : Int32
		{
			/// <summary>
			/// The axis works with absolute data.
			/// </summary>
			Absolute = DIPROPAXISMODE_ABS,

			/// <summary>
			/// The axis works with relative data.
			/// </summary>
			Relative = DIPROPAXISMODE_REL
		};

		/// <summary>
		/// Specifies the device type of an object data format.
		/// </summary>
		[Flags]
		public enum class ObjectDeviceType : Int32
		{
			/// <summary>
		    /// The object must be an absolute axis.
		    /// </summary>
			AbsoluteAxis = DIDFT_ABSAXIS,

			/// <summary>
		    /// The object must be an absolute or relative axis.
		    /// </summary>
			Axis = DIDFT_AXIS,

			/// <summary>
		    /// The object must be a relative axis.
		    /// </summary>
			RelativeAxis = DIDFT_RELAXIS,

			/// <summary>
		    /// The object must be a toggle or push button.
		    /// </summary>
			Button = DIDFT_BUTTON,

			/// <summary>
		    /// The object must contain a force-feedback actuator.
		    /// </summary>
			ForceFeedbackActuator = DIDFT_FFACTUATOR,

			/// <summary>
		    /// The object must be a valid force-feedback effect trigger.
		    /// </summary>
			ForceFeedbackEffectTrigger = DIDFT_FFEFFECTTRIGGER,

			/// <summary>
		    /// The object must be a Point-Of-View controller.
		    /// </summary>
			PointOfViewController = DIDFT_POV,

			/// <summary>
		    /// The object must be a push button.
		    /// </summary>
			PushButton = DIDFT_PSHBUTTON,

			/// <summary>
		    /// The object must be a toggle button.
		    /// </summary>
			ToggleButton = DIDFT_TGLBUTTON,

			/// <summary>
		    /// The object must be a type defined by the manufacturer.
		    /// </summary>
			VendorDefined = DIDFT_VENDORDEFINED
		};

		/// <summary>
		/// Specifies other attributes of an object data format.
		/// </summary>
		[Flags]
		public enum class ObjectDataFormatFlags : Int32
		{
			/// <summary>
		    /// No extra flags specified.
		    /// </summary>
			None = 0,

			/// <summary>
		    /// The object must report acceleration information.
		    /// </summary>
			Acceleration,

			/// <summary>
		    /// The object must report force information.
		    /// </summary>
			Force,

			/// <summary>
		    /// The object must report position information.
		    /// </summary>
			Position,

			/// <summary>
		    /// The object must report velocity information.
		    /// </summary>
			Velocity
		};

		/// <summary>
		/// Specifies other attributes of a data format.
		/// </summary>
		public enum class DataFormatFlag : Int32
		{
			/// <summary>
			/// The axes are in absolute mode.
			/// </summary>
			AbsoluteAxis = DIDF_ABSAXIS,

			/// <summary>
			/// The axes are in relative mode.
			/// </summary>
			RelativeAxis = DIDF_RELAXIS
		};

		/// <summary>
		/// Specifies the main type of a DirectInput device.
		/// </summary>
		public enum class DeviceType : Int32
		{
			/// <summary>
			/// A first-person action game device.
			/// </summary>
			FirstPerson = DI8DEVTYPE_1STPERSON,

			/// <summary>
			/// A device that does not fall into any other category.
			/// </summary>
			Other = DI8DEVTYPE_DEVICE,

			/// <summary>
			/// Input device used to control another type of device from within the context of
			/// the application.
			/// </summary>
			ControlDevice = DI8DEVTYPE_DEVICECTRL,

			/// <summary>
			/// A device for steering.
			/// </summary>
			Driving = DI8DEVTYPE_DRIVING,

			/// <summary>
			/// Controller for a flight simulation.
			/// </summary>
			Flight = DI8DEVTYPE_FLIGHT,

			/// <summary>
			/// A console game pad.
			/// </summary>
			Gamepad = DI8DEVTYPE_GAMEPAD,

			/// <summary>
			/// A generic joystick.
			/// </summary>
			Joystick = DI8DEVTYPE_JOYSTICK,

			/// <summary>
			/// A keyboard or keyboard-like device.
			/// </summary>
			Keyboard = DI8DEVTYPE_KEYBOARD,

			/// <summary>
			/// A mouse or mouse-like device.
			/// </summary>
			Mouse = DI8DEVTYPE_MOUSE,

			/// <summary>
			/// A remote-control device.
			/// </summary>
			Remote = DI8DEVTYPE_REMOTE,

			/// <summary>
			/// A screen pointer device.
			/// </summary>
			ScreenPointer = DI8DEVTYPE_SCREENPOINTER,

			/// <summary>
			/// A specialized device with functionality unsuitable for main control of an application,
			/// such as pedals with a wheel.
			/// </summary>
			Supplemental = DI8DEVTYPE_SUPPLEMENTAL
		};

		/// <summary>
		/// Specifies the flags that can be associated with a DirectInput device.
		/// </summary>
		[Flags]
		public enum class DeviceFlags : Int32
		{
			/// <summary>
			/// The device is a duplicate of another DirectInput device.
			/// </summary>
			Alias = DIDC_ALIAS,

			/// <summary>
			/// The device is physically attached to the user's computer.
			/// </summary>
			Attached = DIDC_ATTACHED,

			/// <summary>
			/// The device supports deadband for at least one force-feedback condition.
			/// </summary>
			DeadBand = DIDC_DEADBAND,

			/// <summary>
			/// Specifies that the device's data is coming from a user mode device interface.
			/// </summary>
			Emulated = DIDC_EMULATED,

			/// <summary>
			/// The device supports force-feedback.
			/// </summary>
			ForceFeedback = DIDC_FORCEFEEDBACK,

			/// <summary>
			/// The force-feedback system supports the fade parameter for at least one effect.
			/// </summary>
			ForceFeedbackFade = DIDC_FFFADE,

			/// <summary>
			/// The force-feedback system supports the attack parameter for at least one effect.
			/// </summary>
			ForceFeedbackAttack = DIDC_FFATTACK,

			/// <summary>
			/// The device is a fictious device created by a device driver so that is can generate
			/// mouse and keyboard events.
			/// </summary>
			Hidden = DIDC_HIDDEN,

			/// <summary>
			/// The device is a placeholder.
			/// </summary>
			Phantom = DIDC_PHANTOM,

			/// <summary>
			/// At least one object in the current data format is polled, rather than interrupt driven.
			/// </summary>
			PolledDataFormat = DIDC_POLLEDDATAFORMAT,

			/// <summary>
			/// At least one object on the device is polled, rather than interrupt driven.
			/// </summary>
			PolledDevice = DIDC_POLLEDDEVICE,

			/// <summary>
			/// The force-feedback system supports two coefficient values for conditions.
			/// </summary>
			PositiveNegativeCoefficients = DIDC_POSNEGCOEFFICIENTS,

			/// <summary>
			/// The force-feedback system supports a maximum saturation for both positive and negative
			/// force output for at least one condition.
			/// </summary>
			PositiveNegativeSaturation = DIDC_POSNEGSATURATION,

			/// <summary>
			/// The force-feedback system supports the saturation of condition effects for at least
			/// one condition.
			/// </summary>
			Saturation = DIDC_SATURATION,

			/// <summary>
			/// The force-feedback system supports the start delay parameter for at least one effect.
			/// </summary>
			StartDelay = DIDC_STARTDELAY
		};

		/// <summary>
		/// Specifies the cooperative level for a DirectInput device.
		/// </summary>
		[Flags]
		public enum class CooperativeLevel : Int32
		{
			/// <summary>
			/// Exclusive access to the device.
			/// </summary>
			Exclusive = DISCL_EXCLUSIVE,

			/// <summary>
			/// Non exclusive access to the device.
			/// </summary>
			Nonexclusive = DISCL_NONEXCLUSIVE,

			/// <summary>
			/// Foreground operation of the device.
			/// </summary>
			Foreground = DISCL_FOREGROUND,

			/// <summary>
			/// Background operation of the device.
			/// </summary>
			Background = DISCL_BACKGROUND,

			/// <summary>
			/// Disables the Windows logo key.
			/// </summary>
			NoWinKey = DISCL_NOWINKEY,
		};

		/// <summary>
		/// The data format for a DirectInput device.
		/// </summary>
		public enum class DeviceDataFormat : Int32
		{
			/// <summary>
			/// Keyboard data.
			/// </summary>
			Keyboard,

			/// <summary>
			/// Mouse data.
			/// </summary>
			Mouse,

			/// <summary>
			/// Joystick data.
			/// </summary>
			Joystick
		};
	}
}