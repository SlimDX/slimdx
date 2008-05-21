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

#include "../ComObject.h"

#include "Enums.h"

namespace SlimDX
{
	namespace DXGI
	{
		ref class Adapter;
		
		/// <summary>
		/// An object that produces image data.
		/// </summary>
		public ref class Device : public ComObject
		{
			COMOBJECT(IDXGIDevice, Device);

		public:
			/// <summary>
			/// Gets or sets the device's GPU thread priority.
			/// </summary>
			property int GpuThreadPriority
			{
				int get();
				void set( int value );
			}
			
			/// <summary>
			/// Gets the adapter associated with the device.
			/// </summary>
			property DXGI::Adapter^ Adapter
			{
				DXGI::Adapter^ get();
			}
			
			/// <summary>
			/// Constructs a new instance of the <see cref="Device"/> class using the specified pointer to a
			/// previously constructed unmanaged object.
			/// </summary>
			/// <param name="pointer">The unmanaged IDXGIDevice pointer.</param>
			/// <returns>The newly constructed object.</returns>
			static Device^ FromPointer( System::IntPtr pointer );
			
			/// <summary>
			/// Gets the residency status of a list of resources.
			/// </summary>
			/// <param name="resources">The resources to query.</param>
			/// <returns>A list of residency status values, one for each entry in the input resources list. The result will be
			/// <c>null</c> on failure.</returns>
			System::Collections::ObjectModel::ReadOnlyCollection<Residency>^ QueryResourceResidency( System::Collections::Generic::IList<ComObject^>^ resources ); 
		};
	}
};