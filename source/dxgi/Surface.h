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

#include "DeviceChild.h"
#include "Enums.h"

namespace SlimDX
{
	ref class DataRectangle;

	namespace DXGI
	{
		value class SurfaceDescription;
		
		/// <remarks>
		/// A Surface represents container for image data.
		/// </remarks>
		public ref class Surface : public DeviceChild
		{
			COMOBJECT(IDXGISurface, Surface);

		public:
			/// <summary>
			/// Gets the surface's description.
			property SurfaceDescription Description
			{
				SurfaceDescription get();
			}
			
			/// <summary>
			/// Constructs a Surface from an unmanaged pointer.
			/// </summary>
			/// <param name="pointer">The unmanaged IDXGISurface pointer.</param>
			static Surface^ FromPointer( System::IntPtr pointer );
			
			/// <summary>
			/// Acquires access to the surface data.
			/// </summary>
			/// <param name="flags">Flags specifying CPU access permissions.</param>
			/// <returns>A DataRectangle for accessing the mapped data, or null on failure.</returns>.
			DataRectangle^ Map( MapFlags flags );
			
			/// <summary>
			/// Relinquishes access to the surface data.
			/// </summary>
			Result Unmap();
		};
	}
};