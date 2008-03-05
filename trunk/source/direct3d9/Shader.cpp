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
	bool Macro::operator == ( Macro left, Macro right )
	{
		return Macro::Equals( left, right );
	}

	bool Macro::operator != ( Macro left, Macro right )
	{
		return !Macro::Equals( left, right );
	}

	int Macro::GetHashCode()
	{
		return Name->GetHashCode() + Definition->GetHashCode();
	}

	bool Macro::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<Macro>( value ) );
	}

	bool Macro::Equals( Macro value )
	{
		return ( Name == value.Name && Definition == value.Definition );
	}

	bool Macro::Equals( Macro% value1, Macro% value2 )
	{
		return ( value1.Name == value2.Name && value1.Definition == value2.Definition );
	}

	bool ShaderSemantic::operator == ( ShaderSemantic left, ShaderSemantic right )
	{
		return ShaderSemantic::Equals( left, right );
	}

	bool ShaderSemantic::operator != ( ShaderSemantic left, ShaderSemantic right )
	{
		return !ShaderSemantic::Equals( left, right );
	}

	int ShaderSemantic::GetHashCode()
	{
		return Usage.GetHashCode() + UsageIndex.GetHashCode();
	}

	bool ShaderSemantic::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<ShaderSemantic>( value ) );
	}

	bool ShaderSemantic::Equals( ShaderSemantic value )
	{
		return ( Usage == value.Usage && UsageIndex == value.UsageIndex );
	}

	bool ShaderSemantic::Equals( ShaderSemantic% value1, ShaderSemantic% value2 )
	{
		return ( value1.Usage == value2.Usage && value1.UsageIndex == value2.UsageIndex );
	}

	IncludeShim::IncludeShim( Include^ wrappedInterface )
	{
		m_WrappedInterface = wrappedInterface;
		m_stream = nullptr;
	}

	HRESULT IncludeShim::Open( D3DXINCLUDE_TYPE includeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes )
	{
		SLIMDX_DEBUG_UNREFERENCED_PARAMETER(pParentData);
		SLIMDX_DEBUG_UNREFERENCED_PARAMETER(ppData);

		try
		{
			Stream^ stream;
			m_WrappedInterface->Open( static_cast<IncludeType>( includeType ), gcnew String(pFileName), stream );
			m_stream = stream;

			if( stream != nullptr )
			{
				if(stream->GetType() == DataStream::typeid)
				{
					//Magic shortcut if we happen to get a DataStream
					DataStream^ data = safe_cast<DataStream^>( stream );
					*ppData = data->RawPointer;
					*pBytes = static_cast<UINT>( data->Length );
				}
				else
				{
					//Read the stream into a byte array and pin it
					array<Byte>^ data = Utilities::ReadStream( stream, 0 );
					m_handle = GCHandle::Alloc( data, GCHandleType::Pinned );
					*ppData = m_handle.AddrOfPinnedObject().ToPointer();
					*pBytes = data->Length;
				}
			}
			else
			{
				*ppData = NULL;
				*pBytes = 0;
			}

			return S_OK;
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}
	}

	HRESULT IncludeShim::Close( LPCVOID pData )
	{
		SLIMDX_DEBUG_UNREFERENCED_PARAMETER(pData);

		try
		{
			if( m_handle.IsAllocated )
			{
				m_handle.Free();
			}

			Stream^ stream = m_stream;
			m_WrappedInterface->Close( stream );
			delete stream;
			m_stream = nullptr;

			return S_OK;
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}
	}

	//helper function to resolve array<Macro>^ to D3DXMACRO*
	D3DXMACRO* Macro::Marshal( array<Macro>^ macros, [Out] array<GCHandle>^% handles )
	{
		if( macros == nullptr )
		{
			handles = nullptr;
			return NULL;
		}

		//this array is null terminated, so we need to patch in an extra value
		D3DXMACRO* result = new D3DXMACRO[macros->Length + 1];
		handles = gcnew array<GCHandle>( macros->Length * 2 );

		for( int i = 0; i < macros->Length; ++i )
		{
			array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( macros[i].Name );
			array<Byte>^ defBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( macros[i].Definition );

			handles[2 * i] = GCHandle::Alloc( nameBytes, GCHandleType::Pinned );
			handles[2 * i + 1] = GCHandle::Alloc( defBytes, GCHandleType::Pinned );

			result[i].Name = reinterpret_cast<LPCSTR>( handles[2 * i].AddrOfPinnedObject().ToPointer() );
			result[i].Definition = reinterpret_cast<LPCSTR>( handles[2 * i + 1].AddrOfPinnedObject().ToPointer() );
		}

		result[macros->Length].Name = NULL;
		result[macros->Length].Definition = NULL;

		return result;
	}

	void Macro::Unmarshal( D3DXMACRO* macros, array<GCHandle>^ handles )
	{
		delete[] macros;
		if( handles != nullptr )
		{
			for( int i = 0; i < handles->Length; ++i )
			{
				handles[i].Free();
			}
		}
	}

	ShaderBytecode::ShaderBytecode( ID3DXBuffer* pointer )
	{
		Construct( pointer );
	}

	ShaderBytecode::ShaderBytecode( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	ShaderBytecode^ ShaderBytecode::FromPointer( ID3DXBuffer* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		ShaderBytecode^ tableEntry = safe_cast<ShaderBytecode^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew ShaderBytecode( pointer );
	}

	ShaderBytecode^ ShaderBytecode::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		ShaderBytecode^ tableEntry = safe_cast<ShaderBytecode^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew ShaderBytecode( pointer );
	}


	DataStream^ ShaderBytecode::GetData()
	{
		return gcnew DataStream( InternalPointer->GetBufferPointer(), InternalPointer->GetBufferSize(), true, true, false );
	}

	ConstantTable^ ShaderBytecode::GetConstantTable()
	{
		ID3DXConstantTable* constantTable;
		HRESULT hr = D3DXGetShaderConstantTable( reinterpret_cast<const DWORD*>( InternalPointer->GetBufferPointer() ), &constantTable );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return ConstantTable::FromPointer( constantTable );
	}

	array<ShaderSemantic>^ ShaderBytecode::GetInputSemantics()
	{
		UINT count = 0;
		const DWORD* function = reinterpret_cast<const DWORD*>( InternalPointer->GetBufferPointer() );

		HRESULT hr = D3DXGetShaderInputSemantics( function, NULL, &count );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;
		
		array<ShaderSemantic>^ inputs = gcnew array<ShaderSemantic>( count );
		pin_ptr<ShaderSemantic> pinnedInputs = &inputs[0];

		hr = D3DXGetShaderInputSemantics( function, reinterpret_cast<D3DXSEMANTIC*>( pinnedInputs ), &count );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;
		
		return inputs;
	}

	array<ShaderSemantic>^ ShaderBytecode::GetOutputSemantics()
	{
		UINT count = 0;
		const DWORD* function = reinterpret_cast<const DWORD*>( InternalPointer->GetBufferPointer() );

		HRESULT hr = D3DXGetShaderOutputSemantics( function, NULL, &count );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;
		
		array<ShaderSemantic>^ outputs = gcnew array<ShaderSemantic>( count );
		pin_ptr<ShaderSemantic> pinnedOutputs = &outputs[0];

		hr = D3DXGetShaderOutputSemantics( function, reinterpret_cast<D3DXSEMANTIC*>( pinnedOutputs ), &count );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;
		
		return outputs;
	}

	array<String^>^ ShaderBytecode::GetSamplers()
	{
		UINT count = 0;
		const DWORD* function = reinterpret_cast<const DWORD*>( InternalPointer->GetBufferPointer() );

		HRESULT hr = D3DXGetShaderSamplers( function, NULL, &count );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;
		
		stack_vector<LPCSTR> samplers( count );

		hr = D3DXGetShaderSamplers( function, &samplers[0], &count );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;
		
		array<String^>^ outputSamplers = gcnew array<String^>( count );
		for( UINT i = 0; i < count; ++i )
		{
			outputSamplers[i] = gcnew String( samplers[i] );
		}

		return outputSamplers;
	}

	int ShaderBytecode::Version::get()
	{
		const DWORD* function = reinterpret_cast<const DWORD*>( InternalPointer->GetBufferPointer() );
		return static_cast<int>( D3DXGetShaderVersion( function ) );
	}

	//D3DXAssembleShader
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
		D3DXMACRO* macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXAssembleShader( reinterpret_cast<LPCSTR>( pinnedData ), sourceData->Length, macros, includePtr,
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

	//D3DXAssembleShaderFromFile
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
		D3DXMACRO* macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXAssembleShaderFromFile( pinnedFileName, macros, includePtr,
			static_cast<DWORD>( flags ), &shaderBuffer, &errorBuffer );

		//clean up after marshaling macros
		Macro::Unmarshal( macros, handles );
		//marshal errors if necessary
		errors = Utilities::BufferToString( errorBuffer );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return ShaderBytecode::FromPointer( shaderBuffer );
   }

	//D3DXCompileShader
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
		D3DXMACRO* macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXCompileShader( reinterpret_cast<LPCSTR>( pinnedData ), sourceData->Length, macros, includePtr,
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
		D3DXMACRO* macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXCompileShader( reinterpret_cast<LPCSTR>( pinnedData ), sourceData->Length, macros, includePtr,
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

	//D3DXCompileShaderFromFile
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
		D3DXMACRO* macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXCompileShaderFromFile( pinnedFileName, macros, includePtr,
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
		D3DXMACRO* macros = Macro::Marshal( defines, handles );

		HRESULT hr = D3DXCompileShaderFromFile( pinnedFileName, macros, includePtr,
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