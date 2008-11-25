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

#include <unknwn.h>

#include "ObjectTable.h"
#include "Configuration.h"
#include "Result.h"
#include "Utilities.h"
#include "InternalHelpers.h"

#ifdef XMLDOCS
using System::IntPtr;
using System::Diagnostics::StackTrace;
#endif

#define COMOBJECT_BASE(nativeType) \
	internal: \
	static property System::Guid NativeInterface { System::Guid get() { return Utilities::ConvertNativeGuid( IID_ ## nativeType ); } } \
	property nativeType* InternalPointer { nativeType* get() new { return static_cast<nativeType*>( UnknownPointer ); } } \
	private:

#define COMOBJECT(nativeType, managedType) \
	private: \
	managedType( nativeType* pointer ); \
	managedType( System::IntPtr pointer ); \
	internal: \
	static managedType^ FromPointer( nativeType* pointer ); \
	COMOBJECT_BASE(nativeType)

namespace SlimDX
{
	/// <summary>
	/// The base class for all SlimDX types which represent COM interfaces.
	/// </summary>
	/// <unmanaged>IUnknown</unmanaged>
	public ref class ComObject abstract : System::IDisposable
	{
	private:
		IUnknown* m_Unknown;		
		System::Diagnostics::StackTrace^ m_Source;
		int m_CreationTime;

	protected:
		ComObject();
		
		void Construct( IUnknown* pointer );
		void Construct( System::IntPtr pointer, System::Guid guid );
		void Destruct();
	
	internal:
		property IUnknown* UnknownPointer
		{
			IUnknown* get();
		}

		property IUnknown* InternalPointer
		{
			IUnknown* get();
		}

		void SetSource( System::Diagnostics::StackTrace^ stack );
		void SetCreationTime( int time );

	public:
		/// <summary>
		/// Gets a value that indicates whether the object has been disposed.
		/// </summary>
		property bool Disposed
		{
			bool get();
		}
		
		/// <summary>
		/// Gets an <see cref="IntPtr">IntPtr</see> to the underlying native COM interface.
		/// </summary>
		property System::IntPtr ComPointer
		{
			System::IntPtr get();
		}
		
		/// <summary>
		/// Gets a <see cref="StackTrace"/> to the location
		/// that the object was created.
		/// </summary>
		property System::Diagnostics::StackTrace^ CreationSource
		{
			System::Diagnostics::StackTrace^ get();
		}
		
		/// <summary>
		/// Gets the timestamp, in millseconds, that this object was created.
		/// </summary>
		property int CreationTime
		{
			int get();
		}
		
		/// <summary>
		/// Gets or sets a value indicating whether or not the object is in the default allocation pool.
		/// </summary>
		property bool IsDefaultPool;
		
		/// <summary>
		/// Extra tag data stored along with the object. This member is intended for use by users of SlimDX
		/// and has no internal meaning to the library.
		/// </summary>
		property Object^ Tag;

		/// <summary>
		/// Releases all resources used by the <see cref="SlimDX::ComObject"/>.
		/// </summary>
		virtual ~ComObject();
	};
}