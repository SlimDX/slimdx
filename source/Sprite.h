#pragma once

using namespace System;

namespace SlimDX
{
	namespace Direct3D
	{
		public ref class Sprite
		{
		private:
			ID3DXSprite* m_Sprite;
			bool m_Disposed;

		internal:
			property ID3DXSprite* InternalPointer
			{
				ID3DXSprite* get() { return m_Sprite; }
			}

		public:
			Sprite( ID3DXSprite* sprite );
			~Sprite();
			!Sprite();
		};
	}
}
