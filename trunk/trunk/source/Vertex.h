#pragma once

using namespace System;

#include "Exceptions.h"
#include "Utils.h"

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

		public ref class VertexDeclaration sealed
		{
		private:
			IDirect3DVertexDeclaration9* m_Decl;
			bool m_Disposed;

		internal:
			property IDirect3DVertexDeclaration9* InternalPointer
			{
				IDirect3DVertexDeclaration9* get() { return m_Decl; }
			}

		public:
			VertexDeclaration( Device^ device, array<VertexElement>^ elements );
			~VertexDeclaration();
			!VertexDeclaration();
		};
	}
}
