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

#define DEFINE_ENUM_FLAG_OPERATORS(x)

#include <d2d1.h>
#include <d2d1helper.h>

#include "Direct2DException.h"

#include "RenderTarget.h"
#include "SolidColorBrush.h"

const IID IID_ID2D1SolidColorBrush = __uuidof(ID2D1SolidColorBrush);

using namespace System;

namespace SlimDX
{
namespace Direct2D
{
	SolidColorBrush::SolidColorBrush( ID2D1SolidColorBrush* pointer )
	{
		Construct( pointer );
	}
	
	SolidColorBrush::SolidColorBrush( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}
	
	SolidColorBrush^ SolidColorBrush::FromPointer( ID2D1SolidColorBrush* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		SolidColorBrush^ tableEntry = safe_cast<SolidColorBrush^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew SolidColorBrush( pointer );
	}

	SolidColorBrush^ SolidColorBrush::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		SolidColorBrush^ tableEntry = safe_cast<SolidColorBrush^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew SolidColorBrush( pointer );
	}

	SolidColorBrush::SolidColorBrush( RenderTarget^ renderTarget, Color4 color )
	{
		ID2D1SolidColorBrush *brush = NULL;

		HRESULT hr = renderTarget->InternalPointer->CreateSolidColorBrush( reinterpret_cast<D2D1_COLOR_F*>( &color ),NULL, &brush );

		if( RECORD_D2D( hr ).IsFailure )
			throw gcnew Direct2DException( Result::Last );

		Construct( brush );
	}

	SolidColorBrush::SolidColorBrush( RenderTarget^ renderTarget, Color4 color, BrushProperties properties )
	{
		ID2D1SolidColorBrush *brush = NULL;

		HRESULT hr = renderTarget->InternalPointer->CreateSolidColorBrush( reinterpret_cast<D2D1_COLOR_F*>( &color ),
			reinterpret_cast<D2D1_BRUSH_PROPERTIES*>( &properties ), &brush );

		if( RECORD_D2D( hr ).IsFailure )
			throw gcnew Direct2DException( Result::Last );

		Construct( brush );
	}
}
}