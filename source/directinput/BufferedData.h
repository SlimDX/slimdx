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
using namespace System::Reflection;

namespace SlimDX
{
	namespace DirectInput
	{
		/// <summary>
		/// Contains buffered device information.
		/// </summary>
		generic<typename DataFormat>
		public ref class BufferedData
		{
		private:
			DataFormat data;
			int timeStamp;
			int sequence;
			Object^ appData;

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
			BufferedData( DataFormat data );

			/// <summary>
			/// Gets or sets the data obtained from or sent to the device. For axis input, the data reflects
			/// the absolute or relative mode of the object.
			/// </summary>
			property DataFormat Data
			{
				DataFormat get() { return data; }
				void set( DataFormat value ) { data = value; }
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
			/// sequence number.
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

		generic<typename DataFormat>
		public ref class BufferedDataCollection : IEnumerable<BufferedData<DataFormat>^>
		{
		private:
			List<BufferedData<DataFormat>^>^ list;

		internal:
			BufferedDataCollection();

			void Add( BufferedData<DataFormat>^ data );

		public:
			property int Count
			{
				int get() { return list->Count; }
			}

			property BufferedData<DataFormat>^ default[int]
			{
				BufferedData<DataFormat>^ get( int index ) { return list[index]; }
			}

			virtual IEnumerator<BufferedData<DataFormat>^>^ GetEnumerator() { return list->GetEnumerator(); }

			virtual System::Collections::IEnumerator^ GetEnumerator2() = System::Collections::IEnumerable::GetEnumerator
			{
				return ((System::Collections::IEnumerable^)list)->GetEnumerator();
			}
		};
	}
}