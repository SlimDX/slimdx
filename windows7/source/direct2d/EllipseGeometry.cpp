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
#include "EllipseGeometry.h"

const IID IID_ID2D1EllipseGeometry = __uuidof(ID2D1EllipseGeometry);

using namespace System;

namespace SlimDX
{
namespace Direct2D
{
	EllipseGeometry::EllipseGeometry( ID2D1EllipseGeometry* pointer )
	{
		Construct( pointer );
	}
	
	EllipseGeometry::EllipseGeometry( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}
	
	EllipseGeometry^ EllipseGeometry::FromPointer( ID2D1EllipseGeometry* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		EllipseGeometry^ tableEntry = safe_cast<EllipseGeometry^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew EllipseGeometry( pointer );
	}

	EllipseGeometry^ EllipseGeometry::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		EllipseGeometry^ tableEntry = safe_cast<EllipseGeometry^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew EllipseGeometry( pointer );
	}

	SlimDX::Direct2D::Ellipse EllipseGeometry::Ellipse::get()
	{
		SlimDX::Direct2D::Ellipse result;

		InternalPointer->GetEllipse( reinterpret_cast<D2D1_ELLIPSE*>( &result ) );
		return result;
	}
}
}