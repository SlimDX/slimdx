/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include "../ComObject.h"

#include "../math/Color4.h"
#include "../math/Vector3.h"

#include "Device.h"
#include "Sprite.h"
#include "Texture.h"

#include "Direct3D9Exception.h"

using namespace System;
using namespace System::Drawing;

namespace SlimDX
{
namespace Direct3D9
{
	Sprite::Sprite( SlimDX::Direct3D9::Device^ device )
	{
		ID3DXSprite* sprite;
		
		HRESULT hr = D3DXCreateSprite( device->InternalPointer, &sprite );
		
		if( RECORD_D3D9( hr ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct(sprite);
	}

	Result Sprite::Begin( SpriteFlags flags )
	{
		HRESULT hr = InternalPointer->Begin( static_cast<DWORD>( flags ) );
		return RECORD_D3D9( hr );
	}

	Result Sprite::End()
	{
		HRESULT hr = InternalPointer->End();
		return RECORD_D3D9( hr );
	}

	Result Sprite::Flush()
	{
		HRESULT hr = InternalPointer->Flush();
		return RECORD_D3D9( hr );
	}

	Result Sprite::OnLostDevice()
	{
		HRESULT hr = InternalPointer->OnLostDevice();
		return RECORD_D3D9( hr );
	}

	Result Sprite::OnResetDevice()
	{
		HRESULT hr = InternalPointer->OnResetDevice();
		return RECORD_D3D9( hr );
	}

	SlimDX::Direct3D9::Device^ Sprite::Device::get()
	{
		IDirect3DDevice9* device;

		HRESULT hr = InternalPointer->GetDevice( &device );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return SlimDX::Direct3D9::Device::FromPointer( device );
	}

	Matrix Sprite::Transform::get()
	{
		Matrix result;

		HRESULT hr = InternalPointer->GetTransform( reinterpret_cast<D3DXMATRIX*>( &result ) );
		RECORD_D3D9( hr );

		return result;
	}

	void Sprite::Transform::set( Matrix value )
	{
		HRESULT hr = InternalPointer->SetTransform( reinterpret_cast<const D3DXMATRIX*>( &value ) );
		RECORD_D3D9( hr );
	}

	Result Sprite::SetWorldViewLH( Matrix world, Matrix view )
	{
		HRESULT hr = InternalPointer->SetWorldViewLH( reinterpret_cast<const D3DXMATRIX*>( &world ), reinterpret_cast<const D3DXMATRIX*>( &view ) );
		return RECORD_D3D9( hr );
	}

	Result Sprite::SetWorldViewRH( Matrix world, Matrix view )
	{
		HRESULT hr = InternalPointer->SetWorldViewRH( reinterpret_cast<const D3DXMATRIX*>( &world ), reinterpret_cast<const D3DXMATRIX*>( &view ) );
		return RECORD_D3D9( hr );
	}

	Result Sprite::Draw( Texture^ texture, System::Drawing::Rectangle sourceRect, Vector3 center, Vector3 position, Color4 color )
	{
		RECT rect = { sourceRect.Left, sourceRect.Top, sourceRect.Right, sourceRect.Bottom };

		HRESULT hr = InternalPointer->Draw( texture->InternalPointer, &rect, reinterpret_cast<const D3DXVECTOR3*>( &center ),
			reinterpret_cast<const D3DXVECTOR3*>( &position ), color.ToArgb() );
		return RECORD_D3D9( hr );
	}

	Result Sprite::Draw( Texture^ texture, System::Drawing::Rectangle sourceRect, Color4 color )
	{
		RECT rect = { sourceRect.Left, sourceRect.Top, sourceRect.Right, sourceRect.Bottom };

		HRESULT hr = InternalPointer->Draw( texture->InternalPointer, &rect, NULL, NULL, color.ToArgb() );
		return RECORD_D3D9( hr );
	}

	Result Sprite::Draw( Texture^ texture, Vector3 center, Vector3 position, Color4 color )
	{
		HRESULT hr = InternalPointer->Draw( texture->InternalPointer, NULL, reinterpret_cast<const D3DXVECTOR3*>( &center ),
			reinterpret_cast<const D3DXVECTOR3*>( &position ), color.ToArgb() );
		return RECORD_D3D9( hr );
	}

	Result Sprite::Draw( Texture^ texture, Color4 color )
	{
		HRESULT hr = InternalPointer->Draw( texture->InternalPointer, NULL, NULL, NULL, color.ToArgb() );
		return RECORD_D3D9( hr );
	}
}
}
