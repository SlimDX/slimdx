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
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "../DataStream.h"
#include "../ComObject.h"

#include "Direct3D9Exception.h"

#include "EffectCompiler.h"

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace Direct3D9
{
	EffectCompiler::EffectCompiler( String^ data, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] String^% compilationErrors )
	{
		ID3DXEffectCompiler* compiler;
		ID3DXBuffer* errorBuffer;

		array<Byte>^ dataBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( data );
		pin_ptr<Byte> pinnedData = &dataBytes[0];

		IncludeShim includeShim = IncludeShim( includeFile );
		ID3DXInclude* includePtr = NULL;
		if( includeFile != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		std::vector<D3DXMACRO> macros = Macro::Marshal( defines, handles );
		D3DXMACRO* macrosPtr = macros.size() > 0 ? &macros[0] : NULL;

		HRESULT hr = D3DXCreateEffectCompiler( reinterpret_cast<LPCSTR>( pinnedData ), data->Length, macrosPtr, includePtr,
			static_cast<DWORD>( flags ), &compiler, &errorBuffer );

		Macro::Unmarshal( macros, handles );
		compilationErrors = Utilities::BufferToString( errorBuffer );
		
		if( RECORD_D3D9_EX( hr, Effect::ExceptionDataKey, compilationErrors ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct( compiler );
	}

	EffectCompiler::EffectCompiler( String^ data, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags )
	{
		ID3DXEffectCompiler* compiler;
		ID3DXBuffer* errorBuffer;

		array<Byte>^ dataBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( data );
		pin_ptr<Byte> pinnedData = &dataBytes[0];

		IncludeShim includeShim = IncludeShim( includeFile );
		ID3DXInclude* includePtr = NULL;
		if( includeFile != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		std::vector<D3DXMACRO> macros = Macro::Marshal( defines, handles );
		D3DXMACRO* macrosPtr = macros.size() > 0 ? &macros[0] : NULL;

		HRESULT hr = D3DXCreateEffectCompiler( reinterpret_cast<LPCSTR>( pinnedData ), data->Length, macrosPtr, includePtr,
			static_cast<DWORD>( flags ), &compiler, &errorBuffer );

		Macro::Unmarshal( macros, handles );
		String^ compilationErrors = Utilities::BufferToString( errorBuffer );
		
		if( RECORD_D3D9_EX( hr, Effect::ExceptionDataKey, compilationErrors ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct( compiler );
	}

	EffectCompiler::EffectCompiler( String^ data, ShaderFlags flags )
	{
		ID3DXEffectCompiler* compiler;
		ID3DXBuffer* errorBuffer;

		array<Byte>^ dataBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( data );
		pin_ptr<Byte> pinnedData = &dataBytes[0];

		HRESULT hr = D3DXCreateEffectCompiler( reinterpret_cast<LPCSTR>( pinnedData ), data->Length, NULL, NULL,
			static_cast<DWORD>( flags ), &compiler, &errorBuffer );

		String^ compilationErrors = Utilities::BufferToString( errorBuffer );
		
		if( RECORD_D3D9_EX( hr, Effect::ExceptionDataKey, compilationErrors ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct( compiler );
	}

	EffectCompiler^ EffectCompiler::FromMemory_Internal( const char* memory, UINT size, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, String^* compilationErrors )
	{
		ID3DXEffectCompiler* compiler;
		ID3DXBuffer* errorBuffer;

		IncludeShim includeShim = IncludeShim( includeFile );
		ID3DXInclude* includePtr = NULL;
		if( includeFile != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		std::vector<D3DXMACRO> macros = Macro::Marshal( defines, handles );
		D3DXMACRO* macrosPtr = macros.size() > 0 ? &macros[0] : NULL;

		HRESULT hr = D3DXCreateEffectCompiler( memory, size, macrosPtr, includePtr,
			static_cast<DWORD>( flags ), &compiler, &errorBuffer );

		Macro::Unmarshal( macros, handles );

		String^ compilationErrorsLocal = Utilities::BufferToString( errorBuffer );
		if( compilationErrors != NULL )
			*compilationErrors = compilationErrorsLocal;
		
		if( RECORD_D3D9_EX( hr, Effect::ExceptionDataKey, compilationErrorsLocal ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		return EffectCompiler::FromPointer( compiler );
	}

	EffectCompiler^ EffectCompiler::FromMemory( array<Byte>^ data, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] String^% compilationErrors )
	{
		pin_ptr<Byte> pinnedData = &data[0];
		String^ compileErrorsLocal;

		EffectCompiler^ effectCompiler = FromMemory_Internal( reinterpret_cast<const char*>( pinnedData ),
			static_cast<UINT>( data->Length ), defines, includeFile, flags, &compileErrorsLocal );
		compilationErrors = compileErrorsLocal;

		return effectCompiler;
	}

	EffectCompiler^ EffectCompiler::FromMemory( array<Byte>^ data, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags )
	{
		pin_ptr<Byte> pinnedData = &data[0];

		return FromMemory_Internal( reinterpret_cast<const char*>( pinnedData ),
			static_cast<UINT>( data->Length ), defines, includeFile, flags, NULL );
	}

	EffectCompiler^ EffectCompiler::FromMemory( array<Byte>^ data, ShaderFlags flags )
	{
		pin_ptr<Byte> pinnedData = &data[0];

		return FromMemory_Internal( reinterpret_cast<const char*>( pinnedData ),
			static_cast<UINT>( data->Length ), nullptr, nullptr, flags, NULL );
	}

	EffectCompiler^ EffectCompiler::FromStream( Stream^ stream, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] String^% compilationErrors )
	{
		DataStream^ ds = nullptr;
		array<Byte>^ data = Utilities::ReadStream( stream, 0, &ds );
		if( data == nullptr )
		{
			String^ compilationErrorsLocal;
			UINT size = static_cast<UINT>( ds->RemainingLength );
			EffectCompiler^ effectCompiler = FromMemory_Internal( ds->SeekToEnd(), size, defines, includeFile, flags, &compilationErrorsLocal );

			compilationErrors = compilationErrorsLocal;
			return effectCompiler;
		}

		return FromMemory( data, defines, includeFile, flags, compilationErrors );
	}

	EffectCompiler^ EffectCompiler::FromStream( Stream^ stream, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags )
	{
		DataStream^ ds = nullptr;
		array<Byte>^ data = Utilities::ReadStream( stream, 0, &ds );
		if( data == nullptr )
		{
			UINT size = static_cast<UINT>( ds->RemainingLength );
			return FromMemory_Internal( ds->SeekToEnd(), size, defines, includeFile, flags, NULL );
		}

		return FromMemory( data, defines, includeFile, flags );
	}

	EffectCompiler^ EffectCompiler::FromStream( Stream^ stream, ShaderFlags flags )
	{
		DataStream^ ds = nullptr;
		array<Byte>^ data = Utilities::ReadStream( stream, 0, &ds );
		if( data == nullptr )
		{
			UINT size = static_cast<UINT>( ds->RemainingLength );
			return FromMemory_Internal( ds->SeekToEnd(), size, nullptr, nullptr, flags, NULL );
		}

		return FromMemory( data, flags );
	}

	EffectCompiler^ EffectCompiler::FromFile( String^ fileName, array<Macro>^ defines, Include^ includeFile, 
		ShaderFlags flags, [Out] String^% errors )
	{
		ID3DXEffectCompiler* compiler;
		ID3DXBuffer* errorBuffer;

		pin_ptr<const wchar_t> pinnedFile = PtrToStringChars( fileName );

		IncludeShim includeShim = IncludeShim( includeFile );
		ID3DXInclude* includePtr = NULL;
		if( includeFile != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		std::vector<D3DXMACRO> macros = Macro::Marshal( defines, handles );
		D3DXMACRO* macrosPtr = macros.size() > 0 ? &macros[0] : NULL;

		HRESULT hr = D3DXCreateEffectCompilerFromFile( reinterpret_cast<LPCTSTR>( pinnedFile ), macrosPtr, includePtr,
			static_cast<DWORD>( flags ), &compiler, &errorBuffer );

		Macro::Unmarshal( macros, handles );
		errors = Utilities::BufferToString( errorBuffer );
		
		if( RECORD_D3D9_EX( hr, Effect::ExceptionDataKey, errors ).IsFailure )
			return nullptr;

		return EffectCompiler::FromPointer( compiler );
	}

	EffectCompiler^ EffectCompiler::FromFile( String^ fileName, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags )
	{
		ID3DXEffectCompiler* compiler;
		ID3DXBuffer* errorBuffer;

		pin_ptr<const wchar_t> pinnedFile = PtrToStringChars( fileName );

		IncludeShim includeShim = IncludeShim( includeFile );
		ID3DXInclude* includePtr = NULL;
		if( includeFile != nullptr )
			includePtr = &includeShim;

		array<GCHandle>^ handles;
		std::vector<D3DXMACRO> macros = Macro::Marshal( defines, handles );
		D3DXMACRO* macrosPtr = macros.size() > 0 ? &macros[0] : NULL;

		HRESULT hr = D3DXCreateEffectCompilerFromFile( reinterpret_cast<LPCTSTR>( pinnedFile ), macrosPtr, includePtr,
			static_cast<DWORD>( flags ), &compiler, &errorBuffer );

		Macro::Unmarshal( macros, handles );
		String^ errors = Utilities::BufferToString( errorBuffer );
		
		if( RECORD_D3D9_EX( hr, Effect::ExceptionDataKey, errors ).IsFailure )
			return nullptr;

		return EffectCompiler::FromPointer( compiler );
	}

	EffectCompiler^ EffectCompiler::FromFile( String^ fileName, ShaderFlags flags )
	{
		ID3DXEffectCompiler* compiler;
		ID3DXBuffer* errorBuffer;

		pin_ptr<const wchar_t> pinnedFile = PtrToStringChars( fileName );

		HRESULT hr = D3DXCreateEffectCompilerFromFile( reinterpret_cast<LPCTSTR>( pinnedFile ), NULL, NULL,
			static_cast<DWORD>( flags ), &compiler, &errorBuffer );

		String^ errors = Utilities::BufferToString( errorBuffer );
		
		if( RECORD_D3D9_EX( hr, Effect::ExceptionDataKey, errors ).IsFailure )
			return nullptr;

		return EffectCompiler::FromPointer( compiler );
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

		HRESULT hr = InternalPointer->CompileShader( handle, reinterpret_cast<LPCSTR>( pinnedTarget ), static_cast<DWORD>( flags ), &shader, &errorBuffer, &table );

		compilationErrors = Utilities::BufferToString( errorBuffer );
			
		if( RECORD_D3D9_EX( hr, Effect::ExceptionDataKey, compilationErrors ).IsFailure )
			return nullptr;

		constantTable = ConstantTable::FromPointer( table );
		return ShaderBytecode::FromPointer( shader );
	}

	ShaderBytecode^ EffectCompiler::CompileShader( EffectHandle^ functionHandle, String^ target, ShaderFlags flags,
		[Out] String^% compilationErrors )
	{
		D3DXHANDLE handle = functionHandle != nullptr ? functionHandle->InternalHandle : NULL;
		array<Byte>^ targetBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( target );
		pin_ptr<unsigned char> pinnedTarget = &targetBytes[0];

		ID3DXBuffer* errorBuffer;
		ID3DXBuffer* shader;

		HRESULT hr = InternalPointer->CompileShader( handle, reinterpret_cast<LPCSTR>( pinnedTarget ), static_cast<DWORD>( flags ), &shader, &errorBuffer, NULL );

		if( errorBuffer != NULL )
			compilationErrors = Utilities::BufferToString( errorBuffer );
		else
			compilationErrors = String::Empty;
			
		if( RECORD_D3D9_EX( hr, Effect::ExceptionDataKey, compilationErrors ).IsFailure )
			return nullptr;

		return ShaderBytecode::FromPointer( shader );
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

		HRESULT hr = InternalPointer->CompileEffect( static_cast<DWORD>( flags ), &effect, &errorBuffer );

		if( errorBuffer != NULL )
			compilationErrors = Utilities::BufferToString( errorBuffer );
		else
			compilationErrors = String::Empty;
		
		if( RECORD_D3D9_EX( hr, Effect::ExceptionDataKey, compilationErrors ).IsFailure )
			return nullptr;

		return gcnew DataStream( effect );
	}

	DataStream^ EffectCompiler::CompileEffect( ShaderFlags flags )
	{
		String^ errors;
		return CompileEffect( flags, errors );
	}

	Result EffectCompiler::SetLiteral( EffectHandle^ handle, bool literal )
	{
		D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetLiteral( nativeHandle, literal );
		return RECORD_D3D9( hr );
	}

	bool EffectCompiler::GetLiteral( EffectHandle^ handle )
	{
		D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
		BOOL literal = false;
		HRESULT hr = InternalPointer->GetLiteral( nativeHandle, &literal );
		RECORD_D3D9( hr );
		
		return literal > 0;
	}
}
}