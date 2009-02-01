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

#include <d3d10.h>

#include "Direct3D10Exception.h"

#include "Debug.h"

#include "Device.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{ 
	Debug::Debug( ID3D10Debug* pointer )
	{
		Construct( pointer );
	}

	Debug::Debug( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}
	
	Debug::Debug( Device^ device )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
	
		void *result = 0;
		if( RECORD_D3D10( device->InternalPointer->QueryInterface( IID_ID3D10Debug, &result ) ).IsFailure )
			throw gcnew Direct3D10Exception( Result::Last );
		
		Construct( reinterpret_cast<ID3D10Debug*>( result ) );
	}
	
	DebugFeatureFlags Debug::FeatureFlags::get()
	{
		UINT flags = InternalPointer->GetFeatureMask();
		return static_cast<DebugFeatureFlags>( flags );
	}
	
	void Debug::FeatureFlags::set( DebugFeatureFlags value )
	{
		if( RECORD_D3D10( InternalPointer->SetFeatureMask( static_cast<UINT>( value ) ) ).IsFailure )
			throw gcnew Direct3D10Exception( Result::Last );
	}
	
	int Debug::PresentDelay::get()
	{
		return InternalPointer->GetPresentPerRenderOpDelay();
	}
	
	void Debug::PresentDelay::set( int value )
	{
		if( RECORD_D3D10( InternalPointer->SetPresentPerRenderOpDelay( value ) ).IsFailure )
			throw gcnew Direct3D10Exception( Result::Last );
	}
	
	DXGI::SwapChain^ Debug::SwapChain::get()
	{
		IDXGISwapChain* swapChain = 0;
		if( RECORD_D3D10( InternalPointer->GetSwapChain( &swapChain ) ).IsFailure )
			throw gcnew Direct3D10Exception( Result::Last );
		
		return DXGI::SwapChain::FromPointer( swapChain );
	}
	
	void Debug::SwapChain::set( DXGI::SwapChain^ value )
	{
		if( RECORD_D3D10( InternalPointer->SetSwapChain( value->InternalPointer ) ).IsFailure )
			throw gcnew Direct3D10Exception( Result::Last );
	}
	
	Result Debug::ValidatePipelineState()
	{
		return RECORD_D3D10( InternalPointer->Validate() );
	}
}
}
