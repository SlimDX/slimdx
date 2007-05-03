#pragma once

#include "Resource.h"
#include "GraphicsStream.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D
	{
		public ref class BaseTexture abstract : public Resource
		{
		};

		public ref class Texture : public BaseTexture
		{
		private:
			IDirect3DTexture9* m_Texture;
			bool m_Disposed;

		internal:
			property IDirect3DTexture9* InternalPointer
			{
				IDirect3DTexture9* get() { return m_Texture; }
			}

			property IDirect3DResource9* ResourcePointer
			{
				virtual IDirect3DResource9* get() override { return m_Texture; }
			}

		public:
			Texture( IDirect3DTexture9* texture );
			Texture( Device^ device, int width, int height, int numLevels, Usage usage, Format format, Pool pool );
			~Texture();
			!Texture();

			generic<typename T> where T : value class
			GraphicsStream<T>^ LockRectangle( int level, LockFlags flags )
			{
				D3DLOCKED_RECT lockedRect;
				HRESULT hr = m_Texture->LockRect( level, &lockedRect, NULL, (DWORD) flags );
				FAILED_THROW( hr );

				bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
				GraphicsStream<T>^ stream = gcnew GraphicsStream<T>( lockedRect.pBits, true, !readOnly );
				return stream;
			}

			void UnlockRectangle( int level )
			{
				HRESULT hr = m_Texture->UnlockRect( level );
				FAILED_THROW( hr );
			}
		};

		public ref class CubeTexture : public BaseTexture
		{
		private:
			IDirect3DCubeTexture9* m_Texture;
			bool m_Disposed;

		internal:
			property IDirect3DCubeTexture9* InternalPointer
			{
				IDirect3DCubeTexture9* get() { return m_Texture; }
			}

			property IDirect3DResource9* ResourcePointer
			{
				virtual IDirect3DResource9* get() override { return m_Texture; }
			}

		public:
			CubeTexture( IDirect3DCubeTexture9* texture );
			CubeTexture( Device^ device, int edgeLength, int numLevels, Usage usage, Format format, Pool pool );
			~CubeTexture();
			!CubeTexture();

			generic<typename T> where T : value class
			GraphicsStream<T>^ LockRectangle( CubeMapFace face, int level, LockFlags flags )
			{
				D3DLOCKED_RECT lockedRect;
				HRESULT hr = m_Texture->LockRect( (D3DCUBEMAP_FACES) face, level, &lockedRect, NULL, (DWORD) flags );
				FAILED_THROW( hr );

				bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
				GraphicsStream<T>^ stream = gcnew GraphicsStream<T>( lockedRect.pBits, true, !readOnly );
				return stream;
			}

			void UnlockRectangle( CubeMapFace face, int level )
			{
			}
		};

		public ref class TextureLoader sealed
		{
		public:
			static Texture^ FromStream( Device^ device, Stream^ stream, int width, int height, int numLevels,
				Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );

			static CubeTexture^ FromCubeStream( Device^ device, Stream^ stream, int size, int numLevels,
				Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
		};
	}
}
