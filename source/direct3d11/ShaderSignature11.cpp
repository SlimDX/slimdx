
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

#include <d3dcompiler.h>

#include "../DataStream.h"

#include "Direct3D11Exception.h"
#include "ShaderSignature11.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{
	ShaderSignature::ShaderSignature( const BYTE *data, UINT length )
	{
		ID3D10Blob *blob;

		HRESULT hr = D3D10CreateBlob( length, &blob );
		if( RECORD_D3D11( hr ).IsFailure )
			throw gcnew Direct3D11Exception( Result::Last );

		memcpy( blob->GetBufferPointer(), data, length );
		Construct( blob );
	}

	ShaderSignature::ShaderSignature( array<Byte>^ data )
	{
		ID3D10Blob *blob;

		if( data == nullptr )
			throw gcnew ArgumentNullException( "data" );

		HRESULT hr = D3D10CreateBlob( data->Length, &blob );
		if( RECORD_D3D11( hr ).IsFailure )
			throw gcnew Direct3D11Exception( Result::Last );

		pin_ptr<Byte> pinnedData = &data[0];
		memcpy( blob->GetBufferPointer(), pinnedData, data->Length );

		Construct( blob );
	}

	ShaderSignature^ ShaderSignature::GetInputSignature( ShaderBytecode^ shaderBytecode )
	{
		ID3D10Blob *blob;

		HRESULT hr = D3DGetInputSignatureBlob( shaderBytecode->InternalPointer->GetBufferPointer(), shaderBytecode->InternalPointer->GetBufferSize(), &blob );
		if( RECORD_D3D11( hr ).IsFailure )
			return nullptr;

		return ShaderSignature::FromPointer( blob );
	}

	ShaderSignature^ ShaderSignature::GetOutputSignature( ShaderBytecode^ shaderBytecode )
	{
		ID3D10Blob *blob;

		HRESULT hr = D3DGetOutputSignatureBlob( shaderBytecode->InternalPointer->GetBufferPointer(), shaderBytecode->InternalPointer->GetBufferSize(), &blob );
		if( RECORD_D3D11( hr ).IsFailure )
			return nullptr;

		return ShaderSignature::FromPointer( blob );
	}

	ShaderSignature^ ShaderSignature::GetInputOutputSignature( ShaderBytecode^ shaderBytecode )
	{
		ID3D10Blob *blob;

		HRESULT hr = D3DGetInputAndOutputSignatureBlob( shaderBytecode->InternalPointer->GetBufferPointer(), shaderBytecode->InternalPointer->GetBufferSize(), &blob );
		if( RECORD_D3D11( hr ).IsFailure )
			return nullptr;

		return ShaderSignature::FromPointer( blob );
	}

	DataStream^ ShaderSignature::Data::get()
	{
		return gcnew DataStream( InternalPointer->GetBufferPointer(), InternalPointer->GetBufferSize(), true, true, false );
	}

	int ShaderSignature::GetHashCode()
	{
		return reinterpret_cast<int>( InternalPointer->GetBufferPointer() );
	}
}
}
