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

#include "../BaseObject.h"
#include "../math/Math.h"

#include "Device.h"
#include "Sprite.h"
#include "Texture.h"

namespace SlimDX
{
namespace Direct3D9
{
	Sprite::Sprite( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	Sprite::Sprite( ID3DXSprite* sprite )
	{
		if( sprite == NULL )
			throw gcnew ArgumentNullException( "sprite" );

		Construct(sprite);
	}

	Sprite::Sprite( Device^ device )
	{
		ID3DXSprite* sprite;
		
		HRESULT hr = D3DXCreateSprite( device->InternalPointer, &sprite );
		GraphicsException::CheckHResult( hr );

		Construct(sprite);
	}

	void Sprite::Begin( SpriteFlags flags )
	{
		HRESULT hr = InternalPointer->Begin( static_cast<DWORD>( flags ) );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::End()
	{
		HRESULT hr = InternalPointer->End();
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::Flush()
	{
		HRESULT hr = InternalPointer->Flush();
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::OnLostDevice()
	{
		HRESULT hr = InternalPointer->OnLostDevice();
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::OnResetDevice()
	{
		HRESULT hr = InternalPointer->OnResetDevice();
		GraphicsException::CheckHResult( hr );
	}

	Device^ Sprite::GetDevice()
	{
		IDirect3DDevice9* device;

		HRESULT hr = InternalPointer->GetDevice( &device );
		GraphicsException::CheckHResult( hr );

		return gcnew Device( device );
	}

	Matrix Sprite::Transform::get()
	{
		Matrix result;

		HRESULT hr = InternalPointer->GetTransform( reinterpret_cast<D3DXMATRIX*>( &result ) );
		GraphicsException::CheckHResult( hr );

		return result;
	}

	void Sprite::Transform::set( Matrix value )
	{
		HRESULT hr = InternalPointer->SetTransform( reinterpret_cast<const D3DXMATRIX*>( &value ) );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::SetWorldViewLH( Matrix world, Matrix view )
	{
		HRESULT hr = InternalPointer->SetWorldViewLH( reinterpret_cast<const D3DXMATRIX*>( &world ), reinterpret_cast<const D3DXMATRIX*>( &view ) );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::SetWorldViewRH( Matrix world, Matrix view )
	{
		HRESULT hr = InternalPointer->SetWorldViewRH( reinterpret_cast<const D3DXMATRIX*>( &world ), reinterpret_cast<const D3DXMATRIX*>( &view ) );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::Draw( Texture^ texture, System::Drawing::Rectangle sourceRect, Vector3 center, Vector3 position, int color )
	{
		RECT rect = { sourceRect.Left, sourceRect.Top, sourceRect.Right, sourceRect.Bottom };

		HRESULT hr = InternalPointer->Draw( texture->TexturePointer, &rect, reinterpret_cast<const D3DXVECTOR3*>( &center ),
			reinterpret_cast<const D3DXVECTOR3*>( &position ), color );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::Draw( Texture^ texture, System::Drawing::Rectangle sourceRect, Vector3 center, Vector3 position, Color color )
	{
		Draw( texture, sourceRect, center, position, color.ToArgb() );
	}

	void Sprite::Draw( Texture^ texture, System::Drawing::Rectangle sourceRect, int color )
	{
		RECT rect = { sourceRect.Left, sourceRect.Top, sourceRect.Right, sourceRect.Bottom };

		HRESULT hr = InternalPointer->Draw( texture->TexturePointer, &rect, NULL, NULL, color );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::Draw( Texture^ texture, System::Drawing::Rectangle sourceRect, Color color )
	{
		Draw( texture, sourceRect, color.ToArgb() );
	}

	void Sprite::Draw( Texture^ texture, Vector3 center, Vector3 position, int color )
	{
		HRESULT hr = InternalPointer->Draw( texture->TexturePointer, NULL, reinterpret_cast<const D3DXVECTOR3*>( &center ),
			reinterpret_cast<const D3DXVECTOR3*>( &position ), color );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::Draw( Texture^ texture, Vector3 center, Vector3 position, Color color )
	{
		Draw( texture, center, position, color.ToArgb() );
	}

	void Sprite::Draw( Texture^ texture, int color )
	{
		HRESULT hr = InternalPointer->Draw( texture->TexturePointer, NULL, NULL, NULL, color );
		GraphicsException::CheckHResult( hr );
	}

	void Sprite::Draw( Texture^ texture, Color color )
	{
		Draw( texture, color.ToArgb() );
	}
}
}
