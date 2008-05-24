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

#include "ThreadPumpStatus.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{ 	
	ThreadPumpStatus::ThreadPumpStatus( UInt32 ioCount, UInt32 processCount, UInt32 deviceCount )
	{
		m_IoQueue = ioCount;
		m_ProcessQueue = processCount; 
		m_DeviceQueue = deviceCount;
	}

	UInt32 ThreadPumpStatus::IoQueueCount::get()
	{
		return m_IoQueue;
	}
	
	UInt32 ThreadPumpStatus::ProcessQueueCount::get()
	{
		return m_ProcessQueue;
	}
	
	UInt32 ThreadPumpStatus::DeviceQueueCount::get()
	{
		return m_DeviceQueue;
	}

	bool ThreadPumpStatus::operator == ( ThreadPumpStatus left, ThreadPumpStatus right )
	{
		return ThreadPumpStatus::Equals( left, right );
	}

	bool ThreadPumpStatus::operator != ( ThreadPumpStatus left, ThreadPumpStatus right )
	{
		return !ThreadPumpStatus::Equals( left, right );
	}

	int ThreadPumpStatus::GetHashCode()
	{
		return m_IoQueue.GetHashCode() + m_ProcessQueue.GetHashCode() + m_ProcessQueue.GetHashCode();
	}

	bool ThreadPumpStatus::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( safe_cast<ThreadPumpStatus>( value ) );
	}

	bool ThreadPumpStatus::Equals( ThreadPumpStatus value )
	{
		return ( m_IoQueue == value.m_IoQueue && m_ProcessQueue == value.m_ProcessQueue && m_DeviceQueue == value.m_DeviceQueue );
	}

	bool ThreadPumpStatus::Equals( ThreadPumpStatus% value1, ThreadPumpStatus% value2 )
	{
		return ( value1.m_IoQueue == value2.m_IoQueue && value1.m_ProcessQueue == value2.m_ProcessQueue && value1.m_DeviceQueue == value2.m_DeviceQueue );
	}
}
}
