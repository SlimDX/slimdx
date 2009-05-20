#include "stdafx.h"
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

#include <vector>

#include "Buffer.h"
#include "SamplerState.h"
#include "ShaderResourceView.h"
#include "PixelShaderWrapper.h"
#include "PixelShader10.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{ 
	PixelShaderWrapper::PixelShaderWrapper( ID3D10Device* device )
	{
		if( device == 0 )
			throw gcnew ArgumentNullException( "device" );
		m_Device = device;
	}

	void PixelShaderWrapper::Set( PixelShader^ shader )
	{
		m_Device->PSSetShader( shader == nullptr ? 0 : shader->InternalPointer );
	}

	PixelShader^ PixelShaderWrapper::Get()
	{
		ID3D10PixelShader* shader = 0;
		m_Device->PSGetShader( &shader );

		return shader == 0 ? nullptr : PixelShader::FromPointer( shader );
	}

	array<Buffer^>^ PixelShaderWrapper::GetConstantBuffers( int startSlot, int count )
	{
		array<Buffer^>^ buffers = gcnew array<Buffer^>( count );
		std::vector<ID3D10Buffer*> results( count );

		m_Device->PSGetConstantBuffers( startSlot, count, &results[0] );

		for( int i = 0; i < count; i++ )
			buffers[i] = Buffer::FromPointer( results[i] );

		return buffers;
	}

	array<SamplerState^>^ PixelShaderWrapper::GetSamplers( int startSlot, int count )
	{
		array<SamplerState^>^ samplers = gcnew array<SamplerState^>( count );
		std::vector<ID3D10SamplerState*> results( count );

		m_Device->PSGetSamplers( startSlot, count, &results[0] );

		for( int i = 0; i < count; i++ )
			samplers[i] = SamplerState::FromPointer( results[i] );

		return samplers;
	}

	array<ShaderResourceView^>^ PixelShaderWrapper::GetShaderResources( int startSlot, int count )
	{
		array<ShaderResourceView^>^ resources = gcnew array<ShaderResourceView^>( count );
		std::vector<ID3D10ShaderResourceView*> results( count );

		m_Device->PSGetShaderResources( startSlot, count, &results[0] );

		for( int i = 0; i < count; i++ )
			resources[i] = ShaderResourceView::FromPointer( results[i] );

		return resources;
	}

	void PixelShaderWrapper::SetConstantBuffers( array<Buffer^>^ constantBuffers, int startSlot, int count )
	{
		if( count > constantBuffers->Length )
			throw gcnew ArgumentOutOfRangeException( "count" );

		std::vector<ID3D10Buffer*> input( count );
		for( int i = 0; i < count; i++ )
			input[i] = constantBuffers[i]->InternalPointer;

		m_Device->PSSetConstantBuffers( startSlot, count, &input[0] );
	}

	void PixelShaderWrapper::SetSamplers( array<SamplerState^>^ samplers, int startSlot, int count )
	{
		if( count > samplers->Length )
			throw gcnew ArgumentOutOfRangeException( "count" );

		std::vector<ID3D10SamplerState*> input( count );
		for( int i = 0; i < count; i++ )
			input[i] = samplers[i]->InternalPointer;

		m_Device->PSSetSamplers( startSlot, count, &input[0] );
	}

	void PixelShaderWrapper::SetShaderResources( array<ShaderResourceView^>^ resourceViews, int startSlot, int count )
	{
		if( count > resourceViews->Length )
			throw gcnew ArgumentOutOfRangeException( "count" );

		std::vector<ID3D10ShaderResourceView*> input( count );
		for( int i = 0; i < count; i++ )
			input[i] = resourceViews[i]->InternalPointer;

		m_Device->PSSetShaderResources( startSlot, count, &input[0] );
	}
}
}
