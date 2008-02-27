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

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace DXGI
	{
		ref class Output;
		value class AdapterDescription;

		/// <remarks>
		/// A display subsystem (one or more GPUs, DACs, and video memory).
		/// </remarks>
		public ref class Adapter : public ComObject
		{
			COMOBJECT(IDXGIAdapter, Adapter);

		public:
			/// <summary>
			/// Gets the adapter's description.
			/// </summary>
			property AdapterDescription Description
			{
				AdapterDescription get();
			}
			
			/// <summary>
			/// Constructs an Adapter from an unmanaged pointer.
			/// </summary>
			/// <param name="pointer">The unmanaged IDXGIAdapter pointer.</param>
			static Adapter^ FromPointer( System::IntPtr pointer );
			
			/// <summary>
			/// Gets the number of outputs on the adapter.
			/// </summary>
			/// <returns>The number of outputs on the adapter.</returns>
			int GetOutputCount();
			
			/// <summary>
			/// Gets the specified output.
			/// </summary>
			/// <returns>The desired output, or null on failure.</returns>
			Output^ GetOutput( int index );
			
			/// <summary>
			/// Determines if a device interface for a graphics component is supported by the adapter.
			/// </v>
			/// <param name="type">The device interface type.</param>
			/// <returns>True if the device interface is supported, false otherwise.</returns>
			bool IsInterfaceSupported( System::Type^ type );
			
			/// <summary>
			/// Determines if a device interface for a graphics component is supported by the adapter.
			/// </summary>
			/// <param name="type">The device interface type.</param>
			/// <param name="userModeVersion">Receives the user-mode driver version of the interface.</param>
			/// <returns>True if the device interface is supported, false otherwise.</returns>
			bool IsInterfaceSupported( System::Type^ type, [Out] System::Int64% userModeVersion );	
		};
	}
};