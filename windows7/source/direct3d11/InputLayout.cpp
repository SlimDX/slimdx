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

#include <d3d11.h>

#include "Direct3D11Exception.h"

#include "Device.h"
#include "InputLayout.h"
#include "ShaderBytecode.h"
#include "ShaderBlob.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{ 
	InputLayout::InputLayout( ID3D11InputLayout* pointer )
	{
		Construct( pointer );
	}
	
	InputLayout::InputLayout( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	InputLayout::InputLayout( SlimDX::Direct3D11::Device^ device, array<InputElement>^ elements, ShaderSignature^ shaderSignature )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
		if( elements == nullptr )
			throw gcnew ArgumentNullException( "elements" );
		if( shaderSignature == nullptr )
			throw gcnew ArgumentNullException( "shaderSignature" );
				
		D3D11_INPUT_ELEMENT_DESC nativeElements[D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT];
		for( int i = 0; i < elements->Length; ++i )
			nativeElements[i] = elements[i].CreateNativeVersion();
			
		ID3D11InputLayout* layout = 0;
		HRESULT hr = device->InternalPointer->CreateInputLayout( nativeElements, elements->Length, shaderSignature->Buffer,
			static_cast<SIZE_T>( shaderSignature->Length ), &layout );

		for( int i = 0; i < elements->Length; i++ )
			Utilities::FreeNativeString( nativeElements[i].SemanticName );

		if( RECORD_D3D11( hr ).IsFailure )
			throw gcnew Direct3D11Exception( Result::Last );

		Construct( layout );
	}


	InputLayout::InputLayout( SlimDX::Direct3D11::Device^ device, array<InputElement>^ elements, ShaderBlob^ shaderBlob )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
		if( elements == nullptr )
			throw gcnew ArgumentNullException( "elements" );
		if( shaderBlob == nullptr )
			throw gcnew ArgumentNullException( "shaderBlob" );
				
		D3D11_INPUT_ELEMENT_DESC nativeElements[D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT];
		for( int i = 0; i < elements->Length; ++i )
			nativeElements[i] = elements[i].CreateNativeVersion();
			
		ID3D11InputLayout* layout = 0;
		HRESULT hr = device->InternalPointer->CreateInputLayout( nativeElements, elements->Length, shaderBlob->InternalPointer->GetBufferPointer(),
			static_cast<SIZE_T>( shaderBlob->InternalPointer->GetBufferSize() ), &layout );

		for( int i = 0; i < elements->Length; i++ )
			Utilities::FreeNativeString( nativeElements[i].SemanticName );

		if( RECORD_D3D11( hr ).IsFailure )
			throw gcnew Direct3D11Exception( Result::Last );

		Construct( layout );
	}
}
}
