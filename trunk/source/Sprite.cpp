#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Sprite.h"
#include "Utils.h"

namespace SlimDX
{
namespace Direct3D
{
	Sprite::Sprite( ID3DXSprite* sprite )
	{
		if( sprite == NULL )
			throw gcnew ArgumentNullException( "sprite" );

		m_Sprite = sprite;
		m_Disposed = false;
	}

	Sprite::~Sprite()
	{
		Utils::MarkDisposed( m_Disposed, this );

		m_Sprite->Release();
		m_Sprite = NULL;
	}

	Sprite::!Sprite()
	{
		Utils::ReportNotDisposed( this );
	}
}
}