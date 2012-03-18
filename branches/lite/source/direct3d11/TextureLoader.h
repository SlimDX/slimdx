/*
* Copyright (c) 2007-2012 SlimDX Group
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
#undef LoadBitmap	// stupid Win32

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace Direct3D11
	{
		/// <summary>
		/// Provides methods for loading and creating textures from image data.
		/// </summary>
		public ref class TextureLoader sealed
		{
		private:
			TextureLoader() { }

		public:
			/// <summary>
			/// Loads a bitmap image from file and creates a texture from it.
			/// </summary>
			/// <param name="device">The device with which to associate the texture.</param>
			/// <param name="context">A device context used to generate mipmaps for the texture. If <c>null</c>, no mipmaps will be generated.</param>
			/// <param name="fileName">Name of the image file to load.</param>
			/// <returns>The newly created texture containing the loaded image data.</returns>
			static Texture2D^ LoadBitmap(Device^ device, DeviceContext^ context, System::String^ fileName);

			/// <summary>
			/// Loads a bitmap image from file and creates a texture from it.
			/// </summary>
			/// <param name="device">The device with which to associate the texture.</param>
			/// <param name="context">A device context used to generate mipmaps for the texture. If <c>null</c>, no mipmaps will be generated.</param>
			/// <param name="fileName">Name of the image file to load.</param>
			/// <param name="resourceView">When the method completes, contains a newly created resource view for the texture.</param>
			/// <returns>The newly created texture containing the loaded image data.</returns>
			static Texture2D^ LoadBitmap(Device^ device, DeviceContext^ context, System::String^ fileName, [Out] ShaderResourceView^ %resourceView);

			/// <summary>
			/// Loads a bitmap image from a stream and creates a texture from it.
			/// </summary>
			/// <param name="device">The device with which to associate the texture.</param>
			/// <param name="context">A device context used to generate mipmaps for the texture. If <c>null</c>, no mipmaps will be generated.</param>
			/// <param name="data">A stream containing the image data.</param>
			/// <returns>The newly created texture containing the loaded image data.</returns>
			static Texture2D^ LoadBitmap(Device^ device, DeviceContext^ context, System::IO::Stream^ data);

			/// <summary>
			/// Loads a bitmap image from a stream and creates a texture from it.
			/// </summary>
			/// <param name="device">The device with which to associate the texture.</param>
			/// <param name="context">A device context used to generate mipmaps for the texture. If <c>null</c>, no mipmaps will be generated.</param>
			/// <param name="data">A stream containing the image data.</param>
			/// <param name="resourceView">When the method completes, contains a newly created resource view for the texture.</param>
			/// <returns>The newly created texture containing the loaded image data.</returns>
			static Texture2D^ LoadBitmap(Device^ device, DeviceContext^ context, System::IO::Stream^ data, [Out] ShaderResourceView^ %resourceView);

			/// <summary>
			/// Loads a DDS image from file and creates a texture from it.
			/// </summary>
			/// <param name="device">The device with which to associate the texture.</param>
			/// <param name="fileName">Name of the image file to load.</param>
			/// <returns>The newly created texture containing the loaded image data. This can be one of any of the three texture types depending on the image being loaded.</returns>
			static Resource^ LoadDDS(Device^ device, System::String^ fileName);

			/// <summary>
			/// Loads a DDS image from file and creates a texture from it.
			/// </summary>
			/// <param name="device">The device with which to associate the texture.</param>
			/// <param name="fileName">Name of the image file to load.</param>
			/// <param name="resourceView">When the method completes, contains a newly created resource view for the texture.</param>
			/// <returns>The newly created texture containing the loaded image data. This can be one of any of the three texture types depending on the image being loaded.</returns>
			static Resource^ LoadDDS(Device^ device, System::String^ fileName, [Out] ShaderResourceView^ %resourceView);

			/// <summary>
			/// Loads a DDS image from a stream and creates a texture from it.
			/// </summary>
			/// <param name="device">The device with which to associate the texture.</param>
			/// <param name="data">A stream containing the image data.</param>
			/// <returns>The newly created texture containing the loaded image data. This can be one of any of the three texture types depending on the image being loaded.</returns>
			static Resource^ LoadDDS(Device^ device, System::IO::Stream^ data);

			/// <summary>
			/// Loads a DDS image from a stream and creates a texture from it.
			/// </summary>
			/// <param name="device">The device with which to associate the texture.</param>
			/// <param name="data">A stream containing the image data.</param>
			/// <param name="resourceView">When the method completes, contains a newly created resource view for the texture.</param>
			/// <returns>The newly created texture containing the loaded image data. This can be one of any of the three texture types depending on the image being loaded.</returns>
			static Resource^ LoadDDS(Device^ device, System::IO::Stream^ data, [Out] ShaderResourceView^ %resourceView);
		};
	}
}