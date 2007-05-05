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

#include "DirectXObject.h"

namespace SlimDX
{
	namespace Direct3D
	{
		[Flags]
		public enum class SpriteFlags : Int32
		{
			None = 0,
			DoNotSaveState = D3DXSPRITE_DONOTSAVESTATE,
			DoNotModifyRenderState = D3DXSPRITE_DONOTMODIFY_RENDERSTATE,
			ObjectSpace = D3DXSPRITE_OBJECTSPACE,
			Billboard = D3DXSPRITE_BILLBOARD,
			AlphaBlend = D3DXSPRITE_ALPHABLEND,
			Texture = D3DXSPRITE_SORT_TEXTURE,
			SortDepthFrontToBack = D3DXSPRITE_SORT_DEPTH_FRONTTOBACK,
			SortDepthBackToFront = D3DXSPRITE_SORT_DEPTH_BACKTOFRONT,
		};

		public ref class Sprite : public DirectXObject
		{
		private:
			ID3DXSprite* m_Sprite;

		internal:
			property ID3DXSprite* InternalPointer
			{
				ID3DXSprite* get() { return m_Sprite; }
			}

			property IUnknown* ComPointer
			{
				virtual IUnknown* get() override { return m_Sprite; }
				virtual void set( IUnknown* value ) override { m_Sprite = (ID3DXSprite*) value; }
			}

		public:
			Sprite( ID3DXSprite* sprite );
			Sprite( Device^ device );

			void Begin( SpriteFlags flags );
			void End();
			void Flush();

			void OnLostDevice();
			void OnResetDevice();

			void SetTransform( Matrix transform );
			void SetWorldViewLH( Matrix world, Matrix view );
			void SetWorldViewRH( Matrix world, Matrix view );
		};
	}
}
