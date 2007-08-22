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

		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectInput::DataFormat"/> class.
			/// </summary>
			DataFormat() { objectDataFormats = gcnew List<ObjectDataFormat^>(); }

			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::DirectInput::DataFormat"/> class.
			/// </summary>
			DataFormat( DataFormatFlags flags, int dataSize )
			{
				objectDataFormats = gcnew List<ObjectDataFormat^>();
				this->dataSize = dataSize;
				this->flags = flags;
			}

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