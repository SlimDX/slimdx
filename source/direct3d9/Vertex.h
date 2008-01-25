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

#include "../ComObject.h"
#include "Direct3D9ErrorHandler.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		public value class VertexElement
		{
		private:
			static VertexElement()
			{
				VertexDeclarationEnd = VertexElement( 255, 0, DeclarationType::Unused, 
					DeclarationMethod::Default, DeclarationUsage::Position, 0 );
			}
			
			short stream;
            short offset;
            DeclarationType type;
            DeclarationMethod method;
            DeclarationUsage usage;
            Byte usageIndex;

		public:
			property short Stream
            {
                short get() { return stream; }
                void set( short value ) { stream = value; }
            }

            property short Offset
            {
                short get() { return offset; }
                void set( short value ) { offset = value; }
            }

            property DeclarationType Type
            {
                DeclarationType get() { return type; }
                void set( DeclarationType value ) { type = value; }
            }

            property DeclarationMethod Method
            {
                DeclarationMethod get() { return method; }
                void set( DeclarationMethod value ) { method = value; }
            }

            property DeclarationUsage Usage
            {
                DeclarationUsage get() { return usage; }
                void set( DeclarationUsage value ) { usage = value; }
            }

            property Byte UsageIndex
            {
                Byte get() { return usageIndex; }
                void set( Byte value ) { usageIndex = value; }
            }

			static initonly VertexElement VertexDeclarationEnd;

			VertexElement( short stream, short offset, DeclarationType declType, 
				DeclarationMethod declMethod, DeclarationUsage declUsage, Byte usageIndex )
				: stream( stream ), offset( offset ), type( declType ),
				method( declMethod ), usage( declUsage ), usageIndex( usageIndex )
			{
			}
		};

		ref class Device;

		public ref class VertexDeclaration : public ComObject
		{
			COMOBJECT(IDirect3DVertexDeclaration9);

		internal:
			VertexDeclaration( IDirect3DVertexDeclaration9* decl );

		public:
			VertexDeclaration( IntPtr decl );
			VertexDeclaration( Device^ device, array<VertexElement>^ elements );
			~VertexDeclaration() { Destruct(); }

			property array<VertexElement>^ Elements
			{
				array<VertexElement>^ get();
			}
		};
	}
}
