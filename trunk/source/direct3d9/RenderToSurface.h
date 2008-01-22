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

using namespace System::IO;
using namespace System::Runtime::InteropServices;

#include "Enums.h"
#include "../Direct3D/Viewport.h"

namespace SlimDX
{
	ref class Surface;

	namespace Direct3D9
	{
		public value class RenderToSurfaceDescription
		{
		public:
			property int Width;
			property int Height;
			property SlimDX::Direct3D9::Format Format;
			property bool DepthStencil;
			property SlimDX::Direct3D9::Format DepthStencilFormat;
		};

		public ref class RenderToSurface : public SlimDXObject
		{
			DXOBJECT(ID3DXRenderToSurface);

		internal:
			/* Unused for now.
			RenderToSurface( ID3DXRenderToSurface* pointer );
			*/

		public:
			RenderToSurface( IntPtr rts );
			RenderToSurface( Device^ device, int width, int height, Format format );
			RenderToSurface( Device^ device, int width, int height, Format format, Format depthStencilFormat );
			~RenderToSurface() { Destruct(); }

			void BeginScene( Surface^ renderSurface, Viewport viewport );
			void EndScene( Filter mipFilter );

			Device^ GetDevice();
			void OnLostDevice();
			void OnResetDevice();

			property RenderToSurfaceDescription Description
			{
				RenderToSurfaceDescription get();
			}
		};
	}
}