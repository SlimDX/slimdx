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

		public value class SurfaceDescription : System::IEquatable<SurfaceDescription>
		{
		public:
			property Format Format;
            property ResourceType Type;
            property Usage Usage;
            property Pool Pool;
            property MultisampleType MultisampleType;
            property int MultisampleQuality;
            property int Width;
            property int Height;

			static bool operator == ( SurfaceDescription left, SurfaceDescription right );
			static bool operator != ( SurfaceDescription left, SurfaceDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( SurfaceDescription other );
			static bool Equals( SurfaceDescription% value1, SurfaceDescription% value2 );
		};

		public ref class Surface : public Resource
		{
			COMOBJECT(IDirect3DSurface9, Surface);

		public:
			virtual ~Surface() { }
			static Surface^ FromPointer( System::IntPtr surface );

			static Surface^ CreateRenderTarget( SlimDX::Direct3D9::Device^ device, int width, int height, Format format, MultisampleType multisampleType, int multisampleQuality, bool lockable );
			static Surface^ CreateOffscreenPlain( SlimDX::Direct3D9::Device^ device, int width, int height, Format format, Pool pool );
			static Surface^ CreateDepthStencil( SlimDX::Direct3D9::Device^ device, int width, int height, Format format, MultisampleType multisampleType, int multisampleQuality, bool discard );

			static Result FromMemory( Surface^ surface, array<System::Byte>^ memory, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle, array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation );
			static Result FromMemory( Surface^ surface, array<System::Byte>^ memory, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle, [Out] ImageInformation% imageInformation );
			static Result FromMemory( Surface^ surface, array<System::Byte>^ memory, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle );
			static Result FromMemory( Surface^ surface, array<System::Byte>^ memory, Filter filter, int colorKey );

			static Result FromStream( Surface^ surface, System::IO::Stream^ stream, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle, array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation );
			static Result FromStream( Surface^ surface, System::IO::Stream^ stream, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle, [Out] ImageInformation% imageInformation );
			static Result FromStream( Surface^ surface, System::IO::Stream^ stream, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle );
			static Result FromStream( Surface^ surface, System::IO::Stream^ stream, Filter filter, int colorKey );

			static Result FromFile( Surface^ surface, System::String^ fileName, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle, array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation );
			static Result FromFile( Surface^ surface, System::String^ fileName, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle, [Out] ImageInformation% imageInformation );
			static Result FromFile( Surface^ surface, System::String^ fileName, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle );
			static Result FromFile( Surface^ surface, System::String^ fileName, Filter filter, int colorKey );

			static Result FromSurface( Surface^ destinationSurface, Surface^ sourceSurface, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle, array<PaletteEntry>^ destinationPalette, array<PaletteEntry>^ sourcePalette );
			static Result FromSurface( Surface^ destinationSurface, Surface^ sourceSurface, Filter filter, int colorKey, System::Drawing::Rectangle sourceRectangle, System::Drawing::Rectangle destinationRectangle );
			static Result FromSurface( Surface^ destinationSurface, Surface^ sourceSurface, Filter filter, int colorKey );

			static DataStream^ ToStream( Surface^ surface, ImageFileFormat format, System::Drawing::Rectangle rectangle, array<PaletteEntry>^ palette );
			static DataStream^ ToStream( Surface^ surface, ImageFileFormat format, System::Drawing::Rectangle rectangle );
			static DataStream^ ToStream( Surface^ surface, ImageFileFormat format );

			static Result ToFile( Surface^ surface, System::String^ fileName, ImageFileFormat format, System::Drawing::Rectangle rectangle, array<PaletteEntry>^ palette );
			static Result ToFile( Surface^ surface, System::String^ fileName, ImageFileFormat format, System::Drawing::Rectangle rectangle );
			static Result ToFile( Surface^ surface, System::String^ fileName, ImageFileFormat format );

			DataRectangle^ LockRectangle( LockFlags flags );
			DataRectangle^ LockRectangle( System::Drawing::Rectangle rect, LockFlags flags );
			Result UnlockRectangle();

			System::IntPtr GetDC();
			Result ReleaseDC( System::IntPtr hdc );

			property SurfaceDescription Description
			{
				SurfaceDescription get();
			}
		};
	}
}
