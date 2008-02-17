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
#include "../DataBox.h"

namespace SlimDX
{
	ref class DataStream;

	namespace Direct3D9
	{
		value class ImageInformation;

		[StructLayout( LayoutKind::Sequential )]
		public value class Box
		{
		public:
			property int Left;
            property int Top;
            property int Right;
            property int Bottom;
            property int Front;
            property int Back;
		};

		[StructLayout( LayoutKind::Sequential )]
		public value class VolumeDescription
		{
		public:
			property Format Format;
			property ResourceType Type;
			property Usage Usage;
			property Pool Pool;
			property int Width;
			property int Height;
			property int Depth;
		};

		public ref class Volume : public Resource
		{
		internal:
			Volume( IDirect3DVolume9* volume );
			property IDirect3DVolume9* VolumePointer
			{
				IDirect3DVolume9* get() { return reinterpret_cast<IDirect3DVolume9*>( InternalPointer ); }
			}

		public:
			Volume( IntPtr volume );
			virtual ~Volume() { }

			static void FromMemory( Volume^ volume, array<Byte>^ memory, Filter filter, int colorKey, Box sourceBox, Box destinationBox, array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation );
			static void FromMemory( Volume^ volume, array<Byte>^ memory, Filter filter, int colorKey, Box sourceBox, Box destinationBox, [Out] ImageInformation% imageInformation );
			static void FromMemory( Volume^ volume, array<Byte>^ memory, Filter filter, int colorKey, Box sourceBox, Box destinationBox );
			static void FromMemory( Volume^ volume, array<Byte>^ memory, Filter filter, int colorKey );

			static void FromStream( Volume^ volume, Stream^ stream, Filter filter, int colorKey, Box sourceBox, Box destinationBox, array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation );
			static void FromStream( Volume^ volume, Stream^ stream, Filter filter, int colorKey, Box sourceBox, Box destinationBox, [Out] ImageInformation% imageInformation );
			static void FromStream( Volume^ volume, Stream^ stream, Filter filter, int colorKey, Box sourceBox, Box destinationBox );
			static void FromStream( Volume^ volume, Stream^ stream, Filter filter, int colorKey );

			static void FromFile( Volume^ volume, String^ fileName, Filter filter, int colorKey, Box sourceBox, Box destinationBox, array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation );
			static void FromFile( Volume^ volume, String^ fileName, Filter filter, int colorKey, Box sourceBox, Box destinationBox, [Out] ImageInformation% imageInformation );
			static void FromFile( Volume^ volume, String^ fileName, Filter filter, int colorKey, Box sourceBox, Box destinationBox );
			static void FromFile( Volume^ volume, String^ fileName, Filter filter, int colorKey );

			static void FromVolume( Volume^ destinationVolume, Volume^ sourceVolume, Filter filter, int colorKey, Box sourceBox, Box destinationBox, array<PaletteEntry>^ destinationPalette, array<PaletteEntry>^ sourcePalette );
			static void FromVolume( Volume^ destinationVolume, Volume^ sourceVolume, Filter filter, int colorKey, Box sourceBox, Box destinationBox );
			static void FromVolume( Volume^ destinationVolume, Volume^ sourceVolume, Filter filter, int colorKey );

			static DataStream^ ToStream( Volume^ volume, ImageFileFormat format, Box box, array<PaletteEntry>^ palette );
			static DataStream^ ToStream( Volume^ volume, ImageFileFormat format, Box box );
			static DataStream^ ToStream( Volume^ volume, ImageFileFormat format );

			static void ToFile( Volume^ volume, String^ fileName, ImageFileFormat format, Box box, array<PaletteEntry>^ palette );
			static void ToFile( Volume^ volume, String^ fileName, ImageFileFormat format, Box box );
			static void ToFile( Volume^ volume, String^ fileName, ImageFileFormat format );

			DataBox^ LockBox( LockFlags flags );
			DataBox^ LockBox( Box box, LockFlags flags );
			void UnlockBox();

			Device^ GetDevice();

			property VolumeDescription Description
			{
				VolumeDescription get();
			}
		};
	}
}
