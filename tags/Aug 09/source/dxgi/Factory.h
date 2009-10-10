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
#ifndef SLIMDX_DXGI_FACTORY_
#define SLIMDX_DXGI_FACTORY_

#include "../ComObject.h"

#include "Enums.h"
#include "ObjectDxgi.h"

#define BOOST_PP_FILENAME_1 "Factory.h"
#include "../InterfaceSetup.h"
#endif
#else
#include "../InterfaceBegin.h"
#include "../ComObjectMacros.h"

namespace SlimDX
{
	namespace DXGI
	{
		ref class Adapter;

		SDX_COM_SUBCLASS(Factory, DXGIObject)
		{
			COMOBJECT_INTERFACE(IDXGIFactory, Factory);
			
		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="Factory"/> class.
			/// </summary>
			SDX_METHOD_CONCRETE(Factory());
			
			/// <summary>
			/// Gets the number of available adapters.
			/// </summary>
			/// <returns>The number of available adapters.</returns>
			SDX_METHOD(int GetAdapterCount());
			
			/// <summary>
			/// Gets the specified adapter.
			/// </summary>
			/// <param name="index">The index of the desired adapter.</param>
			/// <returns>The specified adapter, or <c>null</c> on failure.</returns>
			SDX_METHOD(Adapter^ GetAdapter( int index ));
		
			/// <summary>
			/// Creates a software adapater interface.
			/// </summary>
			/// <param name="softwareModule">The unmanaged HMODULE for the software adapter DLL.</param>
			/// <returns>The specified adapter, or <c>null</c> on failure.</returns>
			[System::Security::Permissions::SecurityPermission( System::Security::Permissions::SecurityAction::LinkDemand, Flags=System::Security::Permissions::SecurityPermissionFlag::UnmanagedCode )]
			SDX_METHOD(Adapter^ CreateSoftwareAdapter( System::IntPtr softwareModule ));
			
			/// <summary>
			/// Creates a software adapater interface.
			/// </summary>
			/// <param name="softwareModule">The module for the software adapter DLL.</param>
			/// <returns>The specified adapter, or <c>null</c> on failure.</returns>
			[System::Security::Permissions::SecurityPermission( System::Security::Permissions::SecurityAction::LinkDemand, Flags=System::Security::Permissions::SecurityPermissionFlag::UnmanagedCode )]
			SDX_METHOD(Adapter^ CreateSoftwareAdapter( System::Reflection::Module^ softwareModule ));
			
			/// <summary>
			/// Gets the window handle associated with the factory (the window through which the user signals fullscreen
			/// transitions).
			/// </summary>
			/// <returns>The window handle.</returns>
			SDX_METHOD(System::IntPtr GetWindowAssociation());
			
			/// <summary>
			/// Sets the window handle associated with the factory (the window through which the user signals fullscreen
			/// transitions).
			/// </summary>
			/// <param name="handle">The window handle.</param>
			/// <param name="flags">Flags controlling window association behavior.</param>
			/// <returns>A <see cref="SlimDX::Result"/> object describing the result of the operation.</returns>
			SDX_METHOD(Result SetWindowAssociation( System::IntPtr handle, WindowAssociationFlags flags ));
		};
	}
};

#include "../InterfaceEnd.h"
#endif