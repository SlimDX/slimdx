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
#include "Resource.h"
#include "Surface.h"
#include "Volume.h"
#include "Effect.h"
#include "ConstantTable.h"
#include "TextureShader.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
		public value class ImageInformation : System::IEquatable<ImageInformation>
		{
		public:
			property int Width;
            property int Height;
            property int Depth;
            property int MipLevels;
            property Format Format;
            property ResourceType ResourceType;
            property ImageFileFormat ImageFileFormat;

			static ImageInformation FromFile( System::String^ fileName );
			static ImageInformation FromMemory( array<System::Byte>^ memory );

			/// <summary>
			/// Function to extract image information from a stream.
			/// </summary>
			/// <param name="stream">Stream containing the image.</param>
			/// <param name="peek">TRUE to preserve the stream position, FALSE will move the stream pointer.</param>
			/// <returns>Information about the image.</returns>
			static ImageInformation FromStream(System::IO::Stream^ stream, bool peek);

			/// <summary>
			/// Function to extract image information from a stream.
			/// </summary>
			/// <param name="stream">Stream containing the image.</param>
			/// <returns>Information about the image.</returns>
			static ImageInformation FromStream(System::IO::Stream^ stream);

			static bool operator == ( ImageInformation left, ImageInformation right );
			static bool operator != ( ImageInformation left, ImageInformation right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( ImageInformation other );
			static bool Equals( ImageInformation% value1, ImageInformation% value2 );
		};

		/// <summary>
		/// Callback function used by FillTexture.
		/// </summary>
		/// <param name="coordinate">Texture coordinate being sampled.</param>
		/// <param name="texelSize">Dimensions of the texel.</param>
		/// <returns>A 4 dimensional vector, representing a color value.  X maps to R, G to Y, etc...</returns>
		public delegate Vector4 Fill2DCallback(Vector2 coordinate, Vector2 texelSize);

		public delegate Vector4 Fill3DCallback(Vector3 coordinate, Vector3 texelSize);

		public value class TextureRequirements : System::IEquatable<TextureRequirements>
		{
		public:
			property int Width;
            property int Height;
            property SlimDX::Direct3D9::Format Format;
            property int MipLevelCount;

			static bool operator == ( TextureRequirements left, TextureRequirements right );
			static bool operator != ( TextureRequirements left, TextureRequirements right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( TextureRequirements other );
			static bool Equals( TextureRequirements% value1, TextureRequirements% value2 );
		};

		public value class CubeTextureRequirements : System::IEquatable<CubeTextureRequirements>
		{
		public:
			property int Size;
            property Format Format;
            property int MipLevelCount;

			static bool operator == ( CubeTextureRequirements left, CubeTextureRequirements right );
			static bool operator != ( CubeTextureRequirements left, CubeTextureRequirements right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( CubeTextureRequirements other );
			static bool Equals( CubeTextureRequirements% value1, CubeTextureRequirements% value2 );
		};

		public value class VolumeTextureRequirements : System::IEquatable<VolumeTextureRequirements>
		{
		public:
			property int Width;
            property int Height;
            property int Depth;
            property SlimDX::Direct3D9::Format Format;
            property int MipLevelCount;

			static bool operator == ( VolumeTextureRequirements left, VolumeTextureRequirements right );
			static bool operator != ( VolumeTextureRequirements left, VolumeTextureRequirements right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( VolumeTextureRequirements other );
			static bool Equals( VolumeTextureRequirements% value1, VolumeTextureRequirements% value2 );
		};

		public ref class Texture : public BaseTexture
		{
		internal:
			property IDirect3DTexture9* TexturePointer
			{
				IDirect3DTexture9* get() { return static_cast<IDirect3DTexture9*>( InternalPointer ); }
			}

			Texture( IDirect3DTexture9* texture );

		public:
			Texture( System::IntPtr texture );
			Texture( Device^ device, int width, int height, int levelCount, Usage usage, Format format, Pool pool );
			virtual ~Texture() { }

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
			static TextureRequirements CheckRequirements(Device^ device, int width, int height, int mipLevelCount, Usage usage, Format format, Pool pool);

			static Texture^ FromMemory( Device^ device, array<System::Byte>^ memory, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static Texture^ FromMemory( Device^ device, array<System::Byte>^ memory, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static Texture^ FromMemory( Device^ device, array<System::Byte>^ memory, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static Texture^ FromMemory( Device^ device, array<System::Byte>^ memory, Usage usage, Pool pool );
			static Texture^ FromMemory( Device^ device, array<System::Byte>^ memory );

			static Texture^ FromStream( Device^ device, System::IO::Stream^ stream, int sizeBytes, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static Texture^ FromStream( Device^ device, System::IO::Stream^ stream, int sizeBytes, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static Texture^ FromStream( Device^ device, System::IO::Stream^ stream, int sizeBytes, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static Texture^ FromStream( Device^ device, System::IO::Stream^ stream, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static Texture^ FromStream( Device^ device, System::IO::Stream^ stream, Usage usage, Pool pool );
			static Texture^ FromStream( Device^ device, System::IO::Stream^ stream );

			static Texture^ FromFile( Device^ device, System::String^ fileName, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static Texture^ FromFile( Device^ device, System::String^ fileName, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static Texture^ FromFile( Device^ device, System::String^ fileName, int width, int height, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static Texture^ FromFile( Device^ device, System::String^ fileName, Usage usage, Pool pool );
			static Texture^ FromFile( Device^ device, System::String^ fileName );

			static Result ComputeNormalMap( Texture^ texture, Texture^ sourceTexture, array<PaletteEntry>^ palette, NormalMapFlags flags, Channel channel, float amplitude );
			static Result ComputeNormalMap( Texture^ texture, Texture^ sourceTexture, NormalMapFlags flags, Channel channel, float amplitude );

			/// <summary>
			/// Uses a user-provided function to fill each texel of each mip level of a given texture.
			/// </summary>
			/// <param name="callback">A function that uses the signature of the Fill2DCallback delegate.</param>
			Result Fill(Fill2DCallback^ callback);

			Result Fill( TextureShader^ shader );

			DataRectangle^ LockRectangle( int level, LockFlags flags );
			DataRectangle^ LockRectangle( int level, System::Drawing::Rectangle rect, LockFlags flags );
			Result UnlockRectangle( int level );

			Result AddDirtyRect( System::Drawing::Rectangle rect );
			SurfaceDescription GetLevelDescription( int level );
			Surface^ GetSurfaceLevel( int level );
		};

		public ref class CubeTexture : public BaseTexture
		{
		internal:
			property IDirect3DCubeTexture9* TexturePointer
			{
				IDirect3DCubeTexture9* get() { return static_cast<IDirect3DCubeTexture9*>( InternalPointer ); }
			}

			CubeTexture( IDirect3DCubeTexture9* texture );

		public:
			CubeTexture( System::IntPtr cubeTexture );
			CubeTexture( Device^ device, int edgeLength, int levelCount, Usage usage, Format format, Pool pool );
			virtual ~CubeTexture() { }

			static CubeTextureRequirements CheckRequirements(Device^ device, int size, int mipLevelCount, Usage usage, Format format, Pool pool);

			static CubeTexture^ FromMemory( Device^ device, array<System::Byte>^ memory, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static CubeTexture^ FromMemory( Device^ device, array<System::Byte>^ memory, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static CubeTexture^ FromMemory( Device^ device, array<System::Byte>^ memory, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static CubeTexture^ FromMemory( Device^ device, array<System::Byte>^ memory, Usage usage, Pool pool );
			static CubeTexture^ FromMemory( Device^ device, array<System::Byte>^ memory );

			static CubeTexture^ FromStream( Device^ device, System::IO::Stream^ stream, int sizeBytes, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static CubeTexture^ FromStream( Device^ device, System::IO::Stream^ stream, int sizeBytes, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static CubeTexture^ FromStream( Device^ device, System::IO::Stream^ stream, int sizeBytes, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static CubeTexture^ FromStream( Device^ device, System::IO::Stream^ stream, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static CubeTexture^ FromStream( Device^ device, System::IO::Stream^ stream, Usage usage, Pool pool );
			static CubeTexture^ FromStream( Device^ device, System::IO::Stream^ stream );

			static CubeTexture^ FromFile( Device^ device, System::String^ fileName, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static CubeTexture^ FromFile( Device^ device, System::String^ fileName, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static CubeTexture^ FromFile( Device^ device, System::String^ fileName, int size, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static CubeTexture^ FromFile( Device^ device, System::String^ fileName, Usage usage, Pool pool );
			static CubeTexture^ FromFile( Device^ device, System::String^ fileName );

			Result Fill( Fill3DCallback^ callback );
			Result Fill( TextureShader^ shader );

			DataRectangle^ LockRectangle( CubeMapFace face, int level, LockFlags flags );
			DataRectangle^ LockRectangle( CubeMapFace face, int level, System::Drawing::Rectangle rect, LockFlags flags );
			Result UnlockRectangle( CubeMapFace face, int level );

			Result AddDirtyRect( CubeMapFace face, System::Drawing::Rectangle rect );
			SurfaceDescription GetLevelDescription( int level );
			Surface^ GetCubeMapSurface( CubeMapFace face, int level );
		};

		public ref class VolumeTexture : public BaseTexture
		{
		internal:
			property IDirect3DVolumeTexture9* TexturePointer
			{
				IDirect3DVolumeTexture9* get() { return static_cast<IDirect3DVolumeTexture9*>( InternalPointer ); }
			}

			VolumeTexture( IDirect3DVolumeTexture9* texture );

		public:
			VolumeTexture( System::IntPtr volumeTexture );
			VolumeTexture( Device^ device, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool );
			virtual ~VolumeTexture() { }

			static VolumeTextureRequirements CheckRequirements(Device^ device, int width, int height, int depth, int mipLevelCount, Usage usage, Format format, Pool pool);

			static VolumeTexture^ FromMemory( Device^ device, array<System::Byte>^ memory, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static VolumeTexture^ FromMemory( Device^ device, array<System::Byte>^ memory, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static VolumeTexture^ FromMemory( Device^ device, array<System::Byte>^ memory, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static VolumeTexture^ FromMemory( Device^ device, array<System::Byte>^ memory, Usage usage, Pool pool );
			static VolumeTexture^ FromMemory( Device^ device, array<System::Byte>^ memory );

			static VolumeTexture^ FromStream( Device^ device, System::IO::Stream^ stream, int sizeBytes, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static VolumeTexture^ FromStream( Device^ device, System::IO::Stream^ stream, int sizeBytes, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static VolumeTexture^ FromStream( Device^ device, System::IO::Stream^ stream, int sizeBytes, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static VolumeTexture^ FromStream( Device^ device, System::IO::Stream^ stream, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static VolumeTexture^ FromStream( Device^ device, System::IO::Stream^ stream, Usage usage, Pool pool );
			static VolumeTexture^ FromStream( Device^ device, System::IO::Stream^ stream );

			static VolumeTexture^ FromFile( Device^ device, System::String^ fileName, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation, [Out] array<PaletteEntry>^% palette );
			static VolumeTexture^ FromFile( Device^ device, System::String^ fileName, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey, [Out] ImageInformation% imageInformation );
			static VolumeTexture^ FromFile( Device^ device, System::String^ fileName, int width, int height, int depth, int levelCount, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static VolumeTexture^ FromFile( Device^ device, System::String^ fileName, Usage usage, Pool pool );
			static VolumeTexture^ FromFile( Device^ device, System::String^ fileName );

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
