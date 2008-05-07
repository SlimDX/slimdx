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
#include "TextureRequirements.h"

#include "CubeTexture.h"
#include "VolumeTexture.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		public ref class Texture : public BaseTexture
		{
			COMOBJECT(IDirect3DTexture9, Texture);

		public:
			Texture( SlimDX::Direct3D9::Device^ device, int width, int height, int levelCount, Usage usage, Format format, Pool pool );
			virtual ~Texture() { }
			static Texture^ FromPointer( System::IntPtr pointer );

			/// <summary>
			/// Checks texture-creation parameters.
			/// </summary>
			/// <param name="device">Device associated with the texture.</param>
			/// <param name="width">Requested width of the texture.</param>
			/// <param name="height">Requested height of the texture.</param>
			/// <param name="mipLevelCount">Requested number of mip-map levels for the texture.</param>
			/// <param name="usage">Usage.None or Usage.RenderTarget.</param>
			/// <param name="format">Requested format for the texture.</param>
			/// <param name="pool">Memory class where the resource will be placed.</param>
			/// <returns>A value type containing the proposed values to pass to the texture creation functions.</returns>
			static TextureRequirements CheckRequirements( SlimDX::Direct3D9::Device^ device, int width, int height, int mipLevelCount, Usage usage, Format format, Pool pool );

			static Texture^ FromMemory( SlimDX::Direct3D9::Device^ device, array<System::Byte>^ memory, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static Texture^ FromMemory( SlimDX::Direct3D9::Device^ device, array<System::Byte>^ memory, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static Texture^ FromMemory( SlimDX::Direct3D9::Device^ device, array<System::Byte>^ memory, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static Texture^ FromMemory( SlimDX::Direct3D9::Device^ device, array<System::Byte>^ memory, Usage usage, Pool pool );
			static Texture^ FromMemory( SlimDX::Direct3D9::Device^ device, array<System::Byte>^ memory );

			static Texture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream, int sizeBytes, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static Texture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream, int sizeBytes, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static Texture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream, int sizeBytes, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static Texture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static Texture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream, Usage usage, Pool pool );
			static Texture^ FromStream( SlimDX::Direct3D9::Device^ device, System::IO::Stream^ stream );

			static Texture^ FromFile( SlimDX::Direct3D9::Device^ device, System::String^ fileName, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static Texture^ FromFile( SlimDX::Direct3D9::Device^ device, System::String^ fileName, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static Texture^ FromFile( SlimDX::Direct3D9::Device^ device, System::String^ fileName, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static Texture^ FromFile( SlimDX::Direct3D9::Device^ device, System::String^ fileName, Usage usage, Pool pool );
			static Texture^ FromFile( SlimDX::Direct3D9::Device^ device, System::String^ fileName );

			static Result ComputeNormalMap( Texture^ texture, Texture^ sourceTexture, array<PaletteEntry>^ palette, NormalMapFlags flags, Channel channel, float amplitude );
			static Result ComputeNormalMap( Texture^ texture, Texture^ sourceTexture, NormalMapFlags flags, Channel channel, float amplitude );

			/// <summary>
			/// Uses a user-provided function to fill each texel of each mip level of a given texture.
			/// </summary>
			/// <param name="callback">A function that uses the signature of the Fill2DCallback delegate.</param>
			[System::Security::Permissions::SecurityPermission( System::Security::Permissions::SecurityAction::LinkDemand, Flags=System::Security::Permissions::SecurityPermissionFlag::UnmanagedCode )]
			Result Fill(Fill2DCallback^ callback);

			Result Fill( TextureShader^ shader );

			DataRectangle^ LockRectangle( int level, LockFlags flags );
			DataRectangle^ LockRectangle( int level, System::Drawing::Rectangle rect, LockFlags flags );
			Result UnlockRectangle( int level );

			Result AddDirtyRect( System::Drawing::Rectangle rect );
			SurfaceDescription GetLevelDescription( int level );
			Surface^ GetSurfaceLevel( int level );
		};
	}
}
