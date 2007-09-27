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
		/// Contains system-defined identifiers for DirectInput devices.
		/// </summary>
		public ref class SystemGuid sealed
		{
		private:
			SystemGuid() { }

		internal:
			static Guid FromGUID( const GUID &guid )
			{
				Guid result( guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], 
					guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7] );
				return result;
			}

			static GUID ToGUID( Guid guid )
			{
				GUID result;
				array<Byte>^ bytes = guid.ToByteArray();
				pin_ptr<unsigned char> pinned_bytes = &bytes[0];
				memcpy( &result, pinned_bytes, sizeof(GUID) );
		
				return result;
			}

		public:
			/// <summary>
			/// Gets the system keyboard identifier.
			/// </summary>
			static property Guid Keyboard
			{
				Guid get() { return SystemGuid::FromGUID( GUID_SysKeyboard ); }
			}

			/// <summary>
			/// Gets the system mouse identifier.
			/// </summary>
			static property Guid Mouse
			{
				Guid get() { return SystemGuid::FromGUID( GUID_SysMouse ); }
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
				Guid get() { return SystemGuid::FromGUID( GUID_XAxis ); }
			}

			static property Guid YAxis
			{
				Guid get() { return SystemGuid::FromGUID( GUID_YAxis ); }
			}

			static property Guid ZAxis
			{
				Guid get() { return SystemGuid::FromGUID( GUID_ZAxis ); }
			}

			static property Guid RotationalXAxis
			{
				Guid get() { return SystemGuid::FromGUID( GUID_RxAxis ); }
			}

			static property Guid RotationalYAxis
			{
				Guid get() { return SystemGuid::FromGUID( GUID_RyAxis ); }
			}

			static property Guid RotationalZAxis
			{
				Guid get() { return SystemGuid::FromGUID( GUID_RzAxis ); }
			}

			static property Guid Slider
			{
				Guid get() { return SystemGuid::FromGUID( GUID_Slider ); }
			}

			static property Guid Button
			{
				Guid get() { return SystemGuid::FromGUID( GUID_Button ); }
			}

			static property Guid Key
			{
				Guid get() { return SystemGuid::FromGUID( GUID_Key ); }
			}

			static property Guid PovController
			{
				Guid get() { return SystemGuid::FromGUID( GUID_POV ); }
			}

			static property Guid Unknown
			{
				Guid get() { return SystemGuid::FromGUID( GUID_Unknown ); }
			}
		};
	}
}