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

#ifdef WRAP_XAPO

#include "Enums.h"

namespace SlimDX
{
	namespace XAPO
	{
		public ref class RegistrationProperties
		{
		private:
			System::Collections::ObjectModel::Collection<System::Guid>^ supportedInterfaces;

		public:
			RegistrationProperties();

			property System::Guid ClassId;
			property System::String^ FriendlyName;
			property System::String^ CopyrightInfo;
			property PropertyFlags Flags;
			property int MajorVersion;
			property int MinorVersion;
			property int MinInputBufferCount;
			property int MaxInputBufferCount;
			property int MinOutputBufferCount;
			property int MaxOutputBufferCount;

			property System::Collections::ObjectModel::Collection<System::Guid>^ SupportedInterfaces
			{
				System::Collections::ObjectModel::Collection<System::Guid>^ get() { return supportedInterfaces; }
			}
		};
	}
}

#endif