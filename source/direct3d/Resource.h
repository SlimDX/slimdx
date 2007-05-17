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
		public enum class ResourceType : Int32
		{
			Surface = D3DRTYPE_SURFACE,
			Volume = D3DRTYPE_VOLUME,
			Texture = D3DRTYPE_TEXTURE,
			VolumeTexture = D3DRTYPE_VOLUMETEXTURE,
			CubeTexture = D3DRTYPE_CUBETEXTURE,
			VertexBuffer = D3DRTYPE_VERTEXBUFFER,
			IndexBuffer = D3DRTYPE_INDEXBUFFER,
		};

		public ref class Resource abstract : public DirectXObject<IDirect3DResource9>
		{
		public:
			Device^ GetDevice();
		};
	}
}
