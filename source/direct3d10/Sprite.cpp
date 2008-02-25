/*
* Copyright (c) 2007-2008 SlimDX Group
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

#include <d3d10.h>
#include <d3dx10.h>

#include "../StackAlloc.h"

#include "Direct3D10Exception.h"

#include "Sprite.h"
#include "Device.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{
	Sprite::Sprite( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	Sprite::Sprite( ID3DX10Sprite* sprite )
	{
		if( sprite == NULL )
			throw gcnew ArgumentNullException( "sprite" );

		Construct(sprite);
	}

	Sprite::Sprite( Device^ device, int bufferSize )
	{
		ID3DX10Sprite* sprite;
		
		HRESULT hr = D3DX10CreateSprite( device->InternalPointer, bufferSize, &sprite );
		RECORD_D3D10( hr );

		Construct(sprite);
	}
	
	Matrix Sprite::ViewTransform::get()
	{
		D3DXMATRIX matrix;
		HRESULT hr = InternalPointer->GetViewTransform( &matrix );
		RECORD_D3D10( hr );
		return Matrix::FromD3DXMATRIX( matrix );
	}

	void Sprite::ViewTransform::set( Matrix value )
	{
		HRESULT hr = InternalPointer->SetViewTransform( reinterpret_cast<D3DXMATRIX*>( &value ) );
		RECORD_D3D10( hr );
	}

	Matrix Sprite::ProjectionTransform::get()
	{
		D3DXMATRIX matrix;
		HRESULT hr = InternalPointer->GetProjectionTransform( &matrix );
		RECORD_D3D10( hr );
		return Matrix::FromD3DXMATRIX( matrix );
	}

	void Sprite::ProjectionTransform::set( Matrix value )
	{
		HRESULT hr = InternalPointer->SetProjectionTransform( reinterpret_cast<D3DXMATRIX*>( &value ) );
		RECORD_D3D10( hr );
	}

	void Sprite::Begin( SpriteFlags flags )
	{
		HRESULT hr = InternalPointer->Begin( static_cast<DWORD>( flags ) );
		RECORD_D3D10( hr );
	}

	void Sprite::End()
	{
		HRESULT hr = InternalPointer->End();
		RECORD_D3D10( hr );
	}

	void Sprite::Flush()
	{
		HRESULT hr = InternalPointer->Flush();
		RECORD_D3D10( hr );
	}

	void Sprite::DrawBuffered( array<SpriteInstance^>^ instances )
	{
		stack_vector<D3DX10_SPRITE> nativeInstances( instances->Length );
		for( int instanceIndex = 0; instanceIndex < instances->Length; ++instanceIndex )
			instances[instanceIndex]->ToNativeObject( nativeInstances[instanceIndex] );
		HRESULT hr = InternalPointer->DrawSpritesBuffered( &nativeInstances[0], instances->Length );
		RECORD_D3D10( hr );
	}

	void Sprite::DrawImmediate( array<SpriteInstance^>^ instances )
	{
		stack_vector<D3DX10_SPRITE> nativeInstances( instances->Length );
		for( int instanceIndex = 0; instanceIndex < instances->Length; ++instanceIndex )
			instances[instanceIndex]->ToNativeObject( nativeInstances[instanceIndex] );
		HRESULT hr = InternalPointer->DrawSpritesImmediate( &nativeInstances[0], instances->Length, sizeof(D3DX10_SPRITE), 0 );
		RECORD_D3D10( hr );
	}
}
}
