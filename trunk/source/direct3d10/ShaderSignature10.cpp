
/*
* Copyright (c) 2007-2010 SlimDX Group
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
#include "stdafx.h"

#include <d3dcompiler.h>

#include "../DataStream.h"

#include "Direct3D10Exception.h"
#include "ShaderSignature10.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{
	ShaderSignature::ShaderSignature( const BYTE* data, UINT length )
	: m_Buffer( data )
	, m_Length( length )
	{
	}
	
	const BYTE* ShaderSignature::GetBufferPointer() 
	{
		return m_Buffer;
	}
	
	UINT ShaderSignature::GetBufferSize() 
	{
		return m_Length;
	}

	ShaderSignature^ ShaderSignature::GetInputSignature( ShaderBytecode^ shaderBytecode )
	{
		ID3D10Blob *blob;

		HRESULT hr = D3DGetInputSignatureBlob( shaderBytecode->InternalPointer->GetBufferPointer(), shaderBytecode->InternalPointer->GetBufferSize(), &blob );
		if( RECORD_D3D10( hr ).IsFailure )
			return nullptr;
		
		ShaderSignature^ result = gcnew ShaderSignature( reinterpret_cast<const BYTE*>( blob->GetBufferPointer() ), blob->GetBufferSize() );
		blob->Release();
		return result;
	}

	ShaderSignature^ ShaderSignature::GetOutputSignature( ShaderBytecode^ shaderBytecode )
	{
		ID3D10Blob *blob;

		HRESULT hr = D3DGetOutputSignatureBlob( shaderBytecode->InternalPointer->GetBufferPointer(), shaderBytecode->InternalPointer->GetBufferSize(), &blob );
		if( RECORD_D3D10( hr ).IsFailure )
			return nullptr;

		ShaderSignature^ result = gcnew ShaderSignature( reinterpret_cast<const BYTE*>( blob->GetBufferPointer() ), blob->GetBufferSize() );
		blob->Release();
		return result;
	}

	ShaderSignature^ ShaderSignature::GetInputOutputSignature( ShaderBytecode^ shaderBytecode )
	{
		ID3D10Blob *blob;

		HRESULT hr = D3DGetInputAndOutputSignatureBlob( shaderBytecode->InternalPointer->GetBufferPointer(), shaderBytecode->InternalPointer->GetBufferSize(), &blob );
		if( RECORD_D3D10( hr ).IsFailure )
			return nullptr;

		ShaderSignature^ result = gcnew ShaderSignature( reinterpret_cast<const BYTE*>( blob->GetBufferPointer() ), blob->GetBufferSize() );
		blob->Release();
		return result;
	}

	DataStream^ ShaderSignature::Data::get()
	{
		return gcnew DataStream( (void*)m_Buffer, m_Length, true, true, false );
	}

	int ShaderSignature::GetHashCode()
	{
		return reinterpret_cast<int>( m_Buffer );
	}
}
}
