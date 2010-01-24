/*
* Copyright (c) 2007-2010 SlimDX Group
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
#ifndef SLIMDX_DXGI_DEVICECHILD_
#define SLIMDX_DXGI_DEVICECHILD_

#include "../ComObject.h"
#include "ObjectDxgi.h"

#define BOOST_PP_FILENAME_1 "DeviceChildDxgi.h"
#include "../InterfaceSetup.h"
#endif
#else
#include "../InterfaceBegin.h"
#include "../ComObjectMacros.h"



namespace SlimDX
{
	namespace DXGI
	{
		ref class Device;
		
		/// <summary>
		/// An object that is bound to a Device.
		/// </summary>
		/// <unmanaged>IDXGIDeviceSubObject</unmanaged>
		SDX_COM_SUBCLASS(DeviceChild, DXGIObject) 
		{
			COMOBJECT_INTERFACE(IDXGIDeviceSubObject, DeviceChild);
		
#ifdef IS_CONCRETE
		protected:
			DeviceChild();
#endif
		public:
			/// <summary>
			/// Gets the device the object is bound to.
			/// </summary>
			property DXGI::Device^ Device
			{
				SDX_METHOD(DXGI::Device^ get());
			}
		};
		}
	};

	#include "../InterfaceEnd.h"
	#endif