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

#include "IResettable.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		public value class RenderToEnvironmentMapDescription : System::IEquatable<RenderToEnvironmentMapDescription>
		{
		public:
			property int Size;
			property int MipLevels;
			property SlimDX::Direct3D9::Format Format;
			property bool DepthStencil;
			property SlimDX::Direct3D9::Format DepthStencilFormat;

			static bool operator == ( RenderToEnvironmentMapDescription left, RenderToEnvironmentMapDescription right );
			static bool operator != ( RenderToEnvironmentMapDescription left, RenderToEnvironmentMapDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( RenderToEnvironmentMapDescription other );
			static bool Equals( RenderToEnvironmentMapDescription% value1, RenderToEnvironmentMapDescription% value2 );
		};

		public ref class RenderToEnvironmentMap : ComObject, IResettable
		{
			COMOBJECT(ID3DXRenderToEnvMap, RenderToEnvironmentMap);

		public:
			RenderToEnvironmentMap( SlimDX::Direct3D9::Device^ device, int size, int mipLevels, Format format );
			RenderToEnvironmentMap( SlimDX::Direct3D9::Device^ device, int size, int mipLevels, Format format, Format depthStencilFormat );
			static RenderToEnvironmentMap^ FromPointer( System::IntPtr pointer );

			property SlimDX::Direct3D9::Device^ Device
			{
				SlimDX::Direct3D9::Device^ get();
			}

			Result BeginCube( CubeTexture^ texture );
			Result BeginHemisphere( Texture^ positiveZTexture, Texture^ negativeZTexture );
			Result BeginParabolic( Texture^ positiveZTexture, Texture^ negativeZTexture );
			Result BeginSphere( Texture^ texture );
			Result End( Filter mipFilter );
			Result Face( CubeMapFace face, Filter mipFilter );

			virtual Result OnLostDevice();
			virtual Result OnResetDevice();

			property RenderToEnvironmentMapDescription Description { RenderToEnvironmentMapDescription get(); }
		};
	}
}