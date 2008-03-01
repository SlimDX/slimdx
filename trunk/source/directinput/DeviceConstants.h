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
	namespace DirectInput
	{
		/// <summary>
		/// Defines possible joystick object codes.
		/// </summary>
		public ref class JoystickObjects sealed
		{
		private:
			JoystickObjects() { }

		public:
			/// <summary>
			/// The rotational X axis.
			/// </summary>
			literal int XAxisRotation = DIJOFS_RX;

			/// <summary>
			/// The rotational X axis.
			/// </summary>
			literal int YAxisRotation = DIJOFS_RY;

			/// <summary>
			/// The rotational X axis.
			/// </summary>
			literal int ZAxisRotation = DIJOFS_RZ;

			/// <summary>
			/// The rotational X axis.
			/// </summary>
			literal int XAxis = DIJOFS_X;

			/// <summary>
			/// The rotational X axis.
			/// </summary>
			literal int YAxis = DIJOFS_Y;

			/// <summary>
			/// The rotational X axis.
			/// </summary>
			literal int ZAxis = DIJOFS_Z;

			/// <summary>
			/// Provides scan codes for the specified button.
			/// </summary>
			static int Button( int buttonId );

			/// <summary>
			/// Provides scan codes for the specified slider.
			/// </summary>
			static int Slider( int sliderId );

			/// <summary>
			/// Provides scan codes for the specified Point-Of-View controller.
			/// </summary>
			static int PointOfView( int povId );
		};

		/// <summary>
		/// Defines object codes that refer to any control type on a device.
		/// </summary>
		public ref class AnyControl sealed
		{
		private:
			AnyControl() { }

		public:
			/// <summary>
			/// Refers to any axis.
			/// </summary>
			literal int Axis1 = DIAXIS_ANY_1;

			/// <summary>
			/// Refers to any axis.
			/// </summary>
			literal int Axis2 = DIAXIS_ANY_2;

			/// <summary>
			/// Refers to any axis.
			/// </summary>
			literal int Axis3 = DIAXIS_ANY_3;

			/// <summary>
			/// Refers to any accelerator.
			/// </summary>
			literal int Accelerator1 = DIAXIS_ANY_A_1;

			/// <summary>
			/// Refers to any accelerator.
			/// </summary>
			literal int Accelerator2 = DIAXIS_ANY_A_2;

			/// <summary>
			/// Refers to any brake.
			/// </summary>
			literal int Brake1 = DIAXIS_ANY_B_1;

			/// <summary>
			/// Refers to any brake.
			/// </summary>
			literal int Brake2 = DIAXIS_ANY_B_2;

			/// <summary>
			/// Refers to any clutch.
			/// </summary>
			literal int Clutch1 = DIAXIS_ANY_C_1;

			/// <summary>
			/// Refers to any clutch.
			/// </summary>
			literal int Clutch2 = DIAXIS_ANY_C_2;

			/// <summary>
			/// Refers to any r-axis.
			/// </summary>
			literal int RAxis1 = DIAXIS_ANY_R_1;

			/// <summary>
			/// Refers to any r-axis.
			/// </summary>
			literal int RAxis2 = DIAXIS_ANY_R_2;

			/// <summary>
			/// Refers to any s-axis.
			/// </summary>
			literal int SAxis1 = DIAXIS_ANY_S_1;

			/// <summary>
			/// Refers to any s-axis.
			/// </summary>
			literal int SAxis2 = DIAXIS_ANY_S_2;

			/// <summary>
			/// Refers to any u-axis.
			/// </summary>
			literal int UAxis1 = DIAXIS_ANY_U_1;

			/// <summary>
			/// Refers to any u-axis.
			/// </summary>
			literal int UAxis2 = DIAXIS_ANY_U_2;

			/// <summary>
			/// Refers to any v-axis.
			/// </summary>
			literal int VAxis1 = DIAXIS_ANY_V_1;

			/// <summary>
			/// Refers to any v-axis.
			/// </summary>
			literal int VAxis2 = DIAXIS_ANY_V_2;

			/// <summary>
			/// Refers to any x-axis.
			/// </summary>
			literal int XAxis1 = DIAXIS_ANY_X_1;

			/// <summary>
			/// Refers to any x-axis.
			/// </summary>
			literal int XAxis2 = DIAXIS_ANY_X_2;

			/// <summary>
			/// Refers to any y-axis.
			/// </summary>
			literal int YAxis1 = DIAXIS_ANY_Y_1;

			/// <summary>
			/// Refers to any y-axis.
			/// </summary>
			literal int YAxis2 = DIAXIS_ANY_Y_2;

			/// <summary>
			/// Refers to any z-axis.
			/// </summary>
			literal int ZAxis1 = DIAXIS_ANY_Z_1;

			/// <summary>
			/// Refers to any z-axis.
			/// </summary>
			literal int ZAxis2 = DIAXIS_ANY_Z_2;

			/// <summary>
			/// Refers to any point-of-view controller.
			/// </summary>
			literal int PointOfView1 = DIPOV_ANY_1;

			/// <summary>
			/// Refers to any point-of-view controller.
			/// </summary>
			literal int PointOfView2 = DIPOV_ANY_2;

			/// <summary>
			/// Refers to any point-of-view controller.
			/// </summary>
			literal int PointOfView3 = DIPOV_ANY_3;

			/// <summary>
			/// Refers to any point-of-view controller.
			/// </summary>
			literal int PointOfView4 = DIPOV_ANY_4;

			/// <summary>
			/// Refers to any button.
			/// </summary>
			static int Button( int buttonId );
		};

		/// <summary>
		/// Defines possible mouse object codes.
		/// </summary>
		public enum class MouseObject : System::Int32
		{
			/// <summary>
			/// The first button.
			/// </summary>
			Button1,

			/// <summary>
			/// The second button.
			/// </summary>
			Button2,

			/// <summary>
			/// The third button.
			/// </summary>
			Button3,

			/// <summary>
			/// The fourth button.
			/// </summary>
			Button4,

			/// <summary>
			/// The fifth button.
			/// </summary>
			Button5,

			/// <summary>
			/// The sixth button.
			/// </summary>
			Button6,

			/// <summary>
			/// The seventh button.
			/// </summary>
			Button7,

			/// <summary>
			/// The eighth button.
			/// </summary>
			Button8,

			/// <summary>
			/// The X axis.
			/// </summary>
			XAxis,

			/// <summary>
			/// The Y axis.
			/// </summary>
			YAxis,

			/// <summary>
			/// The Z axis.
			/// </summary>
			ZAxis
		};

		private ref class DeviceConstantConverter sealed
		{
		private:
			DeviceConstantConverter() { }

		public:
			static int KeyToDIK( Key key );
			static Key DIKToKey( int dik );
			
			/* Unused.
			static int MouseToDIMOFS( MouseObject mouse );
			static int MouseToDIMOUSE( MouseObject mouse );
			static int KeyToDIKEYBOARD( Key key );
			*/
		};
	}
}