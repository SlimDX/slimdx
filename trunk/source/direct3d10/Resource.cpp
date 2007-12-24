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

#include "Resource.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	Resource::Resource()
	{
	}
	
	Resource::Resource( ID3D10Resource* resource )
	{
		m_Pointer = resource;
	}

	Resource::Resource( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		void* result;
		IUnknown* unknown = static_cast<IUnknown*>( pointer.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_ID3D10Resource, &result );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<ID3D10Resource*>( result );
	}
	
	ResourcePriority Resource::EvictionPriority::get()
	{
		return static_cast<ResourcePriority>( m_Pointer->GetEvictionPriority() );
	}
	
	void Resource::EvictionPriority::set(ResourcePriority value)
	{
		m_Pointer->SetEvictionPriority( static_cast<UINT>( value ) );
	}
	
	ResourceDimension Resource::Dimension::get()
	{
		D3D10_RESOURCE_DIMENSION type;
		m_Pointer->GetType(&type);
		return static_cast<ResourceDimension>( type );
	}
}
}
