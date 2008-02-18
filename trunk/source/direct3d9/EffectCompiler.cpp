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

#include "../DataStream.h"
#include "../ComObject.h"

#include "Direct3D9Exception.h"

#include "EffectCompiler.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace Direct3D9
{
	EffectCompiler::EffectCompiler( ID3DXEffectCompiler* compiler ) : BaseEffect( compiler )
	{
		if( compiler == NULL )
			throw gcnew ArgumentNullException( "compiler" );

		Construct(compiler);
	}

	EffectCompiler::EffectCompiler( IntPtr compiler )
	{
		Construct( compiler, NativeInterface );
	}

	EffectCompiler::EffectCompiler( String^ data, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] String^% errors )
	{
		InitThis( System::Text::ASCIIEncoding::ASCII->GetBytes( data ), defines, includeFile, flags, errors );
	}

	EffectCompiler::EffectCompiler( array<Byte>^ data, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] String^% errors )
	{
		InitThis( data, defines, includeFile, flags, errors );
	}

	void EffectCompiler::InitThis( array<Byte>^ data, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] String^% errors )
	{
		ID3DXEffectCompiler* compiler;
		ID3DXBuffer* errorBuffer;
		pin_ptr<Byte> pinnedData = &data[0];

		IncludeShim includeShim = IncludeShim( includeFile );
		ID3DXInclude* includePtr = NULL;
		if( includeFile != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		D3DXMACRO* macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXCreateEffectCompiler( reinterpret_cast<LPCSTR>( pinnedData ), data->Length, macros, includePtr,
			static_cast<DWORD>( flags ), &compiler, &errorBuffer );
		
		//clean up after marshaling macros
		Macro::Unmarshal( macros, handles );
		//marshal errors if necessary
		errors = Utilities::BufferToString( errorBuffer );
		
		Result::Record( hr );
		if( FAILED( hr ) )
			throw gcnew Direct3D9Exception();

		Construct(compiler);
	}

	EffectCompiler^ EffectCompiler::FromFile( String^ fileName, array<Macro>^ defines,
		Include^ includeFile, ShaderFlags flags, [Out] String^% errors )
	{
		ID3DXEffectCompiler* compiler;
		ID3DXBuffer* errorBuffer;
		pin_ptr<const wchar_t> pinnedFile = PtrToStringChars( fileName );

		IncludeShim includeShim = IncludeShim( includeFile );
		ID3DXInclude* includePtr = NULL;
		if( includeFile != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		D3DXMACRO* macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXCreateEffectCompilerFromFile( reinterpret_cast<LPCTSTR>( pinnedFile ), macros, includePtr,
			static_cast<DWORD>( flags ), &compiler, &errorBuffer );
		
		//clean up after marshaling macros
		Macro::Unmarshal( macros, handles );
		//marshal errors if necessary
		errors = Utilities::BufferToString( errorBuffer );
		
		Result::Record( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew EffectCompiler( compiler );
	}

	ShaderBytecode^ EffectCompiler::CompileShader( EffectHandle^ functionHandle, String^ target, ShaderFlags flags,
		[Out] String^% compilationErrors, [Out] ConstantTable^% constantTable )
	{
		D3DXHANDLE handle = functionHandle != nullptr ? functionHandle->InternalHandle : NULL;
		array<Byte>^ targetBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( target );
		pin_ptr<unsigned char> pinnedTarget = &targetBytes[0];

		ID3DXBuffer* errorBuffer;
		ID3DXBuffer* shader;
		ID3DXConstantTable* table;

		HRESULT hr = CompilerPointer->CompileShader( handle, reinterpret_cast<LPCSTR>( pinnedTarget ), static_cast<DWORD>( flags ), &shader, &errorBuffer, &table );

		//marshal errors if necessary
		compilationErrors = Utilities::BufferToString( errorBuffer );
			
		// CheckHResult() is not used because we need to include the compiler errors.
		if( Configuration::EnableExceptions && FAILED(hr) )
		{
			Direct3D9Exception^ ex = gcnew Direct3D9Exception( hr );
			ex->Data->Add( "CompilationErrors", compilationErrors );
			throw ex;
		}

		SetLastError( hr );		
		if( FAILED( hr ) )
			return nullptr;

		constantTable = gcnew ConstantTable( table );
		return gcnew ShaderBytecode( shader );
	}

	ShaderBytecode^ EffectCompiler::CompileShader( EffectHandle^ functionHandle, String^ target, ShaderFlags flags,
		[Out] String^% compilationErrors )
	{
		D3DXHANDLE handle = functionHandle != nullptr ? functionHandle->InternalHandle : NULL;
		array<Byte>^ targetBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( target );
		pin_ptr<unsigned char> pinnedTarget = &targetBytes[0];

		ID3DXBuffer* errorBuffer;
		ID3DXBuffer* shader;

		HRESULT hr = CompilerPointer->CompileShader( handle, reinterpret_cast<LPCSTR>( pinnedTarget ), static_cast<DWORD>( flags ), &shader, &errorBuffer, NULL );

		//marshal errors if necessary
		if( errorBuffer != NULL )
		{
			compilationErrors = gcnew String( reinterpret_cast<const char*>( errorBuffer->GetBufferPointer() ) );
		}
		else
		{
			compilationErrors = String::Empty;
		}
			
		// CheckHResult() is not used because we need to include the compiler errors.
		if( Configuration::EnableExceptions && FAILED(hr) )
		{
			Direct3D9Exception^ ex = gcnew Direct3D9Exception( hr );
			ex->Data->Add( "CompilationErrors", compilationErrors );
			throw ex;
		}

		SetLastError( hr );		
		if( FAILED( hr ) )
			return nullptr;

		return gcnew ShaderBytecode( shader );
	}

	ShaderBytecode^ EffectCompiler::CompileShader( EffectHandle^ functionHandle, String^ target, ShaderFlags flags )
	{
		String^ errors;
		return CompileShader( functionHandle, target, flags, errors );
	}

	DataStream^ EffectCompiler::CompileEffect( ShaderFlags flags, [Out] String^% compilationErrors )
	{
		ID3DXBuffer* effect;
		ID3DXBuffer* errorBuffer;

		HRESULT hr = CompilerPointer->CompileEffect( static_cast<DWORD>( flags ), &effect, &errorBuffer );

		//marshal errors if necessary
		if( errorBuffer != NULL )
		{
			compilationErrors = gcnew String( reinterpret_cast<const char*>( errorBuffer->GetBufferPointer() ) );
		}
		else
		{
			compilationErrors = String::Empty;
		}
		
		// CheckHResult() is not used because we need to include the compiler errors.
		if( Configuration::EnableExceptions && FAILED(hr) )
		{
			Direct3D9Exception^ ex = gcnew Direct3D9Exception( hr );
			ex->Data->Add( "CompilationErrors", compilationErrors );
			throw ex;
		}

		SetLastError( hr );		
		if( FAILED( hr ) )
			return nullptr;

		return gcnew DataStream( effect );
	}

	DataStream^ EffectCompiler::CompileEffect( ShaderFlags flags )
	{
		String^ errors;
		return CompileEffect( flags, errors );
	}

	void EffectCompiler::SetLiteral( EffectHandle^ handle, bool literal )
	{
		D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
		HRESULT hr = CompilerPointer->SetLiteral( nativeHandle, literal );
		Result::Record( hr );
	}

	bool EffectCompiler::GetLiteral( EffectHandle^ handle )
	{
		D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
		BOOL literal = false;
		HRESULT hr = CompilerPointer->GetLiteral( nativeHandle, &literal );
		Result::Record( hr );
		
		return literal > 0;
	}
}
}