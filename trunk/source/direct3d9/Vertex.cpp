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
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>

#include "Device.h"
#include "Vertex.h"

namespace SlimDX
{
namespace Direct3D9
{
	VertexDeclaration::VertexDeclaration( IDirect3DVertexDeclaration9* declaration )
	{
		if( declaration == NULL )
			throw gcnew ArgumentNullException( "declaration" );

		Construct(declaration);
	}

	VertexDeclaration::VertexDeclaration( IntPtr declaration )
	{
		Construct( declaration, NativeInterface );
	}

	VertexDeclaration::VertexDeclaration( Device^ device, array<VertexElement>^ elements )
	{
		if( elements == nullptr )
			throw gcnew ArgumentNullException( "elements" );

		pin_ptr<VertexElement> pinnedElements = &elements[0];
		IDirect3DVertexDeclaration9* decl;

		HRESULT hr = device->InternalPointer->CreateVertexDeclaration( reinterpret_cast<const D3DVERTEXELEMENT9*>( pinnedElements ), &decl );
		Direct3D9ErrorHandler::TestForFailure( hr );

		Construct(decl);
	}

	array<VertexElement>^ VertexDeclaration::Elements::get()
	{
		unsigned int count = 0;

		HRESULT hr = InternalPointer->GetDeclaration( 0, &count );
		Direct3D9ErrorHandler::TestForFailure( hr );
		if( FAILED( hr ) )
			return nullptr;

		array<VertexElement>^ decl = gcnew array<VertexElement>( count );
		pin_ptr<VertexElement> pinnedDecl = &decl[0];

		hr = InternalPointer->GetDeclaration( reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedDecl ), &count );
		Direct3D9ErrorHandler::TestForFailure( hr );
		if( FAILED( hr ) )
			return nullptr;

		return decl;
	}
}
}
