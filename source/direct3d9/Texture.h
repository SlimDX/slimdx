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

#include "BaseTexture.h"
#include "Resource.h"
#include "Surface.h"
#include "Volume.h"
#include "Buffer.h"
#include "../direct3d/LockedBox.h"
#include "../direct3d/LockedRect.h"
#include "../math/Math.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		[StructLayout( LayoutKind::Sequential )]
		public value class ImageInformation
		{
		private:
			int width;
            int height;
            int depth;
            int mipLevels;
            Format format;
            ResourceType resourceType;
            ImageFileFormat imageFileFormat;

		public:
			property int Width
            {
                int get() { return width; }
                void set( int value ) { width = value; }
            }

            property int Height
            {
                int get() { return height; }
                void set( int value ) { height = value; }
            }

            property int Depth
            {
                int get() { return depth; }
                void set( int value ) { depth = value; }
            }

            property int MipLevels
            {
                int get() { return mipLevels; }
                void set( int value ) { mipLevels = value; }
            }

			property SlimDX::Direct3D9::Format Format
            {
                SlimDX::Direct3D9::Format get() { return format; }
                void set( SlimDX::Direct3D9::Format value ) { format = value; }
            }

            property SlimDX::Direct3D9::ResourceType ResourceType
            {
                SlimDX::Direct3D9::ResourceType get() { return resourceType; }
                void set( SlimDX::Direct3D9::ResourceType value ) { resourceType = value; }
            }

            property SlimDX::Direct3D9::ImageFileFormat ImageFileFormat
            {
                SlimDX::Direct3D9::ImageFileFormat get() { return imageFileFormat; }
                void set( SlimDX::Direct3D9::ImageFileFormat value ) { imageFileFormat = value; }
            }

			static ImageInformation FromFile( String^ fileName );
			static ImageInformation FromMemory( array<Byte>^ memory );

			/// <summary>
			/// Function to extract image information from a stream.
			/// </summary>
			/// <param name="stream">Stream containing the image.</param>
			/// <param name="peek">TRUE to preserve the stream position, FALSE will move the stream pointer.</param>
			/// <returns>Information about the image.</returns>
			static ImageInformation FromStream(Stream^ stream, bool peek);

			/// <summary>
			/// Function to extract image information from a stream.
			/// </summary>
			/// <param name="stream">Stream containing the image.</param>
			/// <returns>Information about the image.</returns>
			static ImageInformation FromStream(Stream^ stream);
		};

		/// <summary>
		/// Callback function used by FillTexture.
		/// </summary>
		/// <param name="coordinate">Texture coordinate being sampled.</param>
		/// <param name="texelSize">Dimensions of the texel.</param>
		/// <returns>A 4 dimensional vector, representing a color value.  X maps to R, G to Y, etc...</returns>
		public delegate Vector4 Fill2DCallback(Vector2 coordinate, Vector2 texelSize);

		public value class TextureRequirements
		{
		private:
			int width;
            int height;
            SlimDX::Direct3D9::Format format;
            int numOfMipLevels;

		public:
			/// <summary>
			/// Proposed width of the texture.
			/// </summary>
			property int Width
            {
                int get() { return width; }
                void set( int value ) { width = value; }
            }

			/// <summary>
			/// Proposed height of the texture.
			/// </summary>
            property int Height
            {
                int get() { return height; }
                void set( int value ) { height = value; }
            }

			/// <summary>
			/// Proposed format of the texture.
			/// </summary>
            property SlimDX::Direct3D9::Format Format
            {
                SlimDX::Direct3D9::Format get() { return format; }
                void set( SlimDX::Direct3D9::Format value ) { format = value; }
            }

			/// <summary>
			/// Proposed number of mip-map levels for the texture.
			/// </summary>
            property int NumOfMipLevels
            {
                int get() { return numOfMipLevels; }
                void set( int value ) { numOfMipLevels = value; }
            }
		};

		public value class CubeTextureRequirements
		{
		private:
			int size;
            Format format;
            int numOfMipLevels;

		public:
			/// <summary>
			/// Proposed size of the texture.
			/// </summary>
			property int Size
            {
                int get() { return size; }
                void set( int value ) { size = value; }
            }

			/// <summary>
			/// Proposed format of the texture.
			/// </summary>
            property SlimDX::Direct3D9::Format Format
            {
                SlimDX::Direct3D9::Format get() { return format; }
                void set( SlimDX::Direct3D9::Format value ) { format = value; }
            }

			/// <summary>
			/// Proposed number of mip-map levels for the texture.
			/// </summary>
            property int NumOfMipLevels
            {
                int get() { return numOfMipLevels; }
                void set( int value ) { numOfMipLevels = value; }
            }
		};

		public value class VolumeTextureRequirements
		{
		private:
			int width;
            int height;
            int depth;
            SlimDX::Direct3D9::Format format;
            int numOfMipLevels;

		public:
			/// <summary>
			/// Proposed width of the texture.
			/// </summary>
			property int Width
            {
                int get() { return width; }
                void set( int value ) { width = value; }
            }

			/// <summary>
			/// Proposed height of the texture.
			/// </summary>
            property int Height
            {
                int get() { return height; }
                void set( int value ) { height = value; }
            }

			/// <summary>
			/// Proposed depth of the texture.
			/// </summary>
            property int Depth
            {
                int get() { return depth; }
                void set( int value ) { depth = value; }
            }

			/// <summary>
			/// Proposed format of the texture.
			/// </summary>
            property SlimDX::Direct3D9::Format Format
            {
                SlimDX::Direct3D9::Format get() { return format; }
                void set( SlimDX::Direct3D9::Format value ) { format = value; }
            }

			/// <summary>
			/// Proposed number of mip-map levels for the texture.
			/// </summary>
            property int NumOfMipLevels
            {
                int get() { return numOfMipLevels; }
                void set( int value ) { numOfMipLevels = value; }
            }
		};

		public ref class Texture : public BaseTexture
		{
		internal:
			property IDirect3DTexture9* TexturePointer
			{
				IDirect3DTexture9* get() { return (IDirect3DTexture9*) m_Pointer; }
			}

			Texture( IDirect3DTexture9* texture );

		public:
			Texture( IntPtr texture );
			Texture( Device^ device, int width, int height, int numLevels, Usage usage, Format format, Pool pool );

			/// <summary>
			/// Checks texture-creation parameters.
			/// </summary>
			/// <param name="device">Device associated with the texture.</param>
			/// <param name="width">Requested width of the texture.</param>
			/// <param name="height">Requested height of the texture.</param>
			/// <param name="numMipLevels">Requested number of mip-map levels for the texture.</param>
			/// <param name="usage">Usage.None or Usage.RenderTarget.</param>
			/// <param name="format">Requested format for the texture.</param>
			/// <param name="pool">Memory class where the resource will be placed.</param>
			/// <returns>A value type containing the proposed values to pass to the texture creation functions.</returns>
			static TextureRequirements CheckRequirements(Device^ device, int width, int height,
				int numMipLevels, Usage usage, Format format, Pool pool);

			static Texture^ FromMemory( Device^ device, array<Byte>^ memory, int width, int height, int numLevels,
				Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static Texture^ FromMemory( Device^ device, array<Byte>^ memory, Usage usage, Pool pool );
			static Texture^ FromMemory( Device^ device, array<Byte>^ memory );

			static Texture^ FromStream( Device^ device, Stream^ stream, int sizeBytes, int width, int height, int numLevels,
				Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static Texture^ FromStream( Device^ device, Stream^ stream, int width, int height, int numLevels,
				Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static Texture^ FromStream( Device^ device, Stream^ stream, Usage usage, Pool pool );
			static Texture^ FromStream( Device^ device, Stream^ stream );

			static Texture^ FromFile( Device^ device, String^ fileName, int width, int height, int numLevels,
				Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static Texture^ FromFile( Device^ device, String^ fileName, Usage usage, Pool pool );
			static Texture^ FromFile( Device^ device, String^ fileName );

			/// <summary>
			/// Function to save the texture to a stream.
			/// </summary>
			/// <param name="format">File format used to encode the image.</param>
			/// <returns>A graphics stream containing the texture data.</returns>
			BufferWrapper^ Save(ImageFileFormat format);

			/// <summary>
			/// Function to save the texture to a file.
			/// </summary>
			/// <param name="fileName">Filename and path for the texture.</param>
			/// <param name="format">File format used to encode the image.</param>
			void SaveToFile(String^ fileName, ImageFileFormat format);

			/// <summary>
			/// Uses a user-provided function to fill each texel of each mip level of a given texture.
			/// </summary>
			/// <param name="callback">A function that uses the signature of the Fill2DCallback delegate.</param>
			void Fill(Fill2DCallback^ callback);

			LockedRect LockRectangle( int level, LockFlags flags );
			LockedRect LockRectangle( int level, System::Drawing::Rectangle rect, LockFlags flags );
			void UnlockRectangle( int level );

			void AddDirtyRect( System::Drawing::Rectangle rect );
			SurfaceDescription GetLevelDescription( int level );
			Surface^ GetSurfaceLevel( int level );
		};

		public ref class CubeTexture : public BaseTexture
		{
		internal:
			property IDirect3DCubeTexture9* TexturePointer
			{
				IDirect3DCubeTexture9* get() { return (IDirect3DCubeTexture9*) m_Pointer; }
			}

			CubeTexture( IDirect3DCubeTexture9* texture );

		public:
			CubeTexture( IntPtr cubeTexture );
			CubeTexture( Device^ device, int edgeLength, int numLevels, Usage usage, Format format, Pool pool );

			static CubeTextureRequirements CheckRequirements(Device^ device, int size,
				int numMipLevels, Usage usage, Format format, Pool pool);

			static CubeTexture^ FromMemory( Device^ device, array<Byte>^ memory, int size, int numLevels,
				Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static CubeTexture^ FromMemory( Device^ device, array<Byte>^ memory, Usage usage, Pool pool );
			static CubeTexture^ FromMemory( Device^ device, array<Byte>^ memory );

			static CubeTexture^ FromStream( Device^ device, Stream^ stream, int sizeBytes, int size, int numLevels,
				Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static CubeTexture^ FromStream( Device^ device, Stream^ stream, int size, int numLevels,
				Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static CubeTexture^ FromStream( Device^ device, Stream^ stream, Usage usage, Pool pool );
			static CubeTexture^ FromStream( Device^ device, Stream^ stream );

			static CubeTexture^ FromFile( Device^ device, String^ fileName, int size, int numLevels,
				Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static CubeTexture^ FromFile( Device^ device, String^ fileName, Usage usage, Pool pool );
			static CubeTexture^ FromFile( Device^ device, String^ fileName );

			LockedRect LockRectangle( CubeMapFace face, int level, LockFlags flags );
			LockedRect LockRectangle( CubeMapFace face, int level, System::Drawing::Rectangle rect, LockFlags flags );
			void UnlockRectangle( CubeMapFace face, int level );

			void AddDirtyRect( CubeMapFace face, System::Drawing::Rectangle rect );
			SurfaceDescription GetLevelDescription( int level );
			Surface^ GetCubeMapSurface( CubeMapFace face, int level );
		};

		public ref class VolumeTexture : public BaseTexture
		{
		internal:
			property IDirect3DVolumeTexture9* TexturePointer
			{
				IDirect3DVolumeTexture9* get() { return (IDirect3DVolumeTexture9*) m_Pointer; }
			}

			VolumeTexture( IDirect3DVolumeTexture9* texture );

		public:
			VolumeTexture( IntPtr volumeTexture );
			VolumeTexture( Device^ device, int width, int height, int depth, int numLevels, Usage usage, Format format, Pool pool );

			static VolumeTextureRequirements CheckRequirements(Device^ device, int width, int height, int depth,
				int numMipLevels, Usage usage, Format format, Pool pool);

			static VolumeTexture^ FromMemory( Device^ device, array<Byte>^ memory, int width, int height, int depth,
				int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static VolumeTexture^ FromMemory( Device^ device, array<Byte>^ memory, Usage usage, Pool pool );
			static VolumeTexture^ FromMemory( Device^ device, array<Byte>^ memory );

			static VolumeTexture^ FromStream( Device^ device, Stream^ stream, int sizeBytes, int width, int height, int depth,
				int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static VolumeTexture^ FromStream( Device^ device, Stream^ stream, int width, int height, int depth,
				int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static VolumeTexture^ FromStream( Device^ device, Stream^ stream, Usage usage, Pool pool );
			static VolumeTexture^ FromStream( Device^ device, Stream^ stream );

			static VolumeTexture^ FromFile( Device^ device, String^ fileName, int width, int height, int depth,
				int numLevels, Usage usage, Format format, Pool pool, Filter filter, Filter mipFilter, int colorKey );
			static VolumeTexture^ FromFile( Device^ device, String^ fileName, Usage usage, Pool pool );
			static VolumeTexture^ FromFile( Device^ device, String^ fileName );

			SlimDX::Direct3D::LockedBox LockBox( int level, LockFlags flags );
			SlimDX::Direct3D::LockedBox LockBox( int level, Box box, LockFlags flags );
			void UnlockBox( int level );

			void AddDirtyBox( Box box );
			//TODO: Implement the following
			//VolumeDescription GetLevelDesc( int level );
			//Volume^ GetVolumeLevel( int level );
		};
	}
}
