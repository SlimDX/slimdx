#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Device.h"
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
	}

	Sprite::Sprite( Device^ device )
	{
		ID3DXSprite* sprite;
		
		HRESULT hr = D3DXCreateSprite( device->InternalPointer, &sprite );
		GraphicsException::CheckHResult( hr );

		m_Sprite = sprite;
	}

	void Sprite::Begin( SpriteFlags flags )
	{
		HRESULT hr = m_Sprite->Begin( (DWORD) flags );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::End()
	{
		HRESULT hr = m_Sprite->End();
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::Flush()
	{
		HRESULT hr = m_Sprite->Flush();
		GraphicsException::CheckHResult( hr );
	}
}
}