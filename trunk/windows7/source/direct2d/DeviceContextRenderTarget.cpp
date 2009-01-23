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

#include "RenderTargetProperties.h"
#include "Factory.h"
#include "RenderTarget.h"
#include "DeviceContextRenderTarget.h"

const IID IID_ID2D1DCRenderTarget = __uuidof(ID2D1DCRenderTarget);

using namespace System;

namespace SlimDX
{
namespace Direct2D
{
	DeviceContextRenderTarget::DeviceContextRenderTarget( ID2D1DCRenderTarget* pointer )
	{
		Construct( pointer );
	}
	
	DeviceContextRenderTarget::DeviceContextRenderTarget( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}
	
	DeviceContextRenderTarget^ DeviceContextRenderTarget::FromPointer( ID2D1DCRenderTarget* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		DeviceContextRenderTarget^ tableEntry = safe_cast<DeviceContextRenderTarget^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew DeviceContextRenderTarget( pointer );
	}

	DeviceContextRenderTarget^ DeviceContextRenderTarget::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		DeviceContextRenderTarget^ tableEntry = safe_cast<DeviceContextRenderTarget^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew DeviceContextRenderTarget( pointer );
	}

	DeviceContextRenderTarget::DeviceContextRenderTarget( SlimDX::Direct2D::Factory^ factory, RenderTargetProperties renderTargetProperties )
	{
		ID2D1DCRenderTarget *renderTarget = NULL;

		HRESULT hr = factory->InternalPointer->CreateDCRenderTarget( reinterpret_cast<D2D1_RENDER_TARGET_PROPERTIES*>( &renderTargetProperties ), &renderTarget );

		if( RECORD_D2D( hr ).IsFailure )
			throw gcnew Direct2DException( Result::Last );

		Construct( renderTarget );
	}
}
}