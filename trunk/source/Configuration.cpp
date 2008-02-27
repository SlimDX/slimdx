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

#include "Configuration.h"

namespace SlimDX
{
	static Configuration::Configuration()
	{
#ifdef _DEBUG
		m_EnableObjectTracking = true;
#else
		m_EnableObjectTracking = false;
#endif	

		m_AlwaysThrowOnError = true;
		m_Watches = gcnew System::Collections::Generic::Dictionary<Result,ResultWatchFlags>();
	}
	
	Configuration::Configuration()
	{
	}
	
	bool Configuration::EnableObjectTracking::get()
	{
		return m_EnableObjectTracking;
	}
	
	void Configuration::EnableObjectTracking::set( bool value )
	{
		m_EnableObjectTracking = value;
	}
	
	bool Configuration::AlwaysThrowOnError::get()
	{
		return m_AlwaysThrowOnError;
	}

	void Configuration::AlwaysThrowOnError::set( bool value )
	{
		m_AlwaysThrowOnError = value;
	}

	bool Configuration::TryGetResultWatch( Result result, ResultWatchFlags% flags )
	{
		return m_Watches->TryGetValue( result, flags );
	}
	
	void Configuration::AddResultWatch( Result result, ResultWatchFlags flags )
	{
		if( m_Watches->ContainsKey( result ) )
			m_Watches[ result ] = flags;
		else
			m_Watches->Add( result, flags );
	}
	
	void Configuration::ClearResultWatch( Result result )
	{
		if( m_Watches->ContainsKey( result ) )
			m_Watches->Remove( result );
	}
	
	void Configuration::ClearResultWatches()
	{
		m_Watches->Clear();
	}
}