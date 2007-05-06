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

#include "Resource.h"
#include "Surface.h"

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

			static Texture^ FromStream( Device^ device, Stream^ stream, int width, int height, int numLevels,
				Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static Texture^ FromStream( Device^ device, Stream^ stream, Usage usage, Pool pool );
			static Texture^ FromStream( Device^ device, Stream^ stream );

			static Texture^ FromFile( Device^ device, String^ fileName, int width, int height, int numLevels,
				Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static Texture^ FromFile( Device^ device, String^ fileName, Usage usage, Pool pool );
			static Texture^ FromFile( Device^ device, String^ fileName );

			GraphicsStream^ LockRectangle( int level, LockFlags flags );
			void UnlockRectangle( int level );

			SurfaceDescription GetLevelDesc( int level );
			Surface^ GetSurfaceLevel( int level );
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

			static CubeTexture^ FromStream( Device^ device, Stream^ stream, int size, int numLevels,
				Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );

			static CubeTexture^ FromFile( Device^ device, String^ fileName, int size, int numLevels,
				Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static CubeTexture^ FromFile( Device^ device, String^ fileName, Usage usage, Pool pool );
			static CubeTexture^ FromFile( Device^ device, String^ fileName );

			GraphicsStream^ LockRectangle( CubeMapFace face, int level, LockFlags flags );
			void UnlockRectangle( CubeMapFace face, int level );
		};
	}
}
