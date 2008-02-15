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

#include "../ComObject.h"

namespace SlimDX
{
	namespace DXGI
	{
		ref class Output;
		value class AdapterDescription;

		/// <remarks>
		/// An Adapter represents a display subsystem (one or more GPUs, DACs, and video memory).
		/// </remarks>
		public ref class Adapter : public ComObject
		{
			COMOBJECT(IDXGIAdapter);

		internal:
			Adapter( IDXGIAdapter* pointer );

		public:
			/// <remarks>
			/// Constructs a new Adapter from an unmanaged IDXGIAdapter pointer.
			/// </remarks>
			Adapter( IntPtr pointer );
			
			/// <remarks>
			/// Gets the adapter's description.
			/// </remarks>
			Result GetDescription( [Out] AdapterDescription% description );
			
			/// <remarks>
			/// Gets the number of outputs on the adapter.
			/// </remarks>
			int GetOutputCount();
			
			/// <remarks>
			/// Gets the specified output.
			/// </remarks>
			Output^ GetOutput( int index );
			
			/// <remarks>
			/// Determines if a device interface for a graphics component is supported by the adapter.
			/// </remarks>
			bool IsInterfaceSupported( Type^ type );
			
			/// <remarks>
			/// Determines if a device interface for a graphics component is supported by the adapter.
			/// </remarks>
			bool IsInterfaceSupported( Type^ type, [Out] Int64% userModeVersion );	
		};
	}
};