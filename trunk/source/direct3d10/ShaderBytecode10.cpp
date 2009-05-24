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
#include "ShaderBytecode10.h"

using namespace System;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace Direct3D10
{
	ShaderBytecode::ShaderBytecode( ID3D10Blob *blob )
	{
		m_Buffer = NULL;

		this->blob = blob;
	}

	ShaderBytecode::ShaderBytecode( const void* buffer, long length )
	{
		m_Buffer = buffer;
		m_Length = length;
	}

	ShaderBytecode::~ShaderBytecode()
	{
		Destruct();
	}

	ShaderBytecode::!ShaderBytecode()
	{
		Destruct();
	}

	void ShaderBytecode::Destruct()
	{
		if( blob != NULL )
			blob->Release();

		blob = NULL;
	}

	int ShaderBytecode::GetHashCode()
	{
		return reinterpret_cast<int>( Buffer );
	}

	const void *ShaderBytecode::Buffer::get()
	{
		if( m_Buffer == NULL )
			return blob->GetBufferPointer();
		else
			return m_Buffer;
	}

	long ShaderBytecode::Length::get()
	{
		if( m_Buffer == NULL )
			return static_cast<long>( blob->GetBufferSize() );
		else
			return m_Length;
	}

	ShaderBytecode^ ShaderBytecode::Compile( String^ shaderSource, String^ entryPoint, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags )
	{
		String^ compilationErrors;
		return Compile( Encoding::ASCII->GetBytes( shaderSource ), entryPoint, profile, shaderFlags, effectFlags, nullptr, nullptr, compilationErrors );
	}

	ShaderBytecode^ ShaderBytecode::Compile( String^ shaderSource, String^ entryPoint, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, array<ShaderMacro>^ defines, Include^ include )
	{
		String^ compilationErrors;
		return Compile( Encoding::ASCII->GetBytes( shaderSource ), entryPoint, profile, shaderFlags, effectFlags, defines, include, compilationErrors );
	}
	
	ShaderBytecode^ ShaderBytecode::Compile( String^ shaderSource, String^ entryPoint, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, array<ShaderMacro>^ defines, Include^ include, [Out] String^ %compilationErrors )
	{
		return Compile( Encoding::ASCII->GetBytes( shaderSource ), entryPoint, profile, shaderFlags, effectFlags, defines, include, compilationErrors );
	}

	ShaderBytecode^ ShaderBytecode::Compile( array<Byte>^ shaderSource, String^ entryPoint, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags )
	{
		String^ compilationErrors;
		return Compile( shaderSource, entryPoint, profile, shaderFlags, effectFlags, nullptr, nullptr, compilationErrors );
	}

	ShaderBytecode^ ShaderBytecode::Compile( array<Byte>^ shaderSource, String^ entryPoint, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, array<ShaderMacro>^ defines, Include^ include )
	{
		String^ compilationErrors;
		return Compile( shaderSource, entryPoint, profile, shaderFlags, effectFlags, defines, include, compilationErrors );
	}

	ShaderBytecode^ ShaderBytecode::Compile( array<Byte>^ shaderSource, String^ entryPoint, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, array<ShaderMacro>^ defines, Include^ include, [Out] String^ %compilationErrors )
	{
		ID3D10Blob *code;
		ID3D10Blob *errors;
		pin_ptr<Byte> pinnedSource = &shaderSource[0];

		array<Byte>^ functionBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( entryPoint );
		pin_ptr<Byte> pinnedFunction = &functionBytes[0];
		array<Byte>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<Byte> pinnedProfile = &profileBytes[0];

		IncludeShim includeShim = IncludeShim( include );
		ID3D10Include* includePtr = NULL;
		if( include != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		std::vector<D3D10_SHADER_MACRO> macros = ShaderMacro::Marshal( defines, handles );
		D3D10_SHADER_MACRO* macrosPtr = macros.size() > 0 ? &macros[0] : NULL;

		HRESULT hr = D3DCompile( pinnedSource, shaderSource->Length, NULL, macrosPtr, includePtr, 
			reinterpret_cast<LPCSTR>( pinnedFunction ), reinterpret_cast<LPCSTR>( pinnedProfile ),
			static_cast<UINT>( shaderFlags ), static_cast<UINT>( effectFlags ), &code, &errors );

		ShaderMacro::Unmarshal( macros, handles );

		String^ compilationErrorsLocal = Utilities::BlobToString( errors );
		compilationErrors = compilationErrorsLocal;

		if( RECORD_D3D10_EX( hr, ExceptionDataKey, compilationErrors ).IsFailure )
			return nullptr;

		if( code == NULL )
			return nullptr;

		return gcnew ShaderBytecode( code );
	}

	ShaderBytecode^ ShaderBytecode::CompileFromFile( String^ fileName, String^ entryPoint, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags )
	{
		String^ compilationErrors;
		return CompileFromFile( fileName, entryPoint, profile, shaderFlags, effectFlags, nullptr, nullptr, compilationErrors );
	}

	ShaderBytecode^ ShaderBytecode::CompileFromFile( String^ fileName, String^ entryPoint, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, array<ShaderMacro>^ defines, Include^ include )
	{
		String^ compilationErrors;
		return CompileFromFile( fileName, entryPoint, profile, shaderFlags, effectFlags, defines, include, compilationErrors );
	}

	ShaderBytecode^ ShaderBytecode::CompileFromFile( String^ fileName, String^ entryPoint, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, array<ShaderMacro>^ defines, Include^ include, [Out] String^ %compilationErrors )
	{
		ID3D10Blob *code;
		ID3D10Blob *errors;

		array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( fileName );
		pin_ptr<Byte> pinnedName = &nameBytes[0];
		array<Byte>^ functionBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( entryPoint );
		pin_ptr<Byte> pinnedFunction = &functionBytes[0];
		array<Byte>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<Byte> pinnedProfile = &profileBytes[0];

		IncludeShim includeShim = IncludeShim( include );
		ID3D10Include* includePtr = NULL;
		if( include != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		std::vector<D3D10_SHADER_MACRO> macros = ShaderMacro::Marshal( defines, handles );
		D3D10_SHADER_MACRO* macrosPtr = macros.size() > 0 ? &macros[0] : NULL;

		HRESULT hr = D3DCompile( NULL, 0, reinterpret_cast<LPCSTR>( pinnedName ), macrosPtr, includePtr, 
			reinterpret_cast<LPCSTR>( pinnedFunction ), reinterpret_cast<LPCSTR>( pinnedProfile ),
			static_cast<UINT>( shaderFlags ), static_cast<UINT>( effectFlags ), &code, &errors );

		ShaderMacro::Unmarshal( macros, handles );

		String^ compilationErrorsLocal = Utilities::BlobToString( errors );
		compilationErrors = compilationErrorsLocal;

		if( RECORD_D3D10_EX( hr, ExceptionDataKey, compilationErrors ).IsFailure )
			return nullptr;

		if( code == NULL )
			return nullptr;

		return gcnew ShaderBytecode( code );
	}
}
}
