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
