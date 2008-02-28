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

#include <d3d9.h>
#include <d3dx9.h>

//#include "Direct3D9ErrorHandler.h"
#include "Direct3D9Exception.h"

#include "Device.h"
#include "StateBlock.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D9
{
	StateBlock::StateBlock( IDirect3DStateBlock9* pointer )
	{
		Construct( pointer );
	}

	StateBlock::StateBlock( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	StateBlock::StateBlock( Device^ device, StateBlockType type )
	{
		IDirect3DStateBlock9* stateBlock;

		HRESULT hr = device->InternalPointer->CreateStateBlock( static_cast<D3DSTATEBLOCKTYPE>( type ), &stateBlock );
		
		if( RECORD_D3D9( hr ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(stateBlock);
	}

	StateBlock^ StateBlock::FromPointer( IDirect3DStateBlock9* pointer )
	{
		StateBlock^ tableEntry = safe_cast<StateBlock^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew StateBlock( pointer );
	}

	StateBlock^ StateBlock::FromPointer( IntPtr pointer )
	{
		StateBlock^ tableEntry = safe_cast<StateBlock^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew StateBlock( pointer );
	}


	Result StateBlock::Apply()
	{
		HRESULT hr = InternalPointer->Apply();
		return RECORD_D3D9( hr );
	}

	Result StateBlock::Capture()
	{
		HRESULT hr = InternalPointer->Apply();
		return RECORD_D3D9( hr );
	}

	Device^ StateBlock::GetDevice()
	{
		IDirect3DDevice9* device;
		HRESULT hr = InternalPointer->GetDevice( &device );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return Device::FromPointer( device );
	}
}
}