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
#include "../DataBox.h"

#include "Enums.h"
#include "Texture.h"

namespace SlimDX
{
	ref class DataBox;
	
	namespace Direct3D10
	{
		ref class Device;
		value class Texture3DDescription;
			
		public ref class Texture3D : public Texture
		{
			COMOBJECT(ID3D10Texture3D);
	
		internal:
			Texture3D( ID3D10Texture3D* pointer );
			
		public:
			property Texture3DDescription Description
			{
				Texture3DDescription get();
			}

			Texture3D( System::IntPtr nativeObject );
			Texture3D( Device^ device, Texture3DDescription description );
			
			DataBox^ Map( int subResource, MapMode mode, MapFlags flags );
			void Unmap( int subResource );
			
			static Texture3D^ FromFile( Device^ device, System::String^ fileName );
			static Texture3D^ FromStream( Device^ device, System::IO::Stream^ stream, int sizeInBytes );
		};
	}
};