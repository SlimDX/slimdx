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
	namespace RawInput
	{
		public ref class Device
		{
		private:
			UsagePage usagePage;
			UsageId usageId;
			DeviceFlags flags;
			System::IntPtr target;

		public:
			Device( UsagePage usagePage, UsageId usageId, DeviceFlags flags );
			Device( UsagePage usagePage, UsageId usageId, DeviceFlags flags, System::IntPtr target );
			virtual ~Device();

			static array<Device^>^ FromUsagePage( UsagePage usagePage );
			static array<Device^>^ FromUsagePage( UsagePage usagePage, array<UsageId>^ exclusions );

			property UsagePage UsagePage
			{
				SlimDX::RawInput::UsagePage get() { return usagePage; }
			}

			property UsageId UsageId
			{
				SlimDX::RawInput::UsageId get() { return usageId; }
			}

			property DeviceFlags Flags
			{
				DeviceFlags get() { return flags; }
			}

			property System::IntPtr Target
			{
				System::IntPtr get() { return target; }
			}

			property static System::Collections::ObjectModel::ReadOnlyCollection<Device^>^ RegisteredDevices
			{
				System::Collections::ObjectModel::ReadOnlyCollection<Device^>^ get();
			}
		};
	}
}