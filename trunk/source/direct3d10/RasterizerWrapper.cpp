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

#include "RasterizerWrapper.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	RasterizerWrapper::RasterizerWrapper( ID3D10Device* device )
	{
		if( device == NULL )
			throw gcnew ArgumentNullException( "device" );
		m_Device = device;
	}
	
	void RasterizerWrapper::SetViewports( SlimDX::Direct3D::Viewport viewport )
	{
		D3D10_VIEWPORT nativeVP = { viewport.X, viewport.Y, viewport.Width, viewport.Height, viewport.MinZ, viewport.MaxZ };
		m_Device->RSSetViewports( 1, &nativeVP );
	}

	void RasterizerWrapper::SetViewports( ... array<SlimDX::Direct3D::Viewport>^ viewports )
	{
		D3D10_VIEWPORT nativeVPs[D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
		for( int i = 0; i < viewports->Length; ++i )
		{
			nativeVPs[ i ].TopLeftX = viewports[ i ].X;
			nativeVPs[ i ].TopLeftY = viewports[ i ].Y;
			nativeVPs[ i ].Width = viewports[ i ].Width;
			nativeVPs[ i ].Height = viewports[ i ].Height;
			nativeVPs[ i ].MinDepth = viewports[ i ].MinZ;
			nativeVPs[ i ].MaxDepth = viewports[ i ].MaxZ;
		}
		
		m_Device->RSSetViewports( viewports->Length, nativeVPs );
	}
}
}
