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

#include "../DataBox.h"
#include "../DataRectangle.h"

#include "BaseTexture.h"
#include "Surface.h"
#include "Volume.h"
#include "Effect.h"
#include "ConstantTable.h"
#include "TextureShader.h"
#include "Delegates.h"

#include "ImageInformation.h"
#include "CubeTextureRequirements.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		public ref class CubeTexture : public BaseTexture
		{
			COMOBJECT(IDirect3DCubeTexture9, CubeTexture);

		public:
			CubeTexture( SlimDX::Direct3D9::Device^ device, int edgeLength, int levelCount, Usage usage, Format format, Pool pool );
			virtual ~CubeTexture() { }
			static CubeTexture^ FromPointer( System::IntPtr pointer );

			static CubeTextureRequirements CheckRequirements( SlimDX::Direct3D9::Device^ device, int size, int mipLevelCount, Usage usage, Format format, Pool pool );

			static CubeTexture^ FromMemory( SlimDX::Direct3D9::Device^ device, array<System::Byte>^ memory, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static CubeTexture^ FromMemory( SlimDX::Direct3D9::Device^ device, array<System::Byte>^ memory, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static CubeTexture^ FromMemory( SlimDX::Direct3D9::Device^ device, array<System::Byte>^ memory, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static CubeTexture^ FromMemory( SlimDX::Direct3D9::Device^ device, array<System::Byte>^ memory, Usage usage, Pool pool );
			static CubeTexture^ FromMemory( SlimDX::Direct3D9::Device^ device, array<System::Byte>^ memory );

			static CubeTexture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream, int sizeBytes, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static CubeTexture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream, int sizeBytes, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static CubeTexture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream, int sizeBytes, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static CubeTexture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static CubeTexture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream, Usage usage, Pool pool );
			static CubeTexture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream );

			static CubeTexture^ FromFile( SlimDX::Direct3D9::Device^ device, System::String^ fileName, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static CubeTexture^ FromFile( SlimDX::Direct3D9::Device^ device, System::String^ fileName, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static CubeTexture^ FromFile( SlimDX::Direct3D9::Device^ device, System::String^ fileName, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static CubeTexture^ FromFile( SlimDX::Direct3D9::Device^ device, System::String^ fileName, Usage usage, Pool pool );
			static CubeTexture^ FromFile( SlimDX::Direct3D9::Device^ device, System::String^ fileName );

			Result Fill( Fill3DCallback^ callback );
			Result Fill( TextureShader^ shader );

			DataRectangle^ LockRectangle( CubeMapFace face, int level, LockFlags flags );
			DataRectangle^ LockRectangle( CubeMapFace face, int level, System::Drawing::Rectangle rect, LockFlags flags );
			Result UnlockRectangle( CubeMapFace face, int level );

			Result AddDirtyRect( CubeMapFace face, System::Drawing::Rectangle rect );
			SurfaceDescription GetLevelDescription( int level );
			Surface^ GetCubeMapSurface( CubeMapFace face, int level );
		};
	}
}