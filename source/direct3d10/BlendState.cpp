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

#include "GraphicsException.h"

#include "BlendState.h"
#include "Device.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	BlendState::BlendState( ID3D10BlendState* state ) : DirectXObject( state )
	{
		if( state == NULL )
			throw gcnew ArgumentNullException( "state" );
		
		D3D10_BLEND_DESC desc;
		state->GetDesc( &desc );
		m_Description = gcnew BlendStateDescription( desc );
	}
	
	BlendState::BlendState( IntPtr state )
	{
		if( state == IntPtr::Zero )
			throw gcnew ArgumentNullException( "state" );

		void* pointer;
		IUnknown* unknown = static_cast<IUnknown*>( state.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_ID3D10BlendState, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<ID3D10BlendState*>( pointer );

		D3D10_BLEND_DESC desc;
		m_Pointer->GetDesc( &desc );
		m_Description = gcnew BlendStateDescription( desc );
	}

	BlendState::BlendState( Device^ device, BlendStateDescription^ description )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
		if( description == nullptr )
			throw gcnew ArgumentNullException( "description" );
	
		D3D10_BLEND_DESC desc;
		m_Description = description;
		m_Description->FillNativeObject( desc );
		
		ID3D10BlendState* state;
		HRESULT hr = device->DevicePointer->CreateBlendState( &desc, &state );
		GraphicsException::CheckHResult( hr );
		
		m_Pointer = state;
	}
	
	BlendStateDescription^ BlendState::CloneDescription()
	{
		D3D10_BLEND_DESC desc;
		m_Pointer->GetDesc( &desc );
		return gcnew BlendStateDescription( desc );
	}
}
}
