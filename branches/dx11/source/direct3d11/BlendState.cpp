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

#include <d3d11.h>
#include <d3dx11.h>

#include "Direct3D11Exception.h"

#include "BlendState.h"
#include "BlendStateDescription.h"
#include "Device.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{ 
	BlendState::BlendState( ID3D11BlendState* pointer )
	{
		Construct( pointer );
	}
	
	BlendState::BlendState( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	BlendState^ BlendState::FromDescription( SlimDX::Direct3D11::Device^ device, BlendStateDescription description )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
	
		ID3D11BlendState* state = 0;
		D3D11_BLEND_DESC nativeDescription = description.CreateNativeVersion();
		
		if( RECORD_D3D11( device->InternalPointer->CreateBlendState( &nativeDescription, &state ) ).IsFailure )
			return nullptr;
		
		return FromPointer( state );
	}

	BlendState^ BlendState::FromPointer( ID3D11BlendState* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		BlendState^ tableEntry = safe_cast<BlendState^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew BlendState( pointer );
	}

	BlendState^ BlendState::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		BlendState^ tableEntry = safe_cast<BlendState^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew BlendState( pointer );
	}

	BlendStateDescription BlendState::Description::get()
	{
		D3D11_BLEND_DESC description;
		InternalPointer->GetDesc( &description );
		return BlendStateDescription( description );
	}
}
}
