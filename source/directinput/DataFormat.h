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
using namespace System::Collections::ObjectModel;

namespace SlimDX
{
	namespace DirectInput
	{
		/// <summary>
		/// Describes a device object's data format.
		/// </summary>
		public ref class ObjectDataFormat
		{
		private:
			Guid guid;
			int offset;
			ObjectDeviceType type;
			int instanceNumber;
			ObjectDataFormatFlags flags;

		internal:
			DIOBJECTDATAFORMAT ToUnmanaged();

		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectInput::ObjectDataFormat"/> class.
		    /// </summary>
			ObjectDataFormat();
			
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectInput::ObjectDataFormat"/> class.
		    /// </summary>
			ObjectDataFormat( Guid guid, int offset, ObjectDeviceType type, int instanceNumber,
				ObjectDataFormatFlags flags );

			/// <summary>
			/// Gets or sets the unique identifier for the axis, button, or other input
			/// source. When requesting a data format, making this member equal to
			/// <see cref="System::Guid::Empty"/> indicates that any type of object
			/// is permissible.
		    /// </summary>
			property Guid SourceGuid
			{
				Guid get() { return guid; }
				void set( Guid value ) { guid = value; }
			}

			/// <summary>
			/// Gets or sets the offset within the data packet where the data for the input
			/// source is stored. This value must be a multiple of 4 for axes data. It can
			/// be byte-aligned for buttons.
		    /// </summary>
			property int Offset
			{
				int get() { return offset; }
				void set( int value ) { offset = value; }
			}

			/// <summary>
			/// Gets or sets the device type that describes the object.
		    /// </summary>
			property ObjectDeviceType Type
			{
				ObjectDeviceType get() { return type; }
				void set( ObjectDeviceType value ) { type = value; }
			}

			/// <summary>
			/// Gets or sets the object instance number. Setting this value to -1
			/// indicates that any object instance is permissible.
		    /// </summary>
			property int InstanceNumber
			{
				int get() { return instanceNumber; }
				void set( int value ) { instanceNumber = value; }
			}

			/// <summary>
			/// Gets or sets extra flags for the object data format.
		    /// </summary>
			property ObjectDataFormatFlags Flags
			{
				ObjectDataFormatFlags get() { return flags; }
				void set( ObjectDataFormatFlags value ) { flags = value; }
			}
		};

		/// <summary>
		/// Describes a device's data format.
		/// </summary>
		public ref class DataFormat
		{
		private:
			DataFormatFlags flags;
			int dataSize;
			List<ObjectDataFormat^>^ objectDataFormats;

		internal:
			DIDATAFORMAT ToUnmanaged();

		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectInput::DataFormat"/> class.
			/// </summary>
			DataFormat();

			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectInput::DataFormat"/> class.
			/// </summary>
			DataFormat( DataFormatFlags flags, int dataSize );

			/// <summary>
			/// Gets or sets the flags describing other attributes of the data format.
			/// </summary>
			property DataFormatFlags Flags
			{
				DataFormatFlags get() { return flags; }
				void set( DataFormatFlags value ) { flags = value; }
			}

			/// <summary>
			/// Gets or sets the size of a data packet returned by the device, in bytes. This
			/// value must be a multiple of 4 and must exceed the largest offset value for
			/// an object's data within the data packet.
			/// </summary>
			property int DataSize
			{
				int get() { return dataSize; }
				void set( int value ) { dataSize = value; }
			}

			/// <summary>
			/// Gets the collection of ObjectDataFormat objects that describe how each object's data
			/// should be reported to the device data.
			/// </summary>
			property Collection<ObjectDataFormat^>^ ObjectDataFormats
			{
				Collection<ObjectDataFormat^>^ get() { return gcnew Collection<ObjectDataFormat^>( objectDataFormats ); }
			}
		};
	}
}