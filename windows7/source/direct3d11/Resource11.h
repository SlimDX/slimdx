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

#include "DeviceChild11.h"
#include "Enums11.h"

namespace SlimDX
{
	namespace Direct3D11
	{
		/// <summary>
		/// A resource object.
		/// </summary>
		/// <unmanaged>ID3D11Resource</unmanaged>
		public ref class Resource abstract : public DeviceChild
		{
			COMOBJECT_BASE(ID3D11Resource);

		internal:
			static int GetMipSize( int mipSlice, int baseSliceSize );
			
			static ID3D11Resource* ConstructFromFile( SlimDX::Direct3D11::Device^ device, System::String^ fileName, D3DX11_IMAGE_LOAD_INFO* info );
			static ID3D11Resource* ConstructFromMemory( SlimDX::Direct3D11::Device^ device, array<System::Byte>^ memory, D3DX11_IMAGE_LOAD_INFO* info );
			static ID3D11Resource* ConstructFromStream( SlimDX::Direct3D11::Device^ device, System::IO::Stream^ stream, int sizeInBytes, D3DX11_IMAGE_LOAD_INFO* info );
		
			static Resource^ FromPointer( ID3D11Resource* pointer );

		protected:
			Resource() { }

		public:
			static Resource^ FromPointer( System::IntPtr pointer );

			/// <summary>
			/// Gets or sets the resource's eviction priority.
			/// </summary>
			property DXGI::ResourcePriority EvictionPriority
			{
				DXGI::ResourcePriority get();
				void set(DXGI::ResourcePriority value);
			}
			
			/// <summary>
			/// Gets the resource's dimension (type).
			/// </summary>
			property ResourceDimension Dimension
			{
				ResourceDimension get();
			}
		};
	}
};