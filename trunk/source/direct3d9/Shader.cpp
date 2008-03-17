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
#include <d3d9.h>
#include <d3dx9.h>
#include <vcclr.h>
#include <memory>

#include "../DataStream.h"
#include "../StackAlloc.h"

#include "Direct3D9Exception.h"

#include "Device.h"
#include "Shader.h"

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace Direct3D9
{
	// D3DXAssembleShader
	ShaderBytecode^ Shader::Assemble( array<Byte>^ sourceData, array<Macro>^ defines,
		Include^ includeFile, ShaderFlags flags, [Out] String^% errors )
	{
		ID3DXBuffer* shaderBuffer;
		ID3DXBuffer* errorBuffer;
		pin_ptr<Byte> pinnedData = &sourceData[0];

		IncludeShim includeShim = IncludeShim( includeFile );
		ID3DXInclude* includePtr = NULL;
		if( includeFile != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		std::vector<D3DXMACRO> macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXAssembleShader( reinterpret_cast<LPCSTR>( pinnedData ), sourceData->Length, &macros[0], includePtr,
			static_cast<DWORD>( flags ), &shaderBuffer, &errorBuffer );

		//clean up after marshaling macros
		Macro::Unmarshal( macros, handles );
		//marshal errors if necessary
		errors = Utilities::BufferToString( errorBuffer );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return ShaderBytecode::FromPointer( shaderBuffer );
	}

	ShaderBytecode^ Shader::Assemble( String^ sourceData, array<Macro>^ defines,
		Include^ includeFile, ShaderFlags flags, [Out] String^% errors )
	{
		array<Byte>^ data = System::Text::ASCIIEncoding::ASCII->GetBytes( sourceData );
		return Assemble( data, defines, includeFile, flags, errors );
	}

	// D3DXAssembleShaderFromFile
	ShaderBytecode^ Shader::AssembleFromFile( String^ fileName, array<Macro>^ defines,
		Include^ includeFile, ShaderFlags flags, [Out] String^% errors )
	{
		ID3DXBuffer* shaderBuffer;
		ID3DXBuffer* errorBuffer;
		pin_ptr<const wchar_t> pinnedFileName = PtrToStringChars( fileName );

		IncludeShim includeShim = IncludeShim( includeFile );
		ID3DXInclude* includePtr = NULL;
		if( includeFile != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		std::vector<D3DXMACRO> macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXAssembleShaderFromFile( pinnedFileName, &macros[0], includePtr,
			static_cast<DWORD>( flags ), &shaderBuffer, &errorBuffer );

		//clean up after marshaling macros
		Macro::Unmarshal( macros, handles );
		//marshal errors if necessary
		errors = Utilities::BufferToString( errorBuffer );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return ShaderBytecode::FromPointer( shaderBuffer );
   }

	// D3DXCompileShader
	ShaderBytecode^ Shader::Compile( array<Byte>^ sourceData, array<Macro>^ defines,
		Include^ includeFile, String^ functionName, String^ profile, ShaderFlags flags,
		[Out] String^% errors, [Out] ConstantTable^% constantTable )
	{
		ID3DXBuffer* shaderBuffer;
		ID3DXBuffer* errorBuffer;
		ID3DXConstantTable* constants;
		pin_ptr<Byte> pinnedData = &sourceData[0];
		
		array<Byte>^ functionBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( functionName );
		pin_ptr<Byte> pinnedFunction = &functionBytes[0];
		array<Byte>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<Byte> pinnedProfile = &profileBytes[0];

		IncludeShim includeShim = IncludeShim( includeFile );
		ID3DXInclude* includePtr = NULL;
		if( includeFile != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		std::vector<D3DXMACRO> macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXCompileShader( reinterpret_cast<LPCSTR>( pinnedData ), sourceData->Length, &macros[0], includePtr,
			reinterpret_cast<LPCSTR>( pinnedFunction ), reinterpret_cast<LPCSTR>( pinnedProfile ),
			static_cast<DWORD>( flags ), &shaderBuffer, &errorBuffer, &constants );

		//clean up after marshaling macros
		Macro::Unmarshal( macros, handles );
		//marshal errors if necessary
		errors = Utilities::BufferToString( errorBuffer );
		
		if( RECORD_D3D9( hr ).IsFailure )
		{
			constantTable = nullptr;
			return nullptr;
		}

		return ShaderBytecode::FromPointer( shaderBuffer );
	}

	ShaderBytecode^ Shader::Compile( String^ sourceData, array<Macro>^ defines,
		Include^ includeFile, String^ functionName, String^ profile, ShaderFlags flags,
		[Out] String^% errors, [Out] ConstantTable^% constantTable )
	{
		array<Byte>^ data = System::Text::ASCIIEncoding::ASCII->GetBytes( sourceData );
		return Compile( data, defines, includeFile, functionName, profile, flags, errors, constantTable );
	}

	ShaderBytecode^ Shader::Compile( array<Byte>^ sourceData, array<Macro>^ defines,
		Include^ includeFile, String^ functionName, String^ profile, ShaderFlags flags,
		[Out] String^% errors )
	{
		ID3DXBuffer* shaderBuffer;
		ID3DXBuffer* errorBuffer;
		pin_ptr<Byte> pinnedData = &sourceData[0];
		
		array<Byte>^ functionBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( functionName );
		pin_ptr<Byte> pinnedFunction = &functionBytes[0];
		array<Byte>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<Byte> pinnedProfile = &profileBytes[0];

		IncludeShim includeShim = IncludeShim( includeFile );
		ID3DXInclude* includePtr = NULL;
		if( includeFile != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		std::vector<D3DXMACRO> macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXCompileShader( reinterpret_cast<LPCSTR>( pinnedData ), sourceData->Length, &macros[0], includePtr,
			reinterpret_cast<LPCSTR>( pinnedFunction ), reinterpret_cast<LPCSTR>( pinnedProfile ),
			static_cast<DWORD>( flags ), &shaderBuffer, &errorBuffer, NULL );

		//clean up after marshaling macros
		Macro::Unmarshal( macros, handles );
		//marshal errors if necessary
		errors = Utilities::BufferToString( errorBuffer );
		
		if( RECORD_D3D9( hr ).IsFailure )
		{
			return nullptr;
		}

		return ShaderBytecode::FromPointer( shaderBuffer );
	}

	ShaderBytecode^ Shader::Compile( String^ sourceData, array<Macro>^ defines,
		Include^ includeFile, String^ functionName, String^ profile, ShaderFlags flags,
		[Out] String^% errors )
	{
		array<Byte>^ data = System::Text::ASCIIEncoding::ASCII->GetBytes( sourceData );
		return Compile( data, defines, includeFile, functionName, profile, flags, errors );
	}

	// D3DXCompileShaderFromFile
	ShaderBytecode^ Shader::CompileFromFile( String^ fileName, array<Macro>^ defines,
		Include^ includeFile, String^ functionName, String^ profile, ShaderFlags flags,
		[Out] String^% errors, [Out] ConstantTable^% constantTable )
	{
		ID3DXBuffer* shaderBuffer;
		ID3DXBuffer* errorBuffer;
		ID3DXConstantTable* constants;
		pin_ptr<const wchar_t> pinnedFileName = PtrToStringChars( fileName );
		
		array<Byte>^ functionBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( functionName );
		pin_ptr<Byte> pinnedFunction = &functionBytes[0];
		array<Byte>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<Byte> pinnedProfile = &profileBytes[0];

		IncludeShim includeShim = IncludeShim( includeFile );
		ID3DXInclude* includePtr = NULL;
		if( includeFile != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		std::vector<D3DXMACRO> macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXCompileShaderFromFile( pinnedFileName, &macros[0], includePtr,
			reinterpret_cast<LPCSTR>( pinnedFunction ), reinterpret_cast<LPCSTR>( pinnedProfile ),
			static_cast<DWORD>( flags ), &shaderBuffer, &errorBuffer, &constants );

		//clean up after marshaling macros
		Macro::Unmarshal( macros, handles );
		//marshal errors if necessary
		errors = Utilities::BufferToString( errorBuffer );
		
		if( RECORD_D3D9( hr ).IsFailure )
		{
			constantTable = nullptr;
			return nullptr;
		}

		return ShaderBytecode::FromPointer( shaderBuffer );
	}

	ShaderBytecode^ Shader::CompileFromFile( String^ fileName, array<Macro>^ defines,
		Include^ includeFile, String^ functionName, String^ profile, ShaderFlags flags,
		[Out] String^% errors )
	{
		ID3DXBuffer* shaderBuffer;
		ID3DXBuffer* errorBuffer;
		pin_ptr<const wchar_t> pinnedFileName = PtrToStringChars( fileName );
		
		array<Byte>^ functionBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( functionName );
		pin_ptr<Byte> pinnedFunction = &functionBytes[0];
		array<Byte>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<Byte> pinnedProfile = &profileBytes[0];

		IncludeShim includeShim = IncludeShim( includeFile );
		ID3DXInclude* includePtr = NULL;
		if( includeFile != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		std::vector<D3DXMACRO> macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXCompileShaderFromFile( pinnedFileName, &macros[0], includePtr,
			reinterpret_cast<LPCSTR>( pinnedFunction ), reinterpret_cast<LPCSTR>( pinnedProfile ),
			static_cast<DWORD>( flags ), &shaderBuffer, &errorBuffer, NULL );

		Macro::Unmarshal( macros, handles );
		errors = Utilities::BufferToString( errorBuffer );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return ShaderBytecode::FromPointer( shaderBuffer );
	}

	int Shader::MajorVersion( int version )
	{
		return D3DSHADER_VERSION_MAJOR( version );
	}

	int Shader::MinorVersion( int version )
	{
		return D3DSHADER_VERSION_MINOR( version );
	}

	Version^ Shader::ParseVersion( int version )
	{
		return gcnew Version( MajorVersion( version ), MinorVersion( version ) );
	}
}
}