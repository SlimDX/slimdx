/*
* Copyright (c) 2007 SlimDX Group
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

using namespace System;

namespace SlimDX
{
	namespace Direct3D
	{
		value class DisplayMode;
		ref class Surface;

		public value class RasterStatus
		{
		public:
			bool InVBlank;
			int ScanLine;
		};

		public ref class SwapChain : public DirectXObject
		{
		private:
			IDirect3DSwapChain9* m_SwapChain;

		internal:
			property IDirect3DSwapChain9* InternalPointer
			{
				IDirect3DSwapChain9* get() { return m_SwapChain; }
			}

			property IUnknown* ComPointer
			{
				virtual IUnknown* get() override { return m_SwapChain; }
				virtual void set( IUnknown* value ) override { m_SwapChain = (IDirect3DSwapChain9*) value; }
			}

		public:
			SwapChain( IDirect3DSwapChain9* swapChain );

			property SlimDX::Direct3D::DisplayMode DisplayMode
			{
				SlimDX::Direct3D::DisplayMode get();
			}

			property SlimDX::Direct3D::RasterStatus RasterStatus
			{
				SlimDX::Direct3D::RasterStatus get();
			}

			Device^ GetDevice();
			Surface^ GetBackBuffer( int index );
			void GetFrontBufferData( Surface^ destSurface );

			void Present( SlimDX::Direct3D::Present flags );
		};
	}
}
