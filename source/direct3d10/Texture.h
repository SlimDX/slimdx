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

//using namespace System;

#include "../ComObject.h"

#include "../dxgi/Enums.h"

#include "Resource.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Device;
		
		/// <remarks>
		/// A base class for texture resources.
		/// </remarks>
		public ref class Texture : public Resource
		{
		internal:
			static int GetMipSize( int mipSlice, int baseSliceSize );
			static int GetElementSize( DXGI::Format format );
			
		protected:
			Texture( ID3D10Resource *pointer );
		
		public:
			Texture();

			static Texture^ FromFile( Device^ device, System::String^ fileName );
			static Texture^ FromMemory( Device^ device, array<System::Byte>^ memory );
			static Texture^ FromStream( Device^ device, System::IO::Stream^ stream, int sizeInBytes );

			static bool ToFile( Texture^ texture, ImageFileFormat format, System::String^ fileName );
		};
	}
};