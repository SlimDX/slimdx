/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include "Enums11.h"
#include "Resource11.h"
#include "ImageLoadInformation11.h"

namespace SlimDX
{
	ref class DataBox;
	
	namespace Direct3D11
	{
		ref class Device;
		ref class DeviceContext;
		value class Texture3DDescription;
			
		public ref class Texture3D : public Resource
		{
			COMOBJECT(ID3D11Texture3D, Texture3D);
			
		private:
				static ID3D11Texture3D* Build( SlimDX::Direct3D11::Device^ device, Texture3DDescription description, D3D11_SUBRESOURCE_DATA* data ); 
		
		public:
			/// <summary>
			/// Gets the texture description.
			/// </summary>
			property Texture3DDescription Description
			{
				Texture3DDescription get();
			}
			
			/// <summary>
			/// Initializes a new instance of the <see cref="Texture3D"/> class.
			/// </summary>
			/// <param name="device">The device to associate the texture with.</param>
			/// <param name="description">The description of the texture.</param>
			Texture3D( SlimDX::Direct3D11::Device^ device, Texture3DDescription description );
			
			/// <summary>
			/// Initializes a new instance of the <see cref="Texture3D"/> class.
			/// </summary>
			/// <param name="device">The device to associate the texture with.</param>
			/// <param name="description">The description of the texture.</param>
			/// <param name="data">The initial texture data.</param>
			Texture3D( SlimDX::Direct3D11::Device^ device, Texture3DDescription description, DataBox^ data );
			
			/// <summary>
			/// Initializes a new instance of the <see cref="Texture3D"/> class.
			/// </summary>
			/// <param name="device">The device to associate the texture with.</param>
			/// <param name="description">The description of the texture.</param>
			/// <param name="data">An array of initial texture data for each subresource.</param>
			Texture3D( SlimDX::Direct3D11::Device^ device, Texture3DDescription description, array<DataBox^>^ data );
			
			static Texture3D^ FromFile( SlimDX::Direct3D11::Device^ device, System::String^ fileName );
			static Texture3D^ FromFile( SlimDX::Direct3D11::Device^ device, System::String^ fileName, ImageLoadInformation loadInfo );
			static Texture3D^ FromMemory( SlimDX::Direct3D11::Device^ device, array<System::Byte>^ memory );
			static Texture3D^ FromMemory( SlimDX::Direct3D11::Device^ device, array<System::Byte>^ memory, ImageLoadInformation loadInfo );
			static Texture3D^ FromStream( SlimDX::Direct3D11::Device^ device, System::IO::Stream^ stream, int sizeInBytes );
			static Texture3D^ FromStream( SlimDX::Direct3D11::Device^ device, System::IO::Stream^ stream, int sizeInBytes, ImageLoadInformation loadInfo );
		
			static Result ToFile( DeviceContext^ context, Texture3D^ texture, ImageFileFormat format, System::String^ fileName );
			static Result ToStream( DeviceContext^ context, Texture3D^ texture, ImageFileFormat format, System::IO::Stream^ stream );
		};
	}
};