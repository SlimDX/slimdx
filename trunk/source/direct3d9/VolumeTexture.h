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
#include "VolumeTextureRequirements.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		public ref class VolumeTexture : public BaseTexture
		{
			COMOBJECT(IDirect3DVolumeTexture9, VolumeTexture);

		public:
			VolumeTexture( SlimDX::Direct3D9::Device^ device, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool );
			virtual ~VolumeTexture() { }
			static VolumeTexture^ FromPointer( System::IntPtr pointer );

			static VolumeTextureRequirements CheckRequirements( SlimDX::Direct3D9::Device^ device, int width, int height, int depth, int mipLevelCount, Usage usage, Format format, Pool pool );

			static VolumeTexture^ FromMemory( SlimDX::Direct3D9::Device^ device, array<System::Byte>^ memory, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static VolumeTexture^ FromMemory( SlimDX::Direct3D9::Device^ device, array<System::Byte>^ memory, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static VolumeTexture^ FromMemory( SlimDX::Direct3D9::Device^ device, array<System::Byte>^ memory, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static VolumeTexture^ FromMemory( SlimDX::Direct3D9::Device^ device, array<System::Byte>^ memory, Usage usage, Pool pool );
			static VolumeTexture^ FromMemory( SlimDX::Direct3D9::Device^ device, array<System::Byte>^ memory );

			static VolumeTexture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream, int sizeBytes, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static VolumeTexture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream, int sizeBytes, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static VolumeTexture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream, int sizeBytes, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static VolumeTexture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static VolumeTexture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream, Usage usage, Pool pool );
			static VolumeTexture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream );

			static VolumeTexture^ FromFile( SlimDX::Direct3D9::Device^ device, System::String^ fileName, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static VolumeTexture^ FromFile( SlimDX::Direct3D9::Device^ device, System::String^ fileName, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static VolumeTexture^ FromFile( SlimDX::Direct3D9::Device^ device, System::String^ fileName, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static VolumeTexture^ FromFile( SlimDX::Direct3D9::Device^ device, System::String^ fileName, Usage usage, Pool pool );
			static VolumeTexture^ FromFile( SlimDX::Direct3D9::Device^ device, System::String^ fileName );

			[System::Security::Permissions::SecurityPermission( System::Security::Permissions::SecurityAction::LinkDemand, Flags=System::Security::Permissions::SecurityPermissionFlag::UnmanagedCode )]
			Result Fill( Fill3DCallback^ callback );
			Result Fill( TextureShader^ shader );

			SlimDX::DataBox^ LockBox( int level, LockFlags flags );
			SlimDX::DataBox^ LockBox( int level, Box box, LockFlags flags );
			Result UnlockBox( int level );

			Result AddDirtyBox( Box box );
			
			VolumeDescription GetLevelDescription( int level );
			Volume^ GetVolumeLevel( int level );
		};
	}
}