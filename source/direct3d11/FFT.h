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

#include "../ComObject.h"

#include "../dxgi/Enums.h"

#include "../ComObject.h"

#include "Enums11.h"

namespace SlimDX
{
	namespace Direct3D11
	{
		ref class Device;
		ref class UnorderedAccessView;

		/// <summary>
		/// An object that is bound to a Device.
		/// </summary>
		/// <unmanaged>ID3D11DeviceChild</unmanaged>
		public ref class FFT : public ComObject 
		{
			COMOBJECT_BASE(ID3DX11FFT);

		protected:
			FFT() { }
			
		public:

			/// <summary>
			/// Gets or sets the forward scale of the FFT.
			/// </summary>
			property float ForwardScale
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the inverse scale of the FFT.
			/// </summary>
			property float InverseScale
			{
				float get();
				void set(float value);
			}

			void AttachBuffersAndPrecompute( array<UnorderedAccessView^>^ tempBuffers, array<UnorderedAccessView^>^ precomputeBuffers );

			void ForwardTransform( UnorderedAccessView^ input, UnorderedAccessView^ output );
			UnorderedAccessView^  ForwardTransform( UnorderedAccessView^ input );

			void InverseTransform( UnorderedAccessView^ input, UnorderedAccessView^ output );
			UnorderedAccessView^  InverseTransform( UnorderedAccessView^ input );
		};
	}
};