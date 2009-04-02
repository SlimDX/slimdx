/*
* Copyright (c) 2007-2009 SlimDX Group
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
#if !BOOST_PP_IS_ITERATING
#ifndef SLIMDX_DXGI_DEVICE_
#define SLIMDX_DXGI_DEVICE_

#include "../ComObject.h"

#include "Enums.h"

#define BOOST_PP_FILENAME_1 "Device.h"
#include "../InterfaceSetup.h"
#endif
#else
#include "../InterfaceBegin.h"
#include "../ComObjectMacros.h"

namespace SlimDX
{
	namespace DXGI
	{
		interface struct IAdapter;
		
		/// <summary>
		/// An object that produces image data.
		/// </summary>
		/// <unmanaged>IDXGIDevice</unmanaged>
		SDX_COM_CLASS(Device)
		{
			COMOBJECT_INTERFACE(IDXGIDevice, Device);

		public:
			/// <summary>
			/// Gets or sets the device's GPU thread priority.
			/// </summary>
			property int GpuThreadPriority
			{
				SDX_METHOD(int get());
				SDX_METHOD(void set( int value ));
			}
			
			/// <summary>
			/// Gets the adapter associated with the device.
			/// </summary>
			property IAdapter^ Adapter
			{
				SDX_METHOD(IAdapter^ get());
			}
			
			/// <summary>
			/// Initializes a new instance of the <see cref="Device"/> class.
			/// </summary>
			/// <param name="device">The COM object implementing the IDXGIDevice interface.</param>
			SDX_METHOD_CONCRETE(Device( ComObject^ device ));

			/// <summary>
			/// Gets the residency status of a list of resources.
			/// </summary>
			/// <param name="resources">The resources to query.</param>
			/// <returns>A list of residency status values, one for each entry in the input resources list. The result will be
			/// <c>null</c> on failure.</returns>
			SDX_METHOD(System::Collections::ObjectModel::ReadOnlyCollection<Residency>^ QueryResourceResidency( System::Collections::Generic::IList<ComObject^>^ resources ));
		};
	}
};

#include "../InterfaceEnd.h"
#endif