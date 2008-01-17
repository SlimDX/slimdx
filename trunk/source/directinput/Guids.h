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
			static property Guid Keyboard
			{
				Guid get() { return Utilities::FromGUID( GUID_SysKeyboard ); }
			}

			/// <summary>
			/// Gets the system mouse identifier.
			/// </summary>
			static property Guid Mouse
			{
				Guid get() { return Utilities::FromGUID( GUID_SysMouse ); }
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
			static property Guid XAxis
			{
				Guid get() { return Utilities::FromGUID( GUID_XAxis ); }
			}

			static property Guid YAxis
			{
				Guid get() { return Utilities::FromGUID( GUID_YAxis ); }
			}

			static property Guid ZAxis
			{
				Guid get() { return Utilities::FromGUID( GUID_ZAxis ); }
			}

			static property Guid RotationalXAxis
			{
				Guid get() { return Utilities::FromGUID( GUID_RxAxis ); }
			}

			static property Guid RotationalYAxis
			{
				Guid get() { return Utilities::FromGUID( GUID_RyAxis ); }
			}

			static property Guid RotationalZAxis
			{
				Guid get() { return Utilities::FromGUID( GUID_RzAxis ); }
			}

			static property Guid Slider
			{
				Guid get() { return Utilities::FromGUID( GUID_Slider ); }
			}

			static property Guid Button
			{
				Guid get() { return Utilities::FromGUID( GUID_Button ); }
			}

			static property Guid Key
			{
				Guid get() { return Utilities::FromGUID( GUID_Key ); }
			}

			static property Guid PovController
			{
				Guid get() { return Utilities::FromGUID( GUID_POV ); }
			}

			static property Guid Unknown
			{
				Guid get() { return Utilities::FromGUID( GUID_Unknown ); }
			}
		};
	}
}