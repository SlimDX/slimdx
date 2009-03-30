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

// This macro provides the basic infrastructure for SlimDX ComObject subclasses. 
#define COMOBJECT(nativeType, managedType) \
	public protected: \
		managedType( nativeType* pointer, ComObject^ owner ) { Construct( pointer, owner ); } \
		managedType( System::IntPtr pointer ) { Construct( pointer, NativeInterface ); } \
	internal: \
		static managedType^ FromPointerReflectionThunk( System::IntPtr pointer ) { return FromPointer( static_cast<nativeType*>( pointer.ToPointer() ) ); } \
		static managedType^ FromPointer( nativeType* pointer ) { return FromPointer( pointer, nullptr, ComObjectFlags::None ); } \
		static managedType^ FromPointer( nativeType* pointer, ComObject^ owner ) { return FromPointer( pointer, owner, ComObjectFlags::None ); } \
		static managedType^ FromPointer( nativeType* pointer, ComObject^ owner, ComObjectFlags flags ) { return ConstructFromPointer<managedType,nativeType>( pointer, owner, flags ); } \
	public: \
		static managedType^ FromPointer( System::IntPtr pointer ) { return ConstructFromUserPointer<managedType>( pointer ); } \
	COMOBJECT_BASE(nativeType)

// This macro provides the basic infrastructure for SlimDX ComObject subclasses, but allows
// the subclass to customize the behavior of the creation process for that subclass. This macro
// should be applied instead of the regular COMOBJECT() macro when such customization is required.
// The subclass must provide a body for the following methods:
//   * managedType( nativeType* pointer, ComObject^ owner )
//   * managedType( System::IntPtr pointer )
//   * managedType^ FromPointer( nativeType* pointer, ComObject^ owner, ComObjectFlags flags )
//   * managedType^ FromPointer( System::IntPtr pointer )
//
// Partial specialization is not supported; if the subclass needs special behavior for only
// a subset of the above methods, it must still implement all of them, copying the standard
// implementation from the COMOBJECT() macro for the appropriate non-specialized methods.
#define COMOBJECT_CUSTOM(nativeType, managedType) \
	public protected: \
		managedType( nativeType* pointer, ComObject^ owner ); \
		managedType( System::IntPtr pointer ); \
	internal: \
		static managedType^ FromPointer( nativeType* pointer ) { return FromPointer( pointer, nullptr, ComObjectFlags::None ); } \
		static managedType^ FromPointer( nativeType* pointer, ComObject^ owner ) { return FromPointer( pointer, owner, ComObjectFlags::None ); } \
		static managedType^ FromPointer( nativeType* pointer, ComObject^ owner, ComObjectFlags flags ); \
	public: \
		static managedType^ FromPointer( System::IntPtr pointer ); \
	COMOBJECT_BASE(nativeType)

namespace SlimDX
{	
	[System::Flags]
	enum class ComObjectFlags
	{
		None = 0,
		IsAncillary = 1,
		IsExternal = 2
	};
	
	/// <summary>
	/// The base class for all SlimDX types which represent COM interfaces.
	/// </summary>
	/// <unmanaged>IUnknown</unmanaged>
	public ref class ComObject abstract : System::IDisposable
	{
	private:
		IUnknown* m_Unknown;
		ComObject^ m_Owner;
		ComObjectFlags m_Flags;
		System::Diagnostics::StackTrace^ m_Source;
		int m_CreationTime;

	protected:
		ComObject();
		
		void Construct( IUnknown* pointer );
		void Construct( IUnknown* pointer, ComObject^ owner );
		void Construct( System::IntPtr pointer, System::Guid guid );
		void Destruct();
		
		template< typename M, typename N >
		static M^ ConstructFromPointer( N* pointer, ComObject^ owner, ComObjectFlags flags ) 
		{
			// Since this method is called internally by SlimDX to essentially translate the results of native
			// API calls to their managed counterparts via the object table, we expect that a null pointer
			// might be passed, and that's okay. This differs from ConstructFromUserPointer.
			if( pointer == 0 )
				return nullptr;
			
			M^ tableEntry = safe_cast<M^>( SlimDX::ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
			if( tableEntry != nullptr )
			{
				if( static_cast<int>( flags & ComObjectFlags::IsAncillary ) == 0 ) 
					pointer->Release();
				return tableEntry;
			}

			M^ result = gcnew M( pointer, owner );
			result->SetFlags( flags );
			return result;
		}
		
		template< typename M >
		static M^ ConstructFromUserPointer( System::IntPtr pointer ) 
		{
			// This method gets called as a result of the user invoking the IntPtr overload of FromPointer
			// to create a SlimDX object from an externally-tracked native object. In this scenario, a
			// null pointer is a failure, so we throw.
			if( pointer == System::IntPtr::Zero )
				throw gcnew System::ArgumentNullException( "pointer" );

			M^ tableEntry = safe_cast<M^>( SlimDX::ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
			if( tableEntry != nullptr )
			{
				return tableEntry;
			}

			M^ result = gcnew M( pointer );
			result->SetFlags( ComObjectFlags::IsExternal );
			return result;
		}
		
	internal:
		property ComObject^ Owner 
		{
			ComObject^ get();
			void set( ComObject^ value );
		}
		
		property IUnknown* UnknownPointer
		{
			IUnknown* get();
		}

		property IUnknown* InternalPointer
		{
			IUnknown* get();
		}
		
		void SetFlags( ComObjectFlags flags );
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
		/// Gets a <see cref="StackTrace"/> to the location where the object was created.
		/// </summary>
		property System::Diagnostics::StackTrace^ CreationSource
		{
			System::Diagnostics::StackTrace^ get();
		}
		
		/// <summary>
		/// Gets the timestamp, in milliseconds, of the object'ss creation.
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