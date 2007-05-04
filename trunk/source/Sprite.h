#pragma once

using namespace System;

#include "DirectXObject.h"

namespace SlimDX
{
	namespace Direct3D
	{
		public ref class Sprite : public DirectXObject
		{
		private:
			ID3DXSprite* m_Sprite;
			bool m_Disposed;

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
		};
	}
}
