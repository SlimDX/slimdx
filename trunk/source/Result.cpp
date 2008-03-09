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

#include <windows.h>
#include <dxerr.h>

#include "Configuration.h"
#include "Result.h"
#include "SlimDXException.h"

using namespace System;
using namespace System::Globalization;

namespace SlimDX
{
	Result::Result( int hr )
	: m_Code( hr )
	{
	}
	
	int Result::Code::get()
	{
		return m_Code;
	}
	
	String^ Result::Name::get()
	{
		if( m_Name == nullptr )
		{
			m_Name = gcnew String( DXGetErrorString( m_Code ) );
		}

		return m_Name;
	}

	String^ Result::Description::get()
	{
		if( m_Description == nullptr )
		{
			m_Description = gcnew String( DXGetErrorDescription( m_Code ) );
		}
		
		return m_Description;
	}
	
	bool Result::IsSuccess::get()
	{
		return SUCCEEDED( m_Code );
	}
	
	bool Result::IsFailure::get()
	{
		return FAILED( m_Code );
	}
	
	generic< typename T >
	void Result::Throw()
	{
		throw safe_cast<SlimDXException^>( Activator::CreateInstance( T::typeid, m_Last ) );
	}

	generic< typename T >
	Result Result::Record( int hr, bool failed )
	{
		m_Last = Result( hr );

		ResultWatchFlags flags;
		if( Configuration::TryGetResultWatch( m_Last, flags ) )
		{
			if( flags == ResultWatchFlags::AlwaysIgnore )
				return Result( hr );
#ifdef _DEBUG
			if( static_cast<int>( flags & ResultWatchFlags::Assert ) != 0 )
				System::Diagnostics::Debugger::Break();
#endif

			if( static_cast<int>( flags & ResultWatchFlags::Throw ) != 0 )
				Throw<T>();
		}

		if( failed && Configuration::ThrowOnError )
			Throw<T>();

		return Result( hr );
	}

	generic< typename T >
	Result Result::Fail( int hr )
	{
		return Record<T>( hr, true );
	}

	generic< typename T >
	Result Result::Record( int hr )
	{
		return Record<T>( hr, hr < 0 );
	}
	
	Result Result::Last::get()
	{
		return m_Last;
	}
	
	bool Result::operator == ( Result left, Result right )
	{
		return Result::Equals( left, right );
	}
	
	bool Result::operator != ( Result left, Result right )
	{
		return !Result::Equals( left, right );
	}

	String^ Result::ToString()
	{
		return String::Format( CultureInfo::CurrentCulture, "{0}: {1} ({2})", Name, Description, Code );
	}

	int Result::GetHashCode()
	{
		return m_Code.GetHashCode();
	}

	bool Result::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( safe_cast<Result>( value ) );
	}

	bool Result::Equals( Result value )
	{
		return ( Code == value.Code );
	}

	bool Result::Equals( Result% value1, Result% value2 )
	{
		return ( value1.Code == value2.Code );
	}
}