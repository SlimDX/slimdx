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
#pragma once

#include "../ComObject.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		public value class VertexElement : System::IEquatable<VertexElement>
		{
		private:
			static VertexElement()
			{
				VertexDeclarationEnd = VertexElement( 255, 0, DeclarationType::Unused, 
					DeclarationMethod::Default, DeclarationUsage::Position, 0 );
			}

		public:
			property short Stream;
            property short Offset;
            property DeclarationType Type;
            property DeclarationMethod Method;
            property DeclarationUsage Usage;
            property System::Byte UsageIndex;

			static initonly VertexElement VertexDeclarationEnd;

			VertexElement( short stream, short offset, DeclarationType declarationType, DeclarationMethod declarationMethod, DeclarationUsage declarationUsage, System::Byte usageIndex )
			{
				Stream = stream;
				Offset = offset;
				Type = declarationType;
				Method = declarationMethod;
				Usage = declarationUsage;
				UsageIndex = usageIndex;
			}

			static bool operator == ( VertexElement left, VertexElement right );
			static bool operator != ( VertexElement left, VertexElement right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( VertexElement other );
			static bool Equals( VertexElement% value1, VertexElement% value2 );
		};

		ref class Device;

		public ref class VertexDeclaration : public ComObject
		{
			COMOBJECT(IDirect3DVertexDeclaration9);

		internal:
			VertexDeclaration( IDirect3DVertexDeclaration9* declaration );

		public:
			VertexDeclaration( System::IntPtr declaration );
			VertexDeclaration( Device^ device, array<VertexElement>^ elements );
			~VertexDeclaration() { Destruct(); }

			property array<VertexElement>^ Elements
			{
				array<VertexElement>^ get();
			}
		};
	}
}
