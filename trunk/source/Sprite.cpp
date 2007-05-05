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

	void Sprite::OnLostDevice()
	{
		HRESULT hr = m_Sprite->OnLostDevice();
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::OnResetDevice()
	{
		HRESULT hr = m_Sprite->OnResetDevice();
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::SetTransform( Matrix transform )
	{
		HRESULT hr = m_Sprite->SetTransform( (const D3DXMATRIX*) &transform );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::SetWorldViewLH( Matrix world, Matrix view )
	{
		HRESULT hr = m_Sprite->SetWorldViewLH( (const D3DXMATRIX*) &world, (const D3DXMATRIX*) &view );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::SetWorldViewRH( Matrix world, Matrix view )
	{
		HRESULT hr = m_Sprite->SetWorldViewRH( (const D3DXMATRIX*) &world, (const D3DXMATRIX*) &view );
		GraphicsException::CheckHResult( hr );
	}
}
}