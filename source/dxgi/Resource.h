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

#include "DeviceChild.h"
#include "Enums.h"

namespace SlimDX
{
	namespace DXGI
	{
		/// <remarks>
		/// A sharable resource.
		/// </remarks>
		public ref class Resource : public DeviceChild
		{
			COMOBJECT(IDXGIResource);

		internal:
			Resource( IDXGIResource* pointer );

		public:
			/// <summary>
			/// Gets or sets the eviction priority for the resource.
			/// </summary>
			property ResourcePriority EvictionPriority
			{
				ResourcePriority get();
				void set( ResourcePriority value );
			}
			
			/// <summary>
			/// Gets the resource usage.
			/// </summary>
			property DXGI::Usage Usage
			{
				DXGI::Usage get();
			}
			
			/// <summary>
			/// Constructs a Resource from an unmanaged pointer.
			/// </summary>
			/// <param name="pointer">The unmanaged IDXGIResource pointer.</param>
			Resource( IntPtr pointer );
		};
	}
};