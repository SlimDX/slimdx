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

#include "DeviceContext11.h"
#include "DeviceChild11.h"
#include "Enums11.h"
#include "../dxgi/SwapChainDxgi.h"
#include "../dxgi/SurfaceDxgi.h"

namespace SlimDX
{
	namespace Direct3D11
	{
		/// <summary>
		/// A base class for all resource objects.
		/// </summary>
		/// <unmanaged>ID3D11Resource</unmanaged>
		public ref class Resource abstract : public DeviceChild
		{
			COMOBJECT_BASE(ID3D11Resource);

		internal:
			static int GetMipSize( int mipSlice, int baseSliceSize );
			static Resource^ FromPointer( ID3D11Resource* pointer );

		private protected:
			Resource() { }

		public:
			/// <summary>
			/// Returns a DXGI Surface for this resource.
			/// </summary>
			/// <returns>The buffer interface, or <c>null</c> on failure.</returns>
			SlimDX::DXGI::Surface^ AsSurface();

			/// <summary>
			/// Gets a swap chain back buffer.
			/// </summary>
			/// <typeparam name="T">The type of the buffer.</typeparam>
			/// <param name="swapChain">The swap chain to get the buffer from.</param>
			/// <param name="index">The index of the desired buffer.</param>
			/// <returns>The buffer interface, or <c>null</c> on failure.</returns>
			generic< class T > where T : Resource, ref class
			static T FromSwapChain( SlimDX::DXGI::SwapChain^ swapChain, int index );

			/// <summary>
			/// Constructs a new instance of the <see cref="Resource"/> class using the specified pointer to a
			/// previously constructed unmanaged object.
			/// </summary>
			/// <param name="pointer">The unmanaged resource pointer.</param>
			/// <returns>The newly constructed object.</returns>
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
			
			/// <summary>
			/// Calculates a subresource index.
			/// </summary>
			/// <param name="mipSlice">The index of the desired mip slice.</param>
			/// <param name="arraySlice">The index of the desired array slice.</param>
			/// <param name="mipLevels">The total number of mip levels.</param>
			/// <returns>The subresource index (equivalent to mipSlice + (arraySlice * mipLevels)).</returns>
			static int CalculateSubresourceIndex( int mipSlice, int arraySlice, int mipLevels );
		};
	}
};