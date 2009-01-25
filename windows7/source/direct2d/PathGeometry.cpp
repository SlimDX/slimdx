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

#define DEFINE_ENUM_FLAG_OPERATORS(x)

#include <d2d1.h>
#include <d2d1helper.h>

#include "Direct2DException.h"

#include "RenderTarget.h"
#include "PathGeometry.h"

const IID IID_ID2D1PathGeometry = __uuidof(ID2D1PathGeometry);

using namespace System;

namespace SlimDX
{
namespace Direct2D
{
	PathGeometry::PathGeometry( ID2D1PathGeometry* pointer )
	{
		Construct( pointer );
	}
	
	PathGeometry::PathGeometry( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}
	
	PathGeometry^ PathGeometry::FromPointer( ID2D1PathGeometry* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		PathGeometry^ tableEntry = safe_cast<PathGeometry^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew PathGeometry( pointer );
	}

	PathGeometry^ PathGeometry::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		PathGeometry^ tableEntry = safe_cast<PathGeometry^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew PathGeometry( pointer );
	}

	int PathGeometry::FigureCount::get()
	{
		UINT32 count;

		InternalPointer->GetFigureCount( &count );
		return count;
	}

	int PathGeometry::SegmentCount::get()
	{
		UINT32 count;

		InternalPointer->GetSegmentCount( &count );
		return count;
	}

	GeometrySink^ PathGeometry::Open()
	{
		ID2D1GeometrySink *sink = NULL;

		HRESULT hr = InternalPointer->Open( &sink );
		if( RECORD_D2D( hr ).IsFailure )
			return nullptr;

		return GeometrySink::FromPointer( sink );
	}

	Result PathGeometry::Stream( GeometrySink^ geometrySink )
	{
		HRESULT hr = InternalPointer->Stream( geometrySink->InternalPointer );
		return RECORD_D2D( hr );
	}
}
}