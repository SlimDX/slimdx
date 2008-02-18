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

#include "ComObject.h"
#include "Configuration.h"

using namespace System;

namespace SlimDX
{
	ComObject::ComObject()
	{
		if( Configuration::EnableObjectTracking )
			ObjectTracker::Add( this );
	}

	ComObject::~ComObject()
	{
	}

	bool ComObject::Disposed::get()
	{
		return m_Unknown == 0;
	}

	IntPtr ComObject::ComPointer::get()
	{
		return IntPtr( m_Unknown );
	}

	IUnknown* ComObject::UnknownPointer::get()
	{
		return m_Unknown;
	}
	
	void ComObject::Construct( IUnknown* pointer )
	{
		if( pointer == 0 )
			throw gcnew ArgumentNullException( "pointer" );

		m_Unknown = pointer;
	}

	void ComObject::Construct( IntPtr pointer, Guid guid )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		void* result = 0;
		IUnknown* unknown = static_cast<IUnknown*>( pointer.ToPointer() );
		HRESULT hr = unknown->QueryInterface( Utilities::ConvertManagedGuid( guid ), &result );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		Construct( unknown );
	}

	void ComObject::Destruct()
	{
		if( m_Unknown != 0 )
			m_Unknown->Release();

		if( Configuration::EnableObjectTracking )
			ObjectTracker::Remove( this );
	}

	void ComObject::DisposeHandler( Object^ sender, EventArgs^ e )
	{
		delete this;
	};
}