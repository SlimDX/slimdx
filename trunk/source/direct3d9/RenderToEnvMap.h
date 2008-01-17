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

namespace SlimDX
{
	namespace Direct3D9
	{
		public value class RenderToEnvironmentMapDescription
		{
		public:
			property int Size;
			property int MipLevels;
			property SlimDX::Direct3D9::Format Format;
			property bool DepthStencil;
			property SlimDX::Direct3D9::Format DepthStencilFormat;
		};

		public ref class RenderToEnvironmentMap : BaseObject
		{
			DXOBJECT(ID3DXRenderToEnvMap);

		internal:
			RenderToEnvironmentMap( ID3DXRenderToEnvMap* pointer );

		public:
			RenderToEnvironmentMap( IntPtr pointer );
			RenderToEnvironmentMap( Device^ device, int size, int mipLevels, Format format );
			RenderToEnvironmentMap( Device^ device, int size, int mipLevels, Format format, Format depthStencilFormat );
			virtual ~RenderToEnvironmentMap() { Destruct(); }

			void BeginCube( CubeTexture^ texture );
			void BeginHemisphere( Texture^ positiveZTexture, Texture^ negativeZTexture );
			void BeginParabolic( Texture^ positiveZTexture, Texture^ negativeZTexture );
			void BeginSphere( Texture^ texture );
			void End( Filter mipFilter );
			void Face( CubeMapFace face, Filter mipFilter );

			Device^ GetDevice();
			void OnLostDevice();
			void OnResetDevice();

			property RenderToEnvironmentMapDescription Description { RenderToEnvironmentMapDescription get(); }
		};
	}
}