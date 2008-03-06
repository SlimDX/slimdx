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

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
		public value class ImageInformation : System::IEquatable<ImageInformation>
		{
		public:
			property int Width;
            property int Height;
            property int Depth;
            property int MipLevels;
            property Format Format;
            property ResourceType ResourceType;
            property ImageFileFormat ImageFileFormat;

			static ImageInformation FromFile( System::String^ fileName );
			static ImageInformation FromMemory( array<System::Byte>^ memory );

			/// <summary>
			/// Function to extract image information from a stream.
			/// </summary>
			/// <param name="stream">Stream containing the image.</param>
			/// <param name="peek">TRUE to preserve the stream position, FALSE will move the stream pointer.</param>
			/// <returns>Information about the image.</returns>
			static ImageInformation FromStream(System::IO::Stream^ stream, bool peek);

			/// <summary>
			/// Function to extract image information from a stream.
			/// </summary>
			/// <param name="stream">Stream containing the image.</param>
			/// <returns>Information about the image.</returns>
			static ImageInformation FromStream(System::IO::Stream^ stream);

			static bool operator == ( ImageInformation left, ImageInformation right );
			static bool operator != ( ImageInformation left, ImageInformation right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( ImageInformation other );
			static bool Equals( ImageInformation% value1, ImageInformation% value2 );
		};
	}
}