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

		internal:
			property IDirect3DTexture9* InternalPointer
			{
				IDirect3DTexture9* get() { return m_Texture; }
			}

			property IDirect3DResource9* ResourcePointer
			{
				virtual IDirect3DResource9* get() override { return m_Texture; }
			}

			property IUnknown* ComPointer
			{
				virtual IUnknown* get() override { return m_Texture; }
				virtual void set( IUnknown* value ) override { m_Texture = (IDirect3DTexture9*) value; }
			}

		public:
			Texture( IDirect3DTexture9* texture );
			Texture( Device^ device, int width, int height, int numLevels, Usage usage, Format format, Pool pool );

			generic<typename T> where T : value class
			GraphicsStream<T>^ LockRectangle( int level, LockFlags flags );
			void UnlockRectangle( int level );
		};

		public ref class CubeTexture : public BaseTexture
		{
		private:
			IDirect3DCubeTexture9* m_Texture;

		internal:
			property IDirect3DCubeTexture9* InternalPointer
			{
				IDirect3DCubeTexture9* get() { return m_Texture; }
			}

			property IDirect3DResource9* ResourcePointer
			{
				virtual IDirect3DResource9* get() override { return m_Texture; }
			}

			property IUnknown* ComPointer
			{
				virtual IUnknown* get() override { return m_Texture; }
				virtual void set( IUnknown* value ) override { m_Texture = (IDirect3DCubeTexture9*) value; }
			}

		public:
			CubeTexture( IDirect3DCubeTexture9* texture );
			CubeTexture( Device^ device, int edgeLength, int numLevels, Usage usage, Format format, Pool pool );

			generic<typename T> where T : value class
			GraphicsStream<T>^ LockRectangle( CubeMapFace face, int level, LockFlags flags );
			void UnlockRectangle( CubeMapFace face, int level );
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
