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
#include <d3d9.h>
#include <d3dx9.h>

#include "../Utilities.h"
#include "Performance.h"
#include <vcclr.h>

using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace Direct3D
{
	int Performance::BeginEvent( int color, String^ name )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( name );
		return D3DPERF_BeginEvent( color, pinnedName );
	}

	int Performance::BeginEvent( System::Drawing::Color color, String^ name )
	{
		return BeginEvent( color.ToArgb(), name );
	}

	int Performance::EndEvent()
	{
		return D3DPERF_EndEvent();
	}

	bool Performance::GetStatus()
	{
		return D3DPERF_GetStatus() > 0;
	}

	bool Performance::QueryRepeatFrame()
	{
		return D3DPERF_QueryRepeatFrame() > 0;
	}

	void Performance::SetMarker( int color, String^ name )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( name );
		D3DPERF_SetMarker( color, pinnedName );
	}

	void Performance::SetMarker( System::Drawing::Color color, String^ name )
	{
		SetMarker( color.ToArgb(), name );
	}

	void Performance::SetOptions( PerformanceOptions options )
	{
		D3DPERF_SetOptions( (DWORD) options );
	}

	void Performance::SetRegion( int color, String^ name )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( name );
		D3DPERF_SetRegion( color, pinnedName );
	}

	void Performance::SetRegion( System::Drawing::Color color, String^ name )
	{
		return SetRegion( color.ToArgb(), name );
	}
}
}
