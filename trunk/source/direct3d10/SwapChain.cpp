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

#include "SwapChain.h"
#include "GraphicsException.h"

#include "Device.h"
#include "Texture2D.h"
#include "ModeDescription.h"
#include "SwapChainDescription.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	SwapChain::SwapChain( Device^ device, SwapChainDescription description )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
			
		IDXGISwapChain *swapChain = 0;
		HRESULT hr = device->FactoryPointer->CreateSwapChain( device->DevicePointer, reinterpret_cast<DXGI_SWAP_CHAIN_DESC*>( &description ), &swapChain );
		GraphicsException::CheckHResult( hr );
		
		m_Pointer = swapChain;
	}

	SwapChain::SwapChain( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		void* result;
		IUnknown* unknown = static_cast<IUnknown*>( pointer.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_IDXGISwapChain, &result );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<IDXGISwapChain*>( result );
	}

	Texture2D^ SwapChain::GetBuffer( int index )
	{
		ID3D10Texture2D *texture;
		HRESULT hr = m_Pointer->GetBuffer( index, __uuidof( ID3D10Texture2D ), reinterpret_cast<void**>( &texture ) );
		GraphicsException::CheckHResult( hr );

		return gcnew Texture2D( texture );
	}
	
	void SwapChain::ResizeBuffers( int count, int width, int height, Format format, SwapChainFlags flags )
	{
		HRESULT hr = m_Pointer->ResizeBuffers( count, width, height, static_cast<DXGI_FORMAT>( format ), static_cast<UINT>( flags ) );
		GraphicsException::CheckHResult( hr );
	}
	
	void SwapChain::ResizeTarget( ModeDescription description )
	{
		HRESULT hr = m_Pointer->ResizeTarget( reinterpret_cast<DXGI_MODE_DESC*>( &description ) );
		GraphicsException::CheckHResult( hr );
	}
	
	PresentResult SwapChain::Present( int syncInterval, PresentFlags flags )
	{
		HRESULT hr = m_Pointer->Present( syncInterval, static_cast<UINT>( flags ) );
		if( hr == S_OK )
			return PresentResult::Okay;
		else if( hr == DXGI_STATUS_OCCLUDED )
			return PresentResult::Occluded;
		
		GraphicsException::CheckHResult( hr );
		return PresentResult::Failed;
	}
}
}
