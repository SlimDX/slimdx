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
#pragma once

using namespace System;

#include "../DirectXObject.h"
#include "GraphicsException.h"

namespace SlimDX
{
	namespace Direct3D
	{
		public value class VertexElement
		{
		public:
			short Stream;
			short Offset;
			DeclarationType Type;
			DeclarationMethod Method;
			DeclarationUsage Usage;
			Byte UsageIndex;

			static initonly VertexElement VertexDeclarationEnd;

			static VertexElement()
			{
				VertexDeclarationEnd = VertexElement( 255, 0, DeclarationType::Unused, 
					DeclarationMethod::Default, DeclarationUsage::Position, 0 );
			}

			VertexElement( short stream, short offset, DeclarationType declType, 
				DeclarationMethod declMethod, DeclarationUsage declUsage, Byte usageIndex )
				: Stream( stream ), Offset( offset ), Type( declType ),
				Method( declMethod ), Usage( declUsage ), UsageIndex( usageIndex )
			{
			}
		};

		ref class Device;

		public ref class VertexDeclaration sealed : public DirectXObject
		{
		private:
			IDirect3DVertexDeclaration9* m_Decl;

		internal:
			property IDirect3DVertexDeclaration9* InternalPointer
			{
				IDirect3DVertexDeclaration9* get() { return m_Decl; }
			}

			property IUnknown* ComPointer
			{
				virtual IUnknown* get() override { return m_Decl; }
				virtual void set( IUnknown* value ) override { m_Decl = (IDirect3DVertexDeclaration9*) value; }
			}

		public:
			VertexDeclaration( Device^ device, array<VertexElement>^ elements );
		};
	}
}
