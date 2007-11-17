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

#include "Enums.h"
#include "Vertex.h"
#include "D3DX.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		int D3DX::GetDeclarationVertexSize( array<VertexElement>^ elements, int stream )
		{
			if( elements == nullptr )
				throw gcnew ArgumentNullException( "elements" );

			pin_ptr<VertexElement> pinnedElements = &elements[0];
			return static_cast<int>( D3DXGetDeclVertexSize( reinterpret_cast<const D3DVERTEXELEMENT9*>( pinnedElements ), stream ) );
		}

		int D3DX::GetFVFVertexSize( VertexFormat fvf )
		{
			return static_cast<int>( D3DXGetFVFVertexSize( static_cast<DWORD>( fvf ) ) );
		}

		Format D3DX::MakeFourCC( Byte c1, Byte c2, Byte c3, Byte c4 )
		{
			int fourcc = (c4 << 24) | (c3 << 16) | (c2 << 8) | (c1);
			return static_cast<Format>( fourcc );
		}

		bool D3DX::DebugMute( bool mute )
		{
			return D3DXDebugMute( mute ) > 0;
		}
	}
}