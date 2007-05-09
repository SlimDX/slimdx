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

#include "../DirectXObject.h"

namespace SlimDX
{
	namespace DirectInput
	{
		[Flags]
		public enum class CooperativeLevel : Int32
		{
			Exclusive = DISCL_EXCLUSIVE,
			NonExclusive = DISCL_NONEXCLUSIVE,
			Foreground = DISCL_FOREGROUND,
			Background = DISCL_BACKGROUND,
			NoWinKey = DISCL_NOWINKEY,
		};

		public enum class DeviceDataFormat : Int32
		{
			Keyboard,
			Mouse,
			Joystick
		};

		public value class MouseState
		{
		internal:
			array<Byte>^ buttons;

		public:
			int X, Y, Z;

			property array<Byte>^ Buttons
			{
				array<Byte>^ get() { return buttons; }
			}
		};

		public ref class Device : public DirectXObject
		{
		private:
			IDirectInputDevice8W* m_Device;

		internal:
			property IDirectInputDevice8W* InternalPointer
			{
				IDirectInputDevice8W* get() { return m_Device; }
			}

			property IUnknown* ComPointer
			{
				virtual IUnknown* get() override { return m_Device; }
				virtual void set( IUnknown* value ) override { m_Device = (IDirectInputDevice8*) value; }
			}
			
		public:
			Device( IDirectInputDevice8W* device );
			Device( Guid subsystem );

			void SetDataFormat( DeviceDataFormat format );
			
			void SetCooperativeLevel( IntPtr handle, CooperativeLevel flags );
			void Acquire();
			void Unacquire();

			void Poll();

			//device state retrieval
			property MouseState CurrentMouseState { MouseState get(); }
		};
	}
}
