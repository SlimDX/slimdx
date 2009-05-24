
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
#include "stdafx.h"

#include "../../external/d3dcompiler.h"

#include "Direct3D10Exception.h"
#include "ShaderSignature.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{
	ShaderSignature::ShaderSignature( ID3D10Blob *blob )
	{
		m_Buffer = NULL;

		this->blob = blob;
	}

	ShaderSignature::ShaderSignature( const void* buffer, long length )
	{
		m_Buffer = buffer;
		m_Length = length;
	}

	ShaderSignature::~ShaderSignature()
	{
		Destruct();
	}

	ShaderSignature::!ShaderSignature()
	{
		Destruct();
	}

	void ShaderSignature::Destruct()
	{
		if( blob != NULL )
			blob->Release();

		blob = NULL;
	}

	int ShaderSignature::GetHashCode()
	{
		return reinterpret_cast<int>( Buffer );
	}

	const void *ShaderSignature::Buffer::get()
	{
		if( m_Buffer == NULL )
			return blob->GetBufferPointer();
		else
			return m_Buffer;
	}

	long ShaderSignature::Length::get()
	{
		if( m_Buffer == NULL )
			return static_cast<long>( blob->GetBufferSize() );
		else
			return m_Length;
	}

	ShaderSignature^ ShaderSignature::GetInputSignature( ShaderBytecode^ shaderBytecode )
	{
		ID3D10Blob *blob;

		HRESULT hr = D3DGetInputSignatureBlob( shaderBytecode->Buffer, shaderBytecode->Length, &blob );
		if( RECORD_D3D10( hr ).IsFailure )
			return nullptr;

		return gcnew ShaderSignature( blob );
	}

	ShaderSignature^ ShaderSignature::GetOutputSignature( ShaderBytecode^ shaderBytecode )
	{
		ID3D10Blob *blob;

		HRESULT hr = D3DGetOutputSignatureBlob( shaderBytecode->Buffer, shaderBytecode->Length, &blob );
		if( RECORD_D3D10( hr ).IsFailure )
			return nullptr;

		return gcnew ShaderSignature( blob );
	}

	ShaderSignature^ ShaderSignature::GetInputOutputSignature( ShaderBytecode^ shaderBytecode )
	{
		ID3D10Blob *blob;

		HRESULT hr = D3DGetInputAndOutputSignatureBlob( shaderBytecode->Buffer, shaderBytecode->Length, &blob );
		if( RECORD_D3D10( hr ).IsFailure )
			return nullptr;

		return gcnew ShaderSignature( blob );
	}
}
}
