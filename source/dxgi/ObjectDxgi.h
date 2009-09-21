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
#ifndef SLIMDX_DXGI_OBJECTDXGI_
#define SLIMDX_DXGI_OBJECTDXGI_

#include "../ComObject.h"
#include "Enums.h"

#define BOOST_PP_FILENAME_1 "ObjectDxgi.h"
#include "../InterfaceSetup.h"
#endif
#else
#include "../InterfaceBegin.h"
#include "../ComObjectMacros.h"

namespace SlimDX
{
	namespace DXGI
	{
		ref class Object;

		/// <summary>
		/// Base class for all DXGI objects
		/// </summary>
		SDX_COM_CLASS(DXGIObject)
		{
			COMOBJECT_INTERFACE_BASE(IDXGIObject);

		public:
			/// <summary>
			/// Gets the parent of the object.
			/// </summary>
			/// <typeparam name="T">The type of the parent object.</typeparam>
			generic<typename T> where T : DXGIObject, ref class 
			T GetParent();
		};
	}
};

#include "../InterfaceEnd.h"
#endif