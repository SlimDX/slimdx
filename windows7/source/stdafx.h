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

// This header epitomizes the abomination that is C++/CLI
// Modify it at your own peril

#ifdef X64
#ifdef PUBLIC
#using "../build/x64/Public/SlimDX.dll" as_friend
#else
#ifdef NDEBUG
#using "../build/x64/Release/SlimDX.dll" as_friend
#else
#using "../build/x64/Debug/SlimDX.dll" as_friend
#endif
#endif
#else
#ifdef PUBLIC
#using "../build/x86/Public/SlimDX.dll" as_friend
#else
#ifdef NDEBUG
#using "../build/x86/Release/SlimDX.dll" as_friend
#else
#using "../build/x86/Debug/SlimDX.dll" as_friend
#endif
#endif
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

template< typename M, typename N >
M^ ConstructFromPointer( N* pointer, SlimDX::ComObject^ owner, SlimDX::ComObjectFlags flags ) 
{
	// Since this method is called internally by SlimDX to essentially translate the results of native
	// API calls to their managed counterparts via the object table, we expect that a null pointer
	// might be passed, and that's okay. This differs from ConstructFromUserPointer.
	if( pointer == 0 )
		return nullptr;
	
	M^ tableEntry = safe_cast<M^>( SlimDX::ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
	if( tableEntry != nullptr )
	{
		if( static_cast<int>( flags & SlimDX::ComObjectFlags::IsAncillary ) == 0 ) 
			pointer->Release();
		return tableEntry;
	}

	M^ result = gcnew M( pointer, owner );
	result->SetFlags( flags );
	return result;
}

template< typename M >
M^ ConstructFromUserPointer( System::IntPtr pointer ) 
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
	result->SetFlags( SlimDX::ComObjectFlags::IsExternal );
	return result;
}

#define SLIMDX_UNREFERENCED_PARAMETER(P) (P)

#ifdef NDEBUG
#	define SLIMDX_DEBUG_UNREFERENCED_PARAMETER(P)
#else
#	define SLIMDX_DEBUG_UNREFERENCED_PARAMETER(P) (P)
#endif

#include <windows.h>
#include <vcclr.h>
#include <unknwn.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#include <string>
#include <memory>
#include <vector>