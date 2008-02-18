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

#include "../Utilities.h"

namespace SlimDX
{
	namespace DirectInput
	{
		/// <summary>
		/// Contains system-defined identifiers for DirectInput devices.
		/// </summary>
		public ref class SystemGuid sealed
		{
		private:
			SystemGuid() { }

		public:
			/// <summary>
			/// Gets the system keyboard identifier.
			/// </summary>
			static property System::Guid Keyboard
			{
				System::Guid get() { return Utilities::ConvertNativeGuid( GUID_SysKeyboard ); }
			}

			/// <summary>
			/// Gets the system mouse identifier.
			/// </summary>
			static property System::Guid Mouse
			{
				System::Guid get() { return Utilities::ConvertNativeGuid( GUID_SysMouse ); }
			}
		};

		/// <summary>
		/// Contains system-defined identifiers for device objects.
		/// </summary>
		public ref class ObjectGuid sealed
		{
		private:
			ObjectGuid() { }

		public:
			static property System::Guid XAxis
			{
				System::Guid get() { return Utilities::ConvertNativeGuid( GUID_XAxis ); }
			}
						
			static property System::Guid YAxis
			{
				System::Guid get() { return Utilities::ConvertNativeGuid( GUID_YAxis ); }
			}

			static property System::Guid ZAxis
			{
				System::Guid get() { return Utilities::ConvertNativeGuid( GUID_ZAxis ); }
			}

			static property System::Guid RotationalXAxis
			{
				System::Guid get() { return Utilities::ConvertNativeGuid( GUID_RxAxis ); }
			}

			static property System::Guid RotationalYAxis
			{
				System::Guid get() { return Utilities::ConvertNativeGuid( GUID_RyAxis ); }
			}

			static property System::Guid RotationalZAxis
			{
				System::Guid get() { return Utilities::ConvertNativeGuid( GUID_RzAxis ); }
			}

			static property System::Guid Slider
			{
				System::Guid get() { return Utilities::ConvertNativeGuid( GUID_Slider ); }
			}

			static property System::Guid Button
			{
				System::Guid get() { return Utilities::ConvertNativeGuid( GUID_Button ); }
			}

			static property System::Guid Key
			{
				System::Guid get() { return Utilities::ConvertNativeGuid( GUID_Key ); }
			}

			static property System::Guid PovController
			{
				System::Guid get() { return Utilities::ConvertNativeGuid( GUID_POV ); }
			}

			static property System::Guid Unknown
			{
				System::Guid get() { return Utilities::ConvertNativeGuid( GUID_Unknown ); }
			}
		};
	}
}