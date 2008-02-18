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

#include "Resource.h"
#include "../DataRectangle.h"

namespace SlimDX
{
	ref class DataStream;

	namespace Direct3D9
	{
		value class ImageInformation;

		public value class SurfaceDescription
		{
		private:
			Format format;
            ResourceType type;
            Usage usage;
            Pool pool;
            MultisampleType multiSampleType;
            int multiSampleQuality;
            int width;
            int height;

		public:
			property SlimDX::Direct3D9::Format Format
            {
                SlimDX::Direct3D9::Format get() { return format; }
                void set( SlimDX::Direct3D9::Format value ) { format = value; }
            }

            property ResourceType Type
            {
                ResourceType get() { return type; }
                void set( ResourceType value ) { type = value; }
            }

            property SlimDX::Direct3D9::Usage Usage
            {
                SlimDX::Direct3D9::Usage get() { return usage; }
                void set( SlimDX::Direct3D9::Usage value ) { usage = value; }
            }

            property SlimDX::Direct3D9::Pool Pool
            {
                SlimDX::Direct3D9::Pool get() { return pool; }
                void set( SlimDX::Direct3D9::Pool value ) { pool = value; }
            }

            property SlimDX::Direct3D9::MultisampleType MultisampleType
            {
                SlimDX::Direct3D9::MultisampleType get() { return multiSampleType; }
                void set( SlimDX::Direct3D9::MultisampleType value ) { multiSampleType = value; }
            }

            property int MultisampleQuality
            {
                int get() { return multiSampleQuality; }
                void set( int value ) { multiSampleQuality = value; }
            }

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
		};

		public ref class Surface : public Resource
		{
		internal:
			Surface( IDirect3DSurface9* surface );
			property IDirect3DSurface9* SurfacePointer
			{
				IDirect3DSurface9* get() { return static_cast<IDirect3DSurface9*>( InternalPointer ); }
			}

		public:
			Surface( System::IntPtr surface );
			virtual ~Surface() { }

			static Surface^ CreateRenderTarget( Device^ device, int width, int height, Format format,
				MultisampleType multisampleType, int multisampleQuality, bool lockable );
			static Surface^ CreateOffscreenPlain( Device^ device, int width, int height, Format format, Pool pool );
			static Surface^ CreateDepthStencil( Device^ device, int width, int height, Format format,
				MultisampleType multisampleType, int multisampleQuality, bool discard );

			static void FromMemory( Surface^ surface, array<System::Byte>^ memory, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle, array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation );
			static void FromMemory( Surface^ surface, array<System::Byte>^ memory, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle, [Out] ImageInformation% imageInformation );
			static void FromMemory( Surface^ surface, array<System::Byte>^ memory, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle );
			static void FromMemory( Surface^ surface, array<System::Byte>^ memory, Filter filter, int colorKey );

			static void FromStream( Surface^ surface, System::IO::Stream^ stream, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle, array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation );
			static void FromStream( Surface^ surface, System::IO::Stream^ stream, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle, [Out] ImageInformation% imageInformation );
			static void FromStream( Surface^ surface, System::IO::Stream^ stream, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle );
			static void FromStream( Surface^ surface, System::IO::Stream^ stream, Filter filter, int colorKey );

			static void FromFile( Surface^ surface, System::String^ fileName, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle, array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation );
			static void FromFile( Surface^ surface, System::String^ fileName, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle, [Out] ImageInformation% imageInformation );
			static void FromFile( Surface^ surface, System::String^ fileName, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle );
			static void FromFile( Surface^ surface, System::String^ fileName, Filter filter, int colorKey );

			static void FromSurface( Surface^ destinationSurface, Surface^ sourceSurface, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle, array<PaletteEntry>^ destinationPalette, array<PaletteEntry>^ sourcePalette );
			static void FromSurface( Surface^ destinationSurface, Surface^ sourceSurface, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle );
			static void FromSurface( Surface^ destinationSurface, Surface^ sourceSurface, Filter filter, int colorKey );

			static DataStream^ ToStream( Surface^ surface, ImageFileFormat format, System::Drawing::Rectangle rectangle, array<PaletteEntry>^ palette );
			static DataStream^ ToStream( Surface^ surface, ImageFileFormat format, System::Drawing::Rectangle rectangle );
			static DataStream^ ToStream( Surface^ surface, ImageFileFormat format );

			static void ToFile( Surface^ surface, System::String^ fileName, ImageFileFormat format, System::Drawing::Rectangle rectangle, array<PaletteEntry>^ palette );
			static void ToFile( Surface^ surface, System::String^ fileName, ImageFileFormat format, System::Drawing::Rectangle rectangle );
			static void ToFile( Surface^ surface, System::String^ fileName, ImageFileFormat format );

			DataRectangle^ LockRectangle( LockFlags flags );
			DataRectangle^ LockRectangle( System::Drawing::Rectangle rect, LockFlags flags );
			void UnlockRectangle();

			property SurfaceDescription Description
			{
				SurfaceDescription get();
			}

			System::IntPtr GetDC();
			void ReleaseDC( System::IntPtr hdc );
		};
	}
}
