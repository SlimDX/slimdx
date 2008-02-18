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

#include "EffectConstantBuffer.h"
//#include "Direct3D10ErrorHandler.h"

#include "Buffer.h"
#include "ShaderResourceView.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	/// 
	EffectConstantBuffer::EffectConstantBuffer( ID3D10EffectConstantBuffer* variable ) : EffectVariable( variable )
	{
	}
	
	/// <summary>
	/// Gets a constant buffer.
	/// </summary>
	Buffer^ EffectConstantBuffer::GetConstantBuffer()
	{
		ID3D10Buffer* buffer = 0;
		HRESULT hr = static_cast<ID3D10EffectConstantBuffer*>( Pointer )->GetConstantBuffer( &buffer );
		Result::Record( hr );
		
		if( buffer == 0 )
			return nullptr;
		return gcnew Buffer( buffer );
	}

	/// <summary>
	/// Sets a constant buffer.
	/// </summary>
	/// <param name="buffer">The buffer to set.</param>
	void EffectConstantBuffer::SetConstantBuffer( Buffer^ buffer )
	{
		HRESULT hr = static_cast<ID3D10EffectConstantBuffer*>( Pointer )->SetConstantBuffer( static_cast<ID3D10Buffer*>( buffer->InternalPointer ) );
		Result::Record( hr );
	}
	
	/// <summary>
	/// Gets a texture buffer.
	/// </summary>
	ShaderResourceView^ EffectConstantBuffer::GetTextureBuffer()
	{
		ID3D10ShaderResourceView* buffer = 0;
		HRESULT hr = static_cast<ID3D10EffectConstantBuffer*>( Pointer )->GetTextureBuffer( &buffer );
		Result::Record( hr );
		
		if( buffer == 0 )
			return nullptr;
		return gcnew ShaderResourceView( buffer );
	}

	/// <summary>
	/// Sets a texture buffer.
	/// </summary>
	/// <param name="buffer">The buffer to set.</param>
	void EffectConstantBuffer::SetTextureBuffer( ShaderResourceView^ buffer )
	{
		HRESULT hr = static_cast<ID3D10EffectConstantBuffer*>( Pointer )->SetTextureBuffer( static_cast<ID3D10ShaderResourceView*>( buffer->InternalPointer ) );
		Result::Record( hr );
	}
}
}
