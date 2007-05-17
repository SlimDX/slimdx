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

#include "../Utils.h"
#include "../DirectXObject.h"
#include "../math/Math.h"

#include "Device.h"
#include "Sprite.h"
#include "Texture.h"

namespace SlimDX
{
namespace Direct3D
{
	Sprite::Sprite( ID3DXSprite* sprite ) : DirectXObject( sprite )
	{
		if( sprite == NULL )
			throw gcnew ArgumentNullException( "sprite" );
	}

	Sprite::Sprite( Device^ device )
	{
		ID3DXSprite* sprite;
		
		HRESULT hr = D3DXCreateSprite( device->InternalPointer, &sprite );
		GraphicsException::CheckHResult( hr );

		m_Pointer = sprite;
	}

	void Sprite::Begin( SpriteFlags flags )
	{
		HRESULT hr = m_Pointer->Begin( (DWORD) flags );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::End()
	{
		HRESULT hr = m_Pointer->End();
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::Flush()
	{
		HRESULT hr = m_Pointer->Flush();
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::OnLostDevice()
	{
		HRESULT hr = m_Pointer->OnLostDevice();
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::OnResetDevice()
	{
		HRESULT hr = m_Pointer->OnResetDevice();
		GraphicsException::CheckHResult( hr );
	}

	Device^ Sprite::GetDevice()
	{
		IDirect3DDevice9* device;

		HRESULT hr = m_Pointer->GetDevice( &device );
		GraphicsException::CheckHResult( hr );

		return gcnew Device( device );
	}

	Matrix Sprite::GetTransform()
	{
		Matrix result;

		HRESULT hr = m_Pointer->GetTransform( (D3DXMATRIX*) &result );
		GraphicsException::CheckHResult( hr );

		return result;
	}

	void Sprite::SetTransform( Matrix transform )
	{
		HRESULT hr = m_Pointer->SetTransform( (const D3DXMATRIX*) &transform );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::SetWorldViewLH( Matrix world, Matrix view )
	{
		HRESULT hr = m_Pointer->SetWorldViewLH( (const D3DXMATRIX*) &world, (const D3DXMATRIX*) &view );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::SetWorldViewRH( Matrix world, Matrix view )
	{
		HRESULT hr = m_Pointer->SetWorldViewRH( (const D3DXMATRIX*) &world, (const D3DXMATRIX*) &view );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::Draw( Texture^ texture, System::Drawing::Rectangle sourceRect, Vector3 center, Vector3 position, int color )
	{
		RECT rect = { sourceRect.Left, sourceRect.Top, sourceRect.Right, sourceRect.Bottom };

		HRESULT hr = m_Pointer->Draw( texture->TexturePointer, &rect, (const D3DXVECTOR3*) &center,
			(const D3DXVECTOR3*) &position, color );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::Draw( Texture^ texture, System::Drawing::Rectangle sourceRect, Vector3 center, Vector3 position, Color color )
	{
		Draw( texture, sourceRect, center, position, color.ToArgb() );
	}

	void Sprite::Draw( Texture^ texture, System::Drawing::Rectangle sourceRect, int color )
	{
		RECT rect = { sourceRect.Left, sourceRect.Top, sourceRect.Right, sourceRect.Bottom };

		HRESULT hr = m_Pointer->Draw( texture->TexturePointer, &rect, NULL, NULL, color );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::Draw( Texture^ texture, System::Drawing::Rectangle sourceRect, Color color )
	{
		Draw( texture, sourceRect, color.ToArgb() );
	}

	void Sprite::Draw( Texture^ texture, Vector3 center, Vector3 position, int color )
	{
		HRESULT hr = m_Pointer->Draw( texture->TexturePointer, NULL, (const D3DXVECTOR3*) &center,
			(const D3DXVECTOR3*) &position, color );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::Draw( Texture^ texture, Vector3 center, Vector3 position, Color color )
	{
		Draw( texture, center, position, color.ToArgb() );
	}

	void Sprite::Draw( Texture^ texture, int color )
	{
		HRESULT hr = m_Pointer->Draw( texture->TexturePointer, NULL, NULL, NULL, color );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::Draw( Texture^ texture, Color color )
	{
		Draw( texture, color.ToArgb() );
	}
}
}
