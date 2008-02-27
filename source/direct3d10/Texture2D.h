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

#include "../ComObject.h"
#include "../DataRectangle.h"

#include "Enums.h"
#include "Texture.h"

namespace SlimDX
{
	ref class DataRectangle;
	
	namespace Direct3D10
	{
		ref class Device;
		value class Texture2DDescription;
		
		public ref class Texture2D : public Texture
		{
			COMOBJECT(ID3D10Texture2D, Texture2D);
		
		public:
			property Texture2DDescription Description
			{
				Texture2DDescription get();
			}
			
			Texture2D( Device^ device, Texture2DDescription description );
			static Texture2D^ FromPointer( System::IntPtr pointer );

			DataRectangle^ Map( int subResource, MapMode mode, MapFlags flags );
			void Unmap( int subResource );
			
			static Texture2D^ FromFile( Device^ device, System::String^ fileName );
			static Texture2D^ FromMemory( Device^ device, array<System::Byte>^ memory );
			static Texture2D^ FromStream( Device^ device, System::IO::Stream^ stream, int sizeInBytes );
		};
	}
};