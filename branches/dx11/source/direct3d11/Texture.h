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

namespace SlimDX
{
	namespace Direct3D11
	{
		ref class Device;
		ref class DeviceContext;
		
		public ref class Texture : public Resource
		{
			COMOBJECT_BASE(ID3D11Resource);

		internal:
			static int GetMipSize( int mipSlice, int baseSliceSize );
			
			static ID3D11Resource* ConstructFromFile( SlimDX::Direct3D11::Device^ device, System::String^ fileName );
			static ID3D11Resource* ConstructFromMemory( SlimDX::Direct3D11::Device^ device, array<System::Byte>^ memory );
			static ID3D11Resource* ConstructFromStream( SlimDX::Direct3D11::Device^ device, System::IO::Stream^ stream, int sizeInBytes );
			
		protected:
			Texture( ID3D11Resource *pointer );
		
		public:
			Texture();

			static Texture^ FromFile( SlimDX::Direct3D11::Device^ device, System::String^ fileName );
			static Texture^ FromMemory( SlimDX::Direct3D11::Device^ device, array<System::Byte>^ memory );
			static Texture^ FromStream( SlimDX::Direct3D11::Device^ device, System::IO::Stream^ stream, int sizeInBytes );

			static bool ToFile( DeviceContext^ deviceContext, Texture^ texture, ImageFileFormat format, System::String^ fileName );
			static bool ToStream( DeviceContext^ deviceContext, Texture^ texture, ImageFileFormat format, System::IO::Stream^ stream );
		};
	}
};