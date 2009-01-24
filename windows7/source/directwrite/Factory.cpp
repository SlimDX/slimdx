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

#include <dwrite.h>

#include "DirectWriteException.h"

#include "Factory.h"

const IID IID_IDWriteFactory = __uuidof(IDWriteFactory);

using namespace System;

namespace SlimDX
{
namespace DirectWrite
{
	Factory::Factory( IDWriteFactory* pointer )
	{
		Construct( pointer );
	}

	Factory::Factory( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	Factory^ Factory::FromPointer( IDWriteFactory* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		Factory^ tableEntry = safe_cast<Factory^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew Factory( pointer );
	}

	Factory^ Factory::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		Factory^ tableEntry = safe_cast<Factory^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew Factory( pointer );
	}

	Factory::Factory()
	{
		Init( FactoryType::Shared );
	}

	Factory::Factory( FactoryType factoryType )
	{
		Init( factoryType );
	}

	void Factory::Init( FactoryType factoryType )
	{
		IDWriteFactory *factory = NULL;

		if( RECORD_DW( DWriteCreateFactory( static_cast<DWRITE_FACTORY_TYPE>( factoryType ), IID_IDWriteFactory, reinterpret_cast<IUnknown**>( &factory ) ) ).IsFailure )
			throw gcnew DirectWriteException( Result::Last );

		Construct( factory );
	}
}
}