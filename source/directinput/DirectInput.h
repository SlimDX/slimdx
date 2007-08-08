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
using namespace System::Runtime::InteropServices;

#include "../Exceptions.h"

namespace SlimDX
{
	namespace DirectInput
	{
		/// <summary>
		/// Contains system-defined identifiers for DirectInput devices.
		/// </summary>
		public ref class SystemGuid sealed
		{
		internal:
			static Guid FromGUID( const GUID &guid );

		public:
			/// <summary>
			/// Gets the system keyboard identifier.
			/// </summary>
			static property Guid Keyboard { Guid get(); }

			/// <summary>
			/// Gets the system mouse identifier.
			/// </summary>
			static property Guid Mouse { Guid get(); }
		};

		ref class Device;

		/// <summary>
		/// Provides an interface to DirectInput.
		/// </summary>
		public ref class DirectInput
		{
		private:
			static IDirectInput8W* m_DirectInput;

			static void OnExit(Object^ sender,EventArgs^ e)
			{
				Terminate();
			}

		internal:
			static property IDirectInput8W* InternalPointer
			{
				IDirectInput8W* get() { return m_DirectInput; }
			}

		public:
			/// <summary>
			/// Called by the application to initialize DirectInput. This method must be
			/// called before any other DirectInput methods.
			/// </summary>
			static void Initialize();

			/// <summary>
			/// Called by the application to release DirectInput and free any resources.
			/// </summary>
            static void Terminate();
		};
	}
}
