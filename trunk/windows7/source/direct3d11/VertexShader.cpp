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
#include <vcclr.h>

#include "../ComObject.h"

#include "DeviceChild.h"
#include "VertexShader.h"
#include "Device.h"
#include "Direct3D11Exception.h"
#include "ShaderBlob.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{ 
	VertexShader::VertexShader( ID3D11VertexShader* pointer )
	{
		Construct( pointer );
	}
	
	VertexShader::VertexShader( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	VertexShader^ VertexShader::CompileFromFile( SlimDX::Direct3D11::Device^ device, System::String^ fileName, System::String^ entryPoint, System::String^ profile, [Out] ShaderBlob^ %shaderBlob, [Out] String^ %compilationErrors )
	{
		pin_ptr<const wchar_t> pinnedFileName = PtrToStringChars( fileName );
		array<unsigned char>^ entryBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( entryPoint );
		pin_ptr<unsigned char> pinnedEntry = &entryBytes[ 0 ];
		array<unsigned char>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<unsigned char> pinnedProfile = &profileBytes[ 0 ];

		ID3D10Blob* bytecodeBlob = 0;
		ID3D10Blob* errorBlob = 0;
		HRESULT hr = D3DX11CompileFromFile( 
			pinnedFileName, 
			0, 
			0, 
			reinterpret_cast<LPCSTR>( pinnedEntry ), 
			reinterpret_cast<LPCSTR>( pinnedProfile ), 
			0, 
			0, 
			0, 
			&bytecodeBlob, 
			&errorBlob, 
			0
			);

		if( errorBlob != 0 )
		{
			compilationErrors = gcnew String( reinterpret_cast<const char*>( errorBlob->GetBufferPointer() ) );
			errorBlob->Release();
		}
		else
		{
			compilationErrors = String::Empty;
		}

		if (FAILED(hr))
		{
			RECORD_D3D11( hr );
			return nullptr;
		}

		ID3D11VertexShader* shader = 0;
		hr = device->InternalPointer->CreateVertexShader(bytecodeBlob->GetBufferPointer(), bytecodeBlob->GetBufferSize(), 0, &shader);

		shaderBlob = ShaderBlob::FromPointer(bytecodeBlob);

		RECORD_D3D11( hr );
		if (shader == NULL)
		{
			return nullptr;
		}
		return FromPointer( shader );
	}
}
}
