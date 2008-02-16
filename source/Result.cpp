/*
* Copyright (c) 2007 SlimDX Group
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

#include "Configuration.h"
#include "Result.h"

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
	
	String^ Result::Description::get()
	{
		if( m_Description == nullptr )
		{
			wchar_t * message = 0;
			
			try
			{
				int flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM;
				int lang = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
				if( FormatMessage( flags, 0, m_Code, lang, reinterpret_cast<wchar_t*>( &message ), 0, 0 ) )
					m_Description = gcnew String( message );
				else
					m_Description = String::Format( "HRESULT: {0}", m_Code );
			}
			finally
			{
				LocalFree( message );
			}
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
	
	Result Result::Record( int hr )
	{
		m_Last = Result( hr );

#ifdef _DEBUG
		if( Configuration::HasResultWatch( m_Last ) )
			System::Diagnostics::Debugger::Break();
#endif
		
		return Result( hr );
	}
	
	Result Result::Last::get()
	{
		return m_Last;
	}
	
	bool Result::operator==( Result left, Result right )
	{
		return left.Code == right.Code;
	}
	
	bool Result::operator!=( Result left, Result right )
	{
		return !(left == right);
	}
}