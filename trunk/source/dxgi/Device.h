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
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace System::Runtime::InteropServices;

#include "../ComObject.h"

#include "Enums.h"

namespace SlimDX
{
	namespace DXGI
	{
		ref class Adapter;
		
		/// <remarks>
		/// An object that produces image data.
		/// </remarks>
		public ref class Device : public ComObject
		{
			COMOBJECT(IDXGIDevice);

		internal:
			Device( IDXGIDevice* pointer );

		public:
			/// <summary>
			/// Constructs a Device from an unmanaged pointer.
			/// </summary>
			/// <param name="pointer">The unmanaged IDXGIDevice pointer.</param>
			Device( IntPtr pointer );
			
			/// <summary>
			/// Gets the adapter associated with the device.
			/// </summary>
			/// <returns>The adapter, or null on failure.</returns>
			Adapter^ GetAdapter();
			
			/// <summary>
			/// Gets the device's GPU thread priority.
			/// <summary>
			/// <param name="priority">Receives the GPU thread priority.</param>
			/// <returns>A Result code.</returns>
			Result GetGPUThreadPriority( [Out] int% priority );
			
			/// <summary>
			/// Sets the device's GPU thread priority.
			/// </summary>
			/// <param name="priority">The GPU thread priority. Must be between -7 and 7, inclusive, where 0 represents normal.</param>
			/// <returns>A Result code.</returns>
			Result SetGPUThreadPriority( int priority );
			
			/// <summary>
			/// Gets the residency status of a list of resources.
			/// <summary>
			/// <param name="resources">The resources to query.</param>
			/// <returns>A list of residency status values, one for each entry in the input resources list. The result will be
			/// null on failure.</returns>
			ReadOnlyCollection<Residency>^ QueryResourceResidency( IList<ComObject^>^ resources ); 
		};
	}
};