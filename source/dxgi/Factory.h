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
		/// Provides access to connected adapters and window associations. A <see cref="Factory"/>
		/// is also required to create most DXGI objects.
		/// </summary>
		public ref class Factory : public ComObject
		{
			COMOBJECT(IDXGIFactory, Factory);
			
		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="Factory"/> class.
			/// </summary>
			Factory();
			
			/// <summary>
			/// Constructs a new instance of the <see cref="Factory"/> class using the specified pointer to a
			/// previously constructed unmanaged object.
			/// </summary>
			/// <param name="pointer">The unmanaged IDXGIFactory pointer.</param>
			/// <returns>The newly constructed object.</returns>
			static Factory^ FromPointer( System::IntPtr pointer );
			
			/// <summary>
			/// Gets the number of available adapters.
			/// </summary>
			/// <returns>The number of available adapters.</returns>
			int GetAdapterCount();
			
			/// <summary>
			/// Gets the specified adapter.
			/// </summary>
			/// <param name="index">The index of the desired adapter.</param>
			/// <returns>The specified adapter, or <c>null</c> on failure.</returns>
			Adapter^ GetAdapter( int index );
		
			/// <summary>
			/// Creates a software adapater interface.
			/// </summary>
			/// <param name="module">The unmanaged HMODULE for the software adapter DLL.</param>
			/// <returns>The specified adapter, or <c>null</c> on failure.</returns>
			[System::Security::Permissions::SecurityPermission( System::Security::Permissions::SecurityAction::LinkDemand, Flags=System::Security::Permissions::SecurityPermissionFlag::UnmanagedCode )]
			Adapter^ CreateSoftwareAdapter( System::IntPtr module );
			
			/// <summary>
			/// Creates a software adapater interface.
			/// </summary>
			/// <param name="module">The module for the software adapter DLL.</param>
			/// <returns>The specified adapter, or <c>null</c> on failure.</returns>
			[System::Security::Permissions::SecurityPermission( System::Security::Permissions::SecurityAction::LinkDemand, Flags=System::Security::Permissions::SecurityPermissionFlag::UnmanagedCode )]
			Adapter^ CreateSoftwareAdapter( System::Reflection::Module^ module );
			
			/// <summary>
			/// Gets the window handle associated with the factory (the window through which the user signals fullscreen
			/// transitions).
			/// </summary>
			/// <returns>The window handle.</returns>
			System::IntPtr GetWindowAssociation();
			
			/// <summary>
			/// Sets the window handle associated with the factory (the window through which the user signals fullscreen
			/// transitions).
			/// </summary>
			/// <param name="handle">The window handle.</param>
			/// <param name="flags">Flags controlling window association behavior.</param>
			/// <returns>A <see cref="SlimDX.Result"/> object describing the result of the operation.</returns>
			Result SetWindowAssociation( System::IntPtr handle, WindowAssociationFlags flags );
		};
	}
};