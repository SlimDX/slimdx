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
#include "../DataBox.h"

namespace SlimDX
{
	ref class DataStream;

	namespace Direct3D9
	{
		value class ImageInformation;

		[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
		public value class Box : System::IEquatable<Box>
		{
		public:
			property int Left;
            property int Top;
            property int Right;
            property int Bottom;
            property int Front;
            property int Back;

			static bool operator == ( Box left, Box right );
			static bool operator != ( Box left, Box right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( Box other );
			static bool Equals( Box% value1, Box% value2 );
		};

		[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
		public value class VolumeDescription : System::IEquatable<VolumeDescription>
		{
		public:
			property Format Format;
			property ResourceType Type;
			property Usage Usage;
			property Pool Pool;
			property int Width;
			property int Height;
			property int Depth;

			static bool operator == ( VolumeDescription left, VolumeDescription right );
			static bool operator != ( VolumeDescription left, VolumeDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( VolumeDescription other );
			static bool Equals( VolumeDescription% value1, VolumeDescription% value2 );
		};

		public ref class Volume : public Resource
		{
			COMOBJECT(IDirect3DVolume9, Volume);

		public:
			virtual ~Volume() { }
			static Volume^ FromPointer( System::IntPtr volume );

			static Result FromMemory( Volume^ volume, array<System::Byte>^ memory, Filter filter, int colorKey, Box sourceBox, Box destinationBox, array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation );
			static Result FromMemory( Volume^ volume, array<System::Byte>^ memory, Filter filter, int colorKey, Box sourceBox, Box destinationBox, [Out] ImageInformation% imageInformation );
			static Result FromMemory( Volume^ volume, array<System::Byte>^ memory, Filter filter, int colorKey, Box sourceBox, Box destinationBox );
			static Result FromMemory( Volume^ volume, array<System::Byte>^ memory, Filter filter, int colorKey );

			static Result FromStream( Volume^ volume, System::IO::Stream^stream, Filter filter, int colorKey, Box sourceBox, Box destinationBox, array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation );
			static Result FromStream( Volume^ volume, System::IO::Stream^stream, Filter filter, int colorKey, Box sourceBox, Box destinationBox, [Out] ImageInformation% imageInformation );
			static Result FromStream( Volume^ volume, System::IO::Stream^stream, Filter filter, int colorKey, Box sourceBox, Box destinationBox );
			static Result FromStream( Volume^ volume, System::IO::Stream^stream, Filter filter, int colorKey );

			static Result FromFile( Volume^ volume, System::String^ fileName, Filter filter, int colorKey, Box sourceBox, Box destinationBox, array<PaletteEntry>^ palette, [Out] ImageInformation% imageInformation );
			static Result FromFile( Volume^ volume, System::String^ fileName, Filter filter, int colorKey, Box sourceBox, Box destinationBox, [Out] ImageInformation% imageInformation );
			static Result FromFile( Volume^ volume, System::String^ fileName, Filter filter, int colorKey, Box sourceBox, Box destinationBox );
			static Result FromFile( Volume^ volume, System::String^ fileName, Filter filter, int colorKey );

			static Result FromVolume( Volume^ destinationVolume, Volume^ sourceVolume, Filter filter, int colorKey, Box sourceBox, Box destinationBox, array<PaletteEntry>^ destinationPalette, array<PaletteEntry>^ sourcePalette );
			static Result FromVolume( Volume^ destinationVolume, Volume^ sourceVolume, Filter filter, int colorKey, Box sourceBox, Box destinationBox );
			static Result FromVolume( Volume^ destinationVolume, Volume^ sourceVolume, Filter filter, int colorKey );

			static DataStream^ ToStream( Volume^ volume, ImageFileFormat format, Box box, array<PaletteEntry>^ palette );
			static DataStream^ ToStream( Volume^ volume, ImageFileFormat format, Box box );
			static DataStream^ ToStream( Volume^ volume, ImageFileFormat format );

			static Result ToFile( Volume^ volume, System::String^ fileName, ImageFileFormat format, Box box, array<PaletteEntry>^ palette );
			static Result ToFile( Volume^ volume, System::String^ fileName, ImageFileFormat format, Box box );
			static Result ToFile( Volume^ volume, System::String^ fileName, ImageFileFormat format );

			DataBox^ LockBox( LockFlags flags );
			DataBox^ LockBox( Box box, LockFlags flags );
			Result UnlockBox();

			property VolumeDescription Description
			{
				VolumeDescription get();
			}
		};
	}
}
