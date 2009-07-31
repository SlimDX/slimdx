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
#ifndef SLIMDX_DXGI_ADAPTER_
#define SLIMDX_DXGI_ADAPTER_

#include "../ComObject.h"

using System::Runtime::InteropServices::OutAttribute;

#define BOOST_PP_FILENAME_1 "Adapter.h"
#include "../InterfaceSetup.h"
#endif
#else
#include "../InterfaceBegin.h"
#include "../ComObjectMacros.h"

namespace SlimDX
{
	namespace DXGI
	{
		FORWARD_DECL_REF(Output);
		FORWARD_DECL_VALUE(AdapterDescription);

		/// <summary>
		/// A display subsystem (one or more GPUs, DACs, and video memory).
		/// </summary>
		/// <unmanaged>IDXGIAdapter</unmanaged>
		SDX_COM_CLASS( Adapter )
		{
			COMOBJECT_INTERFACE(IDXGIAdapter, Adapter);

		public:
			/// <summary>
			/// Gets the adapter's description.
			/// </summary>
			property AdapterDescription Description
			{
				SDX_METHOD(AdapterDescription get());
			}

			/// <summary>
			/// Gets the number of outputs on the adapter.
			/// </summary>
			/// <returns>The number of outputs on the adapter.</returns>
			SDX_METHOD(int GetOutputCount());
			
			/// <summary>
			/// Gets the specified output.
			/// </summary>
			/// <returns>The desired output, or <c>null</c> on failure.</returns>
			SDX_METHOD(Output^ GetOutput( int index ));
			
			/// <summary>
			/// Determines if a device interface for a graphics component is supported by the adapter.
			/// </summary>
			/// <param name="type">The device interface type.</param>
			/// <returns><c>true</c> if the device interface is supported; otherwise, <c>false</c>.</returns>
			SDX_METHOD(bool IsInterfaceSupported( System::Type^ type ));
			
			/// <summary>
			/// Determines if a device interface for a graphics component is supported by the adapter.
			/// </summary>
			/// <param name="type">The device interface type.</param>
			/// <param name="userModeVersion">Receives the user-mode driver version of the interface.</param>
			/// <returns><c>true</c> if the device interface is supported; otherwise, <c>false</c>.</returns>
			SDX_METHOD(bool IsInterfaceSupported( System::Type^ type, [Out] System::Int64% userModeVersion ));
			
			/// <summary>
			/// Converts the value of the object to its equivalent string representation.
			/// </summary>
			/// <returns>The string representation of the value of this instance.</returns>
			SDX_METHOD_CONCRETE(virtual System::String^ ToString() override);
		};
	}
};

#include "../InterfaceEnd.h"
#endif