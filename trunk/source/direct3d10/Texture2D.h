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
			
		private:
			static ID3D10Texture2D* Build( SlimDX::Direct3D10::Device^ device, Texture2DDescription description, D3D10_SUBRESOURCE_DATA* data ); 
		
		public:
			/// <summary>
			/// Gets the texture description.
			/// </summary>
			property Texture2DDescription Description
			{
				Texture2DDescription get();
			}
			
			/// <summary>
			/// Initializes a new instance of the <see cref="Texture2D"/> class.
			/// </summary>
			/// <param name="device">The device to associate the texture with.</param>
			/// <param name="description">The description of the texture.</param>
			Texture2D( SlimDX::Direct3D10::Device^ device, Texture2DDescription description );
			
			/// <summary>
			/// Initializes a new instance of the <see cref="Texture2D"/> class.
			/// </summary>
			/// <param name="device">The device to associate the texture with.</param>
			/// <param name="description">The description of the texture.</param>
			/// <param name="data">The initial texture data.</param>
			Texture2D( SlimDX::Direct3D10::Device^ device, Texture2DDescription description, DataRectangle^ data );
			
			/// <summary>
			/// Initializes a new instance of the <see cref="Texture2D"/> class.
			/// </summary>
			/// <param name="device">The device to associate the texture with.</param>
			/// <param name="description">The description of the texture.</param>
			/// <param name="data">An array of initial texture data for each subresource.</param>
			Texture2D( SlimDX::Direct3D10::Device^ device, Texture2DDescription description, array<DataRectangle^>^ data );
			
			/// <summary>
			/// Constructs a texture object from a marshalled native pointer.
			/// </summary>
			/// <param name="pointer">The native object pointer.</param>
			/// <returns>The Texture2D object for the native object.</returns>
			static Texture2D^ FromPointer( System::IntPtr pointer );
		
			/// <summary>
			/// Maps the texture, providing CPU access to its contents.
			/// </summary>
			/// <param name="subresource">The subresource to map.</param>
			/// <param name="mode">The IO operations to enable on the CPU.</param>
			/// <param name="flags">Flags indicating how the CPU should respond when the GPU is busy.</param>
			/// <returns>A data rectangle containing the mapped data. This data stream is invalidated
			/// when the buffer is unmapped.</returns>
			DataRectangle^ Map( int subresource, MapMode mode, MapFlags flags );
			
			/// <summary>
			/// Unmaps the texture.
			/// </summary>
			/// <param name="subresource">The subresource to unmap.</param>
			void Unmap( int subresource );
			
			static Texture2D^ FromFile( SlimDX::Direct3D10::Device^ device, System::String^ fileName );
			static Texture2D^ FromFile( SlimDX::Direct3D10::Device^ device, System::String^ fileName, ImageLoadInformation loadInfo );
			static Texture2D^ FromMemory( SlimDX::Direct3D10::Device^ device, array<System::Byte>^ memory );
			static Texture2D^ FromMemory( SlimDX::Direct3D10::Device^ device, array<System::Byte>^ memory, ImageLoadInformation loadInfo );
			static Texture2D^ FromStream( SlimDX::Direct3D10::Device^ device, System::IO::Stream^ stream, int sizeInBytes );
			static Texture2D^ FromStream( SlimDX::Direct3D10::Device^ device, System::IO::Stream^ stream, int sizeInBytes, ImageLoadInformation loadInfo );
		};
	}
};