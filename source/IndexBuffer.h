#pragma once

#include "Resource.h"
#include "GraphicsStream.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D
	{
		public ref class IndexBuffer sealed : public Resource
		{
		private:
			IDirect3DIndexBuffer9* m_Buffer;
			bool m_Disposed;

		internal:
			property IDirect3DIndexBuffer9* InternalPointer
			{
				IDirect3DIndexBuffer9* get() { return m_Buffer; }
			}

			property IDirect3DResource9* ResourcePointer
			{
				virtual IDirect3DResource9* get() override { return m_Buffer; }
			}

		public:
			IndexBuffer( IDirect3DIndexBuffer9* buffer );
			IndexBuffer( Device^ device, int sizeBytes, Usage usage, Pool pool, bool sixteenBit );
			~IndexBuffer();
			!IndexBuffer();

			generic<typename T> where T : value class
			GraphicsStream<T>^ Lock( int offset, int size, LockFlags flags );
			generic<typename T> where T : value class
			GraphicsStream<T>^ Lock( int offset, LockFlags flags )	{ return Lock<T>( offset, 0, flags ); }
			void Unlock();
		};
	}
}
