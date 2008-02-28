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
#include <dxerr.h>

#include "Device.h"
#include "Vertex.h"

#include "Direct3D9Exception.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D9
{
	VertexDeclaration::VertexDeclaration( IDirect3DVertexDeclaration9* pointer )
	{
		Construct( pointer );
	}

	VertexDeclaration::VertexDeclaration( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	VertexDeclaration::VertexDeclaration( Device^ device, array<VertexElement>^ elements )
	{
		if( elements == nullptr )
			throw gcnew ArgumentNullException( "elements" );

		pin_ptr<VertexElement> pinnedElements = &elements[0];
		IDirect3DVertexDeclaration9* decl;

		HRESULT hr = device->InternalPointer->CreateVertexDeclaration( reinterpret_cast<const D3DVERTEXELEMENT9*>( pinnedElements ), &decl );
		
		if( RECORD_D3D9(hr).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(decl);
	}

	VertexDeclaration^ VertexDeclaration::FromPointer( IDirect3DVertexDeclaration9* pointer )
	{
		VertexDeclaration^ tableEntry = safe_cast<VertexDeclaration^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew VertexDeclaration( pointer );
	}

	VertexDeclaration^ VertexDeclaration::FromPointer( IntPtr pointer )
	{
		VertexDeclaration^ tableEntry = safe_cast<VertexDeclaration^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew VertexDeclaration( pointer );
	}

	array<VertexElement>^ VertexDeclaration::Elements::get()
	{
		unsigned int count = 0;

		HRESULT hr = InternalPointer->GetDeclaration( 0, &count );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		array<VertexElement>^ decl = gcnew array<VertexElement>( count );
		pin_ptr<VertexElement> pinnedDecl = &decl[0];

		hr = InternalPointer->GetDeclaration( reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedDecl ), &count );
		
		if( RECORD_D3D9(hr).IsFailure )
			return nullptr;

		return decl;
	}

	bool VertexElement::operator == ( VertexElement left, VertexElement right )
	{
		return VertexElement::Equals( left, right );
	}

	bool VertexElement::operator != ( VertexElement left, VertexElement right )
	{
		return !VertexElement::Equals( left, right );
	}

	int VertexElement::GetHashCode()
	{
		return Stream.GetHashCode() + Offset.GetHashCode() + Type.GetHashCode()
			 + Method.GetHashCode() + Usage.GetHashCode() + UsageIndex.GetHashCode();
	}

	bool VertexElement::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<VertexElement>( value ) );
	}

	bool VertexElement::Equals( VertexElement value )
	{
		return ( Stream == value.Stream && Offset == value.Offset && Type == value.Type
			 && Method == value.Method && Usage == value.Usage && UsageIndex == value.UsageIndex );
	}

	bool VertexElement::Equals( VertexElement% value1, VertexElement% value2 )
	{
		return ( value1.Stream == value2.Stream && value1.Offset == value2.Offset && value1.Type == value2.Type
			 && value1.Method == value2.Method && value1.Usage == value2.Usage && value1.UsageIndex == value2.UsageIndex );
	}
}
}
