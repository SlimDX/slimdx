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

#include <d3d10.h>

#include "CounterCapabilities.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	CounterCapabilities::CounterCapabilities( const D3D10_COUNTER_INFO& native )
	{
		m_LastDeviceDependentCounter = static_cast<int>( native.LastDeviceDependentCounter );
		m_NumSimultaneousCounters = native.NumSimultaneousCounters;
		m_NumDetectableParallelUnits = native.NumDetectableParallelUnits;
	}
	
	int CounterCapabilities::LastDeviceDependantCounter::get()
	{
		return m_LastDeviceDependentCounter;
	}
	
	int CounterCapabilities::MaximumSimultaneousCounters::get()
	{
		return m_NumSimultaneousCounters;
	}
	
	int CounterCapabilities::MaximumParallelUnits::get()
	{
		return m_NumDetectableParallelUnits;
	}
}
}
