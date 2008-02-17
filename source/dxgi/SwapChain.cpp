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

#include <d3d10.h>
#include <d3dx10.h>

#include "DXGIException.h"

#include "Factory.h"
#include "SwapChain.h"
#include "SwapChainDescription.h"
#include "FrameStatistics.h"
#include "ModeDescription.h"

namespace SlimDX
{
namespace DXGI
{ 	
	SwapChain::SwapChain( IDXGISwapChain* pointer )
	{
		Construct( pointer );
	}
	
	SwapChain::SwapChain( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}
	
	SwapChain::SwapChain( Factory^ factory, ComObject^ device, SwapChainDescription description )
	{
		if( factory == nullptr )
			throw gcnew ArgumentNullException( "factory" );
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
		
		IDXGISwapChain* swapChain = 0;
		DXGI_SWAP_CHAIN_DESC nativeDescription = description.CreateNativeVersion();
		Result::Record( factory->InternalPointer->CreateSwapChain( device->UnknownPointer, &nativeDescription, &swapChain ) );
		if( Result::Last.IsFailure )
			throw gcnew DXGIException( Result::Last );
		
		Construct( swapChain );
	}
	
	DXGI::FrameStatistics SwapChain::FrameStatistics::get()
	{
		DXGI_FRAME_STATISTICS stats;
		Result::Record( InternalPointer->GetFrameStatistics( &stats ) );
		if( Result::Last.IsSuccess )
			return DXGI::FrameStatistics( stats );
		
		throw gcnew DXGIException( Result::Last );
	}
	
	generic< class T > where T : ComObject, ref class
	T SwapChain::GetBuffer( int index )
	{
		IUnknown* unknown = 0;
		GUID guid = Utilities::GetNativeGuidForType( T::typeid );
		Result::Record( InternalPointer->GetBuffer( index, guid, reinterpret_cast<void**>( &unknown ) ) );
		if( Result::Last.IsFailure )
			return T();
		return safe_cast<T>( Activator::CreateInstance( T::typeid, IntPtr( unknown ) ) );
	}

	Result SwapChain::ResizeBuffers( int count, int width, int height, SlimDX::DXGI::Format format, SwapChainFlags flags )
	{
		return Result::Record( InternalPointer->ResizeBuffers( count, width, height, static_cast<DXGI_FORMAT>( format ), static_cast<UINT>( flags ) ) );
	}
	
	Result SwapChain::ResizeTarget( ModeDescription description )
	{
		return Result::Record( InternalPointer->ResizeTarget( reinterpret_cast<DXGI_MODE_DESC*>( &description ) ) );
	}

	Result SwapChain::Present( int syncInterval, PresentFlags flags )
	{
		return Result::Record( InternalPointer->Present( syncInterval, static_cast<UINT>( flags ) ) );
	}
}
}
