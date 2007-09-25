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

namespace SlimDX
{
	namespace Direct3D9
	{
		value class DisplayMode;
		ref class Surface;

		public value class RasterStatus
		{
		private:
			bool inVBlank;
            int scanLine;

		public:
			property bool InVBlank
            {
                bool get() { return inVBlank; }
                void set( bool value ) { inVBlank = value; }
            }

            property int ScanLine
            {
                int get() { return scanLine; }
                void set( int value ) { scanLine = value; }
            }
		};

		public ref class SwapChain : public DirectXObject<IDirect3DSwapChain9>
		{
		public:
			SwapChain( IDirect3DSwapChain9* swapChain );
			SwapChain( Device^ device, PresentParameters^ presentParams );
			~SwapChain() { Destruct(); }

			property SlimDX::Direct3D9::DisplayMode DisplayMode
			{
				SlimDX::Direct3D9::DisplayMode get();
			}

			property SlimDX::Direct3D9::RasterStatus RasterStatus
			{
				SlimDX::Direct3D9::RasterStatus get();
			}

			Device^ GetDevice();
			Surface^ GetBackBuffer( int index );
			void GetFrontBufferData( Surface^ destSurface );

			void Present( SlimDX::Direct3D9::Present flags );
		};
	}
}
