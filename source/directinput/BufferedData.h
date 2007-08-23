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
		/// Contains buffered device information.
		/// </summary>
		public ref class BufferedData
		{
		private:
			int offset;
			int data;
			int timeStamp;
			int sequence;
			GCHandle handle;
			Object^ appData;

			void Destruct();

		internal:
			BufferedData( const DIDEVICEOBJECTDATA &data );

		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectInput::BufferedData"/> class.
			/// </summary>
			BufferedData();

			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectInput::BufferedData"/> class.
			/// </summary>
			BufferedData( int offset, int data, int timeStamp, int sequence, Object^ applicationData );	

			/// <summary>
			/// Disposes of unmanaged resources.
			/// </summary>
			!BufferedData();

			/// <summary>
			/// Disposes of managed resources.
			/// </summary>
			~BufferedData();

			/// <summary>
			/// Compares two sequence numbers, compensating for potential wraparound. If the first is
			/// greater than the second, 1 is returned. If the second is greater than the first, -1 is
			/// returned. If they are equal, 0 is returned.
			/// </summary>
			static int CompareSequence( int sequence1, int sequence2 );

			/// <summary>
			/// Gets the offset into the current data format of the object whose data is being reported;
			/// that is, the location in which the data would have been stored if the data had been obtained
			/// by a call to the GetCurrentState method. If the device
			/// accessed is a mouse, keyboard, or joystick device, the offset is one of the mouse, keyboard,
			/// joystick constants.
			///
			/// If data is being sent to the device, the offset is the instance ID of the object to which the
			/// data is being sent.
			/// </summary>
			property int Offset
			{
				int get() { return offset; }
				void set( int value ) { offset = value; }
			}

			/// <summary>
			/// Gets or sets the data obtained from or sent to the device. For axis input, the data reflects
			/// the absolute or relative mode of the object. For button input, see the
			/// <see cref="SlimDX::DirectInput::BufferedData::ButtonData"/> property.
			/// </summary>
			property int Data
			{
				int get() { return data; }
				void set( int value ) { data = value; }
			}

			/// <summary>
			/// Gets the data obtained from a button object.
			/// </summary>
			property int ButtonData
			{
				int get() { return ( data >> 7 ) & 1; }
			}

			/// <summary>
			/// Gets the system time at which the input event was generated, in milliseconds. This value
			/// wraps around approximately every 50 days.
			/// </summary>
			property int TimeStamp
			{
				int get() { return timeStamp; }
			}

			/// <summary>
			/// Gets the DirectInput sequence number for the event. All input events are assigned an increasing
			/// sequence number. Because this value can wrap around, use the 
			/// <see cref="SlimDX::DirectInput::BufferedData::CompareSequence"/> method to reliably compare
			/// two sequence values.
			/// </summary>
			property int Sequence
			{
				int get() { return sequence; }
			}

			/// <summary>
			/// Gets the application-defined action value assigned to this object using action mapping.
			/// </summary>
			property Object^ ApplicationData
			{
				Object^ get() { return appData; }
			}
		};
	}
}